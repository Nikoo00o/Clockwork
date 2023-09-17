#pragma once
#include "src\Maths\Mat4x4.h" 

namespace clockwork {
	namespace logics {
		class State;
	}
	namespace graphics {

		class BorderManager;

		class CubeBorder
		{

		private:
			friend class BorderManager;
			maths::Mat4f* m_modelMatrixPointer;//pointer auf modelmatrix, damit hier immer die aktuelle benutzt wird(aktualisiert sich automatisch, ist hier ja normal rendering und nicht instanced) | bei chunks dann einfach modelmatrix mit new erstellen, da chunksize ja nicht im spiel verändert wird
			bool m_deleteModelMatrixPointer;
			BorderManager* m_manager;//im konstruktor wieder state pointer mitgeben, damit es ermittelt wird

		public:
			CubeBorder(maths::Mat4f* modelMatrixPointer, bool deleteModelMatrixPointer, logics::State* state) noexcept;
			~CubeBorder() noexcept;

		public:
			void add() noexcept;//wie bei anderen modellen add/remove | muss dann von chunks auch in renderadd/renderremove aufgerufen werden | wird bei border aber auch automatisch
			void remove() noexcept;


		};

	}
}