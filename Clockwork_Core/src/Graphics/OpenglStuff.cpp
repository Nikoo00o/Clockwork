#include "OpenglStuff.h"
#include "Buffers\VertexBuffer.h"
#include "Buffers\CopyBuffer.h"
#include "Buffers\InternalCopyBuffer.h"
#include "src\Graphics\Textures\TextureArray2D.h"

namespace clockwork {
	namespace graphics {

		void initBuffers(unsigned int size) noexcept
		{
			VertexBuffer::copyBuffer = new InternalCopyBuffer(nullptr, size, GL_STREAM_DRAW);
			CopyBuffer::copyBuffer = new InternalCopyBuffer(nullptr, size, GL_STREAM_DRAW);
			InternalCopyBuffer::copyBuffer = new CopyBuffer(nullptr, size, GL_STREAM_DRAW);
		}

		void openglParams(int cullFace, int windingOrder, int depthCompare, int blendSourceFactor, int blendDestinationFactor, int blendFunc) noexcept
		{
			glEnable(GL_CULL_FACE);
			glCullFace(cullFace);
			glFrontFace(windingOrder);

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(depthCompare);

			glEnable(GL_BLEND);
			glBlendEquation(blendFunc);
			glBlendFunc(blendSourceFactor, blendDestinationFactor);
		}

		void initTextures()
		{
			TextureArray2D::m_readBuffer = new FrameBuffer(GL_READ_FRAMEBUFFER);
			TextureArray2D::m_drawBuffer = new FrameBuffer(GL_DRAW_FRAMEBUFFER);
		}

	}
}