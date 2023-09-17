#include "glad\glad.h"
#include "glfw\glfw3.h"
#include "Window.h"
#include "Engine.h"
#include "FreeImage\FreeImage.h"

namespace clockwork {
	namespace graphics {

		Window::Window(const char *title, int width, int height, unsigned short vsync, bool fullscreen, int monitorNumber, GLFWwindow* shared) noexcept
			:m_title(title), m_width(width), m_height(height), m_vsync(vsync), m_fullscreen(fullscreen), m_currentMonitor(monitorNumber), m_mouseX(0), m_mouseY(0), m_mouseSpeed(1), m_lastScreenMouseX(0), m_lastScreenMouseY(0)
		{
			m_monitors = glfwGetMonitors(&m_monitorCount);
			if ( m_width == 0 || m_height == 0 )
			{
				const GLFWvidmode* mode = glfwGetVideoMode(m_monitors[m_currentMonitor]);
				m_width = mode->width;
				m_height = mode->height;
			}

			if ( m_fullscreen ) 
				m_window = glfwCreateWindow(m_width, m_height, m_title, m_monitors[m_currentMonitor], shared);
			else 
				m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, shared);

			if ( !m_window )
			{
				std::cout << "Window creation failed" << std::endl;
			}

			makeCurrent();
			glfwGetFramebufferSize(m_window, &m_width, &m_height);//pixelsize
			int tempWidth, tempHeight;
			glfwGetWindowSize(m_window, &tempWidth, &tempHeight);//screensize
			m_sizeRatioX = static_cast<double>( m_width ) / static_cast<double>( tempWidth );//ration from screensize to pixelsize
			m_sizeRatioY = static_cast<double>( m_height ) / static_cast<double>( tempHeight );

			glViewport(0, 0, m_width, m_height);
			glfwGetCursorPos(m_window, &m_lastScreenMouseX, &m_lastScreenMouseY);
			m_mouseX = m_lastScreenMouseX * m_sizeRatioX;
			m_mouseY = m_height - m_lastScreenMouseY * m_sizeRatioY;
			glfwSwapInterval(m_vsync);//VSYNC

			glfwSetWindowUserPointer(m_window, this);//classobject to glfw pointer
			glfwSetFramebufferSizeCallback(m_window, Window::resize_callback);
			glfwSetKeyCallback(m_window, Window::key_callback);
			glfwSetCharModsCallback(m_window, Window::charmods_callback);
			glfwSetMouseButtonCallback(m_window, Window::mouse_button_callback);
			glfwSetCursorPosCallback(m_window, Window::mouse_position_callback);
			glfwSetScrollCallback(m_window, Window::scroll_callback);
			glfwSetCursorEnterCallback(m_window, Window::cursor_enter_callback);
			glfwSetDropCallback(m_window, drop_callback);
			glfwSetWindowFocusCallback(m_window, Window::window_focus_callback);
			glfwSetWindowCloseCallback(m_window, Window::window_close_callback);

		}

		Window::~Window() noexcept
		{
			if( !glfwWindowShouldClose(m_window) )
				glfwDestroyWindow(m_window);
		}

		void Window::init() noexcept
		{
			FreeImage_Initialise(false);
#if CLOCKWORK_DEBUG
			glfwSetErrorCallback(Window::glfw_error_callback);
			FreeImage_SetOutputMessage(freeImage_error_callback);
#endif
			if ( !glfwInit() )
			{
				std::cout << "GLFW init failed" << std::endl;
			}

			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
			glfwWindowHint(GLFW_SAMPLES, 4);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
			glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
			glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
			glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
			glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
			glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
			glfwWindowHint(GLFW_RED_BITS, GLFW_DONT_CARE);
			glfwWindowHint(GLFW_GREEN_BITS, GLFW_DONT_CARE);
			glfwWindowHint(GLFW_BLUE_BITS, GLFW_DONT_CARE);
			glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
		}

		void Window::destroy() noexcept
		{
			FreeImage_DeInitialise();
			glfwTerminate();
		}

		void Window::resize_callback(GLFWwindow *window, int width, int height) noexcept
		{
			Window* win = static_cast<Window*>( glfwGetWindowUserPointer(window) );
			win->m_width = width;
			win->m_height = height;
			int tempWidth, tempHeight;
			glfwGetWindowSize(win->m_window, &tempWidth, &tempHeight);//convert screensize to pixelsize 
			win->m_sizeRatioX = static_cast<double>( win->m_width ) / static_cast<double>( tempWidth );
			win->m_sizeRatioY = static_cast<double>( win->m_height ) / static_cast<double>( tempHeight );
			glViewport(0, 0, win->m_width, win->m_height);//viewport for opengl to use for drawing
			engine->onResize(width, height, win);
		}

		void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept
		{
			engine->onKeyPress(key, scancode, action, mods, static_cast<Window*>( glfwGetWindowUserPointer(window) ));
		}

		void Window::charmods_callback(GLFWwindow* window, unsigned int codepoint, int mods) noexcept
		{
			engine->onCharTyped(codepoint, mods, static_cast<Window*>( glfwGetWindowUserPointer(window) ));
		}

		void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) noexcept
		{
			engine->onMousePress(button, action, mods, static_cast<Window*>( glfwGetWindowUserPointer(window) ));//void pointer casted to Window pointer to the class object related to the opengl window object
		}

		void Window::mouse_position_callback(GLFWwindow* window, double xpos, double ypos) noexcept
		{
			Window* win = static_cast<Window*>( glfwGetWindowUserPointer(window) );///GANZ WICHTIG HIER NOCH OPTIMIEREN UND ÜBERALL ANDERS KOMMENTIEREN UND ÄNDERN, ALSO GET/SET MOUSEPOS IM WINDOW UND CALLBACK IN ENGINE UND WINDOW

			win->m_mouseX += ( xpos - win->m_lastScreenMouseX )*win->m_mouseSpeed*win->m_sizeRatioX;
			win->m_mouseY -= ( ypos - win->m_lastScreenMouseY )*win->m_mouseSpeed*win->m_sizeRatioY;

			if ( win->m_mouseX < 0 )
				win->m_mouseX = 0;
			else if ( win->m_mouseX >= win->m_width )
				win->m_mouseX = win->m_width - 1;

			if ( win->m_mouseY < 0 )
				win->m_mouseY = 0;
			else if ( win->m_mouseY >= win->m_height )
				win->m_mouseY = win->m_height - 1;

			engine->onMouseMove(( xpos - win->m_lastScreenMouseX )*win->m_mouseSpeed*win->m_sizeRatioX, -( ( ypos - win->m_lastScreenMouseY )*win->m_mouseSpeed*win->m_sizeRatioY ), win);
			win->m_lastScreenMouseX = xpos;
			win->m_lastScreenMouseY = ypos;
		}

		void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) noexcept
		{
			engine->onScroll(xoffset, yoffset, static_cast<Window*>( glfwGetWindowUserPointer(window) ));
		}

		void Window::cursor_enter_callback(GLFWwindow* window, int entered) noexcept
		{
			engine->onCursorEnter(entered, static_cast<Window*>( glfwGetWindowUserPointer(window) ));
		}

		void Window::drop_callback(GLFWwindow* window, int count, const char** paths) noexcept
		{
			engine->onFileDrop(count, paths, static_cast<Window*>( glfwGetWindowUserPointer(window) ));
		}

		void Window::window_focus_callback(GLFWwindow* window, int focused) noexcept
		{
			engine->onFocus(focused, static_cast<Window*>( glfwGetWindowUserPointer(window) ));
		}

		void Window::window_close_callback(GLFWwindow* window) noexcept
		{
			engine->onClose(static_cast<Window*>( glfwGetWindowUserPointer(window) ));
		}

		void Window::glfw_error_callback(int error, const char* description) noexcept
		{
			std::cout << "GLFW3 Error: " << error << " Info: " << description << std::endl;
		}

		void Window::freeImage_error_callback(FREE_IMAGE_FORMAT fif, const char* message) noexcept
		{
			std::cout << "FreeImage Error: ";
			if ( fif != FIF_UNKNOWN )
				std::cout << " Format: " << FreeImage_GetFormatFromFIF(fif);
			std::cout << " Message: " << message << std::endl;
		}

		/*void GLAPIENTRY Window::opengl_error_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
		{
		std::cout << "OPENGL Error: \n" << "Source: " << source << " Type: " << type << " Id: " << id << " Severity: " << severity << "\nMessage: " << message;
		}*/

		void Window::makeCurrent() const noexcept
		{
			glfwMakeContextCurrent(m_window);
			if ( !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) )
			{
				std::cout << "GLAD init failed" << std::endl;
			}
			std::cout << "Opengl Version: " << glGetString(GL_VERSION) << std::endl;
/*#if CLOCKWORK_DEBUG
			if ( glDebugMessageCallback )
			{
				std::cout << "Register OpenGL debug callback " << std::endl;
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageCallback(graphics::Window::opengl_error_callback, nullptr);
			}
			else
				std::cout << "glDebugMessageCallback not available" << std::endl;
#endif*/
		}

		void Window::updateWindow() const noexcept
		{
			if ( !glfwWindowShouldClose(m_window) )
			{
				glfwSwapBuffers(m_window);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
		}

		void Window::checkError() const noexcept
		{
			if ( GLenum error = glGetError() )
				std::cout << "Opengl Error: " << error << std::endl;
		}

		void Window::updateInput() const noexcept
		{
			glfwPollEvents();
		}

		const bool Window::isOpen() const noexcept
		{
			return !glfwWindowShouldClose(m_window);
		}

		const bool Window::isKeyPressed(int key) const noexcept
		{
			if ( glfwGetKey(m_window, key) == GLFW_PRESS )
				return true; 
			return false;
		}

		const bool Window::isMouseButtonPressed(int button) const noexcept
		{
			if ( glfwGetMouseButton(m_window, button) == GLFW_PRESS )
				return true; 
			return false;
		}

		const char* Window::getKeyName(int key) const noexcept
		{
			return glfwGetKeyName(key, 0);
		}

		const char* Window::getClipboard() const noexcept
		{
			return glfwGetClipboardString(m_window);
		}

		const double Window::getTimer() const noexcept
		{
			return glfwGetTime();
		}

		void Window::setMonitor(int monitorCount) noexcept
		{
			m_currentMonitor = monitorCount;
			if ( m_fullscreen )
			{
				const GLFWvidmode* mode = glfwGetVideoMode(m_monitors[m_currentMonitor]);
				glfwSetWindowMonitor(m_window, m_monitors[m_currentMonitor], 0, 0, mode->width, mode->height, mode->refreshRate);
				glfwSwapInterval(m_vsync);
			}
		}

		void Window::setFullscreen(bool fullscreen) noexcept
		{
			m_fullscreen = fullscreen;
			const GLFWvidmode* mode = glfwGetVideoMode(m_monitors[m_currentMonitor]);
			if ( fullscreen )
				glfwSetWindowMonitor(m_window, m_monitors[m_currentMonitor], 0, 0, mode->width, mode->height, mode->refreshRate);
			else
				glfwSetWindowMonitor(m_window, NULL, 0, 30, mode->width, mode->height - 70, mode->refreshRate);
			glfwSwapInterval(m_vsync);
		}

		void Window::hideCursor(bool hide) noexcept
		{
			if(hide)
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			glfwGetCursorPos(m_window, &m_lastScreenMouseX, &m_lastScreenMouseY);
			m_mouseX = m_lastScreenMouseX * m_sizeRatioX;
			m_mouseY = m_height - m_lastScreenMouseY * m_sizeRatioY;
		}

		void Window::setScreenSize(int width, int height) const noexcept
		{
			glfwSetWindowSize(m_window, width, height);
		}

		void Window::setPixelSize(int width, int height) const noexcept
		{
			glfwSetWindowSize(m_window, width / m_sizeRatioX, height / m_sizeRatioY);
		}

		void Window::setMousePosition(double mouseX, double mouseY) noexcept
		{
			m_mouseX = mouseX;
			m_mouseY = mouseY;
		}

		void Window::setTitle(const char* title) noexcept
		{
			m_title = title;
			glfwSetWindowTitle(m_window, m_title); 
		}

		void Window::setVsync(int vsync) noexcept
		{
			m_vsync = vsync; 
			glfwSwapInterval(m_vsync);
		}

		void Window::setIcon(const GLFWimage* image, int count) const noexcept
		{
			glfwSetWindowIcon(m_window, count, image);
		}

		void Window::setClipboard(const char* cstring) const noexcept
		{
			glfwSetClipboardString(m_window, cstring);
		}

		void  Window::setTimer(double time) noexcept
		{
			glfwSetTime(time);
		}

	}
}