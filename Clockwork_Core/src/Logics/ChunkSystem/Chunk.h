#pragma once
#include "src\Maths\Vec3.h"
#include "src\Maths\MathFunctions.h"

#define CHUNK_BORDER 1

namespace clockwork {
	namespace graphics {
		class CubeBorder;
	}

	namespace logics {

		class State;
		class ChunkSystem;
		class RenderListener;
		class GameObject;
		class RenderListener;
		class MovingTickListener;
		class StaticTickListener;

		class Chunk
		{

		private:
			friend class ChunkSystem;

		private:
			maths::Vec3f m_min;
			maths::Vec3f m_max;
			maths::Vec3i m_id;//id is 0 to chunksize-1
			ChunkSystem* m_chunkSystem;

#if CHUNK_BORDER
			graphics::CubeBorder* m_border;
#endif

			std::vector<RenderListener*> m_renderList;//noch in konstruktor/movekonstruktor/copy/etc einbinden | ggf auch von gameobjects setchunk zum ändern machen und in destruktor von gameobject müssen sie sich auch löschen | die moving sachen können sich auch von chunk zu chunk bewegen(ggf testen ob x höher ist, dann id.x++ und auch so für andere, etc)
			std::vector<MovingTickListener*> m_movingTickList;
			std::vector<StaticTickListener*> m_staticTickList;

		public:
			Chunk() noexcept;
			~Chunk() noexcept;

		private:
			void init(const maths::Vec3f& min, const maths::Vec3f& max, int idX, int idY, int idZ, ChunkSystem* chunkSystem) noexcept;
			void collisionTest(const Chunk& otherChunk) const noexcept;

		public:
			void renderAdd() noexcept;
			void renderRemove() noexcept;
			void fastTick() noexcept;
			void slowTick() noexcept;
			void updateCollision() const noexcept;

			void addRenderListener(RenderListener* listener) noexcept;
			void removeRenderListener(RenderListener* listener) noexcept;
			void addMovingTickListener(MovingTickListener* listener) noexcept;
			void removeMovingTickListener(MovingTickListener* listener) noexcept;
			void addStaticTickListener(StaticTickListener* listener) noexcept;
			void removeStaticTickListener(StaticTickListener* listener) noexcept;

			/*passes a function to the chunk itself and the sorrounding chunks(3x3 cube) | you have to call this method with a functor struct layout like the following
			the positions can be negative below 0, or above the count and the method will cut it into the range
			struct SlowTickFunctor
			{
			void function(Chunk& chunk) noexcept
			{
			chunk.slowTick();
			}
			};
			passFunctionToArea<SlowTickFunctor>();
			*/
			template<typename functor>void passFunctionToArea() noexcept;
			//in relation zum currentchunk, ob der chunk hier in renderdistance liegt
			const bool inRenderDistance() const noexcept;
			const bool inTickDistance() const noexcept;
		public:
			friend bool operator==(const Chunk& c1, const Chunk& c2) noexcept;
			friend bool operator!=(const Chunk& c1, const Chunk& c2) noexcept;

		public:
			const maths::Vec3i getId() const noexcept{return m_id;}//braucht wahrscheinlich keine mutex, da es nur beim erstellen der chunks verändert wird und dann nicht mehr
			const ChunkSystem& getChunkSystem() const noexcept;
			ChunkSystem& getChunkSystem() noexcept;
		};

	}
}

#include "ChunkSystem.h"

namespace clockwork {
	namespace logics {

		template<typename functor>void Chunk::passFunctionToArea() noexcept
		{
			m_chunkSystem->passFunctionToChunks<functor>(m_id - 1, m_id + 1);
		}

	}
}