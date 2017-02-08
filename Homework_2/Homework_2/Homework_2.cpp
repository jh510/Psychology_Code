// Homework_2.cpp : Defines the entry point for the console application.
//

#include "data.h"
#include <iostream>


int main()
{
	printf("Starting Problem 1....\n");
	/*--- Set Up Data ---*/
	std::vector<float> cntrl = { 38,47,32,43,38,44,40,58 }; // Control Data Set
	std::vector<float> hr = { 38,33,35,32,24,18,33,25 };	// Three Hours of Sleep Data Set
	std::vector<float> no = { 26,33,32,40,28,49,37,33 };	// No Sleep Data Set
	/*--- Create Groups ---*/
	Group control(cntrl), three_hours(hr), no_sleep(no);
	/*--- Create Dataset ---*/
	std::vector<Group> p_1 = { control, three_hours, no_sleep };
	Data problem_1(p_1);
	/*--- Perform ANOVA ---*/
	problem_1.anova();
	
	printf("Starting Problem 2...\n");
	printf(" Part A. \n");
	/*--- Define Variables ---*/
	float mean_A = 17.5,	// Mean of Group A
		mean_B = 19,		// Mean of Group B
		mean_C = 25,		// Mean of Group C
		mean_D = 20.5,		// Mean of Group D
	    sigma_y = 9,		// Population Std. Deviation
	    n = 20,				// Number of Samples per Group (Equal n's Design)
	    j = 4;				// Number of Groups
	/*--- Calculate Grand Mean ---*/
	float grand_mean = (mean_A + mean_B + mean_C + mean_D) / j; 
	printf("Grand Mean = %f \n", grand_mean);
	/*--- Calculate Across Group Variance ---*/
	float sigma_m = sqrt(pow(17.5 - grand_mean, 2) + pow(19 - grand_mean, 2) + pow(25 - grand_mean, 2) + pow(20.5 - grand_mean, 2));
	sigma_m = sigma_m / sqrt(j);
	printf("Sigma M = %f \n", sigma_m);
	/*--- Calculate Cohen's F ---*/
	float f = sigma_m / sigma_y;
	printf("Cohen's F = %f \n", f);
	/*--- Calculate Non-Centrality Parameter ---*/
	float lambda = f*f*n*j;
	printf("Lambda = %f \n", lambda);
	/*--- Calculate Power using Class Member Function ---*/
	problem_1.calc_f_power(j - 1, j * (n -1), .05, lambda);
	printf("Power = %f \n", problem_1.get_power());

	/*--- Part B ---*/
	printf(" \n \n Part B. \n");
	/*--- Calculate New Grand Mean ---*/
	grand_mean = (10 * (mean_A + mean_B + mean_D) + 30 * mean_C) /  60;
	printf("Grand Mean = %f \n", grand_mean);
	/*--- Calculate Lambda ---*/
	lambda = (10 * (pow(17.5 - grand_mean, 2) + pow(19 - grand_mean, 2) + pow(20.5 - grand_mean, 2)) + 30 * pow(25 - grand_mean, 2)) / (sigma_y*sigma_y);
	printf("Lambda = %f \n", lambda);
	/*--- Calculate Power ---*/
	problem_1.calc_f_power(j - 1, j * (n - 1), .05, lambda);
	printf("Power = %f \n", problem_1.get_power());

	/*--- Part C ---*/
	printf(" \n \n Part C. \n");
	n = 20;		// Reset n
	f = 0.25;	// Medium Effect Size
	/*--- Cycle Through n's until Power >.80 ---*/
	while (problem_1.get_power() < 0.80 && n < 100) {
		n++;
		lambda = f*f*n*j;
		problem_1.calc_f_power(j - 1, j * (n - 1), .05, lambda);
	}
	/*--- Print Out Answers ---*/
	printf("Power of %f is at n = %f \n", problem_1.get_power(), n);

    return 0;
}

/*
void Data::calc_f_power(int dof_1, int dof_2, float alpha, float lambda) {
	fisher_f dist(dof_1, dof_2);     // Create F Distribution
	non_central_f non_dist(dof_1, dof_2, lambda);     // Create F Distribution
	f_crit = quantile(complement(dist, alpha)); // Calculate Critical Value
	power = 1 - cdf(non_dist, f_crit);
}
*/
