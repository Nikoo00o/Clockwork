#pragma once
#include "src\Logics\Entities\GameObject.h"

namespace clockwork {
	namespace logics {
		
		class Chunk;

		class RenderListener 
			: public virtual GameObject
		{

		public:
			RenderListener() noexcept;//bei move/copy konstruktor/operator ggf nicht addrenderlistener/etc aufrufen, oder auch schon remove und renderadd zum verschieben, kopieren, etc
			~RenderListener() noexcept;

		protected:
			//muss von allen UNTERSTEN erbenden klassen im konstruktor aufgerufen werden(wegen virtual objekte müssen erstellt worden sein)
			void init() noexcept;

		public:
			//dazuschreiben: wird aufgerufen, wenn chunk des objekts in renderdistance kommt | kann somit auch ggf andere effekte abspielen | kann aber auch manuell aufgerufen werden
			virtual void renderAdd() noexcept = 0;
			virtual void renderRemove() noexcept = 0;


		};

	}
}

