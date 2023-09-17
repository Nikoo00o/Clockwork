#pragma once
#include "MathFunctions.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

namespace clockwork {
	namespace maths {

		template<typename type>struct Mat2x2;
		template<typename type>struct Mat2x3;
		template<typename type>struct Mat2x4;
		template<typename type>struct Mat3x2;
		template<typename type>struct Mat3x3;
		template<typename type>struct Mat3x4;
		template<typename type>struct Mat4x2;
		template<typename type>struct Mat4x3;
		template<typename type>struct Mat4x4;

		template<typename type>Mat4x4<type> operator*(const Mat4x4<type>& left, const Mat4x4<type>& right) noexcept;
		template<typename type>Mat4x4<type>&& operator*(Mat4x4<type>&& left, const Mat4x4<type>& right) noexcept;
		template<typename type>Mat4x4<type>&& operator*(const Mat4x4<type>& left, Mat4x4<type>&& right) noexcept;
		template<typename type>Vec4<type>&& operator*(const Mat4x4<type>& left, Vec4<type>&& right) noexcept;
		template<typename type>Vec4<type> operator*(const Mat4x4<type>& left, const Vec4<type>& right) noexcept;
		template<typename type>Vec3<type>&& operator*(const Mat4x4<type>& left, Vec3<type>&& right) noexcept;
		template<typename type>Vec3<type> operator*(const Mat4x4<type>& left, const Vec3<type>& right) noexcept;
		template<typename type>Vec2<type>&& operator*(const Mat4x4<type>& left, Vec2<type>&& right) noexcept;
		template<typename type>Vec2<type> operator*(const Mat4x4<type>& left, const Vec2<type>& right) noexcept;


		template<typename type>Vec4<type> operator-(Vec4<type> vec) noexcept;


		/*matrices are defined as first row(--) then column(|) and to name elements in a matrix its the same, so x2 would be mat.at(1,2) 
		row-major layout in parameters, access and in methods(x1,x2,x3,x4,...,w1,w2,w3,w4) | column-major layout in memory, so its better for opengl
		careful, opengl uses column-major layout in glsl shader language(x1,y1,z1,w1,...,x4,y4,z4,w4) */
		template<typename type>
		struct Mat4x4
		{

		public:
			union
			{
				struct
				{
					/*first row(--), first column(|)
					ME x2 x3 x4
					y1 y2 y3 y4
					z1 z2 z3 z4
					w1 w2 w3 w4*/
					type x1;

					/*second row(--), first column(|)
					x1 x2 x3 x4
					ME y2 y3 y4
					z1 z2 z3 z4
					w1 w2 w3 w4*/
					type y1;

					/*third row(--), first column(|)
					x1 x2 x3 x4
					y1 y2 y3 y4
					ME z2 z3 z4
					w1 w2 w3 w4*/
					type z1;

					/*fourth row(--), first column(|)
					x1 x2 x3 x4
					y1 y2 y3 y4
					z1 z2 z3 z4
					ME w2 w3 w4*/
					type w1;

					/*first row(--), second column(|)
					x1 ME x3 x4
					y1 y2 y3 y4
					z1 z2 z3 z4
					w1 w2 w3 w4*/
					type x2;

					/*second row(--), second column(|)
					x1 x2 x3 x4
					y1 ME y3 y4
					z1 z2 z3 z4
					w1 w2 w3 w4*/
					type y2;

					/*third row(--), second column(|)
					x1 x2 x3 x4
					y1 y2 y3 y4
					z1 ME z3 z4
					w1 w2 w3 w4*/
					type z2;

					/*fourth row(--), second column(|)
					x1 x2 x3 x4
					y1 y2 y3 y4
					z1 z2 z3 z4
					w1 ME w3 w4*/
					type w2;

					/*first row(--), third column(|)
					x1 x2 ME x4
					y1 y2 y3 y4
					z1 z2 z3 z4
					w1 w2 w3 w4*/
					type x3;

					/*second row(--), third column(|)
					x1 x2 x3 x4
					y1 y2 ME y4
					z1 z2 z3 z4
					w1 w2 w3 w4*/
					type y3;

					/*third row(--), third column(|)
					x1 x2 x3 x4
					y1 y2 y3 y4
					z1 z2 ME z4
					w1 w2 w3 w4*/
					type z3;

					/*fourth row(--), third column(|)
					x1 x2 x3 x4
					y1 y2 y3 y4
					z1 z2 z3 z4
					w1 w2 ME w4*/
					type w3;

					/*first row(--), fourth column(|)
					x1 x2 x3 ME
					y1 y2 y3 y4
					z1 z2 z3 z4
					w1 w2 w3 w4*/
					type x4;

					/*second row(--), fourth column(|)
					x1 x2 x3 x4
					y1 y2 y3 ME
					z1 z2 z3 z4
					w1 w2 w3 w4*/
					type y4;

					/*third row(--), fourth column(|)
					x1 x2 x3 x4
					y1 y2 y3 y4
					z1 z2 z3 ME
					w1 w2 w3 w4*/
					type z4;

					/*fourth row(--), fourth column(|)
					x1 x2 x3 x4
					y1 y2 y3 y4
					z1 z2 z3 z4
					w1 w2 w3 ME*/
					type w4;
				};
				
				/* row-major direct access to the data in the matrix, so the positions are row per row: 
				x1=0 x2=1 x3=2 x4=3
				y1=4 y2=5 y3=6 y4=7
				z1=8 z2=9 z3=10 z4=11
				w1=12 w2=13 w3=14 w4=15*/
				type data[4 * 4];
			};

		public:
			/*seperate values constructor | the default values are set to the identity matrix
			x1 x2 x3 x4
			y1 y2 y3 y4
			z1 z2 z3 z4
			w1 w2 w3 w4*/
			explicit Mat4x4
			(
				type x1=1, type x2=0, type x3=0, type x4=0,
				type y1=0, type y2=1, type y3=0, type y4=0,
				type z1=0, type z2=0, type z3=1, type z4=0,
				type w1=0, type w2=0, type w3=0, type w4=1
			) noexcept
				:x1(x1), y1(y1), z1(z1), w1(w1), x2(x2), y2(y2), z2(z2), w2(w2), x3(x3), y3(y3), z3(z3), w3(w3), x4(x4), y4(y4), z4(z4), w4(w4)
			{}

			/*vec constructor | 1 vec for each collumn(|)
			v1.x v2.x v3.x v4.x
			v1.y v2.y v3.y v4.y
			v1.z v2.z v3.z v4.z
			v1.w v2.w v3.w v4.w*/
			Mat4x4(const Vec4<type>& v1, const Vec4<type>& v2, const Vec4<type>& v3, const Vec4<type>& v4) noexcept
				: x1(v1.x), y1(v1.y), z1(v1.z), w1(v1.w), x2(v2.x), y2(v2.y), z2(v2.z), w2(v2.w), x3(v3.x), y3(v3.y), z3(v3.z), w3(v3.w), x4(v4.x), y4(v4.y), z4(v4.z), w4(v4.w)
			{}
			/*copy a matrix*/
			Mat4x4(const Mat4x4<type>& other)
				: x1(other.x1), x2(other.x2), x3(other.x3), x4(other.x4), y1(other.y1), y2(other.y2), y3(other.y3), y4(other.y4), z1(other.z1), z2(other.z2), z3(other.z3), z4(other.z4), w1(other.w1), w2(other.w2), w3(other.w3), w4(other.w4)
			{}
			/*copy a matrix*/
			Mat4x4<type>& operator=(const Mat4x4<type>& other)
			{
				x1 = other.x1; x2 = other.x2; x3 = other.x3; x4 = other.x4;
				y1 = other.y1; y2 = other.y2; y3 = other.y3; y4 = other.y4;
				z1 = other.z1; z2 = other.z2; z3 = other.z3; z4 = other.z4;
				w1 = other.w1; w2 = other.w2; w3 = other.w3; w4 = other.w4;
				return *this;
			}

			/*returns an identity matrix | matrices or vectors multiplied by this do not change
			1 0 0 0
			0 1 0 0
			0 0 1 0
			0 0 0 1*/
			static constexpr Mat4x4<type> identity() noexcept
			{
				return Mat4x4<type> {
						1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1 };
			}

			/*returns a scaling matrix | scaling matrices are used to scale a vector/change its size | the vector will keep its direction
			s1 0  0  0   
			0  s2 0  0	 
			0  0  s3 0   
			0  0  0  1  
			vector modification: 
			s1*x
			s2*y
			s3*z
			1*/
			static Mat4x4<type> scaling(type s1, type s2, type s3) noexcept
			{
				return Mat4x4<type> {
						s1, 0, 0, 0,
						0, s2, 0, 0,
						0, 0, s3, 0,
						0, 0, 0, 1 };
			}

			/*returns a scaling matrix | scaling matrices are used to scale a vector/change its size | the vector will keep its direction
			sx 0  0  0
			0  sy 0  0
			0  0  sz 0
			0  0  0  1
			vector modification:
			sx*x
			sy*y
			sz*z
			1*/
			static Mat4x4<type> scaling(const Vec3<type>& s) noexcept
			{
				return Mat4x4<type> {
						s.x, 0, 0, 0,
						0, s.y, 0, 0,
						0, 0, s.z, 0,
						0, 0, 0, 1 };
			}

			/*scales a matrix(more efficient than multiply a scaling matrix to this) | scaling matrices are used to scale a vector/change its size | the vector will keep its direction
			its like multiply a scaling matrix to this matrix, where x/y/z 1 to x/y/z 4 are multiplied by s1/s2/s3 | so the order of methods is important, because the multiplication is not commutative( A*B != B*A)
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			here its first matrix.scale(), then matrix.rotate(), then matrix.translate(), because the arguments are assigned to this matrix | logically this matrix would be the right side matrix
			s1 0  0  0
			0  s2 0  0
			0  0  s3 0
			0  0  0  1
			vector modification:
			s1*x
			s2*y
			s3*z
			1*/
			Mat4x4<type>& scale(type s1, type s2, type s3) noexcept
			{
				x1 *= s1; x2 *= s1; x3 *= s1; x4 *= s1;
				y1 *= s2; y2 *= s2; y3 *= s2; y4 *= s2;
				z1 *= s3; z2 *= s3; z3 *= s3; z4 *= s3;
				return *this;
			}

			/*scales a matrix(more efficient than multiply a scaling matrix to this) | scaling matrices are used to scale a vector/change its size | the vector will keep its direction
			its like multiply a scaling matrix to this matrix, where x/y/z 1 to x/y/z 4 are multiplied by sx/sy/sz | the parameter vector is not scaled! | so the order of methods is important, because the multiplication is not commutative( A*B != B*A)
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			here its first matrix.scale(), then matrix.rotate(), then matrix.translate(), because the arguments are assigned to this matrix | logically this matrix would be the right side matrix
			sx 0  0  0
			0  sy 0  0
			0  0  sz 0
			0  0  0  1
			vector modification:
			sx*x
			sy*y
			sz*z
			1*/
			Mat4x4<type>& scale(const Vec3<type>& s) noexcept
			{
				x1 *= s.x; x2 *= s.x; x3 *= s.x; x4 *= s.x;
				y1 *= s.y; y2 *= s.y; y3 *= s.y; x4 *= s.y;
				z1 *= s.z; z2 *= s.z; z3 *= s.z; x4 *= s.z;
				return *this;
			}

			/*returns a translation matrix | translation matrices are used to translate a vector/move it | you can only translate a vec with a w=1(position vector) and not a vec with w=0(direction vector)
			1  0  0  t1
			0  1  0  t2
			0  0  1  t3
			0  0  0  1
			vector modification:
			x+t1
			y+t2
			z+t3
			1*/
			static Mat4x4<type> translation(type t1, type t2, type t3) noexcept
			{
				return Mat4x4<type> {
						1, 0, 0, t1,
						0, 1, 0, t2, 
						0, 0, 1, t3, 
						0, 0, 0, 1 };
			}

			/*returns a translation matrix | translation matrices are used to translate a vector/move it | you can only translate a vec with a w=1(position vector) and not a vec with w=0(direction vector)
			1  0  0  tx
			0  1  0  ty
			0  0  1  tz
			0  0  0  1
			vector modification:
			x+tx
			y+ty
			z+tz
			1*/
			static Mat4x4<type> translation(const Vec3<type>& t) noexcept
			{
				return Mat4x4<type> {
						1, 0, 0, t.x,
						0, 1, 0, t.y,
						0, 0, 1, t.z,
						0, 0, 0, 1 };
			}

			/*translates a matrix(more efficient than multiply a translation matrix to this) | translation matrices are used to translate a vector/move it | you can only translate a vec with a w=1(position vector) and not a vec with w=0(direction vector)
			its like multiply a translation matrix to this matrix, where t1/t2/t3 is added to x/y/z 1 to x/y/z 4  | so the order of methods is important, because the multiplication is not commutative( A*B != B*A)
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			here its first matrix.scale(), then matrix.rotate(), then matrix.translate(), because the arguments are assigned to this matrix | logically this matrix would be the right side matrix
			1  0  0  t1
			0  1  0  t2
			0  0  1  t3
			0  0  0  1
			vector modification:
			x+t1
			y+t2
			z+t3
			1*/
			Mat4x4<type>& translate(type t1, type t2, type t3) noexcept
			{
				x1 += t1 * w1;
				x2 += t1 * w2;
				x3 += t1 * w3;
				x4 += t1 * w4;
				   
				y1 += t2 * w1;
				y2 += t2 * w2;
				y3 += t2 * w3;
				y4 += t2 * w4;
				   		   
				z1 += t3 * w1;
				z2 += t3 * w2;
				z3 += t3 * w3;
				z4 += t3 * w4;
				return *this;
			}

			/*translates a matrix(more efficient than multiply a translation matrix to this) | translation matrices are used to translate a vector/move it | you can only translate a vec with a w=1(position vector) and not a vec with w=0(direction vector)
			its like multiply a translation matrix to this matrix, where tx/ty/tz is added to x/y/z 1 to x/y/z 4 | the parameter vector is not translated! | so the order of methods is important, because the multiplication is not commutative( A*B != B*A)
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			here its first matrix.scale(), then matrix.rotate(), then matrix.translate(), because the arguments are assigned to this matrix | logically this matrix would be the right side matrix
			1  0  0  tx
			0  1  0  ty
			0  0  1  tz
			0  0  0  1
			vector modification:
			x+tx
			y+ty
			z+tz
			1*/
			Mat4x4<type>& translate(const Vec3<type>& t) noexcept
			{
				x1 += t.x * w1;
				x2 += t.x * w2;
				x3 += t.x * w3;
				x4 += t.x * w4;
				   
				y1 += t.y * w1;
				y2 += t.y * w2;
				y3 += t.y * w3;
				y4 += t.y * w4;
				   			
				z1 += t.z * w1;
				z2 += t.z * w2;
				z3 += t.z * w3;
				z4 += t.z * w4;
				return *this;
			}

			/*returns a scaling and translation matrix combined | scaling matrices are used to scale a vector/change its size and translation matrices are used to translate a vector/move it
			you can only translate a vec with a w=1(position vector) and not a vec with w=0(direction vector) | the scaling is applied before the translation
			s1  0   0   t1
			0   s2  0   t2
			0   0   s3  t3
			0   0   0   1
			vector modification:
			x*s1+t1
			y*s2+t2
			z*s3+t3
			1*/
			static Mat4x4<type> scaleTrans(type s1, type s2, type s3, type t1, type t2, type t3) noexcept
			{
				return Mat4x4<type> {
						s1, 0, 0, t1,
						0, s2, 0, t2,
						0, 0, s3, t3,
						0, 0, 0, 1 };
			}

			/*returns a scaling and translation matrix combined | scaling matrices are used to scale a vector/change its size and translation matrices are used to translate a vector/move it
			you can only translate a vec with a w=1(position vector) and not a vec with w=0(direction vector) | the scaling is applied before the translation
			sx  0   0   tx
			0   sy  0   ty
			0   0   sz  tz
			0   0   0   1
			vector modification:
			x*s1+t1
			y*s2+t2
			z*s3+t3
			1*/
			static Mat4x4<type> scaleTrans(const Vec3<type>& s, const Vec3<type>& t) noexcept
			{
				return Mat4x4<type> {
						s.x, 0, 0, t.x,
						0, s.y, 0, t.y,
						0, 0, s.z, t.z,
						0, 0, 0, 1 };
			}




			/*returns a rotation matrix for the x-axis with the angle parameter as degrees | rotation matrices are used to rotate a vector at a given angle along the rotation axis
			s=sin(angle), c=cos(angle)
			1  0  0   0
			0  c  -s  0
			0  s  c   0
			0  0  0   1
			vector modification:
			x
			c*y-s*z
			s*y+c*z
			1*/
			static Mat4x4<type> rotationXD(type degrees) noexcept
			{
				return Mat4x4<type> {
						1, 0, 0, 0,
						0, maths::cosD(degrees),-maths::sinD(degrees), 0,
						0, maths::sinD(degrees), maths::cosD(degrees), 0,
						0, 0, 0, 1 };
			}

			/*returns a rotation matrix for the x-axis with the angle parameter as radians | rotation matrices are used to rotate a vector at a given angle along the rotation axis
			s=sin(angle), c=cos(angle)
			1  0  0   0
			0  c  -s  0
			0  s  c   0
			0  0  0   1
			vector modification:
			x
			c*y-s*z
			s*y+c*z
			1*/
			static Mat4x4<type> rotationXR(type radians) noexcept
			{
				return Mat4x4<type> {
						1, 0, 0, 0,
						0, maths::cosR(radians),-maths::sinR(radians), 0,
						0, maths::sinR(radians), maths::cosR(radians), 0,
						0, 0, 0, 1 };
			}

			/*rotates a matrix around the x-axis with the angle parameter as degrees (more efficient than multiply a rotation matrix to this) | rotation matrices are used to rotate a vector at a given angle along the rotation axis
			s=sin(angle), c=cos(angle) its like multiply a rotation matrix to this matrix | so the order of methods is important, because the multiplication is not commutative( A*B != B*A)
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			here its first matrix.scale(), then matrix.rotate(), then matrix.translate(), because the arguments are assigned to this matrix | logically this matrix would be the right side matrix
			1  0  0   0
			0  c  -s  0
			0  s  c   0
			0  0  0   1
			vector modification:
			x
			c*y-s*z
			s*y+c*z
			1*/
			Mat4x4<type>& rotateXD(type degrees) noexcept
			{
				type temp = maths::cosD(degrees) * y1 + -maths::sinD(degrees) * z1;
				z1 = maths::sinD(degrees) * y1 + maths::cosD(degrees) * z1;
				y1 = temp;
				temp = maths::cosD(degrees) * y2 + -maths::sinD(degrees) * z2;
				z2 = maths::sinD(degrees) * y2 + maths::cosD(degrees) * z2;
				y2 = temp;
				temp = maths::cosD(degrees) * y3 + -maths::sinD(degrees) * z3;
				z3 = maths::sinD(degrees) * y3 + maths::cosD(degrees) * z3;
				y3 = temp;
				temp = maths::cosD(degrees) * y4 + -maths::sinD(degrees) * z4;
				z4 = maths::sinD(degrees) * y4 + maths::cosD(degrees) * z4;
				y4 = temp;
				return *this;
			}

			/*rotates a matrix around the x-axis with the angle parameter as radians (more efficient than multiply a rotation matrix to this) | rotation matrices are used to rotate a vector at a given angle along the rotation axis
			s=sin(angle), c=cos(angle) its like multiply a rotation matrix to this matrix | so the order of methods is important, because the multiplication is not commutative( A*B != B*A)
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			here its first matrix.scale(), then matrix.rotate(), then matrix.translate(), because the arguments are assigned to this matrix | logically this matrix would be the right side matrix
			1  0  0   0
			0  c  -s  0
			0  s  c   0
			0  0  0   1
			vector modification:
			x
			c*y-s*z
			s*y+c*z
			1*/
			Mat4x4<type>& rotateXR(type radians) noexcept
			{
				type temp = maths::cosR(radians) * y1 + -maths::sinR(radians) * z1;
				z1 = maths::sinR(radians) * y1 + maths::cosR(radians) * z1;
				y1 = temp;
				temp = maths::cosR(radians) * y2 + -maths::sinR(radians) * z2;
				z2 = maths::sinR(radians) * y2 + maths::cosR(radians) * z2;
				y2 = temp;
				temp = maths::cosR(radians) * y3 + -maths::sinR(radians) * z3;
				z3 = maths::sinR(radians) * y3 + maths::cosR(radians) * z3;
				y3 = temp;
				temp = maths::cosR(radians) * y4 + -maths::sinR(radians) * z4;
				z4 = maths::sinR(radians) * y4 + maths::cosR(radians) * z4;
				y4 = temp;
				return *this;
			}

			/*returns a rotation matrix for the y-axis with the angle parameter as degrees | rotation matrices are used to rotate a vector at a given angle along the rotation axis
			s=sin(angle), c=cos(angle)
			c	0  s  0
			0	1  0  0
			-s  0  c  0
			0	0  0  1
			vector modification:
			c*x+s*z
			y
			-s*x+c*z
			1*/
			static Mat4x4<type> rotationYD(type degrees) noexcept
			{
				return Mat4x4<type> {
						maths::cosD(degrees), 0, maths::sinD(degrees), 0,
						0, 1, 0, 0,
						-maths::sinD(degrees), 0, maths::cosD(degrees), 0,
						0, 0, 0, 1 };
			}
			/*returns a rotation matrix for the y-axis with the angle parameter as radians | rotation matrices are used to rotate a vector at a given angle along the rotation axis
			s=sin(angle), c=cos(angle)
			c	0  s  0
			0	1  0  0
			-s  0  c  0
			0	0  0  1
			vector modification:
			c*x+s*z
			y
			-s*x+c*z
			1*/

			static Mat4x4<type> rotationYR(type radians) noexcept
			{
				return Mat4x4<type> {
						maths::cosR(radians), 0, maths::sinR(radians), 0,
						0, 1, 0, 0,
						-maths::sinR(radians), 0, maths::cosR(radians), 0,
						0, 0, 0, 1 };
			}

			/*rotates a matrix around the y-axis with the angle parameter as degrees (more efficient than multiply a rotation matrix to this) | rotation matrices are used to rotate a vector at a given angle along the rotation axis
			s=sin(angle), c=cos(angle) its like multiply a rotation matrix to this matrix | so the order of methods is important, because the multiplication is not commutative( A*B != B*A)
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			here its first matrix.scale(), then matrix.rotate(), then matrix.translate(), because the arguments are assigned to this matrix | logically this matrix would be the right side matrix
			c	0  s  0
			0	1  0  0
			-s  0  c  0
			0	0  0  1
			vector modification:
			c*x+s*z
			y
			-s*x+c*z
			1*/
			Mat4x4<type>& rotateYD(type degrees) noexcept
			{
				type temp = maths::cosD(degrees) * x1 + maths::sinD(degrees) * z1;
				z1 = -maths::sinD(degrees) * x1 + maths::cosD(degrees) * z1;
				x1 = temp;
				temp = maths::cosD(degrees) * x2 + maths::sinD(degrees) * z2;
				z2 = -maths::sinD(degrees) * x2 + maths::cosD(degrees) * z2;
				x2 = temp;
				temp = maths::cosD(degrees) * x3 + maths::sinD(degrees) * z3;
				z3 = -maths::sinD(degrees) * x3 + maths::cosD(degrees) * z3;
				x3 = temp;
				temp = maths::cosD(degrees) * x4 + maths::sinD(degrees) * z4;
				z4 = -maths::sinD(degrees) * x4 + maths::cosD(degrees) * z4;
				x4 = temp;
				return *this;
			}

			/*rotates a matrix around the y-axis with the angle parameter as degrees (more efficient than multiply a rotation matrix to this) | rotation matrices are used to rotate a vector at a given angle along the rotation axis
			s=sin(angle), c=cos(angle) its like multiply a rotation matrix to this matrix | so the order of methods is important, because the multiplication is not commutative( A*B != B*A)
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			here its first matrix.scale(), then matrix.rotate(), then matrix.translate(), because the arguments are assigned to this matrix | logically this matrix would be the right side matrix
			c	0  s  0
			0	1  0  0
			-s  0  c  0
			0	0  0  1
			vector modification:
			c*x+s*z
			y
			-s*x+c*z
			1*/
			Mat4x4<type>& rotateYR(type radians) noexcept
			{
				type temp = maths::cosR(radians) * x1 + maths::sinR(radians) * z1;
				z1 = -maths::sinR(radians) * x1 + maths::cosR(radians) * z1;
				x1 = temp;
				temp = maths::cosR(radians) * x2 + maths::sinR(radians) * z2;
				z2 = -maths::sinR(radians) * x2 + maths::cosR(radians) * z2;
				x2 = temp;
				temp = maths::cosR(radians) * x3 + maths::sinR(radians) * z3;
				z3 = -maths::sinR(radians) * x3 + maths::cosR(radians) * z3;
				x3 = temp;
				temp = maths::cosR(radians) * x4 + maths::sinR(radians) * z4;
				z4 = -maths::sinR(radians) * x4 + maths::cosR(radians) * z4;
				x4 = temp;
				return *this;
			}


			/*returns a rotation matrix for the z-axis with the angle parameter as degrees | rotation matrices are used to rotate a vector at a given angle along the rotation axis
			s=sin(angle), c=cos(angle)
			c  -s  0  0
			s  c   0  0
			0  0   1  0
			0  0   0  1
			vector modification:
			c*x-s*y
			s*x+c*y
			z
			1*/
			static Mat4x4<type> rotationZD(type degrees) noexcept
			{
				return Mat4x4<type> {
						maths::cosD(degrees), -maths::sinD(degrees), 0, 0,
						maths::sinD(degrees), maths::cosD(degrees), 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1 };
			}

			/*returns a rotation matrix for the z-axis with the angle parameter as radians | rotation matrices are used to rotate a vector at a given angle along the rotation axis
			s=sin(angle), c=cos(angle)
			c  -s  0  0
			s  c   0  0
			0  0   1  0
			0  0   0  1
			vector modification:
			c*x-s*y
			s*x+c*y
			z
			1*/
			static Mat4x4<type> rotationZR(type radians) noexcept
			{
				return Mat4x4<type> {
						maths::cosR(radians), -maths::sinR(radians), 0, 0,
						maths::sinR(radians), maths::cosR(radians), 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1 };
			}

			/*rotates a matrix around the z-axis with the angle parameter as degrees (more efficient than multiply a rotation matrix to this) | rotation matrices are used to rotate a vector at a given angle along the rotation axis
			s=sin(angle), c=cos(angle) its like multiply a rotation matrix to this matrix | so the order of methods is important, because the multiplication is not commutative( A*B != B*A)
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			here its first matrix.scale(), then matrix.rotate(), then matrix.translate(), because the arguments are assigned to this matrix | logically this matrix would be the right side matrix
			c  -s  0  0
			s  c   0  0
			0  0   1  0
			0  0   0  1
			vector modification:
			c*x-s*y
			s*x+c*y
			z
			1*/
			Mat4x4<type>& rotateZD(type degrees) noexcept
			{
				type temp = maths::cosD(degrees) * x1 + -maths::sinD(degrees) * y1;
				y1 = maths::sinD(degrees) * x1 + maths::cosD(degrees) * y1;
				x1 = temp;
				temp = maths::cosD(degrees) * x2 + -maths::sinD(degrees) * y2;
				y2 = maths::sinD(degrees) * x2 + maths::cosD(degrees) * y2;
				x2 = temp;
				temp = maths::cosD(degrees) * x3 + -maths::sinD(degrees) * y3;
				y3 = maths::sinD(degrees) * x3 + maths::cosD(degrees) * y3;
				x3 = temp;
				temp = maths::cosD(degrees) * x4 + -maths::sinD(degrees) * y4;
				y4 = maths::sinD(degrees) * x4 + maths::cosD(degrees) * y4;
				x4 = temp;
				return *this;
			}

			/*rotates a matrix around the z-axis with the angle parameter as degrees (more efficient than multiply a rotation matrix to this) | rotation matrices are used to rotate a vector at a given angle along the rotation axis
			s=sin(angle), c=cos(angle) its like multiply a rotation matrix to this matrix | so the order of methods is important, because the multiplication is not commutative( A*B != B*A)
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			here its first matrix.scale(), then matrix.rotate(), then matrix.translate(), because the arguments are assigned to this matrix | logically this matrix would be the right side matrix
			c  -s  0  0
			s  c   0  0
			0  0   1  0
			0  0   0  1
			vector modification:
			c*x-s*y
			s*x+c*y
			z
			1*/
			Mat4x4<type>& rotateZR(type radians) noexcept
			{
				type temp = maths::cosR(radians) * x1 + -maths::sinR(radians) * y1;
				y1 = maths::sinR(radians) * x1 + maths::cosR(radians) * y1;
				x1 = temp;
				temp = maths::cosR(radians) * x2 + -maths::sinR(radians) * y2;
				y2 = maths::sinR(radians) * x2 + maths::cosR(radians) * y2;
				x2 = temp;
				temp = maths::cosR(radians) * x3 + -maths::sinR(radians) * y3;
				y3 = maths::sinR(radians) * x3 + maths::cosR(radians) * y3;
				x3 = temp;
				temp = maths::cosR(radians) * x4 + -maths::sinR(radians) * y4;
				y4 = maths::sinR(radians) * x4 + maths::cosR(radians) * y4;
				x4 = temp;
				return *this;
			}

			/*returns a rotation matrix for a given axis(axis.x,axis.y,axis.z) with the angle parameter as degrees | rotation matrices are used to rotate a vector at a given angle along the rotation axis*/
			static Mat4x4<type> rotationD(type degrees, Vec3<type> axis) noexcept
			{
				axis.normalizeSelf();
				return Mat4x4<type> {
						maths::cosD(degrees) + axis.x * axis.x*( static_cast<type>(1) - maths::cosD(degrees) ),
						axis.x*axis.y*( static_cast<type>(1) - maths::cosD(degrees) ) - axis.z * maths::sinD(degrees),
						axis.x*axis.z*( static_cast<type>(1) - maths::cosD(degrees) ) + axis.y * maths::sinD(degrees),
						0,
						axis.y*axis.x*( static_cast<type>(1) - maths::cosD(degrees) ) + axis.z * maths::sinD(degrees),
						maths::cosD(degrees) + axis.y * axis.y*( static_cast<type>(1) - maths::cosD(degrees) ),
						axis.y*axis.z*( static_cast<type>(1) - maths::cosD(degrees) ) - axis.x * maths::sinD(degrees),
						0,
						axis.z*axis.x*( static_cast<type>(1) - maths::cosD(degrees) ) - axis.y * maths::sinD(degrees),
						axis.z*axis.y*( static_cast<type>(1) - maths::cosD(degrees) ) + axis.x * maths::sinD(degrees),
						maths::cosD(degrees) + axis.z * axis.z*( static_cast<type>(1) - maths::cosD(degrees) ),
						0,
						0,
						0,
						0,
						1 };
			}

			/*returns a rotation matrix for a given axis(axis.x,axis.y,axis.z) with the angle parameter as radians | rotation matrices are used to rotate a vector at a given angle along the rotation axis*/
			static Mat4x4<type> rotationR(type radians, Vec3<type> axis) noexcept
			{
				axis.normalizeSelf();
				return Mat4x4<type> {
						maths::cosR(radians) + axis.x * axis.x*( 1 - maths::cosR(radians) ),
						axis.x*axis.y*( 1 - maths::cosR(radians) ) - axis.z * maths::sinR(radians),
						axis.x*axis.z*( 1 - maths::cosR(radians) ) + axis.y * maths::sinR(radians),
						0,
						axis.y*axis.x*( 1 - maths::cosR(radians) ) + axis.z * maths::sinR(radians),
						maths::cosR(radians) + axis.y * axis.y*( 1 - maths::cosR(radians) ),
						axis.y*axis.z*( 1 - maths::cosR(radians) ) - axis.x * maths::sinR(radians),
						0,
						axis.z*axis.x*( 1 - maths::cosR(radians) ) - axis.y * maths::sinR(radians),
						axis.z*axis.y*( 1 - maths::cosR(radians) ) + axis.x * maths::sinR(radians),
						maths::cosR(radians) + axis.z * axis.z*( 1 - maths::cosR(radians) ),
						0,
						0,
						0,
						0,
						1 };
			}


			/*~local/object space: one object with its position relative to its origin(0,0,0) where each vertex has a diffrent position
			->transformed with model matrix: rotate/scale/translate the object, so it fits in the world
			~world space: relative to worlds origin(0,0,0) with a large game world and many objects | camera will likely look in the -z directio, so if you want objects to move away from you, the camera has to move in the z+ direction, otherwise if the camera should move closer to the objects z- direction
			->transformed with view matrix: scale/rotate/translate the scene, so the objects in front of the camera are in the focus
			~view space: relative to the viewers point of view(camera)
			->transformed with projection matrix: transforms a range of 3d coordinates(-1000 to 1000) in each dimension to normalized 2d device coordinates(-1 to 1) for the screen | objects outside the range are not visible(if not atleast one vertex position is in the range)
			objects in the frustum range are visible to the screen | also the x/y/z are devided by w of the vectors in the end of the vertex shader for each vertex to scale them

			opengl uses right hand system for world coordinates (y goes to the top++, x goes to the right ++ and z goes to you ++) | the projection matrix(orthographic or perspective) will convert the hand system from right handed to left handed for the normalized screen coordinates(z goes away from you ++)

			~clip space: normalized device coordinates between -1.0 and 1.0 | the vertex shader also works with normalized device coordinates with gl_position
			->transformed with viewport:
			~screen space:
			
			orthographic projection matrix: cube like frustum box for clipping space between 2 planes(near and far) with a width/height | does not change the w component for scaling of each vector(leaves it at 1) | all objects have the same size | better for 2d
			left(x), right(x+width), bottom(y), top(y+height) are the 4 points that define the size of the near/far planes and the parameter near(z)/far(z+depth) define the distance between the planes */
			static Mat4x4<type> orthographic(type left, type right, type bottom, type top, type near1, type far1)
			{
				return Mat4x4<type>{
						static_cast<type>( 2 ) / ( right - left ), 0, 0, -( right + left ) / ( right - left ),
						0, static_cast<type>( 2 ) / ( top - bottom ), 0, -( top + bottom ) / ( top - bottom ),
						0, 0, static_cast<type>( 2 ) / ( far1 - near1 ), -( far1 + near1 ) / ( far1 - near1 ),
						0, 0, 0, 1
				};
			}

			/*~local/object space: one object with its position relative to its origin(0,0,0) where each vertex has a diffrent position
			->transformed with model matrix: rotate/scale/translate the object, so it fits in the world
			~world space: relative to worlds origin(0,0,0) with a large game world and many objects | camera will likely look in the -z directio, so if you want objects to move away from you, the camera has to move in the z+ direction, otherwise if the camera should move closer to the objects z- direction
			->transformed with view matrix: scale/rotate/translate the scene, so the objects in front of the camera are in the focus
			~view space: relative to the viewers point of view(camera)
			->transformed with projection matrix: transforms a range of 3d coordinates(-1000 to 1000) in each dimension to normalized 2d device coordinates(-1 to 1) for the screen | objects outside the range are not visible(if not atleast one vertex position is in the range)
			objects in the frustum range are visible to the screen | also the x/y/z are devided by w of the vectors in the end of the vertex shader for each vertex to scale them 

			opengl uses right hand system for world coordinates (y goes to the top++, x goes to the right ++ and z goes to you ++) | the projection matrix(orthographic or perspective) will convert the hand system from right handed to left handed for the normalized screen coordinates(z goes away from you ++)

			~clip space: normalized device coordinates between -1.0 and 1.0 | the vertex shader also works with normalized device coordinates with gl_position
			->transformed with viewport:
			~screen space: 

			perspective projection matrix: objects that are farther away appear much smaller by scaling w component of each vector(higher w if further away then each component of the vector is devided by w )
			non uniformly shaped box frustum with a smaller near plane and a bigger far plane | better for 3d
			@param[fov] angle in degrees of the field of view defines how large the viewspace is | realistic would be 45 degrees, but can be bigger for a bigger viewspace(90, 120, etc)
			@param[aspect] the screen ratio | divide viewport width by its height to get the aspect ratio(screen size in pixel) | so this matrix has to be recalculated when the window is resized and the viewport changed
			@param[near1/far1] the z coordinates of the planes of the frustum to get the distance */
			static Mat4x4<type> perspective(type fov, type aspect, type near1, type far1)
			{
				type tan = maths::tanR(fov / static_cast<type>( 2 ));
				return Mat4x4<type>{
						static_cast<type>( 1 ) / ( aspect * tan ), 0, 0, 0,
						0, static_cast<type>( 1 ) / ( tan ), 0, 0,
						0, 0, ( far1 + near1 ) / ( far1 - near1 ), -( static_cast<type>( 2 ) * far1 * near1 ) / ( far1 - near1 ),
						0, 0, static_cast<type>( 1 ), 0
				};
			}

			/*calculates a camera view matrix to transform any vector to the view/camera space by multiply the matrix to it | transforms world space to view space
			the camera matrix has a coordinate system with the camera position(translation) as its origin and with 3 axes(x,y,z) | the camera is looking at the target vector
			the camera uses opengls right hand coordinate system with x++ to the right, y++ up and z++ to you out of the screen | the camera position inside the matrix will be inverted, because the world will be moved in the opposite direction of where the camera moves
			@param[camera] the position of the camera in world space
			@param[target] the position of the target in world space
			@param[up] a help vector to calculate the axes should point up in world space | the default parameter is the y-axis direction*/
			static Mat4x4<type> lookAt(const Vec3<type>& camera, const Vec3<type>& target, const Vec3<type>& up = { 0,1,0 })
			{
				Vec3<type> direction { ( target - camera ).normalizeSelf() };//z 
				//will be treated as normalized direction vector in positive z-axis(position-target) because of opengls right hand coordinate system | its the reverse direction of the distance to the target(not from camera to target, but from target to camera) | so it will be negated
				Vec3<type> right { ( up.crossproduct(direction) ).normalizeSelf() };//x 
				Vec3<type> newUP { direction.crossproduct(right) };//y | y-axis of the camera
				return Mat4x4<type>{
						right.x, right.y, right.z, -right.dotproduct(camera),
						newUP.x, newUP.y, newUP.z, -newUP.dotproduct(camera),
						direction.x, direction.y, direction.z, -direction.dotproduct(camera),
						0,0,0,1
				};

			}


		public:
			/*returns the determinant of the matrix | the number of rows have to be the same as the number of colums, so it has to be a square matrix
			the absolut value of the determinant describes the volume/area of the matrix | det(mat1*mat2) = det(mat1)*det(mat2) | det(value*mat) = value^n * det(mat) n=number of rows/columns 
			the determinant of 2 matrices is the same, if the rows and columns swap values(like turning the matrix diagonal)
			*/
			type determinant() noexcept
			{
				/*2x2 return (x1*y2-x2*y1);*/
				/*3x3 return x1*y2*z3 + x2*y3*z1 + x3*y1*z2 - x3*y2*z1 - x1*y3*z2 - x1*y1*z3    */
				return 
					x4*y3*z2*w1 - x3 * y4*z2*w1 - x4 * y2*z3*w1 + x2 * y4*z3*w1 +
					x3 * y2*z4*w1 - x2 * y3*z4*w1 - x4 * y3*z1*w2 + x3 * y4*z1*w2 +
					x4 * y1*z3*w2 - x1 * y4*z3*w2 - x3 * y1*z4*w2 + x1 * y3*z4*w2 +
					x4 * y2*z1*w3 - x2 * y4*z1*w3 - x4 * y1*z2*w3 + x1 * y4*z2*w3 +
					x2 * y1*z4*w3 - x1 * y2*z4*w3 - x3 * y2*z1*w4 + x2 * y3*z1*w4 +
					x3 * y1*z2*w4 - x1 * y3*z2*w4 - x2 * y1*z3*w4 + x1 * y2*z3*w4;
			}

			/*returns the inverse matrix of this matrix | would be the same as pow(-1) | this matrix multiplied by the inverse matrix will be the identity matrix | this* this^-1 = identity 
			the order of the multiplication between the old matrix and its inverse matrix to get the identity matrix does not matter, so here the multiplication is commutative: this*inverse = inverse*this
			returns a copy of the matrix and does not modify this matrix | the number of rows have to be the same as the number of columns, so it has to be a square matrix and the determinant has to be not zero
			newmat = this * this; | identity^-1 = identity | (mat^-1)^-1=mat | (mat1*mat2)^-1 = mat1^-1*mat2^-1 | (mat^n)^-1 = (mat^-1)^n
			*/
			Mat4x4<type> inverse() noexcept
			{
				/*2x2
				return Mat2x2<type>(y2,-x2,-y1,x1).multiply( 1/determinant() );
				3x3
				return Mat3x3<type>(
				y2*z3-y3*z2, x3*z2-x2*z3, x2*y3-x3*y2,
				y3*z1-y1*z3, x1*z3-x3*z1, x3*y1-x1*y3,
				y1*z2-y2*z1, x2*z1-x1*z2, x1*y2-x2*y1
				).multiply(1/determinant());
				*/
				return Mat4x4<type>(
					y3 * z4*w2 - y4 * z3*w2 + y4 * z2*w3 - y2 * z4*w3 - y3 * z2*w4 + y2 * z3*w4,
					x4 * z3*w2 - x3 * z4*w2 - x4 * z2*w3 + x2 * z4*w3 + x3 * z2*w4 - x2 * z3*w4,
					x3 * y4*w2 - x4 * y3*w2 + x4 * y2*w3 - x2 * y4*w3 - x3 * y2*w4 + x2 * y3*w4,
					x4 * y3*z2 - x3 * y4*z2 - x4 * y2*z3 + x2 * y4*z3 + x3 * y2*z4 - x2 * y3*z4,
					y4 * z3*w1 - y3 * z4*w1 - y4 * z1*w3 + y1 * z4*w3 + y3 * z1*w4 - y1 * z3*w4,
					x3 * z4*w1 - x4 * z3*w1 + x4 * z1*w3 - x1 * z4*w3 - x3 * z1*w4 + x1 * z3*w4,
					x4 * y3*w1 - x3 * y4*w1 - x4 * y1*w3 + x1 * y4*w3 + x3 * y1*w4 - x1 * y3*w4,
					x3 * y4*z1 - x4 * y3*z1 + x4 * y1*z3 - x1 * y4*z3 - x3 * y1*z4 + x1 * y3*z4,
					y2 * z4*w1 - y4 * z2*w1 + y4 * z1*w2 - y1 * z4*w2 - y2 * z1*w4 + y1 * z2*w4,
					x4 * z2*w1 - x2 * z4*w1 - x4 * z1*w2 + x1 * z4*w2 + x2 * z1*w4 - x1 * z2*w4,
					x2 * y4*w1 - x4 * y2*w1 + x4 * y1*w2 - x1 * y4*w2 - x2 * y1*w4 + x1 * y2*w4,
					x4 * y2*z1 - x2 * y4*z1 - x4 * y1*z2 + x1 * y4*z2 + x2 * y1*z4 - x1 * y2*z4,
					y3 * z2*w1 - y2 * z3*w1 - y3 * z1*w2 + y1 * z3*w2 + y2 * z1*w3 - y1 * z2*w3,
					x2 * z3*w1 - x3 * z2*w1 + x3 * z1*w2 - x1 * z3*w2 - x2 * z1*w3 + x1 * z2*w3,
					x3 * y2*w1 - x2 * y3*w1 - x3 * y1*w2 + x1 * y3*w2 + x2 * y1*w3 - x1 * y2*w3,
					x2 * y3*z1 - x3 * y2*z1 + x3 * y1*z2 - x1 * y3*z2 - x2 * y1*z3 + x1 * y2*z3).multiply(static_cast<type>(1) / determinant());
			}

			/*multiplies the matrix n times with itself | use this method instead of this*=this; | scalar product matrix-matrix multiplication, not elementwise multiplication | use the multiply method for the elementwise multiplication
			returns a copy of the matrix and does not modify this matrix | mat^0 = identity | m1^n * m2^n = (m1*m2)^n | determinant(mat^n)= det(mat)^n | only use positive count numbers and dont use 0
			the number of rows have to be the same as the number of columns, so it has to be a square matrix
			newmat = this * this;
			*/
			Mat4x4<type> pow(unsigned int count) noexcept
			{
				if ( count == 0 )
					return identity();
				Mat4x4<type> temp(*this);
				for ( unsigned int i = 1; i < count; ++i )
				{
					temp *= *this;
				}
				return temp;
			}

			/*multiplies the matrix n times with itself | use this method instead of this*=this; | scalar product matrix-matrix multiplication, not elementwise multiplication | use the multiply method for the elementwise multiplication
			returns the matrix and modifies this matrix | mat^0 = identity | m1^n * m2^n = (m1*m2)^n | determinant(mat^n)= det(mat)^n | only use positive count numbers and dont use 0
			the number of rows have to be the same as the number of columns, so it has to be a square matrix
			this = this * this;
			*/
			Mat4x4<type>& powSelf(unsigned int count) noexcept
			{
				Mat4x4<type> temp(*this);
				for ( unsigned int i = 1; i < count; ++i )
				{
					*this *= temp;
				}
				return *this;
			}

			/*returns the nth root of the matrix as a copy and does not modify the matrix | only positive count numbers
			square root: newmat * newmat == this; 
			the number of rows have to be the same as the number of columns, so it has to be a square matrix*/
			Mat4x4<type> root(unsigned int count) noexcept
			{

			}

			/*returns the nth root of the matrix and also modifies this matrix | only positive count numbers
			square root: thisnew * thisnew == this;
			the number of rows have to be the same as the number of columns, so it has to be a square matrix*/
			Mat4x4<type>& rootSelf(unsigned int count) noexcept
			{

			}

			//add a value to this 
			Mat4x4<type>& add(type val) noexcept
			{
				x1 += val; x2 += val; x3 += val; x4 += val;
				y1 += val; y2 += val; y3 += val; y4 += val;
				z1 += val; z2 += val; z3 += val; z4 += val;
				w1 += val; w2 += val; w3 += val; w4 += val;
				return *this;
			}
			//add another Mat4x4 to this 
			Mat4x4<type>& add(const Mat4x4<type>& other) noexcept
			{
				x1 += other.x1; x2 += other.x2; x3 += other.x3; x4 += other.x4;
				y1 += other.y1; y2 += other.y2; y3 += other.y3; y4 += other.y4;
				z1 += other.z1; z2 += other.z2; z3 += other.z3; z4 += other.z4;
				w1 += other.w1; w2 += other.w2; w3 += other.w3; w4 += other.w4;
				return *this;
			}
			//substract a value from this 
			Mat4x4<type>& substract(type val) noexcept
			{
				x1 -= val; x2 -= val; x3 -= val; x4 -= val;
				y1 -= val; y2 -= val; y3 -= val; y4 -= val;
				z1 -= val; z2 -= val; z3 -= val; z4 -= val;
				w1 -= val; w2 -= val; w3 -= val; w4 -= val;
				return *this;
			}
			//substract another Mat4x4 from this 
			Mat4x4<type>& substract(const Mat4x4<type>& other) noexcept
			{
				x1 -= other.x1; x2 -= other.x2; x3 -= other.x3; x4 -= other.x4;
				y1 -= other.y1; y2 -= other.y2; y3 -= other.y3; y4 -= other.y4;
				z1 -= other.z1; z2 -= other.z2; z3 -= other.z3; z4 -= other.z4;
				w1 -= other.w1; w2 -= other.w2; w3 -= other.w3; w4 -= other.w4;
				return *this;
			}
			//multiply a value to this | elementwise multiplication, not scalar product matrix-matrix multiplication | use the math operators(* *=) for the normal scalar product matrix-matrix multiplication
			Mat4x4<type>& multiply(type val) noexcept
			{
				x1 *= val; x2 *= val; x3 *= val; x4 *= val;
				y1 *= val; y2 *= val; y3 *= val; y4 *= val;
				z1 *= val; z2 *= val; z3 *= val; z4 *= val;
				w1 *= val; w2 *= val; w3 *= val; w4 *= val;
				return *this;
			}
			//multiply another Mat4x4 to this | elementwise, not dotproduct
			Mat4x4<type>& multiply(const Mat4x4<type>& other) noexcept
			{
				x1 *= other.x1; x2 *= other.x2; x3 *= other.x3; x4 *= other.x4;
				y1 *= other.y1; y2 *= other.y2; y3 *= other.y3; y4 *= other.y4;
				z1 *= other.z1; z2 *= other.z2; z3 *= other.z3; z4 *= other.z4;
				w1 *= other.w1; w2 *= other.w2; w3 *= other.w3; w4 *= other.w4;
				return *this;
			}
			//divide a value from this 
			Mat4x4<type>& divide(type val) noexcept
			{
				x1 /= val; x2 /= val; x3 /= val; x4 /= val;
				y1 /= val; y2 /= val; y3 /= val; y4 /= val;
				z1 /= val; z2 /= val; z3 /= val; z4 /= val;
				w1 /= val; w2 /= val; w3 /= val; w4 /= val;
				return *this;
			}
			//divide another Mat4x4 from this | elementwise division, not scalar product matrix-matrix division | use the math operators(/ /=) for the normal scalar product matrix-matrix division
			Mat4x4<type>& divide(const Mat4x4<type>& other) noexcept
			{
				x1 /= other.x1; x2 /= other.x2; x3 /= other.x3; x4 /= other.x4;
				y1 /= other.y1; y2 /= other.y2; y3 /= other.y3; y4 /= other.y4;
				z1 /= other.z1; z2 /= other.z2; z3 /= other.z3; z4 /= other.z4;
				w1 /= other.w1; w2 /= other.w2; w3 /= other.w3; w4 /= other.w4;
				return *this;
			}
			//add another Mat2x2 to this 
			Mat4x4<type>& add(const Mat2x2<type>& other) noexcept;
			//add another Mat2x3 to this 
			Mat4x4<type>& add(const Mat2x3<type>& other) noexcept;
			//add another Mat2x4 to this 
			Mat4x4<type>& add(const Mat2x4<type>& other) noexcept;
			//add another Mat3x2 to this 
			Mat4x4<type>& add(const Mat3x2<type>& other) noexcept;
			//add another Mat3x3 to this 
			Mat4x4<type>& add(const Mat3x3<type>& other) noexcept;
			//add another Mat3x4 to this 
			Mat4x4<type>& add(const Mat3x4<type>& other) noexcept;
			//add another Mat4x2 to this 
			Mat4x4<type>& add(const Mat4x2<type>& other) noexcept;
			//add another Mat4x3 to this 
			Mat4x4<type>& add(const Mat4x3<type>& other) noexcept;
			///hier für multiply alle anderen nehmen, muss aber nicht bei den operatoren wegen mathe spalten zeilen regel und bei operatoren ist normales mat mat mult | zu operatoren dann like skalarproduct hinschreiben | auch natürlich für divide/add/etc




		public:
			/*multiply another matrix to this matrix | scalar product matrix-matrix multiplication, not elementwise multiplication | use the multiply method for the elementwise multiplication | DO NOT MULTIPLY A MATRIX WITH ITSELF, IT WILL DESTROY THE MATRIX, use the square method instead
			this matrix is the right side matrix in the multiplication and this(right side matrix) will be modified by the multiplication | so this = other*this;
			matrix multiplication is not commutative: a*b is not equal to b*a | but matrix multiplication is associative: (a*b)*c is equal to a*(b*c) | also (a+b) * c is equal to a*c + b*c and a * (b+c) is equal to a*b + a*c
			the order of matrix multiplication is important because its not commutative, so the left matrix is always multiplied/applied to the right matrix and if you apply more matrices to a vector, the most right matrix is always first multiplied to the vector and you should read the multiplication from right to left, because all the left matrices affect all the right matrices
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			you can also do first matrix = scaling; then matrix*=rotation; and then matrix*=translation; because the operator*= always multiplies the right matrix of the assignment to the left matrix(this) and therefor the order is correct: first scaling, then rotation and then translation | important: the left matrix of the assignment with *=(the this object) is logicly the right side matrix of the multiplication 
			you can only multiply two matrices if the number of columns on the left side matrix is equal to the number of rows on the right side matrix | mat(m,n) * mat(i,j) only if n is equal to i
			the resulting matrix has the dimension(n,m) with the number of rows of the left side matrix(n) and the number of columns of the right side matrix(m) */
			Mat4x4<type>& operator*=(const Mat4x4<type>& left) noexcept
			{
				type temp1 = left.x1 * x1 + left.x2 * y1 + left.x3 * z1 + left.x4 * w1;//new x1: first row of left mat times first column of right mat
				type temp2 = left.y1 * x1 + left.y2 * y1 + left.y3 * z1 + left.y4 * w1;//new y1: second row of left mat times first column of right mat   
				type temp3 = left.z1 * x1 + left.z2 * y1 + left.z3 * z1 + left.z4 * w1;//new z1: third row of left mat times first column of right mat   
				w1 = left.w1 * x1 + left.w2 * y1 + left.w3 * z1 + left.w4 * w1;//new w1: fourth row of left mat times first column of right mat   
				x1 = temp1; y1 = temp2; z1 = temp3;

				temp1 = left.x1 * x2 + left.x2 * y2 + left.x3 * z2 + left.x4 * w2;//new x2: first row of left mat times second column of right mat
				temp2 = left.y1 * x2 + left.y2 * y2 + left.y3 * z2 + left.y4 * w2;//new y2: second row of left mat times second column of right mat   
				temp3 = left.z1 * x2 + left.z2 * y2 + left.z3 * z2 + left.z4 * w2;//new z2: third row of left mat times second column of right mat   
				w2 = left.w1 * x2 + left.w2 * y2 + left.w3 * z2 + left.w4 * w2;//new w2: fourth row of left mat times second column of right mat   
				x2 = temp1; y2 = temp2; z2 = temp3;

				temp1 = left.x1 * x3 + left.x2 * y3 + left.x3 * z3 + left.x4 * w3;//new x3: first row of left mat times third column of right mat
				temp2 = left.y1 * x3 + left.y2 * y3 + left.y3 * z3 + left.y4 * w3;//new y3: second row of left mat times third column of right mat   
				temp3 = left.z1 * x3 + left.z2 * y3 + left.z3 * z3 + left.z4 * w3;//new z3: third row of left mat times third column of right mat   
				w3 = left.w1 * x3 + left.w2 * y3 + left.w3 * z3 + left.w4 * w3;//new w3: fourth row of left mat times third column of right mat   
				x3 = temp1; y3 = temp2; z3 = temp3;

				temp1 = left.x1 * x4 + left.x2 * y4 + left.x3 * z4 + left.x4 * w4;//new x4: first row of left mat times fourth column of right mat
				temp2 = left.y1 * x4 + left.y2 * y4 + left.y3 * z4 + left.y4 * w4;//new y4: second row of left mat times fourth column of right mat  
				temp3 = left.z1 * x4 + left.z2 * y4 + left.z3 * z4 + left.z4 * w4;//new z4: third row of left mat times fourth column of right mat   
				w4 = left.w1 * x4 + left.w2 * y4 + left.w3 * z4 + left.w4 * w4;//new w4: fourth row of left mat times fourth column of right mat   
				x4 = temp1; y4 = temp2; z4 = temp3;
				return *this;
			}


			/*divivde another mat from this | scalar product matrix-matrix division, not elementwise division | use divide method for the elementwise division |DO NOT DIVIDE A MATRIX BY ITSELF, IT WILL DESTROY THE MATRIX and the result would be the identity matrix, so its pointless
			this matrix is the right side matrix in the multiplication and this(right side matrix) will be modified by the multiplication | so this = (other^-1)*this;
			you can only multiply two matrices if the number of columns on the left side matrix is equal to the number of rows on the right side matrix | mat(m,n) * mat(i,j) only if n is equal to i
			the other matrix has to be a square matrix with the same amount of rows and columns | dividing another matrix from this matrix is the same as multiply the inverse of the other matrix to this matrix */
			Mat4x4<type>& operator/=(const Mat4x4<type>& other) noexcept
			{
				return this->operator*=(other.inverse());
				/// /= ist einfach a/b =  a * b hoch -1 ??? | bei operatoren auch elementwise dinger für alle anderen matrix dimensionen machen, ausser halt bei /= *= * und / die anderen für nicht alle anderen dimensionen, sondern nur wenn zeilen/spalten passt
				///WICHTIG beim division operator/ wahrscheinlich reihenfolge anders als bei multiplication machen, da es logisch ist, eine matrix wird durch eine andere geteilt 1/2 und 1 wird verändert | aber eine matrix wird auf eine andere drauf multipliziert 1*2 und 2 wird verändert | WICHTIG DAZU KOMMENTIEREN UND SO MACHEN IM / OPERATOR
			}///ggf bei manchen methoden die kommentare genauer machen und auch die rechenschritte ins kommentar rein schreiben, oder erklären









		public:
			/*multiply a lvalue matrix to another lvalue matrix | scalar product matrix-matrix multiplication, not elementwise multiplication | use the multiply method for the elementwise multiplication | DO NOT MULTIPLY A MATRIX WITH ITSELF, IT WILL DESTROY THE MATRIX, use the square method instead
			the left matrix is multiplied to the right side matrix and a copy of the right side matrix is returned | result = left*right;
			matrix multiplication is not commutative: a*b is not equal to b*a | but matrix multiplication is associative: (a*b)*c is equal to a*(b*c) | also (a+b) * c is equal to a*c + b*c and a * (b+c) is equal to a*b + a*c
			the order of matrix multiplication is important because its not commutative, so the left matrix is always multiplied/applied to the right matrix and if you apply more matrices to a vector, the most right matrix is always first multiplied to the vector and you should read the multiplication from right to left, because all the left matrices affect all the right matrices
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			you can also do first matrix = scaling; then matrix*=rotation; and then matrix*=translation; because the operator*= always multiplies the right matrix of the assignment to the left matrix(this) and therefor the order is correct: first scaling, then rotation and then translation | important: the left matrix of the assignment with *=(the this object) is logicly the right side matrix of the multiplication
			you can only multiply two matrices if the number of columns on the left side matrix is equal to the number of rows on the right side matrix | mat(m,n) * mat(i,j) only if n is equal to i
			the resulting matrix has the dimension(n,m) with the number of rows of the left side matrix(n) and the number of columns of the right side matrix(m) */
			friend Mat4x4<type> operator*(const Mat4x4<type>& left, const Mat4x4<type>& right) noexcept
			{
				return Mat4x4<type>{
					left.x1 * right.x1 + left.x2 * right.y1 + left.x3 * right.z1 + left.x4 * right.w1,//new x1: first row of left mat times first column of right mat
					left.y1 * right.x1 + left.y2 * right.y1 + left.y3 * right.z1 + left.y4 * right.w1,//new y1: second row of left mat times first column of right mat   
					left.z1 * right.x1 + left.z2 * right.y1 + left.z3 * right.z1 + left.z4 * right.w1,//new z1: third row of left mat times first column of right mat   
					left.w1 * right.x1 + left.w2 * right.y1 + left.w3 * right.z1 + left.w4 * right.w1,//new w1: fourth row of left mat times first column of right mat

					left.x1 * right.x2 + left.x2 * right.y2 + left.x3 * right.z2 + left.x4 * right.w2,//new x2: first row of left mat times second column of right mat
					left.y1 * right.x2 + left.y2 * right.y2 + left.y3 * right.z2 + left.y4 * right.w2,//new y2: second row of left mat times second column of right mat   
					left.z1 * right.x2 + left.z2 * right.y2 + left.z3 * right.z2 + left.z4 * right.w2,//new z2: third row of left mat times second column of right mat   
					left.w1 * right.x2 + left.w2 * right.y2 + left.w3 * right.z2 + left.w4 * right.w2,//new w2: fourth row of left mat times second column of right mat   

					left.x1 * right.x3 + left.x2 * right.y3 + left.x3 * right.z3 + left.x4 * right.w3,//new x3: first row of left mat times third column of right mat
					left.y1 * right.x3 + left.y2 * right.y3 + left.y3 * right.z3 + left.y4 * right.w3,//new y3: second row of left mat times third column of right mat   
					left.z1 * right.x3 + left.z2 * right.y3 + left.z3 * right.z3 + left.z4 * right.w3,//new z3: third row of left mat times third column of right mat   
					left.w1 * right.x3 + left.w2 * right.y3 + left.w3 * right.z3 + left.w4 * right.w3,//new w3: fourth row of left mat times third column of right mat   

					left.x1 * right.x4 + left.x2 * right.y4 + left.x3 * right.z4 + left.x4 * right.w4,//new x4: first row of left mat times fourth column of right mat
					left.y1 * right.x4 + left.y2 * right.y4 + left.y3 * right.z4 + left.y4 * right.w4,//new y4: second row of left mat times fourth column of right mat  
					left.z1 * right.x4 + left.z2 * right.y4 + left.z3 * right.z4 + left.z4 * right.w4,//new z4: third row of left mat times fourth column of right mat   
					left.w1 * right.x4 + left.w2 * right.y4 + left.w3 * right.z4 + left.w4 * right.w4//new w4: fourth row of left mat times fourth column of right mat   
				};
			}

			/*multiply a rvalue matrix to another lvalue matrix | scalar product matrix-matrix multiplication, not elementwise multiplication | use the multiply method for the elementwise multiplication | DO NOT MULTIPLY A MATRIX WITH ITSELF, IT WILL DESTROY THE MATRIX, use the square method instead
			the left matrix is multiplied to the right side matrix and the left sside matrix is returned | result = left*right;
			matrix multiplication is not commutative: a*b is not equal to b*a | but matrix multiplication is associative: (a*b)*c is equal to a*(b*c) | also (a+b) * c is equal to a*c + b*c and a * (b+c) is equal to a*b + a*c
			the order of matrix multiplication is important because its not commutative, so the left matrix is always multiplied/applied to the right matrix and if you apply more matrices to a vector, the most right matrix is always first multiplied to the vector and you should read the multiplication from right to left, because all the left matrices affect all the right matrices
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			you can also do first matrix = scaling; then matrix*=rotation; and then matrix*=translation; because the operator*= always multiplies the right matrix of the assignment to the left matrix(this) and therefor the order is correct: first scaling, then rotation and then translation | important: the left matrix of the assignment with *=(the this object) is logicly the right side matrix of the multiplication 
			you can only multiply two matrices if the number of columns on the left side matrix is equal to the number of rows on the right side matrix | mat(m,n) * mat(i,j) only if n is equal to i
			the resulting matrix has the dimension(n,m) with the number of rows of the left side matrix(n) and the number of columns of the right side matrix(m) */
			friend Mat4x4<type>&& operator*(Mat4x4<type>&& left, const Mat4x4<type>& right) noexcept
			{
				type temp1 = left.x1 * right.x1 + left.x2 * right.y1 + left.x3 * right.z1 + left.x4 * right.w1;//new x1: first row of left mat times first column of right mat
				type temp2 = left.x1 * right.x2 + left.x2 * right.y2 + left.x3 * right.z2 + left.x4 * right.w2;//new x2: first row of left mat times second column of right mat
				type temp3 = left.x1 * right.x3 + left.x2 * right.y3 + left.x3 * right.z3 + left.x4 * right.w3;//new x3: first row of left mat times third column of right mat
				left.x4 = left.x1 * right.x4 + left.x2 * right.y4 + left.x3 * right.z4 + left.x4 * right.w4;//new x4: first row of left mat times fourth column of right mat
				left.x1 = temp1; left.x2 = temp2; left.x3 = temp3;

				temp1 = left.y1 * right.x1 + left.y2 * right.y1 + left.y3 * right.z1 + left.y4 * right.w1;//new y1: second row of left mat times first column of right mat   
				temp2 = left.y1 * right.x2 + left.y2 * right.y2 + left.y3 * right.z2 + left.y4 * right.w2;//new y2: second row of left mat times second column of right mat   
				temp3 = left.y1 * right.x3 + left.y2 * right.y3 + left.y3 * right.z3 + left.y4 * right.w3;//new y3: second row of left mat times third column of right mat   
				left.y4 = left.y1 * right.x4 + left.y2 * right.y4 + left.y3 * right.z4 + left.y4 * right.w4;//new y4: second row of left mat times fourth column of right mat  
				left.y1 = temp1; left.y2 = temp2; left.y3 = temp3;

				temp1 = left.z1 * right.x1 + left.z2 * right.y1 + left.z3 * right.z1 + left.z4 * right.w1;//new z1: third row of left mat times first column of right mat
				temp2 = left.z1 * right.x2 + left.z2 * right.y2 + left.z3 * right.z2 + left.z4 * right.w2;//new z2: third row of left mat times second column of right mat 
				temp3 = left.z1 * right.x3 + left.z2 * right.y3 + left.z3 * right.z3 + left.z4 * right.w3;//new z3: third row of left mat times third column of right mat   
				left.z4 = left.z1 * right.x4 + left.z2 * right.y4 + left.z3 * right.z4 + left.z4 * right.w4;//new z4: third row of left mat times fourth column of right mat   
				left.z1 = temp1; left.z2 = temp2; left.z3 = temp3;

				temp1 = left.w1 * right.x1 + left.w2 * right.y1 + left.w3 * right.z1 + left.w4 * right.w1;//new w1: fourth row of left mat times first column of right mat   
				temp2 = left.w1 * right.x2 + left.w2 * right.y2 + left.w3 * right.z2 + left.w4 * right.w2;//new w2: fourth row of left mat times second column of right mat   
				temp3 = left.w1 * right.x3 + left.w2 * right.y3 + left.w3 * right.z3 + left.w4 * right.w3;//new w3: fourth row of left mat times third column of right mat   
				left.w4 = left.w1 * right.x4 + left.w2 * right.y4 + left.w3 * right.z4 + left.w4 * right.w4;//new w4: fourth row of left mat times fourth column of right mat   
				left.w1 = temp1; left.w2 = temp2; left.w3 = temp3;
				return std::move(left);
			}

			/*multiply a lvalue matrix to another rvalue matrix | scalar product matrix-matrix multiplication, not elementwise multiplication | use the multiply method for the elementwise multiplication | DO NOT MULTIPLY A MATRIX WITH ITSELF, IT WILL DESTROY THE MATRIX, use the square method instead
			the left matrix is multiplied to the right side matrix and the right side matrix is returned | result = left*right;
			matrix multiplication is not commutative: a*b is not equal to b*a | but matrix multiplication is associative: (a*b)*c is equal to a*(b*c) | also (a+b) * c is equal to a*c + b*c and a * (b+c) is equal to a*b + a*c
			the order of matrix multiplication is important because its not commutative, so the left matrix is always multiplied/applied to the right matrix and if you apply more matrices to a vector, the most right matrix is always first multiplied to the vector and you should read the multiplication from right to left, because all the left matrices affect all the right matrices
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			you can also do first matrix = scaling; then matrix*=rotation; and then matrix*=translation; because the operator*= always multiplies the right matrix of the assignment to the left matrix(this) and therefor the order is correct: first scaling, then rotation and then translation | important: the left matrix of the assignment with *=(the this object) is logicly the right side matrix of the multiplication 
			you can only multiply two matrices if the number of columns on the left side matrix is equal to the number of rows on the right side matrix | mat(m,n) * mat(i,j) only if n is equal to i
			the resulting matrix has the dimension(n,m) with the number of rows of the left side matrix(n) and the number of columns of the right side matrix(m) */
			friend Mat4x4<type>&& operator*(const Mat4x4<type>& left, Mat4x4<type>&& right) noexcept
			{
				type temp1 = left.x1 * right.x1 + left.x2 * right.y1 + left.x3 * right.z1 + left.x4 * right.w1;//new x1: first row of left mat times first column of right mat
				type temp2 = left.y1 * right.x1 + left.y2 * right.y1 + left.y3 * right.z1 + left.y4 * right.w1;//new y1: second row of left mat times first column of right mat   
				type temp3 = left.z1 * right.x1 + left.z2 * right.y1 + left.z3 * right.z1 + left.z4 * right.w1;//new z1: third row of left mat times first column of right mat
				right.w1 = left.w1 * right.x1 + left.w2 * right.y1 + left.w3 * right.z1 + left.w4 * right.w1;//new w1: fourth row of left mat times first column of right mat   
				right.x1 = temp1; right.y1 = temp2; right.z1 = temp3;

				temp1 = left.x1 * right.x2 + left.x2 * right.y2 + left.x3 * right.z2 + left.x4 * right.w2;//new x2: first row of left mat times second column of right mat
				temp2 = left.y1 * right.x2 + left.y2 * right.y2 + left.y3 * right.z2 + left.y4 * right.w2;//new y2: second row of left mat times second column of right mat   
				temp3 = left.z1 * right.x2 + left.z2 * right.y2 + left.z3 * right.z2 + left.z4 * right.w2;//new z2: third row of left mat times second column of right mat 
				right.w2 = left.w1 * right.x2 + left.w2 * right.y2 + left.w3 * right.z2 + left.w4 * right.w2;//new w2: fourth row of left mat times second column of right mat   
				right.x2 = temp1; right.y2 = temp2; right.z2 = temp3;

				temp1 = left.x1 * right.x3 + left.x2 * right.y3 + left.x3 * right.z3 + left.x4 * right.w3;//new x3: first row of left mat times third column of right mat
				temp2 = left.y1 * right.x3 + left.y2 * right.y3 + left.y3 * right.z3 + left.y4 * right.w3;//new y3: second row of left mat times third column of right mat   
				temp3 = left.z1 * right.x3 + left.z2 * right.y3 + left.z3 * right.z3 + left.z4 * right.w3;//new z3: third row of left mat times third column of right mat   
				right.w3 = left.w1 * right.x3 + left.w2 * right.y3 + left.w3 * right.z3 + left.w4 * right.w3;//new w3: fourth row of left mat times third column of right mat   
				right.x3 = temp1; right.y3 = temp2; right.z3 = temp3;

				temp1 = left.x1 * right.x4 + left.x2 * right.y4 + left.x3 * right.z4 + left.x4 * right.w4;//new x4: first row of left mat times fourth column of right mat
				temp2 = left.y1 * right.x4 + left.y2 * right.y4 + left.y3 * right.z4 + left.y4 * right.w4;//new y4: second row of left mat times fourth column of right mat  
				temp3 = left.z1 * right.x4 + left.z2 * right.y4 + left.z3 * right.z4 + left.z4 * right.w4;//new z4: third row of left mat times fourth column of right mat   
				right.w4 = left.w1 * right.x4 + left.w2 * right.y4 + left.w3 * right.z4 + left.w4 * right.w4;//new w4: fourth row of left mat times fourth column of right mat   
				right.x4 = temp1; right.y4 = temp2; right.z4 = temp3;
				return std::move(right);
			}

			/*multiply a rvalue matrix to another rvalue matrix | scalar product matrix-matrix multiplication, not elementwise multiplication | use the multiply method for the elementwise multiplication | DO NOT MULTIPLY A MATRIX WITH ITSELF, IT WILL DESTROY THE MATRIX, use the square method instead
			the left matrix is multiplied to the right side matrix and the right side matrix is returned | result = left*right;
			matrix multiplication is not commutative: a*b is not equal to b*a | but matrix multiplication is associative: (a*b)*c is equal to a*(b*c) | also (a+b) * c is equal to a*c + b*c and a * (b+c) is equal to a*b + a*c
			the order of matrix multiplication is important because its not commutative, so the left matrix is always multiplied/applied to the right matrix and if you apply more matrices to a vector, the most right matrix is always first multiplied to the vector and you should read the multiplication from right to left, because all the left matrices affect all the right matrices
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			you can also do first matrix = scaling; then matrix*=rotation; and then matrix*=translation; because the operator*= always multiplies the right matrix of the assignment to the left matrix(this) and therefor the order is correct: first scaling, then rotation and then translation | important: the left matrix of the assignment with *=(the this object) is logicly the right side matrix of the multiplication 
			you can only multiply two matrices if the number of columns on the left side matrix is equal to the number of rows on the right side matrix | mat(m,n) * mat(i,j) only if n is equal to i
			the resulting matrix has the dimension(n,m) with the number of rows of the left side matrix(n) and the number of columns of the right side matrix(m) */
			friend Mat4x4<type>&& operator*(Mat4x4<type>&& left, Mat4x4<type>&& right) noexcept
			{
				type temp1 = left.x1 * right.x1 + left.x2 * right.y1 + left.x3 * right.z1 + left.x4 * right.w1;//new x1: first row of left mat times first column of right mat
				type temp2 = left.y1 * right.x1 + left.y2 * right.y1 + left.y3 * right.z1 + left.y4 * right.w1;//new y1: second row of left mat times first column of right mat   
				type temp3 = left.z1 * right.x1 + left.z2 * right.y1 + left.z3 * right.z1 + left.z4 * right.w1;//new z1: third row of left mat times first column of right mat
				right.w1 = left.w1 * right.x1 + left.w2 * right.y1 + left.w3 * right.z1 + left.w4 * right.w1;//new w1: fourth row of left mat times first column of right mat   
				right.x1 = temp1; right.y1 = temp2; right.z1 = temp3;

				temp1 = left.x1 * right.x2 + left.x2 * right.y2 + left.x3 * right.z2 + left.x4 * right.w2;//new x2: first row of left mat times second column of right mat
				temp2 = left.y1 * right.x2 + left.y2 * right.y2 + left.y3 * right.z2 + left.y4 * right.w2;//new y2: second row of left mat times second column of right mat   
				temp3 = left.z1 * right.x2 + left.z2 * right.y2 + left.z3 * right.z2 + left.z4 * right.w2;//new z2: third row of left mat times second column of right mat 
				right.w2 = left.w1 * right.x2 + left.w2 * right.y2 + left.w3 * right.z2 + left.w4 * right.w2;//new w2: fourth row of left mat times second column of right mat   
				right.x2 = temp1; right.y2 = temp2; right.z2 = temp3;

				temp1 = left.x1 * right.x3 + left.x2 * right.y3 + left.x3 * right.z3 + left.x4 * right.w3;//new x3: first row of left mat times third column of right mat
				temp2 = left.y1 * right.x3 + left.y2 * right.y3 + left.y3 * right.z3 + left.y4 * right.w3;//new y3: second row of left mat times third column of right mat   
				temp3 = left.z1 * right.x3 + left.z2 * right.y3 + left.z3 * right.z3 + left.z4 * right.w3;//new z3: third row of left mat times third column of right mat   
				right.w3 = left.w1 * right.x3 + left.w2 * right.y3 + left.w3 * right.z3 + left.w4 * right.w3;//new w3: fourth row of left mat times third column of right mat   
				right.x3 = temp1; right.y3 = temp2; right.z3 = temp3;

				temp1 = left.x1 * right.x4 + left.x2 * right.y4 + left.x3 * right.z4 + left.x4 * right.w4;//new x4: first row of left mat times fourth column of right mat
				temp2 = left.y1 * right.x4 + left.y2 * right.y4 + left.y3 * right.z4 + left.y4 * right.w4;//new y4: second row of left mat times fourth column of right mat  
				temp3 = left.z1 * right.x4 + left.z2 * right.y4 + left.z3 * right.z4 + left.z4 * right.w4;//new z4: third row of left mat times fourth column of right mat   
				right.w4 = left.w1 * right.x4 + left.w2 * right.y4 + left.w3 * right.z4 + left.w4 * right.w4;//new w4: fourth row of left mat times fourth column of right mat   
				right.x4 = temp1; right.y4 = temp2; right.z4 = temp3;
				return std::move(right);
			}

			/*multiply a matrix to a rvalue vector | scalar product matrix-matrix multiplication, not elementwise multiplication | use the multiply method for the elementwise multiplication | DO NOT MULTIPLY A MATRIX WITH ITSELF, IT WILL DESTROY THE MATRIX, use the square method instead
			the left matrix is multiplied to the right vector and the right side vector is returned | result = left*right; 
			with vectors its almost the same, its just a matrix with 1 column and the matrix transforms the vector with translation, rotation, scaling, etc | translation(x4/y4/z4 of Mat4x4) only works on Vec4 with w=1 and not w=0 | when called with Vec3 the w is always 1 | when called with Vec2 the z is always 0 and the w is always one
			matrix multiplication is not commutative: a*b is not equal to b*a | but matrix multiplication is associative: (a*b)*c is equal to a*(b*c) | also (a+b) * c is equal to a*c + b*c and a * (b+c) is equal to a*b + a*c
			the order of matrix multiplication is important because its not commutative, so the left matrix is always multiplied/applied to the right matrix and if you apply more matrices to a vector, the most right matrix is always first multiplied to the vector and you should read the multiplication from right to left, because all the left matrices affect all the right matrices
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			you can also do first matrix = scaling; then matrix*=rotation; and then matrix*=translation; because the operator*= always multiplies the right matrix of the assignment to the left matrix(this) and therefor the order is correct: first scaling, then rotation and then translation | important: the left matrix of the assignment with *=(the this object) is logicly the right side matrix of the multiplication 
			you can only multiply two matrices if the number of columns on the left side matrix is equal to the number of rows on the right side matrix | mat(m,n) * mat(i,j) only if n is equal to i
			the resulting matrix has the dimension(n,m) with the number of rows of the left side matrix(n) and the number of columns of the right side matrix(m) */
			friend Vec4<type>&& operator*(const Mat4x4<type>& left, Vec4<type>&& right) noexcept
			{
				type temp1 = left.x1 * right.x + left.x2 * right.y + left.x3 * right.z + left.x4 * right.w;//new x1: first row of left mat times first column of right mat
				type temp2 = left.y1 * right.x + left.y2 * right.y + left.y3 * right.z + left.y4 * right.w;//new y1: second row of left mat times first column of right mat   
				type temp3 = left.z1 * right.x + left.z2 * right.y + left.z3 * right.z + left.z4 * right.w;//new z1: third row of left mat times first column of right mat
				right.w = left.w1 * right.x + left.w2 * right.y + left.w3 * right.z + left.w4 * right.w;//new w1: fourth row of left mat times first column of right mat   
				right.x = temp1; right.y = temp2; right.z = temp3;
				return std::move(right);
			}

			/*multiply a matrix to a rvalue vector | scalar product matrix-matrix multiplication, not elementwise multiplication | use the multiply method for the elementwise multiplication | DO NOT MULTIPLY A MATRIX WITH ITSELF, IT WILL DESTROY THE MATRIX, use the square method instead
			the left matrix is multiplied to the right vector and a copy of the right side vector is returned | result = left*right;
			with vectors its almost the same, its just a matrix with 1 column and the matrix transforms the vector with translation, rotation, scaling, etc | translation(x4/y4/z4 of Mat4x4) only works on Vec4 with w=1 and not w=0 | when called with Vec3 the w is always 1 | when called with Vec2 the z is always 0 and the w is always one
			matrix multiplication is not commutative: a*b is not equal to b*a | but matrix multiplication is associative: (a*b)*c is equal to a*(b*c) | also (a+b) * c is equal to a*c + b*c and a * (b+c) is equal to a*b + a*c
			the order of matrix multiplication is important because its not commutative, so the left matrix is always multiplied/applied to the right matrix and if you apply more matrices to a vector, the most right matrix is always first multiplied to the vector and you should read the multiplication from right to left, because all the left matrices affect all the right matrices
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			you can also do first matrix = scaling; then matrix*=rotation; and then matrix*=translation; because the operator*= always multiplies the right matrix of the assignment to the left matrix(this) and therefor the order is correct: first scaling, then rotation and then translation | important: the left matrix of the assignment with *=(the this object) is logicly the right side matrix of the multiplication 
			you can only multiply two matrices if the number of columns on the left side matrix is equal to the number of rows on the right side matrix | mat(m,n) * mat(i,j) only if n is equal to i
			the resulting matrix has the dimension(n,m) with the number of rows of the left side matrix(n) and the number of columns of the right side matrix(m) */
			friend Vec4<type> operator*(const Mat4x4<type>& left, const Vec4<type>& right) noexcept
			{
				return Vec4<type>{
					left.x1 * right.x + left.x2 * right.y + left.x3 * right.z + left.x4 * right.w,//new x1: first row of left mat times first column of right mat
					left.y1 * right.x + left.y2 * right.y + left.y3 * right.z + left.y4 * right.w,//new y1: second row of left mat times first column of right mat   
					left.z1 * right.x + left.z2 * right.y + left.z3 * right.z + left.z4 * right.w,//new z1: third row of left mat times first column of right mat
					left.w1 * right.x + left.w2 * right.y + left.w3 * right.z + left.w4 * right.w//new w1: fourth row of left mat times first column of right mat   
				};
			}

			/*multiply a matrix to a rvalue vector | scalar product matrix-matrix multiplication, not elementwise multiplication | use the multiply method for the elementwise multiplication | DO NOT MULTIPLY A MATRIX WITH ITSELF, IT WILL DESTROY THE MATRIX, use the square method instead
			the left matrix is multiplied to the right vector and the right side vector is returned | result = left*right;
			with vectors its almost the same, its just a matrix with 1 column and the matrix transforms the vector with translation, rotation, scaling, etc | translation(x4/y4/z4 of Mat4x4) only works on Vec4 with w=1 and not w=0 | when called with Vec3 the w is always 1 | when called with Vec2 the z is always 0 and the w is always one
			matrix multiplication is not commutative: a*b is not equal to b*a | but matrix multiplication is associative: (a*b)*c is equal to a*(b*c) | also (a+b) * c is equal to a*c + b*c and a * (b+c) is equal to a*b + a*c
			the order of matrix multiplication is important because its not commutative, so the left matrix is always multiplied/applied to the right matrix and if you apply more matrices to a vector, the most right matrix is always first multiplied to the vector and you should read the multiplication from right to left, because all the left matrices affect all the right matrices
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			you can also do first matrix = scaling; then matrix*=rotation; and then matrix*=translation; because the operator*= always multiplies the right matrix of the assignment to the left matrix(this) and therefor the order is correct: first scaling, then rotation and then translation | important: the left matrix of the assignment with *=(the this object) is logicly the right side matrix of the multiplication 
			you can only multiply two matrices if the number of columns on the left side matrix is equal to the number of rows on the right side matrix | mat(m,n) * mat(i,j) only if n is equal to i
			the resulting matrix has the dimension(n,m) with the number of rows of the left side matrix(n) and the number of columns of the right side matrix(m) */
			friend Vec3<type>&& operator*(const Mat4x4<type>& left, Vec3<type>&& right) noexcept
			{
				type temp1 = left.x1 * right.x + left.x2 * right.y + left.x3 * right.z + left.x4;//new x1: first row of left mat times first column of right mat
				type temp2 = left.y1 * right.x + left.y2 * right.y + left.y3 * right.z + left.y4;//new y1: second row of left mat times first column of right mat   
				right.z = left.z1 * right.x + left.z2 * right.y + left.z3 * right.z + left.z4;//new z1: third row of left mat times first column of right mat
				right.x = temp1; right.y = temp2;
				return std::move(right);
			}

			/*multiply a matrix to a rvalue vector | scalar product matrix-matrix multiplication, not elementwise multiplication | use the multiply method for the elementwise multiplication | DO NOT MULTIPLY A MATRIX WITH ITSELF, IT WILL DESTROY THE MATRIX, use the square method instead
			the left matrix is multiplied to the right vector and a copy of the right side vector is returned | result = left*right;
			with vectors its almost the same, its just a matrix with 1 column and the matrix transforms the vector with translation, rotation, scaling, etc | translation(x4/y4/z4 of Mat4x4) only works on Vec4 with w=1 and not w=0 | when called with Vec3 the w is always 1 | when called with Vec2 the z is always 0 and the w is always one
			matrix multiplication is not commutative: a*b is not equal to b*a | but matrix multiplication is associative: (a*b)*c is equal to a*(b*c) | also (a+b) * c is equal to a*c + b*c and a * (b+c) is equal to a*b + a*c
			the order of matrix multiplication is important because its not commutative, so the left matrix is always multiplied/applied to the right matrix and if you apply more matrices to a vector, the most right matrix is always first multiplied to the vector and you should read the multiplication from right to left, because all the left matrices affect all the right matrices
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			you can also do first matrix = scaling; then matrix*=rotation; and then matrix*=translation; because the operator*= always multiplies the right matrix of the assignment to the left matrix(this) and therefor the order is correct: first scaling, then rotation and then translation | important: the left matrix of the assignment with *=(the this object) is logicly the right side matrix of the multiplication 
			you can only multiply two matrices if the number of columns on the left side matrix is equal to the number of rows on the right side matrix | mat(m,n) * mat(i,j) only if n is equal to i
			the resulting matrix has the dimension(n,m) with the number of rows of the left side matrix(n) and the number of columns of the right side matrix(m) */
			friend Vec3<type> operator*(const Mat4x4<type>& left, const Vec3<type>& right) noexcept
			{
				return Vec3<type>{
					left.x1 * right.x + left.x2 * right.y + left.x3 * right.z + left.x4,//new x1: first row of left mat times first column of right mat
					left.y1 * right.x + left.y2 * right.y + left.y3 * right.z + left.y4,//new y1: second row of left mat times first column of right mat   
					left.z1 * right.x + left.z2 * right.y + left.z3 * right.z + left.z4//new z1: third row of left mat times first column of right mat
				};
			}

			/*multiply a matrix to a rvalue vector | scalar product matrix-matrix multiplication, not elementwise multiplication | use the multiply method for the elementwise multiplication | DO NOT MULTIPLY A MATRIX WITH ITSELF, IT WILL DESTROY THE MATRIX, use the square method instead
			the left matrix is multiplied to the right vector and the right side vector is returned | result = left*right;
			with vectors its almost the same, its just a matrix with 1 column and the matrix transforms the vector with translation, rotation, scaling, etc | translation(x4/y4/z4 of Mat4x4) only works on Vec4 with w=1 and not w=0 | when called with Vec3 the w is always 1 | when called with Vec2 the z is always 0 and the w is always one
			matrix multiplication is not commutative: a*b is not equal to b*a | but matrix multiplication is associative: (a*b)*c is equal to a*(b*c) | also (a+b) * c is equal to a*c + b*c and a * (b+c) is equal to a*b + a*c
			the order of matrix multiplication is important because its not commutative, so the left matrix is always multiplied/applied to the right matrix and if you apply more matrices to a vector, the most right matrix is always first multiplied to the vector and you should read the multiplication from right to left, because all the left matrices affect all the right matrices
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			you can also do first matrix = scaling; then matrix*=rotation; and then matrix*=translation; because the operator*= always multiplies the right matrix of the assignment to the left matrix(this) and therefor the order is correct: first scaling, then rotation and then translation | important: the left matrix of the assignment with *=(the this object) is logicly the right side matrix of the multiplication 
			you can only multiply two matrices if the number of columns on the left side matrix is equal to the number of rows on the right side matrix | mat(m,n) * mat(i,j) only if n is equal to i
			the resulting matrix has the dimension(n,m) with the number of rows of the left side matrix(n) and the number of columns of the right side matrix(m) */
			friend Vec2<type>&& operator*(const Mat4x4<type>& left, Vec2<type>&& right) noexcept
			{
				type temp1 = left.x1 * right.x + left.x2 * right.y + left.x4;//new x1: first row of left mat times first column of right mat
				right.y = left.y1 * right.x + left.y2 * right.y + left.y4;//new y1: second row of left mat times first column of right mat   
				right.x = temp1;
				return std::move(right);
			}

			/*multiply a matrix to a lvalue vector | scalar product matrix-matrix multiplication, not elementwise multiplication | use the multiply method for the elementwise multiplication | DO NOT MULTIPLY A MATRIX WITH ITSELF, IT WILL DESTROY THE MATRIX, use the square method instead
			the left matrix is multiplied to the right vector and a copy of the right side vector is returned | result = left*right;
			with vectors its almost the same, its just a matrix with 1 column and the matrix transforms the vector with translation, rotation, scaling, etc | translation(x4/y4/z4 of Mat4x4) only works on Vec4 with w=1 and not w=0 | when called with Vec3 the w is always 1 | when called with Vec2 the z is always 0 and the w is always one
			matrix multiplication is not commutative: a*b is not equal to b*a | but matrix multiplication is associative: (a*b)*c is equal to a*(b*c) | also (a+b) * c is equal to a*c + b*c and a * (b+c) is equal to a*b + a*c
			the order of matrix multiplication is important because its not commutative, so the left matrix is always multiplied/applied to the right matrix and if you apply more matrices to a vector, the most right matrix is always first multiplied to the vector and you should read the multiplication from right to left, because all the left matrices affect all the right matrices
			it is advised to first do scaling, then rotations and then translations, otherwise they might negatively affect each other(for example first translate, then scale would also scale the translation) | the order here is from right to left(because the left matrix is multiplied to the right): translation * rotations * scale * vector; is the right way to first scale the vector and lastly apply the translation
			you can also do first matrix = scaling; then matrix*=rotation; and then matrix*=translation; because the operator*= always multiplies the right matrix of the assignment to the left matrix(this) and therefor the order is correct: first scaling, then rotation and then translation | important: the left matrix of the assignment with *=(the this object) is logicly the right side matrix of the multiplication 
			you can only multiply two matrices if the number of columns on the left side matrix is equal to the number of rows on the right side matrix | mat(m,n) * mat(i,j) only if n is equal to i
			the resulting matrix has the dimension(n,m) with the number of rows of the left side matrix(n) and the number of columns of the right side matrix(m) */
			friend Vec2<type> operator*(const Mat4x4<type>& left, const Vec2<type>& right) noexcept
			{
				return Vec2<type>{
					left.x1 * right.x + left.x2 * right.y + left.x4,//new x1: first row of left mat times first column of right mat
					left.y1 * right.x + left.y2 * right.y + left.y4//new y1: second row of left mat times first column of right mat   
				};
			}

			///hier vor noch matrix untereinander operatoren + - und genau wie * auch noch / für vektoren und die eigene matrix UND ANDEREN MATRITZEN MIT spalten/zeilen regel 
			///hier noch matrix mal vektor operator*  und unten den operator *= von vektor mit matrix definieren, der in vektoren deklariert wurde | die normalen elementwise operatoren + und - für alle anderen matritzen | bei * und / nur für alle matnx4 wobei dann halt immer die eigene matrix als rechte behandelt wird und es in den anderen genauso gemacht wird | natürlich bei allem auch für die += -= *= /= operatoren das gleiche machen

		public:
			//negate the mat
			friend Mat4x4<type> operator-(Mat4x4<type> mat) noexcept
			{
				mat.x1 = -mat.x1; mat.x2 = -mat.x2; mat.x3 = -mat.x3; mat.x4 = -mat.x4;
				mat.y1 = -mat.y1; mat.y2 = -mat.y2;	mat.y3 = -mat.y3; mat.y4 = -mat.y4;
				mat.z1 = -mat.z1; mat.z2 = -mat.z2;	mat.z3 = -mat.z3; mat.z4 = -mat.z4;
				mat.w1 = -mat.w1; mat.w2 = -mat.w2;	mat.w3 = -mat.w3; mat.w4 = -mat.w4;
				return mat;
			}
			/*const read-only row-major direct position access to the data in the matrix, so the positions are row per row:
			x1=0 x2=1 x3=2 x4=3
			y1=4 y2=5 y3=6 y4=7
			z1=8 z2=9 z3=10 z4=11
			w1=12 w2=13 w3=14 w4=15*/
			const type operator[](unsigned short position) const noexcept
			{
				return data[position];
			}
			/*row-major direct position access to the data in the matrix, so the positions are row per row:
			x1=0 x2=1 x3=2 x4=3
			y1=4 y2=5 y3=6 y4=7
			z1=8 z2=9 z3=10 z4=11
			w1=12 w2=13 w3=14 w4=15*/
			type& operator[](unsigned short position) noexcept
			{
				return data[position];
			}



		};

	}
}



namespace clockwork {
	namespace maths {




		using Mat4f = Mat4x4<float>;
	}
}