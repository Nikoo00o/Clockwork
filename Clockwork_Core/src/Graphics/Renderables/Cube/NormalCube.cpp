#include "CubeManager.h"
#include "NormalCube.h"
#include "src\Graphics\Renderer\Renderer.h"
#include "src\Logics\Entities\GameObject.h"

namespace clockwork {
	namespace graphics {

		NormalCube::NormalCube(int textureId, bool transparent, logics::GameObject* gameObject, Renderer* renderer) noexcept
			: Renderable(textureId, gameObject), m_visible(true), m_transparent(transparent), m_pos(-1), m_manager(&renderer->cubeManager)
		{
#if CLOCKWORK_DEBUG
			if ( m_transparent )
			{
				if ( m_manager->m_transparentTextures.size() <= textureId )
					std::cout << "Error NormalCube::NormalCube(): TextureId is not in the transparent texture list of the cubemanager" << std::endl;
			}
			else
			{
				if ( m_manager->m_normalTextures.size() <= textureId )
					std::cout << "Error NormalCube::NormalCube(): TextureId is not in the texture list of the cubemanager" << std::endl;
			}
#endif
		}

		NormalCube::NormalCube(const std::string& imagePath, logics::GameObject* gameObject, Renderer* renderer) noexcept
			: Renderable(0, gameObject), m_visible(true), m_pos(-1), m_manager(&renderer->cubeManager)
		{
			if ( m_manager->containsNormalTexture(imagePath) )
			{
				m_textureId = m_manager->getNormalTextureId(imagePath);
				m_transparent = false;
			}
			else if ( m_manager->containsTransparentTexture(imagePath) )
			{
				m_textureId = m_manager->getTransparentTextureId(imagePath);
				m_transparent = true;
			}
			else
			{
				utils::Image image(imagePath);
				image.load();
				if ( image.hasAlpha() )
				{
					m_textureId = m_manager->getTransparentTextureId(image);
					m_transparent = true;
				}
				else
				{
					m_textureId = m_manager->getNormalTextureId(image);
					m_transparent = false;
				}
			}
		}

		NormalCube::NormalCube(const utils::Image& image, logics::GameObject* gameObject, Renderer* renderer) noexcept
			: Renderable(0, gameObject), m_visible(true), m_pos(-1), m_manager(&renderer->cubeManager)
		{
			if ( image.hasAlpha() )
			{
				m_textureId = m_manager->getTransparentTextureId(image);
				m_transparent = true;
			}
			else
			{
				m_textureId = m_manager->getNormalTextureId(image);
				m_transparent = false;
			}
		}

		NormalCube::~NormalCube() noexcept
		{
			this->remove();
		}

		NormalCube::NormalCube(NormalCube&& other) noexcept
			: Renderable(std::move(other)), m_visible(other.m_visible), m_transparent(other.m_transparent), m_pos(other.m_pos), m_manager(other.m_manager)
		{
			other.m_pos = -1;
			other.m_manager = nullptr;
			if ( m_pos != -1 )
			{
				if ( m_transparent )
					m_manager->m_transparentCubes.at(m_pos) = this;
				else
					m_manager->m_normalCubes.at(m_pos) = this;
			}
		}

		NormalCube& NormalCube::operator=(NormalCube&& other) noexcept
		{
			this->remove();
			m_visible = other.m_visible;
			m_transparent = other.m_transparent;
			m_pos = other.m_pos;
			m_manager = other.m_manager;
			Renderable::operator=(std::move(other));
			other.m_pos = -1;
			other.m_manager = nullptr;
			if ( m_pos != -1 )
			{
				if(m_transparent )
					m_manager->m_transparentCubes.at(m_pos) = this;
				else
					m_manager->m_normalCubes.at(m_pos) = this;
			}
			return *this;
		}

		void NormalCube::render() noexcept
		{
			Shader* shader = m_manager->m_renderer->normalShader;
			shader->setUniform("u_model",m_gameObject->getModelMatrix());
		}

		void NormalCube::remove() noexcept
		{
#if CLOCKWORK_DEBUG == 2
			if ( m_pos == -1 )
				std::cout << "Info NormalCube::remove(): NormalCube was already removed" << std::endl;
#endif
			if ( m_pos != -1 )
			{
				if ( m_transparent )
				{
					m_manager->m_transparentCubes.back()->m_pos = m_pos;
					m_manager->m_transparentCubes.at(m_pos) = m_manager->m_transparentCubes.back();
					m_pos = -1;
					m_manager->m_transparentCubes.erase(m_manager->m_transparentCubes.end() - 1);
				}
				else
				{
					m_manager->m_normalCubes.back()->m_pos = m_pos;
					m_manager->m_normalCubes.at(m_pos) = m_manager->m_normalCubes.back();
					m_pos = -1;
					m_manager->m_normalCubes.erase(m_manager->m_normalCubes.end() - 1);
				}
			}
		}

		void NormalCube::add() noexcept
		{
#if CLOCKWORK_DEBUG == 2
			if ( m_pos != -1 )
				std::cout << "Info NormalCube::add(): NormalCube was already added" << std::endl;
#endif
			if ( m_pos == -1 )
			{
				if ( m_transparent )
				{
					m_pos = m_manager->m_transparentCubes.size();
					m_manager->m_transparentCubes.push_back(this);
				}
				else
				{
					m_pos = m_manager->m_normalCubes.size();
					m_manager->m_normalCubes.push_back(this);
				}
			}
		}

		void NormalCube::setTexture(int textureId, bool transparent) noexcept
		{
			if ( transparent != m_transparent )
			{
				if ( m_pos != -1 )
				{
					remove();
					m_transparent = transparent;
					add();
				}
				else
					m_transparent = transparent;
			}
			m_textureId = textureId;
#if CLOCKWORK_DEBUG
			if ( m_transparent )
			{
				if ( m_manager->m_transparentTextures.size() <= textureId )
					std::cout << "Error NormalCube::setTexture(): TextureId is not in the texture list of the cubemanager" << std::endl;
			}
			else
			{
				if ( m_manager->m_normalTextures.size() <= textureId )
					std::cout << "Error NormalCube::setTexture(): TextureId is not in the texture list of the cubemanager" << std::endl;
			}
#endif
		}

		void NormalCube::setTexture(const utils::Image& image) noexcept
		{
			if ( image.hasAlpha() )
			{
				if ( !m_transparent )
				{
					if ( m_pos != -1 )
					{
						remove();
						m_transparent = true;
						add();
					}
					else
						m_transparent = true;
				}
				m_textureId = m_manager->getTransparentTextureId(image);
			}
			else
			{
				if ( m_transparent )
				{
					if ( m_pos != -1 )
					{
						remove();
						m_transparent = false;
						add();
					}
					else
						m_transparent = false;
				}
				m_textureId = m_manager->getNormalTextureId(image);
			}
		}

		void NormalCube::setTexture(const std::string& imagePath) noexcept
		{
			if ( m_manager->containsNormalTexture(imagePath) )
			{
				if ( m_transparent )
				{
					if ( m_pos != -1 )
					{
						remove();
						m_transparent = false;
						add();
					}
					else
						m_transparent = false;
				}
				m_textureId = m_manager->getNormalTextureId(imagePath);
			}
			else if ( m_manager->containsTransparentTexture(imagePath) )
			{
				if ( !m_transparent )
				{
					if ( m_pos != -1 )
					{
						remove();
						m_transparent = true;
						add();
					}
					else
						m_transparent = true;
				}
				m_textureId = m_manager->getTransparentTextureId(imagePath);
			}
			else
			{
				utils::Image image(imagePath);
				image.load();
				setTexture(image);
			}
		}

		void NormalCube::setVisible(bool visible) noexcept
		{
			m_visible = visible;
		}

		const utils::Image& NormalCube::getTextureImage() noexcept
		{
			if(m_transparent )
				return m_manager->m_transparentTextures.at(m_textureId).getImage();
			else
				return m_manager->m_normalTextures.at(m_textureId).getImage();

		}

		void NormalCube::changeRenderer(Renderer* renderer) noexcept
		{
			const utils::Image& image = getTextureImage();
			if ( m_pos != -1 )
			{
				remove();
				m_manager = &renderer->cubeManager;
				add();
			}
			else
			{
				m_manager = &renderer->cubeManager;
			}
			if ( m_transparent )
				m_textureId = m_manager->getTransparentTextureId(image);
			else
				m_textureId = m_manager->getNormalTextureId(image);
		}

		const Renderer* const NormalCube::getRenderer() const noexcept
		{
			return m_manager->m_renderer;
		}

	}
}


