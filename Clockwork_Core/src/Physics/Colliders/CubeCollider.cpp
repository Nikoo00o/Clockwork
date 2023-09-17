#include "SphereCollider.h"
#include "CubeCollider.h"
#include "src\Logics\Entities\GameObject.h"
#include "src\Logics\Entities\Listener\MovingTickListener.h"
#include "src\Logics\Entities\Listener\StaticTickListener.h"
#include "src\Core\Engine.h"
namespace clockwork {
	namespace physics {

		CubeCollider::CubeCollider(logics::GameObject* gameObject, const maths::Vec3f& frontBotLeft, const maths::Vec3f& backTopRight) noexcept
			: Collider(gameObject), m_frontBotLeft(frontBotLeft), m_backTopRight(backTopRight)
		{

		}

		bool CubeCollider::collides(const Collider* other) const noexcept//collides wird immer von movingticklistener mit entweder movingticklistener, oder staticticklistener aufgerufen
		{
			double time = engine->getTimeFactor();
			const logics::MovingTickListener* ownMoving = dynamic_cast<const logics::MovingTickListener*>( m_gameObject );
			maths::Vec3f myfbl = m_gameObject->getModelMatrix()*m_frontBotLeft + ownMoving->getVelocity()*time;
			maths::Vec3f mybtr = m_gameObject->getModelMatrix()*m_backTopRight + ownMoving->getVelocity()*time;
			const logics::MovingTickListener* otherMoving = dynamic_cast<const logics::MovingTickListener*>( other->getGameObject() );
			if ( otherMoving )
			{
				const CubeCollider* cube = dynamic_cast<const CubeCollider*>( other );
				if ( cube )
				{
					maths::Vec3f otherfbl = cube->m_gameObject->getModelMatrix()*cube->m_frontBotLeft + otherMoving->getVelocity()*time;//THREAD_SAFE: ggf mit getter machen
					maths::Vec3f otherbtr = cube->m_gameObject->getModelMatrix()*cube->m_backTopRight + otherMoving->getVelocity()*time;
					if ( myfbl.x <= otherbtr.x&&mybtr.x >= otherfbl.x//schlechte collision ohne rotation miteinbezogen, lieber https://gamedevelopment.tutsplus.com/tutorials/collision-detection-using-the-separating-axis-theorem--gamedev-169  https://gamedev.stackexchange.com/questions/112883/simple-3d-obb-collision-directx9-c  http://www.randygaul.net/2014/05/22/deriving-obb-to-obb-intersection-sat/
						&&myfbl.y <= otherbtr.y&&mybtr.y >= otherfbl.y
						&&myfbl.z <= otherbtr.z&&mybtr.z >= otherfbl.z )
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				const CubeCollider* cube = dynamic_cast<const CubeCollider*>( other );
				if ( cube )
				{
					maths::Vec3f otherfbl = cube->m_gameObject->getModelMatrix()*cube->m_frontBotLeft;//THREAD_SAFE: ggf mit getter machen
					maths::Vec3f otherbtr = cube->m_gameObject->getModelMatrix()*cube->m_backTopRight;
					if ( myfbl.x <= otherbtr.x&&mybtr.x >= otherfbl.x//schlechte collision ohne rotation miteinbezogen, lieber https://gamedevelopment.tutsplus.com/tutorials/collision-detection-using-the-separating-axis-theorem--gamedev-169  https://gamedev.stackexchange.com/questions/112883/simple-3d-obb-collision-directx9-c  http://www.randygaul.net/2014/05/22/deriving-obb-to-obb-intersection-sat/
						&&myfbl.y <= otherbtr.y&&mybtr.y >= otherfbl.y
						&&myfbl.z <= otherbtr.z&&mybtr.z >= otherfbl.z )
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}

	}
}