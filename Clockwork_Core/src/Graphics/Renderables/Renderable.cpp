#include "Renderable.h"
#include "src\Logics\Entities\GameObject.h"

namespace clockwork {
	namespace graphics {

		Renderable::Renderable(int textureId, logics::GameObject* gameObject) noexcept
			: m_textureId(textureId), m_gameObject(gameObject)
		{}
		Renderable::~Renderable() noexcept
		{}
		Renderable::Renderable(Renderable&& other) noexcept
			: m_textureId(other.m_textureId), m_gameObject(other.m_gameObject)
		{}
		Renderable& Renderable::operator=(Renderable&& other) noexcept
		{
			m_textureId = other.m_textureId;
			m_gameObject = other.m_gameObject;
			return *this;
		}
		const logics::GameObject& Renderable::getGameObject() const noexcept
		{
			return *m_gameObject;
		}

		logics::GameObject& Renderable::getGameObject() noexcept
		{
			return *m_gameObject;
		}
		void Renderable::setGameObject(logics::GameObject* gameObject) noexcept
		{
			m_gameObject = gameObject;
		}

	}
}
