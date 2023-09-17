#pragma once
#include "src\Utils\Helper.h"

struct GLFWwindow;
struct GLFWmonitor;
struct GLFWimage;
enum FREE_IMAGE_FORMAT : int;

namespace clockwork {
	namespace graphics {

		/*handels the glfw3 window and functions | can only be created and destroyed from the main thread */
		class Window
		{

		private:
			int m_width, m_height;
			double m_mouseX, m_mouseY;
			double m_mouseSpeed;
			double m_lastScreenMouseX, m_lastScreenMouseY;
			double m_sizeRatioX, m_sizeRatioY;
			GLFWwindow* m_window;
			const char* m_title;
			bool m_fullscreen;
			unsigned short m_vsync; 
			int m_monitorCount, m_currentMonitor;
			GLFWmonitor** m_monitors;

		public:
			/*creates an glfw3 window and an opengl context | must be called from the main thread and init has to be called first 
			also calls glViewport(0, 0, width, height)
			@param[title] displayed on the window 
			@param[width] the width of the window in pixel
			@param[height] the height of the window in pixel
			@param[vsync] the number of screen updates to wait for when swapping back(render) and front(display) buffers | 0 = no vsync, 1 = vsync 
			@param[fullscreen] maximized window true/false bool
			@param[monitorNumber] the monitor to display the window on | 0 = primary monitor 
			@param[shared] a window to share the opengl context(same textures, etc) | NULL = no shared window */
			Window(const char *title, int width = 0, int height = 0, unsigned short vsync=0, bool fullscreen=true, int monitorNumber = 0, GLFWwindow* shared = nullptr) noexcept;
			
			/*destroys the glfw3 window | does not call the onClose callback | must be called from the main thread */
			~Window() noexcept;

		public:
			/*inits glfw3 and FreeImage | must be called from the main thread and before windows are created at the start of the program | will be called from the engine constructor*/
			static void init() noexcept;

			/*destroys glfw, FreeImage and every window | must be called from the main thread at the end of the program | will be called from the engine destructor*/
			static void destroy() noexcept;

			/*resize callback: gets called when the window size changes(fullscreen, setsize, etc) from main thread/updateInput()
			updates the window size and its ratios to the new width and height in pixels
			calls glViewport(0, 0, width, height) and engine->onResize(width,height,window)
			onResize can be overridden in subclass of Engine*/
			static void resize_callback(GLFWwindow *window, int width, int height) noexcept;

			/*key callback: gets called when a key is pressed from the main thread/updateInput() | not ment for text input
			@param[key] is represented in ascii code, or with GLFW_KEY_[NAME] http://www.glfw.org/docs/latest/group__keys.html | plattform independant | GLFW_KEY_UNKNOWN if key is not specified
			@param[scancode] is plattform-specific but consistent | better use key
			@param[action] GLFW_PRESS fires once a key is pressed | GLFW_RELEASE fires once a key is released | GLFW_REPEAT pressing a key a bit longer for text typing
			@param[mods] GLFW_MOD_SHIFT 0x0001 for shift held down while pressing keys, GLFW_MOD_CONTROL 0x0002, GLFW_MOD_ALT 0x0004, GLFW_MOD_SUPER 0x0008 for super keys
			if you dont want to include GLFW, you can include src/Utils/Helper(if its not automaticly included) and use the clockwork macros(just swap the GLFW against CLOCKWORK) 
			calls engine->onKeyPress(key,scancode,action,mods,window)
			onKeyPress can be overridden in a subclass of Engine*/
			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept;

			/*char callback: gets called when a key is typed for text input from the main thread/updateInput()
			@param[keycode] unicode code points in utf-32
			@param[mods] GLFW_MOD_SHIFT 0x0001 for shift held down while pressing keys, GLFW_MOD_CONTROL 0x0002, GLFW_MOD_ALT 0x0004, GLFW_MOD_SUPER 0x0008
			if you dont want to include GLFW, you can include src/Utils/Helper(if its not automaticly included) and use the clockwork macros(just swap the GLFW against CLOCKWORK)
			calls engine->onCharTyped(keycode,mods,window)
			onCharTyped can be overridden in a subclass of Engine*/
			static void charmods_callback(GLFWwindow* window, unsigned int codepoint, int mods) noexcept;

			/*mouse button callback: gets called when a mouse button is pressed from the main thread/updateInput()
			@param[button] is represented in numbers from 0 to 7, or with GLFW_MOUSE_BUTTON_[NUMBER] http://www.glfw.org/docs/latest/group__buttons.html | plattform independant
			@param[action] GLFW_PRESS fires once a mouse button is pressed | GLFW_RELEASE fires once a mouse button is released
			@param[mods] GLFW_MOD_SHIFT 0x0001 for shift held down while pressing mouse buttons, GLFW_MOD_CONTROL 0x0002, GLFW_MOD_ALT 0x0004, GLFW_MOD_SUPER 0x0008 for super keys
			if you dont want to include GLFW, you can include src/Utils/Helper(if its not automaticly included) and use the clockwork macros(just swap the GLFW against CLOCKWORK)
			calls engine->onMousePress(button,action,mods,window)
			onMousePress can be overridden in a subclass of Engine*/
			static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) noexcept;

			/*mouse position callback: gets called when the mouse is moved from the main thread/updateInput()
			the mouse position is relative to the top left corner of the screen in pixels
			it starts at 0,0 from the bottom left corner and goes to windowWidth-1, windowHeight-1 to the top right corner | it does not matter if the cursor is visible or not
			@param[xmove] the amount of pixels the mouse moved on the x axis | 0 is no movement, a positive value is movement to the right and a negative value is movement to the left
			@param[ymove] the amount of pixels the mouse moved on the y axis | 0 is no movement, a positive value is movement up and a negative value is movement down
			to get the mouse position in pixels you have to call window.getMouseX() and window.getMouseY()
			the movement can be big, when the cursor leaves the window on the one side and enters the window on the other side, so you might wanna check for too high move values
			calls engine->onMouseMove(xmove,ymove,window)
			onMouseMove can be overridden in a subclass of Engine*/
			static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos) noexcept;

			/*scroll callback: gets called when scrolling with the mouse, or touchpad from the main thread/updateInput()
			@param[xoffset] 0 = no scrolling, 1 = forward, -1 = backward
			@param[yoffset] 0 = no scrolling, 1 = left, -1 = right
			calls engine->onScroll(xoffset, yoffset)
			onScroll can be overridden in a subclass of Engine*/
			static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) noexcept;

			/*cursor enter callback: gets called when the cursor enters, or exits the window from the main thread/updateInput()
			@param[entered] 0 = cursor left, 1 = cursor entered
			calls engine->onCursorEnter(entered,window)
			onCursorEnter can be overridden in a subclass of Engine*/
			static void cursor_enter_callback(GLFWwindow* window, int entered) noexcept;

			/*file drop callback: gets called when a file, or a directory is dropped into the window
			returns an array of strings(utf-8 encoded) for the file paths(need to be deep copied)
			@param[count] number of files
			@param[paths] array of cstrings for the file paths
			calls engine->onFileDrop(count,paths)
			onFileDrop can be overridden in a subclass of Engine*/
			static void drop_callback(GLFWwindow* window, int count, const char** paths) noexcept;

			/*window focus callback: gets called when the window is focused, or looses focus from the main thread/updateInput()
			@param[focused] 0 = lost focus, 1 = gain focus
			calls engine->onFocus(focus,window)
			onFocus can be overridden in a subclass of Engine*/
			static void window_focus_callback(GLFWwindow* window, int focused) noexcept;

			/*close callback: gets called when the window is closed by the user by pressing the X on the window from the main thread/updateInput()
			calls engine->onClose(window)
			onClose can be overridden in a subclass of Engine*/
			static void window_close_callback(GLFWwindow* window) noexcept;

			/*glfw3 error callback: logs the error to the console in debug mode*/
			static void glfw_error_callback(int error, const char* description) noexcept;

			/*FreeImage errror callback: logs the error to the console in debug mode*/
			static void freeImage_error_callback(FREE_IMAGE_FORMAT fif, const char* message) noexcept;

			/*opengl error callback: logs the error to the console in debug mode*/
			//static void GLAPIENTRY opengl_error_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

		public:
			/*binds the opengl context of the window to the calling thread and inits glad | should be called from the graphic thread
			opengl rendering for this window can only be done from the calling thread after calling this method once 
			context can only be current for a single thread at a time and a thread can only have a single context current at a time*/
			void makeCurrent() const noexcept;

			/*swaps the back(render) and front(display) buffers and clears the back buffer if the window is open
			should be called from the graphic thread at the end of rendering in a loop
			calls glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)*/
			void updateWindow() const noexcept;

			/*manually checks for opengl errors and prints them to the console
			should only be used in debug mode*/
			void checkError() const noexcept;

			/*updates the events, invokes callbacks | must be called from the main thread and should be called in a loop
			cannot be called from a callback */
			void updateInput() const noexcept;

		public:
			/*returns if the window is open/visible */
			const bool isOpen() const noexcept;

			/*returns if a key was last pressed=true, or released=false | must be called from main thread
			@param[key] represented in ascii code, or with GLFW_KEY_[NAME] http://www.glfw.org/docs/latest/group__keys.html | plattform independant | GLFW_KEY_UNKNOWN if key is not specified
			if you dont want to include GLFW, you can include src/Utils/Helper(if its not automaticly included) and use the clockwork macros(just swap the GLFW against CLOCKWORK)*/
			const bool isKeyPressed(int key) const noexcept;

			/*returns if a mouse button was last pressed=true, or released=false | must be called from main thread
			@param[button] represented in numbers from 0 to 7, or with GLFW_MOUSE_BUTTON_[NUMBER] http://www.glfw.org/docs/latest/group__buttons.html | plattform independant
			if you dont want to include GLFW, you can include src/Utils/Helper(if its not automaticly included) and use the clockwork macros(just swap the GLFW against CLOCKWORK)*/
			const bool isMouseButtonPressed(int button) const noexcept;
			
			/*returns the keyboard layout dependent name of the printable keycode, or scancode | must be called from main thread
			@param[key] represented in ascii code, or with GLFW_KEY_[NAME] http://www.glfw.org/docs/latest/group__keys.html | plattform independant | GLFW_KEY_UNKNOWN if key is not specified
			if you dont want to include GLFW, you can include src/Utils/Helper(if its not automaticly included) and use the clockwork macros(just swap the GLFW against CLOCKWORK)*/
			const char* getKeyName(int key) const noexcept;
			
			/*returns the string saved in the clipboard | strg+v as string | must be called from main thread*/
			const char* getClipboard() const noexcept;

			/*returns the width of the window in screen coordinates*/
			const int getScreenWidth() const noexcept {return m_width/m_sizeRatioX;}

			/*returns the height of the window in screen coordinates*/
			const int getScreenHeight() const noexcept {return m_height/m_sizeRatioY;}

			/*returns the width of the window in pixels*/
			const int getWidth() const noexcept {return m_width;}

			/*returns the height of the window in pixels*/ 
			const int getHeight() const noexcept {return m_height;}

			/*returns the mouse position relative to the bottom left corner of the window in pixels
			it starts at 0,0 from the bottom left corner and goes to windowWidth-1, windowHeight-1 to the top right corner | it does not matter if the cursor is visible or not*/
			const double getMouseX() const noexcept {return m_mouseX;}

			/*returns the mouse position relative to the bottom left corner of the window in pixels
			it starts at 0,0 from the bottom left corner and goes to windowWidth-1, windowHeight-1 to the top right corner | it does not matter if the cursor is visible or not*/
			const double getMouseY() const noexcept {return m_mouseY;}

			/*returns the mouse speed = the multiplication of pixels moved when moving the mouse | an alternative to changing the mouse dpi | the default is 1 without any modifiers to the dpi of the mouse*/
			const double getMouseSpeed() const noexcept {return m_mouseSpeed;}

			/*returns the GLFWwindow pointer*/
			GLFWwindow* const getWindow() const noexcept { return m_window; }

			/*returns the name of the window*/
			const char* const getTitle() const noexcept { return m_title; }

			/*returns the number of screen updates to wait for when swapping back(render) and front(display) buffers | 0 = no vsync, 1 = vsync   */
			const int getVsync() const noexcept {return m_vsync;}

			/*returns the number of the current monitor to display the window on | 0=primary monitor, etc of the monitor array*/
			const int getCurrentMonitor() const noexcept {return m_currentMonitor;}

			/*returns the number of connected moniotors to the pc and available to use for a window*/
			const int getMonitorCount() const noexcept {return m_monitorCount;}

			/*returns an array of monitor pointers to each monitor connected on the pc and available to use for a window | 0 = first/primary monitor*/
			const GLFWmonitor*const*const getMonitorArray() const noexcept {return m_monitors;}

			/*returns if the window is in fullscreen mode*/
			const bool isFullscreen() const noexcept {return m_fullscreen;}

			/*returns the value of the glfw timer | its the time elapsed in seconds(resolution of timer is system dependent micro or nanoseconds) since glfw was initialized if it has not been changed with setTimer */
			const double getTimer() const noexcept;

		public:
			/*changes the number of the current monitor to display the window on and automaticly changes the size of the window | 0=primary monitor, etc of the monitor array | must be called from main thread*/
			void setMonitor(int monitorCount) noexcept;

			/*changes fullscreen(true/false) and automaticly changes the size of the window | must be called from main thread*/
			void setFullscreen(bool fullscreen) noexcept;

			/*hides and locks the cursor to the window(true), or shows and unlocks the cursor from the window(false) | must be called from the main thread
			if the cursor is locked to the window, it cant go out of the window while tabbed in
			you should always draw an own cursor and hide the default glfw3 cursor */
			void hideCursor(bool hide=true) noexcept;

			/*resizes the window to the given parameters in screen coordinates | must be called from main thread*/ 
			void setScreenSize(int width, int height) const noexcept;

			/*resizes the window to the given parameters in pixels | must be called from main thread*/
			void setPixelSize(int width, int height) const noexcept;

			/*sets the mouse position relative to the bottom left corner of the window in pixels
			it starts at 0,0 from the bottom left corner and goes to windowWidth-1, windowHeight-1 to the top right corner | it does not matter if the cursor is visible or not*/
			void setMousePosition(double mouseX, double mouseY) noexcept;

			/*sets the mouse speed = the multiplication of pixels moved when moving the mouse | an alternative to changing the mouse dpi | the default is 1 without any modifiers to the dpi of the mouse*/
			void setMouseSpeed(double speed) noexcept {m_mouseSpeed=speed;}

			/*changes the title displayed on the window | must be called from main thread*/
			void setTitle(const char* title) noexcept;

			/*changes the number of screen updates to wait for when swapping back(render) and front(display) buffers | 0 = no vsync, 1 = vsync   */
			void setVsync(int vsync) noexcept;

			/*one or more images(best 48x48) to display as icon on the window | automaticly changes to the needed size and chooses the image of the array with the nearest size | must be called from main thread
			@param[image] pointer to an array of images 
			@param[count] the size of the array of images*/
			void setIcon(const GLFWimage* image, int count = 1) const noexcept;

			/*saves the string into the clipboard | strg+c as string | must be called from main thread*/
			void setClipboard(const char* cstring) const noexcept;
			
			/*sets the value of the glfw timer in seconds(resolution of timer is system dependent micro or nanoseconds) and it will continue to count up from that value*/
			void setTimer(double time) noexcept;

		};


	}
}