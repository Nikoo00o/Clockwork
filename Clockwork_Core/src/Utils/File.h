#pragma once
#include "Helper.h"
#include <string>


#include <fstream>//später nur in cpp und hier noch sachen anpassen
#include <sstream>



namespace clockwork {
	namespace utils {

		class File
		{

		private:
			std::string m_data;
			std::string m_filepath;

		public:
			/**/
			File() noexcept
			{

			}

			/**/
			File(const std::string& filepath) noexcept
			{
				m_filepath = filepath;
			}


		public:
			/**/
			File& read() noexcept
			{
				m_data = static_cast< std::stringstream const& >( std::stringstream() << std::ifstream(m_filepath).rdbuf() ).str();
				return *this;
			}

			/**/
			File& write() noexcept
			{
				return *this;
			}

		public:
			/**/
			const std::string& getData() const noexcept{return m_data;}

		};

	}
}