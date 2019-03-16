#pragma once
#include <fstream>
#include <memory>
#include <sstream>
#include "student.hpp"
#include "generator.hpp"

using namespace std;

struct option
{
	int total_num;
	char op;
};

//The class which reperesents studentlist.
class studentlist {
private:
	vector<shared_ptr<student>> list;
	vector<shared_ptr<student>>::iterator it;
	//Constants to avoid magic number.
	const int loops{ 125 };
	const int option_size{ 5 };
	const int seat_size{ 25 };
	const int initalizer{ 0 };
public:
	studentlist();
	studentlist(const string filename);
	studentlist(const studentlist& object);
	~studentlist();
	void output_studentlist(const string filename); 
	shared_ptr<vector<shared_ptr<student>>>  create_list_from_file(const string filename); 
	vector<shared_ptr<student>> place_by_gpa(const string filename);
	vector<shared_ptr<student>>& minimize_unhappiness(vector<shared_ptr<student>>& orderedlist);
	const int get_entire_unhappiness(vector<shared_ptr<student>>& ordered_list);
	void output_txt(vector<shared_ptr<student>>& list, const string filename);
};