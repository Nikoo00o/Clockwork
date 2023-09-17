#pragma once
#include "src\Graphics\Buffers\VertexBuffer.h"
#include "src\Graphics\Buffers\IndexBuffer.h"
#include "src\Graphics\Buffers\VertexArray.h"
#include "src\Graphics\Renderer\Shader.h"
#include "src\Graphics\Textures\Texture2D.h"
#include "src\Maths\Mat4x4.h"
#include "src\Maths\Vec2.h"

#include <vector>
#include <stdlib.h>  

namespace clockwork {
	namespace graphics {

		class BadTerrainTest
		{

		private:
			struct Vertex
			{
				maths::Vec3f pos;
				maths::Vec2f tex;
				maths::Vec3f normal;
			};
			using floatarr = float[8 * 4 * 6];//anders nimmt compiler es nicht an, muss also mit using 
			using uchararr = unsigned char[36];

		private:
			VertexArray m_vao;
			VertexBuffer m_vbo;
			IndexBuffer<unsigned char> m_ibo;//einfach hier als unsigned int angenommen, klasse muss eh nochmal anders gemacht werden für instanced rendering 
			Texture2D bot, top, left, right, front, back;
			maths::Mat4x4<float> m_modelMatrix;

		public:

			BadTerrainTest(unsigned int width=500, unsigned int height = 500, unsigned int depth=500) noexcept
			{
				m_vbo =  VertexBuffer(//you could also create a local nameless array of vertices, where vertex is a struct with vec2 of float for position and vec2 of float for colour
					floatarr//floats
					{//positions          texture coords	 vertex normals
				    //back
					-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,//0
					1.0f, -1.0f, 1.0f,      1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
					-1.0f, 1.0f, 1.0f,      0.0f, 1.0f,     0.0f, 0.0f, 1.0f,
					1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
					//top								
					-1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f, //4
					1.0f, 1.0f, 1.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
					-1.0f, 1.0f, -1.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
					1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
					//front							
					-1.0f, 1.0f, -1.0f,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f,//8
					1.0f, 1.0f, -1.0f,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f,
					-1.0f, -1.0f, -1.0f,	1.0f, 0.0f,		0.0f, 0.0f, -1.0f,
					1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
					//bot								
					-1.0f, -1.0f, -1.0f,    1.0f, 1.0f,     0.0f, -1.0f, 0.0f,//12
					1.0f, -1.0f, -1.0f,     0.0f, 1.0f,     0.0f, -1.0f, 0.0f,
					-1.0f, -1.0f,  1.0f,    1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
					1.0f, -1.0f,  1.0f,     0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
					//right			    			    
					1.0f, -1.0f,  1.0f,     0.0f, 0.0f,     1.0f,  0.0f, 0.0f,//16
					1.0f, -1.0f, -1.0f,     1.0f, 0.0f,     1.0f,  0.0f, 0.0f,
					1.0f,  1.0f,  1.0f,     0.0f, 1.0f,     1.0f,  0.0f, 0.0f,
					1.0f,  1.0f, -1.0f,     1.0f, 1.0f,     1.0f, 0.0f, 0.0f,
					//left				    			    
					-1.0f, -1.0f, -1.0f,    0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,//20
					-1.0f, -1.0f, 1.0f,	    1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
					-1.0f, 1.0f, -1.0f,	    0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
					-1.0f, 1.0f, 1.0f,	    1.0f, 1.0f,     -1.0f, 0.0f, 0.0f
					}, 8 * 4 * 6 * sizeof(float)
					);

				m_ibo = IndexBuffer<unsigned char>(uchararr {
					2,1,0,		3,1,2,
					6,5,4,		7,5,6,
					10,9,8,		11,9,10,
					14,13,12,	15,13,14,
					18,17,16,	19,17,18,
					22,21,20,	23,21,22
												   }, 36
												   );


				front = Texture2D(utils::Image("res/Images/skybox/front.png").load());
				back = Texture2D(utils::Image("res/Images/skybox/back.png").load());
				top = Texture2D(utils::Image("res/Images/skybox/top.png").load());
				bot = Texture2D(utils::Image("res/Images/skybox/bot.png").load());
				left = Texture2D(utils::Image("res/Images/skybox/left.png").load());
				right = Texture2D(utils::Image("res/Images/skybox/right.png").load());

				m_vbo.connectToVao<float>(3, false, 8 * sizeof(float));//3d position
				m_vbo.connectToVao<float>(2, false, 8 * sizeof(float));//2d texture coords
				m_vbo.connectToVao<float>(3, false, 8 * sizeof(float));//3d vertex normals

				m_modelMatrix = maths::Mat4x4<float>::scaling(200, 200, 200);
				m_modelMatrix.translate(0, 0, 0);
			}


			void render(Shader* shader) noexcept
			{
				shader->setUniform("u_model", m_modelMatrix);
				m_vao.bind();

				front.bind();//reverse order, because camera is inside the cube
				m_ibo.drawParts(0, 6);

				top.bind();
				m_ibo.drawParts(6, 6);

				back.bind();
				m_ibo.drawParts(12, 6);

				bot.bind();
				m_ibo.drawParts(18, 6);

				left.bind();
				m_ibo.drawParts(24, 6);

				right.bind();
				m_ibo.drawParts(30, 6);
			}


		};

	}
}