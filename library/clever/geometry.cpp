#include <algorithm>
#define _USE_MATH_DEFINES
#include <cmath>




// structs
typedef struct Point
{
	double x, y;
} Vector;

struct Triangle
{
	Point a, b, c;
};

struct Circle
{
	Point c;
	double r;
};





// objects
constexpr double const ALPHA = 0.0000000001f;





// functions
	// Разность точек, вычтите из конца начала,
	// чтобы получить вектор
inline double todegree(double radian)
{
	return radian * 180 / M_PI;
}

inline double toradian(double degree)
{
	return degree * M_PI / 180;
}


inline Vector operator-(Point const &lhs, Point const &rhs)
{
	return Vector{ lhs.x-rhs.x, lhs.y-rhs.y };
}


	// скалярное произведение векторов
inline double operator*(Vector const &lhs, Vector const &rhs)
{
	return lhs.x*rhs.x + lhs.y*rhs.y;
}



	// Возвращает длинну вектора
inline double length(Vector const &v)
{
	return std::hypot(v.x, v.y);
}


	// Расстояние между точками
inline double distance(Point const &f, Point const &s)
{
	return std::hypot( s.x-f.x, s.y-f.y );
}


	// Возвращает синус угла(в радианах) между векторами
	// против часовой стрелки от первого к второму
inline double sin(Vector const &f, Vector const &s)
{
	double const flen = length(f), slen = length(s);
	if( std::fabs(flen) < ALPHA || std::fabs(slen) < ALPHA )
		return 0.0f;
	return 
		(f.x*s.y - s.x*f.y) /
		( flen * slen );
}

	// Возвращает угол(в радианах) между векторами
	// против часовой стрелки от первого к второму
inline double angle(Vector const &f, Vector const &s)
{
	return std::asin(
		sin(f, s)
	);
}


inline double wide_horizontal_angle(
	Vector const &v
)
{
	double const acos = std::acos(
		v.x / std::hypot(v.x, v.y)
	);

	if( !(v.y > -ALPHA) )
		return 2*M_PI - acos;
	return acos;
}



// Определяет с какой сторны находится точка
// p от прямой, определяющейся beg и end. Ориентация
// (право-лево) устанавливается с помощью вектора
// с началом beg и концом end.
// 1 - справа от прямой;
// -1 - слево от прямой;
// 0 - на прямой;
int define_position( 
	Point const &beg, 
	Point const &end,
	Point const &p
)
{
	double const angl = 
		angle( end - beg, p - beg );
	return fabs(angl) < ALPHA ?
		0 :
		( angl < ALPHA ? 1 : -1 );
}


// Определяет местоположение точки - находится ли
// она в полуплоскости созданной с помощью двух
// пересекающихся прямых с началами и концами
// в beg-fend и beg-send соответственно.
// Выбирается та полуплоскость, которая 
// включает точки beg, fend и send и угол
// между прямыми со стороны которой полуплоскости
// наименьший.
// 1 - полуплоскость строго включает точку;
// 0 - точка на границе полуплоскости;
// -1 - полуплоскость не включает точку.
int define_position(
	Point const &beg, 
	Point const &fend, Point const &send,
	Point const &p
)
{
	Point const mid{
		(fend.x + send.x) / 2.0f,
		(fend.y + send.y) / 2.0f
	};

	int const
		fp = define_position( beg, fend, p ),
		sp = define_position( beg, send, p ),
		midfp = define_position( beg, fend, mid ),
		midsp = define_position( beg, send, mid );

	if(fp == midfp)
	{
		if(sp == 0)
			return 0;
		if(sp == midsp)
			return 1;
		return -1;
	}
	if(fp == 0 && ( sp == midsp || sp == 0 ))
		return 0;
	return -1;
}


// Определяет местоположение точки относительно
// теругольника, заданным тремя точками.
// 1 - треугольник строго включает точку;
// 0 - точка находится на границе;
// -1 - точка находится вне треугольника.
int define_position(Triangle const &t, Point const &p)
{
	int const
		fres = define_position(t.a, t.b, t.c, p),
		sres = define_position(t.b, t.a, t.c, p);

	if(fres == -1 || sres == -1)
		return -1;
	if(fres == 0 || sres == 0)
		return 0;
	return 1;
}



// Определяет площадь пересечения кругов 
double define_intersects_area(Circle const &f, Circle const &s)
{
	double const a = distance(f.c, s.c);
	if( a >= f.r+s.r )
		return 0.0f;
	if(
		f.r+a <= s.r ||
		s.r+a <= f.r
	)
		return M_PI * pow( std::min(f.r, s.r), 2 );

	double const alpha = 
		2 * acos(
			( pow(f.r, 2) + pow(a, 2) - pow(s.r, 2) ) /
			( 2 * f.r * a )
		);
	double const beta =
		2 * acos(
			( pow(s.r, 2) + pow(a, 2) - pow(f.r, 2) ) /
			( 2 * s.r * a )
		);
	return 
		pow(f.r, 2)/2*(alpha - sin(alpha)) +
		pow(s.r, 2)/2*(beta - sin(beta));
}





// end
