#pragma once
#include "src\Graphics\Renderables\Renderable.h"

namespace clockwork {
	namespace logics {
		class GameObject;
	}
	namespace graphics {

		class Renderer;
		class CubeManager;
		class Shader;

		class NormalCube
			: public Renderable
		{

		protected:
			friend class CubeManager;
			friend class Renderer;
			friend class TransparentCubeCompare;
			int m_pos;
			bool m_visible;
			bool m_transparent;
			CubeManager* m_manager;

		public:

			NormalCube(int textureId, bool transparent, logics::GameObject* gameObject, Renderer* renderer) noexcept;

			NormalCube(const std::string& imagePath, logics::GameObject* gameObject, Renderer* renderer) noexcept;

			NormalCube(const utils::Image& image, logics::GameObject* gameObject, Renderer* renderer) noexcept;

			virtual ~NormalCube() noexcept;

			NormalCube(const NormalCube& other) = delete;

			NormalCube(NormalCube&& other) noexcept;

			NormalCube& operator=(const NormalCube& other) = delete;

			NormalCube& operator=(NormalCube&& other) noexcept;

		public:
			//kann durch virtual erben überschrieben werden | ggf shader anders bearbeiten vor dem rendern
			virtual void render() noexcept;

			//wie bei instancedcube kommentieren | es wird intern überprüft, ob cube schon removed/added ist
			void remove() noexcept;

			void add() noexcept;

			//bleibt im gleichen cubemanager, wenn als bool transparent einfach istransparent getter mitgegeben wird 
			void setTexture(int textureId, bool transparent) noexcept;

			//kann auch zu transparentcubemanager wechseln
			void setTexture(const utils::Image& image) noexcept;

			void setTexture(const std::string& imagePath) noexcept;

			//hier gibt setvisible schon guten performance boost
			void setVisible(bool visible) noexcept;

			/*returns the image of the texture in the texture list at the textureid with size, imagepath, etc | CAREFUL: the image has no imagedata, because it has been cleared*/
			const utils::Image& getTextureImage() noexcept;

			void changeRenderer(Renderer* renderer) noexcept;

			const Renderer* const getRenderer() const noexcept;

		public:
			inline const bool isAdded() const noexcept {return m_pos!=-1;}
			inline const bool isVisible() const noexcept { return m_visible;}
			inline const bool isTransparent() const noexcept {return m_transparent;}

		};

	}
}
