#include "student.hpp"

//Default constructor.
student::student():id{ generator::get_instance().generate_id() }, gpa{ default_gpa }, options{default_options}, priority{default_priority} 
{}

//3 parameter constructor.
student::student(int id, double gpa, vector<char> options, int priority) :id{ id },  gpa { gpa }, options{ options }, priority{ priority }
{}

//Copy constructor.
student::student(const student & s)
{
	id = s.get_id();
	set_gpa(s.get_gpa());
	set_options(s.get_options());
	set_priority(s.get_priority());
}

//Overload Insertion operator.
ostream & operator<<(ostream & os, const student & student)
{
	const int option_size{ 5 };
	os << "Studnet ID : " << setfill('0') << setw(8) << student.get_id() << endl;
	os << "GPA : " << showpoint << student.get_gpa() << endl;
	os << "Options : ";
	for (int i = 0; i < option_size; ++i) {
		os << student.get_options().at(i);
		os << ' ';
	}
	os << "\n";
	os << "Priority : " << student.get_priority() << endl;
	return os;
}
