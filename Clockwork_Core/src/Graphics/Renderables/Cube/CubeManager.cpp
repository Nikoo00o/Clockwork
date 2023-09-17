#include <algorithm>
#include "InstancedCube.h"
#include "NormalCube.h"
#include "CubeManager.h"
#include "src\Graphics\Renderer\Renderer.h"
#include "src\Logics\Entities\GameObject.h"

namespace clockwork {
	namespace graphics {

		struct TransparentCubeCompare
		{
			CubeManager* m_manager;
			TransparentCubeCompare(CubeManager* manager)
				:m_manager(manager)
			{}
			inline bool operator()(NormalCube* ptr1, NormalCube* ptr2)
			{
				return ptr1->m_gameObject->getPosition().distance(( *m_manager->m_renderer->m_currentCamera )->getPosition()) > ptr2->m_gameObject->getPosition().distance(( *m_manager->m_renderer->m_currentCamera )->getPosition());
			}
		};

		CubeManager::CubeManager() noexcept
			:  m_renderer(nullptr)
		{}

		CubeManager::CubeManager(unsigned int reserved, Renderer* renderer) noexcept
			: m_textureArray(10), m_renderer(renderer)
		{
			m_instanceArray.bind();
			m_vertexBuffer = VertexBuffer(//you could also create a local nameless array of vertices, where vertex is a struct with vec2 of float for position and vec2 of float for colour
				floatarr//floats
				{//positions          texture coords	 vertex normals
				    //back
					-1.0f, -1.0f, 1.0f,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f,//0
					1.0f, -1.0f, 1.0f,      0.0f, 0.0f,     0.0f, 0.0f, 1.0f,
					-1.0f, 1.0f, 1.0f,      1.0f, 1.0f,     0.0f, 0.0f, 1.0f,
					1.0f, 1.0f, 1.0f,		0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
					//top								
					-1.0f, 1.0f, 1.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f, //4
					1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
					-1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
					1.0f, 1.0f, -1.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
					//front							
					-1.0f, 1.0f, -1.0f,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f,//8
					1.0f, 1.0f, -1.0f,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f,
					-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
					1.0f, -1.0f, -1.0f,		1.0f, 0.0f,		0.0f, 0.0f, -1.0f,
					//bot								
					-1.0f, -1.0f, -1.0f,    0.0f, 1.0f,     0.0f, -1.0f, 0.0f,//12
					1.0f, -1.0f, -1.0f,     1.0f, 1.0f,     0.0f, -1.0f, 0.0f,
					-1.0f, -1.0f,  1.0f,    0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
					1.0f, -1.0f,  1.0f,     1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
					//right			    			    
					1.0f, -1.0f,  1.0f,     1.0f, 0.0f,     1.0f,  0.0f, 0.0f,//16
					1.0f, -1.0f, -1.0f,     0.0f, 0.0f,     1.0f,  0.0f, 0.0f,
					1.0f,  1.0f,  1.0f,     1.0f, 1.0f,     1.0f,  0.0f, 0.0f,
					1.0f,  1.0f, -1.0f,     0.0f, 1.0f,     1.0f, 0.0f, 0.0f,
					//left				    			    
					-1.0f, -1.0f, -1.0f,    1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,//20
					-1.0f, -1.0f, 1.0f,	    0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
					-1.0f, 1.0f, -1.0f,	    1.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
					-1.0f, 1.0f, 1.0f,	    0.0f, 1.0f,     -1.0f, 0.0f, 0.0f
				}, 8 * 4 * 6 * sizeof(float)
				);
			m_modelBuffer = VertexBuffer(nullptr, reserved * ( sizeof(int) + sizeof(maths::Mat4f) ), GL_STREAM_DRAW);
			m_indexBuffer = IndexBuffer<unsigned char>(uchararr {//unsigned chars
				0,1,2,		2,1,3,//back
				4,5,6,		6,5,7,//top
				8,9,10,		10,9,11,//front
				12,13,14,	14,13,15,//bot
				16,17,18,	18,17,19,//right
				20,21,22,	22,21,23//left
				}, 36//6 indices
				);
			m_vertexBuffer.bind();
			m_vertexBuffer.connectToVao<float>(3, false, 8 * sizeof(float));//3d position
			m_vertexBuffer.connectToVao<float>(2, false, 8 * sizeof(float));//2d texture coords
			m_vertexBuffer.connectToVao<float>(3, false, 8 * sizeof(float));//3d vertex normal
			VertexBuffer::vaoOffset = 0;
			m_modelBuffer.bind();
			m_modelBuffer.connectToVao<int>(1, false, ( sizeof(int) + sizeof(maths::Mat4f) ), 1);
			m_modelBuffer.connectToVao<float>(4, false, ( sizeof(int) + sizeof(maths::Mat4f) ), 1);//4 vec4s modelmatrices
			m_modelBuffer.connectToVao<float>(4, false, ( sizeof(int) + sizeof(maths::Mat4f) ), 1);
			m_modelBuffer.connectToVao<float>(4, false, ( sizeof(int) + sizeof(maths::Mat4f) ), 1);
			m_modelBuffer.connectToVao<float>(4, false, ( sizeof(int) + sizeof(maths::Mat4f) ), 1);
			VertexBuffer::vaoOffset = 0;
			VertexBuffer::VaoPos = 0;
			m_normalArray.bind();
			m_vertexBuffer.bind();
			m_indexBuffer.bind();
			m_vertexBuffer.connectToVao<float>(3, false, 8 * sizeof(float));//3d position
			m_vertexBuffer.connectToVao<float>(2, false, 8 * sizeof(float));//2d texture coords
			m_vertexBuffer.connectToVao<float>(3, false, 8 * sizeof(float));//3d vertex normal
			m_normalArray.unbind();
			m_copyBuffer = CopyBuffer(nullptr, reserved * ( sizeof(int) + sizeof(maths::Mat4f) ), GL_STREAM_DRAW);
			m_instanceCubes.reserve(reserved);
			m_normalCubes.reserve(reserved);
			m_transparentCubes.reserve(reserved);
			m_transparentTextures.reserve(10);
			m_normalTextures.reserve(10);
		}

		CubeManager::~CubeManager() noexcept
		{}

		CubeManager::CubeManager(CubeManager&& other) noexcept
			: m_instanceArray(std::move(other.m_instanceArray)), m_normalArray(std::move(other.m_normalArray)), m_indexBuffer(std::move(other.m_indexBuffer)), m_vertexBuffer(std::move(other.m_vertexBuffer)), m_modelBuffer(std::move(other.m_modelBuffer)),
			m_copyBuffer(std::move(other.m_copyBuffer)), m_textureArray(std::move(other.m_textureArray)), m_normalTextures(std::move(other.m_normalTextures)), m_transparentTextures(std::move(other.m_transparentTextures)), m_instanceCubes(std::move(other.m_instanceCubes)),
			m_normalCubes(std::move(other.m_normalCubes)), m_transparentCubes(std::move(other.m_transparentCubes)), m_renderer(other.m_renderer)
		{
			for ( auto& cube : m_instanceCubes )
			{
				cube->m_manager = this;
			}
			for ( auto& cube : m_normalCubes )
			{
				cube->m_manager = this;
			}
			for ( auto& cube : m_transparentCubes )
			{
				cube->m_manager = this;
			}
			other.m_renderer = nullptr;
		}

		CubeManager& CubeManager::operator=(CubeManager&& other) noexcept
		{
			m_instanceArray = std::move(other.m_instanceArray);//muss bei allen die pointer verschieben(auch bei den neuen) | also aus allen listen, etc 
			m_normalArray = std::move(other.m_normalArray);
			m_vertexBuffer = std::move(other.m_vertexBuffer);
			m_modelBuffer = std::move(other.m_modelBuffer);
			m_copyBuffer = std::move(other.m_copyBuffer);
			m_indexBuffer = std::move(other.m_indexBuffer);
			m_textureArray = std::move(other.m_textureArray);
			m_normalTextures = std::move(other.m_normalTextures);
			m_transparentTextures = std::move(other.m_transparentTextures);
			m_instanceCubes = std::move(other.m_instanceCubes);
			m_normalCubes = std::move(other.m_normalCubes);
			m_transparentCubes = std::move(other.m_transparentCubes);
			m_renderer = other.m_renderer;
			for ( auto& cube : m_instanceCubes )
			{
				cube->m_manager = this;
			}
			for ( auto& cube : m_normalCubes )
			{
				cube->m_manager = this;
			}
			for ( auto& cube : m_transparentCubes )
			{
				cube->m_manager = this;
			}
			other.m_renderer = nullptr;
			return *this;
		}

		int CubeManager::getNormalTextureId(const utils::Image& image) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( image.getData() == nullptr )
				std::cout << "Error CubeManager::getNormalTextureId(): Image has no data" << std::endl;
#endif
			for ( unsigned int i = 0; i < m_normalTextures.size(); ++i )
			{
				if ( m_normalTextures.at(i).getImage().getFilepath() == image.getFilepath() )
					return i;
			}
			m_normalTextures.push_back(Texture2D(image));
			return m_normalTextures.size() - 1;
		}

		int CubeManager::getNormalTextureId(const std::string& imagePath) noexcept
		{
			for ( unsigned int i = 0; i < m_normalTextures.size(); ++i )
			{
				if ( m_normalTextures.at(i).getImage().getFilepath() == imagePath )
					return i;
			}
			utils::Image image(imagePath);
			image.load();
#if CLOCKWORK_DEBUG
			if ( image.getData() == nullptr )
				std::cout << "Error CubeManager::getNormalTextureId(): Image has no data" << std::endl;
#endif
			m_normalTextures.push_back(Texture2D(image));
			return m_normalTextures.size() - 1;
		}

		int CubeManager::getTransparentTextureId(const utils::Image& image) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( image.getData() == nullptr )
				std::cout << "Error CubeManager::getNormalTextureId(): Image has no data" << std::endl;
#endif
			for ( unsigned int i = 0; i < m_transparentTextures.size(); ++i )
			{
				if ( m_transparentTextures.at(i).getImage().getFilepath() == image.getFilepath() )
					return i;
			}
			m_transparentTextures.push_back(Texture2D(image));
			return m_transparentTextures.size() - 1;
		}

		int CubeManager::getTransparentTextureId(const std::string& imagePath) noexcept
		{
			for ( unsigned int i = 0; i < m_transparentTextures.size(); ++i )
			{
				if ( m_transparentTextures.at(i).getImage().getFilepath() == imagePath )
					return i;
			}
			utils::Image image(imagePath);
			image.load();
#if CLOCKWORK_DEBUG
			if ( image.getData() == nullptr )
				std::cout << "Error CubeManager::getNormalTextureId(): Image has no data" << std::endl;
#endif
			m_transparentTextures.push_back(Texture2D(image));
			return m_transparentTextures.size() - 1;
		}

		void CubeManager::renderInstancedCubes() noexcept
		{
			m_textureArray.bind();
			m_copyBuffer.bind();
			m_modelBuffer.bind();
			for ( auto cube : m_instanceCubes )
			{
				cube->updateBufferData();
			}
			m_modelBuffer.copy(m_copyBuffer);
			m_instanceArray.bind();
			m_indexBuffer.drawInstanced(m_instanceCubes.size());
		}

		void CubeManager::renderNormalCubes() noexcept
		{
			m_normalArray.bind();
			for ( auto cube : m_normalCubes )
			{
				if ( cube->m_visible )
				{
					m_normalTextures.at(cube->m_textureId).bind();
					cube->render();
					m_indexBuffer.draw();
				}
			}
		}

		void CubeManager::renderTransparentCubes() noexcept
		{
			m_normalArray.bind();
			std::sort(m_transparentCubes.begin(), m_transparentCubes.end(), TransparentCubeCompare { this });
			for ( unsigned int i = 0; i < m_transparentCubes.size(); ++i )
			{
				NormalCube* cube = m_transparentCubes.at(i);
				if ( cube->m_pos != i )
					cube->m_pos = i;
				if ( cube->m_visible )
				{
					m_transparentTextures.at(cube->m_textureId).bind();
					cube->render();

					maths::Vec3f distToCamera = ( *m_renderer->m_currentCamera )->getPosition() - cube->m_gameObject->getPosition();

					if ( distToCamera.x > 0 )//camera is on the right side of the cube 
						m_indexBuffer.drawParts(30, 6);//left
					else//camera is on the left side of the cube
						m_indexBuffer.drawParts(24, 6);//right

					if ( distToCamera.y > 0 )//camera is on the top side of the cube 
						m_indexBuffer.drawParts(18, 6);//bot
					else//camera is on the bot side of the cube
						m_indexBuffer.drawParts(6, 6);//top

					if ( distToCamera.z > 0 )//camera is on the front side of the cube 
						m_indexBuffer.drawParts(12, 6);//back
					else//camera is on the back side of the cube
						m_indexBuffer.drawParts(0, 6);//front

					if ( maths::abs(distToCamera.x) < maths::abs(distToCamera.y) )
					{
						if ( maths::abs(distToCamera.x) < maths::abs(distToCamera.z) )
						{
							if ( distToCamera.x > 0 )//camera is on the right side of the cube 
								m_indexBuffer.drawParts(24, 6);//right
							else//camera is on the left side of the cube
								m_indexBuffer.drawParts(30, 6);//left

							if ( maths::abs(distToCamera.y) < maths::abs(distToCamera.z) )
							{
								if ( distToCamera.y > 0 )//camera is on the top side of the cube 
									m_indexBuffer.drawParts(6, 6);//top
								else//camera is on the bot side of the cube
									m_indexBuffer.drawParts(18, 6);//bot
								if ( distToCamera.z > 0 )//camera is on the front side of the cube 
									m_indexBuffer.drawParts(0, 6);//front
								else//camera is on the back side of the cube
									m_indexBuffer.drawParts(12, 6);//back
							}
							else
							{
								if ( distToCamera.z > 0 )//camera is on the front side of the cube 
									m_indexBuffer.drawParts(0, 6);//front
								else//camera is on the back side of the cube
									m_indexBuffer.drawParts(12, 6);//back
								if ( distToCamera.y > 0 )//camera is on the top side of the cube 
									m_indexBuffer.drawParts(6, 6);//top
								else//camera is on the bot side of the cube
									m_indexBuffer.drawParts(18, 6);//bot
							}
						}
						else
						{
							if ( distToCamera.z > 0 )//camera is on the front side of the cube 
								m_indexBuffer.drawParts(0, 6);//front
							else//camera is on the back side of the cube
								m_indexBuffer.drawParts(12, 6);//back
							if ( distToCamera.y > 0 )//camera is on the top side of the cube 
								m_indexBuffer.drawParts(6, 6);//top
							else//camera is on the bot side of the cube
								m_indexBuffer.drawParts(18, 6);//bot
							if ( distToCamera.x > 0 )//camera is on the right side of the cube 
								m_indexBuffer.drawParts(24, 6);//right
							else//camera is on the left side of the cube
								m_indexBuffer.drawParts(30, 6);//left
						}
					}
					else
					{
						if ( maths::abs(distToCamera.y) < maths::abs(distToCamera.z) )
						{
							if ( distToCamera.y > 0 )//camera is on the top side of the cube 
								m_indexBuffer.drawParts(6, 6);//top
							else//camera is on the bot side of the cube
								m_indexBuffer.drawParts(18, 6);//bot

							if ( maths::abs(distToCamera.x) < maths::abs(distToCamera.z) )
							{
								if ( distToCamera.x > 0 )//camera is on the right side of the cube 
									m_indexBuffer.drawParts(24, 6);//right
								else//camera is on the left side of the cube
									m_indexBuffer.drawParts(30, 6);//left
								if ( distToCamera.z > 0 )//camera is on the front side of the cube 
									m_indexBuffer.drawParts(0, 6);//front
								else//camera is on the back side of the cube
									m_indexBuffer.drawParts(12, 6);//back
							}
							else
							{
								if ( distToCamera.z > 0 )//camera is on the front side of the cube 
									m_indexBuffer.drawParts(0, 6);//front
								else//camera is on the back side of the cube
									m_indexBuffer.drawParts(12, 6);//back
								if ( distToCamera.x > 0 )//camera is on the right side of the cube 
									m_indexBuffer.drawParts(24, 6);//right
								else//camera is on the left side of the cube
									m_indexBuffer.drawParts(30, 6);//left
							}
						}
						else
						{
							if ( distToCamera.z > 0 )//camera is on the front side of the cube 
								m_indexBuffer.drawParts(0, 6);//front
							else//camera is on the back side of the cube
								m_indexBuffer.drawParts(12, 6);//back
							if ( distToCamera.x > 0 )//camera is on the right side of the cube 
								m_indexBuffer.drawParts(24, 6);//right
							else//camera is on the left side of the cube
								m_indexBuffer.drawParts(30, 6);//left
							if ( distToCamera.y > 0 )//camera is on the top side of the cube 
								m_indexBuffer.drawParts(6, 6);//top
							else//camera is on the bot side of the cube
								m_indexBuffer.drawParts(18, 6);//bot
						}
					}
				}
			}
		}

		void CubeManager::removeInstancedCubesAt(int pos) noexcept
		{
			m_instanceCubes.back()->m_pos = pos;
			m_instanceCubes.back()->m_changed = true;
			m_instanceCubes.at(pos)->m_pos = -1;
			m_instanceCubes.at(pos) = m_instanceCubes.back();
			m_instanceCubes.erase(m_instanceCubes.end() - 1);
		}

		void CubeManager::removeLastInstancedCube() noexcept
		{
			m_instanceCubes.back()->m_pos = -1;
			m_instanceCubes.erase(m_instanceCubes.end() - 1);
		}

		void CubeManager::removeNormalCubesAt(int pos) noexcept
		{
			m_normalCubes.at(pos)->m_pos = -1;
			m_normalCubes.erase(m_normalCubes.begin() + pos);
		}

		void CubeManager::removeLastNormalCube() noexcept
		{
			m_normalCubes.back()->m_pos = -1;
			m_normalCubes.erase(m_normalCubes.end() - 1);
		}

		void CubeManager::removeTransparentCubesAt(int pos) noexcept
		{
			m_transparentCubes.at(pos)->m_pos = -1;
			m_transparentCubes.erase(m_transparentCubes.begin() + pos);
		}

		void CubeManager::removeLastTransparentCube() noexcept
		{
			m_transparentCubes.back()->m_pos = -1;
			m_transparentCubes.erase(m_transparentCubes.end() - 1);
		}

		void CubeManager::addInstancedTexture(const utils::Image& image) noexcept
		{
			m_textureArray.addTexture(image);
		}

		void CubeManager::addInstancedTexture(const std::string& imagePath) noexcept
		{
			m_textureArray.addTexture(imagePath);
		}

		void CubeManager::addNormalTexture(const utils::Image& image) noexcept
		{
#if CLOCKWORK_DEBUG
			if ( image.getData() == nullptr )
				std::cout << "Error CubeManager::addNormalTexture(): Image has no data" << std::endl;
#endif
#if CLOCKWORK_DEBUG
			if ( image.hasAlpha() )
			{
				for ( unsigned int i = 0; i < m_transparentTextures.size(); ++i )
				{
					if ( m_transparentTextures.at(i).getImage().getFilepath() == image.getFilepath() )
					{
						std::cout << "Error TextureArray2D::addTexture(): an image with the same imagepath already is in the texture list" << std::endl;
						return;
					}
				}
			}
			else
			{
				for ( unsigned int i = 0; i < m_normalTextures.size(); ++i )
				{
					if ( m_normalTextures.at(i).getImage().getFilepath() == image.getFilepath() )
					{
						std::cout << "Error TextureArray2D::addTexture(): an image with the same imagepath already is in the texture list" << std::endl;
						return;
					}
				}
			}
#endif 
			if(image.hasAlpha() )
				m_transparentTextures.push_back(Texture2D(image));
			else
				m_normalTextures.push_back(Texture2D(image));
		}

		void CubeManager::addNormalTexture(const std::string& imagePath) noexcept
		{
#if CLOCKWORK_DEBUG
			for ( unsigned int i = 0; i < m_normalTextures.size(); ++i )
			{
				if ( m_normalTextures.at(i).getImage().getFilepath() == imagePath )
				{
					std::cout << "Error TextureArray2D::addTexture(): an image with the same imagepath already is in the texture list" << std::endl;
					return;
				}
			}
			for ( unsigned int i = 0; i < m_transparentTextures.size(); ++i )
			{
				if ( m_transparentTextures.at(i).getImage().getFilepath() == imagePath )
				{
					std::cout << "Error TextureArray2D::addTexture(): an image with the same imagepath already is in the texture list" << std::endl;
					return;
				}
			}
#endif 
			utils::Image image(imagePath);
			image.load();
#if CLOCKWORK_DEBUG
			if ( image.getData() == nullptr )
				std::cout << "Error CubeManager::addNormalTexture(): Image has no data" << std::endl;
#endif
			if ( image.hasAlpha() )
				m_transparentTextures.push_back(Texture2D(image));
			else
				m_normalTextures.push_back(Texture2D(image));
		}

		void CubeManager::addTextureBoth(const utils::Image& image) noexcept
		{
			addInstancedTexture(image);
			addNormalTexture(image);
		}

		void CubeManager::addTextureBoth(const std::string& imagePath) noexcept
		{
			addInstancedTexture(imagePath);
			addNormalTexture(imagePath);
		}

		void CubeManager::removeInstancedTexture(int textureId) noexcept
		{
			m_copyBuffer.bind();
			m_textureArray.removeTexture(textureId);
			for ( unsigned int i = 0; i < m_instanceCubes.size(); ++i )
			{
				if ( m_instanceCubes.at(i)->m_textureId == textureId )
				{
					m_instanceCubes.at(i)->m_textureId = 0;
					m_instanceCubes.at(i)->m_changed = true;
				}
				else if ( m_instanceCubes.at(i)->m_textureId > textureId )
				{
					--m_instanceCubes.at(i)->m_textureId;
					m_instanceCubes.at(i)->m_changed = true;
				}
			}
		}

		void CubeManager::removeInstancedTexture(const utils::Image& image) noexcept
		{
			removeInstancedTexture(m_textureArray.getTextureId(image));
		}

		void CubeManager::removeInstancedTexture(const std::string& imagePath) noexcept
		{
			removeInstancedTexture(m_textureArray.getTextureId(imagePath));
		}

		void CubeManager::removeNormalTexture(int textureId, bool transparent) noexcept
		{
			if ( transparent )
			{
#if CLOCKWORK_DEBUG
				if ( m_transparentTextures.size() <= textureId )
					std::cout << "Error CubeManager::removeNormalTexture(): TextureId is not in the texture list" << std::endl;
#endif
				m_transparentTextures.erase(m_transparentTextures.begin() + textureId);
				for ( unsigned int i = 0; i < m_transparentCubes.size(); ++i )
				{
					if ( m_transparentCubes.at(i)->m_textureId == textureId )
					{
						m_transparentCubes.at(i)->m_textureId = 0;
					}
					else if ( m_transparentCubes.at(i)->m_textureId > textureId )
					{
						--m_transparentCubes.at(i)->m_textureId;
					}
				}
			}
			else
			{
#if CLOCKWORK_DEBUG
				if ( m_normalTextures.size() <= textureId )
					std::cout << "Error CubeManager::removeNormalTexture(): TextureId is not in the texture list" << std::endl;
#endif
				m_normalTextures.erase(m_normalTextures.begin() + textureId);
				for ( unsigned int i = 0; i < m_normalCubes.size(); ++i )
				{
					if ( m_normalCubes.at(i)->m_textureId == textureId )
					{
						m_normalCubes.at(i)->m_textureId = 0;
					}
					else if ( m_instanceCubes.at(i)->m_textureId > textureId )
					{
						--m_normalCubes.at(i)->m_textureId;
					}
				}
			}
		}

		void CubeManager::removeNormalTexture(const utils::Image& image) noexcept
		{
			for ( unsigned int i = 0; i < m_normalTextures.size(); ++i )
			{
				if ( m_normalTextures.at(i).getImage().getFilepath() == image.getFilepath() )
				{
					removeNormalTexture(i, false);
					break;
				}
			}
			for ( unsigned int i = 0; i < m_transparentTextures.size(); ++i )
			{
				if ( m_transparentTextures.at(i).getImage().getFilepath() == image.getFilepath() )
				{
					removeNormalTexture(i, true);
					break;
				}
			}
		}

		void CubeManager::removeNormalTexture(const std::string& imagePath) noexcept
		{
			for ( unsigned int i = 0; i < m_normalTextures.size(); ++i )
			{
				if ( m_normalTextures.at(i).getImage().getFilepath() == imagePath )
				{
					removeNormalTexture(i, false);
					break;
				}
			}
			for ( unsigned int i = 0; i < m_transparentTextures.size(); ++i )
			{
				if ( m_transparentTextures.at(i).getImage().getFilepath() == imagePath )
				{
					removeNormalTexture(i, true);
					break;
				}
			}
		}

		bool CubeManager::containsInstancedTexture(const utils::Image& image) noexcept
		{
			return m_textureArray.contains(image);
		}

		bool CubeManager::containsInstancedTexture(const std::string& imagePath) noexcept
		{
			return m_textureArray.contains(imagePath);
		}

		bool CubeManager::containsNormalTexture(const utils::Image& image) noexcept
		{
			for ( unsigned int i = 0; i < m_normalTextures.size(); ++i )
			{
				if ( m_normalTextures.at(i).getImage().getFilepath() == image.getFilepath() )
					return true;
			}
			return false;
		}

		bool CubeManager::containsNormalTexture(const std::string& imagePath) noexcept
		{
			for ( unsigned int i = 0; i < m_normalTextures.size(); ++i )
			{
				if ( m_normalTextures.at(i).getImage().getFilepath() == imagePath )
					return true;
			}
			return false;
		}

		bool CubeManager::containsTransparentTexture(const utils::Image& image) noexcept
		{
			for ( unsigned int i = 0; i < m_transparentTextures.size(); ++i )
			{
				if ( m_transparentTextures.at(i).getImage().getFilepath() == image.getFilepath() )
					return true;
			}
			return false;
		}

		bool CubeManager::containsTransparentTexture(const std::string& imagePath) noexcept
		{
			for ( unsigned int i = 0; i < m_transparentTextures.size(); ++i )
			{
				if ( m_transparentTextures.at(i).getImage().getFilepath() == imagePath )
					return true;
			}
			return false;
		}

		const Renderer* const CubeManager::getRenderer() const noexcept
		{
			return m_renderer;
		}

	}
}