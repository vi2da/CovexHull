// Created by vi2da - 9/5/16.

#ifndef EX1_POINTSET_H
#define EX1_POINTSET_H

#include "Point.h"

/**
 * @brief - represent a matematicle set of Point.
 */
class PointSet
{
    int _size;
    int _numPlace;
    Point **_group;

    /**
     * @brief - double the set (to use if the set id full).
     * @return - true if success to double the group, else false,
     */
    bool doubleGroup();

    /**
     * @brief - check if the given Point exist in the set.
     * @param - toCheckIn: const reference to Point.
     * @return - true if find it in the set, else false,
     */
    bool contain(const Point& toCheckIn) const;

    /**
     * @brief - give the sgn of the sin of angle between (base,vec1) to (base,vec2).
     * @param - base: reference to Point.
     * @param - vec1: reference to Point.
     * @param - vec2: reference to Point.
     * @return - 0 if p, q and r are colinear, -1 if Clockwise, 1 if Counterclockwise
     */
    static int sinSgn(const Point& base, const Point& vec1, const Point& vec2);

    /**
     * @brief - compare by angle.
     * @param - statP: const pointer to Point.
     * @param - firstP: const pointer to Point.
     * @param - secP: const pointer to Point.
     * @return true if (statP,firstP) < (statP,secP)
     */
    static bool degCompar(const Point *statP, const Point *firstP, const Point *secP);

public:

    /**
     * @brief - default contractor.
     */
    PointSet();

    /**
     * @brief - copy contractor.
     * @param - toCopy: reference to PointSet.
     */
    PointSet(const PointSet& toCopy);

    /**
     * @brief - destractor.
     */
    ~PointSet();

    /**
     * @brief - that make from Point a string.
     * @return - string of this(the Point).
     */
    std::string toString() const;

    /**
     * @brief - add new Point to the set.
     * @param - toAdd: reference to Point.
     * @return - true if success, else false.
     */
    bool add(const Point& toAdd);

    /**
     * @brief - remove the Point from the set.
     * @param - toRemove: reference to Point.
     * @return - true if success, else false.
     */
    bool remove(const Point& toRemove);

    /**
     * @brief - to get the size of the set.
     * @return - the size of the set.
     */
    int size() const;

    /**
     * @brief - if the point is not contained not do enything else return the point and after him all the
     *          point in order of oposite clock.
     * @param - stationPoint: reference to Point.
     * @return - true if success, else false.
     */
    void degSortGroup(const Point stationPoint);

    /**
     * @brief - get the Point that in place index in the set.
     * @param - index: int to requier place of the search Point in set.
     * @return - const pointer to the Point, if the index is not legal return nullptr.
     */
    const Point* getInIndx(int index)const;

    /**
     * @brief - swap all the Fields between first and second.
     * @param - first: const refrens to PointSet.
     * @param - second: const refrens to PointSet.
     */
    friend void swap(PointSet& first, PointSet& second);

    /**
     * @brief - A function that overload the operator'=='.
     * @param - secPoint: const reference to Point.
     * @return - true if equals, else false.
     */
    bool operator==(const PointSet& secPoint) const;

    /**
     * @brief - A function that overload the operator'!='.
     * @param - secPoint: const reference to Point.
     * @return - true if not equals, else false.
     */
    bool operator!=(const PointSet& secPoint) const;

    /**
     * @brief - A function that overload the operator'-'.
     * @param - secPoint: const reference to Point.
     * @return - a PointSet.
     * @return - a PointSet.
     */
    PointSet operator-(const PointSet& secPoint) const;

    /**
     * @brief - A function that overload the operator'&'.
     * @param - secPoint: const reference to Point.
     * @return - a PointSet.
     */
    PointSet operator&(const PointSet& secPoint) const;

    /**
     * @brief - A function that overload the operator'='.
     * @param - secPoint: const reference to Point.
     * @return - reference to PointSet the one that was left that operator.
     */
    PointSet& operator=(PointSet secPoint);
};
#endif //EX1_POINTSET_H
