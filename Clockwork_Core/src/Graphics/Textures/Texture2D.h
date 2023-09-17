#pragma once
#include "glad\glad.h"
#include "FreeImage\FreeImage.h"
#include "src\Utils\Image.h"
#include "src\Maths\Vec4.h"

namespace clockwork {
	namespace graphics {

		/*a default 2dtexture to paint a model with an image | the vertices of the model need 2d texture coordinates to tell opengl what part of the image should be displayed between the vertices and each pair of (3) vertices cuts a triangle out of the texture image to display between the model vertices
		texture coordinates are needed to tell each vertex of a model which part of the texture it corresponds to(called sampling) where the range of texture coords is from 0,0 at the bottom left to 1,1 at the top right corner of the image 
		so a 2d triangle with 3 vertices with the texture coordinates 0,0; 0.5,1 and 1,0 would have as a texture a triangle cut out of the image from the bottom left to the top middle to the bottom right corner of the image | texture coordinates are independent from position coordinates
		each model can have multiple textures that can be calculated in the shaders, but each texture has to be bound first
		
		the normal texture2d is used for few big models without instancing*/
		class Texture2D
		{

		private:
			GLuint m_id;
			utils::Image m_image;//image to compare textures | ggf verändern und nicht mehr img speichern, sondern dateipfad, damit Image gelöscht werden kann | mal gucken wie, wo und wann image loaded werden soll und für texturearrays auch spritesheet überarbeiten

		public:
			/*creates a texture2D object that represents the image and binds it, so another bind() call is unnecessary
			also sets the texture parameters for the texture object | here its a GL_TEXTURE_2D
			@param[textureRepeat] the behavior how to repeat the image when texture coordinates are outside the range of the image(0,0 to 1,1), for example 2,2 
			texture coordinates are needed to tell each vertex of a model which part of the texture it corresponds to(called sampling) where the range of texture coords is from 0,0 at the bottom left to 1,1 at the top right of the image 
			so a 2d triangle with 3 vertices with the texture coordinates 0,0; 0.5,1 and 1,0 would have as a texture a triangle cut out of the image from the bottom left to the top middle to the bottom right corner of the image | texture coordinates are independent from position coordinates
			GL_REPEAT=10497 normal repeat, GL_MIRRORED_REPEAT=33648 mirrors the image with each repeat, GL_CLAMP_TO_EDGE=33071 the edges of the image are streched outside the range, GL_CLAMP_TO_BORDER=33069 border colour fills the space outside the range 
			you should use GL_CLAMP_TO_EDGE when using a texture once for a model(not repeating it over and over again) and otherwise GL_REPEAT(with model texture coordinates outside the range of the texture 0 to 1) | you should also use GL_CLAMP_TO_EDGE for transparent textures with an alpha channel
			because with GL_REPEAT the pixels on the borders of the image are linear mixed with each other and that will look bad when its not used with a repeating texture like a terrain
			@param[borderColour] the colour of the border for the parameter GL_CLAMP_TO_BOARDER as a vec4 of floats | the default is black(0,0,0,0)
			@param[textureFilterUpscale] how opengl chooses the pixels from an image when upscaling textures/images | large model/many texture coordinates, low resolution/little pixel
			texture coordinates do not depend on resolution but can be any floating point value and opengl figures out which texture pixel(textel) to map the texture coordinate to (texture coordinates can be between pixels and not exactly on one pixel) | so with large objects and low resolution textures texture filtering is important because the texture coordinates of the large model
			can be between 4 pixels of the low resolution image and opengl has to decide which pixel to show on the model | so there are more texture coordinates and they are more specific than the low pixels(for example 16 pixel image for a model with 100 vertices each with its own texture coordinate = many texture coordinates between pixels and not exacly on one pixel) 
			GL_NEAREST=9728 selects the whole pixel of the image which center is closest to the texture coordinate of the model for a for a blocked pattern where each pixel is clearly visible(8 bit look with sharp corners)
			GL_LINEAR=9729 mixes the colours of the nearest pixels depending on the distance to the texture coordinate of the model to a new output colour for a more realistic output with a smoother pattern where the individual pixels are less visible
			@param[textureFilterDownscale] how opengl chooses the pixels and how opengl chooses the right mipmap from an image when downscaling textures/images | small model/little texture coordinates, high resolution/many pixel
			Mipmaps are collections of texture images where each texture is twice as small as the previous one, so opengl can use the right mipmap texture that best suits the distance to the object and the size of the object | a smaller resolution on smaller objects is not noticeable and its good for performance
			so its good for a high resolution texture on a small object, or a far distant object(because objects with a bigger distance to the viewer are also automaticly smaller) and opengl can pick the right mipmap texture and therefor the right colours for each pixel
			mipmap levels can also be filtered like scaling textures/texture filtering
			GL_NEAREST_MIPMAP_NEAREST=9984 takes the nearest mipmap to mach the pixel size and chooses the nearest pixel like GL_NEAREST
			GL_LINEAR_MIPMAP_NEAREST=9985 takes the nearest mipmap to mach the pixel size and mixes the nearest pixels like GL_LINEAR
			GL_NEAREST_MIPMAP_LINEAR=9986 mixes the two closest mipmaps to the pixel size(linearly interpolates between the two mipmaps) and chooses the nearest pixel like GL_NEAREST
			GL_LINEAR_MIPMAP_LINEAR=9987 mixes the two closest mipmaps to the pixel size(linearly interpolates between the two mipmaps) and mixes the nearest pixel like GL_LINEAR*/
			explicit Texture2D(const utils::Image& image, GLint textureRepeat = GL_CLAMP_TO_EDGE, const maths::Vec4<float>& borderColour = maths::Vec4<float>(0, 0, 0, 0), GLint textureFilterUpscale = GL_LINEAR, GLint textureFilterDownscale = GL_NEAREST_MIPMAP_LINEAR) noexcept///bei anderen klassen alles mit 2d durch 3d, 2darray, etc ersetzen und kommentare auch bei texturearrray ergänzen
				: m_image(image)
			{
#if CLOCKWORK_DEBUG
				if ( image.getData() == nullptr )
					std::cout << "Error Texture2D::Texture2D(): Image has no data" << std::endl;
#endif
				glGenTextures(1, &m_id);//generate texture in opengl state machine and save id 
				glBindTexture(GL_TEXTURE_2D, m_id);//like other objects bind the texture to modify and access it 

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureRepeat);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureRepeat);
				float colour[4] = { borderColour.r,borderColour.g, borderColour.b , borderColour.a };
				glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, colour);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilterUpscale);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilterDownscale);

				if ( m_image.hasAlpha())//look at pixelsize to guess the colour format for the image
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.getWidth(), m_image.getHeight(), 0, utils::Image::getColourOrderRGBA(), GL_UNSIGNED_BYTE, static_cast<void*>( m_image.getData() ));//7. input colour format of the image(RGB/RGBA), 8. input datatype of the image, 9. pointer to image data
				else
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_image.getWidth(), m_image.getHeight(), 0, utils::Image::getColourOrderRGB(), GL_UNSIGNED_BYTE, static_cast<void*>( m_image.getData() ));//1. texture target(mostly texture_2d, so 1d and 3d are not affected), 2. mipmap lvl to create the texture for(base lvl at 0), 3. output colour format of the image(RGB/RGBA), 4./5. width/height of the image, 6. always 0(legacy opengl)
				glGenerateMipmap(GL_TEXTURE_2D);//activate mipmaps for the currently bound texture object | like calling the function from above with diffrent positions for the mipmap as second parameter instead of 0 and changing width/height
				m_image.clearData();
			}

			/*creates an empty texture with no texturedata and no id*/
			Texture2D()
				: m_id(0)
			{}

			/*deletes the Textureid in the opengl state machine*/
			~Texture2D() noexcept
			{
				glDeleteTextures(1, &m_id);
			}

			Texture2D(const Texture2D&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			Texture2D(Texture2D&& other) noexcept
				: m_id(other.m_id), m_image(std::move(other.m_image))
			{
				other.m_id = 0;
			}

			Texture2D& operator=(const Texture2D&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			Texture2D& operator=(Texture2D&& other) noexcept
			{
				m_id = other.m_id;
				m_image = std::move(other.m_image);
				other.m_id = 0;
				return *this;
			}

		public:
			/*binds the current texture2d object to the selected texture slot where the default slot is 0 | there can only be one texture bound per texture slot at the same time | so there can be 32 textures be bound at the same time to use for rendering a single model
			the shader has to be enabled first, but the texture should be bound before binding the model, so the texture can be applied to the model | the texture bind call is just for this texture kind(GL_TEXTURE_2D)
			there can be multiple textures bound at the same time(even of the same texture kind), if they are bound at a diffrent location(number) | the location is shared with all the other texture kinds, so you cant bind 2 diffrent texturekinds to the same location
			all(maximum 32) bound textures in diffrent slots can be accessed in the shader with a position at the same time and can be calculated in the fragment shader  | you have to define multiple "uniform sampler2DArray name"(2d just in this case because of texturearray2d) with diffrent names in the fragmentshader
			so you can work with the textures under diffrent names in the fragment shader | but you have to connect the shader names and the texture slots with shadername.setUniform(texture name in shader, texture slot number); in the main programm(after the shader is enabled only once)
			for each texture slot that you might wanna use with a diffrent name in the shader as an alias for the texture slot
			@param[number] 0-31 range for the first texture slot to the last texture slot*/
			void bind(unsigned char number=0) const noexcept
			{
				glActiveTexture(GL_TEXTURE0+number);
				glBindTexture(GL_TEXTURE_2D, m_id);
			}

			/*unbinds all textures of the texture kind of this class, but does not affect the other texture kinds*/
			void unbind() const noexcept
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}

		public:
			/*returns the image of the texture with the filepath, size, etc | CAREFUL: the image will have no imagedata, because it will have been cleared*/
			const utils::Image& getImage() const noexcept {return m_image;}

		};

	}
}