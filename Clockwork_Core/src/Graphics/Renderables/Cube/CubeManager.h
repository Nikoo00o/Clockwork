#pragma once
#include <vector>
#include "src\Maths\Mat4x4.h"
#include "src\Graphics\Buffers\VertexBuffer.h"
#include "src\Graphics\Buffers\CopyBuffer.h"
#include "src\Graphics\Buffers\InternalCopyBuffer.h"
#include "src\Graphics\Buffers\IndexBuffer.h"
#include "src\Graphics\Buffers\VertexArray.h"
#include "src\Utils\Image.h"
#include "src\Graphics\Textures\TextureArray2D.h"
#include "src\Graphics\Textures\Texture2D.h"

namespace clockwork {
	namespace graphics {

		class InstancedCube;
		class NormalCube;
		class Renderer;

		/*
		CAREFUL: the size of each image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level), so CAREFUL WITH TRANSPARENCY TEXUTRES | dont use them for instanced cubes */
		class CubeManager
		{

		private:
			friend class InstancedCube;
			friend class NormalCube;
			friend class Renderer;
			friend struct TransparentCubeCompare;
			using floatarr = float[8 * 4 * 6];
			using uchararr = unsigned  char[36];

		private:
			VertexArray m_instanceArray;
			VertexArray m_normalArray;
			VertexBuffer m_vertexBuffer;
			VertexBuffer m_modelBuffer;
			CopyBuffer m_copyBuffer;
			IndexBuffer<unsigned char> m_indexBuffer;
			TextureArray2D m_textureArray;
			std::vector<Texture2D> m_normalTextures;
			std::vector<Texture2D> m_transparentTextures;
			std::vector<InstancedCube*> m_instanceCubes;
			std::vector<NormalCube*> m_normalCubes;
			std::vector<NormalCube*> m_transparentCubes;
			Renderer* m_renderer;

		public:

			CubeManager() noexcept;

			CubeManager(unsigned int reserved, Renderer* renderer) noexcept;

			~CubeManager() noexcept;

			CubeManager(const CubeManager& other) = delete;

			CubeManager(CubeManager&& other) noexcept;

			CubeManager& operator=(const CubeManager& other) = delete;

			CubeManager& operator=(CubeManager&& other) noexcept;

		private:
			int getNormalTextureId(const utils::Image& image) noexcept;
			int getNormalTextureId(const std::string& imagePath) noexcept;
			int getTransparentTextureId(const utils::Image& image) noexcept;
			int getTransparentTextureId(const std::string& imagePath) noexcept;

		public:

			void renderInstancedCubes() noexcept;

			void renderNormalCubes() noexcept;

			void renderTransparentCubes() noexcept;

			/*dont use the object at the position in the cubemanager, because it will change places with the last object in the list and the last object will then be removed */
			void removeInstancedCubesAt(int pos) noexcept;///neu besser kommentieren		| kommentieren, funktioniert nicht, wenn man 3. letztes mehrmals hintereinander entfernt, da es die sachen mischt und nicht aufrückt, also das letzte objekt kommt zur position des gelöschten objekts | ist richtig so, nur dazu schreiben | vorher binden | objekt danach nicht mehr benutzen
			
			//entfernt bei transparent immer das nächste
			void removeLastInstancedCube() noexcept;

			void removeNormalCubesAt(int pos) noexcept;

			void removeLastNormalCube() noexcept;

			void removeTransparentCubesAt(int pos) noexcept;//seperat für jede liste

			void removeLastTransparentCube() noexcept;

			/*adds an image/texture(that is not in the texturearray) to the texturearray2d of the cubemanager | dont add an image that already is in the texturearray, because then 2 identical images/textures would be in the texturearray2d
			CAREFUL: the size of the new image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[image] the texture/image that will be used for this model*/
			void addInstancedTexture(const utils::Image& image) noexcept;

			/*adds an image/texture(that is not in the texturearray) to the texturearray2d of the cubemanager | dont add an image that already is in the texturearray, because then 2 identical images/textures would be in the texturearray2d
			CAREFUL: the size of the new image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[imagePath] the path of a texture/image that will be used for this model*/
			///KEINE TRANSPARENTEN TEXTUREN 
			void addInstancedTexture(const std::string& imagePath) noexcept;

			//kann transparent sein, oder nicht | seperate texturelisten | textureid ist auch seperat für normal/transparent und natürlich auch für instanced
			void addNormalTexture(const utils::Image& image) noexcept;

			void addNormalTexture(const std::string& imagePath) noexcept;

			void addTextureBoth(const utils::Image& image) noexcept;//texture zu beiden hinzugefügt, kommentieren | normal und instanced, darf aber keine transparent texture sein 

			void addTextureBoth( const std::string& imagePath ) noexcept;

			void removeInstancedTexture(int textureId) noexcept;

			void removeInstancedTexture(const utils::Image& image) noexcept;

			void removeInstancedTexture(const std::string& imagePath) noexcept;

			void removeNormalTexture(int textureId, bool transparent) noexcept;

			void removeNormalTexture(const utils::Image& image) noexcept;

			void removeNormalTexture(const std::string& imagePath) noexcept;

			bool containsInstancedTexture(const utils::Image& image) noexcept;

			bool containsInstancedTexture(const std::string& imagePath) noexcept;

			bool containsNormalTexture(const utils::Image& image) noexcept;

			bool containsNormalTexture(const std::string& imagePath) noexcept;
			
			bool containsTransparentTexture(const utils::Image& image) noexcept;
			
			bool containsTransparentTexture(const std::string& imagePath) noexcept;

			const Renderer* const getRenderer() const noexcept;

			inline const unsigned int getInstanceCount() const noexcept {return m_instanceCubes.size();}

			inline const unsigned int getNormalCount() const noexcept {return m_normalCubes.size();}

			inline const unsigned int getTransparentCount() const noexcept {return m_transparentCubes.size();}

			inline const unsigned int getInstancedTextureCount() const noexcept {return m_textureArray.getTextureCount();}

			inline const unsigned int getNormalTextureCount() const noexcept {return m_normalTextures.size();}

			inline const unsigned int getTransparentTextureCount() const noexcept {return m_transparentTextures.size();}
		};

	}
}