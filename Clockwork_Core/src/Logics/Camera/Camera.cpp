#include "Camera.h"
#include "src\Logics\States\State.h"

namespace clockwork {
	namespace logics {

		Camera::Camera(State* state, const maths::Vec3f& position, const maths::Vec3f& direction, const maths::Vec3f& up) noexcept
			: m_state(state), m_position(position), m_direction(direction), m_worldUp(up), m_yaw(90.0), m_pitch(0.0), m_fov(90.0), m_near(0.05f), m_far(1000.0f)///später auch hier werte von konstruktor übernehmen | pitch yaw sind hier noch fest und werden nicht anhand direction bestimmt
		{
			m_direction.normalizeSelf();
			m_worldUp.normalizeSelf();
			m_right = m_worldUp.crossproduct(m_direction).normalizeSelf();
			m_up = m_direction.crossproduct(m_right).normalizeSelf();
		}

		void Camera::setFov(float fov) noexcept
		{
			m_fov = fov;
			m_state->updateProjection();
		}
		void Camera::setNear(float near_) noexcept
		{
			m_near = near_;
			m_state->updateProjection();
		}
		void Camera::setFar(float far_) noexcept
		{
			m_far = far_;
			m_state->updateProjection();
		}

		const State&  Camera::getState() const noexcept
		{
			return *m_state;
		}
		State&  Camera::getState() noexcept
		{
			return *m_state;
		}

	}
}