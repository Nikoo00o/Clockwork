#pragma once
#include "src\Maths\Vec3.h"
#include "src\Maths\Mat4x4.h"
#include "src\Utils\Image.h"

namespace clockwork {
	namespace logics {
		class GameObject;
	}
	namespace graphics {

		class Renderable
		{

		protected:
			int m_textureId;///später wahrscheinlich materialid mit materialarray benutzen | dann auch materialarray, etc machen 
			logics::GameObject* m_gameObject;

		public:
			Renderable(int textureId, logics::GameObject* gameObject) noexcept;
			~Renderable() noexcept;
			Renderable(const Renderable& other) = delete;
			Renderable(Renderable&& other) noexcept;
			Renderable& operator=(const Renderable& other) = delete;
			Renderable& operator=(Renderable&& other) noexcept;

		public:
			const logics::GameObject& getGameObject() const noexcept;
			logics::GameObject& getGameObject() noexcept;
			void setGameObject(logics::GameObject* gameObject) noexcept;
			inline const int getTextureId() const noexcept{return m_textureId;}

		};

	}
}




