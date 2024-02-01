//
// Created by david.oh on 9/11/16.
//


// ------------------------------ includes ------------------------------
#include <iostream>
#include "PointSet.h"

// -------------------------- const definitions -------------------------

// dond make him more that requireSize-2
#define ONE_COORDINATE 1
#define TWO_COORDINATE 2

//can be anything
#define RAN_DIVISOR 10

//--------------------------------main------------------------------------


/**
 * @brief - main function that check if the overload of the operators in PointSet worg good.
 */
int main()
{
	int requireSize = 1550;

	PointSet *set0 = new PointSet;
	PointSet *set1 = new PointSet;
	PointSet *set2 = new PointSet;
	PointSet *set3 = new PointSet;
	PointSet *set4 = new PointSet;
	PointSet *set5 = new PointSet;

	//inserting points into set1 and set2
	for(int i = 0; i < requireSize; i++)
	{
		if(!(set1->add(Point(i + ONE_COORDINATE, i + TWO_COORDINATE)) ||
		   !(set2->add(Point(i - TWO_COORDINATE, i - ONE_COORDINATE)))))
		{
			std::cout << "ERROR: Fail test add" << std::endl;
			return EXIT_SUCCESS;
		}
	}

	//test operator '=='
	if(!(*set1 == *set1) || (*set1 == *set2))
	{
		std::cout << "ERROR: Fail test ==" << std::endl;
		return EXIT_SUCCESS;
	}

	//test operator '!='
	if(!(*set1 != *set2) || (*set1 != *set1))
	{
		std::cout << "ERROR: Fail test !=" << std::endl;
		return EXIT_SUCCESS;
	}

	//test operator '='
	set3->operator=(*set2);

	if(*set3 != *set2)
	{
		std::cout << "ERROR: Fail test of operator '='." << std::endl;
		return EXIT_SUCCESS;
	}

	//test num 1 of operator '&'
	*set3 = set1->operator&(*set2);

	if(*set3 != *set0)
	{
		std::cout << "ERROR: Fail test one of operator '&'." << std::endl;
		return EXIT_SUCCESS;
	}

	//inset to set3 two Point accord the ranIndex
	int ranIndex = requireSize / RAN_DIVISOR;
	set3->add(Point(ranIndex, ranIndex + ONE_COORDINATE));
	set3->add(Point(ranIndex + ONE_COORDINATE, ranIndex + TWO_COORDINATE));

	//test num 2 of operator '&'
	*set4 = set3->operator&(*set1);

	if(*set3 != *set4)
	{
		std::cout << "ERROR: Fail test two of operator '&'." << std::endl;
		return EXIT_SUCCESS;
	}

	//test num 1 of operator '-'
	*set5 = set4->operator-(*set2);

	if(*set5 != *set4)
	{
		std::cout << "ERROR: Fail test one of operator '-'." << std::endl;
		return EXIT_SUCCESS;
	}

	//test num 2 of operator '-'
	*set5 = set4->operator-(*set1);

	if(*set5 != *set0)
	{
		std::cout << "ERROR: Fail test two of operator '-'." << std::endl;
		return EXIT_SUCCESS;
	}

	delete(set0);
	delete(set1);
	delete(set2);
	delete(set3);
	delete(set4);
	delete(set5);
	std::cout << "NO FOUND ERROR!!" << std::endl;
	return EXIT_SUCCESS;
}