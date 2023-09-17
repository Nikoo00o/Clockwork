#pragma once
#include "Helper.h"
#include "FreeImage\FreeImage.h"
#include <string>

namespace clockwork {
	namespace utils {

		class Image
		{

		private:
			FIBITMAP* m_img;//pointer to image bitmap
			FREE_IMAGE_FORMAT m_format;//image format(png,jpg,etc)
			std::string m_filepath;//filepath to compare
			mutable unsigned int m_subImageCount;//for subimage filepath
			unsigned int m_width;
			unsigned int m_height;
			unsigned int m_pixelSize;
			bool m_hasAlpha;

		public:
			/*creates an empty image with no filepath and no image data and no format*/
			Image() noexcept;

			/*creates an empty image object with a filepath relative to the engine.exe that should point to an image but it has no image data and no fileformat
			for loading the imagedata of the image into the imageobject, YOU HAVE TO CALL the method load()*/
			explicit Image(const std::string& filepath) noexcept;

			/*copies the image data*/
			Image(const Image& other) noexcept;

			/*moves the data of the other image object to this image object and removes the access to the data in the other image*/
			Image(Image&& other) noexcept;

			/*deletes the image data*/
			~Image() noexcept;

			/*copies the image data*/
			Image& operator=(const Image& other) noexcept;

			/*moves the data of the other image object to this image object and removes the access to the data in the other image*/
			Image& operator=(Image&& other) noexcept;

		public:
			/*the imagedata is stored in colour values in either RGB, or BGR plattform dependant(BGR for little endian processor windows/linux and RGB for big endian processor linux/unix/mac)
			this method will return the opengl integer for the current colour order of the image for textures without alpha channel
			GL_RGB = 6407 | GL_BGR = 32992*/
			static int getColourOrderRGB() noexcept;
			/*the imagedata is stored in colour values in either RGBA, or BGRA plattform dependant(BGR for little endian processor windows/linux and RGB for big endian processor linux/unix/mac)
			this method will return the opengl integer for the current colour order of the image for textures with alpha channel
			GL_RGBA = 6408 | GL_BGRA = 32993*/
			static int getColourOrderRGBA() noexcept;

		public:
			/*loads the image data of the image file with the given filepath into the image object
			sets the fileformat to the format of the image file at the given path and will use it to load the data*/
			Image& load() noexcept;

			/*saves the image data of the image object into the image file with the given filepath
			there has to be image data in the image object, a filepath has to be specified and the image format has to be set(either by calling load, or setting it) */
			Image& save() noexcept;

			/*returns an image cut out of the current image with the specified rectangle dimension | width and height are the count of pixels and x and y are the start positions of the new image | the image coordinate space starts at the top left 0,0 to the bottom right
			positions: pixel at position x,y to pixel at position x+width-1,y+height-1 | the positions are from 0 to width/height-1 where 0,0 is the first pixel of the image and width-1,height-1 is the last pixel of the image
			the filepath of the subimage will be the same as the filepath of the parent image with the subimagecount of the parent image added as a number to the string | the subimagecount of the image object will raise from 0 per subimage taken 
			you have to load the new image after calling this method with load(), otherwise it will not have any data*/
			Image subImage(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const noexcept;

			/*returns the data of the image as an unsigned char pointer(==bytes) | array of pixel with size of width*height representing the colour values in either RGB/RGBA, or BGR/BGRA plattform dependant(BGR for little endian processor windows/linux and RGB for big endian processor linux/unix/mac)*/
			unsigned char* const getData() const noexcept;

			/*changes the image data of the imageobject to another bitmap | array of pixel with size of width*height representing the colour values in either RGB/RGBA, or BGR/BGRA plattform dependant(BGR for little endian processor windows/linux and RGB for big endian processor linux/unix/mac)
			the image data pointer will point to the same data as the data pointer*/
			Image& setData(FIBITMAP* const data) noexcept;

			/*returns the width of the image in pixel(count of pixels) | positions: pixel 0 to getWidth()-1 */
			const unsigned int getWidth() const noexcept;

			/*returns the height of the image in pixel(count of pixels) | positions: pixel 0 to getHeight()-1*/
			const unsigned int getHeight() const noexcept;

			/*returns the size of one pixel in the bitmap of the image object in bits | the colour value is saved per pixel, so 24 = RGB and 32 = RGBA*/
			const unsigned int getPixelSize() const noexcept;

			/*returns the size of the image: getWidth()*getHeight()*getPixelSize()*/
			const unsigned int getSize() const noexcept;

			/*returns if the image is transparent/has alpha value, so the pixelsize is greater than 24*/
			const bool hasAlpha() const noexcept;

		public:
			/*compares 2 images if they display the same pixels by comparing the filepaths*/
			friend bool operator==(const Image& img1, const Image& img2) noexcept;

		public:
		    /*returns the filepath of the image object relative to the engine.exe*/
			const std::string& getFilepath() const noexcept{return m_filepath;}

			/*returns  the file format of the image object */
			const FREE_IMAGE_FORMAT getFormat() const noexcept{return m_format;}

			/*changes the filepath of the image object relative to the engine.exe*/
			Image& setFilepath(const std::string& filepath) noexcept;

			/*changes the fileformat of the image object(png, jpg, etc) | good for saving an image, but the file format will automaticly be read when loading an image
	fileformats:
	FIF_UNKNOWN = -1,
	FIF_BMP		= 0,
	FIF_ICO		= 1,
	FIF_JPEG	= 2,
	FIF_JNG		= 3,
	FIF_KOALA	= 4,
	FIF_LBM		= 5,
	FIF_IFF = FIF_LBM,
	FIF_MNG		= 6,
	FIF_PBM		= 7,
	FIF_PBMRAW	= 8,
	FIF_PCD		= 9,
	FIF_PCX		= 10,
	FIF_PGM		= 11,
	FIF_PGMRAW	= 12,
	FIF_PNG		= 13,
	FIF_PPM		= 14,
	FIF_PPMRAW	= 15,
	FIF_RAS		= 16,
	FIF_TARGA	= 17,
	FIF_TIFF	= 18,
	FIF_WBMP	= 19,
	FIF_PSD		= 20,
	FIF_CUT		= 21,
	FIF_XBM		= 22,
	FIF_XPM		= 23,
	FIF_DDS		= 24,
	FIF_GIF     = 25,
	FIF_HDR		= 26,
	FIF_FAXG3	= 27,
	FIF_SGI		= 28,
	FIF_EXR		= 29,
	FIF_J2K		= 30,
	FIF_JP2		= 31,
	FIF_PFM		= 32,
	FIF_PICT	= 33,
	FIF_RAW		= 34,
	FIF_WEBP	= 35,
	FIF_JXR		= 36*/
			Image& setFormat(int format) noexcept;

			/*clears the image data, so you have more free space | you can not use the image data anymore, but you can still use the size/filepath for textures */
			void clearData() noexcept;

		};

	}
}