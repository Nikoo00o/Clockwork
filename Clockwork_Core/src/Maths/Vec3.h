#pragma once
#include <vector>
#include<iostream>
#include <sstream>
#include <cmath>

namespace clockwork {
	namespace maths {

		template<typename type>struct Vec2;
		template<typename type>struct Vec3;
		template<typename type>struct Vec4;
		template<typename type>struct Mat2x2;
		template<typename type>struct Mat2x3;
		template<typename type>struct Mat2x4;
		template<typename type>struct Mat3x2;
		template<typename type>struct Mat3x3;
		template<typename type>struct Mat3x4;
		template<typename type>struct Mat4x2;
		template<typename type>struct Mat4x3;
		template<typename type>struct Mat4x4;

		template<typename type> Vec3<type>&& operator+(Vec3<type>&& v1, Vec2<type>&& v2) noexcept;
		template<typename type> Vec3<type>&& operator+(Vec3<type>&& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec3<type> operator+(const Vec3<type>& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec3<type>&& operator+(Vec3<type>&& v1, Vec4<type>&& v2) noexcept;
		template<typename type> Vec3<type>&& operator+(Vec3<type>&& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec3<type> operator+(const Vec3<type>& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec3<type>&& operator-(Vec3<type>&& v1, Vec2<type>&& v2) noexcept;
		template<typename type> Vec3<type>&& operator-(Vec3<type>&& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec3<type> operator-(const Vec3<type>& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec3<type>&& operator-(Vec3<type>&& v1, Vec4<type>&& v2) noexcept;
		template<typename type> Vec3<type>&& operator-(Vec3<type>&& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec3<type> operator-(const Vec3<type>& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec3<type>&& operator*(Vec3<type>&& v1, Vec2<type>&& v2) noexcept;
		template<typename type> Vec3<type>&& operator*(Vec3<type>&& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec3<type> operator*(const Vec3<type>& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec3<type>&& operator*(Vec3<type>&& v1, Vec4<type>&& v2) noexcept;
		template<typename type> Vec3<type>&& operator*(Vec3<type>&& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec3<type> operator*(const Vec3<type>& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec3<type>&& operator/(Vec3<type>&& v1, Vec2<type>&& v2) noexcept;
		template<typename type> Vec3<type>&& operator/(Vec3<type>&& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec3<type> operator/(const Vec3<type>& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec3<type>&& operator/(Vec3<type>&& v1, Vec4<type>&& v2) noexcept;
		template<typename type> Vec3<type>&& operator/(Vec3<type>&& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec3<type> operator/(const Vec3<type>& v1, const Vec4<type>& v2) noexcept;
		template<typename type>Vec3<type> operator-(Vec3<type> vec) noexcept;

		template<typename type>
		struct Vec3
		{

		public:
			union
			{
				struct
				{
					type x;
					type y;
					type z;
				};
				struct
				{
					type r;
					type g;
					type b;
				};
				struct
				{
					type s;
					type t;
					type p;
				};
				type data[3];
			};

		public:
			//default constructor
			Vec3() noexcept
				:x(0), y(0), z(0)
			{}
			//1 value for all constructor
			explicit Vec3(type val) noexcept
				:x(val), y(val), z(val)
			{}
			//seperate values constructor
			Vec3(type x, type y, type z) noexcept
				:x(x), y(y), z(z)
			{}



			//array constructor
			explicit Vec3(const type(&arr)[3]) noexcept
			{
				x = arr[0];
				y = arr[1];
				z = arr[2];
			}
			Vec3(type pitch, type yaw) noexcept
			{
				x = std::cos(yaw) * std::cos(pitch);
				y = std::cos(yaw) * std::sin(pitch);
				z = std::sin(pitch);
			}
			void rotate(const Vec3& exis, type theta) noexcept
			{

			}
			//vielleicht hier auch noch abstand punkt gerade, gerade ebene, ob punkt auf gerade oder linie ligt und schneiden 
			///hier weiter machen und ggf nochmal alle methoden überprüfen, ob sie an dem vec selbst nichts verändern 





			//vector constructor
			explicit Vec3(const std::vector<type>& other) noexcept
			{
				x = other.at(0);
				y = other.at(1);
				z = other.at(2);
			}
			//vec3 copy constructor
			Vec3(const Vec3<type>& other) noexcept
				:x(other.x), y(other.y), z(other.z)
			{}
			//vec3 move constructor
			Vec3(Vec3<type>&& other) noexcept
				:x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z))
			{}
			//vec3 assign operator
			Vec3<type>& operator=(const Vec3<type>& other) noexcept
			{
				x = other.x;
				y = other.y;
				z = other.z;
				return *this;
			}
			//vec3 move operator
			Vec3<type>& operator=(Vec3<type>&& other) noexcept
			{
				x = std::move(other.x);
				y = std::move(other.y);
				z = std::move(other.z);
				return *this;
			}
			//vec2 copy constructor
			explicit Vec3(const Vec2<type>& other) noexcept;
			//vec2 move constructor
			explicit Vec3(Vec2<type>&& other) noexcept;
			//vec4 copy constructor
			explicit Vec3(const Vec4<type>& other) noexcept;
			//vec4 move constructor
			explicit Vec3(Vec4<type>&& other) noexcept;
			//vec2 assign operator
			Vec3<type>& operator=(const Vec2<type>& other) noexcept;
			//vec2 move operator
			Vec3<type>& operator=(Vec2<type>&& other) noexcept;
			//vec4 assign operator
			Vec3<type>& operator=(const Vec4<type>& other) noexcept;
			//vec4 move operator
			Vec3<type>& operator=(Vec4<type>&& other) noexcept;

			//vec3 other type copy constructor
			template<typename othertype>
			explicit Vec3(const Vec3<othertype>& other) noexcept
				:x(static_cast<type>( other.x )), y(static_cast<type>( other.y )), z(static_cast<type>( other.z ))
			{}
			//vec3 other type move constructor
			template<typename othertype>
			explicit Vec3(Vec3<othertype>&& other) noexcept
				: x(static_cast<type>( std::move(other.x) )), y(static_cast<type>( std::move(other.y) )), z(static_cast<type>( std::move(other.z) ))
			{}
			//vec3 other type assign operator
			template<typename othertype>
			Vec3<type>& operator=(const Vec3<othertype>& other) noexcept
			{
				x = static_cast<type>( other.x );
				y = static_cast<type>( other.y );
				z = static_cast<type>( other.z );
				return *this;
			}
			//vec3 other type move operator
			template<typename othertype>
			Vec3<type>& operator=(Vec3<othertype>&& other) noexcept
			{
				x = static_cast<type>( std::move(other.x) );
				y = static_cast<type>( std::move(other.y) );
				z = static_cast<type>( std::move(other.z) );
				return *this;
			}

		public:
			//add a value to this 
			Vec3<type>& add(type val) noexcept
			{
				x += val;
				y += val;
				z += val;
				return *this;
			}
			//add another Vec3 to this 
			Vec3<type>& add(const Vec3<type>& other) noexcept
			{
				x += other.x;
				y += other.y;
				z += other.z;
				return *this;
			}
			//add another Vec3 to this 
			Vec3<type>& add(Vec3<type>&& other) noexcept
			{
				x += other.x;
				y += other.y;
				z += other.z;
				return *this;
			}
			//substract a value from this 
			Vec3<type>& substract(type val) noexcept
			{
				x -= val;
				y -= val;
				z -= val;
				return *this;
			}
			//substract another Vec3 from this 
			Vec3<type>& substract(const Vec3<type>& other) noexcept
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				return *this;
			}
			//substract another Vec3 from this 
			Vec3<type>& substract(Vec3<type>&& other) noexcept
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				return *this;
			}
			//multiply a value to this | elementwise, not dotproduct
			Vec3<type>& multiply(type val) noexcept
			{
				x *= val;
				y *= val;
				z *= val;
				return *this;
			}
			//multiply another Vec3 to this | elementwise, not dotproduct
			Vec3<type>& multiply(const Vec3<type>& other) noexcept
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
				return *this;
			}
			//multiply another Vec3 to this | elementwise, not dotproduct
			Vec3<type>& multiply(Vec3<type>&& other) noexcept
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
				return *this;
			}
			//divide a value from this 
			Vec3<type>& divide(type val) noexcept
			{
				x /= val;
				y /= val;
				z /= val;
				return *this;
			}
			//divide another Vec3 from this 
			Vec3<type>& divide(const Vec3<type>& other) noexcept
			{
				x /= other.x;
				y /= other.y;
				z /= other.z;
				return *this;
			}
			//divide another Vec3 from this 
			Vec3<type>& divide(Vec3<type>&& other) noexcept
			{
				x /= other.x;
				y /= other.y;
				z /= other.z;
				return *this;
			}
			//add another Vec2 to this 
			Vec3<type>& add(const Vec2<type>& other) noexcept;
			//add another Vec2 to this 
			Vec3<type>& add(Vec2<type>&& other) noexcept;
			//add another Vec4 to this 
			Vec3<type>& add(const Vec4<type>& other) noexcept;
			//add another Vec4 to this 
			Vec3<type>& add(Vec4<type>&& other) noexcept;
			//substract another Vec2 from this 
			Vec3<type>& substract(const Vec2<type>& other) noexcept;
			//substract another Vec2 from this 
			Vec3<type>& substract(Vec2<type>&& other) noexcept;
			//substract another Vec4 from this 
			Vec3<type>& substract(const Vec4<type>& other) noexcept;
			//substract another Vec4 from this 
			Vec3<type>& substract(Vec4<type>&& other) noexcept;
			//multiply another Vec2 to this | elementwise, not dotproduct
			Vec3<type>& multiply(const Vec2<type>& other) noexcept;
			//multiply another Vec2 to this | elementwise, not dotproduct
			Vec3<type>& multiply(Vec2<type>&& other) noexcept;
			//multiply another Vec4 to this | elementwise, not dotproduct
			Vec3<type>& multiply(const Vec4<type>& other) noexcept;
			//multiply another Vec4 to this | elementwise, not dotproduct
			Vec3<type>& multiply(Vec4<type>&& other) noexcept;
			//divide another Vec2 from this 
			Vec3<type>& divide(const Vec2<type>& other) noexcept;
			//divide another Vec2 from this 
			Vec3<type>& divide(Vec2<type>&& other) noexcept;
			//divide another Vec4 from this 
			Vec3<type>& divide(const Vec4<type>& other) noexcept;
			//divide another Vec4 from this 
			Vec3<type>& divide(Vec4<type>&& other) noexcept;

		public:
			//negate the vec
			friend Vec3<type> operator-(Vec3<type> vec) noexcept
			{
				vec.x = -vec.x;
				vec.y = -vec.y;
				vec.z = -vec.z;
				return vec;
			}
			//add a value to this 
			Vec3<type>& operator+=(type val) noexcept
			{
				x += val;
				y += val;
				z += val;
				return *this;
			}
			//add another Vec3 to this 
			Vec3<type>& operator+=(const Vec3<type>& other) noexcept
			{
				x += other.x;
				y += other.y;
				z += other.z;
				return *this;
			}
			//add another Vec3 to this 
			Vec3<type>& operator+=(Vec3<type>&& other) noexcept
			{
				x += other.x;
				y += other.y;
				z += other.z;
				return *this;
			}
			//substract a value from this 
			Vec3<type>& operator-=(type val) noexcept
			{
				x -= val;
				y -= val;
				z -= val;
				return *this;
			}
			//substract another Vec3 from this 
			Vec3<type>& operator-=(const Vec3<type>& other) noexcept
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				return *this;
			}
			//substract another Vec3 from this 
			Vec3<type>& operator-=(Vec3<type>&& other) noexcept
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				return *this;
			}
			//multiply a value to this | elementwise, not dotproduct
			Vec3<type>& operator*=(type val) noexcept
			{
				x *= val;
				y *= val;
				z *= val;
				return *this;
			}
			//multiply another Vec3 to this | elementwise, not dotproduct
			Vec3<type>& operator*=(const Vec3<type>& other) noexcept
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
				return *this;
			}
			//multiply another Vec3 to this | elementwise, not dotproduct
			Vec3<type>& operator*=(Vec3<type>&& other) noexcept
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
				return *this;
			}
			//divide a value from this 
			Vec3<type>& operator/=(type val) noexcept
			{
				x /= val;
				y /= val;
				z /= val;
				return *this;
			}
			//divide another Vec3 from this 
			Vec3<type>& operator/=(const Vec3<type>& other) noexcept
			{
				x /= other.x;
				y /= other.y;
				z /= other.z;
				return *this;
			}
			//divide another Vec3 from this 
			Vec3<type>& operator/=(Vec3<type>&& other) noexcept
			{
				x /= other.x;
				y /= other.y;
				z /= other.z;
				return *this;
			}
			//add another Vec2 to this 
			Vec3<type>& operator+=(const Vec2<type>& other) noexcept;
			//add another Vec2 to this 
			Vec3<type>& operator+=(Vec2<type>&& other) noexcept;
			//add another Vec4 to this 
			Vec3<type>& operator+=(const Vec4<type>& other) noexcept;
			//add another Vec4 to this 
			Vec3<type>& operator+=(Vec4<type>&& other) noexcept;
			//substract another Vec2 from this 
			Vec3<type>& operator-=(const Vec2<type>& other) noexcept;
			//substract another Vec2 from this 
			Vec3<type>& operator-=(Vec2<type>&& other) noexcept;
			//substract another Vec4 from this 
			Vec3<type>& operator-=(const Vec4<type>& other) noexcept;
			//substract another Vec4 from this 
			Vec3<type>& operator-=(Vec4<type>&& other) noexcept;
			//multiply another Vec2 to this | elementwise, not dotproduct
			Vec3<type>& operator*=(const Vec2<type>& other) noexcept;
			//multiply another Vec2 to this | elementwise, not dotproduct
			Vec3<type>& operator*=(Vec2<type>&& other) noexcept;
			//multiply another Vec4 to this | elementwise, not dotproduct
			Vec3<type>& operator*=(const Vec4<type>& other) noexcept;
			//multiply another Vec4 to this | elementwise, not dotproduct
			Vec3<type>& operator*=(Vec4<type>&& other) noexcept;
			//divide another Vec2 from this 
			Vec3<type>& operator/=(const Vec2<type>& other) noexcept;
			//divide another Vec2 from this 
			Vec3<type>& operator/=(Vec2<type>&& other) noexcept;
			//divide another Vec4 from this 
			Vec3<type>& operator/=(const Vec4<type>& other) noexcept;
			//divide another Vec4 from this 
			Vec3<type>& operator/=(Vec4<type>&& other) noexcept;
			//compare all values to another lvalue Vec3
			bool operator==(const Vec3<type>& other) const noexcept
			{
				return x == other.x && y == other.y && z == other.z;
			}
			//compare all values to another rvalue Vec3
			bool operator==(Vec3<type>&& other) const noexcept
			{
				return x == other.x && y == other.y && z == other.z;
			}
			//compare all values to another lvalue Vec3
			bool operator!=(const Vec3<type>& other) const noexcept
			{
				return x != other.x || y != other.y || z != other.z;
			}
			//compare all values to another rvalue Vec3
			bool operator!=(Vec3<type>&& other) const noexcept
			{
				return x != other.x || y != other.y || z != other.z;
			}
			//compare all values to another lvalue Vec3 | values are added up
			bool operator<=(const Vec3<type>& other) const noexcept
			{
				return ( x + y + z ) <= ( other.x + other.y + other.z );
			}
			//compare all values to another rvalue Vec3 | values are added up
			bool operator<=(Vec3<type>&& other) const noexcept
			{
				return ( x + y + z ) <= ( other.x + other.y + other.z );
			}
			//compare all values to another lvalue Vec3 | values are added up
			bool operator>=(const Vec3<type>& other) const noexcept
			{
				return ( x + y + z ) >= ( other.x + other.y + other.z );
			}
			//compare all values to another rvalue Vec3 | values are added up
			bool operator>=(Vec3<type>&& other) const noexcept
			{
				return ( x + y + z ) >= ( other.x + other.y + other.z );
			}
			//compare all values to another lvalue Vec3 | values are added up
			bool operator<(const Vec3<type>& other) const noexcept
			{
				return ( x + y + z ) < ( other.x + other.y + other.z );
			}
			//compare all values to another rvalue Vec3 | values are added up
			bool operator<(Vec3<type>&& other) const noexcept
			{
				return ( x + y + z ) < ( other.x + other.y + other.z );
			}
			//compare all values to another lvalue Vec3 | values are added up
			bool operator>(const Vec3<type>& other) const noexcept
			{
				return ( x + y + z ) > ( other.x + other.y + other.z );
			}
			//compare all values to another rvalue Vec3 | values are added up
			bool operator>(Vec3<type>&& other) const noexcept
			{
				return ( x + y + z ) > ( other.x + other.y + other.z );
			}


			//add a rvalue Vec3 object to a rvalue Vec3 object
			friend Vec3<type>&& operator+(Vec3<type>&& v1, Vec3<type>&& v2) noexcept
			{
				v1.x += v2.x;
				v1.y += v2.y;
				v1.z += v2.z;
				return std::move(v1);
			}
			//add a rvalue Vec3 object to a lvalue Vec3 object 
			friend Vec3<type>&& operator+(const Vec3<type>& v1, Vec3<type>&& v2) noexcept
			{
				v2.x += v1.x;
				v2.y += v1.y;
				v2.z += v1.z;
				return std::move(v2);
			}
			//add a lvalue Vec3 object to a rvalue Vec3 object
			friend Vec3<type>&& operator+(Vec3<type>&& v1, const Vec3<type>& v2) noexcept
			{
				v1.x += v2.x;
				v1.y += v2.y;
				v1.z += v2.z;
				return std::move(v1);
			}
			//add a type to a lvalue Vec3 object
			friend Vec3<type> operator+(const Vec3<type>& vec, type val) noexcept
			{
				return Vec3<type>(vec.x + val, vec.y + val, vec.z + val);
			}
			//add a lvalue Vec3 object to a lvalue Vec3 object
			friend Vec3<type> operator+(const Vec3<type>& v1, const Vec3<type>& v2) noexcept
			{
				return Vec3<type>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
			}
			//add a rvalue Vec2 object to a rvalue Vec3 object
			friend Vec3<type>&& operator+<type>( Vec3<type>&& v1, Vec2<type>&& v2 ) noexcept;
			//add a lvalue Vec2 object to a rvalue Vec3 object
			friend Vec3<type>&& operator+<type>( Vec3<type>&& v1, const Vec2<type>& v2 ) noexcept;
			//add a lvalue Vec2 object to a lvalue Vec3 object
			friend Vec3<type> operator+<type>( const Vec3<type>& v1, const Vec2<type>& v2 ) noexcept;
			//add a rvalue Vec4 object to a rvalue Vec3 object
			friend Vec3<type>&& operator+<type>( Vec3<type>&& v1, Vec4<type>&& v2 ) noexcept;
			//add a lvalue Vec4 object to a rvalue Vec3 object
			friend Vec3<type>&& operator+<type>( Vec3<type>&& v1, const Vec4<type>& v2 ) noexcept;
			//add a lvalue Vec4 object to a lvalue Vec3 object
			friend Vec3<type> operator+<type>( const Vec3<type>& v1, const Vec4<type>& v2 ) noexcept;
			//substract a rvalue Vec3 object from a rvalue Vec3 object
			friend Vec3<type>&& operator-(Vec3<type>&& v1, Vec3<type>&& v2) noexcept
			{
				v1.x -= v2.x;
				v1.y -= v2.y;
				v1.z -= v2.z;
				return std::move(v1);
			}
			//substract a rvalue Vec3 object from a lvalue Vec3 object 
			friend Vec3<type> operator-(const Vec3<type>& v1, Vec3<type>&& v2) noexcept
			{
				return Vec3<type>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
			}
			//substract a lvalue Vec3 object from a rvalue Vec3 object
			friend Vec3<type>&& operator-(Vec3<type>&& v1, const Vec3<type>& v2) noexcept
			{
				v1.x -= v2.x;
				v1.y -= v2.y;
				v1.z -= v2.z;
				return std::move(v1);
			}
			//substract a type from a lvalue Vec3 object
			friend Vec3<type> operator-(const Vec3<type>& vec, type val) noexcept
			{
				return Vec3<type>(vec.x - val, vec.y - val, vec.z - val);
			}
			//substract a lvalue Vec3 object from a lvalue Vec3 object
			friend Vec3<type> operator-(const Vec3<type>& v1, const Vec3<type>& v2) noexcept
			{
				return Vec3<type>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
			}
			//substract a rvalue Vec2 object from a rvalue Vec3 object
			friend Vec3<type>&& operator-<type>( Vec3<type>&& v1, Vec2<type>&& v2 ) noexcept;
			//substract a lvalue Vec2 object from a rvalue Vec3 object
			friend Vec3<type>&& operator-<type>( Vec3<type>&& v1, const Vec2<type>& v2 ) noexcept;
			//substract a lvalue Vec2 object from a lvalue Vec3 object
			friend Vec3<type> operator-<type>( const Vec3<type>& v1, const Vec2<type>& v2 ) noexcept;
			//substract a rvalue Vec4 object from a rvalue Vec3 object
			friend Vec3<type>&& operator-<type>( Vec3<type>&& v1, Vec4<type>&& v2 ) noexcept;
			//substract a lvalue Vec4 object from a rvalue Vec3 object
			friend Vec3<type>&& operator-<type>( Vec3<type>&& v1, const Vec4<type>& v2 ) noexcept;
			//substract a lvalue Vec4 object from a lvalue Vec3 object
			friend Vec3<type> operator-<type>( const Vec3<type>& v1, const Vec4<type>& v2 ) noexcept;
			//multiply a rvalue Vec3 object to a rvalue Vec3 object | elementwise, not dotproduct
			friend Vec3<type>&& operator*(Vec3<type>&& v1, Vec3<type>&& v2) noexcept
			{
				v1.x *= v2.x;
				v1.y *= v2.y;
				v1.z *= v2.z;
				return std::move(v1);
			}
			//multiply a rvalue Vec3 object to a lvalue Vec3 object | elementwise, not dotproduct
			friend Vec3<type>&& operator*(const Vec3<type>& v1, Vec3<type>&& v2) noexcept
			{
				v2.x *= v1.x;
				v2.y *= v1.y;
				v2.z *= v1.z;
				return std::move(v2);
			}
			//multiply a lvalue Vec3 object to a rvalue Vec3 object | elementwise, not dotproduct
			friend Vec3<type>&& operator*(Vec3<type>&& v1, const Vec3<type>& v2) noexcept
			{
				v1.x *= v2.x;
				v1.y *= v2.y;
				v1.z *= v2.z;
				return std::move(v1);
			}
			//multiply a type to a lvalue Vec3 object | elementwise, not dotproduct
			friend Vec3<type> operator*(type val, const Vec3<type>& vec) noexcept
			{
				return Vec3<type>(vec.x * val, vec.y * val, vec.z * val);
			}
			//multiply a type to a lvalue Vec3 object | elementwise, not dotproduct
			friend Vec3<type> operator*(const Vec3<type>& vec, type val) noexcept
			{
				return Vec3<type>(vec.x * val, vec.y * val, vec.z * val);
			}
			//multiply a lvalue Vec3 object to a lvalue Vec3 object | elementwise, not dotproduct
			friend Vec3<type> operator*(const Vec3<type>& v1, const Vec3<type>& v2) noexcept
			{
				return Vec3<type>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
			}
			//multiply a rvalue Vec2 object to a rvalue Vec3 object | elementwise, not dotproduct
			friend Vec3<type>&& operator*<type>( Vec3<type>&& v1, Vec2<type>&& v2 ) noexcept;
			//multiply a lvalue Vec2 object to a rvalue Vec3 object | elementwise, not dotproduct
			friend Vec3<type>&& operator*<type>( Vec3<type>&& v1, const Vec2<type>& v2 ) noexcept;
			//multiply a lvalue Vec2 object to a lvalue Vec3 object | elementwise, not dotproduct
			friend Vec3<type> operator*<type>( const Vec3<type>& v1, const Vec2<type>& v2 ) noexcept;
			//multiply a rvalue Vec4 object to a rvalue Vec3 object | elementwise, not dotproduct
			friend Vec3<type>&& operator*<type>( Vec3<type>&& v1, Vec4<type>&& v2 ) noexcept;
			//multiply a lvalue Vec4 object to a rvalue Vec3 object | elementwise, not dotproduct
			friend Vec3<type>&& operator*<type>( Vec3<type>&& v1, const Vec4<type>& v2 ) noexcept;
			//multiply a lvalue Vec4 object to a lvalue Vec3 object | elementwise, not dotproduct
			friend Vec3<type> operator*<type>( const Vec3<type>& v1, const Vec4<type>& v2 ) noexcept;
			//divide a rvalue Vec3 object to a rvalue Vec3 object
			friend Vec3<type>&& operator/(Vec3<type>&& v1, Vec3<type>&& v2) noexcept
			{
				v1.x /= v2.x;
				v1.y /= v2.y;
				v1.z /= v2.z;
				return std::move(v1);
			}
			//divide a rvalue Vec3 object to a lvalue Vec3 object 
			friend Vec3<type> operator/(const Vec3<type>& v1, Vec3<type>&& v2) noexcept
			{
				return Vec3<type>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
			}
			//divide a lvalue Vec3 object to a rvalue Vec3 object
			friend Vec3<type>&& operator/(Vec3<type>&& v1, const Vec3<type>& v2) noexcept
			{
				v1.x /= v2.x;
				v1.y /= v2.y;
				v1.z /= v2.z;
				return std::move(v1);
			}
			//divide a type to a lvalue Vec3 object
			friend Vec3<type> operator/(const Vec3<type>& vec, type val) noexcept
			{
				return Vec3<type>(vec.x / val, vec.y / val, vec.z / val);
			}
			//divide a lvalue Vec3 object to a lvalue Vec3 object
			friend Vec3<type> operator/(const Vec3<type>& v1, const Vec3<type>& v2) noexcept
			{
				return Vec3<type>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
			}
			//divide a rvalue Vec2 object to a rvalue Vec3 object
			friend Vec3<type>&& operator/<type>( Vec3<type>&& v1, Vec2<type>&& v2 ) noexcept;
			//divide a lvalue Vec2 object to a rvalue Vec3 object
			friend Vec3<type>&& operator/<type>( Vec3<type>&& v1, const Vec2<type>& v2 ) noexcept;
			//divide a lvalue Vec2 object to a lvalue Vec3 object
			friend Vec3<type> operator/<type>( const Vec3<type>& v1, const Vec2<type>& v2 ) noexcept;
			//divide a rvalue Vec4 object to a rvalue Vec3 object
			friend Vec3<type>&& operator/<type>( Vec3<type>&& v1, Vec4<type>&& v2 ) noexcept;
			//divide a lvalue Vec4 object to a rvalue Vec3 object
			friend Vec3<type>&& operator/<type>( Vec3<type>&& v1, const Vec4<type>& v2 ) noexcept;
			//divide a lvalue Vec4 object to a lvalue Vec3 object
			friend Vec3<type> operator/<type>( const Vec3<type>& v1, const Vec4<type>& v2 ) noexcept;
			//modulo a vec3 with a number(only works with int and will take int values)
			friend Vec3<type> operator%(const Vec3<type>& vec, int val) noexcept
			{
				return Vec3<type>(static_cast<int>( vec.x ) % val, static_cast<int>( vec.y ) % val, static_cast<int>( vec.z ) % val);
			}

		public:
			//const read-only position access x=0, y=1, z=2
			const type operator[](unsigned short position) const noexcept
			{
				return data[position];
			}
			//position access x=0, y=1, z=2
			type& operator[](unsigned short position) noexcept
			{
				return data[position];
			}
			//|vec| returns the lenght of the vec/direct distance from origin vec(0,0,0) | std::sqrt(x * x + y * y + z * z)
			type magnitude() const noexcept
			{
				return std::sqrt(x * x + y * y + z * z);
			}
			//|vec| returns the lenght of the vec/direct distance from origin vec(0,0,0) | std::sqrt(x * x + y * y + z * z)
			type slowLenght() const noexcept
			{
				return std::sqrt(x * x + y * y + z * z);
			}
			//|vec| returns the lenght of the vec/direct distance from origin vec(0,0,0,0) | the fast method to compare without the sqrt | its not the actual distance
			type fastLenght() const noexcept
			{
				return x * x + y * y + z * z;
			}
			//std::sqrt(vec*vec) returns the not negative value of the vec as a copie of the vec
			Vec3<type> abs() const noexcept
			{
				return Vec3<type>(std::sqrt(x*x), std::sqrt(y*y), std::sqrt(z*z));
			}
			//std::sqrt(vec*vec) returns the not negative value of the vec as a copie of the vec | its the fast method without the sqrt
			Vec3<type> fastAbs() const noexcept
			{
				type tempx;
				if ( x < 0 )
					tempx = -x;
				else
					tempx = x;

				type tempy;
				if ( y < 0 )
					tempy = -y;
				else
					tempy = y;

				type tempz;
				if ( z < 0 )
					tempz = -z;
				else
					tempz = z;
				return Vec3<type>(tempx, tempy, tempz);
			}
			//std::sqrt(vec*vec) converts the vec itself to its not negative value
			Vec3<type>& absSelf() noexcept
			{
				x = std::sqrt(x*x);
				y = std::sqrt(y*y);
				z = std::sqrt(z*z);
				return *this;
			}
			//std::sqrt(vec*vec) converts the vec itself to its not negative value | its the fast method without the sqrt
			Vec3<type>& fastAbsSelf() noexcept
			{
				if ( x < 0 )
					x = -x;
				if ( y < 0 )
					y = -y;
				if ( z < 0 )
					z = -z;
				return *this;
			}
			//vec(x/magnitude(), y/magnitude(), z/magnitude()) returns a normalized copy of the vec relative to the lenght of the vec  | also called called unit vector, because the magnitude/lenght of the vector is always one 
			Vec3<type> normalize() const noexcept
			{
				return Vec3<type>(x / std::sqrt(x * x + y * y + z * z), y / std::sqrt(x * x + y * y + z * z), z / std::sqrt(x * x + y * y + z * z));
			}
			//vec(x/magnitude(), y/magnitude()) normalize the vec itself relative to the lenght of the vec | also called called unit vector, because the magnitude/lenght of the vector is always one 
			Vec3<type>& normalizeSelf() noexcept
			{
				type scale = std::sqrt(x * x + y * y + z * z);
				x /= scale;
				y /= scale;
				z /= scale;
				return *this;
			}
			//|vec1-vec2| returns the direct distance to another vec | std::sqrt(( x - other.x ) * ( x - other.x ) + ( y - other.y ) * ( y - other.y ) + ( z - other.z ) * ( z - other.z ))
			type distance(const Vec3<type>& other) const noexcept
			{
				return std::sqrt(( x - other.x ) * ( x - other.x ) + ( y - other.y ) * ( y - other.y ) + ( z - other.z ) * ( z - other.z ));
			}
			//|vec1-vec2| can be used to compare distances, will return the non negative value of the components added together | its the fast method and not the actual distance | its without the sqrt
			type fastDistance(const Vec3<type>& other) const noexcept
			{
				return ( x - other.x ) * ( x - other.x ) + ( y - other.y ) * ( y - other.y ) + ( z - other.z ) * ( z - other.z );
			}
			/*vec1*vec2 = |vec1|*|vec2|*cos(vec1,vec2) returns the dotproduct of 2 vecs, vecs are orthogonal(_|_) if the result is 0 and vecs are parallel if the result is 1(||) | x * other.x + y * other.y + z * other.z | not the normal multiply method 
			its more efficient than comparing the vecs with the magnitude method*/
			type dotproduct(const Vec3<type>& other) const noexcept
			{
				return x * other.x + y * other.y + z * other.z;
			}
			/*vec1*vec2 = |vec1|*|vec2|*cos(vec1,vec2) returns the dotproduct of 2 vecs, vecs are orthogonal(_|_) if the result is 0 and vecs are parallel if the result is 1(||) | x * other.x + y * other.y + z * other.z | not the normal multiply method 
			its more efficient than comparing the vecs with the magnitude method*/
			type dotproduct(Vec3<type>&& other) const noexcept
			{
				return x * other.x + y * other.y + z * other.z;
			}
			//acos(dotproduct() / (magnitude()*other.magnitude())) returns the angle between 2 vecs in radians 
			type angleR(const Vec3<type>& other) const noexcept
			{
				return std::acos(( x * other.x + y * other.y + z * other.z ) / ( std::sqrt(x * x + y * y + z * z) * std::sqrt(other.x * other.x + other.y * other.y + other.z * other.z) ));
			}
			//acos(dotproduct() / (magnitude()*other.magnitude())) returns the angle between 2 vecs in radians 
			type angleR(Vec3<type>&& other) const noexcept
			{
				return std::acos(( x * other.x + y * other.y + z * other.z ) / ( std::sqrt(x * x + y * y + z * z) * std::sqrt(other.x * other.x + other.y * other.y + other.z * other.z) ));
			}
			//acos(dotproduct() / (magnitude()*other.magnitude())) returns the angle between 2 vecs in degrees 
			type angleD(const Vec3<type>& other) const noexcept
			{
				return std::acos(( x * other.x + y * other.y + z * other.z ) / ( std::sqrt(x * x + y * y + z * z) * std::sqrt(other.x * other.x + other.y * other.y + other.z * other.z) ))*( 180.0 / 3.14159265359 );
			}
			//acos(dotproduct() / (magnitude()*other.magnitude())) returns the angle between 2 vecs in degrees 
			type angleD(Vec3<type>&& other) const noexcept
			{
				return std::acos(( x * other.x + y * other.y + z * other.z ) / ( std::sqrt(x * x + y * y + z * z) * std::sqrt(other.x * other.x + other.y * other.y + other.z * other.z) ))*( 180.0 / 3.14159265359 );
			}
			//vec1xvec2 returns the orthogonal vec to the level of the 2 other vecs(_|/), magnitude of the vec is the area of the 2 vecs 
			Vec3<type> crossproduct(const Vec3<type>& other) const noexcept
			{
				return Vec3<type>(y*other.z - z * other.y, z* other.x - x * other.z, x * other.y - y * other.x);
			}
			//vec1xvec2 returns the orthogonal vec to the level of the 2 other vecs(_|/), magnitude of the vec is the area of the 2 vecs 
			Vec3<type> crossproduct(Vec3<type>&& other) const noexcept
			{
				return Vec3<type>(y*other.z - z * other.y, z* other.x - x * other.z, x * other.y - y * other.x);
			}
			//|vec1xvec2| returns the area of the 2 vecs, also is the magnitude of the crossproduct
			type area(const Vec3<type>& other) const noexcept
			{
				return std::sqrt(( y*other.z - z * other.y ) * ( y*other.z - z * other.y ) + ( z* other.x - x * other.z ) * ( z* other.x - x * other.z ) + ( x * other.y - y * other.x ) * ( x * other.y - y * other.x ));
			}
			//|vec1xvec2| returns the area of the 2 vecs, also is the magnitude of the crossproduct
			type area(Vec3<type>&& other) const noexcept
			{
				return std::sqrt(( y*other.z - z * other.y ) * ( y*other.z - z * other.y ) + ( z* other.x - x * other.z ) * ( z* other.x - x * other.z ) + ( x * other.y - y * other.x ) * ( x * other.y - y * other.x ));
			}
			//(vec1xvec2)*vec3 returns the non negative |volume| of the 3 vecs, also called triple product | std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) )) | not the normal multiply method 
			type volume(const Vec3<type>& v2, const Vec3<type>& v3) const noexcept
			{
				return std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) ));
			}
			//(vec1xvec2)*vec3 returns the non negative |volume| of the 3 vecs, also called triple product | std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) )) | not the normal multiply method 
			type volume(Vec3<type>&& v2, Vec3<type>&& v3) const noexcept
			{
				return std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) ));
			}
			//(vec1xvec2)*vec3 returns the non negative |volume| of the 3 vecs, also called triple product | std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) )) | not the normal multiply method 
			type volume(Vec3<type>&& v2, const Vec3<type>& v3) const noexcept
			{
				return std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) ));
			}
			//(vec1xvec2)*vec3 returns the non negative |volume| of the 3 vecs, also called triple product | std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) )) | not the normal multiply method 
			type volume(const Vec3<type>& v2, Vec3<type>&& v3) const noexcept
			{
				return std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) ));
			}
			//vec as string: "Vec3<type>(x,y,z)"
			std::string toString() const noexcept
			{
				std::stringstream stream;
				stream << "Vec3<" << typeid( type ).name() << ">(" << x << "," << y << "," << z << ")";
				return stream.str();
			}
			//ostream operator: "Vec3<type>(x,y,z)"
			friend std::ostream& operator<<(std::ostream& stream, const Vec3<type>& vec) noexcept
			{
				stream << "Vec3<" << typeid( type ).name() << ">(" << vec.x << "," << vec.y << "," << vec.z << ")";
				return stream;
			}

		};

	}
}

#include "Vec2.h"
#include "Vec4.h"

namespace clockwork {
	namespace maths {

		//vec2 copy constructor
		template<typename type>Vec3<type>::Vec3(const Vec2<type>& other) noexcept
			:x(other.x), y(other.y), z(0)
		{}
		//vec2 move constructor
		template<typename type>Vec3<type>::Vec3(Vec2<type>&& other) noexcept
			: x(std::move(other.x)), y(std::move(other.y)), z(0)
		{}
		//vec4 copy constructor
		template<typename type>Vec3<type>::Vec3(const Vec4<type>& other) noexcept
			: x(other.x), y(other.y), z(other.z)
		{}
		//vec4 move constructor
		template<typename type>Vec3<type>::Vec3(Vec4<type>&& other) noexcept
			: x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z))
		{}
		//vec2 assign operator
		template<typename type>Vec3<type>& Vec3<type>::operator=(const Vec2<type>& other) noexcept
		{
			x = other.x;
			y = other.y;
			return *this;
		}
		//vec2 move operator
		template<typename type>Vec3<type>& Vec3<type>::operator=(Vec2<type>&& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
			return *this;
		}
		//vec4 assign operator
		template<typename type>Vec3<type>& Vec3<type>::operator=(const Vec4<type>& other) noexcept
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}
		//vec4 move operator
		template<typename type>Vec3<type>& Vec3<type>::operator=(Vec4<type>&& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
			z = std::move(other.z);
			return *this;
		}

		//add another Vec2 to this 
		template<typename type>Vec3<type>& Vec3<type>::add(const Vec2<type>& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another Vec2 to this 
		template<typename type>Vec3<type>& Vec3<type>::add(Vec2<type>&& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another Vec4 to this 
		template<typename type>Vec3<type>& Vec3<type>::add(const Vec4<type>& other) noexcept
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		//add another Vec4 to this 
		template<typename type>Vec3<type>& Vec3<type>::add(Vec4<type>&& other) noexcept
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		//substract another Vec2 from this 
		template<typename type>Vec3<type>& Vec3<type>::substract(const Vec2<type>& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another Vec2 from this 
		template<typename type>Vec3<type>& Vec3<type>::substract(Vec2<type>&& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another Vec4 from this 
		template<typename type>Vec3<type>& Vec3<type>::substract(const Vec4<type>& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		//substract another Vec4 from this 
		template<typename type>Vec3<type>& Vec3<type>::substract(Vec4<type>&& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		//multiply another Vec2 to this | elementwise, not dotproduct
		template<typename type>Vec3<type>& Vec3<type>::multiply(const Vec2<type>& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another Vec2 to this | elementwise, not dotproduct
		template<typename type>Vec3<type>& Vec3<type>::multiply(Vec2<type>&& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another Vec4 to this | elementwise, not dotproduct
		template<typename type>Vec3<type>& Vec3<type>::multiply(const Vec4<type>& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}
		//multiply another Vec4 to this | elementwise, not dotproduct
		template<typename type>Vec3<type>& Vec3<type>::multiply(Vec4<type>&& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}
		//divide another Vec2 from this 
		template<typename type>Vec3<type>& Vec3<type>::divide(const Vec2<type>& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another Vec2 from this 
		template<typename type>Vec3<type>& Vec3<type>::divide(Vec2<type>&& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another Vec4 from this  
		template<typename type>Vec3<type>& Vec3<type>::divide(const Vec4<type>& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}
		//divide another Vec4 from this 
		template<typename type>Vec3<type>& Vec3<type>::divide(Vec4<type>&& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}

		//add another Vec2 to this 
		template<typename type>Vec3<type>& Vec3<type>::operator+=(const Vec2<type>& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another Vec2 to this 
		template<typename type>Vec3<type>& Vec3<type>::operator+=(Vec2<type>&& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another Vec4 to this 
		template<typename type>Vec3<type>& Vec3<type>::operator+=(const Vec4<type>& other) noexcept
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		//add another Vec4 to this 
		template<typename type>Vec3<type>& Vec3<type>::operator+=(Vec4<type>&& other) noexcept
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		//substract another Vec2 from this 
		template<typename type>Vec3<type>& Vec3<type>::operator-=(const Vec2<type>& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another Vec2 from this 
		template<typename type>Vec3<type>& Vec3<type>::operator-=(Vec2<type>&& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another Vec4 from this 
		template<typename type>Vec3<type>& Vec3<type>::operator-=(const Vec4<type>& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		//substract another Vec4 from this 
		template<typename type>Vec3<type>& Vec3<type>::operator-=(Vec4<type>&& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		//multiply another Vec2 to this | elementwise, not dotproduct
		template<typename type>Vec3<type>& Vec3<type>::operator*=(const Vec2<type>& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another Vec2 to this | elementwise, not dotproduct
		template<typename type>Vec3<type>& Vec3<type>::operator*=(Vec2<type>&& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another Vec4 to this | elementwise, not dotproduct
		template<typename type>Vec3<type>& Vec3<type>::operator*=(const Vec4<type>& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}
		//multiply another Vec4 to this | elementwise, not dotproduct
		template<typename type>Vec3<type>& Vec3<type>::operator*=(Vec4<type>&& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}
		//divide another Vec2 from this 
		template<typename type>Vec3<type>& Vec3<type>::operator/=(const Vec2<type>& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another Vec2 from this 
		template<typename type>Vec3<type>& Vec3<type>::operator/=(Vec2<type>&& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another Vec4 from this 
		template<typename type>Vec3<type>& Vec3<type>::operator/=(const Vec4<type>& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}
		//divide another Vec4 from this 
		template<typename type>Vec3<type>& Vec3<type>::operator/=(Vec4<type>&& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}


		//add a rvalue Vec2 object to a rvalue Vec3 object
		template<typename type>Vec3<type>&& operator+(Vec3<type>&& v1, Vec2<type>&& v2) noexcept
		{
			v1.x += v2.x;
			v1.y += v2.y;
			return std::move(v1);
		}
		//add a lvalue Vec2 object to a rvalue Vec3 object
		template<typename type>Vec3<type>&& operator+(Vec3<type>&& v1, const Vec2<type>& v2) noexcept
		{
			v1.x += v2.x;
			v1.y += v2.y;
			return std::move(v1);
		}
		//add a lvalue Vec2 object to a lvalue Vec3 object
		template<typename type>Vec3<type> operator+(const Vec3<type>& v1, const Vec2<type>& v2) noexcept
		{
			return Vec3<type>(v1.x + v2.x, v1.y + v2.y, v1.z);
		}
		//add a rvalue Vec4 object to a rvalue Vec3 object
		template<typename type>Vec3<type>&& operator+(Vec3<type>&& v1, Vec4<type>&& v2) noexcept
		{
			v1.x += v2.x;
			v1.y += v2.y;
			v1.z += v2.z;
			return std::move(v1);
		}
		//add a lvalue Vec4 object to a rvalue Vec3 object
		template<typename type>Vec3<type>&& operator+(Vec3<type>&& v1, const Vec4<type>& v2) noexcept
		{
			v1.x += v2.x;
			v1.y += v2.y;
			v1.z += v2.z;
			return std::move(v1);
		}
		//add a lvalue Vec4 object to a lvalue Vec3 object
		template<typename type>Vec3<type> operator+(const Vec3<type>& v1, const Vec4<type>& v2) noexcept
		{
			return Vec3<type>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
		}
		//substract a rvalue Vec2 object from a rvalue Vec3 object
		template<typename type>Vec3<type>&& operator-(Vec3<type>&& v1, Vec2<type>&& v2) noexcept
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			return std::move(v1);
		}
		//substract a lvalue Vec2 object from a rvalue Vec3 object
		template<typename type>Vec3<type>&& operator-(Vec3<type>&& v1, const Vec2<type>& v2) noexcept
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			return std::move(v1);
		}
		//substract a lvalue Vec2 object from a lvalue Vec3 object
		template<typename type>Vec3<type> operator-(const Vec3<type>& v1, const Vec2<type>& v2) noexcept
		{
			return Vec3<type>(v1.x - v2.x, v1.y - v2.y, v1.z);
		}
		//substract a rvalue Vec4 object from a rvalue Vec3 object
		template<typename type>Vec3<type>&& operator-(Vec3<type>&& v1, Vec4<type>&& v2) noexcept
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			v1.z -= v2.z;
			return std::move(v1);
		}
		//substract a lvalue Vec4 object from a rvalue Vec3 object
		template<typename type>Vec3<type>&& operator-(Vec3<type>&& v1, const Vec4<type>& v2) noexcept
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			v1.z -= v2.z;
			return std::move(v1);
		}
		//substract a lvalue Vec4 object from a lvalue Vec3 object
		template<typename type>Vec3<type> operator-(const Vec3<type>& v1, const Vec4<type>& v2) noexcept
		{
			return Vec3<type>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
		}
		//multiply a rvalue Vec2 object to a rvalue Vec3 object | elementwise, not dotproduct
		template<typename type>Vec3<type>&& operator*(Vec3<type>&& v1, Vec2<type>&& v2) noexcept
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			return std::move(v1);
		}
		//multiply a lvalue Vec2 object to a rvalue Vec3 object | elementwise, not dotproduct
		template<typename type>Vec3<type>&& operator*(Vec3<type>&& v1, const Vec2<type>& v2) noexcept
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			return std::move(v1);
		}
		//multiply a lvalue Vec2 object to a lvalue Vec3 object | elementwise, not dotproduct
		template<typename type>Vec3<type> operator*(const Vec3<type>& v1, const Vec2<type>& v2) noexcept
		{
			return Vec3<type>(v1.x * v2.x, v1.y * v2.y, v1.z);
		}
		//multiply a rvalue Vec4 object to a rvalue Vec3 object | elementwise, not dotproduct
		template<typename type>Vec3<type>&& operator*(Vec3<type>&& v1, Vec4<type>&& v2) noexcept
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			v1.z *= v2.z;
			return std::move(v1);
		}
		//multiply a lvalue Vec4 object to a rvalue Vec3 object | elementwise, not dotproduct
		template<typename type>Vec3<type>&& operator*(Vec3<type>&& v1, const Vec4<type>& v2) noexcept
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			v1.z *= v2.z;
			return std::move(v1);
		}
		//multiply a lvalue Vec4 object to a lvalue Vec3 object | elementwise, not dotproduct
		template<typename type>Vec3<type> operator*(const Vec3<type>& v1, const Vec4<type>& v2) noexcept
		{
			return Vec3<type>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
		}
		//divide a rvalue Vec2 object from a rvalue Vec3 object
		template<typename type>Vec3<type>&& operator/(Vec3<type>&& v1, Vec2<type>&& v2) noexcept
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			return std::move(v1);
		}
		//divide a lvalue Vec2 object from a rvalue Vec3 object
		template<typename type>Vec3<type>&& operator/(Vec3<type>&& v1, const Vec2<type>& v2) noexcept
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			return std::move(v1);
		}
		//divide a lvalue Vec2 object from a lvalue Vec3 object
		template<typename type>Vec3<type> operator/(const Vec3<type>& v1, const Vec2<type>& v2) noexcept
		{
			return Vec3<type>(v1.x / v2.x, v1.y / v2.y, v1.z);
		}
		//divide a rvalue Vec4 object from a rvalue Vec3 object
		template<typename type>Vec3<type>&& operator/(Vec3<type>&& v1, Vec4<type>&& v2) noexcept
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			v1.z /= v2.z;
			return std::move(v1);
		}
		//divide a lvalue Vec4 object from a rvalue Vec3 object
		template<typename type>Vec3<type>&& operator/(Vec3<type>&& v1, const Vec4<type>& v2) noexcept
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			v1.z /= v2.z;
			return std::move(v1);
		}
		//divide a lvalue Vec4 object from a lvalue Vec3 object
		template<typename type>Vec3<type> operator/(const Vec3<type>& v1, const Vec4<type>& v2) noexcept
		{
			return Vec3<type>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
		}


		using Vec3f = Vec3<float>;
		using Vec3i = Vec3<int>;

	}
}