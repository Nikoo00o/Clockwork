#include "RenderListener.h"
#include "src\Logics\ChunkSystem\Chunk.h"

namespace clockwork {
	namespace logics {

		RenderListener::RenderListener() noexcept
		{
			m_chunk->addRenderListener(this);
		}

		RenderListener::~RenderListener() noexcept
		{
			m_chunk->removeRenderListener(this);
		}

		void RenderListener::init() noexcept
		{
			if ( m_chunk->inRenderDistance() )
				renderAdd();
		}

	}
}