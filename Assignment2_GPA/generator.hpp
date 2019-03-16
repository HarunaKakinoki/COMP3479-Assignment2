#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

//A class which has several generator functions.(Singleton)
class generator
{
public:
	//Return instance of this class.
	//PRE: Generator class exists.
	//POST: Return instance.
	//RETURN: The instance of a generator class. 
	static generator& get_instance()
	{
		static generator instance; 
		return instance;
	}
private:
	generator() {}
	random_device rd;
	static int student_id;
	static int priority1;
	static int priority2;
public:
	generator(generator const&) = delete;
	void operator=(generator const&) = delete;
	int generate_id();
	double generate_gpa();
	vector<char> generate_options();
	int generate_priority();
};