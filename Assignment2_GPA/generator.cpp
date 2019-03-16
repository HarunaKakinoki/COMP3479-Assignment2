#include "generator.hpp"

//Initialize private static variables.
int generator::student_id = 0;
int generator::priority1 = 0;
int generator::priority2 = 0;

//Generate unique id(Sequencial).
//PRE: None.
//POST: Return unique id.
//RETURN: Unique id of type int.
int generator::generate_id()
{
	return student_id++;
}

//Generate gpa within 5.0 to 9.0.
//PRE: Lower bound & Upper bound are indicated.
//POST: Return gpa within a proper range.
//RETURN: A gpa of type double.
double generator::generate_gpa()
{
	const double gpa_lower{ 50.0 };
	const double gpa_upper{ 100.0 };
	default_random_engine generator(rd());
	uniform_real_distribution<double> distribution(gpa_lower, gpa_upper);
	
	return distribution(generator);
}

//Sort option list A to E randomly.
//PRE: Option values are declared.
//POST: Options inside a vector shuffled.
//RETURN: Options stored in a vector<char>.
vector<char> generator::generate_options()
{
	vector<char> options = { 'A', 'B', 'C', 'D', 'E'};
	random_shuffle(options.begin(), options.end());
	return options;
}

//Generate priorities according to the limit.
//PRE: Lower bound & Upper bound are indicated.
//POST: 80% of the results should be "1", 20% of the results should be "2". 
int generator::generate_priority()
{
	const int priority_lower{ 1 };
	const int priority_upper{ 2 };
	const int priority1_limit{ 100 };
	const int priority2_limit{ 25 };
	int priority{ 0 };
	default_random_engine generator(rd());
	uniform_int_distribution<> distribution(priority_lower, priority_upper);

	//When "2" is already generated 25 times.
	if (priority2 >= priority2_limit) {

		return priority_lower; /*Return: "1"*/
	
	//When "2" is not generated 25 times 
	// & "1" is already generated 100 times.
	} else if (priority1 >= priority1_limit) {
		
		return priority_upper; /*Return: "2"*/
	
	} 
		
	priority = distribution(generator);

	//Count the times that "1" is generated.
	if (priority == 1) {
		priority1++;

	//Count the times that "2" is generated.
	} else {
		priority2++;
	}

	return priority;
}
