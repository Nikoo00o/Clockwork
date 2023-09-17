#pragma once
#include "src\Maths\Vec3.h"
#include "src\Maths\MathFunctions.h"

namespace clockwork {
	namespace logics {

		class State;
		class Chunk;

		class ChunkSystem
		{

		public:
			friend class Chunk;
			struct RenderAddFunctor
			{
				void function(Chunk& chunk) noexcept;
			};
			struct RenderRemoveFunctor
			{
				void function(Chunk& chunk) noexcept;
			};
			struct FastTickFunctor
			{
				void function(Chunk& chunk) noexcept;
			};
			struct SlowTickFunctor
			{
				void function(Chunk& chunk) noexcept;
			};
			struct CollisionFunctor
			{
				void function(Chunk& chunk) noexcept;
			};
			
		private:
			maths::Vec3f m_min;
			maths::Vec3f m_max;
			maths::Vec3f m_chunkSize;
			maths::Vec3i m_count;//neue größe machen ist noch nicht vorgesehen
			maths::Vec3i m_renderDistance;///noch miteinbeziehen KONSTRUKTOR | getter/setter(mit debug test) | ist wichtig für renderadd/renderremove | wird für tick nicht benötigt, da dort die range mitgegeben werden kann
			maths::Vec3i m_tickDistance;///sollte nicht größer als count sein ggf in debug abfragen | braucht noch getter und setter, bei setter natürlich auch mutex setzten, da es in tick/render gebraucht wird
			Chunk*** m_chunks;
			Chunk* m_currentChunk;
			State* m_state;

		public:
			ChunkSystem(const maths::Vec3f& min, const maths::Vec3f& max, const maths::Vec3f& chunkSize, const maths::Vec3i& renderDistance, const maths::Vec3i& tickDistance, State* state) noexcept;
			~ChunkSystem() noexcept;

		public:
			const Chunk& getChunk(const maths::Vec3i& id) const noexcept;
			Chunk& getChunk(const maths::Vec3i& id) noexcept;
			const Chunk& getChunk(int idX, int idY, int idZ) const noexcept;
			Chunk& getChunk(int idX, int idY, int idZ) noexcept;
			const Chunk& getChunkAt(const maths::Vec3f& position) const noexcept;
			Chunk& getChunkAt(const maths::Vec3f& position) noexcept;

			const Chunk& getCurrentChunk() const noexcept;
			Chunk& getCurrentChunk() noexcept;
			const maths::Vec3i& getRenderDistance() const noexcept;
			const maths::Vec3i& getTickDistance() const noexcept;
			const unsigned int getBytes() const noexcept;
			const unsigned int getChunkCount() const noexcept;
			Chunk*** getChunkPointer() noexcept;//nicht wirklich threadsafe, nicht const | kann alles mit gemacht werden | wahrscheinlich nur in passFunction benutzen und dann in passFunction mutex für chunkSystem locken und in den einzelnen chunk.tick/render/etc methoden dann chunks locken
			const State& getState() const noexcept;
			State& getState() noexcept;


		public:
			void update() noexcept;
			void fastTick() noexcept;
			void slowTick() noexcept;
			void fastTickAll() noexcept;
			void slowTickAll() noexcept;
			//void onKeyPress() noexcept;///auch noch extra onmousepress und onmouseMove machen | auch on Chartyped
			
									   
			/*passes a function to chunks in the given range | you have to call this method with a functor struct layout like the following 
			the function is passed to the chunks between and at the 2 positions | the positions can be negative below 0, or above the count and the method will cut it into the range
			struct SlowTickFunctor
			{
				void function(Chunk& chunk) noexcept
				{
					chunk.slowTick();
				}
			};
			passFunction<SlowTickFunctor>(m_currentChunk->getId()-m_tickDistance, m_currentChunk->getId()+m_tickDistance);
			*/
			template<typename functor>void passFunctionToChunks(const maths::Vec3<int>& pos1, const maths::Vec3<int>& pos2) noexcept;
			//fast genau gleich kommentieren
			template<typename functor>void passFunctionToAll() noexcept;
		};

	}
}

#include "Chunk.h"

namespace clockwork {
	namespace logics {

		template<typename functor>void ChunkSystem::passFunctionToChunks(const maths::Vec3<int>& pos1, const maths::Vec3<int>& pos2) noexcept
		{
			functor funct {};
#if CLOCKWORK_DEBUG
			if ( pos1.x < 0 || pos1.y < 0 || pos1.z < 0 )
				std::cout << "Error ChunkSystem::passFunctionToChunks(): pos1 is below 0" << std::endl;
			if ( pos2.x >= m_count.x || pos2.y >= m_count.y || pos2.z >= m_count.z )
				std::cout << "Error ChunkSystem::passFunctionToChunks(): pos2 is above, or equal to count of the chunksystem" << std::endl;
#endif

			for ( int x = pos1.x; x <= pos2.x; ++x )
			{
				for ( int y = pos1.y; y <= pos2.y; ++y )
				{
					for ( int z = pos1.z; z <= pos2.z; ++z )
					{
						funct.function(m_chunks[x][y][z]);
					}
				}
			}
		}

		template<typename functor>void ChunkSystem::passFunctionToAll() noexcept
		{
			functor funct {};
			for ( int x = 0; x < m_count.x; ++x )
			{
				for ( int y = 0; y < m_count.x; ++y )
				{
					for ( int z = 0; z < m_count.x; ++z )
					{
						funct.function(m_chunks[x][y][z]);
					}
				}
			}
		}

	}
}