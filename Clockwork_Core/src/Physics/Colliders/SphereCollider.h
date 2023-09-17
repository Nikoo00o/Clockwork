#pragma once
#include "Collider.h"
#include "src\Maths\Mat4x4.h"

namespace clockwork {
	namespace physics {

		class SphereCollider : public Collider//wichtig dazu kommentieren, bei spherecollider müssen alle size werte gleich skaliert sein, also (2,2,2), da es nur einen radius gibt und dies nicht in alle dimensionen anpassbar ist | sonst anderen collider nehmen
		{

		private:
			friend class Hitbox;

		protected:
			maths::Vec3f m_position;
			float m_radius;

		public:
			SphereCollider(logics::GameObject* gameObject, const maths::Vec3f& position = maths::Vec3f { 0,0,0 }, float radius = 1.5) noexcept;
			virtual bool collides(const Collider* other) const noexcept override;

		};

	}
}