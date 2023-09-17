#pragma once
#include "glad\glad.h"
#include "src\Graphics\OpenglStuff.h"
#include "src\Utils\Helper.h"
#if CLOCKWORK_DEBUG
#include <vector>
#endif

namespace clockwork {
	namespace graphics {

		class CopyBuffer;
		class InternalCopyBuffer;
		class VertexArray;

		/*stores the vertex data on the gpu and configure how opengl should interpret the memory
		the data(large number of vertices) is passed to the vertex shader all at once
		its a gl_array_buffer
		has an internalcopybuffer as its internal buffer to swap data*/
		class VertexBuffer
		{

		private:
			GLuint m_id;
			GLuint m_size;
			GLenum m_bufferMode;

		private:
			static InternalCopyBuffer* copyBuffer;

		public:
			/*the offset that is calculated when calling connectToVao and reset when creating an object with the constructor */
			static GLuint vaoOffset;
			/*the position that is calculated when calling connectToVao and reset when creating an object with the constructor */
			static GLuint VaoPos;
			/*the buffertype of the buffer | here GL_ARRAY_BUFFER*/
			static const GLint bufferType = GL_ARRAY_BUFFER;

		public:
#if CLOCKWORK_DEBUG
			static std::vector<VertexBuffer*> debug_buffers;
			mutable bool debug_bound;
#endif

		public:
			/*creates a vertexbuffer with the given data, fills the buffer with the data and binds it, so another bind() call is unnecessary | important:this is limited to one type of data in the vertexbuffer, so you cant store diffrent types like positions as floats and colours as unsigned chars
			but you can create a struct called vertex with members like 3 floats for position and 4 unsigned chars for colours | then you pass a pointer to an array of vertices and the size is count of vertices times sizeof(vertex) | like this you can store diffrent types together in a vertexbuffer
			@param[data] pointer to the userdata which is copied into the buffer(can be nullptr for an empty buffer with reserved capacity of size) | should be called with an array of data
			@param[size] the size of the data(array) in bytes | count of elements times sizeof(type) | its the capacity of the vertexbuffer, so it can be larger than the actual size of the data of the pointer to reserve some bytes
			@param[bufferMode] the kind of the buffer data / how its stored and how it will be changed
			GL_STATIC_DRAW 0x88E4 the data will most likely not change at all or very rarely
			GL_DYNAMIC_DRAW 0x88E8 the data is likely to change a lot
			GL_STREAM_DRAW 0x88E0 the data will change every time it is drawn
			
			you can either create create a vertexbuffer with a pointer to some data with the size of the data or an empty vertexbuffer with data pointer as nullptr and a predefined size for future data */
			VertexBuffer(const void* data, GLuint size, GLenum bufferMode = GL_STATIC_DRAW) noexcept
				: m_size(size), m_bufferMode(bufferMode)
			{
				glGenBuffers(1, &m_id);
				glBindBuffer(bufferType, m_id);//type of vertexbuffer is GL_ARRAY_BUFFER
				glBufferData(bufferType, size, data, bufferMode);//1. type, 2. size, 3. pointer to data array, 4. drawmode
				if ( VaoPos != 0 )
				{
					VaoPos = 0;
					vaoOffset = 0;
				}
#if CLOCKWORK_DEBUG
				for ( std::vector<VertexBuffer*>::iterator it = debug_buffers.begin(); it != debug_buffers.end(); ++it )
					(*it)->debug_bound = false;
				debug_bound = true;
				debug_buffers.push_back(this);
#endif
			}

			/*creates an empty vertexbuffer with an uninitialized opengl buffer | does not bind it*/
			VertexBuffer() noexcept
				:m_id(0), m_size(0), m_bufferMode(0)
			{
#if CLOCKWORK_DEBUG
				debug_bound = false;
				debug_buffers.push_back(this);
#endif
			}

			/*deletes the vertexbufferid in the opengl state machine*/
			~VertexBuffer() noexcept
			{
				glDeleteBuffers(1, &m_id);
#if CLOCKWORK_DEBUG
				debug_bound = false;
				for ( std::vector<VertexBuffer*>::iterator it = debug_buffers.begin(); it != debug_buffers.end(); ++it )
				{
					if ( ( *it ) == this )
					{
						debug_buffers.erase(it);
						break;
					}
				}
#endif
			}

			VertexBuffer(const VertexBuffer&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			VertexBuffer(VertexBuffer&& other) noexcept
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

			VertexBuffer& operator=(const VertexBuffer&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			VertexBuffer& operator=(VertexBuffer&& other) noexcept
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

			/*the vertexbuffer has to be bound first and the vertexarray where the pointers should be stored in has to be bound too|
			specifies how the data is stored in the currently bound vertexbuffer and how to access the data in the shaders by using the position that is saved in the currently bound vertexarray
			this is the version of the method where the offset and pos are automaticly calculated per method call for all vertexbuffers and reset when a new vertexbuffer is created with the constructor call | its important to call this method in order(first for the first attribute in the vertex(stored in the vertexbufferdata), then again for the second attribute and so on)
			you should first create all your needed vertexbuffers, then call the method n times to specify the pointers for one, or more vertexbuffers and then never edit this vertexarray again, because after the creation of another vertexbuffer the offset and the position of the last edited vertexarray with the vertexbuffers are lost, because they were reset
			@templateparam[type] the type of the data at the position/offset/attribute in the vertexbuffer | for example a 3d position has 3 floats, so the type is float, but if the next data in the vertexbuffer is a colour, you might wanna use unsigned chars for the colour value(and normalized true and) at the next position/offset/attribute of a vertex in the vertexbuffer  
			@param[dim] the dimension of each vertex attribute(1=vec1 to 4=vec4) for example 3d position is 3 | its the count of objects of the type that are saved at the position/offset/attribute in the vertexbuffer | maximum is vec4, so a mat4 in a vertexbuffer has to be connected as 4 vec4s
			@param[normalized] if the type value should be normalized to a floating point value from -1 to 1(for unsigned types from 0 to 1), so the shader can work with the data | if the date is already normalized pass in false
			@param[pos] the position in the vertexarray to access the vertexbuffer in the shaders | for example pos=0 access in shader with layout(location = 0)in ... | the first call starts at 0 and then it increments per call | the pos is a public static variable of the class vertexbuffer, so you can manually change it 
			@param[offset] the offset/distance in bytes where the attribute is stored per vertex | first attribute is 0, but then always add the other attributes together | the offset is a public static variable of the class vertexbuffer, so you can manually change it 
			@param[stride] the distance in bytes from one vertex attribute to the next vertex attribute from the same kind in the vertexbuffer | all attributes added up together to make up the size of one vertex in the vertexbuffer, so the stride is the size of one vertex | the stride can be left at 0 when the data in the vertexbuffer is tighly packed(just one attribute) for example one vertexbuffer for only positions, etc
			@param[instancing] when to update the content of a vertex attribute to the next element | 0 = per vertex(each time the vertex shader is called), 1 = per instance(each time a new instance/model is drawn with ibo.drawInstanced(10) for 10 instances of a model, 2 = per 2 instances, etc
			the default of instancing is 0(where the vertexbuffer is not an instanced array and stores data per vertex) and a value of 1 for the instancing means the current vbo is an instanced array and stores data per instance of the model
			the updating means when to process the next set of attributes in the vertexbuffer | for example position, colour are saved per vertex in vertexbuffer to form the model and instancing should be 0 | or modelmatrices are saved in the vertexbuffer to draw objects with diffrent transformations of the model and instancing should be 1 

			pos is in relation to the vertexarray and offset/stride are in relation to the vertexbuffer | pos and offset will be calculated per call of the method, so if you wanna use another vertexbuffer for the same vertexarray, you have to reset the offset, or use the other method

			for example you have a vertexbuffer with an array of data where you got per vertex first 3 floats for the position(normalized from -1 to 1) and then 3 floats from 0 to 1 for the rgb colour value
			you would first call this method with the type float and the vbo, the position 0(because its the first pointer in the vertexarray), the dimension 3(because 3 floats per position) and normalized false(because the positions are already normalized), the stride 24 because of the 3 floats for position and the 3 floats for colour(3*4+3*4 bytes), the offset 0 because its the first attribute per vertex
			then you would call this method again with the type float and the vbo, the position 1(because its the second pointer int the vertexarray), the dimension 3 again and normalized false again, because its also normalized, stride same as above and offset is now 12, because of the 3*4 bytes of the 3 floats for the position, because its the second attribute
			you can then access the position of the vertices as location 0 in the shader and the colour of the vertices as location 1 in the shader
			another good example would be an array of an own defined vertex class as data in the vertexbuffer, where the diffrent attributes of one vertex are stored(for example 3 floats for position and 4 unsigned chars for colour) | its almost the same as above, but you have to change the type to unsigned char for the second call for the colour vec4
			the benefits are that stride is simply sizeof(vertex) and the offset can also be calculated with offsetof(position.x) or offsetof(colour.r) when they are vec3/4 member of the vertex class | and you can also easily store attributes of diffrent types in the vertexbuffer*/
			template<typename type>
			void connectToVao(GLint dim, GLboolean normalized, GLuint stride = 0, GLuint instancing = 0) const noexcept
			{
#if CLOCKWORK_DEBUG
				if ( !debug_bound )
					std::cout << "Error VertexBuffer::connectToVao(): VertexBuffer was not bound" << std::endl;
#endif
				glEnableVertexAttribArray(VaoPos);//enables the vertexarray at the position

				if( OpenglType<type>::gltype == OpenglType<float>::gltype || OpenglType<type>::gltype == OpenglType<double>::gltype )
					glVertexAttribPointer(VaoPos, dim, OpenglType<type>::gltype, normalized, stride, reinterpret_cast<void*>( vaoOffset ));//1. position of the vertexbuffer in the vertexarray, 2. dimension of the vertices(vec2-vec4), 3. type of the vertices, 4. normalized, 4. size of one vertex, 5. offset from the beginning of the vertexbuffer to this position
				else
					glVertexAttribIPointer(VaoPos, dim, OpenglType<type>::gltype, stride, reinterpret_cast<void*>( vaoOffset ));
				glVertexAttribDivisor(VaoPos, instancing);
				vaoOffset += dim * sizeof(type);
				VaoPos += 1;
			}

			/*the vertexbuffer has to be bound first and the vertexarray where the pointers should be stored in has to be bound too|
			specifies how the data is stored in the currently bound vertexbuffer and how to access the data in the shaders by using the position that is saved in the currently bound vertexarray
			this is the version where you specify the pos and offset yourself, so you dont have to worry about the order when you specify the pointers 
			@templateparam[type] the type of the data at the position/offset/attribute in the vertexbuffer | for example a 3d position has 3 floats, so the type is float, but if the next data in the vertexbuffer is a colour, you might wanna use unsigned chars for the colour value(and normalized true and) at the next position/offset/attribute of a vertex in the vertexbuffer
			@param[dim] the dimension of each vertex attribute(1=vec1 to 4=vec4) for example 3d position is 3 | its the count of objects of the type that are saved at the position/offset/attribute in the vertexbuffer | maximum is vec4, so a mat4 in a vertexbuffer has to be connected as 4 vec4s
			@param[normalized] if the type value should be normalized to a floating point value from -1 to 1(for unsigned types from 0 to 1), so the shader can work with the data | if the date is already normalized pass in false
			@param[pos] the position in the vertexarray to access the vertexbuffer in the shaders | for example pos=0 access in shader with layout(location = 0)in ... | the first call starts at 0 and then it increments per call | the pos is a public static variable of the class vertexbuffer, so you can manually change it
			@param[offset] the offset/distance in bytes where the attribute is stored per vertex | first attribute is 0, but then always add the other attributes together 
			@param[stride] the distance in bytes from one vertex attribute to the next vertex attribute from the same kind in the vertexbuffer | all attributes added up together to make up the size of one vertex in the vertexbuffer, so the stride is the size of one vertex | the stride can be left at 0 when the data in the vertexbuffer is tighly packed(just one attribute) for example one vertexbuffer for only positions, etc
			@param[instancing] when to update the content of a vertex attribute to the next element | 0 = per vertex(each time the vertex shader is called), 1 = per instance(each time a new instance/model is drawn with ibo.drawInstanced(10) for 10 instances of a model, 2 = per 2 instances, etc
			the default of instancing is 0(where the vertexbuffer is not an instanced array and stores data per vertex) and a value of 1 for the instancing means the current vbo is an instanced array and stores data per instance of the model
			the updating means when to process the next set of attributes in the vertexbuffer | for example position, colour are saved per vertex in vertexbuffer to form the model and instancing should be 0 | or modelmatrices are saved in the vertexbuffer to draw objects with diffrent transformations of the model and instancing should be 1

			pos is in relation to the vertexarray, but offset and stride are in relation to the vertexbuffer | so pos has to be calculated per vertexarray, but the others have to be calculated per vertexbuffer

			for example you have a vertexbuffer with an array of data where you got per vertex first 3 floats for the position(normalized from -1 to 1) and then 3 floats from 0 to 1 for the rgb colour value
			you would first call this method with the type float and the vbo, the position 0(because its the first pointer in the vertexarray), the dimension 3(because 3 floats per position) and normalized false(because the positions are already normalized), the stride 24 because of the 3 floats for position and the 3 floats for colour(3*4+3*4 bytes), the offset 0 because its the first attribute per vertex
			then you would call this method again with the type float and the vbo, the position 1(because its the second pointer int the vertexarray), the dimension 3 again and normalized false again, because its also normalized, stride same as above and offset is now 12, because of the 3*4 bytes of the 3 floats for the position, because its the second attribute
			you can then access the position of the vertices as location 0 in the shader and the colour of the vertices as location 1 in the shader
			another good example would be an array of an own defined vertex class as data in the vertexbuffer, where the diffrent attributes of one vertex are stored(for example 3 floats for position and 4 unsigned chars for colour) | its almost the same as above, but you have to change the type to unsigned char for the second call for the colour vec4
			the benefits are that stride is simply sizeof(vertex) and the offset can also be calculated with offsetof(position.x) or offsetof(colour.r) when they are vec3/4 member of the vertex class*/
			template<typename type>
			void connectToVao(GLint dim, GLboolean normalized, GLuint pos, GLuint offset, GLuint stride, GLuint instancing = 0) const noexcept
			{
#if CLOCKWORK_DEBUG
				if ( !debug_bound )
					std::cout << "Error VertexBuffer::connectToVao(): VertexBuffer was not bound" << std::endl;
				//if ( debug_vertexarray== nullptr )
				//	std::cout << "Error VertexBuffer::connectToVao(): debug_vertexarray was not initialized" << std::endl;
				//else if ( !debug_vertexarray->debug_bound )
				//	std::cout << "Error VertexBuffer::connectToVao(): VertexArray was not bound" << std::endl;
#endif
				glEnableVertexAttribArray(pos);//enables the vertexarray at the position
				if ( OpenglType<type>::gltype == OpenglType<float>::gltype || OpenglType<type>::gltype == OpenglType<double>::gltype )
				glVertexAttribPointer(pos, dim, OpenglType<type>::gltype, normalized, stride, reinterpret_cast<void*>( offset ));//1. position of the vertexbuffer in the vertexarray, 2. dimension of the vertices(vec2-vec4), 3. type of the vertices, 4. normalized, 4. size of one vertex, 5. offset from the beginning of the vertexbuffer to this position
				else
					glVertexAttribIPointer(pos, dim, OpenglType<type>::gltype, stride, reinterpret_cast<void*>( offset ));
				glVertexAttribDivisor(pos, instancing);
			}

			/*copies new data into the buffer with a given offset and with a specified size and replaces the old data at that area | the buffermode and the size stays the same
			the buffer has to be bound first
			@param[data] pointer to the userdata which is copied into the buffer | should be called with an array of data
			@param[size] the size of the data(array) in bytes | count of elements times sizeof(type) | the size and the offset together should not be larger than the size/capacity of the buffer
			@param[offset] the position in the buffer where to start | the default is 0 for the beginning of the buffer to set the size equal to the size of the buffer and replace all of the data of the buffer with new data
			the offset is also how many bytes from the start are not copied, so it specifies where the data replacement will begin measured in bytes*/
			void setData(const void* data, unsigned int size, unsigned int offset=0) noexcept;

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
			VertexBuffer& copy(const VertexBuffer& other) noexcept;

			/*copies the the size and the data of the other buffer to this buffer | the buffermode will stay the same
			both buffer have to be bound first and both buffers will stay bound after the method*/
			VertexBuffer& copy(const CopyBuffer& other) noexcept;

			/*copies the the size and the data of the other buffer to this buffer | the buffermode will stay the same
			both buffer have to be bound first and both buffers will stay bound after the method*/
			VertexBuffer& copy(const InternalCopyBuffer& other) noexcept;

			/*binds this opengl array buffer to the opengl state machine, so opengl can work with it(by using buffercalls on GL_ARRAY_BUFFER)
			only one buffer of the same type(here vertexbuffer/gl_array_buffer) can be bound at a time, but buffers of other types can be bound at the same time | vertexarray, vertexbuffer and indexbuffer are independant(can be bound at the same time)*/
			void bind() const noexcept
			{
#if CLOCKWORK_DEBUG
				for ( std::vector<VertexBuffer*>::iterator it = debug_buffers.begin(); it != debug_buffers.end(); ++it )
					( *it )->debug_bound = false;
				debug_bound = true;
#endif
				glBindBuffer(bufferType, m_id);
			}

			/*unbinds all vertexbuffers/gl_array_buffers*/
			void unbind() const noexcept
			{
#if CLOCKWORK_DEBUG
				for ( std::vector<VertexBuffer*>::iterator it = debug_buffers.begin(); it != debug_buffers.end(); ++it )
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
			const GLuint getId() const noexcept {return m_id;}

			/*returns the capacity of the vertexbuffer in bytes*/
			const GLuint getSize() const noexcept{return m_size;}

		};


	}
}