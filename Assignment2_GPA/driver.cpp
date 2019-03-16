#include "student.hpp"
#include "studentlist.hpp"
#include "generator.hpp"
#include <sstream>

using namespace std;

int main()
{
	vector<shared_ptr<student>>::iterator it;
	vector<shared_ptr<student>> new_list;
	vector<shared_ptr<student>> new_list2;

	studentlist list1;
	
	//1. Create students.txt.
	list1.output_studentlist("students.txt");
	
	//2. Create list by opening students.txt.
	studentlist list2(list1);

	//3. Create gpa.txt.
	new_list = list2.place_by_gpa("students.txt");
	
	//4. Create maxhappy.txt.
	list2.minimize_unhappiness(new_list);
	
	system("pause");
	return 0;
}