#pragma once
#include <vector>

class Group {
private: 
	std::vector<float> dataset;
	float mean, variance, std_deviation;
	int dof;
	void calc_mean();
	void calc_sample_variance();
public:
	Group(std::vector<float>);
	~Group();
	float get_mean() { return mean; };
	float get_variance() { return variance; };
	float get_std_deviation() { return std_deviation; };
	int   get_dof() { return dof; };

	
};


class Data
{
private:
	std::vector<Group> dataset;
	float f_crit, inv_f_crit;
public:
	Data(std::vector<Group>);
	~Data();
	void calc_f_crit(int, int, float);
	void f_test(Group, Group);
	void f_test();
	std::vector<Group> get_dataset() { return dataset; };
	
};

