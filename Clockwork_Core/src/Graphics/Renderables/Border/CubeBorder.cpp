#include <algorithm>
#include "src\Logics\States\State.h"
#include "src\Graphics\Renderer\Renderer.h"
#include "CubeBorder.h"
#include "BorderManager.h"

namespace clockwork {
	namespace graphics {



		CubeBorder::CubeBorder(maths::Mat4f* modelMatrixPointer, bool deleteModelMatrixPointer, logics::State* state) noexcept//ggf updatemodelmatrix, setmodelmatrix, oder so machen 
			: m_modelMatrixPointer(modelMatrixPointer), m_deleteModelMatrixPointer(deleteModelMatrixPointer), m_manager(&state->getDefaultRenderer().m_borderManager)
		{}

		CubeBorder::~CubeBorder() noexcept
		{
			remove();
			if ( m_deleteModelMatrixPointer )
				delete m_modelMatrixPointer;
		}

		void CubeBorder::add() noexcept
		{
			auto iterator = std::find(m_manager->m_cubeBorders.begin(), m_manager->m_cubeBorders.end(), this);
			if ( iterator != m_manager->m_cubeBorders.end() )
				return;
			m_manager->m_cubeBorders.push_back(this);

		}

		void CubeBorder::remove() noexcept
		{
 			auto iterator = std::find(m_manager->m_cubeBorders.begin(), m_manager->m_cubeBorders.end(), this);
			if ( iterator != m_manager->m_cubeBorders.end() )
				m_manager->m_cubeBorders.erase(iterator);
		}

	}
}