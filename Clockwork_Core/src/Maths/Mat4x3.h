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
		struct Mat4x3
		{

		public:
			/*first row(--), first column(|)
			ME x2 x3
			y1 y2 y3
			z1 z2 z3
			w1 w2 w3*/
			type x1;

			/*first row(--), second column(|)
			x1 ME x3
			y1 y2 y3
			z1 z2 z3
			w1 w2 w3*/
			type x2;

			/*first row(--), third column(|)
			x1 x2 ME
			y1 y2 y3
			z1 z2 z3
			w1 w2 w3*/
			type x3;

			/*second row(--), first column(|)
			x1 x2 x3
			ME y2 y3
			z1 z2 z3
			w1 w2 w3*/
			type y1;

			/*second row(--), second column(|)
			x1 x2 x3
			y1 ME y3
			z1 z2 z3
			w1 w2 w3*/
			type y2;

			/*second row(--), third column(|)
			x1 x2 x3
			y1 y2 ME
			z1 z2 z3
			w1 w2 w3*/
			type y3;

			/*third row(--), first column(|)
			x1 x2 x3
			y1 y2 y3
			ME z2 z3
			w1 w2 w3*/
			type z1;

			/*third row(--), second column(|)
			x1 x2 x3
			y1 y2 y3
			z1 ME z3
			w1 w2 w3*/
			type z2;

			/*third row(--), third column(|)
			x1 x2 x3
			y1 y2 y3
			z1 z2 ME
			w1 w2 w3*/
			type z3;

			/*fourth row(--), first column(|)
			x1 x2 x3
			y1 y2 y3
			z1 z2 z3
			ME w2 w3*/
			type w1;

			/*fourth row(--), second column(|)
			x1 x2 x3
			y1 y2 y3
			z1 z2 z3
			w1 ME w3*/
			type w2;

			/*fourth row(--), third column(|)
			x1 x2 x3
			y1 y2 y3
			z1 z2 z3
			w1 w2 ME*/
			type w3;

		public:
			/*seperate values constructor
			x1 x2 x3
			y1 y2 y3
			z1 z2 z3
			w1 w2 w3*/
			Mat4x3
			(
				type x1=0, type x2=0, type x3=0,
				type y1=0, type y2=0, type y3=0,
				type z1=0, type z2=0, type z3=0,
				type w1=0, type w2=0, type w3=0
			) noexcept
				:x1(x1), y1(y1), z1(z1), w1(w1), x2(x2), y2(y2), z2(z2), w2(w2), x3(x3), y3(y3), z3(z3), w3(w3)
			{}


			/*returns an identity matrix | matrices or vectors multiplied by this do not change
			1 0 0 
			0 1 0 
			0 0 1 
			0 0 0*/
			static Mat4x3<type> identity() noexcept
			{
				return Mat4x3<type> {
						1, 0, 0,
						0, 1, 0,
						0, 0, 1,
						0, 0, 0 };
			}
		};

	}
}