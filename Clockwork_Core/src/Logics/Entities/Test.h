#pragma once
#include "Listener\RenderListener.h"
#include "src\Logics\Entities\Listener\MovingTickListener.h"
#include "src\Logics\Entities\Listener\StaticTickListener.h"
#include "src\Graphics\Renderables\Cube\Cube.h"
#include "src\Core\Engine.h"
#include "src\Core\Window.h"

#include "src\Logics\ChunkSystem\ChunkSystem.h"
#include "src\Logics\States\State.h"
#include "src\Logics\Camera\Camera.h"
#include "src\Physics\Colliders\CubeCollider.h"
#include "src\Physics\Colliders\Hitbox.h"

namespace clockwork {
	namespace logics {

		struct Block : public RenderListener, public StaticTickListener
		{
			graphics::InstancedCube cube;
			physics::CubeCollider cubeCollider;
			Block(int textureId, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				: GameObject(size, rotation, position, state), cube(textureId, this, renderer), cubeCollider(this)
			{
				RenderListener::init();
				m_hitbox.addCollider(&cubeCollider);
			}
			void renderAdd() noexcept override
			{
				cube.add();
			}
			void renderRemove() noexcept override
			{
				cube.remove();
			}
			void fastTick() noexcept override
			{
				double time = engine->getTimeFactor();//time scaling factor 
				this->GameObject::updateModelMatrix();
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_RIGHT) )
					m_rotation.y += 60 * time;
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_LEFT) )
					m_rotation.y -= 60 * time;
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_UP) )
					m_rotation.x += 60 * time;
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_DOWN) )
					m_rotation.x -= 60 * time;
				if ( m_rotation.x < 0 )
					m_rotation.x += 360;
				if ( m_rotation.y < 0 )
					m_rotation.y += 360;
			}
			void slowTick() noexcept override
			{

			}
			void onCollision(MovingTickListener* otherMoving, int ownColliderNumber, int otherColliderNumber) noexcept override
			{
				//MovingBlock* block = dynamic_cast<MovingBlock*>( otherMoving );///geht hier nicht, da alles in einer datei ist
				//std::cout << "COLLISION STATIC TO MOVING" << std::endl;
			}
		protected:
			void onMatrixChange() noexcept override
			{
				cube.setChanged(true);
			}
		};

		struct MovingBlock : public RenderListener, public MovingTickListener
		{
			graphics::InstancedCube cube;
			physics::CubeCollider cubeCollider;
			MovingBlock(int textureId, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				:GameObject(size, rotation, position, state), cube(textureId, this, renderer), cubeCollider(this)
			{
				RenderListener::init();
				m_hitbox.addCollider(&cubeCollider);
				m_velocity.x = -(float) ( rand() % 6000 + 1 ) / 1000 + (float) ( rand() % 6000 + 1 ) / 1000;
				m_velocity.y = -(float) ( rand() % 6000 + 1 ) / 1000 + (float) ( rand() % 6000 + 1 ) / 1000;
				m_velocity.z = -(float) ( rand() % 6000 + 1 ) / 1000 + (float) ( rand() % 6000 + 1 ) / 1000;
			}
		public:
			virtual void renderAdd() noexcept override
			{
				cube.add();
			}
			virtual void renderRemove() noexcept override
			{
				cube.remove();
			}
			virtual void fastTick() noexcept override
			{
				double time = engine->getTimeFactor();//time scaling factor 
				m_position += m_velocity * time;//WICHTIG in fastTick immer am anfang zuerst position neu kalkulieren anhand direction und modelmatrix updaten, dann ggf direction verändert und danach wird automatisch mit ggf collision direction wieder verändert
				this->GameObject::updateModelMatrix();

				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_RIGHT) )
					m_rotation.y += 60 * time;
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_LEFT) )
					m_rotation.y -= 60 * time;
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_UP) )
					m_rotation.x += 60 * time;
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_DOWN) )
					m_rotation.x -= 60 * time;
				if ( m_rotation.x < 0 )
					m_rotation.x += 360;
				if ( m_rotation.y < 0 )
					m_rotation.y += 360;

				// 				if ( m_position.distance(m_chunk->getChunkSystem().getState().getCurrentCamera().getPosition()) > 25 )
				// 				{
				// 					m_velocity = (m_chunk->getChunkSystem().getState().getCurrentCamera().getPosition() - m_position)/2;
				// 				}

			}
			virtual void slowTick() noexcept override
			{
				// 				m_direction.x = -(float) ( rand() % 6000 + 1 ) / 1000 + (float) ( rand() % 6000 + 1 ) / 1000;
				// 				m_direction.y = -(float) ( rand() % 6000 + 1 ) / 1000 + (float) ( rand() % 6000 + 1 ) / 1000;
				// 				m_direction.z = -(float) ( rand() % 6000 + 1 ) / 1000 + (float) ( rand() % 6000 + 1 ) / 1000;
			}
			virtual void onCollision(MovingTickListener* otherMoving, int ownColliderNumber, int otherColliderNumber) noexcept override
			{
				double time = engine->getTimeFactor();//time scaling factor 
				const MovingBlock* block = dynamic_cast<const MovingBlock*>( otherMoving );//eigentlich noch nullptr test
				if ( block != nullptr )//ggf noch mass und winkel berücksichtigen | reflektieren und ggf noch speed variable einbauen 
				{
					m_velocity = ( m_position - block->getPosition() ) * 2;//other direction
				}

			}
			virtual void onCollision(StaticTickListener* otherStatic, int ownColliderNumber, int otherColliderNumber) noexcept override//in collision sollten nur eigene sachen geregelt werden, aber eine kugel z.b. kann sich selbst löschen und dem anderen schaden machen, wenn es ein player/entity ist | nur das dann halt nicht in der anderen collision methode auch machen | es werden also keine const pointer übergeben
			{
				double time = engine->getTimeFactor();//time scaling factor 
				const Block* block = dynamic_cast<const Block*>( otherStatic );
				if ( block != nullptr )
				{
					m_velocity = ( m_position - block->getPosition() ) * 2;//other direction
				}
			}
		protected:
			void onMatrixChange() noexcept override
			{
				cube.setChanged(true);//wenn instanced
			}
		};

		struct Player : public RenderListener, public MovingTickListener
		{
			graphics::NormalCube cube;
			physics::CubeCollider cubeCollider;
			bool alive = true;
			std::vector<MovingBlock*> enemys;
			Player(State* state, graphics::Renderer* renderer) noexcept
				:GameObject({ 0.3f,0.5f,0.3f }, { 0,0,0 }, { 0,0,0 }, state), cube(0, false, this, renderer), cubeCollider(this)
			{
				RenderListener::init();
				m_hitbox.addCollider(&cubeCollider);
			}
		public:
			virtual void renderAdd() noexcept override
			{
				cube.add();
			}
			virtual void renderRemove() noexcept override
			{
				cube.remove();
			}
			virtual void fastTick() noexcept override
			{
				double time = engine->getTimeFactor();//time scaling factor 
				m_position += m_velocity * time;//WICHTIG in fastTick immer am anfang zuerst position neu kalkulieren anhand direction und modelmatrix updaten, dann ggf direction verändert und danach wird automatisch mit ggf collision direction wieder verändert
				this->GameObject::updateModelMatrix();
				const maths::Vec3f& camDir = m_chunk->getChunkSystem().getState().getCurrentCamera().getDirection() * 5;
				const maths::Vec3f& camRight = m_chunk->getChunkSystem().getState().getCurrentCamera().getRight() * 5;
				const maths::Vec3f& camUp = m_chunk->getChunkSystem().getState().getCurrentCamera().getUp() * 5;
				m_chunk->getChunkSystem().getState().getCurrentCamera().setPosition(m_position - camDir / 3);

				m_velocity = maths::Vec3f { 0,0,0 };
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_W) )//lieber später mit onkeypress machen und dann direction umschalten, aber noch mit boolean und onrelease wieder direction auf 0 | dann von keylistener erben 
				{
					m_velocity += camDir;
				}
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_S) )
				{
					m_velocity += -camDir;
				}
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_A) )
				{
					m_velocity += -camRight;
				}
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_D) )
				{
					m_velocity += camRight;
				}
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_LEFT_CONTROL) )
				{
					m_velocity += -camUp;
				}
				else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_SPACE) )
				{
					m_velocity += camUp;
				}
				if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_P) )
				{
					cube.setTexture(0, false);
					alive = true;
				}
			}
			virtual void slowTick() noexcept override
			{
				static int rounds = 0;
				static int record = 0;
				if ( !alive )
				{
					if ( rounds != 0 )
						record = rounds;
					std::cout << "You Lost, but survived " << record << " Rounds!" << std::endl;
					rounds = 0;
					for ( unsigned int i = 0; i < enemys.size(); ++i )
					{
						delete enemys.at(i);
					}
					enemys.clear();
				}
				else
				{
					for ( unsigned int i = 0; i < rounds; ++i )
					{
						float rx = ( -150.0f + ( rand() % 301 ) ) / 10;
						float ry = ( -150.0f + ( rand() % 301 ) ) / 10;
						float rz = ( -150.0f + ( rand() % 301 ) ) / 10;
						if ( rx < 0 )
							rx -= 5;
						else
							rx += 5;
						if ( ry < 0 )
							ry -= 5;
						else
							ry += 5;
						if ( rz < 0 )
							rz -= 5;
						else
							rz += 5;
						int textureid = rand() % engine->getCurrentState()->getDefaultRenderer().cubeManager.getInstancedTextureCount();
						maths::Vec3f pos = m_position + maths::Vec3f { rx,ry,rz };
						logics::MovingBlock* inst = new logics::MovingBlock(textureid, maths::Vec3f(1, 1, 1), maths::Vec3f(0, 0, 0), pos, engine->getCurrentState(), &engine->getCurrentState()->getDefaultRenderer());
						enemys.push_back(inst);
					}
					rounds++;
				}
			}
			virtual void onCollision(MovingTickListener* otherMoving, int ownColliderNumber, int otherColliderNumber) noexcept override//dazu kommentieren wichtig: in der oncollision methode sollte man am besten nur das eigene objekt verändern und keine anderen objekte | man kann das eigene objekt auch löschen(dann sollte man aber auch das andere objekt verändern, da die on collision methode nicht mehr unbedingt für das andere objekt aufgerufen wird, wenn diese hier zuerst aufgerufen wird und das eigene objekt somit gelöscht ist)
																																	   //MAN DARF NICHT andere objekte löschen, da es leicht zu fehlern kommen kann
			{
				cube.setTexture(1, false);
				alive = false;
			}
			virtual void onCollision(StaticTickListener* otherStatic, int ownColliderNumber, int otherColliderNumber) noexcept override
			{
				maths::Vec3f dist = m_position - otherStatic->getPosition();
				dist.absSelf();
				dist -= m_size + otherStatic->getSize();
				if ( dist.x > dist.y&&dist.x > dist.z )
					m_velocity.x = 0;
				else if ( dist.y > dist.z )
					m_velocity.y = 0;
				else
					m_velocity.z = 0;
			}
		protected:
			void onMatrixChange() noexcept override
			{

			}
		};

		struct TransparentBlock : public RenderListener
		{
			graphics::NormalCube cube;
			TransparentBlock(const std::string& test, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				:GameObject(size, rotation, position, state), cube(test, this, renderer)
			{
				RenderListener::init();
			}
			TransparentBlock(int test, const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state, graphics::Renderer* renderer) noexcept
				: GameObject(size, rotation, position, state), cube(test, true, this, renderer)
			{
				RenderListener::init();
			}
			void renderAdd() noexcept override
			{
				cube.add();
			}
			void renderRemove() noexcept override
			{
				cube.remove();
			}
		protected:
			void onMatrixChange() noexcept override
			{

			}
		};

	}
}