// data.cpp
// Jamison Heard
// Psychology 6104
// 1/31/2017

/*---- Include Files ----*/
#include "data.h" // Class Header
#include <math.h> // Math Functions
#include <iostream> // I/O Support
#include <boost/math/distributions/fisher_f.hpp> // F distribution functions, i.e., calculate critical values
#include <boost/math/distributions/non_central_f.hpp>

/*---- Name Spaces ----*/
using namespace boost::math;
using namespace std;

/*---- Easy Table Formatting Function ----*/
template<typename T> void printElement(T t, const int& width)
{
	cout << left << setw(width) << setfill(' ') << t;
}


/*------------------------------------*/
/*--- Constructor for Class Group  ---*/
/*------------------------------------*/
Group::Group(std::vector<float> input)
{
	dataset = input; // Copy input into class member variable
	size = dataset.size();  // Determine size of dataset
	dof = size - 1;         // Calculate degrees of freedom
	calc_data_statistics(); // Calculate mean, variance, and standard deviation
}

/*------------------------------------*/
/*--- Destructor for Class Group   ---*/
/*------------------------------------*/

Group::~Group()
{
	
}

/*------------------------------------------*/
/*--- Class: Group                       ---*/
/*--- Calculates mean, variance, and std ---*/
/*------------------------------------------*/
void Group::calc_data_statistics() {
	float sum = 0; // dummy variable
	/*--- Calculate Mean ---*/
	for (int i = 0; i < size; i++) {
		sum += dataset[i];
	}
	mean = sum / size;
    sum = 0;
	/*--- Calculate Variance ---*/
	for (int i = 0; i < size; i++) {
		sum += pow(dataset[i] - mean, 2);
	}
	variance = sum / (size - 1);
	/*--- Calculate Standard Deviation ---*/
	std_deviation = sqrt(variance);
}



/*------------------------------------*/
/*--- Constructor for Class Data   ---*/
/*------------------------------------*/
Data::Data(std::vector<Group> input)
{
	dataset = input; // Copy dataset into member variable
	calc_grand_mean(); // Calculate grand mean
	
}

/*------------------------------------*/
/*--- Destructor for Class Data   ---*/
/*------------------------------------*/
Data::~Data()
{
}

/*------------------------------------------*/
/*--- Class: Data                        ---*/
/*--- Calculates Grand Mean of Dataset   ---*/
/*------------------------------------------*/
void Data::calc_grand_mean() {
	float sum = 0; // Dummy Variable
	total_samples = 0; // Reset Number of Samples to Zero
	/*--- Cycle through Groups ---*/
	/*--- Sum = Nj * Ybarj     ---*/
	for (int i = 0; i < dataset.size(); i++) {
		sum += dataset[i].get_size() * dataset[i].get_mean();
		total_samples += dataset[i].get_size();
	}
	/*--- Grand Mean = Sum / Number of total samples ---*/
	grand_mean = sum / (float)total_samples;
}


/*---------------------------------------------------------*/
/*--- Class: Data                                   -------*/
/*--- Calculates Critical Value of F Distribution   -------*/
/*--- Input: Dof Numerator, Dof Denomerator, Error Rate ---*/
/*---------------------------------------------------------*/
void Data::calc_f_crit(int dof_1, int dof_2, float alpha) {

	fisher_f dist(dof_1, dof_2);     // Create F Distribution
	fisher_f inv_dist(dof_2, dof_1); // Create Inverse F Distribution
	f_crit =  quantile(complement(dist, alpha)); // Calculate Critical Value
	inv_f_crit = quantile(complement(inv_dist, alpha));
	inv_f_crit = 1 / inv_f_crit;
}


/*---------------------------------------------------------*/
/*--- Class: Data                                   -------*/
/*--- Calculates Critical Value of F Distribution   -------*/
/*--- Input: Dof Numerator, Dof Denomerator, Error Rate ---*/
/*---------------------------------------------------------*/
void Data::calc_f_power(int dof_1, int dof_2, float alpha, float lambda) {
	fisher_f dist(dof_1, dof_2);     // Create F Distribution
	non_central_f non_dist(dof_1, dof_2, lambda);     // Create F Distribution
	f_crit = quantile(complement(dist, alpha)); // Calculate Critical Value
	power = 1 - cdf(non_dist, f_crit);
}

/*----------------------------------------------------*/
/*--- Class: Data                                  ---*/
/*--- F Test on first and second Group in Dataset  ---*/
/*----------------------------------------------------*/

void Data::f_test() {
	float f_value; // F Value
	const int element_size = 10; // Changes Cell Width in Table
	/*--- Calculate F Value and Critical Value ---*/
	/*--- Makes sure larger variance is on top ---*/
	if (dataset[0].get_variance() > dataset[1].get_variance()) {
		calc_f_crit(dataset[0].get_dof(), dataset[1].get_dof(), .025);
		f_value = dataset[0].get_variance() / dataset[1].get_variance();
	}
	else {
		calc_f_crit(dataset[1].get_dof(), dataset[0].get_dof(), .025);
		f_value = dataset[1].get_variance() / dataset[0].get_variance();
	}

	/*--- Calculate Confidence Intervals for Variance ---*/
	float high_confidence = f_value / f_crit;
	float low_confidence = f_value / inv_f_crit;

	/*--- Print Table ---*/
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
	high_confidence = sqrt(high_confidence); // Calculate Std. Deviation Confidence Intervals
	low_confidence = sqrt(low_confidence);
	printf("Confidence interval  = %f < Population Std Deviation < %f \n", high_confidence, low_confidence);
	printf("Conclusion:   ");

	/*--- Determine if Null Hypothesis is Rejected ---*/
	if (f_crit < f_value)
		printf("Null Hypothesis is Rejected \n");
	else
		printf("Null Hypothesis is Not Rejected \n");
	cout << "____________________________________\n\n";
}

/*----------------------------------------------------*/
/*--- Class: Data        Overloaded Function       ---*/
/*--- F test on specified groups                   ---*/
/*----------------------------------------------------*/
void Data::f_test(Group, Group) {

}

/*------------------------------------------------------------*/
/*--- Class: Data                                          ---*/
/*--- Calculate Sum of Squares Between, Within, and Total  ---*/
/*------------------------------------------------------------*/
void Data::calc_sum_of_squares() {
	ssb = 0; // Sum of Squares Between
	/*--- SSB = sum( Samples in Group * (Group Mean - Grand Mean)^2) ---*/
	for (int i = 0; i < dataset.size(); i++) {
		ssb += dataset[i].get_size() * pow(dataset[i].get_mean() - grand_mean,2);
	}
	ssw = 0; // Sum of Squares Within
	/*--- SSW = Sum(Sum((Sample in Group - Group Mean)^2))*/
	for (int i = 0; i < dataset.size(); i++) {
		for (int j = 0; j < dataset[i].get_size(); j++) {
			ssw += pow(dataset[i].get_element(j) - dataset[i].get_mean(), 2);
		}
	}
	/*--- SST = Sum of Squares Between + Sum of Squares Within ---*/
	sst = ssb + ssw; // Sum of Squares Total
}

/*-----------------------------------------------*/
/*--- Class: Data                             ---*/
/*--- One-Way ANOVA Test over Entire Dataset  ---*/
/*-----------------------------------------------*/
void Data::anova() {
	float  msb,     // Mean Squares Between
		   msw,     // Mean Squares Within
		   f_score; // F Score
	unsigned int df_between,  // Dof Between Groups
				 df_within,   // Dof Within Groups
				 df_total;    // Dof Total
	const int element_size = 17; // Table Cell Width Size
	/*--- Calculate Degrees of Freedom ---*/
	df_between = dataset.size() - 1; // J - 1
	df_within  = total_samples - dataset.size(); // N - J
	df_total = df_between + df_within;
	/*--- Calculate Sum of Squares ---*/
	calc_sum_of_squares();
	/*--- Calculate Mean Squares ---*/
	msb = ssb / df_between;
	msw = ssw / df_within;
	/*--- Calculate F Score ---*/
	f_score = msb / msw;
	/*--- Calculate Critical Value ---*/
	calc_f_crit(df_between, df_within, 0.05);
	/*--- Calculate Unadjusted R^2 ---*/
	unadjusted_r2 = ssb / sst;
	/*--- Calculate Shrunken R^2 ---*/
	shrunken_r2 = 1 - ((float)df_total / df_within * (1 - unadjusted_r2));
	/*--- Calculate Adjusted W^2 ---*/
	adjusted_w2 = (ssb - df_between*msw) /( sst + msw);
	/*--- Calculate Power ---*/
	calc_f_power(df_between, df_within, 0.05, 0.25*0.25*df_between*df_within);
	/*--- Print Source Table ---*/
	cout <<
		"____________________________________\n"
		"            ANOVA Test\n"
		"____________________________________\n\n";

	printElement("Source", element_size);
	printElement("DOF", element_size - 10);
	printElement("Sum of Squares", element_size);
	printElement("Mean Square", element_size);
	printElement("F Score", element_size);
	cout << endl;
	printElement("Between Groups", element_size);
	printElement(df_between, element_size - 10);
	printElement(ssb, element_size);
	printElement(msb, element_size);
	printElement(f_score, element_size);
	cout << endl;
	printElement("Within Groups", element_size);
	printElement(df_within, element_size - 10);
	printElement(ssw, element_size);
	printElement(msw, element_size);
	cout << endl;
	printElement("Total", element_size);
	printElement(df_total, element_size - 10);
	printElement(sst, element_size);
	cout << endl << endl;
	cout << "____________________________________\n\n";
	printf("F Crit value at p < .05 = %f \n", f_crit);
	printf("Unadjusted R^2 Value = %f \n", unadjusted_r2);
	printf("Shrunken R^2 Value = %f \n", shrunken_r2);
	printf("Adjusted W^2 Value = %f \n", adjusted_w2);
	printf("Power Value = %f \n", power);
	printf("Conclusion:   ");
	/*--- Determine To Reject or Accepet Null Hypothesis ---*/
	if (f_crit < f_score)
		printf("Null Hypothesis is Rejected \n");
	else
		printf("Null Hypothesis is Not Rejected \n");
	cout << "____________________________________\n\n";

}
