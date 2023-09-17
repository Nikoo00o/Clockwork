#include "StaticTickListener.h"
#include "src\Logics\ChunkSystem\Chunk.h"

namespace clockwork {
	namespace logics {

		StaticTickListener::StaticTickListener() noexcept
			: m_mass(0), m_hitbox(this)
		{
			m_chunk->addStaticTickListener(this);
		}

		StaticTickListener::~StaticTickListener() noexcept
		{
			m_chunk->removeStaticTickListener(this);
		}


	}
}