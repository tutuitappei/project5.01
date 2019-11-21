#pragma once

template<class T> class Vector2Template
{
public:
	Vector2Template();
	Vector2Template(T  x, T  y);
	~Vector2Template();
	T x;
	T y;

	//‘ã“ü‰‰Zq
	Vector2Template& operator = (const  Vector2Template<T>&Vec);

	//“Y‚¦š‰‰Zq
	T& operator [] (T i);

	//”äŠr‰‰Zq
	bool operator == (const  Vector2Template<T>&Vec)const;

	bool operator != (const  Vector2Template<T>&Vec)const;

	bool operator > (const  Vector2Template<T>&Vec)const;

	bool operator >= (const Vector2Template<T>&Vec)const;

	bool operator <(const  Vector2Template<T>&Vec)const;

	bool operator <= (const  Vector2Template<T>&Vec)const;

	//’P€‰‰Zq
	Vector2Template& operator+= (const  Vector2Template<T>&Vec);

	Vector2Template& operator-= (const  Vector2Template<T>&Vec);

	Vector2Template& operator*= (int k);

	Vector2Template& operator/= (int k);

	Vector2Template operator + () const;

	Vector2Template operator - () const;
};

using Vector2db = Vector2Template<double>;	//ƒ_ƒuƒ‹Œ^
using Vector2in = Vector2Template<int>;	//ƒCƒ“ƒgŒ^

//ÍŞ¸ÄÙ‚Ì‰‰Z

//Vector2 + Vector2
template<class T>
Vector2Template<T> operator + (const Vector2Template<T>& u, const Vector2Template<T>& v);

//Vector2 - Vector2
template<class T>
Vector2Template<T> operator - (const Vector2Template<T>& u, const Vector2Template<T>& v);

//Vector2 * Vector2
template<class T>
Vector2Template<T> operator * (const Vector2Template<T>& u, const Vector2Template<T>& v);

//Vector2 / Vector2
template<class T>
Vector2Template<T> operator / (const Vector2Template<T>& u, const Vector2Template<T>& v);

//Vector2 % Vector2
template<class T>
Vector2Template<T> operator % (const Vector2Template<T>& u, const Vector2Template<T>& v);

//Vector2 +@int
template<class T>
Vector2Template<T> operator + (const Vector2Template<T>& u, int a);

//Vector2 - int
template<class T>
Vector2Template<T> operator - (const Vector2Template<T>& u, int a);

//Vector2 * int
template<class T>
Vector2Template<T> operator * (const Vector2Template<T>& u, int a);

//int	  * vector2
template<class T>
Vector2Template<T> operator * (int a, const Vector2Template<T>& u);


//Vector2 / int
template<class T>
Vector2Template<T> operator / (const Vector2Template<T>& u, int a);


//Vector2 % int
template<class T>
Vector2Template<T> operator % (const Vector2Template<T>& u, int a);

#include "./details/Vector2.h"