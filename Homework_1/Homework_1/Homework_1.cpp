// Homework_1.cpp 
// Jamison Heard
// Psychology 6104
// 1/31/2017


/*---- Include Files ----*/
#include <iostream> // I/O Instructions
#include "data.h"   // Group and Data Classes



int main()
{
	/*---- Problem 1 ----*/
	std::cout << "Starting Problem 1..." << std::endl;
	std::vector<float> un = {66, 61, 67, 60, 71, 63, 67, 66}; // Uninhibited Group Data
	std::vector<float> in = { 89, 78, 67, 86, 82, 66, 85, 79, 88, 79, 90, 64 }; // Inhibited Group Data
	Group uninhibited(un), inhibited(in); // Create Data Sets
	std::vector<Group> p1 = { uninhibited, inhibited }; // Combine Data Setys
	Data problem_1(p1); // Create Complete Data Set
	problem_1.f_test(); // Implement F Test on Variances 
						// H0: Variances are Equal
						// H1: Variances are not Equal


	/*----- Problem 2 ----*/
	std::cout << "__________________" << std::endl;
	std::cout << "Starting Problem 2..." << std::endl;
	std::vector<float> zol = { 9,11,5,12,15,14,13,12,7,6 };     // Zoloft Data Set
	std::vector<float> nal = { 15,16,12,12,18,19,23,20,13,17 }; // Naltrexone Data Set
	std::vector<float> val = { 9,11,12,5,13,15,11,8,6,9 };		// Valium Data Set
	Group Zoloft(zol), Naltrexone(nal), Valium(val);            // Create Data Groups
	std::vector<Group> p2 = { Zoloft, Naltrexone, Valium };     // Combine Groups into complete Dataset
	Data problem_2(p2);
	problem_2.anova();	// Implement ANOVA Test
						// H0: Variances are Equal
						// H1: Variances are not Equal
    return 0;
}

