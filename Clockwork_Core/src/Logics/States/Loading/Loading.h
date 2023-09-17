#pragma once
#include "src\Logics\States\State.h"

namespace clockwork {
	namespace logics {

		class Loading
			: public State//muss noch angepasst werden und alles überschreiben
		{

		private:
			State** m_statePointer;
			State* m_newState;

		public:
			Loading() noexcept;
			virtual ~Loading() noexcept;

		public:
			virtual void changeState(State* prevState, State* newState, State** statePointer) noexcept;
			virtual void fastTick() noexcept override;
			virtual void render() noexcept override;


		};


	}
}