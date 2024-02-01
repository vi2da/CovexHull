//
// Created by david.oh on 9/4/16.
//

// ------------------------------ includes ------------------------------
#include <sstream>
#include <iostream>
#include "Point.h"

// ------------------------------ functions/methods -----------------------------


/**
 * @brief - that make from Point a string.
 * @return - string of this(the Point).
 */
std::string Point::toString() const
{
    std::stringstream ss;
    ss << getX() << ","  << getY();
    std::string toReturn = ss.str();
    return toReturn;
}


/**
 * @brief - A function that overload the operator'=='.
 * @param - secPoint: const reference to Point.
 * @return - true if equals, else false.
 */
bool Point::operator==(const Point &secPoint) const
{
    return ((_x == secPoint._x) && (_y == secPoint._y));
}


/**
 * @brief - A function that overload the operator'!='.
 * @param - secPoint: const reference to Point.
 * @return - true if not equals, else false.
 */
bool Point::operator!=(const Point &secPoint) const
{
    return !(*this == secPoint);
}
