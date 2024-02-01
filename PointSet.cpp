// Created by vi2da - 9/5/16.

// ------------------------------ includes ------------------------------
#include <sstream>
#include <iostream>
#include <assert.h>
#include <functional>
#include <algorithm>

#include "PointSet.h"

// -------------------------- const definitions -------------------------

/**
 * @def EMPTY 0
 * @brief size for empty set.
 */
#define EMPTY 0

/**
 * @def START_SIZE 2
 * @brief default size to be the set size.
 */
#define START_SIZE 2

/**
 * @def DIFF_INDX 1
 * @brief.
 */
#define DIFF_INDX 1

/**
 * @def MULT_TWO 2
 * @brief.
 */
#define MULT_TWO 2

/**
 * @def MIN_POSITIVE 0
 * @brief the min positive int.
 */
#define MIN_POSITIVE 0

/**
 * @def COLINEAR 0
 * @brief the returning from the function sinSgn() to say that is colinear Point's..
 */
#define COLINEAR 0

/**
 * @def POSITIVE 1
 * @brief the returning from the function sinSgn().
 */
#define POSITIVE 1

/**
 * @def NEGATIVE -1
 * @brief the returning from the function sinSgn().
 */
#define NEGATIVE -1

// ------------------------------ functions/methods -----------------------------


/**
 * @brief - default contractor.
 */
PointSet::PointSet()
{
    _size = EMPTY;
    _numPlace = START_SIZE;
    _group = new Point*[START_SIZE];
}


/**
 * @brief - copy contractor.
 * @param - toCopy: reference to PointSet.
 */
PointSet::PointSet(const PointSet &toCopy)
{
    _size = toCopy._size;
    _numPlace = toCopy._numPlace;
    _group = new Point*[toCopy._numPlace];

    for(int i = 0; i < _size; i++)
    {
        _group[i] = new Point(*(toCopy._group[i]));
    }
}


/**
 * @brief - destractor.
 */
PointSet::~PointSet()
{
    for(int i = 0; i < _size; i++)
    {
        delete(_group[i]);
    }
    delete[] _group;
}


/**
 * @brief - check if the given Point exist in the set.
 * @param - toCheckIn: const reference to Point.
 * @return - true if find it in the set, else false,
 */
bool PointSet::contain(const Point &toCheckIn) const
{
    for(int i = 0; i < _size; i++)
    {
        if(*(_group[i]) == toCheckIn)
        {
            return true;
        }
    }
    return false;
}


/**
 * @brief - that make from Point a string.
 * @return - string of this(the Point).
 */
std::string PointSet::toString() const
{
    std::stringstream ss;

    for(int i = 0; i < _size; i++)
    {
        ss << _group[i]->toString() << std::endl;
    }
    std::string toReturn = ss.str();
    return toReturn;
}


/**
 * @brief - to get the size of the set.
 * @return - the size of the set.
 */
int PointSet::size() const
{
    return _size;
}


/**
 * @brief - double the set (to use if the set id full).
 * @return - true if success to double the group, else false,
 */
bool PointSet::doubleGroup()
{
    Point **newGroup = new Point*[_numPlace * MULT_TWO];

    for(int i = 0; i < _size; i++)
    {
        newGroup[i] = _group[i];
        _group[i] = nullptr;
    }
    delete[](_group);
    _group = newGroup;
    _numPlace *= MULT_TWO;
    return true;
}


/**
 * @brief - add new Point to the set.
 * @param - toAdd: reference to Point.
 * @return - true if success, else false.
 */
bool PointSet::add(const Point &toAdd)
{

    for(int i = 0; i < _size; i++)
    {

        if(*(_group[i]) == toAdd)
        {
            return false;
        }
    }
    if(_size >= _numPlace)
    {
        if (!PointSet::doubleGroup())
        {
            return false;
        }
    }

    _group[_size] = new Point(toAdd);

    if(_group[_size] != nullptr)
    {
        _size++;
        return true;
    }
    return false;
}


/**
 * @brief - remove the Point from the set.
 * @param - toRemove: reference to Point.
 * @return - true if success, else false.
 */
bool PointSet::remove(const Point& toRemove)
{
    if(_size == EMPTY)
    {
        return false;
    }

    if(*(_group[_size - DIFF_INDX]) == toRemove)
    {
        delete(_group[_size - DIFF_INDX]);
        _size--;
        return true;
    }
    for(int i = 0; i < _size; i++)
    {
        if(*(_group[i]) == toRemove)
        {
            delete(_group[i]);
            _group[i] = _group[_size - DIFF_INDX];
            _size--;
            return true;
        }
    }
    return false;
}


/**
 * @brief - A function that overload the operator'=='.
 * @param - secPoint: const reference to Point.
 * @return - true if equals, else false.
 */
bool PointSet::operator==(const PointSet& secPoint) const
{
    if(_size != secPoint._size)
    {
        return false;
    }

    for(int i = 0; i < _size; i++)
    {
        if(!contain(*(secPoint._group[i])))
        {
            return false;
        }
    }
    return true;
}


/**
 * @brief - A function that overload the operator'!='.
 * @param - secPoint: const reference to Point.
 * @return - true if not equals, else false.
 */
bool PointSet::operator!=(const PointSet& secPoint) const
{
    return !(*this == secPoint);
}


/**
 * @brief - A function that overload the operator'-'.
 * @param - secPoint: const reference to Point.
 * @return - a PointSet.
 * @return - a PointSet.
 */
PointSet PointSet::operator-(const PointSet& secPoint) const
{
    PointSet resault = PointSet(*this);
    for(int i = 0; i < secPoint._size; i++)
    {
        resault.remove(*(secPoint._group[i]));
    }
    return resault;
}


/**
 * @brief - A function that overload the operator'&'.
 * @param - secPoint: const reference to Point.
 * @return - a PointSet.
 */
PointSet PointSet::operator&(const PointSet &secPoint) const
{
    return *this -(*this - secPoint);
}


/**
 * @brief - A function that overload the operator'='.
 * @param - secPoint: const reference to Point.
 * @return - reference to PointSet the one that was left that operator.
 */
PointSet& PointSet::operator=(PointSet secPoint)
{
    if(*this == secPoint)
    {
        return *this;
    }

    swap(*this, secPoint);
    return *this;
}


/**
 * @brief - give the sgn of the sin of angle between (base,vec1) to (base,vec2).
 * @param - base: reference to Point.
 * @param - vec1: reference to Point.
 * @param - vec2: reference to Point.
 * @return - 0 if p, q and r are colinear, -1 if Clockwise, 1 if Counterclockwise
 */
int PointSet::sinSgn(const Point& base, const Point& vec1, const Point& vec2)
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
 * @brief - A utility function to return square of distance between start and end
 * @param - start: const refrens to Point.
 * @param - end: const refrens to Point.
 * @return - the square of distance between start and end
 */
int getSqrDist(const Point& start, const Point& end)
{
    return ((start.getX() - end.getX()) * (start.getX() - end.getX())) +
           ((start.getY() - end.getY()) * (start.getY() - end.getY()));
}


/**
 * @brief - compare by angle.
 * @param - statP: const pointer to Point.
 * @param - firstP: const pointer to Point.
 * @param - secP: const pointer to Point.
 * @return true if (statP,firstP) < (statP,secP)
 */
bool PointSet::degCompar(const Point *statP, const Point *firstP, const Point *secP)
{
    if(*firstP == *statP)
    {
        return true;
    }
    if(*secP == *statP)
    {
        return false;
    }
    if((firstP->getY() < statP->getY()) && (secP->getY() >= statP->getY()))
    {
        return false;
    }
    if((firstP->getY() >= statP->getY()) && (secP->getY() < statP->getY()))
    {
        return true;
    }

    int deg = sinSgn(*statP, *firstP, *secP);
    bool resault = (deg > MIN_POSITIVE);
    if(deg == MIN_POSITIVE)
    {
        resault = (getSqrDist(*statP, *firstP) < getSqrDist(*statP, *secP));
    }
    return resault;
}


/**
 * @brief - if the point is not contained not do enything else return the point and after him all the
 *          point in order of oposite clock.
 * @param - stationPoint: reference to Point.
 * @return - true if success, else false.
 */
void PointSet::degSortGroup(const Point stationPoint)
{
    using namespace std::placeholders;
    if(!contain(stationPoint))
    {
        return;
    }
    std::sort(_group, _group + _size , std::bind(PointSet::degCompar, &stationPoint, _1, _2));
}


/**
 * @brief - get the Point that in place index in the set.
 * @param - index: int to requier place of the search Point in set.
 * @return - const pointer to the Point, if the index is not legal return nullptr.
 */
const Point* PointSet::getInIndx(int index)const
{
    if((index < MIN_POSITIVE) || (index > _size))
    {
        return nullptr;
    }
    return _group[index];
}



/**
 * @brief - swap all the Fields between first and second.
 * @param - first: const refrens to PointSet.
 * @param - second: const refrens to PointSet.
 */
void swap(PointSet& first, PointSet& second)
{
    using std::swap;
    swap(first._size, second._size);
    swap(first._numPlace, second._numPlace);
    swap(first._group, second._group);
}
