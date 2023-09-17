#include "Loading.h"

namespace clockwork {
	namespace logics {

		Loading::Loading() noexcept
			: State(), m_statePointer(nullptr), m_newState(nullptr)
		{

		}

		Loading:: ~Loading() noexcept
		{

		}

		void Loading::changeState(State* prevState, State* newState, State** statePointer) noexcept
		{
			*m_statePointer = *statePointer;
			m_newState = newState;
			if ( prevState != nullptr )
			prevState->leave();//vielleicht wenn es schnell genug geht, einfach alles löschen, sonst die aktionen dem threadworker system zuweisen
			newState->enter();//hier auch wie oben und natürlich texturen, etc zur renderwarteschlange adden
		}

		void Loading::fastTick() noexcept
		{
			//irgendwie testen wie lange es noch loaden muss 
			//es muss auch mit dem server ausgetauscht werden, ob eine welt, oder ähnliches geladen werden muss und loadingscreen darf ja erst 
			//state wieder wechseln, wenn alles fertig geladen ist 
			*m_statePointer = m_newState;//hier state von engine auf den neuen state setzten, WENN ALLES FERTIG GELADEN HAT ! also hier noch irgendwie testen, ob renderloop fertig mit laden ist und ob der threadworkerthread fertig ist und der server sachen für den state geschickt hat 

		}

		void Loading::render() noexcept
		{
			//immer loadingscreen zeichnen | ggf auch erbende klasse mit loadingbalken machen 
		}

	}
}