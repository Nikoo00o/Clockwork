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

		template<typename type> Vec2<type>&& operator+(Vec2<type>&& v1, Vec3<type>&& v2) noexcept;
		template<typename type> Vec2<type>&& operator+(Vec2<type>&& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec2<type> operator+(const Vec2<type>& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec2<type>&& operator+(Vec2<type>&& v1, Vec4<type>&& v2) noexcept;
		template<typename type> Vec2<type>&& operator+(Vec2<type>&& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec2<type> operator+(const Vec2<type>& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec2<type>&& operator-(Vec2<type>&& v1, Vec3<type>&& v2) noexcept;
		template<typename type> Vec2<type>&& operator-(Vec2<type>&& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec2<type> operator-(const Vec2<type>& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec2<type>&& operator-(Vec2<type>&& v1, Vec4<type>&& v2) noexcept;
		template<typename type> Vec2<type>&& operator-(Vec2<type>&& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec2<type> operator-(const Vec2<type>& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec2<type>&& operator*(Vec2<type>&& v1, Vec3<type>&& v2) noexcept;
		template<typename type> Vec2<type>&& operator*(Vec2<type>&& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec2<type> operator*(const Vec2<type>& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec2<type>&& operator*(Vec2<type>&& v1, Vec4<type>&& v2) noexcept;
		template<typename type> Vec2<type>&& operator*(Vec2<type>&& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec2<type> operator*(const Vec2<type>& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec2<type>&& operator/(Vec2<type>&& v1, Vec3<type>&& v2) noexcept;
		template<typename type> Vec2<type>&& operator/(Vec2<type>&& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec2<type> operator/(const Vec2<type>& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec2<type>&& operator/(Vec2<type>&& v1, Vec4<type>&& v2) noexcept;
		template<typename type> Vec2<type>&& operator/(Vec2<type>&& v1, const Vec4<type>& v2) noexcept;
		template<typename type> Vec2<type> operator/(const Vec2<type>& v1, const Vec4<type>& v2) noexcept;
		template<typename type>Vec2<type> operator-(Vec2<type> vec) noexcept;

		template<typename type>
		struct Vec2
		{

		public:
			union
			{
				struct
				{
					type x;
					type y;
				};
				struct
				{
					type r;
					type g;
				};
				struct
				{
					type s;
					type t;
				};
				type data[2];
			};

		public:
			//default constructor
			Vec2() noexcept
				:x(0), y(0)
			{}
			//1 value for all constructor
			explicit Vec2(type val) noexcept
				:x(val), y(val)
			{}
			//seperate values constructor
			Vec2(type x, type y) noexcept
				:x(x), y(y)
			{}
			//vector constructor
			explicit Vec2(const std::vector<type>& other) noexcept
			{
				x = other.at(0);
				y = other.at(1);
			}
			//vec2 copy constructor
			Vec2(const Vec2<type>& other) noexcept
				:x(other.x), y(other.y)
			{}
			//vec2 move constructor
			Vec2(Vec2<type>&& other) noexcept
				:x(std::move(other.x)), y(std::move(other.y))
			{}
			//vec2 assign operator
			Vec2<type>& operator=(const Vec2<type>& other) noexcept
			{
				x = other.x;
				y = other.y;
				return *this;
			}
			//vec2 move operator
			Vec2<type>& operator=(Vec2<type>&& other) noexcept
			{
				x = std::move(other.x);
				y = std::move(other.y);
				return *this;
			}
			//vec3 copy constructor
			explicit Vec2(const Vec3<type>& other) noexcept;
			//vec3 move constructor
			explicit Vec2(Vec3<type>&& other) noexcept;
			//vec4 copy constructor
			explicit Vec2(const Vec4<type>& other) noexcept;
			//vec4 move constructor
			explicit Vec2(Vec4<type>&& other) noexcept;
			//vec3 assign operator
			Vec2<type>& operator=(const Vec3<type>& other) noexcept;
			//vec3 move operator
			Vec2<type>& operator=(Vec3<type>&& other) noexcept;
			//vec4 assign operator
			Vec2<type>& operator=(const Vec4<type>& other) noexcept;
			//vec4 move operator
			Vec2<type>& operator=(Vec4<type>&& other) noexcept;

			//vec2 other type copy constructor
			template<typename othertype>
			explicit Vec2(const Vec2<othertype>& other) noexcept
				:x(static_cast<type>( other.x )), y(static_cast<type>( other.y ))
			{}
			//vec2 other type move constructor
			template<typename othertype>
			explicit Vec2(Vec2<othertype>&& other) noexcept
				: x(static_cast<type>( std::move(other.x) )), y(static_cast<type>( std::move(other.y) ))
			{}
			//vec2 other type assign operator
			template<typename othertype>
			Vec2<type>& operator=(const Vec2<othertype>& other) noexcept
			{
				x = static_cast<type>(other.x);
				y = static_cast<type>( other.y);
				return *this;
			}
			//vec2 other type move operator
			template<typename othertype>
			Vec2<type>& operator=(Vec2<othertype>&& other) noexcept
			{
				x = static_cast<type>( std::move(other.x));
				y = static_cast<type>( std::move(other.y));
				return *this;
			}

		public:
			//add a value to this 
			Vec2<type>& add(type val) noexcept
			{
				x += val;
				y += val;
				return *this;
			}
			//add another vec2 to this 
			Vec2<type>& add(const Vec2<type>& other) noexcept
			{
				x += other.x;
				y += other.y;
				return *this;
			}
			//add another vec2 to this 
			Vec2<type>& add(Vec2<type>&& other) noexcept
			{
				x += other.x;
				y += other.y;
				return *this;
			}
			//substract a value from this 
			Vec2<type>& substract(type val) noexcept
			{
				x -= val;
				y -= val;
				return *this;
			}
			//substract another vec2 from this 
			Vec2<type>& substract(const Vec2<type>& other) noexcept
			{
				x -= other.x;
				y -= other.y;
				return *this;
			}
			//substract another vec2 from this 
			Vec2<type>& substract(Vec2<type>&& other) noexcept
			{
				x -= other.x;
				y -= other.y;
				return *this;
			}
			//multiply a value to this | elementwise, not dotproduct
			Vec2<type>& multiply(type val) noexcept
			{
				x *= val;
				y *= val;
				return *this;
			}
			//multiply another vec2 to this | elementwise, not dotproduct
			Vec2<type>& multiply(const Vec2<type>& other) noexcept
			{
				x *= other.x;
				y *= other.y;
				return *this;
			}
			//multiply another vec2 to this | elementwise, not dotproduct
			Vec2<type>& multiply(Vec2<type>&& other) noexcept
			{
				x *= other.x;
				y *= other.y;
				return *this;
			}
			//divide a value from this 
			Vec2<type>& divide(type val) noexcept
			{
				x /= val;
				y /= val;
				return *this;
			}
			//divide another vec2 from this 
			Vec2<type>& divide(const Vec2<type>& other) noexcept
			{
				x /= other.x;
				y /= other.y;
				return *this;
			}
			//divide another vec2 from this 
			Vec2<type>& divide(Vec2<type>&& other) noexcept
			{
				x /= other.x;
				y /= other.y;
				return *this;
			}
			//add another vec3 to this 
			Vec2<type>& add(const Vec3<type>& other) noexcept;
			//add another vec3 to this 
			Vec2<type>& add(Vec3<type>&& other) noexcept;
			//add another vec4 to this 
			Vec2<type>& add(const Vec4<type>& other) noexcept;
			//add another vec4 to this 
			Vec2<type>& add(Vec4<type>&& other) noexcept;
			//substract another vec3 from this 
			Vec2<type>& substract(const Vec3<type>& other) noexcept;
			//substract another vec3 from this 
			Vec2<type>& substract(Vec3<type>&& other) noexcept;
			//substract another vec4 from this 
			Vec2<type>& substract(const Vec4<type>& other) noexcept;
			//substract another vec4 from this 
			Vec2<type>& substract(Vec4<type>&& other) noexcept;
			//multiply another vec3 to this | elementwise, not dotproduct
			Vec2<type>& multiply(const Vec3<type>& other) noexcept;
			//multiply another vec3 to this | elementwise, not dotproduct
			Vec2<type>& multiply(Vec3<type>&& other) noexcept;
			//multiply another vec4 to this | elementwise, not dotproduct
			Vec2<type>& multiply(const Vec4<type>& other) noexcept;
			//multiply another vec4 to this | elementwise, not dotproduct
			Vec2<type>& multiply(Vec4<type>&& other) noexcept;
			//divide another vec3 from this 
			Vec2<type>& divide(const Vec3<type>& other) noexcept;
			//divide another vec3 from this 
			Vec2<type>& divide(Vec3<type>&& other) noexcept;
			//divide another vec4 from this 
			Vec2<type>& divide(const Vec4<type>& other) noexcept;
			//divide another vec4 from this 
			Vec2<type>& divide(Vec4<type>&& other) noexcept;

		public:
			//negate the vec
			friend Vec2<type> operator-(Vec2<type> vec) noexcept
			{
				vec.x = -vec.x;
				vec.y = -vec.y;
				return vec;
			}
			//add a value to this 
			Vec2<type>& operator+=(type val) noexcept
			{
				x += val;
				y += val;
				return *this;
			}
			//add another vec2 to this 
			Vec2<type>& operator+=(const Vec2<type>& other) noexcept
			{
				x += other.x;
				y += other.y;
				return *this;
			}
			//add another vec2 to this 
			Vec2<type>& operator+=(Vec2<type>&& other) noexcept
			{
				x += other.x;
				y += other.y;
				return *this;
			}
			//substract a value from this 
			Vec2<type>& operator-=(type val) noexcept
			{
				x -= val;
				y -= val;
				return *this;
			}
			//substract another vec2 from this 
			Vec2<type>& operator-=(const Vec2<type>& other) noexcept
			{
				x -= other.x;
				y -= other.y;
				return *this;
			}
			//substract another vec2 from this 
			Vec2<type>& operator-=(Vec2<type>&& other) noexcept
			{
				x -= other.x;
				y -= other.y;
				return *this;
			}
			//multiply a value to this | elementwise, not dotproduct
			Vec2<type>& operator*=(type val) noexcept
			{
				x *= val;
				y *= val;
				return *this;
			}
			//multiply another vec2 to this | elementwise, not dotproduct
			Vec2<type>& operator*=(const Vec2<type>& other) noexcept
			{
				x *= other.x;
				y *= other.y;
				return *this;
			}
			//multiply another vec2 to this | elementwise, not dotproduct
			Vec2<type>& operator*=(Vec2<type>&& other) noexcept
			{
				x *= other.x;
				y *= other.y;
				return *this;
			}
			//divide a value from this 
			Vec2<type>& operator/=(type val) noexcept
			{
				x /= val;
				y /= val;
				return *this;
			}
			//divide another vec2 from this 
			Vec2<type>& operator/=(const Vec2<type>& other) noexcept
			{
				x /= other.x;
				y /= other.y;
				return *this;
			}
			//divide another vec2 from this 
			Vec2<type>& operator/=(Vec2<type>&& other) noexcept
			{
				x /= other.x;
				y /= other.y;
				return *this;
			}
			//add another vec3 to this 
			Vec2<type>& operator+=(const Vec3<type>& other) noexcept;
			//add another vec3 to this 
			Vec2<type>& operator+=(Vec3<type>&& other) noexcept;
			//add another vec4 to this 
			Vec2<type>& operator+=(const Vec4<type>& other) noexcept;
			//add another vec4 to this 
			Vec2<type>& operator+=(Vec4<type>&& other) noexcept;
			//substract another vec3 from this 
			Vec2<type>& operator-=(const Vec3<type>& other) noexcept;
			//substract another vec3 from this 
			Vec2<type>& operator-=(Vec3<type>&& other) noexcept;
			//substract another vec4 from this 
			Vec2<type>& operator-=(const Vec4<type>& other) noexcept;
			//substract another vec4 from this 
			Vec2<type>& operator-=(Vec4<type>&& other) noexcept;
			//multiply another vec3 to this | elementwise, not dotproduct
			Vec2<type>& operator*=(const Vec3<type>& other) noexcept;
			//multiply another vec3 to this | elementwise, not dotproduct
			Vec2<type>& operator*=(Vec3<type>&& other) noexcept;
			//multiply another vec4 to this | elementwise, not dotproduct
			Vec2<type>& operator*=(const Vec4<type>& other) noexcept;
			//multiply another vec4 to this | elementwise, not dotproduct
			Vec2<type>& operator*=(Vec4<type>&& other) noexcept;
			//divide another vec3 from this 
			Vec2<type>& operator/=(const Vec3<type>& other) noexcept;
			//divide another vec3 from this 
			Vec2<type>& operator/=(Vec3<type>&& other) noexcept;
			//divide another vec4 from this 
			Vec2<type>& operator/=(const Vec4<type>& other) noexcept;
			//divide another vec4 from this 
			Vec2<type>& operator/=(Vec4<type>&& other) noexcept;
			//compare all values to another lvalue vec2 
			bool operator==(const Vec2<type>& other) const noexcept
			{
				return x == other.x && y == other.y;
			}
			//compare all values to another rvalue vec2
			bool operator==(Vec2<type>&& other) const noexcept
			{
				return x == other.x && y == other.y;
			}
			//compare all values to another lvalue vec2
			bool operator!=(const Vec2<type>& other) const noexcept
			{
				return x != other.x || y != other.y;
			}
			//compare all values to another rvalue vec2
			bool operator!=(Vec2<type>&& other) const noexcept
			{
				return x != other.x || y != other.y;
			}
			//compare all values to another lvalue vec2 | values are added up
			bool operator<=(const Vec2<type>& other) const noexcept
			{
				return ( x + y ) <= ( other.x + other.y );
			}
			//compare all values to another rvalue vec2 | values are added up
			bool operator<=(Vec2<type>&& other) const noexcept
			{
				return ( x + y ) <= ( other.x + other.y );
			}
			//compare all values to another lvalue vec2 | values are added up
			bool operator>=(const Vec2<type>& other) const noexcept
			{
				return ( x + y ) >= ( other.x + other.y );
			}
			//compare all values to another rvalue vec2 | values are added up
			bool operator>=(Vec2<type>&& other) const noexcept
			{
				return ( x + y ) >= ( other.x + other.y );
			}
			//compare all values to another lvalue vec2 | values are added up
			bool operator<(const Vec2<type>& other) const noexcept
			{
				return ( x + y ) < ( other.x + other.y );
			}
			//compare all values to another rvalue vec2 | values are added up
			bool operator<(Vec2<type>&& other) const noexcept
			{
				return ( x + y ) < ( other.x + other.y );
			}
			//compare all values to another lvalue vec2 | values are added up
			bool operator>(const Vec2<type>& other) const noexcept
			{
				return ( x + y ) > ( other.x + other.y );
			}
			//compare all values to another rvalue vec2 | values are added up
			bool operator>(Vec2<type>&& other) const noexcept
			{
				return ( x + y ) > ( other.x + other.y );
			}


			//add a rvalue vec2 object to a rvalue vec2 object
			friend Vec2<type>&& operator+(Vec2<type>&& v1, Vec2<type>&& v2) noexcept
			{
				v1.x += v2.x;
				v1.y += v2.y;
				return std::move(v1);
			}
			//add a rvalue vec2 object to a lvalue vec2 object 
			friend Vec2<type>&& operator+(const Vec2<type>& v1, Vec2<type>&& v2) noexcept
			{
				v2.x += v1.x;
				v2.y += v1.y;
				return std::move(v2);
			}
			//add a lvalue vec2 object to a rvalue vec2 object
			friend Vec2<type>&& operator+(Vec2<type>&& v1, const Vec2<type>& v2) noexcept
			{
				v1.x += v2.x;
				v1.y += v2.y;
				return std::move(v1);
			}
			//add a type to a lvalue vec2 object
			friend Vec2<type> operator+(const Vec2<type>& vec, type val) noexcept
			{
				return Vec2<type>(vec.x + val, vec.y + val);
			}
			//add a lvalue vec2 object to a lvalue vec2 object
			friend Vec2<type> operator+(const Vec2<type>& v1, const Vec2<type>& v2) noexcept
			{
				return Vec2<type>(v1.x + v2.x, v1.y + v2.y);
			}
			//add a rvalue vec3 object to a rvalue vec2 object
			friend Vec2<type>&& operator+<type>( Vec2<type>&& v1, Vec3<type>&& v2 ) noexcept;
			//add a lvalue vec3 object to a rvalue vec2 object
			friend Vec2<type>&& operator+<type>( Vec2<type>&& v1, const Vec3<type>& v2 ) noexcept;
			//add a lvalue vec3 object to a lvalue vec2 object
			friend Vec2<type> operator+<type>( const Vec2<type>& v1, const Vec3<type>& v2 ) noexcept;
			//add a rvalue vec4 object to a rvalue vec2 object
			friend Vec2<type>&& operator+<type>( Vec2<type>&& v1, Vec4<type>&& v2 ) noexcept;
			//add a lvalue vec4 object to a rvalue vec2 object
			friend Vec2<type>&& operator+<type>( Vec2<type>&& v1, const Vec4<type>& v2 ) noexcept;
			//add a lvalue vec4 object to a lvalue vec2 object
			friend Vec2<type> operator+<type>( const Vec2<type>& v1, const Vec4<type>& v2 ) noexcept;
			//substract a rvalue vec2 object from a rvalue vec2 object
			friend Vec2<type>&& operator-(Vec2<type>&& v1, Vec2<type>&& v2) noexcept
			{
				v1.x -= v2.x;
				v1.y -= v2.y;
				return std::move(v1);
			}
			//substract a rvalue vec2 object from a lvalue vec2 object 
			friend Vec2<type> operator-(const Vec2<type>& v1, Vec2<type>&& v2) noexcept
			{
				return Vec2<type>(v1.x - v2.x, v1.y - v2.y);
			}
			//substract a lvalue vec2 object from a rvalue vec2 object
			friend Vec2<type>&& operator-(Vec2<type>&& v1, const Vec2<type>& v2) noexcept
			{
				v1.x -= v2.x;
				v1.y -= v2.y;
				return std::move(v1);
			}
			//substract a type from a lvalue vec2 object
			friend Vec2<type> operator-(const Vec2<type>& vec, type val) noexcept
			{
				return Vec2<type>(vec.x - val, vec.y - val);
			}
			//substract a lvalue vec2 object from a lvalue vec2 object
			friend Vec2<type> operator-(const Vec2<type>& v1, const Vec2<type>& v2) noexcept
			{
				return Vec2<type>(v1.x - v2.x, v1.y - v2.y);
			}
			//substract a rvalue vec3 object from a rvalue vec2 object
			friend Vec2<type>&& operator-<type>( Vec2<type>&& v1, Vec3<type>&& v2 ) noexcept;
			//substract a lvalue vec3 object from a rvalue vec2 object
			friend Vec2<type>&& operator-<type>( Vec2<type>&& v1, const Vec3<type>& v2 ) noexcept;
			//substract a lvalue vec3 object from a lvalue vec2 object
			friend Vec2<type> operator-<type>( const Vec2<type>& v1, const Vec3<type>& v2 ) noexcept;
			//substract a rvalue vec4 object from a rvalue vec2 object
			friend Vec2<type>&& operator-<type>( Vec2<type>&& v1, Vec4<type>&& v2 ) noexcept;
			//substract a lvalue vec4 object from a rvalue vec2 object
			friend Vec2<type>&& operator-<type>( Vec2<type>&& v1, const Vec4<type>& v2 ) noexcept;
			//substract a lvalue vec4 object from a lvalue vec2 object
			friend Vec2<type> operator-<type>( const Vec2<type>& v1, const Vec4<type>& v2 ) noexcept;
			//multiply a rvalue vec2 object to a rvalue vec2 object | elementwise, not dotproduct
			friend Vec2<type>&& operator*(Vec2<type>&& v1, Vec2<type>&& v2) noexcept
			{
				v1.x *= v2.x;
				v1.y *= v2.y;
				return std::move(v1);
			}
			//multiply a rvalue vec2 object to a lvalue vec2 object | elementwise, not dotproduct
			friend Vec2<type>&& operator*(const Vec2<type>& v1, Vec2<type>&& v2) noexcept
			{
				v2.x *= v1.x;
				v2.y *= v1.y;
				return std::move(v2);
			}
			//multiply a lvalue vec2 object to a rvalue vec2 object | elementwise, not dotproduct
			friend Vec2<type>&& operator*(Vec2<type>&& v1, const Vec2<type>& v2) noexcept
			{
				v1.x *= v2.x;
				v1.y *= v2.y;
				return std::move(v1);
			}
			//multiply a type to a lvalue vec2 object | elementwise, not dotproduct
			friend Vec2<type> operator*(type val, const Vec2<type>& vec) noexcept
			{
				return Vec2<type>(vec.x * val, vec.y * val);
			}
			//multiply a type to a lvalue vec2 object | elementwise, not dotproduct
			friend Vec2<type> operator*(const Vec2<type>& vec, type val) noexcept
			{
				return Vec2<type>(vec.x * val, vec.y * val);
			}
			//multiply a lvalue vec2 object to a lvalue vec2 object | elementwise, not dotproduct
			friend Vec2<type> operator*(const Vec2<type>& v1, const Vec2<type>& v2) noexcept
			{
				return Vec2<type>(v1.x * v2.x, v1.y * v2.y);
			}
			//multiply a rvalue vec3 object to a rvalue vec2 object | elementwise, not dotproduct
			friend Vec2<type>&& operator*<type>( Vec2<type>&& v1, Vec3<type>&& v2 ) noexcept;
			//multiply a lvalue vec3 object to a rvalue vec2 object | elementwise, not dotproduct
			friend Vec2<type>&& operator*<type>( Vec2<type>&& v1, const Vec3<type>& v2 ) noexcept;
			//multiply a lvalue vec3 object to a lvalue vec2 object | elementwise, not dotproduct
			friend Vec2<type> operator*<type>( const Vec2<type>& v1, const Vec3<type>& v2 ) noexcept;
			//multiply a rvalue vec4 object to a rvalue vec2 object | elementwise, not dotproduct
			friend Vec2<type>&& operator*<type>( Vec2<type>&& v1, Vec4<type>&& v2 ) noexcept;
			//multiply a lvalue vec4 object to a rvalue vec2 object | elementwise, not dotproduct
			friend Vec2<type>&& operator*<type>( Vec2<type>&& v1, const Vec4<type>& v2 ) noexcept;
			//multiply a lvalue vec4 object to a lvalue vec2 object | elementwise, not dotproduct
			friend Vec2<type> operator*<type>( const Vec2<type>& v1, const Vec4<type>& v2 ) noexcept;
			//divide a rvalue vec2 object from a rvalue vec2 object
			friend Vec2<type>&& operator/(Vec2<type>&& v1, Vec2<type>&& v2) noexcept
			{
				v1.x /= v2.x;
				v1.y /= v2.y;
				return std::move(v1);
			}
			//divide a rvalue vec2 object from a lvalue vec2 object 
			friend Vec2<type> operator/(const Vec2<type>& v1, Vec2<type>&& v2) noexcept
			{
				return Vec2<type>(v1.x / v2.x, v1.y / v2.y);
			}
			//divide a lvalue vec2 object from a rvalue vec2 object
			friend Vec2<type>&& operator/(Vec2<type>&& v1, const Vec2<type>& v2) noexcept
			{
				v1.x /= v2.x;
				v1.y /= v2.y;
				return std::move(v1);
			}
			//divide a type from a lvalue vec2 object
			friend Vec2<type> operator/(const Vec2<type>& vec, type val) noexcept
			{
				return Vec2<type>(vec.x / val, vec.y / val);
			}
			//divide a lvalue vec2 object from a lvalue vec2 object
			friend Vec2<type> operator/(const Vec2<type>& v1, const Vec2<type>& v2) noexcept
			{
				return Vec2<type>(v1.x / v2.x, v1.y / v2.y);
			}
			//divide a rvalue vec3 object from a rvalue vec2 object
			friend Vec2<type>&& operator/<type>( Vec2<type>&& v1, Vec3<type>&& v2 ) noexcept;
			//divide a lvalue vec3 object from a rvalue vec2 object
			friend Vec2<type>&& operator/<type>( Vec2<type>&& v1, const Vec3<type>& v2 ) noexcept;
			//divide a lvalue vec3 object from a lvalue vec2 object
			friend Vec2<type> operator/<type>( const Vec2<type>& v1, const Vec3<type>& v2 ) noexcept;
			//divide a rvalue vec4 object from a rvalue vec2 object
			friend Vec2<type>&& operator/<type>( Vec2<type>&& v1, Vec4<type>&& v2 ) noexcept;
			//divide a lvalue vec4 object from a rvalue vec2 object
			friend Vec2<type>&& operator/<type>( Vec2<type>&& v1, const Vec4<type>& v2 ) noexcept;
			//divide a lvalue vec4 object from a lvalue vec2 object
			friend Vec2<type> operator/<type>( const Vec2<type>& v1, const Vec4<type>& v2 ) noexcept;
			//modulo a vec2 with a number(only works with int and will take int values)
			friend Vec2<type> operator%(const Vec2<type>& vec, int val) noexcept
			{
				return Vec2<type>(static_cast<int>( vec.x ) % val, static_cast<int>( vec.y ) % val);
			}

		public:
			//const read-only position access x=0, y=1
			const type operator[](unsigned short position) const noexcept
			{
				return data[position];
			}
			//position access x=0, y=1
			type& operator[](unsigned short position) noexcept
			{
				return data[position];
			}
			//|vec| returns the lenght of the vec/direct distance from origin vec(0,0) | std::sqrt(x * x + y * y)
			type magnitude() const noexcept
			{
				return std::sqrt(x * x + y * y);
			}
			//|vec| returns the lenght of the vec/direct distance from origin vec(0,0,0,0) | the fast method
			type fastLenght() const noexcept
			{
				type result = 0;
				if ( x < 0 )
					result += -x;
				else
					result += x;
				if ( y < 0 )
					result += -y;
				else
					result += y;
				return result;
			}
			//std::sqrt(vec*vec) returns the not negative value of the vec as a copie of the vec
			Vec2<type> abs() const noexcept
			{
				return Vec2<type>(std::sqrt(x*x), std::sqrt(y*y));
			}
			//std::sqrt(vec*vec) converts the vec itself to its not negative value
			Vec2<type>& absSelf() noexcept
			{
				x = std::sqrt(x*x);
				y = std::sqrt(y*y);
				return *this;
			}
			//vec(x/magnitude(), y/magnitude()) returns a normalized copy of the vec relative to the lenght of the vec | also called called unit vector, because the magnitude/lenght of the vector is always one 
			Vec2<type> normalize() const noexcept
			{
				return Vec2<type>(x / std::sqrt(x * x + y * y), y / std::sqrt(x * x + y * y));
			}
			//vec(x/magnitude(), y/magnitude()) normalize the vec itself relative to the lenght of the vec | also called called unit vector, because the magnitude/lenght of the vector is always one 
			Vec2<type>& normalizeSelf() noexcept
			{
				type scale = std::sqrt(x * x + y * y);
				x /= scale;
				y /= scale;
				return *this;
			}
			//|vec1-vec2| returns the direct distance to another vec | std::sqrt(( x - other.x ) * ( x - other.x ) + ( y - other.y ) * ( y - other.y ))
			type distance(const Vec2<type>& other) const noexcept
			{
				return std::sqrt(( x - other.x ) * ( x - other.x ) + ( y - other.y ) * ( y - other.y ));
			}
			//|vec1-vec2| can be used to compare distances, will return the non negative value of the components added together 
			type distanceFast(const Vec2<type>& other) const noexcept
			{
				type tempx;
				if ( other.x < x )
					tempx = x - other.x;
				else
					tempx = other.x - x;
				type tempy;
				if ( other.y < y )
					tempy = y - other.y;
				else
					tempy = other.y - y;
				return tempx + tempy;
			}
			/*vec1*vec2 = |vec1|*|vec2|*cos(vec1,vec2) returns the dotproduct of 2 vecs, vecs are orthogonal(_|_) if the result is 0 and vecs are parallel if the result is 1(||) | x * other.x + y * other.y | not the normal multiply method 
			its more efficient than comparing the vecs with the magnitude method*/
			type dotproduct(const Vec2<type>& other) const noexcept
			{
				return x * other.x + y * other.y;
			}
			/*vec1*vec2 = |vec1|*|vec2|*cos(vec1,vec2) returns the dotproduct of 2 vecs, vecs are orthogonal(_|_) if the result is 0 and vecs are parallel if the result is 1(||) | x * other.x + y * other.y | not the normal multiply method 
			its more efficient than comparing the vecs with the magnitude method*/
			type dotproduct(Vec2<type>&& other) const noexcept
			{
				return x * other.x + y * other.y;
			}
			//acos(dotproduct() / (magnitude()*other.magnitude())) returns the angle between 2 vecs in radians 
			type angleR(const Vec2<type>& other) const noexcept
			{
				return std::acos(( x * other.x + y * other.y ) / ( std::sqrt(x * x + y * y) * std::sqrt(other.x * other.x + other.y * other.y) ));
			}
			//acos(dotproduct() / (magnitude()*other.magnitude())) returns the angle between 2 vecs in radians 
			type angleR(Vec2<type>&& other) const noexcept
			{
				return std::acos(( x * other.x + y * other.y ) / ( std::sqrt(x * x + y * y) * std::sqrt(other.x * other.x + other.y * other.y) ));
			}
			//acos(dotproduct() / (magnitude()*other.magnitude())) returns the angle between 2 vecs in degrees 
			type angleD(const Vec2<type>& other) const noexcept
			{
				return std::acos(( x * other.x + y * other.y ) / ( std::sqrt(x * x + y * y) * std::sqrt(other.x * other.x + other.y * other.y) ))*( 180.0 / 3.14159265359 );
			}
			//acos(dotproduct() / (magnitude()*other.magnitude())) returns the angle between 2 vecs in degrees 
			type angleD(Vec2<type>&& other) const noexcept
			{
				return std::acos(( x * other.x + y * other.y ) / ( std::sqrt(x * x + y * y) * std::sqrt(other.x * other.x + other.y * other.y) ))*( 180.0 / 3.14159265359 );
			}
			//|vec1xvec2| returns the area of the 2 vecs, also is the magnitude of the crossproduct
			type area(const Vec2<type>& other) const noexcept
			{
				return x * other.y - y * other.x;
			}
			//|vec1xvec2| returns the area of the 2 vecs, also is the magnitude of the crossproduct
			type area(Vec2<type>&& other) const noexcept
			{
				return x * other.y - y * other.x;
			}
			//vec as string: "Vec2<type>(x,y)"
			std::string toString() const noexcept
			{
				std::stringstream stream;
				stream << "Vec2<" << typeid( type ).name() << ">(" << x << "," << y << ")";
				return stream.str();
			}
			//ostream operator: "Vec2<type>(x,y)"
			friend std::ostream& operator<<(std::ostream& stream, const Vec2<type>& vec) noexcept
			{
				stream << "Vec2<" << typeid( type ).name() << ">(" << vec.x << "," << vec.y << ")";
				return stream;
			}


		};

	}
}

#include "Vec3.h"
#include "Vec4.h"

namespace clockwork {
	namespace maths {

		//vec3 copy constructor
		template<typename type>Vec2<type>::Vec2(const Vec3<type>& other) noexcept
			:x(other.x), y(other.y)
		{}
		//vec3 move constructor
		template<typename type>Vec2<type>::Vec2(Vec3<type>&& other) noexcept
			: x(std::move(other.x)), y(std::move(other.y))
		{}
		//vec4 copy constructor
		template<typename type>Vec2<type>::Vec2(const Vec4<type>& other) noexcept
			: x(other.x), y(other.y)
		{}
		//vec4 move constructor
		template<typename type>Vec2<type>::Vec2(Vec4<type>&& other) noexcept
			: x(std::move(other.x)), y(std::move(other.y))
		{}
		//vec3 assign operator
		template<typename type>Vec2<type>& Vec2<type>::operator=(const Vec3<type>& other) noexcept
		{
			x = other.x;
			y = other.y;
			return *this;
		}
		//vec3 move operator
		template<typename type>Vec2<type>& Vec2<type>::operator=(Vec3<type>&& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
			return *this;
		}
		//vec4 assign operator
		template<typename type>Vec2<type>& Vec2<type>::operator=(const Vec4<type>& other) noexcept
		{
			x = other.x;
			y = other.y;
			return *this;
		}
		//vec4 move operator
		template<typename type>Vec2<type>& Vec2<type>::operator=(Vec4<type>&& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
			return *this;
		}

		//add another vec3 to this 
		template<typename type>Vec2<type>& Vec2<type>::add(const Vec3<type>& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another vec3 to this 
		template<typename type>Vec2<type>& Vec2<type>::add(Vec3<type>&& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another vec4 to this 
		template<typename type>Vec2<type>& Vec2<type>::add(const Vec4<type>& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another vec4 to this 
		template<typename type>Vec2<type>& Vec2<type>::add(Vec4<type>&& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//substract another vec3 from this 
		template<typename type>Vec2<type>& Vec2<type>::substract(const Vec3<type>& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another vec3 from this 
		template<typename type>Vec2<type>& Vec2<type>::substract(Vec3<type>&& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another vec4 from this 
		template<typename type>Vec2<type>& Vec2<type>::substract(const Vec4<type>& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another vec4 from this 
		template<typename type>Vec2<type>& Vec2<type>::substract(Vec4<type>&& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//multiply another vec3 to this | elementwise, not dotproduct
		template<typename type>Vec2<type>& Vec2<type>::multiply(const Vec3<type>& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another vec3 to this | elementwise, not dotproduct
		template<typename type>Vec2<type>& Vec2<type>::multiply(Vec3<type>&& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another vec4 to this | elementwise, not dotproduct
		template<typename type>Vec2<type>& Vec2<type>::multiply(const Vec4<type>& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another vec4 to this | elementwise, not dotproduct
		template<typename type>Vec2<type>& Vec2<type>::multiply(Vec4<type>&& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//divide another vec3 from this 
		template<typename type>Vec2<type>& Vec2<type>::divide(const Vec3<type>& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another vec3 from this 
		template<typename type>Vec2<type>& Vec2<type>::divide(Vec3<type>&& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another vec4 from this 
		template<typename type>Vec2<type>& Vec2<type>::divide(const Vec4<type>& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another vec4 from this 
		template<typename type>Vec2<type>& Vec2<type>::divide(Vec4<type>&& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}

		//add another vec3 to this 
		template<typename type>Vec2<type>& Vec2<type>::operator+=(const Vec3<type>& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another vec3 to this 
		template<typename type>Vec2<type>& Vec2<type>::operator+=(Vec3<type>&& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another vec4 to this 
		template<typename type>Vec2<type>& Vec2<type>::operator+=(const Vec4<type>& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another vec4 to this 
		template<typename type>Vec2<type>& Vec2<type>::operator+=(Vec4<type>&& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//substract another vec3 from this 
		template<typename type>Vec2<type>& Vec2<type>::operator-=(const Vec3<type>& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another vec3 from this 
		template<typename type>Vec2<type>& Vec2<type>::operator-=(Vec3<type>&& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another vec4 from this 
		template<typename type>Vec2<type>& Vec2<type>::operator-=(const Vec4<type>& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another vec4 from this 
		template<typename type>Vec2<type>& Vec2<type>::operator-=(Vec4<type>&& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//multiply another vec3 to this | elementwise, not dotproduct
		template<typename type>Vec2<type>& Vec2<type>::operator*=(const Vec3<type>& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another vec3 to this | elementwise, not dotproduct
		template<typename type>Vec2<type>& Vec2<type>::operator*=(Vec3<type>&& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another vec4 to this | elementwise, not dotproduct
		template<typename type>Vec2<type>& Vec2<type>::operator*=(const Vec4<type>& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another vec4 to this | elementwise, not dotproduct
		template<typename type>Vec2<type>& Vec2<type>::operator*=(Vec4<type>&& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//divide another vec3 from this 
		template<typename type>Vec2<type>& Vec2<type>::operator/=(const Vec3<type>& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another vec3 from this 
		template<typename type>Vec2<type>& Vec2<type>::operator/=(Vec3<type>&& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another vec4 from this 
		template<typename type>Vec2<type>& Vec2<type>::operator/=(const Vec4<type>& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another vec4 from this 
		template<typename type>Vec2<type>& Vec2<type>::operator/=(Vec4<type>&& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}


		//add a rvalue vec3 object to a rvalue vec2 object
		template<typename type>Vec2<type>&& operator+(Vec2<type>&& v1, Vec3<type>&& v2) noexcept
		{
			v1.x += v2.x;
			v1.y += v2.y;
			return std::move(v1);
		}
		//add a lvalue vec3 object to a rvalue vec2 object
		template<typename type>Vec2<type>&& operator+(Vec2<type>&& v1, const Vec3<type>& v2) noexcept
		{
			v1.x += v2.x;
			v1.y += v2.y;
			return std::move(v1);
		}
		//add a lvalue vec3 object to a lvalue vec2 object
		template<typename type>Vec2<type> operator+(const Vec2<type>& v1, const Vec3<type>& v2) noexcept
		{
			return Vec2<type>(v1.x + v2.x, v1.y + v2.y);
		}
		//add a rvalue vec4 object to a rvalue vec2 object
		template<typename type>Vec2<type>&& operator+(Vec2<type>&& v1, Vec4<type>&& v2) noexcept
		{
			v1.x += v2.x;
			v1.y += v2.y;
			return std::move(v1);
		}
		//add a lvalue vec4 object to a rvalue vec2 object
		template<typename type>Vec2<type>&& operator+(Vec2<type>&& v1, const Vec4<type>& v2) noexcept
		{
			v1.x += v2.x;
			v1.y += v2.y;
			return std::move(v1);
		}
		//add a lvalue vec4 object to a lvalue vec2 object
		template<typename type>Vec2<type> operator+(const Vec2<type>& v1, const Vec4<type>& v2) noexcept
		{
			return Vec2<type>(v1.x + v2.x, v1.y + v2.y);
		}
		//substract a rvalue vec3 object from a rvalue vec2 object
		template<typename type>Vec2<type>&& operator-(Vec2<type>&& v1, Vec3<type>&& v2) noexcept
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			return std::move(v1);
		}
		//substract a lvalue vec3 object from a rvalue vec2 object
		template<typename type>Vec2<type>&& operator-(Vec2<type>&& v1, const Vec3<type>& v2) noexcept
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			return std::move(v1);
		}
		//substract a lvalue vec3 object from a lvalue vec2 object
		template<typename type>Vec2<type> operator-(const Vec2<type>& v1, const Vec3<type>& v2) noexcept
		{
			return Vec2<type>(v1.x - v2.x, v1.y - v2.y);
		}
		//substract a rvalue vec4 object from a rvalue vec2 object
		template<typename type>Vec2<type>&& operator-(Vec2<type>&& v1, Vec4<type>&& v2) noexcept
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			return std::move(v1);
		}
		//substract a lvalue vec4 object from a rvalue vec2 object
		template<typename type>Vec2<type>&& operator-(Vec2<type>&& v1, const Vec4<type>& v2) noexcept
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			return std::move(v1);
		}
		//substract a lvalue vec4 object from a lvalue vec2 object
		template<typename type>Vec2<type> operator-(const Vec2<type>& v1, const Vec4<type>& v2) noexcept
		{
			return Vec2<type>(v1.x - v2.x, v1.y - v2.y);
		}
		//multiply a rvalue vec3 object to a rvalue vec2 object | elementwise, not dotproduct
		template<typename type>Vec2<type>&& operator*(Vec2<type>&& v1, Vec3<type>&& v2) noexcept
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			return std::move(v1);
		}
		//multiply a lvalue vec3 object to a rvalue vec2 object | elementwise, not dotproduct
		template<typename type>Vec2<type>&& operator*(Vec2<type>&& v1, const Vec3<type>& v2) noexcept
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			return std::move(v1);
		}
		//multiply a lvalue vec3 object to a lvalue vec2 object | elementwise, not dotproduct
		template<typename type>Vec2<type> operator*(const Vec2<type>& v1, const Vec3<type>& v2) noexcept
		{
			return Vec2<type>(v1.x * v2.x, v1.y * v2.y);
		}
		//multiply a rvalue vec4 object to a rvalue vec2 object | elementwise, not dotproduct
		template<typename type>Vec2<type>&& operator*(Vec2<type>&& v1, Vec4<type>&& v2) noexcept
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			return std::move(v1);
		}
		//multiply a lvalue vec4 object to a rvalue vec2 object | elementwise, not dotproduct
		template<typename type>Vec2<type>&& operator*(Vec2<type>&& v1, const Vec4<type>& v2) noexcept
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			return std::move(v1);
		}
		//multiply a lvalue vec4 object to a lvalue vec2 object | elementwise, not dotproduct
		template<typename type>Vec2<type> operator*(const Vec2<type>& v1, const Vec4<type>& v2) noexcept
		{
			return Vec2<type>(v1.x * v2.x, v1.y * v2.y);
		}
		//divide a rvalue vec3 object from a rvalue vec2 object
		template<typename type>Vec2<type>&& operator/(Vec2<type>&& v1, Vec3<type>&& v2) noexcept
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			return std::move(v1);
		}
		//divide a lvalue vec3 object from a rvalue vec2 object
		template<typename type>Vec2<type>&& operator/(Vec2<type>&& v1, const Vec3<type>& v2) noexcept
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			return std::move(v1);
		}
		//divide a lvalue vec3 object from a lvalue vec2 object
		template<typename type>Vec2<type> operator/(const Vec2<type>& v1, const Vec3<type>& v2) noexcept
		{
			return Vec2<type>(v1.x / v2.x, v1.y / v2.y);
		}
		//divide a rvalue vec4 object from a rvalue vec2 object
		template<typename type>Vec2<type>&& operator/(Vec2<type>&& v1, Vec4<type>&& v2) noexcept
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			return std::move(v1);
		}
		//divide a lvalue vec4 object from a rvalue vec2 object
		template<typename type>Vec2<type>&& operator/(Vec2<type>&& v1, const Vec4<type>& v2) noexcept
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			return std::move(v1);
		}
		//divide a lvalue vec4 object from a lvalue vec2 object
		template<typename type>Vec2<type> operator/(const Vec2<type>& v1, const Vec4<type>& v2) noexcept
		{
			return Vec2<type>(v1.x / v2.x, v1.y / v2.y);
		}




		using Vec2f = Vec2<float>;

	}
}