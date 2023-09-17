#include "glad\glad.h"
#include "glfw\glfw3.h"
#include "TestGame.h"
#include "src\Core\Window.h"
#include "src\Graphics\Renderer\Shader.h"
#include "src\Graphics\Buffers\IndexBuffer.h"
#include "src\Graphics\Buffers\VertexBuffer.h"
#include "src\Graphics\Buffers\VertexArray.h"
#include "src\Logics\States\State.h"
#include "src\Logics\States\Loading\Loading.h"
#include "src\Graphics\Textures\Texture2D.h"
#include "src\Graphics\Textures\TextureArray2D.h"
#include "src\Graphics\Textures\SpriteSheet.h"
#include "src\Core\Engine.h"
#include "src\Logics\Camera\Camera.h"


#include "src\Graphics\Renderables\Cube\CubeManager.h"
#include "src\Graphics\Renderables\Cube\InstancedCube.h"


#include "src\Maths\Vec3.h"


#include "src\Logics\Entities\Test.h"
#include "src\Logics\ChunkSystem\ChunkSystem.h"

namespace clockwork {
	namespace logics {

		static bool transparent = false;//global zum test, später weg
		static int texturecount = 15;//anzahl texturen temporär | geht auch einfach m_defaultRenderer->cubeManager.getTextureCount()
		static int transparentTexturecount = 8;

		TestGame::TestGame() noexcept
		{

		}

		TestGame::~TestGame() noexcept
		{

		}

		static float getRand() noexcept//global zum test, später weg
		{
			float test =  -(float)( rand() % 100000 + 1 ) / 100 + (float)( rand() % 100000 + 1 ) / 100;
			return test;
		}

		void TestGame::enter() noexcept
		{
			using namespace graphics;
			using namespace utils;
			setCurrentCamera(m_defaultCamera);//muss aufgerufen werden, nachdem alle renderer erstellt wurden, aber vor chunksystem
			m_chunkSystem = new ChunkSystem({ -800,-800,-800 }, { 800,800,800 }, { 10,10,10 }, { 4,4,4 }, { 4,4,4 }, this);//chunksystem in erbenden states mit den jeweiligenn größen erstellen | nachdem camera und renderer erstellt wurden, aber bevor gameobjects hinzugefügt werden 
			///immoment nur renderdistance 1 zum testen | später auch chunkdistanz erhöhen, da man immoment error bekommt, wenn camerapos ausserhalb des chunks ist | auch gucken wie z is(negativ/nicht) wegen opengl right hand system

			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/brick.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/stone.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/granite.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/moss.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/brick2.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/granite2.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/wood.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/grass.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/blue.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/red.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/purple.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/brick3.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/green.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/abstract.jpg").load());
			m_defaultRenderer->cubeManager.addInstancedTexture(utils::Image("res/Images/ice.jpg").load());


 			m_defaultRenderer->cubeManager.addNormalTexture("res/Images/transparent/glass.png");
			m_defaultRenderer->cubeManager.addNormalTexture("res/Images/transparent/blue.png");
			m_defaultRenderer->cubeManager.addNormalTexture("res/Images/transparent/diagmonds.png");
			m_defaultRenderer->cubeManager.addNormalTexture("res/Images/transparent/diamond.png");
			m_defaultRenderer->cubeManager.addNormalTexture("res/Images/transparent/dust.png");
			m_defaultRenderer->cubeManager.addNormalTexture("res/Images/transparent/straws.png");
			m_defaultRenderer->cubeManager.addNormalTexture("res/Images/transparent/wall.png");
			m_defaultRenderer->cubeManager.addNormalTexture("res/Images/transparent/washi.png");

			m_defaultRenderer->cubeManager.addNormalTexture("res/Images/player1.png");
			m_defaultRenderer->cubeManager.addNormalTexture("res/Images/player2.png");

			std::srand(engine->getWindow()->getTimer() * 10);

			for ( int i = 0; i < 25000; ++i )//10000 objects: normal 300fps, instancing 2300fps | 1000objects: normal 2000fps, instancing 5000fps | 100 objects: normal 5500fps, instancing 6100fps | 10 objects: normal 5500fps, instancing 5500fps | 1 object: normal 6300fps, instancing 6100fps
			{
				maths::Vec3f pos = maths::Vec3f(getRand(), getRand(), getRand());
				logics::Block* inst = new logics::Block(rand() % texturecount, maths::Vec3f(1, 1, 1), maths::Vec3f(0, 0, 0), pos, this, m_defaultRenderer);
			}

			for ( int i = 0; i < 100; ++i )
			{
				maths::Vec3f pos = maths::Vec3f(getRand(), getRand(), getRand());
				logics::TransparentBlock* inst = new logics::TransparentBlock(rand() % transparentTexturecount, maths::Vec3f(1, 1, 1), maths::Vec3f(0, 0, 0), pos, this, m_defaultRenderer);
			}

			logics::Player* player = new logics::Player(this, m_defaultRenderer);

		}

		void TestGame::leave() noexcept
		{

		}

		void TestGame::fastTick() noexcept
		{
			double time = engine->getTimeFactor();//time scaling factor 

			//camera movement
// 			if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_W) )
// 			{
// 				m_currentCamera->moveZ(5 * time);
// 			}
// 			else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_S) )
// 			{
// 				m_currentCamera->moveZ(-5 * time);
// 			}
// 			if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_A) )
// 			{
// 				m_currentCamera->moveX(-5 * time);
// 			}
// 			else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_D) )
// 			{
// 				m_currentCamera->moveX(5 * time);
// 			}
// 			if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_LEFT_CONTROL) )
// 			{
// 				m_currentCamera->moveY(-5 * time);
// 			}
// 			else if ( engine->getWindow()->isKeyPressed(CLOCKWORK_KEY_SPACE) )
// 			{
// 				m_currentCamera->moveY(5 * time);
// 			}

			m_chunkSystem->fastTick();

		}

		void TestGame::slowTick() noexcept
		{
			m_chunkSystem->slowTick();
			std::cout << "CameraPos: " << m_currentCamera->getPosition() << " Direction: " << m_currentCamera->getDirection() << std::endl;
		}

		void TestGame::render() noexcept
		{
			m_chunkSystem->update();
			m_defaultRenderer->render();//ggf in state render verschieben | gennauso mit allen weiterleitungen ans chunksystem
			m_defaultRenderer->renderTransparent();
		}


		void TestGame::onResize(int width, int height, graphics::Window* window) noexcept
		{

		}

		void TestGame::onKeyPress(int key, int scancode, int action, int mods, graphics::Window* window) noexcept
		{
			if ( key == CLOCKWORK_KEY_X && action == CLOCKWORK_PRESS )
				m_currentCamera->movePos(m_currentCamera->getDirection() * 50);
			else if ( key == CLOCKWORK_KEY_C && action == CLOCKWORK_PRESS )
				m_currentCamera->movePos(-m_currentCamera->getDirection() * 50);
		}

		void TestGame::onCharTyped(unsigned int keycode, int mods, graphics::Window* window) noexcept
		{

		}

		void TestGame::onMousePress(int button, int action, int mods, graphics::Window* window) noexcept
		{
			if ( action == CLOCKWORK_PRESS )
			{
				if ( button == CLOCKWORK_MOUSE_BUTTON_1 )
				{
					if ( transparent )
					{
						logics::TransparentBlock* inst3 = new logics::TransparentBlock(rand() % transparentTexturecount, maths::Vec3f(1, 1, 1), maths::Vec3f(0, 0, 0), m_currentCamera->getPosition() + m_currentCamera->getDirection() * 5, this, m_defaultRenderer);
					}
					else
					{
// 						for ( unsigned int i = 0; i < 11; ++i )
// 						{
// 							logics::MovingBlock* inst2 = new logics::MovingBlock(rand() % texturecount, maths::Vec3f(1, 1, 1), maths::Vec3f(0, 0, 0), m_currentCamera->getPosition() + m_currentCamera->getDirection() * 5*i, this, m_defaultRenderer);
// 						}
					}
				}
				else if ( button == CLOCKWORK_MOUSE_BUTTON_2 )
				{
					if ( transparent )
					{
						m_defaultRenderer->cubeManager.removeLastTransparentCube();
					}
					else
					{
/*						m_defaultRenderer->cubeManager.removeLastInstancedCube();*/
					}
				}
				else if ( button == CLOCKWORK_MOUSE_BUTTON_3)
				{
					if ( transparent )
						transparent = false;
					else
						transparent = true;
				}
			}

		}

		void TestGame::onMouseMove(double xoffset, double yoffset, graphics::Window* window) noexcept
		{
			m_currentCamera->rotate(xoffset/10, yoffset /10);
		}

		void TestGame::onScroll(int xoffset, int yoffset, graphics::Window* window) noexcept
		{
			if ( m_currentCamera->getFov()> 120 )//zooming by changing fov and then updating projectionmatrix 
				m_currentCamera->setFov(120);
			else if ( m_currentCamera->getFov() < 1 )
				m_currentCamera->setFov(1);
			else
				m_currentCamera->setFov(m_currentCamera->getFov() - yoffset);
		}

		void TestGame::onCursorEnter(int entered, graphics::Window* window) noexcept
		{

		}

		void TestGame::onFileDrop(int count, const char** paths, graphics::Window* window) noexcept
		{

		}

		void TestGame::onFocus(int focus, graphics::Window* window) noexcept
		{

		}

		void TestGame::onClose(graphics::Window* window) noexcept
		{

		}

	}
}