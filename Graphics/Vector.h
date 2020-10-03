#pragma once

template <class T> class Vector
{
public:

	Vector(T x = 0, T y = 0);

	Vector<T> operator+(const Vector<T>& second) const;
	Vector<T>& operator+=(const Vector<T>& second);

	Vector<T> operator-(const Vector<T>& second) const;
	Vector<T>& operator-=(const Vector<T>& second);
	
	Vector<T> operator*(const Vector<T>& second) const;
	Vector<T>& operator*=(const Vector<T>& second);

	Vector<T> operator/(const Vector<T>& second) const;
	Vector<T>& operator/=(const Vector<T>& second);

	Vector<T> operator-() const;

public:

	T x;
	T y;
};

//======================================================================================================
template <class T> Vector<T>::Vector(T x, T y)
{
	this->x = x;
	this->y = y;
}
//======================================================================================================
template <class T> Vector<T> Vector<T>::operator+(const Vector<T>& second) const
{
	Vector<T> result(*this);
	return (result += second);
}
//======================================================================================================
template <class T> Vector<T>& Vector<T>::operator+=(const Vector<T>& second)
{
	x += second.x;
	y += second.y;
	return *this;
}
//======================================================================================================
template <class T> Vector<T> Vector<T>::operator-(const Vector<T>& second) const
{
	Vector<T> result(*this);
	return (result -= second);
}
//======================================================================================================
template <class T> Vector<T>& Vector<T>::operator-=(const Vector<T>& second)
{
	x -= second.x;
	y -= second.y;
	return *this;
}
//======================================================================================================
template <class T> Vector<T> Vector<T>::operator*(const Vector<T>& second) const
{
	Vector<T> result(*this);
	return (result *= second);
}
//======================================================================================================
template <class T> Vector<T>& Vector<T>::operator*=(const Vector<T>& second)
{
	x *= second.x;
	y *= second.y;
	return *this;
}
//======================================================================================================
template <class T> Vector<T> Vector<T>::operator/(const Vector<T>& second) const
{
	Vector<T> result(*this);
	return (result /= second);
}
//======================================================================================================
template <class T> Vector<T>& Vector<T>::operator/=(const Vector<T>& second)
{
	if (second != 0) x /= second;
	if (second != 0) y /= second;
	return *this;
}
//======================================================================================================
template <class T> Vector<T> Vector<T>::operator-() const
{
	Vector<T> result(-x, -y);
	if (result.x == -0) result.x = 0;
	if (result.y == -0) result.y = 0;
	return result;
}
