//#include "stdafx.h"
#include "data.h"
#include <math.h>
#include <iostream>
#include <boost/math/distributions/fisher_f.hpp>



#define nameWidth 6
#define numWidth  8
#define VNAME(x) #x

using namespace boost::math;
using namespace std;

template<typename T> void printElement(T t, const int& width)
{
	cout << left << setw(width) << setfill(' ') << t;
}

Group::Group(std::vector<float> input)
{
	dataset = input;
	dof = dataset.size() - 1;
	calc_mean();
	calc_sample_variance();
	std_deviation = sqrt(variance);
}

Group::~Group()
{
	
}

void Group::calc_mean() {
	float sum = 0.00;
	for (int i = 0; i < dataset.size(); i++) {
		sum += dataset[i];
	}
	mean = sum / dataset.size();
}

void Group::calc_sample_variance() {
	float sum = 0;
	for (int i = 0; i < dataset.size(); i++) {
		sum += pow(dataset[i] - mean,2);
	}
	variance = sum / (dataset.size() - 1);
}


Data::Data(std::vector<Group> input)
{
	dataset = input;
	
}


Data::~Data()
{
}

void Data::calc_f_crit(int dof_1, int dof_2, float alpha) {

	fisher_f dist(dof_1, dof_2);
	fisher_f inv_dist(dof_2, dof_1);
	f_crit =  quantile(complement(dist, alpha));
	inv_f_crit = quantile(complement(inv_dist, alpha));
	inv_f_crit = 1 / inv_f_crit;
}

void Data::f_test() {
	float f_value;
	const int element_size = 10;
	if (dataset[0].get_variance() > dataset[1].get_variance()) {
		calc_f_crit(dataset[0].get_dof(), dataset[1].get_dof(), .025);
		f_value = dataset[0].get_variance() / dataset[1].get_variance();
	}
	else {
		calc_f_crit(dataset[1].get_dof(), dataset[0].get_dof(), .025);
		f_value = dataset[1].get_variance() / dataset[0].get_variance();
	
	}

	float high_confidence = f_value / f_crit;
	float low_confidence = f_value / inv_f_crit;

	cout <<
		"____________________________________\n"
		"      F test for equal variance\n"
		"____________________________________\n\n";
	
	printElement("Group", element_size);
	printElement("N", element_size);
	printElement("DOF", element_size);
	printElement("Mean", element_size);
	printElement("Variance", element_size);
	cout << endl;
	printElement("One", element_size);
	printElement(dataset[0].get_dof() + 1, element_size);
	printElement(dataset[0].get_dof(), element_size);
	printElement(dataset[0].get_mean(), element_size);
	printElement(dataset[0].get_variance(), element_size);
	cout << endl;
	printElement("Two", element_size);
	printElement(dataset[1].get_dof() + 1, element_size);
	printElement(dataset[1].get_dof(), element_size);
	printElement(dataset[1].get_mean(), element_size);
	printElement(dataset[1].get_variance(), element_size);
	cout << endl << endl;
	cout << "____________________________________\n\n";
	printf("F Crit value at .975 = %f \n", f_crit);
	printf("Calculated F Value   = %f \n", f_value);
	printf("Confidence interval  = %f < Population Variance < %f \n", high_confidence, low_confidence);
	high_confidence = sqrt(high_confidence);
	low_confidence = sqrt(low_confidence);
	printf("Confidence interval  = %f < Population Std Deviation < %f \n", high_confidence, low_confidence);

	printf("Conclusion:   ");

	if (f_crit < f_value)
		printf("Null Hypothesis is Rejected \n");
	else
		printf("Null Hypothesis is Not Rejected \n");
	cout << "____________________________________\n\n";
}

void Data::f_test(Group, Group) {

}
