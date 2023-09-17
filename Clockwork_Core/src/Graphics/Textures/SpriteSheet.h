#pragma once
#include "glad\glad.h"
#include <vector>
#include "src\Maths\Vec4.h"
#include "src\Utils\Image.h"
#include "FreeImage\FreeImage.h"

namespace clockwork {
	namespace graphics {

		/*stores a number of images with the same width/height/pixelsize | mostly different textures for the same model to create a TextureArray*/
		class SpriteSheet///VIELLEICHT NOCHMAL NEU MACHEN, ÜBERARBEITEN
		{
		private:
			std::vector<utils::Image> images;

		public:

			/*reserves size for n images in the spritesheet, but doesnt add images*/
			SpriteSheet(unsigned int size=5) noexcept
			{
				images.reserve(size);
			}

			/*adds a single image to the spritesheet and reserves size for n more images*/
			SpriteSheet(const utils::Image& image, unsigned int size = 5) noexcept
			{
				images.reserve(size+1);
				images.push_back(image);
			}

			/*creates a spritesheet from a spritesheet image where the different images are stored in one big image
			the images are saved per x-row from the top left(not like opengl coordinate space) to the bottom right | so the top left to top right row first, then the middel left to middel right row, etc
			@param[image] the spritesheet
			@param[imageWidth] the width of a single small image, NOT THE SPRITESHEET
			@param[imageHeight]the height of a single small image, NOT THE SPRITESHEET*/
			SpriteSheet(const utils::Image& image, unsigned int imageWidth, unsigned int imageHeight) noexcept
			{
				unsigned int xCount = image.getWidth() / imageWidth;
				unsigned int yCount = image.getHeight() / imageHeight;
				images.reserve(xCount*yCount);
				for ( unsigned int y = 0; y < yCount; ++y )
				{
					for ( unsigned int x = 0; x < xCount; ++x )
					{
						images.push_back(image.subImage(x*imageWidth, y*imageHeight, imageWidth, imageHeight));
					}
				}

			}

		public:
			/*returns the number of images stored in the SpriteSheet*/
			const unsigned int getCount() const noexcept{return images.size();}

			/*returns the width of a single small image, NOT THE SPRITESHEET*/
			const unsigned int getImageWidth() const noexcept{return images.at(0).getWidth();}

			/*returns the height of a single small image, NOT THE SPRITESHEET*/
			const unsigned int getImageHeight() const noexcept{return images.at(0).getHeight();}

			/*returns the pixel size of a single small image*/
			const unsigned int getImagePixelSize() const noexcept{return images.at(0).getPixelSize();}

			/*returns an image at the given position in the SpriteSheet(0 to size-1)*/
			const utils::Image& getImage(unsigned int pos) const noexcept{return images.at(pos);}

			/*adds an image to the spritesheet if it has the same width/height and pixelsize as the other images*/
			void addImage(const utils::Image& image) noexcept
			{
				if ( images.size() < 1 )
					images.push_back(image);
				else if ( image.getWidth() == images.at(0).getWidth() && image.getHeight() == images.at(0).getHeight() && image.getPixelSize() == images.at(0).getPixelSize() )
					images.push_back(image);
			}

		};

	}
}
