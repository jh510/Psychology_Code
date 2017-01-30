// Homework_1.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include "data.h"



int main()
{
	std::vector<float> un = {66, 61, 67, 60, 71, 63, 67, 66};
	std::vector<float> in = { 89, 78, 67, 86, 82, 66, 85, 79, 88, 79, 90, 64 };
	Group uninhibited(un), inhibited(in);
	std::vector<Group> p1 = { uninhibited, inhibited };
	Data problem_1(p1);
	problem_1.f_test();
	
    return 0;
}

