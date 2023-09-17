#pragma once
#include "glad\glad.h"
#include "src\Utils\Helper.h"
#if CLOCKWORK_DEBUG
#include <vector>
#endif

namespace clockwork {
	namespace graphics {

		class VertexBuffer;

		/*has a vector/array of vertexbuffers and links the position of the vertexbuffer in the vector to the shader input location | the first vertexbuffer will have position 0 as shader input for the vertex shader
		also specifies how opengl will interpret the vertexbufferdata: the dimension of each vertex(vec2-vec4), the size of each vertex in bytes and the offset of the vertexbuffer in the vertexarray
		can save a float vec3/vec2 vertexbuffer for position, an unsigned char vec4 vertexbuffer for colour, etc
		its not a buffer like vertexbuffer/indexbuffer to store data
		should be created and bound first and then vertexbuffer/indexbuffer should be created, bound and connected to the vertexarray */
		class VertexArray
		{
		private:
			GLuint m_id;

		public:
#if CLOCKWORK_DEBUG
			static std::vector<VertexArray*> debug_vertexarrays;
			bool debug_bound;
#endif

		public:
			/*creates a vao and binds it, so another bind() call is unnecessary*/
			VertexArray() noexcept
			{
#if CLOCKWORK_DEBUG
				debug_vertexarrays.push_back(this);
#endif
				glGenVertexArrays(1, &m_id);
				bind();
			}

			/*deletes the vbos and the vertexarrayid itself in the opengl state machine*/
			~VertexArray() noexcept
			{
#if CLOCKWORK_DEBUG
				debug_bound = false;
				for ( std::vector<VertexArray*>::iterator it = debug_vertexarrays.begin(); it != debug_vertexarrays.end(); ++it )
				{
					if ( ( *it ) == this )
					{
						debug_vertexarrays.erase(it);
						break;
					}
				}
#endif
				glDeleteVertexArrays(1, &m_id);
			}

			VertexArray(const VertexArray&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			VertexArray(VertexArray&& other) noexcept
				: m_id(other.m_id)
			{
				other.m_id = 0;
#if CLOCKWORK_DEBUG
				debug_bound = other.debug_bound;
				other.debug_bound = false;
				debug_vertexarrays.push_back(this);
#endif
			}

			VertexArray& operator=(const VertexArray&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			VertexArray& operator=(VertexArray&& other) noexcept
			{
				m_id = other.m_id;
				other.m_id = 0;
#if CLOCKWORK_DEBUG
				debug_bound = other.debug_bound;
				other.debug_bound = false;
#endif
				return *this;
			}

		public:

			/*binds the vertexarray(only one vertexarray can be bound at the same time) and automaticly saves all vbos with data that the vertexarray is pointing to(methode connectToVao() from vbo) 
			also saves the last ibo bound while the vao was bound (but just one) | will allow drawing without binding the vbos and the ibo first by only binding the vao| vertexarray, vertexbuffer and indexbuffer are independant(can be bound at the same time)
			does not bind the vertexbuffers, or the indexbuffer! */
			void bind() noexcept
			{
#if CLOCKWORK_DEBUG
				for ( std::vector<VertexArray*>::iterator it = debug_vertexarrays.begin(); it != debug_vertexarrays.end(); ++it )
					( *it )->debug_bound = false;
				debug_bound = true;
#endif
				glBindVertexArray(m_id);
			}

			/*unbinds all vertexarrays and therfor all owned vertexbuffers/indexbuffers*/
			void unbind() noexcept
			{
#if CLOCKWORK_DEBUG
				for ( std::vector<VertexArray*>::iterator it = debug_vertexarrays.begin(); it != debug_vertexarrays.end(); ++it )
					( *it )->debug_bound = false;
#endif
				glBindVertexArray(0);
			}


		public:
			/*returns the unique opengl id of this buffer for opengls state machine*/
			const GLuint getId() const noexcept {return m_id;}


		};


	}
}
