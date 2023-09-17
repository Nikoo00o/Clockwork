#pragma once
#include "glad\glad.h"
#include "src\Utils\Helper.h"

namespace clockwork {
	namespace graphics {

		class FrameBuffer
		{

		private:
			GLuint m_id;
			GLenum m_buffer;
			unsigned int m_size;

		public:

			/*das gleiche wie bei anderen buffern kommentieren | buffer ist bufferart kann GL_READ_FRAMEBUFFER, oder GL_DRAW_FRAMEBUFFER sein, oder GL_FRAMEBUFFER für beide
			die beiden sind seperat für bind calls(können also gleichzeitig bound sein) 
			buffer ist nicht bound nach konstruktor */
			explicit FrameBuffer(GLenum buffer = GL_FRAMEBUFFER) noexcept
				: m_size(0), m_buffer(buffer)
			{
				glGenFramebuffers(1, &m_id);
			}

			//auch noch move/copy konstruktoren machen
			~FrameBuffer() noexcept
			{
				glDeleteFramebuffers(1, &m_id);
			}

			void bind() noexcept
			{
				glBindFramebuffer(m_buffer, m_id);
			}

			void unbind() noexcept
			{
				glBindFramebuffer(m_buffer, 0);
			}

			const GLenum getBufferType() const noexcept
			{
				return m_buffer;
			}

			const GLuint getId() const noexcept
			{
				return m_id;
			}



		};

	}
}