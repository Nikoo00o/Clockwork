#include "src\Logics\Camera\Camera.h"
#include "src\Logics\States\State.h"
#include "ChunkSystem.h"


namespace clockwork {
	namespace logics {



		ChunkSystem::ChunkSystem(const maths::Vec3f& min, const maths::Vec3f& max, const maths::Vec3f& chunkSize, const maths::Vec3i& renderDistance, const maths::Vec3i& tickDistance, State* state) noexcept
			: m_min(min), m_max(max), m_chunkSize(chunkSize), m_state(state), m_renderDistance(renderDistance), m_tickDistance(tickDistance)
		{
			maths::Vec3<float> count = ( max - min ) / chunkSize;
			m_count.x = maths::ceil(count.x);
			m_count.y = maths::ceil(count.y);
			m_count.z = maths::ceil(count.z);

			m_chunks = new Chunk**[m_count.x];
			for ( int x = 0; x < m_count.x; ++x )
			{
				m_chunks[x] = new Chunk*[m_count.y];
				for ( int y = 0; y < m_count.x; ++y )
				{
					m_chunks[x][y] = new Chunk[m_count.z];
					for ( int z = 0; z < m_count.x; ++z )
					{
						maths::Vec3<float> tempMin
						{ min.x + x * chunkSize.x,
							min.y + y * chunkSize.y,
							min.z + z * chunkSize.z };
						maths::Vec3<float> tempMax
						{ maths::min(tempMin.x + chunkSize.x, max.x),
							maths::min(tempMin.y + chunkSize.y, max.y),
							maths::min(tempMin.z + chunkSize.z, max.z) };
						m_chunks[x][y][z].init(tempMin, tempMax, x, y, z, this);
					}
				}
			}

#if CLOCKWORK_DEBUG 
			if ( m_renderDistance >= m_count )
				std::cout << "Error ChunkSystem::ChunkSystem(): RenderDistance too big" << std::endl;
			if ( m_tickDistance >= m_count )
				std::cout << "Error ChunkSystem::ChunkSystem(): TickDistance too big" << std::endl;
#endif
			m_currentChunk = &getChunkAt(m_state->getCurrentCamera().getPosition());
			passFunctionToChunks<RenderAddFunctor>(m_currentChunk->getId() - m_renderDistance, m_currentChunk->getId() + m_renderDistance);
		}

		ChunkSystem::~ChunkSystem() noexcept
		{
			for ( int x = 0; x < m_count.x; ++x )
			{
				for ( int y = 0; y < m_count.x; ++y )
				{
					delete[] m_chunks[x][y];
				}
				delete m_chunks[x];
			}
			delete[] m_chunks;
		}

		const Chunk& ChunkSystem::getChunk(const maths::Vec3i& id) const noexcept
		{
			return m_chunks[id.x][id.y][id.z];
		}
		Chunk& ChunkSystem::getChunk(const maths::Vec3i& id) noexcept
		{
			return m_chunks[id.x][id.y][id.z];
		}
		const Chunk& ChunkSystem::getChunk(int idX, int idY, int idZ) const noexcept
		{
			return m_chunks[idX][idY][idZ];
		}
		Chunk& ChunkSystem::getChunk(int idX, int idY, int idZ) noexcept
		{
			return m_chunks[idX][idY][idZ];
		}
		const Chunk& ChunkSystem::getChunkAt(const maths::Vec3f& position) const noexcept
		{
			return m_chunks[static_cast<int>( maths::floor(( position.x - m_min.x ) / m_chunkSize.x) )][static_cast<int>( maths::floor(( position.y - m_min.y ) / m_chunkSize.y) )][static_cast<int>( maths::floor(( position.z - m_min.z ) / m_chunkSize.z) )];
		}
		Chunk& ChunkSystem::getChunkAt(const maths::Vec3f& position) noexcept
		{
			return m_chunks[static_cast<int>( maths::floor(( position.x - m_min.x ) / m_chunkSize.x) )][static_cast<int>( maths::floor(( position.y - m_min.y ) / m_chunkSize.y) )][static_cast<int>( maths::floor(( position.z - m_min.z ) / m_chunkSize.z) )];
		}

		const Chunk& ChunkSystem::getCurrentChunk() const noexcept
		{
			return *m_currentChunk;
		}

		Chunk& ChunkSystem::getCurrentChunk() noexcept
		{
			return *m_currentChunk;
		}

		const maths::Vec3i& ChunkSystem::getRenderDistance() const noexcept
		{
			return m_renderDistance;
		}
		const maths::Vec3i& ChunkSystem::getTickDistance() const noexcept
		{
			return m_tickDistance;
		}

		const unsigned int ChunkSystem::getBytes() const noexcept
		{
			return m_count.x*m_count.y*m_count.z * sizeof(Chunk);
		}
		const unsigned int ChunkSystem::getChunkCount() const noexcept
		{
			return m_count.x*m_count.y*m_count.z;
		}
		Chunk*** ChunkSystem::getChunkPointer() noexcept
		{
			return m_chunks;
		}
		const State& ChunkSystem::getState() const noexcept
		{
			return *m_state;
		}
		State& ChunkSystem::getState() noexcept
		{
			return *m_state;
		}

		void  ChunkSystem::update() noexcept
		{
			if ( *m_currentChunk != getChunkAt(m_state->getCurrentCamera().getPosition()) )
			{
				Chunk& newChunk = getChunkAt(m_state->getCurrentCamera().getPosition());
				const maths::Vec3i& oldId = m_currentChunk->getId();
				const maths::Vec3i& newId = getChunkAt(m_state->getCurrentCamera().getPosition()).getId();

				maths::Vec3i diffrence = newChunk.getId() - m_currentChunk->getId();
				maths::Vec3i defaultRemoveLeft(oldId.x - m_renderDistance.x, oldId.y - m_renderDistance.y, oldId.z - m_renderDistance.z);///sollte eigentlich funktionieren, nur gucken, ob das erhöhen/verringern von defaultRemoveLeft/Right auch richtig ist und funktioniert, wenn eine richtung der bewegung positiv ist und eine andere negativ(1,-2,3)
				maths::Vec3i defaultRemoveRight(oldId.x + m_renderDistance.x, oldId.y + m_renderDistance.y, oldId.z + m_renderDistance.z);
				maths::Vec3i defaultAddLeft(newId.x - m_renderDistance.x, newId.y - m_renderDistance.y, newId.z - m_renderDistance.z);///keine ahnung, ob es funktioniert
				maths::Vec3i defaultAddRight(newId.x + m_renderDistance.x, newId.y + m_renderDistance.y, newId.z + m_renderDistance.z);

#if CLOCKWORK_DEBUG
				std::cout << std::endl << "Diffrence: " << diffrence << " Old Chunk: " << oldId << " New Chunk: " << newId << std::endl;
#endif

				if ( diffrence.x > 0 )//right side of chunk cube added and left side of chunk cube removed
				{
					maths::Vec3i xRemoveRight(maths::min(newId.x - m_renderDistance.x - 1, oldId.x + m_renderDistance.x), defaultRemoveRight.y, defaultRemoveRight.z);//left=inner/closer to oldchunk | right=outer/closer to newchunk
#if CLOCKWORK_DEBUG
					std::cout << "X-Axis: " << defaultRemoveLeft << " to " << xRemoveRight << " is removed" << std::endl;
#endif
					passFunctionToChunks<RenderRemoveFunctor>(defaultRemoveLeft, xRemoveRight);
					++defaultRemoveLeft.x;//preperation for y and z

					maths::Vec3i xAddLeft(maths::max(oldId.x + m_renderDistance.x + 1, newId.x - m_renderDistance.x), defaultAddLeft.y, defaultAddLeft.z);//left=inner/closer to oldchunk | right=outer/closer to newchunk
#if CLOCKWORK_DEBUG
					std::cout << "X-Axis: " << xAddLeft << " to " << defaultAddRight << " is added" << std::endl;
#endif
					passFunctionToChunks<RenderAddFunctor>(xAddLeft, defaultAddRight);
					--defaultAddRight.x;//preperation for y and z
				}
				else if ( diffrence.x < 0 )//left side of chunk cube added and right side of chunk cube removed | reverse order, because its moving towards negative x
				{
					maths::Vec3i xRemoveLeft(maths::max(newId.x + m_renderDistance.x + 1, oldId.x - m_renderDistance.x), defaultRemoveLeft.y, defaultRemoveLeft.z);//right=inner/closer to oldchunk | left=outer/closer to newchunk
#if CLOCKWORK_DEBUG
					std::cout << "X-Axis: " << xRemoveLeft << " to " << defaultRemoveRight << " is removed" << std::endl;
#endif
					passFunctionToChunks<RenderRemoveFunctor>(xRemoveLeft, defaultRemoveRight);
					--defaultRemoveRight.x;//preperation for y and z

					maths::Vec3i xAddRight(maths::min(oldId.x - m_renderDistance.x - 1, newId.x + m_renderDistance.x), defaultAddRight.y, defaultAddRight.z);//left=inner/closer to oldchunk | right=outer/closer to newchunk
#if CLOCKWORK_DEBUG
					std::cout << "X-Axis: " << defaultAddLeft << " to " << xAddRight << " is added" << std::endl;
#endif
					passFunctionToChunks<RenderAddFunctor>(defaultAddLeft, xAddRight);
					++defaultAddLeft.x;//preperation for y and z
				}

				if ( diffrence.y > 0 )//right side of chunk cube added and left side of chunk cube removed
				{
					maths::Vec3i yRemoveRight(defaultRemoveRight.x, maths::min(newId.y - m_renderDistance.y - 1, oldId.y + m_renderDistance.y), defaultRemoveRight.z);//left=inner/closer to oldchunk | right=outer/closer to newchunk
#if CLOCKWORK_DEBUG
					std::cout << "Y-Axis: " << defaultRemoveLeft << " to " << yRemoveRight << " is removed" << std::endl;
#endif
					passFunctionToChunks<RenderRemoveFunctor>(defaultRemoveLeft, yRemoveRight);
					++defaultRemoveLeft.y;//preperation for z

					maths::Vec3i yAddLeft(defaultAddLeft.x, maths::max(oldId.y + m_renderDistance.y + 1, newId.y - m_renderDistance.y), defaultAddLeft.z);//left=inner/closer to oldchunk | right=outer/closer to newchunk
#if CLOCKWORK_DEBUG
					std::cout << "Y-Axis: " << yAddLeft << " to " << defaultAddRight << " is added" << std::endl;
#endif
					passFunctionToChunks<RenderAddFunctor>(yAddLeft, defaultAddRight);
					--defaultAddRight.y;//preperation for y and z
				}
				else if ( diffrence.y < 0 )//left side of chunk cube added and right side of chunk cube removed | reverse order, because its moving towards negative y
				{
					maths::Vec3i yRemoveLeft(defaultRemoveLeft.x, maths::max(newId.y + m_renderDistance.y + 1, oldId.y - m_renderDistance.y), defaultRemoveLeft.z);//right=inner/closer to oldchunk | left=outer/closer to newchunk
#if CLOCKWORK_DEBUG
					std::cout << "Y-Axis: " << yRemoveLeft << " to " << defaultRemoveRight << " is removed" << std::endl;
#endif
					passFunctionToChunks<RenderRemoveFunctor>(yRemoveLeft, defaultRemoveRight);
					--defaultRemoveRight.y;//preperation for z

					maths::Vec3i yAddRight(defaultAddRight.x, maths::min(oldId.y - m_renderDistance.y - 1, newId.y + m_renderDistance.y), defaultAddRight.z);//left=inner/closer to oldchunk | right=outer/closer to newchunk
#if CLOCKWORK_DEBUG
					std::cout << "Y-Axis: " << defaultAddLeft << " to " << yAddRight << " is added" << std::endl;
#endif
					passFunctionToChunks<RenderAddFunctor>(defaultAddLeft, yAddRight);
					++defaultAddLeft.y;//preperation for y and z
				}

				if ( diffrence.z > 0 )//right side of chunk cube added and left side of chunk cube removed
				{
					maths::Vec3i zRemoveRight(defaultRemoveRight.x, defaultRemoveRight.y, maths::min(newId.z - m_renderDistance.z - 1, oldId.z + m_renderDistance.z));//left=inner/closer to oldchunk | right=outer/closer to newchunk
#if CLOCKWORK_DEBUG
					std::cout << "Z-Axis: " << defaultRemoveLeft << " to " << zRemoveRight << " is removed" << std::endl;
#endif
					passFunctionToChunks<RenderRemoveFunctor>(defaultRemoveLeft, zRemoveRight);

					maths::Vec3i zAddLeft(defaultAddLeft.x, defaultAddLeft.y, maths::max(oldId.z + m_renderDistance.z + 1, newId.z - m_renderDistance.z));//left=inner/closer to oldchunk | right=outer/closer to newchunk
#if CLOCKWORK_DEBUG
					std::cout << "Z-Axis: " << zAddLeft << " to " << defaultAddRight << " is added" << std::endl;
#endif
					passFunctionToChunks<RenderAddFunctor>(zAddLeft, defaultAddRight);
				}
				else if ( diffrence.z < 0 )//left side of chunk cube added and right side of chunk cube removed | reverse order, because its moving towards negative z
				{
					maths::Vec3i zRemoveLeft(defaultRemoveLeft.x, defaultRemoveLeft.y, maths::max(newId.z + m_renderDistance.z + 1, oldId.z - m_renderDistance.z));//right=inner/closer to oldchunk | left=outer/closer to newchunk
#if CLOCKWORK_DEBUG
					std::cout << "Z-Axis: " << zRemoveLeft << " to " << defaultRemoveRight << " is removed" << std::endl;
#endif
					passFunctionToChunks<RenderRemoveFunctor>(zRemoveLeft, defaultRemoveRight);

					maths::Vec3i zAddRight(defaultAddRight.x, defaultAddRight.y, maths::min(oldId.z - m_renderDistance.z - 1, newId.z + m_renderDistance.z));//left=inner/closer to oldchunk | right=outer/closer to newchunk
#if CLOCKWORK_DEBUG
					std::cout << "Z-Axis: " << defaultAddLeft << " to " << zAddRight << " is added" << std::endl << std::endl;
#endif
					passFunctionToChunks<RenderAddFunctor>(defaultAddLeft, zAddRight);
				}



				//hier renderadd/renderremove mit currentchunklist vergleichen, etc ... | am besten gucken wie id ist was schon in renderrange liegt und was dann nicht mehr, etc | WICHTIG auch bei setrenderdistance, etc verändern 

				//beim erstellen müssen die einzelnen renderlistener objekte sich aber auch schon renderAdd von sich aufrufen, wenn der chunk, dem sie hinzugefügt werden in renderrange vom currentchunk ist(ggf methode in chunk machen inRenderRange() ) | das darf aber nicht im konstruktor von renderlistener geschehen, da renderadd wahrscheinlich virtuelle methode ist und der subklassenanteil noch nicht erstellt ist 
				//ggf aus subklassenkonstruktor von dem erbenden gameobject check methode, oder so der superklasse aufrufen(ist dann protected methode) | renderadd und renderremove werden ja dann virtuell überschrieben und werden von den modellen add und remove aufrufen(immer) | bei den modell methoden add/remove wird intern dann noch getestet, ob sie schon added/removed wurden und dann wird dies nicht ausgeführt
				//visible bool, etc von gameobject muss dann in renderadd/renderremove von gameobject geregelt werden, wo es an die modelle weitergeleitet wird 
				//gameobject hat dann wahrscheinlich auch nur noch einen chunk pointer auf aktuellen chunk und eine move funktion zu neuem chunk(von allen pointer listen render/tick/etc entfernen und beim neuen adden(ggf renderadd/renderremove aufrufen, wenn in rendersichtweite)
				//alwaysactive chunk nicht vergessen | dafür ggf noch bool in konstruktor von gameobject mitgeben, ob alwaysactive, oder nicht und dementsprechend wird es hinzugefügt | alwaysactivechunk kann auch von einer anderen klasse sein mit nur den listen ohne position, id, etc
				//von normalem chunk zu alwaysactive chunk und andersherum moven wird schwer

				m_currentChunk = &newChunk;
			}
		}


		void ChunkSystem::fastTick() noexcept
		{
			passFunctionToChunks<CollisionFunctor>(m_currentChunk->getId() - m_tickDistance, m_currentChunk->getId() + m_tickDistance);
			passFunctionToChunks<FastTickFunctor>(m_currentChunk->getId() - m_tickDistance, m_currentChunk->getId() + m_tickDistance);
		}

		void ChunkSystem::slowTick() noexcept
		{
			passFunctionToChunks<SlowTickFunctor>(m_currentChunk->getId() - m_tickDistance, m_currentChunk->getId() + m_tickDistance);
		}

		void ChunkSystem::fastTickAll() noexcept
		{
			for ( int x = 0; x < m_count.x; ++x )
			{
				for ( int y = 0; y < m_count.x; ++y )
				{
					for ( int z = 0; z < m_count.x; ++z )
					{
						m_chunks[x][y][z].fastTick();
					}
				}
			}
		}

		void ChunkSystem::slowTickAll() noexcept
		{
			for ( int x = 0; x < m_count.x; ++x )
			{
				for ( int y = 0; y < m_count.x; ++y )
				{
					for ( int z = 0; z < m_count.x; ++z )
					{
						m_chunks[x][y][z].slowTick();
					}
				}
			}
		}

		void ChunkSystem::RenderAddFunctor::function(Chunk& chunk) noexcept
		{
			chunk.renderAdd();
		}

		void ChunkSystem::RenderRemoveFunctor::function(Chunk& chunk) noexcept
		{
			chunk.renderRemove();
		}
		
		void ChunkSystem::FastTickFunctor::function(Chunk& chunk) noexcept
		{
			chunk.fastTick();
		}

		void ChunkSystem::SlowTickFunctor::function(Chunk& chunk) noexcept
		{
			chunk.slowTick();
		}

		void ChunkSystem::CollisionFunctor::function(Chunk& chunk) noexcept
		{
			chunk.updateCollision();
		}

	}
}