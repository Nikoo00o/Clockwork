#include <algorithm>
#include <iostream>
#include "Hitbox.h"
#include "Collider.h"
#include "src\Logics\Entities\Listener\MovingTickListener.h"
#include "src\Logics\Entities\Listener\StaticTickListener.h"
#include "CubeCollider.h"
#include "SphereCollider.h"

namespace clockwork {
	namespace physics {

		Hitbox::Hitbox(logics::GameObject* gameObject) noexcept
			: m_radius(0), m_gameObject(gameObject)
		{}

		float Hitbox::getRadius(Collider* collider) noexcept
		{			//wichtig auch noch für andere collider  machen!!
			CubeCollider* cube = dynamic_cast<CubeCollider*>( collider );
			if (cube!=nullptr)
			{
				float first = cube->m_frontBotLeft.slowLenght();
				float second = cube->m_backTopRight.slowLenght();
				if ( first > second )
					return first;
				else
					return second;
			}

			SphereCollider* sphere = dynamic_cast<SphereCollider*>( collider );
			if ( sphere != nullptr )
			{
				return sphere->m_position.slowLenght() + sphere->m_radius;
			}

		}

		void Hitbox::addCollider(Collider* collider) noexcept
		{
			m_colliders.push_back(collider);
			float newRadius = getRadius(collider);
			if ( newRadius > m_radius )
				m_radius = newRadius;
		}

		void Hitbox::removeCollider(Collider* collider) noexcept
		{
			auto iterator = std::find(m_colliders.begin(), m_colliders.end(), collider);
#if CLOCKWORK_DEBUG
			if ( iterator == m_colliders.end() )
				std::cout << "Error Chunk::removeCollider(): The collider pointer is not in the colliderlist" << std::endl;
#endif
			float oldRadius = getRadius(*iterator);
			m_colliders.erase(iterator);
			if ( oldRadius == m_radius )
			{
				m_radius = 0;
				for ( unsigned int i = 0; i < m_colliders.size(); ++i )
				{
					float newRadius = getRadius(m_colliders.at(i));
					if ( newRadius > m_radius )
					{
						m_radius = newRadius;
					}
				}
			}
		}

		void Hitbox::removeCollider(unsigned int position) noexcept
		{
			float oldRadius = getRadius(m_colliders.at(position));
			m_colliders.erase(m_colliders.begin() + position);
			if ( oldRadius == m_radius )
			{
				m_radius = 0;
				for ( unsigned int i = 0; i < m_colliders.size(); ++i )
				{
					float newRadius = getRadius(m_colliders.at(i));
					if ( newRadius > m_radius )
					{
						m_radius = newRadius;
					}
				}
			}
		}

		void Hitbox::removeLastCollider() noexcept
		{
			float oldRadius = getRadius(m_colliders.back());
			m_colliders.erase(m_colliders.end() - 1);
			if ( oldRadius == m_radius )
			{
				m_radius = 0;
				for ( unsigned int i = 0; i < m_colliders.size(); ++i )
				{
					float newRadius = getRadius(m_colliders.at(i));
					if ( newRadius > m_radius )
					{
						m_radius = newRadius;
					}
				}
			}
		}

		bool Hitbox::fastCollides(const Hitbox& other, const maths::Vec3f& mypos, const maths::Vec3f& otherpos) const noexcept
		{
			const maths::Vec3f& ownSize = m_gameObject->getSize();
			const maths::Vec3f& otherSize = other.m_gameObject->getSize();
			float myRadius = m_radius * maths::max(maths::max(ownSize.x, ownSize.y), ownSize.z);
			float otherRadius = other.m_radius * maths::max(maths::max(otherSize.x, otherSize.y), otherSize.z);
			if ( mypos.fastDistance(otherpos) > maths::square(myRadius + otherRadius) )
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		bool Hitbox::slowCollides(const Hitbox& other, int* ownColliderNumber, int* otherColliderNumber) const noexcept
		{
			for ( unsigned int me = 0; me < m_colliders.size(); ++me )
			{
				for ( unsigned int ot = 0; ot < other.m_colliders.size(); ++ot )
				{
					if ( m_colliders[me]->collides(other.m_colliders[ot]) )///TREAD_SAFE: wahrscheinlich auch wenn es von gleicher klasse ist nicht über member zugreifen, sondern auf das element des vektors mit einem getter mit mutex zugreifen, da das andere objekt auch gerade verändert werden könnte
					{
						*ownColliderNumber = me;
						*otherColliderNumber = ot;
						return true;
					}
				}
			}
			return false;
		}

	}
}