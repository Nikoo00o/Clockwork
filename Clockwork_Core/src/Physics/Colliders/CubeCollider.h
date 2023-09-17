#pragma once
#include "Collider.h"
#include "src\Maths\Mat4x4.h"

namespace clockwork {
	namespace physics {

		class CubeCollider : public Collider
		{

		private:
			friend class Hitbox;
		
		protected:
			maths::Vec3f m_frontBotLeft;
			maths::Vec3f m_backTopRight;//range of cube collision box(size compared to model)

		public:
			CubeCollider(logics::GameObject* gameObject, const maths::Vec3f& frontBotLeft = maths::Vec3f { -1,-1,-1 }, const maths::Vec3f& backTopRight = maths::Vec3f { 1,1,1 }) noexcept;
			virtual bool collides(const Collider* other) const noexcept override;

		};

	}
}