#pragma once
#include "src\Logics\Entities\GameObject.h"
#include "src\Physics\Colliders\Hitbox.h"

namespace clockwork {
	namespace logics {

		class Chunk;
		class MovingTickListener;

		class StaticTickListener//unterschied zu staticticklistener dazu schreiben | der hier verändert chunk, wenn er sich bewegt | static listener darf auch nicht mehr position so verändert kriegen, dass er in nem anderen chunk ist
			: public virtual GameObject
		{

		protected:
			float m_mass;
			physics::Hitbox m_hitbox;

		public:
			StaticTickListener() noexcept;
			~StaticTickListener() noexcept;

		public:
			virtual void fastTick() noexcept = 0;
			virtual void slowTick() noexcept = 0;
			virtual void onCollision(MovingTickListener* otherMoving, int ownColliderNumber, int otherColliderNumber) noexcept = 0;

			inline const physics::Hitbox& getHitbox() const {return m_hitbox;}//ggf auch noch nicht const getter, wenn benötigt

		};

	}
}

