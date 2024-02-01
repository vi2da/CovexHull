// Created by vi2da - 9/5/16.

#include <string>

#ifndef EX1_POINT_H
#define EX1_POINT_H

/**
 * @def DEFAULT_POINT 0
 * @brief to default contractor to value x, y.
 */
#define DEFAULT_POINT 0

/**
 * @brief - represent a Point.
 */
class Point
{
private:
    int _x;
    int _y;

public:

    /**
     * @brief - default contractor.
     */
    Point(): _x(DEFAULT_POINT), _y(DEFAULT_POINT){ };

    /**
     * @brief - copy contractor.
     * @param - x: int to be the new x value.
     * @param - y: int to be the new y value.
     */
    Point(int x, int y): _x(x), _y(y){ };

    /**
     * @brief - set cordinat x.
     * @param - x: int to be the new x value.
     */
    void setX(int x){ _x = x; };

    /**
     * @brief - set cordinat y.
     * @param - y: int to be the new y value.
     */
    void setY(int y){ _y = y; };

    /**
     * @brief - get cordinat x.
     * @return - x value;
     */
    int getX()const{ return _x; };

    /**
     * @brief - get cordinat y.
     * @return - y value;
     */
    int getY()const{ return _y; };

    /**
     * @brief - that make from Point a string.
     * @return - string of this(the Point).
     */
    std::string toString()const;

    /**
     * @brief - A function that overload the operator'=='.
     * @param - secPoint: const reference to Point.
     * @return - true if equals, else false.
     */
    bool operator==(const Point& secPoint) const;

    /**
     * @brief - A function that overload the operator'!='.
     * @param - secPoint: const reference to Point.
     * @return - true if not equals, else false.
     */
    bool operator!=(const Point& secPoint) const;
};

#endif //EX1_POINT_H
