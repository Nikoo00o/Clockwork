#include "State.h"
#include "src\Core\Engine.h"
#include "src\Core\Window.h"
#include "src\Logics\Camera\Camera.h"
#include "src\Graphics\Renderer\Renderer.h"
#include "src\Logics\ChunkSystem\ChunkSystem.h"

namespace clockwork {
	namespace logics {

			State::State() noexcept
			{
			
			}

			State::~State() noexcept
			{

			}

			void State::enter() noexcept
			{
				//sachen/texturen vorbereiten/der renterwarteschlange adden 
				m_defaultCamera = new Camera(this, { 0,5,5 });
				m_defaultRenderer = new graphics::Renderer(new graphics::Shader("res/Shaders/Default/Instancing.vs", "res/Shaders/Default/Instancing.fs"), new graphics::Shader("res/Shaders/Default/Normal.vs", "res/Shaders/Default/Normal.fs"), &m_currentCamera, &m_perspectiveProjection);
			}

			void State::leave() noexcept
			{
				delete m_defaultCamera;
				delete m_defaultRenderer;
				delete m_chunkSystem;
				//sachen/texturen löschen
			}

			void State::fastTick() noexcept
			{

			}

			void State::slowTick() noexcept
			{

			}

			void State::render() noexcept
			{

			}

			void State::onProjectionUpdate() noexcept
			{

			}

			void State::updateProjection() noexcept
			{
				if ( engine->getWindow()->getWidth() != 0 && engine->getWindow()->getHeight() != 0 )
				{
					m_perspectiveProjection = maths::Mat4x4<float>::perspective(maths::toRadians<float>(m_currentCamera->getFov()), static_cast<double>( engine->getWindow()->getWidth() ) / static_cast<double>( engine->getWindow()->getHeight() ), m_currentCamera->getNear(), m_currentCamera->getFar());//projection matrix for the scene to transform world coordinates into screen coordinates | has to be set once per update of the window size
					//auch noch orthographic updaten
					m_defaultRenderer->updateProjection();
				}
				onProjectionUpdate();
			}

			logics::Camera& State::getCurrentCamera() noexcept
			{
				return *m_currentCamera;
			}
			const logics::Camera& State::getCurrentCamera() const noexcept
			{
				return *m_currentCamera;
			}
			logics::ChunkSystem& State::getChunkSystem() noexcept
			{
				return *m_chunkSystem;
			}
			const logics::ChunkSystem& State::getChunkSystem() const noexcept
			{
				return *m_chunkSystem;
			}
			graphics::Renderer& State::getDefaultRenderer() noexcept
			{
				return *m_defaultRenderer;
			}
			const graphics::Renderer& State::getDefaultRenderer() const noexcept
			{
				return *m_defaultRenderer;
			}

			void State::setCurrentCamera(logics::Camera* camera) noexcept
			{
				m_currentCamera = camera;
				updateProjection();
			}

			void State::onResize(int width, int height, graphics::Window* window) noexcept
			{
				updateProjection();
			}

			void State::onKeyPress(int key, int scancode, int action, int mods, graphics::Window* window) noexcept
			{

			}

			void State::onCharTyped(unsigned int keycode, int mods, graphics::Window* window) noexcept
			{

			}

			void State::onMousePress(int button, int action, int mods, graphics::Window* window) noexcept
			{

			}

			void State::onMouseMove(double xoffset, double yoffset, graphics::Window* window) noexcept
			{

			}

			void State::onScroll(int xoffset, int yoffset, graphics::Window* window) noexcept
			{

			}

			void State::onCursorEnter(int entered, graphics::Window* window) noexcept
			{

			}

			void State::onFileDrop(int count, const char** paths, graphics::Window* window) noexcept
			{

			}

			void State::onFocus(int focus, graphics::Window* window) noexcept
			{

			}

			void State::onClose(graphics::Window* window) noexcept
			{

			}

	}
}