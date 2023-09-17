#include <algorithm>
#include "src\Core\Engine.h"
#include "src\Logics\Camera\Camera.h"
#include "src\Logics\States\State.h"
#include "src\Logics\Entities\Listener\RenderListener.h"
#include "src\Logics\Entities\Listener\MovingTickListener.h"
#include "src\Logics\Entities\Listener\StaticTickListener.h"
#include "Chunk.h"
#include "src\Graphics\Renderables\Border\CubeBorder.h"

#include "src\Physics\Colliders\Hitbox.h"

namespace clockwork {
	namespace logics {

		Chunk::Chunk() noexcept
			: m_chunkSystem(nullptr)
#if CHUNK_BORDER
			, m_border(nullptr)
#endif
		{

		}

		Chunk::~Chunk() noexcept//hier später wahrscheinlich alle gameobjects löschem
		{
#if CHUNK_BORDER
			if ( m_border )
			{
				delete m_border;
				m_border = nullptr;
			}
#endif
		}

		void Chunk::init(const maths::Vec3f& min, const maths::Vec3f& max, int idX, int idY, int idZ, ChunkSystem* chunkSystem) noexcept
		{
			m_min = min;
			m_max = max;
			m_id.x = idX;
			m_id.y = idY;
			m_id.z = idZ;
			m_chunkSystem = chunkSystem;
		}

		void Chunk::renderAdd() noexcept
		{
			for ( unsigned int i = 0; i < m_renderList.size(); ++i )
			{
				m_renderList[i]->renderAdd();
			}
#if CHUNK_BORDER
			if ( !m_border )
			{
				maths::Mat4f* modelmatrix = new maths::Mat4f();
				modelmatrix->scale(m_chunkSystem->m_chunkSize*0.5 - 0.001).translate(m_min + ( m_max - m_min ) / 2);
				m_border = new graphics::CubeBorder(modelmatrix,true,&m_chunkSystem->getState());
				m_border->add();
			}
#endif
		}

		void Chunk::renderRemove() noexcept
		{
			for ( unsigned int i = 0; i < m_renderList.size(); ++i )
			{
				m_renderList[i]->renderRemove();
			}
#if CHUNK_BORDER
			if ( m_border )
			{
				delete m_border;
				m_border = nullptr;
			}
#endif
		}

		void Chunk::fastTick() noexcept
		{
			for ( unsigned int i = 0; i < m_movingTickList.size(); ++i )
			{
				MovingTickListener* listener = m_movingTickList[i];
				Chunk& newChunk = m_chunkSystem->getChunkAt(listener->getPosition());
				if ( newChunk != *this )
				{
					this->removeMovingTickListener(listener);
					newChunk.addMovingTickListener(listener);
					RenderListener* r_listener  = dynamic_cast<RenderListener*>(listener);//WICHTIG AUCH FÜR ALLE ANDEREN LISTENER MACHEN(ausser static tick listener), aber keylistener, etc auch mit dynamic cast überprüfen | vielleicht auch in mediumtick verschrieben | THREAD_SAFE: ist wahrscheinlich nicht threadsafe
					if ( r_listener != nullptr )
					{
						this->removeRenderListener(r_listener);
						newChunk.addRenderListener(r_listener);
						if ( this->inRenderDistance()==true && newChunk.inRenderDistance() == false )
						{
							r_listener->renderRemove();
						}
						else if ( this->inRenderDistance() == false && newChunk.inRenderDistance() == true )
						{
							r_listener->renderAdd();
						}
					}
					listener->setChunk(&newChunk);
					const maths::Vec3i& ownId = this->getId();
					const maths::Vec3i& otherId = newChunk.getId();

					if ( newChunk.inTickDistance() )
					{
						if ( otherId.x < ownId.x )
							listener->fastTick();
						else if ( otherId.x == ownId.x )
						{
							if ( otherId.y < ownId.y )
								listener->fastTick();
							else if ( otherId.y == ownId.y )
							{
								if ( otherId.z < ownId.z )
									listener->fastTick();
							}
						}
					}
				}
				else
				{
					listener->fastTick();
				}
			}

			for ( unsigned int i = 0; i < m_staticTickList.size(); ++i )
			{
				m_staticTickList[i]->fastTick();
			}

		}

		void Chunk::slowTick() noexcept
		{
			for ( unsigned int i = 0; i < m_movingTickList.size(); ++i )
			{
				m_movingTickList[i]->slowTick();
			}

			for ( unsigned int i = 0; i < m_staticTickList.size(); ++i )
			{
				m_staticTickList[i]->slowTick();
			}
		}

		void Chunk::collisionTest(const Chunk& otherChunk) const noexcept
		{
			double time = engine->getTimeFactor();
			if ( otherChunk.inTickDistance() )
			{
				int outerCollider { -1 }, innerCollider { -1 };
				for ( unsigned int outer = 0; outer < m_movingTickList.size(); ++outer )
				{
					MovingTickListener* outerListener = m_movingTickList[outer];
					for ( unsigned int inner = 0; inner < otherChunk.m_movingTickList.size(); ++inner )
					{
						MovingTickListener* innerListener = otherChunk.m_movingTickList[inner];
						if ( 
							outerListener->getHitbox().fastCollides(innerListener->getHitbox(), outerListener->getPosition() + outerListener->getVelocity()*time, innerListener->getPosition() + innerListener->getVelocity()*time) &&
							outerListener->getHitbox().slowCollides(innerListener->getHitbox(), &outerCollider, &innerCollider) )
						{
							outerListener->onCollision(innerListener, outerCollider, innerCollider);
							if ( outerListener != m_movingTickList[outer] )
							{
								break;
							}
							innerListener->onCollision(outerListener, innerCollider, outerCollider);
						}
					}
					for ( unsigned int inner = 0; inner < otherChunk.m_staticTickList.size(); ++inner )
					{
						StaticTickListener* innerListener = otherChunk.m_staticTickList[inner];
						if (
							outerListener->getHitbox().fastCollides(innerListener->getHitbox(), outerListener->getPosition() + outerListener->getVelocity()*time, innerListener->getPosition()) &&
							outerListener->getHitbox().slowCollides(innerListener->getHitbox(), &outerCollider, &innerCollider) )
						{
							outerListener->onCollision(innerListener, outerCollider, innerCollider);
							if ( outerListener != m_movingTickList[outer] )
							{
								break;
							}
							innerListener->onCollision(outerListener, innerCollider, outerCollider);
						}
					}
				}
				for ( unsigned int outer = 0; outer < otherChunk.m_movingTickList.size(); ++outer )
				{
					MovingTickListener* outerListener = otherChunk.m_movingTickList[outer];
					for ( unsigned int inner = 0; inner < m_staticTickList.size(); ++inner )
					{
						StaticTickListener* innerListener = m_staticTickList[inner];
						if (
							outerListener->getHitbox().fastCollides(innerListener->getHitbox(), outerListener->getPosition() + outerListener->getVelocity()*time, innerListener->getPosition()) &&
							outerListener->getHitbox().slowCollides(innerListener->getHitbox(), &outerCollider, &innerCollider) )
						{
							outerListener->onCollision(innerListener, outerCollider, innerCollider);
							if ( outerListener != otherChunk.m_movingTickList[outer] )
							{
								break;
							}
							innerListener->onCollision(outerListener, innerCollider, outerCollider);
						}
					}
				}
			}
		}

		void Chunk::updateCollision() const noexcept
		{
			double time = engine->getTimeFactor();
			int outerCollider { -1 }, innerCollider { -1 };
			for ( unsigned int outer = 0; outer < m_movingTickList.size(); ++outer )
			{
				MovingTickListener* outerListener = m_movingTickList[outer];
				for ( unsigned int inner = outer + 1; inner < m_movingTickList.size(); ++inner )
				{
					MovingTickListener* innerListener = m_movingTickList[inner];
					if (
						outerListener->getHitbox().fastCollides(innerListener->getHitbox(), outerListener->getPosition() + outerListener->getVelocity()*time, innerListener->getPosition() + innerListener->getVelocity()*time) &&
						outerListener->getHitbox().slowCollides(innerListener->getHitbox(), &outerCollider, &innerCollider) )
					{
						outerListener->onCollision(innerListener, outerCollider, innerCollider);
						if ( outerListener != m_movingTickList[outer] )
						{
							break;
						}
						innerListener->onCollision(outerListener, innerCollider, outerCollider);
					}
				}
				for ( unsigned int inner = 0; inner < m_staticTickList.size(); ++inner )
				{
					StaticTickListener* innerListener = m_staticTickList[inner];
					if (
						outerListener->getHitbox().fastCollides(innerListener->getHitbox(), outerListener->getPosition() + outerListener->getVelocity()*time, innerListener->getPosition()) &&
						outerListener->getHitbox().slowCollides(innerListener->getHitbox(), &outerCollider, &innerCollider) )
					{
						outerListener->onCollision(innerListener, outerCollider, innerCollider);
						if ( outerListener != m_movingTickList[outer] )
						{
							break;
						}
						innerListener->onCollision(outerListener, innerCollider, outerCollider);
					}
				}
			}

			collisionTest(m_chunkSystem->getChunk(m_id.x - 1, m_id.y, m_id.z));
			for ( unsigned int chunkX = m_id.x - 1; chunkX <= m_id.x + 1; ++chunkX )
			{
				collisionTest(m_chunkSystem->getChunk(chunkX, m_id.y - 1, m_id.z));
				for ( unsigned int chunkY = m_id.y - 1; chunkY <= m_id.y + 1; ++chunkY )
				{
					collisionTest(m_chunkSystem->getChunk(chunkX, chunkY, m_id.z - 1));
				}
			}
		}

		void Chunk::addRenderListener(RenderListener* listener) noexcept
		{
			m_renderList.push_back(listener);
		}

		void Chunk::removeRenderListener(RenderListener* listener) noexcept
		{
			auto iterator = std::find(m_renderList.begin(), m_renderList.end(), listener);
#if CLOCKWORK_DEBUG
			if ( iterator == m_renderList.end() )
				std::cout << "Error Chunk::removeRenderListener(): The listener pointer is not in the renderList" << std::endl;
#endif
			m_renderList.erase(iterator);
		}

		void Chunk::addMovingTickListener(MovingTickListener* listener) noexcept
		{
			m_movingTickList.push_back(listener);
		}

		void Chunk::removeMovingTickListener(MovingTickListener* listener) noexcept
		{
			auto iterator = std::find(m_movingTickList.begin(), m_movingTickList.end(), listener);
#if CLOCKWORK_DEBUG
			if ( iterator == m_movingTickList.end() )
				std::cout << "Error Chunk::removeMovingTickListener(): The listener pointer is not in the movingTickList" << std::endl;
#endif
			m_movingTickList.erase(iterator);
		}

		void Chunk::addStaticTickListener(StaticTickListener* listener) noexcept
		{
			m_staticTickList.push_back(listener);
		}

		void Chunk::removeStaticTickListener(StaticTickListener* listener) noexcept
		{
			auto iterator = std::find(m_staticTickList.begin(), m_staticTickList.end(), listener);
#if CLOCKWORK_DEBUG
			if ( iterator == m_staticTickList.end() )
				std::cout << "Error Chunk::removeStaticTickListener(): The listener pointer is not in the staticTickList" << std::endl;
#endif
			m_staticTickList.erase(iterator);
		}

		const bool Chunk::inRenderDistance() const noexcept
		{
			const maths::Vec3i& otherId = m_chunkSystem->getCurrentChunk().getId();
			const maths::Vec3i& renderDistance = m_chunkSystem->getRenderDistance();
			if ( m_id.x >= otherId.x - renderDistance.x && m_id.x <= otherId.x + renderDistance.x && m_id.y >= otherId.y - renderDistance.y&& m_id.y <= otherId.y + renderDistance.y && m_id.z >= otherId.z - renderDistance.z && m_id.z <= otherId.z + renderDistance.z )
				return true;
			else
				return false;
		}

		const bool Chunk::inTickDistance() const noexcept
		{
			const maths::Vec3i& otherId = m_chunkSystem->getCurrentChunk().getId();
			const maths::Vec3i& tickDistance = m_chunkSystem->getTickDistance();
			if ( m_id.x >= otherId.x - tickDistance.x && m_id.x <= otherId.x + tickDistance.x && m_id.y >= otherId.y - tickDistance.y&& m_id.y <= otherId.y + tickDistance.y && m_id.z >= otherId.z - tickDistance.z && m_id.z <= otherId.z + tickDistance.z )
				return true;
			else
				return false;
		}

		const ChunkSystem& Chunk::getChunkSystem() const noexcept
		{
			return *m_chunkSystem;
		}

		ChunkSystem& Chunk::getChunkSystem() noexcept
		{
			return *m_chunkSystem;
		}

		bool operator==(const Chunk& c1, const Chunk& c2) noexcept
		{
			return c1.m_id == c2.m_id;
		}

		bool operator!=(const Chunk& c1, const Chunk& c2) noexcept
		{
			return c1.m_id != c2.m_id;
		}

	}
}
