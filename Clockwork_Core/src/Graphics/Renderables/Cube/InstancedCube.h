#pragma once
#include "src\Graphics\Renderables\Renderable.h"

namespace clockwork {
	namespace logics {
		class GameObject;
	}
	namespace graphics {

		class Renderer;
		class CubeManager;

		/*this is an instanced textured cube for drawing many small models with the same shader
		there will be one model and some textures in the cubemanager and each instancedcube is an instance of this model 
		where the modelmatrix is used to display the instance with its transformation in the world and the textureid is used to display the correct texture
		the instancedcube will have a pointer to a renderer, where a cubemanager will render all instancedcubes that are added to the cubemanager
		the cubemanager can also add a texture to prepare for instancedcubes(textures are also automaticly added when adding instancedcubes), or remove an instancedcube from the render list
		every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures*/
		///NEUE KOMMENTARE | KANN NICHT TRANSPARENT SEIN
		class InstancedCube
			: public Renderable
		{

		private:
			friend class CubeManager;
			friend class Renderer;
			int m_pos;
			bool m_changed;
			CubeManager* m_manager;

		public:

			/*creates an instancedcube that is not added to the cubemanager and will not be rendered | so you have to call add after the constructor to render it 
			dont use this constructor, if the count of textures/images in the texturearray2d of the cubemanager is equal or less than the textureID, because it will give an error
			@param[textureId] the id of the texture in the texturearray2d of the cubemanager that will be used for this model
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[size] the scale of the size of the model
			@param[rotation] the rotation of the model around each axis in degrees
			@param[position] the position of the model
			the modelmatrix of the instance/object will be created out of the 3 vectors and will transform the model into the world
			@param[renderer] a pointer to an instancedrenderer where the cubemanager is stored*/
			InstancedCube(int textureId, logics::GameObject* gameObject, Renderer* renderer) noexcept;

			/*creates an instancedcube that is not added to the cubemanager and will not be rendered | so you have to call add after the constructor to render it 
			@param[imagePath] the path of a texture/image that will be used for this model
			the textureId will be equal to the position of the image in the texturearray2d of the cubemanager and if the image is not already in the texturearray2d, it will be added to it
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[size] the scale of the size of the model
			@param[rotation] the rotation of the model around each axis in degrees
			@param[position] the position of the model
			the modelmatrix of the instance/object will be created out of the 3 vectors and will transform the model into the world
			@param[renderer] a pointer to an instancedrenderer where the cubemanager is stored*/
			InstancedCube(const std::string& imagePath, logics::GameObject* gameObject, Renderer* renderer) noexcept;

			/*creates an instancedcube that is not added to the cubemanager and will not be rendered | so you have to call add after the constructor to render it 
			@param[image] the texture/image that will be used for this model
			the textureId will be equal to the position of the image in the texturearray2d of the cubemanager and if the image is not already in the texturearray2d, it will be added to it
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures
			@param[size] the scale of the size of the model
			@param[rotation] the rotation of the model around each axis in degrees
			@param[position] the position of the model
			the modelmatrix of the instance/object will be created out of the 3 vectors and will transform the model into the world
			@param[renderer] a pointer to an instancedrenderer where the cubemanager is stored*/
			InstancedCube(const utils::Image& image, logics::GameObject* gameObject, Renderer* renderer) noexcept;

			/*removes the instancedcube from the cubemanager, if its currently added to it*/
			~InstancedCube() noexcept;

			InstancedCube(const InstancedCube& other) = delete;

			/*moves the data, removes the old this object from the cubemanager and changes the pointer in the list of the cubemanager from the other object to this object*/
			InstancedCube(InstancedCube&& other) noexcept;

			InstancedCube& operator=(const InstancedCube& other) = delete;

			/*moves the data, removes the old this object from the cubemanager and changes the pointer in the list of the cubemanager from the other object to this object*/
			InstancedCube& operator=(InstancedCube&& other) noexcept;

		public:

			//wird nur von transparentmanager aufgerufen, auch ggf private |  copybuffer muss vorher gebindet werden und es wird ja eh automatisch gemacht vor dem rendern
			void updateBufferData() noexcept;


			/*removes the instancedcube from the cubemanager in the instancedrender | the last instancedcube in the list of the cubemanager will swap positions with this instancedcube and then this instancedcube(then the last instancedcube in the list) will be removed from the list
			calling remove twice will have no effect, because it will check if the cube already is removed | the destructor will also call remove
			use add()/remove() for few changes with many models to hide/show objects/instances and use setVisible(true/false) for many changes with few models
			BUT setvisible will not give a huge performance boost, because the render call will still happen | add/remove will give a performanceboost, because the render call will not happen*/
			void remove() noexcept;

			/*adds the instancedcube to the cubemanager in the instancedrender | the instancedcube will be added to the end of the list
			calling add twice will have no effect, because it will check if the cube already is added | the constructor will not automaticly call add()
			use add()/remove() for few changes with many models to hide/show objects/instances and use setVisible(true/false) for many changes with few models
			BUT setvisible will not give a huge performance boost, because the render call will still happen | add/remove will give a performanceboost, because the render call will not happen*/
			void add() noexcept;


			/*changes the texture of this instancedcube and automaticly updates the buffer(gpu side) in the cubemanager
			dont use this method, if the count of textures/images in the texturearray2d of the cubemanager is equal or less than the textureID, because it will give an error
			@param[textureId] the id of the texture in the texturearray2d of the cubemanager that will be used for this model
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures*/
			void setTexture(int textureId) noexcept;

			/*changes the texture of this instancedcube and automaticly updates the buffer(gpu side) in the cubemanager
			@param[image] the texture/image that will be used for this model
			the textureId will be equal to the position of the image in the texturearray2d of the cubemanager and if the image is not already in the texturearray2d, it will be added to it
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures*/
			void setTexture(const utils::Image& image) noexcept;

			/*changes the texture of this instancedcube and automaticly updates the buffer(gpu side) in the cubemanager
			@param[imagePath] the path of a texture/image that will be used for this model
			the textureId will be equal to the position of the image in the texturearray2d of the cubemanager and if the image is not already in the texturearray2d, it will be added to it
			every texture/image has to be the same size(same resolution and same pixelkind(rgb/rgba), so you have to use the transparentinstancedcube and transparentinstancedcubemanager for transparency textures*/
			void setTexture(const std::string& imagePath) noexcept;

			/*returns the image of the texture in the texturearray at the textureid with size, imagepath, etc | CAREFUL: the image has no imagedata, because it has been cleared*/
			const utils::Image& getTextureImage() noexcept;

			void changeRenderer(Renderer* renderer) noexcept;///changerenderer auch in normalcube machen

			const Renderer* const getRenderer() const noexcept;

		public:
			inline const bool isAdded() const noexcept {return m_pos!=-1;}
			inline const bool hasChanged() const noexcept {return m_changed;}//wahrscheinlich wird es nicht gebraucht
			inline void setChanged(bool changed) noexcept{m_changed=changed;}

		};

	}
}