#pragma once
#include "src\Maths\Vec3.h"
#include "src\Maths\Mat4x4.h"
#include "src\Graphics\Renderer\Shader.h"

namespace clockwork {
	namespace logics {

		class State;

		/*vertex positions of world coordinates are transformed into view coordinates(in camera/view space) relative to the cameras position and direction
		the camera is like a coordinate system with the 3 axis and itself in the origin | careful with opengls right hand coordinate system(positive z-axis is going towards you) 
		so if you want to move the camera backwards(to you/the screen, away from the objects), you have to move it along the positive z-axis++
		and if you want to move the camera forward closer to the objects, you have to move it along the negative z-axis--
		the camera can be moved in each direction/axis and can be rotated around the x-axis(pitch) and the y-axis(yaw), but not around the z-axis(roll) */
		class Camera///ggf noch von erben mit third person und first person camera, etc | vielleicht muss dann gar keine virtuelle vererbung, da immer die methoden der superklasse benutzt werden können und nur verschiedene anfangswerte gesetzt werden im konstruktor | vielleicht muss auch keine vererbung | vielleicht nur noch freelook camera
		{
			
		private:
			maths::Vec3f m_position;//position of the camera in world space
			maths::Vec3f m_direction;//normalized direction(z-axis) of the camera in world space
			maths::Vec3f m_worldUp;//the start up(y-axis) vector of the camera in world space without rotations
			maths::Vec3f m_up;//normalized up(y-axis) vector of the camera in world space
			maths::Vec3f m_right;//normalized right(x-axis) vector of the camera in world space
			float m_yaw;//rotation angle around y-axis in degrees | looking left/right
			float m_pitch;//rotation angle around x-axis in degrees | looking up/down
			//roll would be rotation angle around the z-axis in degrees | rolling the camera
			float m_fov;//auch mit gettern mit referenz, einmal const, einmal nicht machen für multithread mit mutex
			float m_near;
			float m_far;
			State* m_state;

		public:
			/*creates a camera object at the given position facing in the given direction
			all parameters are in world space and the direction/worldUp vectors will be normalized inside
			@param[position] the position of the camera
			@param[direction] the direction of the camera to the front | z has to be negative, if you want the camera to look into the screen away from you, because of opengls right hand cooordinate system(positive z-axis is going towards you)
			the direction is not a point to where the camera looking at, but an offset to the position of the camera to calculate the point the camera is looking at
			@param[up] the y-axis of the camera | should go up to positive(y++) and should be orthogonal to the direction | should be 0,1,0 for a normal not rolled camera | the camera cant be rolled afterwards because of the fixed worldUp vector
			with the default parameters the camera is at the origin(0,0,0) facing the negative z-axis(into the screen away from you) aligned to the y-axis(for moving upwards) */
			Camera(State* state, const maths::Vec3f& position = { 0,0,0 }, const maths::Vec3f& direction = { 0,0,1 }, const maths::Vec3f& up = { 0,1,0 }) noexcept;///NEU KOMMENTIEREN LEFT HAND SYSTEm und jetzt in richtung positiv z
			virtual ~Camera() noexcept = default;//ggf virtual, wenn andere cameras von dieser erben, aber vielleicht auch weg machen

			/*shader has to be enabled first
			calculates the camera view matrix ands sends it to the selected shader | has to be called for each shader 
			and has to be called again after the camera changed | can also be updated every frame in the gameloop*/
			void update(graphics::Shader* shader) noexcept
			{
				shader->setUniform("u_view", maths::Mat4f::lookAt(m_position, m_position + m_direction, m_up));
			}

			/*moves the camera along its x-axis relative to its rotation and where its looking at
			speed is relative to the normalized crossproduct of the up and direction vector and used to scale it | this will result in the x-axis vector (mostly positive x++ to the right)
			so positive speed is the right vector and negative speed is the inverted right vector
			the view matrix has to be recalculated after this and send to the shader again by calling update(shader); */
			void moveX(float speed) noexcept
			{
				m_position += m_right * speed;
			}
			/*moves the camera along its y-axis relative to its rotation and where its looking at
			speed is relative to the up vector and used to scale it | so positive speed is the up vector and negative speed is the inverted up vector
			the view matrix has to be recalculated after this and send to the shader again by calling update(shader);*/
			void moveY(float speed) noexcept
			{
				m_position += speed * m_up;
			}
			/*moves the camera along its z-axis relative to its rotation and where its looking at
			speed is relative to the direction vector and used to scale it | so positive speed is the direction vector and negative speed is the inverted direction vector
			the view matrix has to be recalculated after this and send to the shader again by calling update(shader);*/
			void moveZ(float speed) noexcept
			{
				m_position += speed * m_direction;
			}
			/*moves the camera along a parameter direction vector | the direction vector WILL NOT BE NORMALIZED in this function, so you maybe have to normalize it yourself and then multiply it by a camera speed
			the parameter direction vector will only be added to the camera position, so if you want to move the camera inside the screen, the z has to be negative(opengls right hand system)
			the view matrix has to be recalculated after this and send to the shader again by calling update(shader);*/
			void movePos(const maths::Vec3f& direction) noexcept
			{
				m_position += direction;
			}

			/*adding degrees to the rotation angles and calculates a direction vector from the pitch/yaw angles | the direction vector will be calculated from where the angles are looking at
			yaw will start at -90(looking in -z direction into the screen)
			pitch will start at 0 and will be capped between -89 and 89
			xoffset will be added to the yaw rotation angle around y-axis in degrees | looking left/right
			yoffset will be added to the pitch rotation angle around x-axis in degrees | looking up/down
			roll would be rotation angle around the z-axis in degrees | rolling the camera | cant be calculated with this camera
			if the direction vector has been reset, it will recalculate the angles for the new position its looking at
			the direction vector has to be recalculated from the rotations after this(will be normalized) and will be when calling update(), moveX, moveY, moveZ
			the view matrix has to be recalculated after this and send to the shader again by calling update(shader);*/
			void rotate(float xoffset, float yoffset) noexcept
			{
				m_yaw -= xoffset;//xoffset for y-axis rotation  | vielleicht falsch wegen left handed coordinate system nochmal neu(temporär hier einfach negative x-offset)
				m_pitch += yoffset;//yoffset for x-axis rotation
				if ( m_pitch > 89.0f )
					m_pitch = 89.0f;
				if ( m_pitch < -89.0f )
					m_pitch = -89.0f;

				m_direction = maths::Vec3f {//euler angles: triangle with hypotenuse lenght=1 | calculate values for pitch rotation around x-axis(depending on y): coordinate system with y=y and x=x/z: right/up side of triangle y = sin(pitch) | bottom/right and foward side of triangle x/z = cos(pitch)
											//the same for yaw rotation around the y-axis(depending on x): coordinate system with y=z and x=x: right/up side of triangle z = sin(yaw) | bottom/right sidew of triangle x = cos(yaw) | y is not affected
					maths::cosR(maths::toRadians(m_pitch))* maths::cosR(maths::toRadians(m_yaw)),
					maths::sinR(maths::toRadians(m_pitch)),
					maths::cosR(maths::toRadians(m_pitch)) * maths::sinR(maths::toRadians(m_yaw))
				}.normalizeSelf();
				m_right = m_worldUp.crossproduct(m_direction).normalizeSelf();
				m_up = m_direction.crossproduct(m_right).normalizeSelf();
			}


		public:
			/*const read only access to the position of the camera in world space*/
			const maths::Vec3f& getPosition() const noexcept
			{
				return m_position;
			}
			/*const read only access to the direction of the camera in world space / where its looking at*/
			const maths::Vec3f& getDirection() const noexcept
			{
				return m_direction;
			}

			const maths::Vec3f& getRight() const noexcept
			{
				return m_right;
			}

			const maths::Vec3f& getUp() const noexcept
			{
				return m_up;
			}

			/*resets the position of the camera in world space | also automaticly resets the point the camera is looking at by adding the direction offset to the new camera position
			its like moving the camera around | the view matrix has to be recalculated after this and send to the shader again by calling update(shader);*/
			void setPosition(const maths::Vec3f& position) noexcept
			{
				m_position = position;
			}
			/*resets the position of the camera in world space | also automaticly resets the point the camera is looking at by adding the direction offset to the new camera position
			its like moving the camera around | the view matrix has to be recalculated after this and send to the shader again by calling update(shader);*/
			void setPositionX(float x) noexcept
			{
				m_position.x = x;
			}
			/*resets the position of the camera in world space | also automaticly resets the point the camera is looking at by adding the direction offset to the new camera position
			its like moving the camera around | the view matrix has to be recalculated after this and send to the shader again by calling update(shader);
			can be used to simulate a fps camera for a player where the y should not change while walking to avoid flying by resetting y to 0 after every move*/
			void setPositionY(float y) noexcept
			{
				m_position.y = y;
			}
			/*resets the position of the camera in world space | also automaticly resets the point the camera is looking at by adding the direction offset to the new camera position
			its like moving the camera around | the view matrix has to be recalculated after this and send to the shader again by calling update(shader);*/
			void setPositionZ(float z) noexcept
			{
				m_position.z = z;
			}
			/*resets the direction of the camera in world space where its looking at | recalculates all axes of the camera(also m_up and m_right vectors)
			its the z-axis of the camera and the z component should be negative, if the camera should move into the window(opengls right hand system)
			its like rotating the camera around | the view matrix has to be recalculated after this and send to the shader again by calling update(shader);
			the direction vector will NOT BE normalized inside the function, so you have to be careful and maybe normalize the parameter direction vector yourself before calling this method!*/
			void setDirection(const maths::Vec3f& direction) noexcept
			{
				m_direction = direction;
				m_pitch = maths::asinR(m_direction.y);///PITCH/YAW FUNKTIONIERT NICHT 
				m_yaw = (maths::atan2R(m_direction.x, m_direction.z)+90);

				//m_yaw = maths::atanR(direction.x / ( -direction.y ));
				//m_pitch = maths::atanR(maths::sqrt(direction.x*direction.x + direction.y*direction.y) / direction.z);


				m_right = m_direction.crossproduct(m_worldUp).normalizeSelf();
				m_up = m_right.crossproduct(m_direction).normalizeSelf();
			}
			/*resets the direction of the camera in world space where its looking at | recalculates all axes of the camera(also m_up and m_right vectors)
			its the z-axis of the camera and the z component should be negative, if the camera should move into the window(opengls right hand system)
			its like rotating the camera around | the view matrix has to be recalculated after this and send to the shader again by calling update(shader);
			the direction vector will NOT BE NORMALIZED inside the function, so you have to be careful when setting different components of the vector*/
			void setDirectionX(float x) noexcept
			{
				m_direction.x = x;
				m_pitch = maths::asinR(m_direction.y);
				m_yaw = maths::atan2R(m_direction.x, m_direction.z);

				m_right = m_direction.crossproduct(m_worldUp).normalizeSelf();
				m_up = m_right.crossproduct(m_direction).normalizeSelf();
			}
			/*resets the direction of the camera in world space where its looking at | recalculates all axes of the camera(also m_up and m_right vectors)
			its the z-axis of the camera and the z component should be negative, if the camera should move into the window(opengls right hand system)
			its like rotating the camera around | the view matrix has to be recalculated after this and send to the shader again by calling update(shader);
			the direction vector will NOT BE NORMALIZED inside the function, so you have to be careful when setting different components of the vector*/
			void setDirectionY(float y) noexcept
			{
				m_direction.y = y;
				m_pitch = maths::asinR(m_direction.y);
				m_yaw = maths::atan2R(m_direction.x, m_direction.z);

				m_right = m_direction.crossproduct(m_worldUp).normalizeSelf();
				m_up = m_right.crossproduct(m_direction).normalizeSelf();
			}
			/*resets the direction of the camera in world space where its looking at | recalculates all axes of the camera(also m_up and m_right vectors)
			its the z-axis of the camera and the z component should be negative, if the camera should move into the window(opengls right hand system)
			its like rotating the camera around | the view matrix has to be recalculated after this and send to the shader again by calling update(shader);
			the direction vector will NOT BE NORMALIZED inside the function, so you have to be careful when setting different components of the vector*/
			void setDirectionZ(float z) noexcept
			{
				m_direction.z = z;
				m_pitch = maths::asinR(m_direction.y);
				m_yaw = maths::atan2R(m_direction.x, m_direction.z);

				m_right = m_direction.crossproduct(m_worldUp).normalizeSelf();
				m_up = m_right.crossproduct(m_direction).normalizeSelf();
			}


// 			float fov;//auch mit gettern mit referenz, einmal const, einmal nicht machen für multithread mit mutex
// 			float nearMin;
// 			float farMax;


			const float getFov() const noexcept
			{
				return m_fov;
			}
			const float getNear() const noexcept
			{
				return m_near;
			}
			const float getFar() const noexcept
			{
				return m_far;
			}

			void setFov(float fov) noexcept;
			void setNear(float near_) noexcept;
			void setFar(float far_) noexcept;

			const State& getState() const noexcept;
			//hier threadsafe machen ohne const kann state verändert werden
			State& getState() noexcept;

		};

	}
}