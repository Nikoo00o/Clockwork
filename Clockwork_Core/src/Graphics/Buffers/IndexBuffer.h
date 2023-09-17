#pragma once
#include "glad\glad.h"
#include "src\Graphics\OpenglStuff.h"
#include "src\Utils\Helper.h"
#if CLOCKWORK_DEBUG
#include <vector>
#endif

namespace clockwork {
	namespace graphics {

		class VertexArray;

		/*specifies the order of drawing the triangles between the vertices of the vertexbuffer
		so for example first draw a triangle between the 0. 3. and 2. vertex of the vertexbuffer of positions saved in the vertexarray in attribute 0
		useful so there are no duplicated vertices in the vertexbuffer if they are used more than one time to draw to connected triangles
		its a buffer with indices, where each index is a integer number for the vertex(position in the vertexbuffer) to be drawn | the indices are drawn in order from first to last
		its a gl_element_array_buffer*/
		template<typename type>
		class IndexBuffer
		{

		private:
			GLuint m_id;
			GLuint m_count;

		public:
			/*the buffertype of the buffer | here GL_ELEMENT_ARRAY_BUFFER */
			static const GLint bufferType = GL_ELEMENT_ARRAY_BUFFER;

		public:

		public:
			/*creates a indexbuffer and binds it, so another bind() call is unnecessary
			@param[data] pointer to the userdata which is copied into the buffer | should be called with an array of data
			the type of the data is depending on the number of vertices avaible to index, so if there are a maximum of 255 vertices to index an unsigned char would be good as a type, but with 4294967295  vertices it should be an unsigned int
			@param[count] the number of elements stored in the array of data 
			@param[drawmode] the kind of the buffer data
			GL_STATIC_DRAW 0x88E4 the data will most likely not change at all or very rarely
			GL_DYNAMIC_DRAW 0x88E8 the data is likely to change a lot
			GL_STREAM_DRAW 0x88E0 the data will change every time it is drawn*/
			IndexBuffer(const type* data, GLuint count, GLenum drawMode = GL_STATIC_DRAW) noexcept
				:m_count(count)
			{
				glGenBuffers(1, &m_id);
				glBindBuffer(bufferType, m_id);//an element array buffer instead of the array buffer of the vbo
				glBufferData(bufferType, count * sizeof(type), static_cast<const void*>( data ), drawMode);//1. type, 2. size, 3. ptr to array of data, 4. drawmode
			}

			/*creates an empty indexbuffer with an uninitialized opengl buffer | does not bind it*/
			IndexBuffer() noexcept
				:m_id(0), m_count(0)
			{
			}

			/*deletes the indexbufferid in the opengl state machine*/
			~IndexBuffer() noexcept
			{
				glDeleteBuffers(1, &m_id);
			}

			IndexBuffer(const IndexBuffer<type>&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			IndexBuffer(IndexBuffer<type>&& other) noexcept
				: m_id(other.m_id), m_count(other.m_count)
			{
				other.m_id = 0;
				other.m_count = 0;
			}

			IndexBuffer<type>& operator=(const IndexBuffer<type>&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			IndexBuffer<type>& operator=(IndexBuffer<type>&& other) noexcept
			{
				m_id = other.m_id;
				m_count = other.m_count;
				other.m_id = 0;
				other.m_count = 0;
				return *this;
			}

		public:
			/*draws all the vertices(as triangles) of the currently bound vertexarray with the order of the indices of the currently bound indexbuffer | the shader has to be bound first, then a texture should be bound and after that the vertexarray has to be bound before calling the method
			vertexarray.bind() saves the vbos bound while the vao was bound and also saves the last ibo bound while the vao was bound (but just one) | CAREFUL it does not bind the vbos, or the ibo, but they dont have to be bound before drawing if the vao is bound
			if more than 1 indexbuffer is used to render the vertexbuffers of an vertexarray you have to call indexbuffer.bind() before indexbuffer.render() for each indexbuffer independently
			otherwise you can just call vertexarray.bind() and then indexbuffer.render() without calling indexbuffer.bind()
			its the normal method for few big models with diffrent shaders where the model is drawn per instance/object with another draw call and the transformation is passed as an uniform to the shader for each drawcall*/
			void draw() const noexcept
			{
				glDrawElements(GL_TRIANGLES, m_count, OpenglType<type>::gltype, nullptr);//gldrawelements to specify that its drawing an indexbuffer | 1. draw kind(everything is drawn of ttriangles), 2. count of indices to draw, 3. type of the indices, 4. offset in the indexbuffer, or index array(for using when not using index buffeR)
			}

			/*its the same as the normal draw method, but the vertices will be drawn as lines*/
			void drawLine() const noexcept
			{
				glDrawElements(GL_LINES, m_count, OpenglType<type>::gltype, nullptr);
			}

			/*draws all the vertices(as triangles) of the currently bound vertexarray with the order of the indices of the currently bound indexbuffer | the shader has to be bound first, then a texture should be bound and after that the vertexarray has to be bound before calling the method
			vertexarray.bind() saves the vbos bound while the vao was bound and also saves the last ibo bound while the vao was bound (but just one) | CAREFUL it does not bind the vbos, or the ibo, but they dont have to be bound before drawing if the vao is bound
			if more than 1 indexbuffer is used to render the vertexbuffers of an vertexarray you have to call indexbuffer.bind() before indexbuffer.render() for each indexbuffer independently
			otherwise you can just call vertexarray.bind() and then indexbuffer.render() without calling indexbuffer.bind()
			its the instanced method for many small models with the same shader where the model is drawn as multiple object instances with diffrent transformations, but the draw call has to be called once per model and not once per object/instance
			@param[instanceCount] the count of diffrent objects/transformations/instances of each model to draw | you have to store the diffrent model matrices per object/instance in a seperate vertexbuffer for instanced arrays and the transformation will be passed as a vertexattribute to the shader for each instance */
			void drawInstanced(unsigned int instanceCount) const noexcept
			{
				glDrawElementsInstanced(GL_TRIANGLES, m_count, OpenglType<type>::gltype, nullptr, instanceCount);//additional count of instances to draw of the model
			}

			/*draws all the vertices(as triangles) of the currently bound vertexarray with the order of the indices of the currently bound indexbuffer | the shader has to be bound first, then a texture should be bound and after that the vertexarray has to be bound before calling the method
			vertexarray.bind() saves the vbos bound while the vao was bound and also saves the last ibo bound while the vao was bound (but just one) | CAREFUL it does not bind the vbos, or the ibo, but they dont have to be bound before drawing if the vao is bound
			if more than 1 indexbuffer is used to render the vertexbuffers of an vertexarray you have to call indexbuffer.bind() before indexbuffer.render() for each indexbuffer independently
			otherwise you can just call vertexarray.bind() and then indexbuffer.render() without calling indexbuffer.bind()
			its the normal method for few big models with the same shader where the model is drawn per instance/object with another draw call and the transformation is passed as an uniform to the shader for each drawcall
			this is an addition to the normal draw method, where you can specify an offset where to start drawing indices and the number of indices to draw | so you dont draw the whole indices of the ibo, but a rather a part of ibos
			for example this is useful to draw the parts of a cube with diffrent textures by binding the first texture with the first vertices for the first square of the cube and so on
			@param[position] the offset into the buffer in count of indices that will be skipped, or the position of the first index to be drawn | 0 means the drawing starts with the first index(position 0) with no offset
			@param[indicesCount] the amount of indices to draw | should not be bigger than the amount of indices stored in the indexbuffer(m_count)*/
			void drawParts(unsigned int position, unsigned int indicesCount ) const noexcept
			{
				glDrawElements(GL_TRIANGLES, indicesCount, OpenglType<type>::gltype, reinterpret_cast<void*>(position * sizeof(type)));
			}

			/*draws all the vertices(as triangles) of the currently bound vertexarray with the order of the indices of the currently bound indexbuffer | the shader has to be bound first, then a texture should be bound and after that the vertexarray has to be bound before calling the method
			vertexarray.bind() saves the vbos bound while the vao was bound and also saves the last ibo bound while the vao was bound (but just one) | CAREFUL it does not bind the vbos, or the ibo, but they dont have to be bound before drawing if the vao is bound
			if more than 1 indexbuffer is used to render the vertexbuffers of an vertexarray you have to call indexbuffer.bind() before indexbuffer.render() for each indexbuffer independently
			otherwise you can just call vertexarray.bind() and then indexbuffer.render() without calling indexbuffer.bind()
			its the instanced method for many small models with diffrent shaders where the model is drawn as multiple object instances with diffrent transformations, but the draw call has to be called once per model and not once per object/instance
			this is an addition to the normal drawinstanced method, where you can specify an offset where to start drawing indices and the number of indices to draw | so you dont draw the whole indices of the ibo, but a rather a part of ibos
			for example this is useful to draw the parts of a cube with diffrent textures by binding the first texture with the first vertices for the first square of the cube and so on
			@param[position] the offset into the buffer in count of indices that will be skipped, or the position of the first index to be drawn | 0 means the drawing starts with the first index(position 0) with no offset
			@param[indicesCount] the amount of indices to draw | should not be bigger than the amount of indices stored in the indexbuffer(m_count)
			@param[instanceCount] the count of diffrent objects/transformations/instances of each model to draw | you have to store the diffrent model matrices per object/instance in a seperate vertexbuffer for instanced arrays and the transformation will be passed as a vertexattribute to the shader for each instance */
			void drawInstancedParts(unsigned int position, unsigned int indicesCount, unsigned int instanceCount) const noexcept
			{
				glDrawElementsInstanced(GL_TRIANGLES, indicesCount, OpenglType<type>::gltype, reinterpret_cast<void*>( position * sizeof(type)), instanceCount);
			}

			/*binds this opengl element array buffer to the opengl state machine, so opengl can work with it(by using buffercalls on GL_ELEMENT_ARRAY_BUFFER)
			only one buffer of the same type(here indexbuffer/element_array_buffer) can be bound at a time, but buffers of other types can be bound at the same time | vertexarray, vertexbuffer and indexbuffer are independant(can be bound at the same time)*/
			void bind() const noexcept
			{
				glBindBuffer(bufferType, m_id);
			}

			/*unbinds all indexbuffers/element_array_buffers*/
			void unbind() const noexcept
			{
				glBindBuffer(bufferType, 0);
			}

		public:
			/*returns the unique opengl id of this buffer for opengls state machine*/
			const GLuint getId() const noexcept {return m_id;}

			/*returns the number of indices to draw*/
			const unsigned int getCount() const noexcept {return m_count;}


		};

	}
}