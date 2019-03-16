#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <exception>
#include "generator.hpp"

using namespace std;

//The class which represents student.
class student
{
private:
	//Parameters of a student.
	int id;
	double gpa;
	vector<char> options;
	char final_option;
	int priority;
	int unhappiness;	
	
	//Constats to avoid magic number.
	const double default_gpa{ 0.0 };
	const vector<char> default_options{};
	const int default_priority{ 2 };
	const int first{ 0 };
public:
	student();
	student(int id, double gpa, vector<char> options, int priority);
	student(const student& s); 
	~student() {}
	friend ostream& operator<<(ostream& os, const student& student);

	//Accessors.
	int get_id() const { return id; }
	double get_gpa() const { return gpa; }
	vector<char> get_options() const { return options;}
	char get_final_option() const { return final_option; }
	int get_priority() const { return priority; }
	int get_unhappiness() const { return unhappiness; }

	//Mutators.
	void set_id(int id) { this->id = id; }; //Error handling, if the id is less than static id, fail. 
	void set_gpa(double gpa) 
	{ 
		const double lower{ 50.0 };
		const double upper{ 100.0 };
		
		//Error handling.
		if (gpa < lower || gpa > upper) {
			throw invalid_argument("GPA should be 50.0 to 100.0");
		}
		
		student::gpa = gpa;
	}
	void set_options(vector<char> options) { this->options = options; }
	void set_final_option(char final_option) { this->final_option = final_option; }
	void set_priority(int priority) { this->priority = priority; }
	void set_unhappiness(int unhappiness) { this->unhappiness = unhappiness; }
};
