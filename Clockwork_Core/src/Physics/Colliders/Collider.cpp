#include "Collider.h"
#include "src\Logics\Entities\GameObject.h"

namespace clockwork {
	namespace physics {

		Collider::Collider(logics::GameObject* gameObject) noexcept
			: m_gameObject(gameObject)
		{

		}

	}
}