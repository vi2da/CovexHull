// Created by vi2da - 9/5/16.

// ------------------------------ includes ------------------------------
#include <iostream>
#include <functional>
#include <algorithm>
#include <assert.h>

#include "PointSet.h"

// -------------------------- const definitions -------------------------

/**
 * @def FIRST_INDX 0
 * @brief the index of the first in array.
 */
#define FIRST_INDX 0

/**
 * @def COLINEAR 0
 * @brief the returning from the function orientation() to say that is colinear Point's.
 */
#define COLINEAR 0

/**
 * @def POSITIVE 1
 * @brief the returning from the function orientation().
 */
#define POSITIVE 1

/**
 * @def NEGATIVE -1
 * @brief the returning from the function orientation().
 */
#define NEGATIVE -1

/**
 * @def TO_FEW_POINT -1
 * @brief to return from runConvex if not enough Point.
 */
#define TO_FEW_POINT -1

/**
 * @def EMPTY 0
 * @brief size to empty group/stack.
 */
#define EMPTY 0

/**
 * @def MIN_FOR_CONVEX 4
 * @brief the min number of Point to .
 */
#define MIN_FOR_CONVEX 4

/**
 * @def EXEPT_LAST 1
 * @brief.
 */
#define EXEPT_LAST 1

/**
 * @def IN_TOP 1
 * @brief to get in from stack the Point in top take the num in place of the next free - 1.
 */
#define IN_TOP 1

/**
 * @def NEXT_IN_TOP 2
 * @briefto get in from stack the Point in next to top take the num in place of the next free - 2.
 */
#define NEXT_IN_TOP 2

// ------------------------------ functions/methods -----------------------------


/**
 * @brief - A function to compare if firstP < secP (Primary by x end if they have the same x scompar them by y).
 * @param - firstP: const reference to Point.
 * @param - secP: const reference to Point.
 * @return -  if firstP < secP return true, else false
 */
bool comparXY(const Point& firstP, const Point& secP)
{
    if(firstP.getX() != secP.getX())
    {
        return firstP.getX() < secP.getX();
    }
    return firstP.getY() < secP.getY();
}


/**
 * @brief - A function to compare if firstP < secP (Primary by y end if they have the same y scompar them by x).
 * @param - firstP: pointer to Point.
 * @param - secP: pointer to Point.
 * @return -  if firstP < secP return true, else false
 */
bool comparYX(const Point *firstP, const Point *secP)
{
    if(firstP->getY() != secP->getY())
    {
        return firstP->getY() < secP->getY();
    }
    return firstP->getX() < secP->getX();
}


/**
 * @brief - To find orientation of ordered triplet (p, q, r)
 * @param - base: reference to Point.
 * @param - vec1: reference to Point.
 * @param - vec2: reference to Point.
 * @return - 0 if p, q and r are colinear, -1 if Clockwise, 1 if Counterclockwise
 */
int orientation(const Point& base, const Point& vec1, const Point& vec2)
{
    assert((base != vec1) && (base != vec2) && (vec1 != vec2));

    int x1 = vec1.getX() - base.getX();
    int y1 = vec1.getY() - base.getY();
    int x2 = vec2.getX() - vec1.getX();
    int y2 = vec2.getY() - vec1.getY();

    int dotSgn = (x1 * y2) - (x2 * y1);
    return (dotSgn == COLINEAR) ? COLINEAR : ((dotSgn > COLINEAR) ? POSITIVE : NEGATIVE);
}


/**
 * @brief - this function get from the user a data and add this Point to toInsertData,
 *          and remember the minimal Point that he see in toBeMin.
 * @param - toInsertData: reference to PointSet to add him all the Point's .
 * @param - toBeMin: reference to Point.
 */
void getFromUser(PointSet& toInsetData, Point& toBeMin)
{
    int currX;
    int currY;
    char separrator;

    bool firstInsert = true;

    while(std::cin >> currX >> separrator >> currY) //!std::cin.eof()
    {
        Point toInsert = Point(currX, currY);
        if(firstInsert)
        {
            firstInsert = false;
            toBeMin = toInsert;
        }
        else if(comparYX(&toInsert, &toBeMin))
        {
            toBeMin = toInsert;
        }
        toInsetData.add(toInsert);
    }
}


/**
 * @brief - A function that take only the Point that is not coolinear to other in toEndale (and if we have a
 *          coolinear Point's we take only the extremity) and put them into witoutColinear.
 * @param - toEndale: reference to PointSet.
 * @param - witoutColinear: Pointer to Point.
 * @return -  the index of the next place in stack witoutColinear.
 */
int endalColinear(const PointSet& toEndale, Point *witoutColinear)
{
    int lastInStack = FIRST_INDX;
    int size = toEndale.size();

    witoutColinear[lastInStack] = *toEndale.getInIndx(lastInStack);
    lastInStack++;

    for(int i = 1; i < size; i++)
    {
        while(i < size - EXEPT_LAST &&
              orientation(*toEndale.getInIndx(FIRST_INDX), *toEndale.getInIndx(i), *toEndale.getInIndx(i + 1)) == 0)
        {
            i++;
        }
        witoutColinear[lastInStack] = *toEndale.getInIndx(i);
        lastInStack++;
    }
    return lastInStack;
}


/**
 * @brief - A function that run the algorithem on fromStack and put the legal Point's into toStack.
 * @param - fromStack: Pointer to Point.
 * @param - witoutColinear: Pointer to Point.
 * @param - lastInStack: the next place in stack fromStack.
 * @return -  the index of last in stack witoutColinear.
 */
int runConvex(const Point *fromStack, Point *toStack, int lastInStack)
{
    if(lastInStack < MIN_FOR_CONVEX)
    {
        return TO_FEW_POINT;
    }

    int lastResult = FIRST_INDX;

    toStack[lastResult] = fromStack[lastResult];
    lastResult++;

    toStack[lastResult] = fromStack[lastResult];
    lastResult++;

    toStack[lastResult] = fromStack[lastResult];
    lastResult++;

    for(int i = MIN_FOR_CONVEX - EXEPT_LAST; i < lastInStack; i++)
    {
        while(orientation(toStack[lastResult - IN_TOP], toStack[lastResult - NEXT_IN_TOP], fromStack[i]) >= COLINEAR)
        {
            lastResult--;
        }
        toStack[lastResult] = fromStack[i];
        lastResult++;
    }
    return lastResult;
}


/**
 * @brief - main function that run the program to find convex hull of a set of points.
 */
int main()
{
    PointSet myPointGroup = PointSet();
    Point currMinPoint;
    getFromUser(myPointGroup, currMinPoint);

    std::cout << "result\n";
    if(myPointGroup.size() == EMPTY)
    {
        return EXIT_SUCCESS;
    }

    myPointGroup.degSortGroup(currMinPoint);
    int size = myPointGroup.size();

    Point *myStack = new Point[size];
    int lastInStack = endalColinear(myPointGroup, myStack);

    Point *resultStack = new Point[lastInStack];
    int lastResult = runConvex(myStack, resultStack, lastInStack);

    if(lastResult == TO_FEW_POINT)
    {
        std::sort(myStack, myStack + lastInStack, comparXY);

        for(int i = 0; i < lastInStack; i++)
        {
            std::cout << myStack[i].toString() << std::endl;
        }
        delete [] myStack;
        delete [] resultStack;
        return EXIT_SUCCESS;
    }

    std::sort(resultStack, resultStack + lastResult, comparXY);

    for(int i = 0; i < lastResult; i++)
    {
        std::cout << resultStack[i].toString() << std::endl;
    }

    delete [] myStack;
    delete [] resultStack;
    return EXIT_SUCCESS;
}
