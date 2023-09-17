#pragma once
#include "glad\glad.h"
#include <unordered_map>
#include <string>
#include "src\Utils\Helper.h"
#include "src\Utils\File.h"
#include "src\Maths\Vec2.h"
#include "src\Maths\Vec3.h"
#include "src\Maths\Vec4.h"
#include "src\Maths\Mat2x2.h"
#include "src\Maths\Mat2x3.h"
#include "src\Maths\Mat2x4.h"
#include "src\Maths\Mat3x2.h"
#include "src\Maths\Mat3x3.h"
#include "src\Maths\Mat3x4.h"
#include "src\Maths\Mat4x2.h"
#include "src\Maths\Mat4x3.h"
#include "src\Maths\Mat4x4.h"

namespace clockwork {
	namespace graphics {

		/*shader programs are in the opengl state machine and need to be enabled/disabled because only one shader program can be enabled at a time
		this shader program is a combination of a vertex shader and a fragment shader*/
		class Shader
		{

		private:
			GLuint m_id;
			std::string m_vertexPath;//paths um später die gameobjekte im chunk in listen von verschiedenen shadern zu unterteilen zum vergleichen vom shaderpath
			std::string m_fragmentPath;//muss dann im konstruktor des gameobjekts genauso wie currentstate mitgegeben werden und das gameobjekt erstellt sich selbst dann im chunksystem und ordnet sich den jeweiligen listen zu 
			std::unordered_map<std::string, int> m_uniformLocationCache;

		public:

			/*creates an empty shader with no data in it, so you have to call loadData() before using it*/
			Shader() noexcept
				: m_id(0)
			{}

			/*loads a vertex and a fragmentshader into a shader program both specified by the file path relative to the engine.exe
			vertex shader is called for each vertex(for example triangle 3 times), specifies how the vertex arrives at the screen and passes the data(for example position) to the fragment shader
			fragment shader is called for each pixel between the vertices and specifies the colour/lightning of the pixels
			the shader will not be enabled after this method before calling enable() | so you have to call enable() ! */
			Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) noexcept
				:m_vertexPath(vertexShaderPath), m_fragmentPath(fragmentShaderPath)
			{
				loadShader(vertexShaderPath, fragmentShaderPath);
			}

			/*deletes the shader program with the id*/
			~Shader() noexcept
			{
				deleteShader();
			}

			Shader(const Shader&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			Shader(Shader&& other) noexcept
				: m_id(other.m_id), m_vertexPath(std::move(other.m_vertexPath)), m_fragmentPath(std::move(other.m_fragmentPath)), m_uniformLocationCache(std::move(other.m_uniformLocationCache))
			{
				other.m_id = 0;
			}

			Shader& operator=(const Shader&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			Shader& operator=(Shader&& other) noexcept
			{
				m_id = other.m_id;
				other.m_id = 0;
				m_vertexPath = std::move(other.m_vertexPath);
				m_fragmentPath = std::move(other.m_fragmentPath);
				m_uniformLocationCache = std::move(other.m_uniformLocationCache);
			}

		public:
			/*loads a vertex and a fragmentshader into a shader program both specified by the file path relative to the engine.exe
			vertex shader is called for each vertex(for example triangle 3 times), specifies how the vertex arrives at the screen and passes the data(for example position) to the fragment shader 
			fragment shader is called for each pixel between the vertices and specifies the colour/lightning of the pixels*/
			void loadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) noexcept
			{
				m_vertexPath = vertexShaderPath;
				m_fragmentPath = fragmentShaderPath;
				if ( m_id == 0 )
					m_id = glCreateProgram();//one shader program for both fragment and vertex shader
				m_uniformLocationCache.clear();

				GLuint vs = glCreateShader(GL_VERTEX_SHADER);//vertex shader unique opengl state id 
				GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);//here fragmentshader

				utils::File tempVsSource { vertexShaderPath };//has to be created as a temp string, because otherwise as a rvalue object the data would have been deleted after the function call and the chars cant be saved in the source when compiling the shaders(temp rvalue objects are deleted after function call when passed as parameters)
				utils::File tempFsSource { fragmentShaderPath };//has to be alive when the shader is being compiled

				const char* vsSource = tempVsSource.read().getData().c_str();//returntyp std::string of utils::readfile has to be converted to cstring for opengl to use it | has to be saved as temp copy, because the opengl function cant take in reference to rvalue objects and std::string.c_str() creates an rvalue char pointer
				const char* fsSource = tempFsSource.read().getData().c_str();

				glShaderSource(vs, 1, &vsSource, NULL);//first shader id, second how many strings, third source of the shader(memoryadress of cstring, so pointer to pointer to char), fourth lenght of the string as nullptr so opengl automaticly determines the size to the \0 char of the cstring
				glShaderSource(fs, 1, &fsSource, NULL);

				glCompileShader(vs);//compiles the shader
				glCompileShader(fs);

#if CLOCKWORK_DEBUG 
				GLint result;
				glGetShaderiv(vs, GL_COMPILE_STATUS, &result);//iv = int vector/array | error checking for the vertex shader and saved in result(parameter memoryadress of result)
				if ( !result )
				{
					GLint lenght;
					glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &lenght);
					char* message = static_cast<char*>( alloca(lenght * sizeof(char)) );//stack allocated array cant be created with runtime dependant size, so it could be created as dynamic array, but to create it on the stack with alloca(bytes) and then cast the void pointer to char pointer | faster and dont have to delete it 
					glGetShaderInfoLog(vs, lenght, &lenght, message);
					std::cout << "Failed to compile vertex shader!" << std::endl;
					std::cout << message << std::endl;
				}
				glGetShaderiv(fs, GL_COMPILE_STATUS, &result);//the same for the fragment shader
				if ( !result )
				{
					GLint lenght;
					glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &lenght);
					char* message = (char*) alloca(lenght * sizeof(char));
					glGetShaderInfoLog(fs, lenght, &lenght, message);
					std::cout << "Failed to compile fragment shader!" << std::endl;
					std::cout << message << std::endl;
				}
#endif

				glAttachShader(m_id, vs);//add shader to the shader program
				glAttachShader(m_id, fs);

				glLinkProgram(m_id);//compile and check shader program
				glValidateProgram(m_id);

				glDeleteShader(vs);//delete the shaders, because they are saved in the program
				glDeleteShader(fs);
			}
			
			/*deletes the shader program with the id*/
			void deleteShader() const noexcept
			{
				glDeleteProgram(m_id);
			}

			/*enables the shader for the following render calls(a shader has to be bound before rendering anything(textures/models) | only one shader can be enabled at the same time*/
			void enable() const noexcept
			{
				glUseProgram(m_id);
			}

			/*disables all shaders*/
			void disable() const noexcept
			{
				glUseProgram(0);
			}

			/*caches the uniformLocation for a given name to improve performance when setting uniforms of the shader*/
			int getUniformLocation(const std::string& name) noexcept
			{
				if ( m_uniformLocationCache.find(name) != m_uniformLocationCache.end() )
					return m_uniformLocationCache[name];
				int location = glGetUniformLocation(m_id, name.c_str());
#if CLOCKWORK_DEBUG 
				if ( location == -1 )
					std::cout << "Error Shader::getUniformLocation(): uniform " << name << " does not exist" << std::endl;
#endif
				m_uniformLocationCache[name] = location;
				return location;
			}

			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, int val) noexcept
			{
				glUniform1i(getUniformLocation(name), val);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Vec2<int>& vec2) noexcept
			{
				glUniform2i(getUniformLocation(name), vec2.x, vec2.y);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, int x, int y) noexcept
			{
				glUniform2i(getUniformLocation(name), x, y);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Vec3<int>& vec3) noexcept
			{
				glUniform3i(getUniformLocation(name), vec3.x, vec3.y, vec3.z);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, int x, int y, int z) noexcept
			{
				glUniform3i(getUniformLocation(name), x, y, z);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Vec4<int>& vec4) noexcept
			{
				glUniform4i(getUniformLocation(name), vec4.x, vec4.y, vec4.z, vec4.w);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, int x, int y, int z, int w) noexcept
			{
				glUniform4i(getUniformLocation(name), x, y, z, w);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, unsigned int val) noexcept
			{
				glUniform1ui(getUniformLocation(name), val);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Vec2<unsigned int>& vec2) noexcept
			{
				glUniform2ui(getUniformLocation(name), vec2.x, vec2.y);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, unsigned int x, unsigned int y) noexcept
			{
				glUniform2ui(getUniformLocation(name), x, y);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Vec3<unsigned int>& vec3) noexcept
			{
				glUniform3ui(getUniformLocation(name), vec3.x, vec3.y, vec3.z);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, unsigned int x, unsigned int y, unsigned int z) noexcept
			{
				glUniform3ui(getUniformLocation(name), x, y, z);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Vec4<unsigned int>& vec4) noexcept
			{
				glUniform4ui(getUniformLocation(name), vec4.x, vec4.y, vec4.z, vec4.w);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, unsigned int x, unsigned int y, unsigned int z, unsigned int w) noexcept
			{
				glUniform4ui(getUniformLocation(name), x, y, z, w);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, float val) noexcept
			{
				glUniform1f(getUniformLocation(name), val);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Vec2<float>& vec2) noexcept
			{
				glUniform2f(getUniformLocation(name), vec2.x, vec2.y);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, float x, float y) noexcept
			{
				glUniform2f(getUniformLocation(name), x, y);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Vec3<float>& vec3) noexcept
			{
				glUniform3f(getUniformLocation(name), vec3.x, vec3.y, vec3.z);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, float x, float y, float z) noexcept
			{
				glUniform3f(getUniformLocation(name), x, y, z);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Vec4<float>& vec4) noexcept
			{
				glUniform4f(getUniformLocation(name), vec4.x, vec4.y, vec4.z, vec4.w);//1. position/name of the uniform in the shaderprogram retrieved with getuniformlocation with shaderid and name of uniform | the other stuff are parameter to pass over
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, float x, float y, float z, float w) noexcept
			{
				glUniform4f(getUniformLocation(name), x, y, z, w);
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Mat2x2<float>& mat2x2) noexcept
			{
				glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, static_cast<const GLfloat*>( &mat2x2.x1 ));//1 for 1 matrix and GL_TRUE because the matrices are in row-major layout and not in column major 
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Mat2x3<float>& mat2x3) noexcept
			{
				glUniformMatrix3x2fv(getUniformLocation(name), 1, GL_FALSE, static_cast<const GLfloat*>( &mat2x3.x1 ));
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Mat2x4<float>& mat2x4) noexcept
			{
				glUniformMatrix4x2fv(getUniformLocation(name), 1, GL_FALSE, static_cast<const GLfloat*>( &mat2x4.x1 ));
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Mat3x2<float>& mat3x2) noexcept
			{
				glUniformMatrix2x3fv(getUniformLocation(name), 1, GL_FALSE, static_cast<const GLfloat*>( &mat3x2.x1 ));
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Mat3x3<float>& mat3x3) noexcept
			{
				glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, static_cast<const GLfloat*>( &mat3x3.x1 ));
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Mat3x4<float>& mat3x4) noexcept
			{
				glUniformMatrix4x3fv(getUniformLocation(name), 1, GL_FALSE, static_cast<const GLfloat*>( &mat3x4.x1 ));
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Mat4x2<float>& mat4x2) noexcept
			{
				glUniformMatrix2x4fv(getUniformLocation(name), 1, GL_FALSE, static_cast<const GLfloat*>( &mat4x2.x1 ));
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Mat4x3<float>& mat4x3) noexcept
			{
				glUniformMatrix3x4fv(getUniformLocation(name), 1, GL_FALSE, static_cast<const GLfloat*>( &mat4x3.x1 ));
			}
			/*passes data to a shader with the name of the uniform for access in the shader | the shader has to be enabled first*/
			void setUniform(const std::string& name, const maths::Mat4x4<float>& mat4x4) noexcept
			{
				glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, static_cast<const GLfloat*>( &mat4x4.x1 ));
			}

		public:
			/*returns the unique opengl shader id of the shader program*/
			const GLuint getId() const noexcept {return m_id;}

			/*returns the path of the vertex shader relative to the engine.exe*/
			const std::string getVertexPath() const noexcept {return m_vertexPath;}

			/*returns the path of the fragment shader relative to the engine.exe*/
			const std::string getFragmentPath() const noexcept {return m_fragmentPath;}

		};

	}
}
