// Pour représenter une position (x,y)

#pragma once

struct Point {
    int x;
    int y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

