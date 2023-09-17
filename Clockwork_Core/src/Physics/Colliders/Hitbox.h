#pragma once
#include <vector>
#include "src\Maths\Vec3.h"

namespace clockwork {
	namespace logics {
		class GameObject;
	}
	namespace physics {

		class Collider;

		class Hitbox//wichtig dazu kommentieren hitbox hat automatisch eine art spherecollider um den 0 punkt(0,0,0) mit verschiebung einberechnet und größter size als radius für erste collision abfragen | hitbox sollte wahrscheinlich aber weitere collider haben
		{
			
		private:
			logics::GameObject* m_gameObject;
			std::vector<Collider*> m_colliders;
			float m_radius;

		private:
			float getRadius(Collider* collider) noexcept;

		public:
			Hitbox(logics::GameObject* gameObject) noexcept;




			void addCollider(Collider* collider) noexcept;
			void removeCollider(Collider* collider) noexcept;
			void removeCollider(unsigned int position) noexcept;
			void removeLastCollider() noexcept;


			bool fastCollides(const Hitbox& other, const maths::Vec3f& mypos, const maths::Vec3f& otherpos) const noexcept;
			//vergleicht die liste von collidern mit den collidern vom anderen objekt und speichert dann die positionen an der memoryadresse vom positions pointer
			//am besten dann in chunksystem collision durchgehen in for schleife, vorher aber collisioninfo objekt abspeichern, dann die methode hier immer aufrufen und bei true das collisioninfo objekt an listener weiterleiten
			bool slowCollides(const Hitbox& other, int* ownColliderNumber, int* otherColliderNumber) const noexcept;

		};

	}
}