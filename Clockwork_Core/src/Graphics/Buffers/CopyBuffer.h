#pragma once
#include "glad\glad.h"
#include "src\Utils\Helper.h"
#if CLOCKWORK_DEBUG
#include <vector>
#endif

namespace clockwork {
	namespace graphics {

		class VertexBuffer;
		class InternalCopyBuffer;

		/*stores some data in the buffer which will mainly be used as a temp copy of some relevant data to improve performance, or copy data between buffers
		you can and should use this kind of buffer
		its a GL_COPY_READ_BUFFER
		has an internalcopybuffer as its internal buffer to swap data*/
		class CopyBuffer
		{

		private:
			GLuint m_id;
			GLuint m_size;
			GLenum m_bufferMode;

		private:
			static InternalCopyBuffer* copyBuffer;

		public:
			/*the buffertype of the buffer | here GL_COPY_READ_BUFFER*/
			static const GLint bufferType = GL_COPY_READ_BUFFER;

		public:
#if CLOCKWORK_DEBUG
			static std::vector<CopyBuffer*> debug_buffers;
			mutable bool debug_bound;
#endif

		public:
			/*creates a copybuffer with the given data, fills the buffer with the data and binds it, so another bind() call is unnecessary | its kinda the same as a vertexbuffer just with another buffertype as storage modifier
			@param[data] pointer to the userdata which is copied into the buffer(can be nullptr for an empty buffer with reserved capacity of size) | should be called with an array of data
			@param[size] the size of the data(array) in bytes | count of elements times sizeof(type) | its the capacity of the vertexbuffer, so it can be larger than the actual size of the data of the pointer to reserve some bytes
			@param[bufferMode] the kind of the buffer data / how its stored and how it will be changed
			GL_STATIC_DRAW 0x88E4 the data will most likely not change at all or very rarely
			GL_DYNAMIC_DRAW 0x88E8 the data is likely to change a lot
			GL_STREAM_DRAW 0x88E0 the data will change every time it is drawn

			you can either create create a copybuffer with a pointer to some data with the size of the data or an empty vertexbuffer with data pointer as nullptr and a predefined size for future data */
			CopyBuffer(const void* data, GLuint size, GLenum bufferMode = GL_STATIC_DRAW) noexcept
				: m_size(size), m_bufferMode(bufferMode)
			{
				glGenBuffers(1, &m_id);
				glBindBuffer(bufferType, m_id);
				glBufferData(bufferType, size, data, bufferMode);
#if CLOCKWORK_DEBUG
				for ( std::vector<CopyBuffer*>::iterator it = debug_buffers.begin(); it != debug_buffers.end(); ++it )
					( *it )->debug_bound = false;
				debug_bound = true;
				debug_buffers.push_back(this);
#endif
			}

			/*creates an empty copybuffer with an uninitialized opengl buffer | does not bind it*/
			CopyBuffer() noexcept
				:m_id(0), m_size(0), m_bufferMode(0)
			{
#if CLOCKWORK_DEBUG
				debug_bound = false;
				debug_buffers.push_back(this);
#endif
			}

			/*deletes the copybufferid in the opengl state machine*/
			~CopyBuffer() noexcept
			{
				glDeleteBuffers(1, &m_id);
#if CLOCKWORK_DEBUG
				debug_bound = false;
				for ( std::vector<CopyBuffer*>::iterator it = debug_buffers.begin(); it != debug_buffers.end(); ++it )
				{
					if ( ( *it ) == this )
					{
						debug_buffers.erase(it);
						break;
					}
				}
#endif
			}

			CopyBuffer(const CopyBuffer&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			CopyBuffer(CopyBuffer&& other) noexcept
				: m_id(other.m_id), m_size(other.m_size), m_bufferMode(other.m_bufferMode)
			{
				other.m_id = 0;
				other.m_size = 0;
				other.m_bufferMode = 0;
#if CLOCKWORK_DEBUG
				debug_bound = other.debug_bound;
				other.debug_bound = false;
				debug_buffers.push_back(this);
#endif
			}

			CopyBuffer& operator=(const CopyBuffer&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			CopyBuffer& operator=(CopyBuffer&& other) noexcept
			{
				m_id = other.m_id;
				m_size = other.m_size;
				m_bufferMode = other.m_bufferMode;
				other.m_id = 0;
				other.m_size = 0;
				other.m_bufferMode = 0;
#if CLOCKWORK_DEBUG
				debug_bound = other.debug_bound;
				other.debug_bound = false;
#endif
				return *this;
			}

		public:
			/*copies new data into the buffer with a given offset and with a specified size and replaces the old data at that area | the buffermode and the size stays the same
			the buffer has to be bound first
			@param[data] pointer to the userdata which is copied into the buffer | should be called with an array of data
			@param[size] the size of the data(array) in bytes | count of elements times sizeof(type) | the size and the offset together should not be larger than the size/capacity of the buffer
			@param[offset] the position in the buffer where to start | the default is 0 for the beginning of the buffer to set the size equal to the size of the buffer and replace all of the data of the buffer with new data
			the offset is also how many bytes from the start are not copied, so it specifies where the data replacement will begin measured in bytes*/
			void setData(const void* data, unsigned int size, unsigned int offset = 0) noexcept;

			/*changes the size of the buffer, but the buffer will keep the same data with a new size and the same buffermode
			the buffer has to be bound first
			the static internalcopybuffer of this class will have the same data and size as this buffer and will also be bound after this method
			@param[size] the size of the data(array) in bytes | count of elements times sizeof(type) | its the new capacity of the buffer that will be reserved*/
			void setSize(GLuint size) noexcept;

			/*changes the size of the buffer, but the buffer will not keep the data(so the old data will be deleted) | the buffer will be empty with the new size and the same buffermode
			the buffer has to be bound first
			@param[size] the size of the data(array) in bytes | count of elements times sizeof(type) | its the new capacity of the buffer that will be reserved*/
			void reset(GLuint size) noexcept;

			/*copies the size and the data of the other buffer to this buffer | the buffermode will stay the same
			the static internalcopybuffer of this class will have the same data and size as this buffer
			no buffer has to be bound first | this buffer and the static internalcopybuffer of this class will be bound after the method, the other buffer will be unchanged/unbound
			not that fast as the other copy methods and a little bit unefficient, because both buffers are of the same type*/
			CopyBuffer& copy(const CopyBuffer& other) noexcept;

			/*copies the the size and the data of the other buffer to this buffer | the buffermode will stay the same
			both buffer have to be bound first and both buffers will stay bound after the method*/
			CopyBuffer& copy(const VertexBuffer& other) noexcept;

			/*copies the the size and the data of the other buffer to this buffer | the buffermode will stay the same
			both buffer have to be bound first and both buffers will stay bound after the method*/
			CopyBuffer& copy(const InternalCopyBuffer& other) noexcept;

			/*binds this opengl copy read buffer to the opengl state machine, so opengl can work with it(by using buffercalls on gl_copy_read_buffers)
			only one buffer of the same type(here copybuffer/gl_copy_read_buffers) can be bound at a time, but buffers of other types can be bound at the same time | vertexarray, vertexbuffer, indexbuffer and copybuffer are independant(can be bound at the same time)*/
			void bind() const noexcept
			{
#if CLOCKWORK_DEBUG
				for ( std::vector<CopyBuffer*>::iterator it = debug_buffers.begin(); it != debug_buffers.end(); ++it )
					( *it )->debug_bound = false;
				debug_bound = true;
#endif
				glBindBuffer(bufferType, m_id);
			}

			/*unbinds all copybuffers/gl_copy_read_buffers*/
			void unbind() const noexcept
			{
#if CLOCKWORK_DEBUG
				for ( std::vector<CopyBuffer*>::iterator it = debug_buffers.begin(); it != debug_buffers.end(); ++it )
					( *it )->debug_bound = false;
#endif
				glBindBuffer(bufferType, 0);
			}

			/*must be called from the render thread with an active opengl context( Window::init() has to be called first and then atleast one window object has to be created before calling this method)
			has to be called before using any buffer and it will initialize the internal copy buffers | will be called from the engine constructor
			@param[size] the reserved size in bytes for the private copy buffers of the buffer classes*/
			friend void initBuffers(unsigned int size) noexcept;

		public:
			/*returns the unique opengl id of this buffer for opengls state machine*/
			const GLuint getId() const noexcept{return m_id;}

			/*returns the capacity of the copybuffer in bytes*/
			const GLuint getSize() const noexcept{return m_size;}


		};


	}
}
