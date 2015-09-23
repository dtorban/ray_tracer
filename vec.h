#ifndef VEC_H_
#define VEC_H_

#include <iostream>
#include <cmath>

template <typename T>
class vec
{
public:
  virtual int getSize() const = 0;
  virtual T operator[](int index) const = 0;
  virtual T& operator[](int index) = 0;
  void operator=(const vec<T>& v) { copy(v); }
  void operator+=(const vec<T>& v) { add(v); }
  void operator-=(const vec<T>& v) { subtract(v); }
  void operator*=(const vec<T>& v) { mult(v); }
  void operator/=(const vec<T>& v) { div(v); }
  void operator=(const T& v) { copy(v); }
  void operator+=(const T& v) { add(v); }
  void operator-=(const T& v) { subtract(v); }
  void operator*=(const T& v) { mult(v); }
  void operator/=(const T& v) { div(v); }
  T dot(const vec& v) const;
  T length() const;

protected:
  void normalizeVec();
  void copy(const vec<T>& v);
  void copy(const T& v);
  void add(const vec<T>& v);
  void add(const T& val);
  void subtract(const vec<T>& v);
  void subtract(const T& val);
  void mult(const vec<T>& v);
  void mult(const T& val);
  void div(const vec<T>& v);
  void div(const T& val);
};

template <typename T>
class v2 : public vec<T>
{
public:
  union {T x, r;};
  union {T y, g;};

  v2() { x = 0; y = 0; }
  v2(T xval, T yval) { x = xval; y = yval; }
  v2(T a) { x = a; y = a; }
  v2(const v2<T>& v) { this->copy(v); }

  virtual T operator[](int index) const;
  virtual T& operator[](int index);
  virtual int getSize() const { return 2; }

  v2<T> normalize() { v2<T> vec(*this); vec.normalizeVec(); return vec; }
  v2<T> operator+(const v2<T>& v) { v2<T> vec(*this); vec+=v; return vec; }
  v2<T> operator-(const v2<T>& v) { v2<T> vec(*this); vec-=v; return vec; }
  v2<T> operator*(const v2<T>& v) { v2<T> vec(*this); vec*=v; return vec; }
  v2<T> operator/(const v2<T>& v) { v2<T> vec(*this); vec/=v; return vec; }
  v2<T> operator+(const T& v) { v2<T> vec(*this); vec+=v; return vec; }
  v2<T> operator-(const T& v) { v2<T> vec(*this); vec-=v; return vec; }
  v2<T> operator*(const T& v) { v2<T> vec(*this); vec*=v; return vec; }
  v2<T> operator/(const T& v) { v2<T> vec(*this); vec/=v; return vec; }
};

template <typename T>
class v3 : public v2<T>
{
public:
  union {T z, b;};

  v3() : v2<T>() { z = 0; }
  v3(T xval, T yval, T zval) : v2<T>(xval, yval) { z = zval; }
  v3(T a) : v2<T>(a) { z = a; }
  v3(const v2<T>& v, T zval) : v2<T>(v) { z = zval; }
  v3(const v3<T>& v) { this->copy(v); }

  virtual T operator[](int index) const { return index == 2 ? z : v2<T>::operator[](index); }
  virtual T& operator[](int index) { return index == 2 ? z : v2<T>::operator[](index); }
  virtual int getSize() const { return 3; }

  v3<T> normalize() const { v3<T> vec(*this); vec.normalizeVec(); return vec; }
  v3<T> operator+(const v3<T>& v) const { v3<T> vec(*this); vec+=v; return vec; }
  v3<T> operator-(const v3<T>& v) const { v3<T> vec(*this); vec-=v; return vec; }
  v3<T> operator*(const v3<T>& v) const { v3<T> vec(*this); vec*=v; return vec; }
  v3<T> operator/(const v3<T>& v) const { v3<T> vec(*this); vec/=v; return vec; }
  v3<T> operator+(const T& v) const { v3<T> vec(*this); vec+=v; return vec; }
  v3<T> operator-(const T& v) const { v3<T> vec(*this); vec-=v; return vec; }
  v3<T> operator*(const T& v) const { v3<T> vec(*this); vec*=v; return vec; }
  v3<T> operator/(const T& v) const { v3<T> vec(*this); vec/=v; return vec; }

  v3<T> cross(const v3<T>& v) const;
};

template <typename T>
class v4 : public v3<T>
{
public:
  union {T t, a;};

  v4() : v3<T>() { t = 0; }
  v4(T xval, T yval, T zval, T tval) : v3<T>(xval, yval, zval) { t = tval; }
  v4(T val) : v3<T>(val) { t = val; }
  v4(const v3<T>& v, T tval) : v3<T>(v) { t = tval; }
  v4(const v4<T>& v) { this->copy(v); }

  virtual T operator[](int index) const { return index == 3 ? t : v3<T>::operator[](index); }
  virtual T& operator[](int index) { return index == 3 ? t : v3<T>::operator[](index); }
  virtual int getSize() const { return 4; }

  v4<T> normalize() { v4<T> vec(*this); vec.normalizeVec(); return vec; }
  v4<T> operator+(const v4<T>& v) { v4<T> vec(*this); vec+=v; return vec; }
  v4<T> operator-(const v4<T>& v) { v4<T> vec(*this); vec-=v; return vec; }
  v4<T> operator*(const v4<T>& v) { v4<T> vec(*this); vec*=v; return vec; }
  v4<T> operator/(const v4<T>& v) { v4<T> vec(*this); vec/=v; return vec; }
  v4<T> operator+(const T& v) { v4<T> vec(*this); vec+=v; return vec; }
  v4<T> operator-(const T& v) { v4<T> vec(*this); vec-=v; return vec; }
  v4<T> operator*(const T& v) { v4<T> vec(*this); vec*=v; return vec; }
  v4<T> operator/(const T& v) { v4<T> vec(*this); vec/=v; return vec; }
};

typedef v2<float> vec2;
typedef v3<float> vec3;
typedef v4<float> vec4;

//-------------------------------------------------------------------

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const vec<T>& v)
{
  os << "(";
  for (int f = 0; f < v.getSize(); f++)
  {
    if (f > 0)
    {
      os << ", ";
    }
    os << v[f];
  }
  os << ")";
  return os;
}

template <typename T>
T vec<T>::dot(const vec& v) const
{
  T val = 0;
  for (int f = 0; f < std::min(getSize(),v.getSize()); f++)
  {
    val += (*this)[f]*v[f];
  }

  return val;
}

template <typename T>
T vec<T>::length() const
  {
    return sqrt(dot(*this));
  }

template <typename T>
  void vec<T>::normalizeVec()
  {
    T len = length();
    for (int f = 0; f < getSize(); f++)
    {
      (*this)[f] = ((*this)[f])/len;
    }
  }

template <typename T>
  void vec<T>::copy(const vec<T>& v)
  {
    for (int f = 0; f < std::min(getSize(),v.getSize()); f++)
    {
      (*this)[f] = v[f];
    }
  }

template <typename T>
  void vec<T>::copy(const T& v)
  {
    for (int f = 0; f < getSize(); f++)
    {
      (*this)[f] = v;
    }
  }

template <typename T>
  void vec<T>::add(const vec<T>& v)
  {
    for (int f = 0; f < std::min(getSize(),v.getSize()); f++)
    {
      (*this)[f] += v[f];
    }
  }

template <typename T>
  void vec<T>::add(const T& val)
  {
    for (int f = 0; f < getSize(); f++)
    {
      (*this)[f] += val;
    }
  }

template <typename T>
  void vec<T>::subtract(const vec<T>& v)
  {
    for (int f = 0; f < std::min(getSize(),v.getSize()); f++)
    {
      (*this)[f] -= v[f];
    }
  }

template <typename T>
  void vec<T>::subtract(const T& val)
  {
    for (int f = 0; f < getSize(); f++)
    {
      (*this)[f] -= val;
    }
  }

template <typename T>
  void vec<T>::mult(const vec<T>& v)
  {
    for (int f = 0; f < std::min(getSize(),v.getSize()); f++)
    {
      (*this)[f] *= v[f];
    }
  }

template <typename T>
  void vec<T>::mult(const T& val)
  {
    for (int f = 0; f < getSize(); f++)
    {
      (*this)[f] *= val;
    }
  }

template <typename T>
  void vec<T>::div(const vec<T>& v)
  {
    for (int f = 0; f < std::min(getSize(),v.getSize()); f++)
    {
      (*this)[f] /= v[f];
    }
  }

template <typename T>
  void vec<T>::div(const T& val)
  {
    for (int f = 0; f < getSize(); f++)
    {
      (*this)[f] /= val;
    }
  }

template <typename T>
T v2<T>::operator[](int index) const
  {
    switch(index)
    {
    case 0:
      return x;
    case 1:
      return y;
    }

    return 0;
  }

template <typename T>
T& v2<T>::operator[](int index)
  {
    switch(index)
    {
    case 0:
      return x;
    case 1:
      return y;
    }

    return x;
  }

template <typename T>
v3<T> v3<T>::cross(const v3<T>& v) const
{
  v3<T> c;
  c.x = this->y*v.z-this->z*v.y;
  c.y = this->x*v.z-this->z*v.x;
  c.z = this->x*v.y-this->y*v.x;
  return c;
}

#endif
