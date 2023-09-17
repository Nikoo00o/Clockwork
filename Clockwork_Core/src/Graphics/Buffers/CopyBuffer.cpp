#include "CopyBuffer.h"
#include "VertexBuffer.h"
#include "InternalCopyBuffer.h"

namespace clockwork {
	namespace graphics {

		InternalCopyBuffer* CopyBuffer::copyBuffer { nullptr };
#if CLOCKWORK_DEBUG
		std::vector<CopyBuffer*> CopyBuffer::debug_buffers;
#endif

		void CopyBuffer::setData(const void* data, unsigned int size, unsigned int offset /*= 0*/) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error CopyBuffer::setData(): CopyBuffer was not bound" << std::endl;
#endif
			glBufferSubData(bufferType, offset, size, data);
		}

		void CopyBuffer::setSize(GLuint size) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error CopyBuffer::setSize(): CopyBuffer was not bound" << std::endl;
#endif
			copyBuffer->bind();
			if ( size > copyBuffer->getSize() )
				copyBuffer->reset(size);
			copyBuffer->copy(*this);
			this->copy(*copyBuffer);
		}

		void CopyBuffer::reset(GLuint size) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error CopyBuffer::reset(): CopyBuffer was not bound" << std::endl;
#endif
			glBufferData(bufferType, size, nullptr, m_bufferMode);
			m_size = size;
		}

		CopyBuffer& CopyBuffer::copy(const CopyBuffer& other) noexcept
		{
			copyBuffer->bind();
			if ( other.m_size > copyBuffer->getSize() )
				copyBuffer->reset(other.m_size);
			other.bind();
			copyBuffer->copy(other);
			this->bind();
			if ( other.m_size > m_size )
				this->reset(other.m_size);
			this->copy(*copyBuffer);
			return *this;
		}

		CopyBuffer& CopyBuffer::copy(const VertexBuffer& other) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error CopyBuffer::copy(): CopyBuffer was not bound" << std::endl;
			if ( !other.debug_bound )
				std::cout << "Error CopyBuffer::copy(): VertexBuffer was not bound" << std::endl;
#endif
			if ( other.getSize() > m_size )
				reset(other.getSize());
			glCopyBufferSubData(other.bufferType, bufferType, 0, 0, other.getSize());
			return *this;
		}

		CopyBuffer& CopyBuffer::copy(const InternalCopyBuffer& other) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( !debug_bound )
				std::cout << "Error CopyBuffer::copy(): CopyBuffer was not bound" << std::endl;
			if ( !other.debug_bound )
				std::cout << "Error CopyBuffer::copy(): InternalCopyBuffer was not bound" << std::endl;
#endif
			if ( other.getSize() > m_size )
				reset(other.getSize());
			glCopyBufferSubData(other.bufferType, bufferType, 0, 0, other.getSize());
			return *this;
		}

	}
}