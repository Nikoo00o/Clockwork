#pragma once
#include "src\Maths\Vec3.h"
#include "src\Maths\Mat4x4.h"


namespace clockwork {
	namespace logics {

		class State;
		class Chunk;

		class GameObject
		{

		protected://auch in subklassen immer erst mutex locken, etc | oder getter/setter nehmen 
			Chunk * m_chunk;
			maths::Mat4f m_modelMatrix;
			maths::Vec3f m_size;
			maths::Vec3f m_rotation;
			maths::Vec3f m_position;

		public:
			GameObject(const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state) noexcept;
			virtual ~GameObject() noexcept;
			GameObject(const GameObject& other) noexcept;
			GameObject(GameObject&& other) noexcept;
			GameObject& operator=(const GameObject& other) noexcept;
			GameObject& operator=(GameObject&& other) noexcept;
			

		protected:
			//muss überschrieben werden und dann für instancedcubes setchanged(true) aufrufen | auch dazuschreiben, dass es protected und nicht public ist
			virtual void onMatrixChange() noexcept = 0;

		public:
			//updated modelmatrix und ruft onMatrixChange auf | immer nach verändern der vektoren irgendwann updatemodelmatrix aufrufen
			void updateModelMatrix() noexcept;

			const Chunk& getChunk() const noexcept;
			//hier threadsafe machen ohne const kann state verändert werden
			Chunk& getChunk() noexcept;

			//dont call this method if you dont know what you are doing | it will change the chunk pointer of the gameobject without updating the listeners in the chunk and without changing the position of the gameobject to the new chunk
			void setChunk(Chunk* newChunk) noexcept;

			inline const maths::Mat4f& getModelMatrix() const noexcept {return m_modelMatrix;}
			inline const maths::Mat4f* getModelMatrixMemoryLocation() const noexcept {return &m_modelMatrix;}
			inline const maths::Vec3f& getSize() const noexcept {return m_size;}
			inline const maths::Vec3f& getRotation() const noexcept {return m_rotation;}
			inline const maths::Vec3f& getPosition() const noexcept {return m_position;}
			inline maths::Vec3f& getSize() noexcept{return m_size;}//ab hier mutex setzen
			inline maths::Vec3f& getRotation() noexcept{return m_rotation;}
			inline maths::Vec3f& getPosition() noexcept{return m_position;}

			//setzt position x anders und updated es automatisch in der modelmatrix | dies auch für changeX machen und auch für andere position, size, translation,etc machen (wegen lars)
			inline void setX(float x) noexcept
			{
				m_position.x = x;
				m_modelMatrix.x4 = x;
			}
			inline void changeX(float x) noexcept
			{
				m_position.x += x;
				m_modelMatrix.x4 += x;
			}

		};

	}
}


