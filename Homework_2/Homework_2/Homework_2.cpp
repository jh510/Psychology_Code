// Homework_2.cpp : Defines the entry point for the console application.
//

#include "data.h"
#include <iostream>


int main()
{
	std::vector<float> cntrl = { 38,47,32,43,38,44,40,58 };
	std::vector<float> hr = { 38,33,35,32,24,18,33,25 };
	std::vector<float> no = { 26,33,32,40,28,49,37,33 };
	Group control(cntrl), three_hours(hr), no_sleep(no);
	std::vector<Group> p_1 = { control, three_hours, no_sleep };
	Data problem_1(p_1);
	problem_1.anova();
	
	float mean_A = 17.5,
		mean_B = 19,
		mean_C = 25,
		mean_D = 20.5,
	    sigma_y = 9,
	    n = 20,
	    j = 4;
	float grand_mean = (mean_A + mean_B + mean_C + mean_D) / j;
	std::cout << grand_mean << std::endl;
	float sigma_m = sqrt(pow(17.5 - grand_mean, 2) + pow(19 - grand_mean, 2) + pow(25 - grand_mean, 2) + pow(20.5 - grand_mean, 2));
	sigma_m = sigma_m / sqrt(j);
	std::cout << sigma_m << std::endl;
	float f = sigma_m / sigma_y;
	std::cout << f << std::endl;
	float lambda = f*f*n*j;
	problem_1.calc_f_power(j - 1, j * (n -1), .05, lambda);
	std::cout << problem_1.get_power() << std::endl;

	grand_mean = (10 * (mean_A + mean_B + mean_D) + 30 * mean_C) /  60;
	std::cout << grand_mean << std::endl;
	lambda = (10 * (pow(17.5 - grand_mean, 2) + pow(19 - grand_mean, 2) + pow(20.5 - grand_mean, 2)) + 30 * pow(25 - grand_mean, 2)) / (sigma_y*sigma_y);
	std::cout << lambda << std::endl;
	problem_1.calc_f_power(j - 1, j * (n - 1), .05, lambda);
	std::cout << problem_1.get_power() << std::endl;

	n = 20;
	f = 0.25;
	while (problem_1.get_power() < 0.80 && n < 100) {
		n++;
		lambda = f*f*n*j;
		problem_1.calc_f_power(j - 1, j * (n - 1), .05, lambda);
	}
	std::cout << problem_1.get_power() << std::endl;
	std::cout << n << std::endl;
    return 0;
}

