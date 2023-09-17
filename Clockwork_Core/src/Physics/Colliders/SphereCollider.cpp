#include "CubeCollider.h"
#include "SphereCollider.h"
#include "src\Logics\Entities\GameObject.h"
#include "src\Logics\Entities\Listener\MovingTickListener.h"
#include "src\Logics\Entities\Listener\StaticTickListener.h"
#include "src\Core\Engine.h"
namespace clockwork {
	namespace physics {

		SphereCollider::SphereCollider(logics::GameObject* gameObject, const maths::Vec3f& position, float radius) noexcept
			: Collider(gameObject), m_position(position), m_radius(radius)
		{

		}

		bool SphereCollider::collides(const Collider* other) const noexcept//collides wird immer von movingticklistener mit entweder movingticklistener, oder staticticklistener aufgerufen
		{
			double time = engine->getTimeFactor();
			const logics::MovingTickListener* ownMoving = dynamic_cast<const logics::MovingTickListener*>( m_gameObject );
			maths::Vec3f mypos = m_gameObject->getModelMatrix()*m_position + ownMoving->getVelocity()*time;
			float myRadius = m_radius * m_gameObject->getSize().x;
			const logics::MovingTickListener* otherMoving = dynamic_cast<const logics::MovingTickListener*>( other->getGameObject() );
			if ( otherMoving )
			{
				const SphereCollider* sphere = dynamic_cast<const SphereCollider*>( other );
				if ( sphere )
				{
					maths::Vec3f otherpos = m_gameObject->getModelMatrix()*m_position + otherMoving->getVelocity()*time;//THREAD_SAFE: ggf alles mit gettern(auf jedenfall für anderen) | auch unten beim anderen
					float otherRadius = sphere->m_radius*sphere->m_gameObject->getSize().x;
					if ( mypos.fastDistance(otherpos) > maths::square(myRadius + otherRadius) )//bei sphere-sphere ist glaube ich rotation miteinbezogen, aber auch noch für sphere-cube machen
					{
						return false;
					}
					else
					{
						return true;
					}
				}
			}
			else
			{
				const SphereCollider* sphere = dynamic_cast<const SphereCollider*>( other );
				if ( sphere )
				{
					maths::Vec3f otherpos = m_gameObject->getModelMatrix()*m_position;
					float otherRadius = sphere->m_radius*sphere->m_gameObject->getSize().x;
					if ( mypos.fastDistance(otherpos) > maths::square(myRadius + otherRadius) )//bei sphere-sphere ist glaube ich rotation miteinbezogen, aber auch noch für sphere-cube machen
					{
						return false;
					}
					else
					{
						return true;
					}
				}
			}
		}

	}
}