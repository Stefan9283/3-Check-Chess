#include "Vec2.h"

vec2::vec2(int x, int y) {
	this->x = x; this->y = y;
}

vec2 vec2::operator+(const vec2& v) {
	return vec2(x + v.x, y + v.y);
}

vec2 vec2::operator-(const vec2& v) {
	return vec2(x - v.x, y - v.y);
}

vec2 vec2::operator-() {
	return vec2(-x, -y);
}

bool vec2::operator==(const vec2& v) {
	return x == v.x && y == v.y;
}

float vec2::getDistanceTo(vec2 v) {
	return sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
}

std::string vec2::toString() {
    std::string s = "vec2(";
    s.append(std::to_string(x));
    s.append(", ");
    s.append(std::to_string(y));
    s.append(")");
    return s;
}
