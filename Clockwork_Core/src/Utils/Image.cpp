#include "Image.h"


namespace clockwork {
	namespace utils {

		Image::Image() noexcept
			: m_img(nullptr), m_format(FIF_UNKNOWN), m_subImageCount(0), m_width(0), m_height(0), m_pixelSize(0), m_hasAlpha(false)
		{}

		Image::Image(const std::string& filepath) noexcept
			: m_img(nullptr), m_format(FIF_UNKNOWN), m_filepath(filepath), m_subImageCount(0), m_width(0), m_height(0), m_pixelSize(0), m_hasAlpha(false)
		{

		}

		Image::Image(const Image& other) noexcept
			: m_img(FreeImage_Copy(other.m_img, 0, 0, other.getWidth(), other.getHeight())), m_format(other.m_format), m_filepath(other.m_filepath), m_subImageCount(other.m_subImageCount), m_width(other.m_width), m_height(other.m_height), m_pixelSize(other.m_pixelSize), m_hasAlpha(other.m_hasAlpha)
		{}

		Image::Image(Image&& other) noexcept
			: m_img(other.m_img), m_format(other.m_format), m_filepath(other.m_filepath), m_subImageCount(other.m_subImageCount), m_width(other.m_width), m_height(other.m_height), m_pixelSize(other.m_pixelSize), m_hasAlpha(other.m_hasAlpha)
		{
			other.m_img = nullptr;
			other.m_format = FIF_UNKNOWN;
		}

		Image::~Image() noexcept
		{
			if ( m_img )
				FreeImage_Unload(m_img);//free FreeImages copy of the image data
		}

		Image& Image::operator=(const Image& other) noexcept
		{
			m_img = FreeImage_Copy(other.m_img, 0, 0, other.m_width, other.m_height);
			m_format = other.m_format;
			m_filepath = other.m_filepath;
			m_subImageCount = other.m_subImageCount;
			m_width = other.m_width;
			m_height = other.m_height;
			m_pixelSize = other.m_pixelSize;
			m_hasAlpha = other.m_hasAlpha;
			return *this;
		}

		Image& Image::operator=(Image&& other) noexcept
		{
			m_img = other.m_img;
			m_format = other.m_format;
			m_filepath = other.m_filepath;
			m_subImageCount = other.m_subImageCount;
			m_width = other.m_width;
			m_height = other.m_height;
			m_pixelSize = other.m_pixelSize;
			m_hasAlpha = other.m_hasAlpha;
			other.m_img = nullptr;
			other.m_format = FIF_UNKNOWN;
			return *this;
		}

		int Image::getColourOrderRGB() noexcept
		{
#if FREEIMAGE_COLORORDER == 0
			return 32992;
#else
			return 6407;
#endif
		}

		int Image::getColourOrderRGBA() noexcept
		{
#if FREEIMAGE_COLORORDER == 0
			return 32993;
#else
			return 6408;
#endif
		}

		Image& Image::load() noexcept
		{
			m_format = FreeImage_GetFileType(m_filepath.c_str(), 0);//check file signature and deduce its format
			if ( m_format == FIF_UNKNOWN )
				m_format = FreeImage_GetFIFFromFilename(m_filepath.c_str());//if still unknown try to guess file format from file extension
			m_img = FreeImage_Load(m_format, m_filepath.c_str());//load image 
#if CLOCKWORK_DEBUG
			if ( m_format == FIF_UNKNOWN )
				std::cout << "Failed to load Image(unknown format): " << m_filepath << std::endl;
			if ( !FreeImage_FIFSupportsReading(m_format) )
				std::cout << "Failed to load Image(plugin has no reading capabilities): " << m_filepath << std::endl;
#endif
			if ( m_img )
				FreeImage_Unload(m_img);//free FreeImages copy of the image data
			m_img = FreeImage_Load(m_format, m_filepath.c_str());//load image 
#if CLOCKWORK_DEBUG
			if ( !m_img )
				std::cout << "Failed to load Image(unknown error): " << m_filepath << std::endl;
#endif
			m_width = FreeImage_GetWidth(m_img);
			m_height = FreeImage_GetHeight(m_img);
			m_pixelSize = FreeImage_GetBPP(m_img);
			m_hasAlpha = m_pixelSize > 24;
			return *this;
		}

		Image& Image::save() noexcept
		{
#if CLOCKWORK_DEBUG
			if ( m_filepath.length()<3 )
				std::cout << "Failed to save Image(unknown filepath): " << m_filepath << std::endl;
			if ( m_format==FIF_UNKNOWN )
				std::cout << "Failed to save Image(unknown format): " << m_filepath << std::endl;
			if ( !m_img )
				std::cout << "Failed to load Image(no image data): " << m_filepath << std::endl;
#endif
			FreeImage_Save(m_format, m_img, m_filepath.c_str());
			return *this;
		}

		Image Image::subImage(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const noexcept
		{
			return Image { m_filepath + std::to_string(m_subImageCount++) }.setFormat(m_format).setData(FreeImage_Copy(m_img, x, y, x + width, y + height));
		}

		unsigned char* const Image::getData() const noexcept
		{
#if CLOCKWORK_DEBUG
			if(m_img==nullptr )
				std::cout << "Error Image::getData: the image has no data " << m_filepath << std::endl;
#endif
			return FreeImage_GetBits(m_img);
		}

		Image& Image::setData(FIBITMAP* const data) noexcept
		{
			m_img = data;
			return *this;
		}

		const unsigned int Image::getWidth() const noexcept
		{
			return m_width;
		}

		const unsigned int Image::getHeight() const noexcept
		{
			return m_height;
		}

		const unsigned int Image::getPixelSize() const noexcept
		{
			return m_pixelSize;
		}

		const unsigned int Image::getSize() const noexcept
		{
			return m_width * m_height*m_pixelSize;
		}

		const bool Image::hasAlpha() const noexcept
		{
			return m_hasAlpha;
		}

		Image& Image::setFilepath(const std::string& filepath) noexcept
		{
			m_filepath = filepath;
			return *this;
		}

		Image& Image::setFormat(int format) noexcept
		{
			m_format = static_cast< FREE_IMAGE_FORMAT >( format );
			return *this;
		}

		void Image::clearData() noexcept
		{
			if ( m_img )
			{
				FreeImage_Unload(m_img);//free FreeImages copy of the image data
				m_img = nullptr;
			}
		}

		bool operator==(const Image& img1, const Image& img2) noexcept
		{
			if ( img1.m_filepath == img2.m_filepath )
				return true;
			else
				return false;
		}

	}
}