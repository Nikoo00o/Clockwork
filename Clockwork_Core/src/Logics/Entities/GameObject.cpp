#include "GameObject.h"
#include "src\Logics\States\State.h"
#include "src\Logics\ChunkSystem\ChunkSystem.h"
#include "src\Logics\ChunkSystem\Chunk.h"
#include "src\Logics\Entities\Listener\RenderListener.h"

namespace clockwork {
	namespace logics {

		GameObject::GameObject(const maths::Vec3f& size, const maths::Vec3f& rotation, const maths::Vec3f& position, State* state) noexcept
			: m_size(size), m_rotation(rotation), m_position(position), m_modelMatrix(maths::Mat4f::scaling(size)), m_chunk(&state->getChunkSystem().getChunkAt(position))
		{
			if ( rotation.x > 0 )
				m_modelMatrix.rotateXD(rotation.x);
			if ( rotation.y > 0 )
				m_modelMatrix.rotateYD(rotation.y);
			if ( rotation.z > 0 )
				m_modelMatrix.rotateZD(rotation.z);
			m_modelMatrix.translate(position);
		}

		GameObject::~GameObject() noexcept
		{

		}

		GameObject::GameObject(const GameObject& other) noexcept
			: m_size(other.m_size), m_rotation(other.m_rotation), m_position(other.m_position), m_modelMatrix(other.m_modelMatrix), m_chunk(other.m_chunk)
		{

		}

		GameObject::GameObject(GameObject&& other) noexcept
			: m_size(other.m_size), m_rotation(other.m_rotation), m_position(other.m_position), m_modelMatrix(other.m_modelMatrix), m_chunk(other.m_chunk)
		{
			other.m_chunk = nullptr;//auch hier bei listenern add/remove/etc
		}

		GameObject& GameObject::operator=(const GameObject& other) noexcept
		{
			m_size = other.m_size;
			m_rotation = other.m_rotation;
			m_position = other.m_position;
			m_modelMatrix = other.m_modelMatrix;
			m_chunk = other.m_chunk;
			this->onMatrixChange();
			return *this;
		}

		GameObject& GameObject::operator=(GameObject&& other) noexcept
		{
			m_size = other.m_size;
			m_rotation = other.m_rotation;
			m_position = other.m_position;
			m_modelMatrix = other.m_modelMatrix;
			m_chunk = other.m_chunk;
			//hier ggf auch add/remove sachen in den listenern
			other.m_chunk = nullptr;
			this->onMatrixChange();
			return *this;
		}

		void GameObject::updateModelMatrix() noexcept
		{
			m_modelMatrix = maths::Mat4f::scaling(m_size);
			if ( m_rotation.x > 0 )
				m_modelMatrix.rotateXD(m_rotation.x);
			if ( m_rotation.y > 0 )
				m_modelMatrix.rotateYD(m_rotation.y);
			if ( m_rotation.z > 0 )
				m_modelMatrix.rotateZD(m_rotation.z);
			m_modelMatrix.translate(m_position);
			this->onMatrixChange();
		}

		const Chunk& GameObject::getChunk() const noexcept
		{
			return *m_chunk;
		}

		Chunk& GameObject::getChunk() noexcept
		{
			return *m_chunk;
		}

		void GameObject::setChunk(Chunk* newChunk) noexcept
		{
			m_chunk = newChunk;
		}
	}
}
