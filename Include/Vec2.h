#ifndef INC_3_CHECK_CHESS_VEC2_H
#define INC_3_CHECK_CHESS_VEC2_H

#include <cmath>
#include <string>

template <class T>
class vec2 {
public:
	T x, y;

    vec2() {
        this->x = 0; this->y = 0;
    }
    vec2(T x, T y) {
        this->x = x; this->y = y;
    }

    vec2<T> operator/(float c) {
        return vec2<T>(x / c, y / c);
    }

    template <class S>
    vec2<T> operator*(S const &c) {
        return vec2<T>(x * c, y * c);
    }

    template <class S>
    vec2<T> operator*=(S const &c) {
        vec2<T> res = *this * c;
        x = res.x;
        y = res.y;
        return res;
    }

    template <class S>
    friend vec2<T> operator*(S const &c, const vec2<T>& v) {
        return vec2<T>(v.x * c, v.y * c);
    }

    vec2<T> operator+(const vec2<T>& v) {
        return vec2<T>(x + v.x, y + v.y);
    }

    vec2<T> operator-(const vec2<T>& v) {
        return vec2<T>(x - v.x, y - v.y);
    }
    vec2<T> operator-() {
        return vec2<T>(-x, -y);
    }

    bool operator==(const vec2<T>& v) {
        return x == v.x && y == v.y;
    }

    float getDistanceTo(vec2<T> v) {
        return sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
    }
    std::string toString() {
        std::string s = "vec2<T>(";
        s.append(std::to_string(x));
        s.append(", ");
        s.append(std::to_string(y));
        s.append(")");
        return s;
    }
};


#endif //INC_3_CHECK_CHESS_VEC2_H