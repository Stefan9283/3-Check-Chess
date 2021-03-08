#ifndef INC_3_CHECK_CHESS_VEC2_H
#define INC_3_CHECK_CHESS_VEC2_H

#include <cmath>
#include <string>

class vec2 {
public:
	int x, y;

	vec2() = default;

	vec2(int x, int y);

	vec2 operator+(const vec2& v);

	vec2 operator-(const vec2& v);

	vec2 operator-();

	bool operator==(const vec2& v);

	float getDistanceTo(vec2 v);

	std::string toString();
};

#endif //INC_3_CHECK_CHESS_VEC2_H