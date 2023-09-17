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

		template<typename type> Vec4<type>&& operator+(Vec4<type>&& v1, Vec2<type>&& v2) noexcept;
		template<typename type> Vec4<type>&& operator+(Vec4<type>&& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec4<type> operator+(const Vec4<type>& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec4<type>&& operator+(Vec4<type>&& v1, Vec3<type>&& v2) noexcept;
		template<typename type> Vec4<type>&& operator+(Vec4<type>&& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec4<type> operator+(const Vec4<type>& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec4<type>&& operator-(Vec4<type>&& v1, Vec2<type>&& v2) noexcept;
		template<typename type> Vec4<type>&& operator-(Vec4<type>&& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec4<type> operator-(const Vec4<type>& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec4<type>&& operator-(Vec4<type>&& v1, Vec3<type>&& v2) noexcept;
		template<typename type> Vec4<type>&& operator-(Vec4<type>&& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec4<type> operator-(const Vec4<type>& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec4<type>&& operator*(Vec4<type>&& v1, Vec2<type>&& v2) noexcept;
		template<typename type> Vec4<type>&& operator*(Vec4<type>&& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec4<type> operator*(const Vec4<type>& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec4<type>&& operator*(Vec4<type>&& v1, Vec3<type>&& v2) noexcept;
		template<typename type> Vec4<type>&& operator*(Vec4<type>&& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec4<type> operator*(const Vec4<type>& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec4<type>&& operator/(Vec4<type>&& v1, Vec2<type>&& v2) noexcept;
		template<typename type> Vec4<type>&& operator/(Vec4<type>&& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec4<type> operator/(const Vec4<type>& v1, const Vec2<type>& v2) noexcept;
		template<typename type> Vec4<type>&& operator/(Vec4<type>&& v1, Vec3<type>&& v2) noexcept;
		template<typename type> Vec4<type>&& operator/(Vec4<type>&& v1, const Vec3<type>& v2) noexcept;
		template<typename type> Vec4<type> operator/(const Vec4<type>& v1, const Vec3<type>& v2) noexcept;
		template<typename type>Vec4<type> operator-(Vec4<type> vec) noexcept;

		template<typename type>
		struct Vec4
		{

		public:
			union
			{
				struct
				{
					type x;
					type y;
					type z;
					type w;
				};
				struct
				{
					type r;
					type g;
					type b;
					type a;
				};
				struct
				{
					type s;
					type t;
					type p;
					type q;
				};
				type data[4];
			};

		public:
			//default constructor
			Vec4() noexcept
				:x(0), y(0), z(0), w(0)
			{}
			//1 value for all constructor
			explicit Vec4(type val) noexcept
				:x(val), y(val), z(val), w(val)
			{}
			//seperate values constructor
			Vec4(type x, type y, type z, type w) noexcept
				:x(x), y(y), z(z), w(w)
			{}
			//vector constructor
			explicit Vec4(const std::vector<type>& other) noexcept
			{
				x = other.at(0);
				y = other.at(1);
				z = other.at(2);
				w = other.at(3);
			}
			//vec4 copy constructor
			Vec4(const Vec4<type>& other) noexcept
				:x(other.x), y(other.y), z(other.z), w(other.w)
			{}
			//vec4 move constructor
			Vec4(Vec4<type>&& other) noexcept
				:x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)), w(std::move(other.w))
			{}
			//vec4 assign operator
			Vec4<type>& operator=(const Vec4<type>& other) noexcept
			{
				x = other.x;
				y = other.y;
				z = other.z;
				w = other.w;
				return *this;
			}
			//vec4 move operator
			Vec4<type>& operator=(Vec4<type>&& other) noexcept
			{
				x = std::move(other.x);
				y = std::move(other.y);
				z = std::move(other.z);
				w = std::move(other.w);
				return *this;
			}
			//vec2 copy constructor 
			explicit Vec4(const Vec2<type>& other) noexcept;
			//vec2 move constructor 
			explicit Vec4(Vec2<type>&& other) noexcept;
			//vec3 copy constructor
			explicit Vec4(const Vec3<type>& other) noexcept;
			//vec3 move constructor
			explicit Vec4(Vec3<type>&& other) noexcept;
			//vec2 assign operator
			Vec4<type>& operator=(const Vec2<type>& other) noexcept;
			//vec2 move operator
			Vec4<type>& operator=(Vec2<type>&& other) noexcept;
			//vec3 assign operator
			Vec4<type>& operator=(const Vec3<type>& other) noexcept;
			//vec3 move operator
			Vec4<type>& operator=(Vec3<type>&& other) noexcept;

			//Vec4 other type copy constructor
			template<typename othertype>
			explicit Vec4(const Vec4<othertype>& other) noexcept
				:x(static_cast<type>( other.x )), y(static_cast<type>( other.y )), z(static_cast<type>( other.z )), w(static_cast<type>( other.w ))
			{}
			//Vec4 other type move constructor
			template<typename othertype>
			explicit Vec4(Vec4<othertype>&& other) noexcept
				: x(static_cast<type>( std::move(other.x) )), y(static_cast<type>( std::move(other.y) )), z(static_cast<type>( std::move(other.z) )), w(static_cast<type>( std::move(other.w) ))
			{}
			//Vec4 other type assign operator
			template<typename othertype>
			Vec4<type>& operator=(const Vec4<othertype>& other) noexcept
			{
				x = static_cast<type>( other.x );
				y = static_cast<type>( other.y );
				z = static_cast<type>( other.z );
				w = static_cast<type>( other.w );
				return *this;
			}
			//Vec4 other type move operator
			template<typename othertype>
			Vec4<type>& operator=(Vec4<othertype>&& other) noexcept
			{
				x = static_cast<type>( std::move(other.x) );
				y = static_cast<type>( std::move(other.y) );
				z = static_cast<type>( std::move(other.z) );
				w = static_cast<type>( std::move(other.w) );
				return *this;
			}

		public:
			//add a value to this 
			Vec4<type>& add(type val) noexcept
			{
				x += val;
				y += val;
				z += val;
				w += val;
				return *this;
			}
			//add another Vec4 to this 
			Vec4<type>& add(const Vec4<type>& other) noexcept
			{
				x += other.x;
				y += other.y;
				z += other.z;
				w += other.w;
				return *this;
			}
			//add another Vec4 to this 
			Vec4<type>& add(Vec4<type>&& other) noexcept
			{
				x += other.x;
				y += other.y;
				z += other.z;
				w += other.w;
				return *this;
			}
			//substract a value from this 
			Vec4<type>& substract(type val) noexcept
			{
				x -= val;
				y -= val;
				z -= val;
				w -= val;
				return *this;
			}
			//substract another Vec4 from this 
			Vec4<type>& substract(const Vec4<type>& other) noexcept
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				w -= other.w;
				return *this;
			}
			//substract another Vec4 from this 
			Vec4<type>& substract(Vec4<type>&& other) noexcept
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				w -= other.w;
				return *this;
			}
			//multiply a value to this | elementwise, not dotproduct
			Vec4<type>& multiply(type val) noexcept
			{
				x *= val;
				y *= val;
				z *= val;
				w *= val;
				return *this;
			}
			//multiply another Vec4 to this | elementwise, not dotproduct
			Vec4<type>& multiply(const Vec4<type>& other) noexcept
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
				w *= other.w;
				return *this;
			}
			//multiply another Vec4 to this | elementwise, not dotproduct
			Vec4<type>& multiply(Vec4<type>&& other) noexcept
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
				w *= other.w;
				return *this;
			}
			//divide a value from this 
			Vec4<type>& divide(type val) noexcept
			{
				x /= val;
				y /= val;
				z /= val;
				w /= val;
				return *this;
			}
			//divide another Vec4 from this 
			Vec4<type>& divide(const Vec4<type>& other) noexcept
			{
				x /= other.x;
				y /= other.y;
				z /= other.z;
				w /= other.w;
				return *this;
			}
			//divide another Vec4 from this 
			Vec4<type>& divide(Vec4<type>&& other) noexcept
			{
				x /= other.x;
				y /= other.y;
				z /= other.z;
				w /= other.w;
				return *this;
			}
			//add another Vec2 to this 
			Vec4<type>& add(const Vec2<type>& other) noexcept;
			//add another Vec2 to this 
			Vec4<type>& add(Vec2<type>&& other) noexcept;
			//add another Vec3 to this 
			Vec4<type>& add(const Vec3<type>& other) noexcept;
			//add another Vec3 to this 
			Vec4<type>& add(Vec3<type>&& other) noexcept;
			//substract another Vec2 from this 
			Vec4<type>& substract(const Vec2<type>& other) noexcept;
			//substract another Vec2 from this 
			Vec4<type>& substract(Vec2<type>&& other) noexcept;
			//substract another Vec3 from this 
			Vec4<type>& substract(const Vec3<type>& other) noexcept;
			//substract another Vec3 from this 
			Vec4<type>& substract(Vec3<type>&& other) noexcept;
			//multiply another Vec2 to this | elementwise, not dotproduct
			Vec4<type>& multiply(const Vec2<type>& other) noexcept;
			//multiply another Vec2 to this | elementwise, not dotproduct
			Vec4<type>& multiply(Vec2<type>&& other) noexcept;
			//multiply another Vec3 to this | elementwise, not dotproduct
			Vec4<type>& multiply(const Vec3<type>& other) noexcept;
			//multiply another Vec3 to this | elementwise, not dotproduct
			Vec4<type>& multiply(Vec3<type>&& other) noexcept;
			//divide another Vec2 from this 
			Vec4<type>& divide(const Vec2<type>& other) noexcept;
			//divide another Vec2 from this 
			Vec4<type>& divide(Vec2<type>&& other) noexcept;
			//divide another Vec3 from this 
			Vec4<type>& divide(const Vec3<type>& other) noexcept;
			//divide another Vec3 from this 
			Vec4<type>& divide(Vec3<type>&& other) noexcept;

		public:
			//negate the vec
			friend Vec4<type> operator-(Vec4<type> vec) noexcept
			{
				vec.x = -vec.x;
				vec.y = -vec.y;
				vec.z = -vec.z;
				vec.w = -vec.w;
				return vec;
			}
			//add a value to this 
			Vec4<type>& operator+=(type val) noexcept
			{
				x += val;
				y += val;
				z += val;
				w += val;
				return *this;
			}
			//add another Vec4 to this 
			Vec4<type>& operator+=(const Vec4<type>& other) noexcept
			{
				x += other.x;
				y += other.y;
				z += other.z;
				w += other.w;
				return *this;
			}
			//add another Vec4 to this 
			Vec4<type>& operator+=(Vec4<type>&& other) noexcept
			{
				x += other.x;
				y += other.y;
				z += other.z;
				w += other.w;
				return *this;
			}
			//substract a value from this 
			Vec4<type>& operator-=(type val) noexcept
			{
				x -= val;
				y -= val;
				z -= val;
				w -= val;
				return *this;
			}
			//substract another Vec4 from this 
			Vec4<type>& operator-=(const Vec4<type>& other) noexcept
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				w -= other.w;
				return *this;
			}
			//substract another Vec4 from this 
			Vec4<type>& operator-=(Vec4<type>&& other) noexcept
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				w -= other.w;
				return *this;
			}
			//multiply a value to this | elementwise, not dotproduct
			Vec4<type>& operator*=(type val) noexcept
			{
				x *= val;
				y *= val;
				z *= val;
				w *= val;
				return *this;
			}
			//multiply another Vec4 to this | elementwise, not dotproduct
			Vec4<type>& operator*=(const Vec4<type>& other) noexcept
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
				w *= other.w;
				return *this;
			}
			//multiply another Vec4 to this | elementwise, not dotproduct
			Vec4<type>& operator*=(Vec4<type>&& other) noexcept
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
				w *= other.w;
				return *this;
			}
			//divide a value from this 
			Vec4<type>& operator/=(type val) noexcept
			{
				x /= val;
				y /= val;
				z /= val;
				w /= val;
				return *this;
			}
			//divide another Vec4 from this 
			Vec4<type>& operator/=(const Vec4<type>& other) noexcept
			{
				x /= other.x;
				y /= other.y;
				z /= other.z;
				w /= other.w;
				return *this;
			}
			//divide another Vec4 from this 
			Vec4<type>& operator/=(Vec4<type>&& other) noexcept
			{
				x /= other.x;
				y /= other.y;
				z /= other.z;
				w /= other.w;
				return *this;
			}
			//add another Vec2 to this 
			Vec4<type>& operator+=(const Vec2<type>& other) noexcept;
			//add another Vec2 to this 
			Vec4<type>& operator+=(Vec2<type>&& other) noexcept;
			//add another Vec3 to this 
			Vec4<type>& operator+=(const Vec3<type>& other) noexcept;
			//add another Vec3 to this 
			Vec4<type>& operator+=(Vec3<type>&& other) noexcept;
			//substract another Vec2 from this 
			Vec4<type>& operator-=(const Vec2<type>& other) noexcept;
			//substract another Vec2 from this 
			Vec4<type>& operator-=(Vec2<type>&& other) noexcept;
			//substract another Vec3 from this 
			Vec4<type>& operator-=(const Vec3<type>& other) noexcept;
			//substract another Vec3 from this 
			Vec4<type>& operator-=(Vec3<type>&& other) noexcept;
			//multiply another Vec2 to this | elementwise, not dotproduct
			Vec4<type>& operator*=(const Vec2<type>& other) noexcept;
			//multiply another Vec2 to this | elementwise, not dotproduct
			Vec4<type>& operator*=(Vec2<type>&& other) noexcept;
			//multiply another Vec3 to this | elementwise, not dotproduct
			Vec4<type>& operator*=(const Vec3<type>& other) noexcept;
			//multiply another Vec3 to this | elementwise, not dotproduct
			Vec4<type>& operator*=(Vec3<type>&& other) noexcept;
			//divide another Vec2 from this 
			Vec4<type>& operator/=(const Vec2<type>& other) noexcept;
			//divide another Vec2 from this 
			Vec4<type>& operator/=(Vec2<type>&& other) noexcept;
			//divide another Vec3 from this 
			Vec4<type>& operator/=(const Vec3<type>& other) noexcept;
			//divide another Vec3 from this 
			Vec4<type>& operator/=(Vec3<type>&& other) noexcept;
			//compare all values to another lvalue Vec4
			bool operator==(const Vec4<type>& other) const noexcept
			{
				return x == other.x && y == other.y && z == other.z && w == other.w;
			}
			//compare all values to another rvalue Vec4
			bool operator==(Vec4<type>&& other) const noexcept
			{
				return x == other.x && y == other.y && z == other.z && w == other.w;
			}
			//compare all values to another lvalue Vec4
			bool operator!=(const Vec4<type>& other) const noexcept
			{
				return x != other.x || y != other.y || z != other.z || w != other.w;
			}
			//compare all values to another rvalue Vec4
			bool operator!=(Vec4<type>&& other) const noexcept
			{
				return x != other.x || y != other.y || z != other.z || w != other.w;
			}
			//compare all values to another lvalue Vec4 | values are added up
			bool operator<=(const Vec4<type>& other) const noexcept
			{
				return ( x + y + z + w ) <= ( other.x + other.y + other.z + other.w );
			}
			//compare all values to another rvalue Vec4 | values are added up
			bool operator<=(Vec4<type>&& other) const noexcept
			{
				return ( x + y + z + w ) <= ( other.x + other.y + other.z + other.w );
			}
			//compare all values to another lvalue Vec4 | values are added up
			bool operator>=(const Vec4<type>& other) const noexcept
			{
				return ( x + y + z + w ) >= ( other.x + other.y + other.z + other.w );
			}
			//compare all values to another rvalue Vec4 | values are added up
			bool operator>=(Vec4<type>&& other) const noexcept
			{
				return ( x + y + z + w ) >= ( other.x + other.y + other.z + other.w );
			}
			//compare all values to another lvalue Vec4 | values are added up
			bool operator<(const Vec4<type>& other) const noexcept
			{
				return ( x + y + z + w ) < ( other.x + other.y + other.z + other.w );
			}
			//compare all values to another rvalue Vec4 | values are added up
			bool operator<(Vec4<type>&& other) const noexcept
			{
				return ( x + y + z + w ) < ( other.x + other.y + other.z + other.w );
			}
			//compare all values to another lvalue Vec4 | values are added up
			bool operator>(const Vec4<type>& other) const noexcept
			{
				return ( x + y + z + w ) > ( other.x + other.y + other.z + other.w );
			}
			//compare all values to another rvalue Vec4 | values are added up
			bool operator>(Vec4<type>&& other) const noexcept
			{
				return ( x + y + z + w ) > ( other.x + other.y + other.z + other.w );
			}


			//add a rvalue Vec4 object to a rvalue Vec4 object
			friend Vec4<type>&& operator+(Vec4<type>&& v1, Vec4<type>&& v2) noexcept
			{
				v1.x += v2.x;
				v1.y += v2.y;
				v1.z += v2.z;
				v1.w += v2.w;
				return std::move(v1);
			}
			//add a rvalue Vec4 object to a lvalue Vec4 object 
			friend Vec4<type>&& operator+(const Vec4<type>& v1, Vec4<type>&& v2) noexcept
			{
				v2.x += v1.x;
				v2.y += v1.y;
				v2.z += v1.z;
				v2.w += v1.w;
				return std::move(v2);
			}
			//add a lvalue Vec4 object to a rvalue Vec4 object
			friend Vec4<type>&& operator+(Vec4<type>&& v1, const Vec4<type>& v2) noexcept
			{
				v1.x += v2.x;
				v1.y += v2.y;
				v1.z += v2.z;
				v1.w += v2.w;
				return std::move(v1);
			}
			//add a type to a lvalue Vec4 object
			friend Vec4<type> operator+(const Vec4<type>& vec, type val) noexcept
			{
				return Vec4<type>(vec.x + val, vec.y + val, vec.z + val, vec.w + val);
			}
			//add a lvalue Vec4 object to a lvalue Vec4 object
			friend Vec4<type> operator+(const Vec4<type>& v1, const Vec4<type>& v2) noexcept
			{
				return Vec4<type>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
			}
			//add a rvalue Vec2 object to a rvalue Vec4 object
			friend Vec4<type>&& operator+<type>( Vec4<type>&& v1, Vec2<type>&& v2 ) noexcept;
			//add a lvalue Vec2 object to a rvalue Vec4 object
			friend Vec4<type>&& operator+<type>( Vec4<type>&& v1, const Vec2<type>& v2 ) noexcept;
			//add a lvalue Vec2 object to a lvalue Vec4 object
			friend Vec4<type> operator+<type>( const Vec4<type>& v1, const Vec2<type>& v2 ) noexcept;
			//add a rvalue Vec3 object to a rvalue Vec4 object
			friend Vec4<type>&& operator+<type>( Vec4<type>&& v1, Vec3<type>&& v2 ) noexcept;
			//add a lvalue Vec3 object to a rvalue Vec4 object
			friend Vec4<type>&& operator+<type>( Vec4<type>&& v1, const Vec3<type>& v2 ) noexcept;
			//add a lvalue Vec3 object to a lvalue Vec4 object
			friend Vec4<type> operator+<type>( const Vec4<type>& v1, const Vec3<type>& v2 ) noexcept;
			//substract a rvalue Vec4 object from a rvalue Vec4 object
			friend Vec4<type>&& operator-(Vec4<type>&& v1, Vec4<type>&& v2) noexcept
			{
				v1.x -= v2.x;
				v1.y -= v2.y;
				v1.z -= v2.z;
				v1.w -= v2.w;
				return std::move(v1);
			}
			//substract a rvalue Vec4 object from a lvalue Vec4 object 
			friend Vec4<type> operator-(const Vec4<type>& v1, Vec4<type>&& v2) noexcept
			{
				return Vec4<type>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
			}
			//substract a lvalue Vec4 object from a rvalue Vec4 object
			friend Vec4<type>&& operator-(Vec4<type>&& v1, const Vec4<type>& v2) noexcept
			{
				v1.x -= v2.x;
				v1.y -= v2.y;
				v1.z -= v2.z;
				v1.w -= v2.w;
				return std::move(v1);
			}
			//substract a type from a lvalue Vec4 object
			friend Vec4<type> operator-(const Vec4<type>& vec, type val) noexcept
			{
				return Vec4<type>(vec.x - val, vec.y - val, vec.z - val, vec.w - val);
			}
			//substract a lvalue Vec4 object from a lvalue Vec4 object
			friend Vec4<type> operator-(const Vec4<type>& v1, const Vec4<type>& v2) noexcept
			{
				return Vec4<type>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
			}
			//substract a rvalue Vec2 object from a rvalue Vec4 object
			friend Vec4<type>&& operator-<type>( Vec4<type>&& v1, Vec2<type>&& v2 ) noexcept;
			//substract a lvalue Vec2 object from a rvalue Vec4 object
			friend Vec4<type>&& operator-<type>( Vec4<type>&& v1, const Vec2<type>& v2 ) noexcept;
			//substract a lvalue Vec2 object from a lvalue Vec4 object
			friend Vec4<type> operator-<type>( const Vec4<type>& v1, const Vec2<type>& v2 ) noexcept;
			//substract a rvalue Vec3 object from a rvalue Vec4 object
			friend Vec4<type>&& operator-<type>( Vec4<type>&& v1, Vec3<type>&& v2 ) noexcept;
			//substract a lvalue Vec3 object from a rvalue Vec4 object
			friend Vec4<type>&& operator-<type>( Vec4<type>&& v1, const Vec3<type>& v2 ) noexcept;
			//substract a lvalue Vec3 object from a lvalue Vec4 object
			friend Vec4<type> operator-<type>( const Vec4<type>& v1, const Vec3<type>& v2 ) noexcept;
			//multiply a rvalue Vec4 object to a rvalue Vec4 object | elementwise, not dotproduct
			friend Vec4<type>&& operator*(Vec4<type>&& v1, Vec4<type>&& v2) noexcept
			{
				v1.x *= v2.x;
				v1.y *= v2.y;
				v1.z *= v2.z;
				v1.w *= v2.w;
				return std::move(v1);
			}
			//multiply a rvalue Vec4 object to a lvalue Vec4 object | elementwise, not dotproduct
			friend Vec4<type>&& operator*(const Vec4<type>& v1, Vec4<type>&& v2) noexcept
			{
				v2.x *= v1.x;
				v2.y *= v1.y;
				v2.z *= v1.z;
				v2.w *= v1.w;
				return std::move(v2);
			}
			//multiply a lvalue Vec4 object to a rvalue Vec4 object | elementwise, not dotproduct
			friend Vec4<type>&& operator*(Vec4<type>&& v1, const Vec4<type>& v2) noexcept
			{
				v1.x *= v2.x;
				v1.y *= v2.y;
				v1.z *= v2.z;
				v1.w *= v2.w;
				return std::move(v1);
			}
			//multiply a type to a lvalue Vec4 object | elementwise, not dotproduct
			friend Vec4<type> operator*(type val, const Vec4<type>& vec) noexcept
			{
				return Vec4<type>(vec.x * val, vec.y * val, vec.z * val, vec.w * val);
			}
			//multiply a type to a lvalue Vec4 object | elementwise, not dotproduct
			friend Vec4<type> operator*(const Vec4<type>& vec, type val) noexcept
			{
				return Vec4<type>(vec.x * val, vec.y * val, vec.z * val, vec.w * val);
			}
			//multiply a lvalue Vec4 object to a lvalue Vec4 object | elementwise, not dotproduct
			friend Vec4<type> operator*(const Vec4<type>& v1, const Vec4<type>& v2) noexcept
			{
				return Vec4<type>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
			}
			//multiply a rvalue Vec2 object to a rvalue Vec4 object | elementwise, not dotproduct
			friend Vec4<type>&& operator*<type>( Vec4<type>&& v1, Vec2<type>&& v2 ) noexcept;
			//multiply a lvalue Vec2 object to a rvalue Vec4 object | elementwise, not dotproduct
			friend Vec4<type>&& operator*<type>( Vec4<type>&& v1, const Vec2<type>& v2 ) noexcept;
			//multiply a lvalue Vec2 object to a lvalue Vec4 object | elementwise, not dotproduct
			friend Vec4<type> operator*<type>( const Vec4<type>& v1, const Vec2<type>& v2 ) noexcept;
			//multiply a rvalue Vec3 object to a rvalue Vec4 object | elementwise, not dotproduct
			friend Vec4<type>&& operator*<type>( Vec4<type>&& v1, Vec3<type>&& v2 ) noexcept;
			//multiply a lvalue Vec3 object to a rvalue Vec4 object | elementwise, not dotproduct
			friend Vec4<type>&& operator*<type>( Vec4<type>&& v1, const Vec3<type>& v2 ) noexcept;
			//multiply a lvalue Vec3 object to a lvalue Vec4 object | elementwise, not dotproduct
			friend Vec4<type> operator*<type>( const Vec4<type>& v1, const Vec3<type>& v2 ) noexcept;
			//divide a rvalue Vec4 object to a rvalue Vec4 object
			friend Vec4<type>&& operator/(Vec4<type>&& v1, Vec4<type>&& v2) noexcept
			{
				v1.x /= v2.x;
				v1.y /= v2.y;
				v1.z /= v2.z;
				v1.w /= v2.w;
				return std::move(v1);
			}
			//divide a rvalue Vec4 object to a lvalue Vec4 object 
			friend Vec4<type> operator/(const Vec4<type>& v1, Vec4<type>&& v2) noexcept
			{
				return Vec4<type>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
			}
			//divide a lvalue Vec4 object to a rvalue Vec4 object
			friend Vec4<type>&& operator/(Vec4<type>&& v1, const Vec4<type>& v2) noexcept
			{
				v1.x /= v2.x;
				v1.y /= v2.y;
				v1.z /= v2.z;
				v1.w /= v2.w;
				return std::move(v1);
			}
			//divide a type to a lvalue Vec4 object
			friend Vec4<type> operator/(const Vec4<type>& vec, type val) noexcept
			{
				return Vec4<type>(vec.x / val, vec.y / val, vec.z / val, vec.w / val);
			}
			//divide a lvalue Vec4 object to a lvalue Vec4 object
			friend Vec4<type> operator/(const Vec4<type>& v1, const Vec4<type>& v2) noexcept
			{
				return Vec4<type>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
			}
			//divide a rvalue Vec2 object to a rvalue Vec4 object
			friend Vec4<type>&& operator/<type>( Vec4<type>&& v1, Vec2<type>&& v2 ) noexcept;
			//divide a lvalue Vec2 object to a rvalue Vec4 object
			friend Vec4<type>&& operator/<type>( Vec4<type>&& v1, const Vec2<type>& v2 ) noexcept;
			//divide a lvalue Vec2 object to a lvalue Vec4 object
			friend Vec4<type> operator/<type>( const Vec4<type>& v1, const Vec2<type>& v2 ) noexcept;
			//divide a rvalue Vec3 object to a rvalue Vec4 object
			friend Vec4<type>&& operator/<type>( Vec4<type>&& v1, Vec3<type>&& v2 ) noexcept;
			//divide a lvalue Vec3 object to a rvalue Vec4 object
			friend Vec4<type>&& operator/<type>( Vec4<type>&& v1, const Vec3<type>& v2 ) noexcept;
			//divide a lvalue Vec3 object to a lvalue Vec4 object
			friend Vec4<type> operator/<type>( const Vec4<type>& v1, const Vec3<type>& v2 ) noexcept;
			//modulo a vec4 with a number(only works with int and will take int values)
			friend Vec4<type> operator%(const Vec4<type>& vec, int val) noexcept
			{
				return Vec4<type>(static_cast<int>( vec.x ) % val, static_cast<int>( vec.y ) % val, static_cast<int>( vec.z ) % val, static_cast<int>( vec.w ) % val);
			}

		public:
			//const read-only position access x=0, y=1, z=2, w=3
			const type operator[](unsigned short position) const noexcept
			{
				return data[position];
			}
			//position access x=0, y=1, z=2, w=3
			type& operator[](unsigned short position) noexcept
			{
				return data[position];
			}
			//|vec| returns the lenght of the vec/direct distance from origin vec(0,0,0,0) | std::sqrt(x * x + y * y + z * z + w * w)
			type magnitude() const noexcept
			{
				return std::sqrt(x * x + y * y + z * z + w * w);
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
				if ( z < 0 )
					result += -z;
				else
					result += z;
				if ( w < 0 )
					result += -w;
				else
					result += w;
				return result;
			}
			//std::sqrt(vec*vec) returns the not negative value of the vec as a copie of the vec
			Vec3<type> abs() const noexcept
			{
				return Vec3<type>(std::sqrt(x*x), std::sqrt(y*y), std::sqrt(z*z), std::sqrt(w*w));
			}
			//std::sqrt(vec*vec) converts the vec itself to its not negative value
			Vec3<type>& absSelf() noexcept
			{
				x = std::sqrt(x*x);
				y = std::sqrt(y*y);
				z = std::sqrt(z*z);
				w = std::sqrt(w*w);
				return *this;
			}
			//vec(x/magnitude(), y/magnitude(), z/magnitude(), w/magnitude()) returns a normalized copy of the vec relative to the lenght of the vec  | also called called unit vector, because the magnitude/lenght of the vector is always one 
			Vec4<type> normalize() const noexcept
			{
				return Vec4<type>(x / std::sqrt(x * x + y * y + z * z + w * w), y / std::sqrt(x * x + y * y + z * z + w * w), z / std::sqrt(x * x + y * y + z * z + w * w), w / std::sqrt(x * x + y * y + z * z + w * w));
			}
			//vec(x/magnitude(), y/magnitude()) normalize the vec itself relative to the lenght of the vec | also called called unit vector, because the magnitude/lenght of the vector is always one 
			Vec4<type>& normalizeSelf() noexcept
			{
				type scale = std::sqrt(x * x + y * y + z * z + w * w);
				x /= scale;
				y /= scale;
				z /= scale;
				w /= scale;
				return *this;
			}
			//|vec1-vec2| returns the direct distance to another vec | std::sqrt(( x - other.x ) * ( x - other.x ) + ( y - other.y ) * ( y - other.y ) + ( z - other.z ) * ( z - other.z ) + ( w - other.w ) * ( w - other.w ))
			type distance(const Vec4<type>& other) const noexcept
			{
				return std::sqrt(( x - other.x ) * ( x - other.x ) + ( y - other.y ) * ( y - other.y ) + ( z - other.z ) * ( z - other.z ) + ( w - other.w ) * ( w - other.w ));
			}
			//|vec1-vec2| can be used to compare distances, will return the non negative value of the components added together 
			type fastDistance(const Vec4<type>& other) const noexcept
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
				type tempz;
				if ( other.z < z )
					tempz = z - other.z;
				else
					tempz = other.z - z;
				type tempw;
				if ( other.w < w )
					tempw = w - other.w;
				else
					tempw = other.w - w;
				return tempx + tempy + tempz + tempw;
			}
			/*vec1*vec2 = |vec1|*|vec2|*cos(vec1,vec2) returns the dotproduct of 2 vecs, vecs are orthogonal(_|_) if the result is 0 and vecs are parallel if the result is 1(||) | x * other.x + y * other.y + z * other.z + w * other.w | not the normal multiply method 
			its more efficient than comparing the vecs with the magnitude method*/
			type dotproduct(const Vec4<type>& other) const noexcept
			{
				return x * other.x + y * other.y + z * other.z + w * other.w;
			}
			/*vec1*vec2 = |vec1|*|vec2|*cos(vec1,vec2) returns the dotproduct of 2 vecs, vecs are orthogonal(_|_) if the result is 0 and vecs are parallel if the result is 1(||) | x * other.x + y * other.y + z * other.z + w * other.w | not the normal multiply method 
			its more efficient than comparing the vecs with the magnitude method*/
			type dotproduct(Vec4<type>&& other) const noexcept
			{
				return x * other.x + y * other.y + z * other.z + w * other.w;
			}
			//acos(dotproduct() / (magnitude()*other.magnitude())) returns the angle between 2 vecs in radians 
			type angleR(const Vec4<type>& other) const noexcept
			{
				return std::acos(( x * other.x + y * other.y + z * other.z + w * other.w ) / ( std::sqrt(x * x + y * y + z * z + w * w) * std::sqrt(other.x * other.x + other.y * other.y + other.z * other.z + other.w * other.w) ));
			}
			//acos(dotproduct() / (magnitude()*other.magnitude())) returns the angle between 2 vecs in radians 
			type angleR(Vec4<type>&& other) const noexcept
			{
				return std::acos(( x * other.x + y * other.y + z * other.z + w * other.w ) / ( std::sqrt(x * x + y * y + z * z + w * w) * std::sqrt(other.x * other.x + other.y * other.y + other.z * other.z + other.w * other.w) ));
			}
			//acos(dotproduct() / (magnitude()*other.magnitude())) returns the angle between 2 vecs in degrees 
			type angleD(const Vec4<type>& other) const noexcept
			{
				return std::acos(( x * other.x + y * other.y + z * other.z + w * other.w ) / ( std::sqrt(x * x + y * y + z * z + w * w) * std::sqrt(other.x * other.x + other.y * other.y + other.z * other.z + other.w * other.w) ))*( 180.0 / 3.14159265359 );
			}
			//acos(dotproduct() / (magnitude()*other.magnitude())) returns the angle between 2 vecs in degrees 
			type angleD(Vec4<type>&& other) const noexcept
			{
				return std::acos(( x * other.x + y * other.y + z * other.z + w * other.w ) / ( std::sqrt(x * x + y * y + z * z + w * w) * std::sqrt(other.x * other.x + other.y * other.y + other.z * other.z + other.w * other.w) ))*( 180.0 / 3.14159265359 );
			}
			//vec1xvec2 returns the orthogonal vec to the level of the 2 other vecs(_|/), magnitude of the vec is the area of the 2 vecs | ignores w, w is 0 
			Vec4<type> crossproduct(const Vec4<type>& other) const noexcept
			{
				return Vec4<type>(y*other.z - z * other.y, z* other.x - x * other.z, x * other.y - y * other.x, 0);
			}
			//vec1xvec2 returns the orthogonal vec to the level of the 2 other vecs(_|/), magnitude of the vec is the area of the 2 vecs | ignores w, w is 0 
			Vec4<type> crossproduct(Vec4<type>&& other) const noexcept
			{
				return Vec4<type>(y*other.z - z * other.y, z* other.x - x * other.z, x * other.y - y * other.x, 0);
			}
			//|vec1xvec2| returns the area of the 2 vecs, also is the magnitude of the crossproduct | ignores w, w is 0 
			type area(const Vec4<type>& other) const noexcept
			{
				return std::sqrt(( y*other.z - z * other.y ) * ( y*other.z - z * other.y ) + ( z* other.x - x * other.z ) * ( z* other.x - x * other.z ) + ( x * other.y - y * other.x ) * ( x * other.y - y * other.x ));
			}
			//|vec1xvec2| returns the area of the 2 vecs, also is the magnitude of the crossproduct | ignores w, w is 0 
			type area(Vec4<type>&& other) const noexcept
			{
				return std::sqrt(( y*other.z - z * other.y ) * ( y*other.z - z * other.y ) + ( z* other.x - x * other.z ) * ( z* other.x - x * other.z ) + ( x * other.y - y * other.x ) * ( x * other.y - y * other.x ));
			}
			//(vec1xvec2)*vec3 returns the non negative |volume| of the 3 vecs, also called triple product | ignores w, w is 0 | std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) )) | not the normal multiply method 
			type volume(const Vec4<type>& v2, const Vec4<type>& v3) const noexcept
			{
				return std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) ));
			}
			//(vec1xvec2)*vec3 returns the non negative |volume| of the 3 vecs, also called triple product | ignores w, w is 0 | std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) )) | not the normal multiply method 
			type volume(Vec4<type>&& v2, Vec4<type>&& v3) const noexcept
			{
				return std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) ));
			}
			//(vec1xvec2)*vec3 returns the non negative |volume| of the 3 vecs, also called triple product | ignores w, w is 0 | std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) )) | not the normal multiply method 
			type volume(Vec4<type>&& v2, const Vec4<type>& v3) const noexcept
			{
				return std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) ));
			}
			//(vec1xvec2)*vec3 returns the non negative |volume| of the 3 vecs, also called triple product | ignores w, w is 0 | std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) )) | not the normal multiply method 
			type volume(const Vec4<type>& v2, Vec4<type>&& v3) const noexcept
			{
				return std::sqrt(( this->crossproduct(v2).dotproduct(v3) ) *( this->crossproduct(v2).dotproduct(v3) ));
			}
			//vec as string: "Vec4<type>(x,y,z,w)"
			std::string toString() const noexcept
			{
				std::stringstream stream;
				stream << "Vec4<" << typeid( type ).name() << ">(" << x << "," << y << "," << z << "," << w << ")";
				return stream.str();
			}
			//ostream operator: "Vec4<type>(x,y,z,w)"
			friend std::ostream& operator<<(std::ostream& stream, const Vec4<type>& vec) noexcept
			{
				stream << "Vec4<" << typeid( type ).name() << ">(" << vec.x << "," << vec.y << "," << vec.z << "," << vec.w << ")";
				return stream;
			}


		};

	}
}

#include "Vec2.h"
#include "Vec3.h"

namespace clockwork {
	namespace maths {

		//vec2 copy constructor
		template<typename type>Vec4<type>::Vec4(const Vec2<type>& other) noexcept
			:x(other.x), y(other.y), z(0), w(0)
		{}
		//vec2 move constructor
		template<typename type>Vec4<type>::Vec4(Vec2<type>&& other) noexcept
			: x(std::move(other.x)), y(std::move(other.y)), z(0), w(0)
		{}
		//vec3 copy constructor
		template<typename type>Vec4<type>::Vec4(const Vec3<type>& other) noexcept
			: x(other.x), y(other.y), z(other.z), w(0)
		{}
		//vec3 move constructor
		template<typename type>Vec4<type>::Vec4(Vec3<type>&& other) noexcept
			: x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)), w(0)
		{}
		//vec2 assign operator
		template<typename type>Vec4<type>& Vec4<type>::operator=(const Vec2<type>& other) noexcept
		{
			x = other.x;
			y = other.y;
			return *this;
		}
		//vec2 move operator
		template<typename type>Vec4<type>& Vec4<type>::operator=(Vec2<type>&& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
			return *this;
		}
		//vec3 assign operator
		template<typename type>Vec4<type>& Vec4<type>::operator=(const Vec3<type>& other) noexcept
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}
		//vec3 move operator
		template<typename type>Vec4<type>& Vec4<type>::operator=(Vec3<type>&& other) noexcept
		{
			x = std::move(other.x);
			y = std::move(other.y);
			z = std::move(other.z);
			return *this;
		}

		//add another Vec2 to this 
		template<typename type>Vec4<type>& Vec4<type>::add(const Vec2<type>& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another Vec2 to this 
		template<typename type>Vec4<type>& Vec4<type>::add(Vec2<type>&& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another Vec3 to this 
		template<typename type>Vec4<type>& Vec4<type>::add(const Vec3<type>& other) noexcept
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		//add another Vec3 to this 
		template<typename type>Vec4<type>& Vec4<type>::add(Vec3<type>&& other) noexcept
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		//substract another Vec2 from this 
		template<typename type>Vec4<type>& Vec4<type>::substract(const Vec2<type>& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another Vec2 from this 
		template<typename type>Vec4<type>& Vec4<type>::substract(Vec2<type>&& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another Vec3 from this 
		template<typename type>Vec4<type>& Vec4<type>::substract(const Vec3<type>& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		//substract another Vec3 from this 
		template<typename type>Vec4<type>& Vec4<type>::substract(Vec3<type>&& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		//multiply another Vec2 to this | elementwise, not dotproduct
		template<typename type>Vec4<type>& Vec4<type>::multiply(const Vec2<type>& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another Vec2 to this | elementwise, not dotproduct
		template<typename type>Vec4<type>& Vec4<type>::multiply(Vec2<type>&& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another Vec3 to this | elementwise, not dotproduct
		template<typename type>Vec4<type>& Vec4<type>::multiply(const Vec3<type>& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}
		//multiply another Vec3 to this | elementwise, not dotproduct
		template<typename type>Vec4<type>& Vec4<type>::multiply(Vec3<type>&& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}
		//divide another Vec2 from this 
		template<typename type>Vec4<type>& Vec4<type>::divide(const Vec2<type>& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another Vec2 from this 
		template<typename type>Vec4<type>& Vec4<type>::divide(Vec2<type>&& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another Vec3 from this 
		template<typename type>Vec4<type>& Vec4<type>::divide(const Vec3<type>& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}
		//divide another Vec3 from this 
		template<typename type>Vec4<type>& Vec4<type>::divide(Vec3<type>&& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}

		//add another Vec2 to this 
		template<typename type>Vec4<type>& Vec4<type>::operator+=(const Vec2<type>& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another Vec2 to this 
		template<typename type>Vec4<type>& Vec4<type>::operator+=(Vec2<type>&& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//add another Vec3 to this 
		template<typename type>Vec4<type>& Vec4<type>::operator+=(const Vec3<type>& other) noexcept
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		//add another Vec3 to this 
		template<typename type>Vec4<type>& Vec4<type>::operator+=(Vec3<type>&& other) noexcept
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		//substract another Vec2 from this 
		template<typename type>Vec4<type>& Vec4<type>::operator-=(const Vec2<type>& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another Vec2 from this 
		template<typename type>Vec4<type>& Vec4<type>::operator-=(Vec2<type>&& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//substract another Vec3 from this 
		template<typename type>Vec4<type>& Vec4<type>::operator-=(const Vec3<type>& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		//substract another Vec3 from this 
		template<typename type>Vec4<type>& Vec4<type>::operator-=(Vec3<type>&& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		//multiply another Vec2 to this | elementwise, not dotproduct
		template<typename type>Vec4<type>& Vec4<type>::operator*=(const Vec2<type>& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another Vec2 to this | elementwise, not dotproduct
		template<typename type>Vec4<type>& Vec4<type>::operator*=(Vec2<type>&& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}
		//multiply another Vec3 to this | elementwise, not dotproduct
		template<typename type>Vec4<type>& Vec4<type>::operator*=(const Vec3<type>& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}
		//multiply another Vec3 to this | elementwise, not dotproduct
		template<typename type>Vec4<type>& Vec4<type>::operator*=(Vec3<type>&& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}
		//divide another Vec2 from this 
		template<typename type>Vec4<type>& Vec4<type>::operator/=(const Vec2<type>& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another Vec2 from this 
		template<typename type>Vec4<type>& Vec4<type>::operator/=(Vec2<type>&& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
		//divide another Vec3 from this 
		template<typename type>Vec4<type>& Vec4<type>::operator/=(const Vec3<type>& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}
		//divide another Vec3 from this 
		template<typename type>Vec4<type>& Vec4<type>::operator/=(Vec3<type>&& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}


		//add a rvalue Vec2 object to a rvalue Vec4 object
		template<typename type>Vec4<type>&& operator+(Vec4<type>&& v1, Vec2<type>&& v2) noexcept
		{
			v1.x += v2.x;
			v1.y += v2.y;
			return std::move(v1);
		}
		//add a lvalue Vec2 object to a rvalue Vec4 object
		template<typename type>Vec4<type>&& operator+(Vec4<type>&& v1, const Vec2<type>& v2) noexcept
		{
			v1.x += v2.x;
			v1.y += v2.y;
			return std::move(v1);
		}
		//add a lvalue Vec2 object to a lvalue Vec4 object
		template<typename type>Vec4<type> operator+(const Vec4<type>& v1, const Vec2<type>& v2) noexcept
		{
			return Vec4<type>(v1.x + v2.x, v1.y + v2.y, v1.z, v1.w);
		}
		//add a rvalue Vec3 object to a rvalue Vec4 object
		template<typename type>Vec4<type>&& operator+(Vec4<type>&& v1, Vec3<type>&& v2) noexcept
		{
			v1.x += v2.x;
			v1.y += v2.y;
			v1.z += v2.z;
			return std::move(v1);
		}
		//add a lvalue Vec3 object to a rvalue Vec4 object
		template<typename type>Vec4<type>&& operator+(Vec4<type>&& v1, const Vec3<type>& v2) noexcept
		{
			v1.x += v2.x;
			v1.y += v2.y;
			v1.z += v2.z;
			return std::move(v1);
		}
		//add a lvalue Vec3 object to a lvalue Vec4 object
		template<typename type>Vec4<type> operator+(const Vec4<type>& v1, const Vec3<type>& v2) noexcept
		{
			return Vec4<type>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w);
		}
		//substract a rvalue Vec2 object from a rvalue Vec4 object
		template<typename type>Vec4<type>&& operator-(Vec4<type>&& v1, Vec2<type>&& v2) noexcept
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			return std::move(v1);
		}
		//substract a lvalue Vec2 object from a rvalue Vec4 object
		template<typename type>Vec4<type>&& operator-(Vec4<type>&& v1, const Vec2<type>& v2) noexcept
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			return std::move(v1);
		}
		//substract a lvalue Vec2 object from a lvalue Vec4 object
		template<typename type>Vec4<type> operator-(const Vec4<type>& v1, const Vec2<type>& v2) noexcept
		{
			return Vec4<type>(v1.x - v2.x, v1.y - v2.y, v1.z, v1.w);
		}
		//substract a rvalue Vec3 object from a rvalue Vec4 object
		template<typename type>Vec4<type>&& operator-(Vec4<type>&& v1, Vec3<type>&& v2) noexcept
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			v1.z -= v2.z;
			return std::move(v1);
		}
		//substract a lvalue Vec3 object from a rvalue Vec4 object
		template<typename type>Vec4<type>&& operator-(Vec4<type>&& v1, const Vec3<type>& v2) noexcept
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			v1.z -= v2.z;
			return std::move(v1);
		}
		//substract a lvalue Vec3 object from a lvalue Vec4 object
		template<typename type>Vec4<type> operator-(const Vec4<type>& v1, const Vec3<type>& v2) noexcept
		{
			return Vec4<type>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w);
		}
		//multiply a rvalue Vec2 object to a rvalue Vec4 object | elementwise, not dotproduct
		template<typename type>Vec4<type>&& operator*(Vec4<type>&& v1, Vec2<type>&& v2) noexcept
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			return std::move(v1);
		}
		//multiply a lvalue Vec2 object to a rvalue Vec4 object | elementwise, not dotproduct
		template<typename type>Vec4<type>&& operator*(Vec4<type>&& v1, const Vec2<type>& v2) noexcept
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			return std::move(v1);
		}
		//multiply a lvalue Vec2 object to a lvalue Vec4 object | elementwise, not dotproduct
		template<typename type>Vec4<type> operator*(const Vec4<type>& v1, const Vec2<type>& v2) noexcept
		{
			return Vec4<type>(v1.x * v2.x, v1.y * v2.y, v1.z, v1.w);
		}
		//multiply a rvalue Vec3 object to a rvalue Vec4 object | elementwise, not dotproduct
		template<typename type>Vec4<type>&& operator*(Vec4<type>&& v1, Vec3<type>&& v2) noexcept
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			v1.z *= v2.z;
			return std::move(v1);
		}
		//multiply a lvalue Vec3 object to a rvalue Vec4 object | elementwise, not dotproduct
		template<typename type>Vec4<type>&& operator*(Vec4<type>&& v1, const Vec3<type>& v2) noexcept
		{
			v1.x *= v2.x;
			v1.y *= v2.y;
			v1.z *= v2.z;
			return std::move(v1);
		}
		//multiply a lvalue Vec3 object to a lvalue Vec4 object | elementwise, not dotproduct
		template<typename type>Vec4<type> operator*(const Vec4<type>& v1, const Vec3<type>& v2) noexcept
		{
			return Vec4<type>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w);
		}
		//divide a rvalue Vec2 object from a rvalue Vec4 object
		template<typename type>Vec4<type>&& operator/(Vec4<type>&& v1, Vec2<type>&& v2) noexcept
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			return std::move(v1);
		}
		//divide a lvalue Vec2 object from a rvalue Vec4 object
		template<typename type>Vec4<type>&& operator/(Vec4<type>&& v1, const Vec2<type>& v2) noexcept
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			return std::move(v1);
		}
		//divide a lvalue Vec2 object from a lvalue Vec4 object
		template<typename type>Vec4<type> operator/(const Vec4<type>& v1, const Vec2<type>& v2) noexcept
		{
			return Vec4<type>(v1.x / v2.x, v1.y / v2.y, v1.z, v1.w);
		}
		//divide a rvalue Vec3 object from a rvalue Vec4 object
		template<typename type>Vec4<type>&& operator/(Vec4<type>&& v1, Vec3<type>&& v2) noexcept
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			v1.z /= v2.z;
			return std::move(v1);
		}
		//divide a lvalue Vec3 object from a rvalue Vec4 object
		template<typename type>Vec4<type>&& operator/(Vec4<type>&& v1, const Vec3<type>& v2) noexcept
		{
			v1.x /= v2.x;
			v1.y /= v2.y;
			v1.z /= v2.z;
			return std::move(v1);
		}
		//divide a lvalue Vec3 object from a lvalue Vec4 object
		template<typename type>Vec4<type> operator/(const Vec4<type>& v1, const Vec3<type>& v2) noexcept
		{
			return Vec4<type>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w);
		}


		using Vec4f = Vec4<float>;
	}
}