#pragma once
#include "src\Logics\States\State.h"
#include <vector>
#include "src\Maths\Mat4x4.h"
#include "src\Graphics\Renderer\Renderer.h"

namespace clockwork {
	namespace logics {

		class TestGame
			: public State
		{

		public:
			TestGame() noexcept;
			virtual ~TestGame() noexcept;

		public:
			virtual void enter() noexcept override;
			virtual void leave() noexcept override;
			virtual void fastTick() noexcept override;
			virtual void slowTick() noexcept override;
			virtual void render() noexcept override;


		public:
			/*resize callback: gets called when the window size changes(fullscreen, setsize, etc) from main thread/updateInput()
			updates the window size and its ratios to the new width and height in pixels
			calls glViewport(0, 0, width, height) and engine->onResize(width,height,window)
			onResize can be overridden in subclass of Engine*/
			virtual void onResize(int width, int height, graphics::Window* window) noexcept override;

			/*key callback: gets called when a key is pressed from the main thread/updateInput() | not ment for text input
			@param[key] is represented in ascii code, or with GLFW_KEY_[NAME] http://www.glfw.org/docs/latest/group__keys.html | plattform independant | GLFW_KEY_UNKNOWN if key is not specified
			@param[scancode] is plattform-specific but consistent | better use key
			@param[action] GLFW_PRESS fires once a key is pressed | GLFW_RELEASE fires once a key is released | GLFW_REPEAT pressing a key a bit longer for text typing
			@param[mods] GLFW_MOD_SHIFT 0x0001 for shift held down while pressing keys, GLFW_MOD_CONTROL 0x0002, GLFW_MOD_ALT 0x0004, GLFW_MOD_SUPER 0x0008 for super keys
			if you dont want to include GLFW, you can include src/Utils/Helper(if its not automaticly included) and use the clockwork macros(just swap the GLFW against CLOCKWORK)
			calls engine->onKeyPress(key,scancode,action,mods,window)
			onKeyPress can be overridden in a subclass of Engine*/
			virtual void onKeyPress(int key, int scancode, int action, int mods, graphics::Window* window) noexcept override;

			/*char callback: gets called when a key is typed for text input from the main thread/updateInput()
			@param[keycode] unicode code points in utf-32
			@param[mods] GLFW_MOD_SHIFT 0x0001 for shift held down while pressing keys, GLFW_MOD_CONTROL 0x0002, GLFW_MOD_ALT 0x0004, GLFW_MOD_SUPER 0x0008
			if you dont want to include GLFW, you can include src/Utils/Helper(if its not automaticly included) and use the clockwork macros(just swap the GLFW against CLOCKWORK)
			calls engine->onCharTyped(keycode,mods,window)
			onCharTyped can be overridden in a subclass of Engine*/
			virtual void onCharTyped(unsigned int keycode, int mods, graphics::Window* window) noexcept override;

			/*mouse button callback: gets called when a mouse button is pressed from the main thread/updateInput()
			@param[button] is represented in numbers from 0 to 7, or with GLFW_MOUSE_BUTTON_[NUMBER] http://www.glfw.org/docs/latest/group__buttons.html | plattform independant
			@param[action] GLFW_PRESS fires once a mouse button is pressed | GLFW_RELEASE fires once a mouse button is released
			@param[mods] GLFW_MOD_SHIFT 0x0001 for shift held down while pressing mouse buttons, GLFW_MOD_CONTROL 0x0002, GLFW_MOD_ALT 0x0004, GLFW_MOD_SUPER 0x0008 for super keys
			if you dont want to include GLFW, you can include src/Utils/Helper(if its not automaticly included) and use the clockwork macros(just swap the GLFW against CLOCKWORK)
			calls engine->onMousePress(button,action,mods,window)
			onMousePress can be overridden in a subclass of Engine*/
			virtual void onMousePress(int button, int action, int mods, graphics::Window* window) noexcept override;

			/*mouse position callback: gets called when the mouse is moved from the main thread/updateInput()
			the mouse position is relative to the top left corner of the screen in pixels
			it starts at 0,0 from the bottom left corner and goes to windowWidth-1, windowHeight-1 to the top right corner | it does not matter if the cursor is visible or not
			@param[xmove] the amount of pixels the mouse moved on the x axis | 0 is no movement, a positive value is movement to the right and a negative value is movement to the left
			@param[ymove] the amount of pixels the mouse moved on the y axis | 0 is no movement, a positive value is movement up and a negative value is movement down
			to get the mouse position in pixels you have to call window.getMouseX() and window.getMouseY()
			the movement can be big, when the cursor leaves the window on the one side and enters the window on the other side, so you might wanna check for too high move values
			calls engine->onMouseMove(xmove,ymove,window)
			onMouseMove can be overridden in a subclass of Engine*/
			virtual void onMouseMove(double xoffset, double yoffset, graphics::Window* window) noexcept override;

			/*scroll callback: gets called when scrolling with the mouse, or touchpad from the main thread/updateInput()
			@param[xoffset] 0 = no scrolling, 1 = forward, -1 = backward
			@param[yoffset] 0 = no scrolling, 1 = left, -1 = right
			calls engine->onScroll(xoffset, yoffset)
			onScroll can be overridden in a subclass of Engine*/
			virtual void onScroll(int xoffset, int yoffset, graphics::Window* window) noexcept override;

			/*cursor enter callback: gets called when the cursor enters, or exits the window from the main thread/updateInput()
			@param[entered] 0 = cursor left, 1 = cursor entered
			calls engine->onCursorEnter(entered,window)
			onCursorEnter can be overridden in a subclass of Engine*/
			virtual void onCursorEnter(int entered, graphics::Window* window) noexcept override;

			/*file drop callback: gets called when a file, or a directory is dropped into the window
			returns an array of strings(utf-8 encoded) for the file paths(need to be deep copied)
			@param[count] number of files
			@param[paths] array of cstrings for the file paths
			calls engine->onFileDrop(count,paths)
			onFileDrop can be overridden in a subclass of Engine*/
			virtual void onFileDrop(int count, const char** paths, graphics::Window* window) noexcept override;

			/*window focus callback: gets called when the window is focused, or looses focus from the main thread/updateInput()
			@param[focused] 0 = lost focus, 1 = gain focus
			calls engine->onFocus(focus,window)
			onFocus can be overridden in a subclass of Engine*/
			virtual void onFocus(int focus, graphics::Window* window) noexcept override;

			/*close callback: gets called when the window is closed by the user by pressing the X on the window from the main thread/updateInput()
			calls engine->onClose(window)
			onClose can be overridden in a subclass of Engine*/
			virtual void onClose(graphics::Window* window) noexcept override;

		};


	}
}