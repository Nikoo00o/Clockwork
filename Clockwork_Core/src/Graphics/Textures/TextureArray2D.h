#pragma once
#include "glad\glad.h"
#include <vector>
#include "src\Maths\Vec4.h"
#include "src\Utils\Image.h"
#include "FreeImage\FreeImage.h"
#include "src\Graphics\Textures\SpriteSheet.h"
#include "src\Maths\MathFunctions.h"
#include "src\Graphics\Buffers\FrameBuffer.h"


namespace clockwork {
	namespace graphics {

		/*a default array of 2dtextures to paint a model with an image | the vertices of the model need 2d texture coordinates to tell opengl what part of the image should be displayed between the vertices and each pair of (3) vertices cuts a triangle out of the texture image to display between the model vertices
		texture coordinates are needed to tell each vertex of a model which part of the texture it corresponds to(called sampling) where the range of texture coords is from 0,0 at the bottom left to 1,1 at the top right corner of the image
		so a 2d triangle with 3 vertices with the texture coordinates 0,0; 0.5,1 and 1,0 would have as a texture a triangle cut out of the image from the bottom left to the top middle to the bottom right corner of the image | texture coordinates are independent from position coordinates
		each model can have multiple textures that can be calculated in the shaders, but each texture has to be bound first

		the texturearray2d is used for many small models with instancing | CAREFUL: the size of every image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level)
		there are multiple textures stored in the texturearray at a position from 0 to size-1, where the position of the image also is its imageId/textureid to access it in the fragmentshader
		in the fragmentshader an image of the texturearray2d is drawn with a given position(imageId/textureid) in the array | the imageId/textureid is used to specify what texture to draw and is stored per model instance/object*/
		class TextureArray2D
		{

		private:
			GLuint m_id;
			std::vector<utils::Image> m_images;
			unsigned int m_bufferSize;
			GLint m_textureRepeat; 
			maths::Vec4f m_borderColour;
			GLint m_textureFilterUpscale;
			GLint m_textureFilterDownscale;
			static FrameBuffer* m_readBuffer;
			static FrameBuffer* m_drawBuffer;

		public:
			/*creates an empty texturearray2d where you can add images to and binds it, so another bind() call is unnecessary
			also sets the texture parameters for the texture object | here its a GL_TEXTURE_2D_ARRAY
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
			explicit TextureArray2D(unsigned int reserved, GLint textureRepeat = GL_CLAMP_TO_EDGE, const maths::Vec4<float>& borderColour = maths::Vec4<float>(0, 0, 0, 0), GLint textureFilterUpscale = GL_LINEAR, GLint textureFilterDownscale = GL_NEAREST_MIPMAP_LINEAR) noexcept
				: m_textureRepeat(textureRepeat), m_borderColour(borderColour), m_textureFilterUpscale(textureFilterUpscale), m_textureFilterDownscale(textureFilterDownscale)
			{
				glGenTextures(1, &m_id);//generate texture in opengl state machine and save id 
				glBindTexture(GL_TEXTURE_2D_ARRAY, m_id);//like other objects bind the texture array to modify and access it 

				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, textureRepeat);
				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, textureRepeat);
				float colour[4] = { borderColour.r,borderColour.g, borderColour.b , borderColour.a };
				glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, colour);
				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, textureFilterUpscale);
				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, textureFilterDownscale);

				m_images.reserve(reserved);
				m_bufferSize = reserved;
			}

			/*creates an empty texturearray2d with no data and no id*/
			TextureArray2D() noexcept
				: m_id(0), m_bufferSize(0)
			{}

			/*deletes the TextureArrayId in the opengl state machine*/
			~TextureArray2D() noexcept
			{
				if(m_id!=0 )
					glDeleteTextures(1, &m_id);
			}

			TextureArray2D(const TextureArray2D&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			TextureArray2D(TextureArray2D&& other) noexcept
				: m_id(other.m_id), m_images(std::move(other.m_images)), m_bufferSize(other.m_bufferSize), m_textureRepeat(other.m_textureRepeat), m_borderColour(other.m_borderColour), m_textureFilterUpscale(other.m_textureFilterUpscale), m_textureFilterDownscale(other.m_textureFilterDownscale)
			{
				other.m_id = 0;
			}

			TextureArray2D& operator=(const TextureArray2D&) = delete;

			/*copies the unique id and resets the id of the moved object*/
			TextureArray2D& operator=(TextureArray2D&& other) noexcept
			{
				if(m_id!=0 )
					glDeleteTextures(1, &m_id);
				m_id = other.m_id;
				other.m_id = 0;
				m_images = std::move(other.m_images);
				m_bufferSize = other.m_bufferSize;
				m_textureRepeat = other.m_textureRepeat;
				m_borderColour = other.m_borderColour;
				m_textureFilterUpscale = other.m_textureFilterUpscale;
				m_textureFilterDownscale = other.m_textureFilterDownscale;
				return *this;
			}

		private:
			void addImage(const utils::Image& image) noexcept
			{
				if ( image.hasAlpha() )//look at pixelsize to guess the colour format for the image
				{
					if ( m_images.empty() )
					{
						glBindTexture(GL_TEXTURE_2D_ARRAY, m_id);
						glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, image.getWidth(), image.getHeight(), m_bufferSize, 0, utils::Image::getColourOrderRGBA(), GL_UNSIGNED_BYTE, nullptr);
					}
					else if ( m_images.size() >= m_bufferSize )
					{
						++m_bufferSize;
						m_bufferSize *= 2;
						TextureArray2D temp { 0,m_textureRepeat,m_borderColour,m_textureFilterUpscale,m_textureFilterDownscale };
						glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, image.getWidth(), image.getHeight(), m_bufferSize, 0, utils::Image::getColourOrderRGBA(), GL_UNSIGNED_BYTE, nullptr);

						m_readBuffer->bind();
						m_drawBuffer->bind();
						for ( unsigned int i = 0; i < m_images.size(); ++i )
						{
							glFramebufferTextureLayer(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_id, 0, i);
							glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, temp.m_id, 0, i);
							glBlitFramebuffer(0, 0, image.getWidth(), image.getHeight(), 0, 0, image.getWidth(), image.getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
						}
						this->m_id = temp.m_id;
						temp.m_id = 0;
						m_readBuffer->unbind();
						m_drawBuffer->unbind();
					}
					glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, m_images.size(), image.getWidth(), image.getHeight(), 1, utils::Image::getColourOrderRGBA(), GL_UNSIGNED_BYTE, image.getData());
				}
				else
				{
					if ( m_images.empty() )
					{
						glBindTexture(GL_TEXTURE_2D_ARRAY, m_id);
						glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, image.getWidth(), image.getHeight(), m_bufferSize, 0, utils::Image::getColourOrderRGB(), GL_UNSIGNED_BYTE, nullptr);
					}
					else if ( m_images.size() >= m_bufferSize )
					{
						++m_bufferSize;
						m_bufferSize *= 2;
						TextureArray2D temp { 0,m_textureRepeat,m_borderColour,m_textureFilterUpscale,m_textureFilterDownscale };
						glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, image.getWidth(), image.getHeight(), m_bufferSize, 0, utils::Image::getColourOrderRGB(), GL_UNSIGNED_BYTE, nullptr);

						m_readBuffer->bind();
						m_drawBuffer->bind();
						for ( unsigned int i = 0; i < m_images.size(); ++i )
						{
							glFramebufferTextureLayer(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_id, 0, i); 
							glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, temp.m_id, 0, i);
							glBlitFramebuffer(0, 0, image.getWidth(), image.getHeight(), 0, 0, image.getWidth(), image.getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
						}
						this->m_id = temp.m_id;
						temp.m_id = 0;
						m_readBuffer->unbind();
						m_drawBuffer->unbind();
					}
					glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, m_images.size(), image.getWidth(), image.getHeight(), 1, utils::Image::getColourOrderRGB(), GL_UNSIGNED_BYTE, image.getData());
				}
				glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
				m_images.push_back(image);
				m_images.back().clearData();
			}

		public:

			friend void initTextures();

			/*binds the current texturearray2d object to the selected texture slot where the default slot is 0 | there can only be one texture bound per texture slot at the same time | so there can be 32 textures be bound at the same time to use for rendering a single model
			the shader has to be enabled first, but the texture should be bound before binding the model, so the texture can be applied to the model | the texture bind call is just for this texture kind(GL_TEXTURE_2D_ARRAY)
			there can be multiple textures bound at the same time(even of the same texture kind), if they are bound at a diffrent location(number) | the location is shared with all the other texture kinds, so you cant bind 2 diffrent texturekinds to the same location
			all(maximum 32) bound textures in diffrent slots can be accessed in the shader with a position at the same time and can be calculated in the fragment shader  | you have to define multiple "uniform sampler2DArray name"(2d just in this case because of texturearray2d) with diffrent names in the fragmentshader
			so you can work with the textures under diffrent names in the fragment shader | but you have to connect the shader names and the texture slots with shadername.setUniform(texture name in shader, texture slot number); in the main programm(after the shader is enabled only once)
			for each texture slot that you might wanna use with a diffrent name in the shader as an alias for the texture slot
			@param[number] 0-31 range for the first texture slot to the last texture slot*/
			void bind(unsigned char number = 0) const noexcept
			{
				glActiveTexture(GL_TEXTURE0 + number);
				glBindTexture(GL_TEXTURE_2D_ARRAY, m_id);
			}

			/*unbinds all textures of the texture kind of this class, but does not affect the other texture kinds*/
			void unbind() const noexcept
			{
				glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
			}

			/*returns the imageId/textureid in relation to the position of the image in the texturearray2d
			if the image already is in the texturearray2d, its position will be returned, otherwise the image will also be added to the texturearray2d
			CAREFUL: the size of the new image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level)
			the imageId/position/textureid range is from 0 to size-1
			the texturearray will be bound after this method*/
			int getTextureId(const utils::Image& image) noexcept
			{
#if CLOCKWORK_DEBUG
				if ( image.getData() == nullptr )
					std::cout << "Error TextureArray2D::getTextureId(): Image has no data" << std::endl;
#endif
#if CLOCKWORK_DEBUG
				if ( m_images.size() > 0 && m_images.at(0).getSize() != image.getSize() )
					std::cout << "Error TextureArray2D::getTextureId(): the new image has not the same size as the other images in the texturearray" << std::endl;
#endif 
				for ( unsigned int i = 0; i < m_images.size(); ++i )
				{
					if ( m_images.at(i).getFilepath() == image.getFilepath() )
						return i;
				}
				addImage(image);
				return m_images.size() - 1;
			}

			/*returns the imageId/position/textureid of an image with the same imagepath in the texturearray2d if the texturearray2d contains an image with the same imagepath
			otherwise an image objekt will be loaded from the imagepath and it will be stored in the texturearray2d
			CAREFUL: the size of the new image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level)
			the imageId/position/textureid range is from 0 to size-1
			the texturearray will be bound after this method*/
			int getTextureId(const std::string& imagePath) noexcept
			{
				for ( unsigned int i = 0; i < m_images.size(); ++i )
				{
					if ( m_images.at(i).getFilepath() == imagePath )
						return i;
				}
				utils::Image image(imagePath);
				image.load();
#if CLOCKWORK_DEBUG
				if ( image.getData() == nullptr )
					std::cout << "Error TextureArray2D::getTextureId(): Image has no data" << std::endl;
#endif
#if CLOCKWORK_DEBUG
				if ( m_images.size() > 0 && m_images.at(0).getSize() != image.getSize() )
					std::cout << "Error TextureArray2D::getTextureId(): the new image has not the same size as the other images in the texturearray" << std::endl;
#endif 
				addImage(image);
				return m_images.size() - 1;
			}

			/*adds an image/texture(that is not in the texturearray) to the texturearray2d | dont add an image that already is in the texturearray, because then 2 identical images/textures would be in the texturearray2d 
			CAREFUL: the size of the new image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level)
			the texturearray will be bound after this method*/
			void addTexture(const utils::Image& image) noexcept
			{
#if CLOCKWORK_DEBUG
				if ( image.getData() == nullptr )
					std::cout << "Error TextureArray2D::addTexture(): Image has no data" << std::endl;
#endif
#if CLOCKWORK_DEBUG
				if ( m_images.size() > 0 && m_images.at(0).getSize() != image.getSize() )
					std::cout << "Error TextureArray2D::addTexture(): the new image has not the same size as the other images in the texturearray" << std::endl;
#endif 
#if CLOCKWORK_DEBUG
				for ( unsigned int i = 0; i < m_images.size(); ++i )
				{
					if ( m_images.at(i).getFilepath() == image.getFilepath() )
					{
						std::cout << "Error TextureArray2D::addTexture(): an image with the same imagepath already is in the texturearray2d" << std::endl;
						return;
					}
				}
#endif 
				addImage(image);
			}

			/*adds an image/texture(that is not in the texturearray) to the texturearray2d | dont add an image that already is in the texturearray, because then 2 identical images/textures would be in the texturearray2d 
			CAREFUL: the size of the new image has to be the same as the size of the other images and the pixelkind has to be the same too(rgb/rgba = same transparancy level)
			the texturearray will be bound after this method*/
			void addTexture(const std::string& imagePath) noexcept
			{
#if CLOCKWORK_DEBUG
				for ( unsigned int i = 0; i < m_images.size(); ++i )
				{
					if ( m_images.at(i).getFilepath() == imagePath )
					{
						std::cout << "Error TextureArray2D::addTexture(): an image with the same imagepath already is in the texturearray2d" << std::endl;
						return;
					}
				}
#endif 
				utils::Image image(imagePath);
				image.load();
#if CLOCKWORK_DEBUG
				if ( image.getData() == nullptr )
					std::cout << "Error TextureArray2D::addTexture(): Image has no data" << std::endl;
#endif
#if CLOCKWORK_DEBUG
				if ( m_images.size() > 0 && m_images.at(0).getSize() != image.getSize() )
					std::cout << "Error TextureArray2D::addTexture(): the new image has not the same size as the other images in the texturearray" << std::endl;
#endif 
				addImage(image);
			}

			/*removes a texture/image out of the texturearray at the given position*/
			void removeTexture(int textureId) noexcept
			{
#if CLOCKWORK_DEBUG
				if ( m_images.size() <= textureId )
					std::cout << "Error TextureArray2D::removeTexture(): TextureId is not in the texturearray2d" << std::endl;
#endif
				m_images.erase(m_images.begin() + textureId);
				m_readBuffer->bind();
				m_drawBuffer->bind();
				for ( unsigned int i = textureId; i < m_images.size(); ++i )
				{
					glFramebufferTextureLayer(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_id, 0, i + 1);
					glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_id, 0, i);
					glBlitFramebuffer(0, 0, m_images.front().getWidth(), m_images.front().getHeight(), 0, 0, m_images.front().getWidth(), m_images.front().getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
				}
				m_readBuffer->unbind();
				m_drawBuffer->unbind();
			}

			/*removes a texture/image with the same filepath out of the texturearray*/
			void removeTexture(const utils::Image& image) noexcept
			{
#if CLOCKWORK_DEBUG
				if ( image.getData() == nullptr )
					std::cout << "Error TextureArray2D::removeTexture(): Image has no data" << std::endl;
#endif
				for ( unsigned int i = 0; i < m_images.size(); ++i )
				{
					if ( m_images.at(i).getFilepath() == image.getFilepath() )
					{
						removeTexture(i);
						return;
					}
				}
#if CLOCKWORK_DEBUG
				std::cout << "Error TextureArray2D::removeTexture(): Texture Image is not in the texturearray2d" << std::endl;
#endif
			}

			/*removes a texture/image with the same filepath out of the texturearray*/
			void removeTexture(const std::string& imagePath) noexcept
			{
				for ( unsigned int i = 0; i < m_images.size(); ++i )
				{
					if ( m_images.at(i).getFilepath() == imagePath )
					{
						removeTexture(i);
						return;
					}
				}
#if CLOCKWORK_DEBUG
				std::cout << "Error TextureArray2D::removeTexture(): Texture Image is not in the texturearray2d" << std::endl;
#endif
			}

			/*returns true if the texturearray2d contains an image with the same filepath*/
			bool contains(const utils::Image& image) const noexcept
			{
#if CLOCKWORK_DEBUG
				if ( image.getData()==nullptr )
					std::cout << "Error TextureArray2D::contains(): Image has no data" << std::endl;
#endif
				for ( unsigned int i = 0; i < m_images.size(); ++i )
				{
					if ( m_images.at(i).getFilepath() == image.getFilepath() )
						return true;
				}
				return false;
			}

			/*returns true if the texturearray2d contains an image with the same filepath*/
			bool contains(const std::string& imagePath) const noexcept
			{
				for ( unsigned int i = 0; i < m_images.size(); ++i )
				{
					if ( m_images.at(i).getFilepath() == imagePath )
						return true;
				}
				return false;
			}

			/*returns the image at the given imageId/textureid | this image will be visible when using the imageId in the fragment shader
			CAREFUL: this image will have no imagedata, because it will have been cleared!*/
			const utils::Image& getTexture(int textureId) const noexcept
			{
#if CLOCKWORK_DEBUG
				if ( m_images.size() <= textureId )
					std::cout << "Error TextureArray2D::getTexture(): TextureId is not in the texturearray2d" << std::endl;
#endif
				return m_images.at(textureId);
			}

			/*returns the number of images in the texturearray2d*/
			const unsigned int getTextureCount() const noexcept{return m_images.size();}

			/*returns the opengl unique id of the texturearray*/
			const GLuint getId() const noexcept {return m_id;}

		};

	}
}