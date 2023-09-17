#pragma once
#include <vector>
#include<iostream>
#include <sstream>
#include <cmath>
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

		/*matrices are defined as first row(--) then column(|) and to name elements in a matrix its the same, so x2 would be mat.at(1,2) | row-major layout in memory and in methods*/
		template<typename type>
		struct Mat2x4
		{

		public:
			/*first row(--), first column(|)
			ME x2 x3 x4
			y1 y2 y3 y4*/
			type x1;

			/*first row(--), second column(|)
			x1 ME x3 x4
			y1 y2 y3 y4*/
			type x2;

			/*first row(--), third column(|)
			x1 x2 ME x4
			y1 y2 y3 y4*/
			type x3;

			/*first row(--), fourth column(|)
			x1 x2 x3 ME
			y1 y2 y3 y4*/
			type x4;

			/*second row(--), first column(|)
			x1 x2 x3 x4
			ME y2 y3 y4*/
			type y1;

			/*second row(--), second column(|)
			x1 x2 x3 x4
			y1 ME y3 y4*/
			type y2;

			/*second row(--), third column(|)
			x1 x2 x3 x4
			y1 y2 ME y4*/
			type y3;

			/*second row(--), fourth column(|)
			x1 x2 x3 x4
			y1 y2 y3 ME*/
			type y4;

		public:
			/*seperate values constructor
			x1 x2 x3 x4
			y1 y2 y3 y4*/
			Mat2x4
			(
				type x1=0, type x2=0, type x3=0, type x4=0,
				type y1=0, type y2=0, type y3=0, type y4=0
			) noexcept
				:x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), x4(x4), y4(y4)
			{}


			/*returns an identity matrix | matrices or vectors multiplied by this do not change
			1 0 0 0
			0 1 0 0*/
			static Mat2x4<type> identity() noexcept
			{
				return Mat2x4<type> {
						1, 0, 0, 0,
						0, 1, 0, 0 };
			}
		};

	}
}