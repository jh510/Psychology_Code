// data.h
// Jamison Heard
// Psychology 6104
// 1/31/2017

#pragma once
#include <vector>

/*--------------------------------------------------*/
/*--- Class: Group                               ---*/
/*--- Contains Datset and Statistics for a Group ---*/
/*--------------------------------------------------*/
class Group {
private: 
	std::vector<float> dataset; // Group Data Set
	float mean,				// Mean of Group Data
		  variance,			// Variance of Group Data
		  std_deviation;	// Std Deviation of Group Data
	int size,	// Size of Group Data (n) 
		dof;	// Degrees of Freedom
	void calc_data_statistics(); // Calculates Mean, Variance, and Std. Deviation
public:
	Group(std::vector<float>); // Constructor
	~Group();	// Destructor
	/*--- Accessor Functions ---*/
	int   get_size() { return size; };
	float get_mean() { return mean; };
	float get_variance() { return variance; };
	float get_std_deviation() { return std_deviation; };
	int   get_dof() { return dof; };
	float get_element(int index) { return dataset[index]; };
};

/*---------------------------------------------*/
/*--- Class: Data                           ---*/
/*--- Contains Experiment Dataset           ---*/
/*--- Allows for F test or ANOVA on Dataset ---*/
/*---------------------------------------------*/
class Data
{
private:
	std::vector<Group> dataset; // Vector of Group Data
	float f_crit,	// Critcal Value for F Distribution
		inv_f_crit,	// Inverse Critical Value for F Distribution
		grand_mean, // Mean of Entire Dataset
		ssb,		// Sum of Squares Between Groups
		ssw,		// Sum of Squares Within Groups
		sst,		// Sum of Squares Total
		unadjusted_r2, // Unadjusted R^2 Value
		shrunken_r2,   // Shrunken R^2 Value
		adjusted_w2,	// Adjusted Omega Squared Value
		power;			// Power of a test
	int total_samples;	// Number of Samples in Dataset (N)
	void  calc_grand_mean(); // Calculates Grand Mean
	void  calc_sum_of_squares(); // Calculates Sum of Squares

public:
	Data(std::vector<Group>); // Constructor
	~Data();				  // Destructor
	/*--- Accessor Functions ---*/
	float get_grand_mean() { return grand_mean; };
	float get_f_crit() { return f_crit; };
	float get_unadjusted_R(){ return unadjusted_r2; };
	std::vector<Group> get_dataset() { return dataset; };
	float get_power() { return power; };
	/*--- Member Functions ---*/
	void calc_f_crit(int, int, float); // Calculate Critical Value for F Distribution
	void calc_f_power(int, int, float, float); // Calculate Power using Non-Central F Distribution
	void f_test(Group, Group);	// F Test on Specified Groups
	void f_test();	// F Test on First Two Groups in Dataset
	void anova();   // One-way ANOVA Test on Entire Dataset
};

