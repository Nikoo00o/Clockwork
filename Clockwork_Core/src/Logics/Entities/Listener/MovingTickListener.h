#pragma once
#include "src\Logics\Entities\GameObject.h"
#include "src\Physics\Colliders\Hitbox.h"

namespace clockwork {
	namespace logics {

		class Chunk;
		class StaticTickListener;

		class MovingTickListener//unterschied zu staticticklistener dazu schreiben | der hier verändert chunk, wenn er sich bewegt | mann soll immer nur entweder von moving, oder von static erben
			: public virtual GameObject
		{

		protected:
			float m_mass;
			maths::Vec3f m_velocity;
			physics::Hitbox m_hitbox;

		public:
			MovingTickListener() noexcept;
			~MovingTickListener() noexcept;

		public:
			virtual void fastTick() noexcept = 0;
			virtual void slowTick() noexcept = 0;
			//mit dynamic cast in unterklassen umcasten und dann testen mit != nullptr, ob das objekt von einer gegebenen klasse ist
			virtual void onCollision(MovingTickListener* otherMoving, int ownColliderNumber, int otherColliderNumber) noexcept = 0;
			virtual void onCollision(StaticTickListener* otherStatic, int ownColliderNumber, int otherColliderNumber) noexcept = 0;

			inline const physics::Hitbox& getHitbox() const {return m_hitbox;}//ggf auch noch nicht const getter, wenn benötigt
			inline const maths::Vec3f& getVelocity() const noexcept {return m_velocity;}
			inline maths::Vec3f& getVelocity() noexcept{return m_velocity;}
		};

	}
}

