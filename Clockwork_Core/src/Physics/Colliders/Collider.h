#pragma once

namespace clockwork {
	namespace logics {
		class GameObject;
	}
	namespace physics {

		class Collider//wahrscheinlich mit virtueller vererbung machen und dann in cube/spehere vertex positions in relation zu 0 speichern für collisionbox position in relation zum model
		{

		protected:
			logics::GameObject* m_gameObject;

		public:
			Collider(logics::GameObject* gameObject) noexcept;
			virtual bool collides(const Collider* other) const noexcept = 0;
			logics::GameObject* const getGameObject() const noexcept {return m_gameObject;}
		};

	}
}