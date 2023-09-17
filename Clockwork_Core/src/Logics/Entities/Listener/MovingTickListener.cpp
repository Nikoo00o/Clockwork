#include "MovingTickListener.h"
#include "src\Logics\ChunkSystem\Chunk.h"

namespace clockwork {
	namespace logics {

		MovingTickListener::MovingTickListener() noexcept
			: m_mass(0), m_hitbox(this)
		{
			m_chunk->addMovingTickListener(this);
		}

		MovingTickListener::~MovingTickListener() noexcept
		{
			m_chunk->removeMovingTickListener(this);
		}


	}
}