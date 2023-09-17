#pragma once
#include <cmath>

namespace clockwork {
	namespace maths {

		/*3.14159265359 as specified type*/
		template<typename type> constexpr type pi = 3.14159265359;
		extern double* sintable;
		extern double* costable;
		extern double* tantable;

		/*returns the absolut/non negative value of the type as a copy*/
		template<typename type> inline constexpr type abs(type value) noexcept
		{
			return value < 0 ? -value : value;
		}
		template<> constexpr inline unsigned char abs<unsigned char>(unsigned char value) noexcept
		{
			return value;
		}
		template<> constexpr inline unsigned short abs<unsigned short>(unsigned short value) noexcept
		{
			return value;
		}
		template<> constexpr inline unsigned int abs<unsigned int>(unsigned int value) noexcept
		{
			return value;
		}
		template<> constexpr inline unsigned long long abs<unsigned long long>(unsigned long long value) noexcept
		{
			return value;
		}

		/*returns a const reference to the smaller value | checks if the left value is smaller than the right*/
		template<typename type> inline const type& min(const type& value, const type& compare) noexcept
		{
			return value < compare ? value : compare;
		}
		/*returns a const reference to the bigger value | checks if the left value is bigger than the right*/
		template<typename type> inline const type& max(const type& value, const type& compare) noexcept
		{
			return value > compare ? value : compare;
		}
		/*round up a float/double value to the upper integer
		2.2 = 3.0 | -2.2 = -2.0*/
		template<typename type> inline constexpr type ceil(type value) noexcept
		{
			int ival = static_cast<int>( value );
			if ( value < 0 )
				return ival;
			else
			{
				if ( value == static_cast<float>( ival ) )
					return ival;
				else
					return ival + 1;
			}
		}
		/*round down a float/double value to the lower integer
		2.2 = 2.0 | -2.2 = -3.0*/
		template<typename type> inline constexpr type floor(type value) noexcept
		{
			if ( value < 0 )
			{
				int ival = static_cast<int>( value );
				if ( value == static_cast<float>( ival ) )
					return ival;
				else
					return ival - 1;
			}
			else
				return static_cast<int>( value );
		}
		/*breaks the value into an integral and a fractional part where the fractional part is returned and the integral part is stored in the integralStorage pointer
		both path will have the same sign as the value | both paths will be the same type as the value(so the storagePointer also has to be of the same type)
		value 3.102139 will return 0.102139 and the integralStorage will be 3.0*/
		template<typename type> inline constexpr int modf(type value, type* integralStorage) noexcept
		{
			return std::modf(value, integralStorage);
		}


		/*rounds a value of float, or double to the nearest given decimal value(always rounding halfway cases(.5) away from zeor regardless of the current rounding direction) | the template parameter decimal = 0 is for integer values 1, 1 is for one decimal 1.1, etc*/
		template<typename inputType, typename outputType, unsigned int decimal>
		inline constexpr outputType round(inputType value) noexcept
		{
			/*if constexpr ( decimal == 0 )//c++17
			{
				return static_cast<outputType>( std::round(value) );
			}
			else
			{*/
			inputType multi = pow(10, decimal);///muss noch in cpp überschrieben werden/definiert werden mal gucken, ob es geht mit mehreren templates, ansonsten decimal als parameter übergeben | aber wichtig nur bei float roundf aufrufen und bei double/long double roundd und bei anderen einfach value returnen
			std::round( value*multi ) / multi;///hiervor in den klammern das runden der ggf funktionen drüber muss auch integer ausgeben die rundfunktion, damit es geht | ggf auch die eigene round funktion benutzen aus notepod letztes new 
			return static_cast<outputType>( value );
			//}
		}


		/*converts an angle in degrees to an angle in radians | the type is the same, so float/double should be used*/
		template<typename type> inline constexpr type toRadians(type degrees) noexcept
		{
			return static_cast<type>( degrees * ( pi<type> / static_cast<type>( 180.0) ) );
		}
		/*converts an angle in radians to an angle in degrees | the type is the same, so float/double should be used*/
		template<typename type> inline constexpr type toDegrees(type radians) noexcept
		{
			return static_cast<type>( radians * ( static_cast<type>(180.0) / pi<type> ) );
		}
		/*returns the factorial for the given number number*number-1*number-2... */
		inline constexpr unsigned long long factorial(unsigned long long number) noexcept
		{
			return number > 1 ? number * factorial(number - 1) : 1;
		}


		///einfach hoch 2 AUCH WICHTIG, der inputtype ist der gleiche type, wie der outputtype dazuschreiben 
		template<typename type> inline constexpr type square(type val) noexcept
		{
			return val * val;
		}

		///Hoch irgendwas, hier noch alles kommentieren und ggf auch header/cpp trennen, sind aber bis jetzt nur einzeiler ! | auch hoch -count = 1/ val ^count 
		template<typename type> inline constexpr type pow(type val, int count) noexcept
		{
			if ( count > 0 )
				return val * pow(val, count - 1);
			else if ( count == 0 )
				return 1;
			else
				return static_cast<type>(1) / pow(val, -count);
		}

		///square root, AUCH NOCH unten nth root algorithm machen  | WICHTIG INPUTTYPE IST DER GLEICHE WIE OUTPUTTYPE BEI TEMPLATE FUNKTIONEN DAZU SCHREIBEN, damit die funktion nicht mit int aufgerufen wird und dann auch int ausgibt
		template<typename type> inline constexpr type sqrt(type val) noexcept
		{
			return std::sqrt(val);///ggf eigenen super effizienten genauen root algorithmus finden und hier einsetzten, genauso wie beim runden
		}

		//nur positive zahl | ist gleich val^(1/count) | WICHTIG WIE OBEN BEI SQRT
		template<typename type> inline constexpr type root(type val, unsigned int count) noexcept
		{
			return 0;
		}

		/*the fast unprecise way for integers between 0 and 360*/
		template<typename type = float> inline constexpr type sinD(unsigned int degrees) noexcept
		{
			degrees %= 360;
			return sintable[degrees];
		}
		template<typename type = float> inline constexpr type cosD(unsigned int degrees) noexcept
		{
			degrees %= 360;
			return costable[degrees];
		}
		template<typename type = float> inline constexpr type tanD(unsigned int degrees) noexcept
		{
			degrees %= 360;
			return tantable[degrees];
		}
		/*the slow precise way for doubles between 0 and 2*pi*/
		template<typename type> inline constexpr type sinR(type radians) noexcept
		{
			return std::sin(radians);
		}
		template<typename type> inline constexpr type cosR(type radians) noexcept
		{
			return std::cos(radians);
		}
		template<typename type> inline constexpr type tanR(type radians) noexcept
		{
			return std::tan(radians);
		}


		///hier noch acos asin atan ... und kommentieren mit hoch -1 wie das mit effizienz geregelt ist wann und warum init aufgerufen werden soll, etc
		/*the slow precise way for doubles between 0 and 2*pi*/
		template<typename type> inline constexpr type asinR(type radians) noexcept
		{
			return std::asin(radians);
		}
		template<typename type> inline constexpr type acosR(type radians) noexcept
		{
			return std::acos(radians);
		}
		template<typename type> inline constexpr type atanR(type radians) noexcept
		{
			return std::atan(radians);
		}
		template<typename type> inline constexpr type atan2R(type r1, type r2) noexcept
		{
			return std::atan2(r1, r2);
		}

		//auch noch machen für alle
		template<typename type> inline constexpr type log2(type value) noexcept
		{
			return 0;
		}













		/*has to be called before mathfunctions are used | will be called from the engine constructor*/
		inline void initMaths() noexcept
		{
			sintable = new double[360];
			costable = new double[360];
			tantable = new double[360];
			for ( unsigned int i = 0; i < 360; ++i )
			{
				sintable[i] = std::sin(toRadians<double>(i));
				costable[i] = std::cos(toRadians<double>(i));
				tantable[i] = std::tan(toRadians<double>(i));
			}
		}
		/*has to be called after mathfunctions are used | will be called from the engine destructor*/
		inline void destroyMaths() noexcept
		{
			delete[] sintable;
			delete[] costable;
			delete[] tantable;
		}

	}
}
