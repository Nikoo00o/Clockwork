#include "TextureArray2D.h"

namespace clockwork {
	namespace graphics {

		FrameBuffer* TextureArray2D::m_readBuffer { nullptr };
		FrameBuffer* TextureArray2D::m_drawBuffer { nullptr };

	}
}