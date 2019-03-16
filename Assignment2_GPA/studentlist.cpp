#include "studentlist.hpp"

//Default constructor.
studentlist::studentlist()
{
	
	for (int i = 0; i < loops; ++i) {

		//Generate a pointer to an student object.
		shared_ptr<student> s(new student(generator::get_instance().generate_id(), generator::get_instance().generate_gpa(),
										 generator::get_instance().generate_options(), generator::get_instance().generate_priority()));
		
		//Push a student object into the list.
		list.push_back(s);
	}
}

//Constructor which accepts a file.(Read a textfile & create list object.)
studentlist::studentlist(const string filename)
{
	list = *create_list_from_file(filename);
}

//Copy constructor.
studentlist::studentlist(const studentlist & object){
	list = object.list;
	it = object.it;
}

//Destructor.
studentlist::~studentlist() {}

//Create a studentlist from a text file.
//PRE: A correct file name passed to the function.
//POST: Return shared pointer to a newly created list.
//RETURN: Shared pointer to a new list.
shared_ptr<vector<shared_ptr<student>>> studentlist::create_list_from_file(const string filename)
{
	/*Constatnt values(To avoid magic nubmers)*/
	const int index_id{ 0 };
	const int index_gpa{ 1 };
	const int option_begin{ 2 };
	const int option_end{ 6 };
	const int index_priority{ 7 };

	/*Temporary values*/
	string line, word;
	istringstream iss;
	vector<string> gpa_list;
	int id;
	double gpa;
	vector<char> gpa_list_options;
	int priority;
	
	/*To return shared pointer.*/
	shared_ptr<student> s;
	shared_ptr<vector<shared_ptr<student>>> new_list(new vector<shared_ptr<student>>);

	//Read file.
	ifstream student_text_data(filename);

	//Error handling.
	if (!student_text_data.is_open()) {
		cerr << "Unable to open the file." << endl;
		system("pause");
		exit(1);
	}

	//Read file line by line.
	while (getline(student_text_data, line, '\n')) {
		istringstream iss(line);

		//Read line word by word.(Separated by space).
		while (getline(iss, word, ' ')) {
			gpa_list.push_back(word);
		}

		//Convert each data string into suitable value &
		//Store each into temporary variable.
		id = stoi(gpa_list.at(index_id));
		gpa = stod(gpa_list.at(index_gpa));
		for (int i = option_begin; i <= option_end; ++i) {
			gpa_list_options.push_back(*gpa_list.at(i).c_str());
		}
		priority = stoi(gpa_list.at(index_priority));
		
		//Create new student object with aquired data.
		s.reset(new student(id, gpa, gpa_list_options, priority));
		
		//Push a shared pointer to a newly created object into the list.
		new_list->push_back(s);

		//Clear temporary vectors for next loop.
		gpa_list.clear();
		gpa_list_options.clear();
	}

	return new_list;
}

//Output a unordered student list.
//PRE: Correct filename is passed.
//POST: Output text file correctly.
//RETURN: None.
void studentlist::output_studentlist(const string file_name)
{
	ofstream output_file(file_name);
	
	//Error handling.
	if (!output_file.is_open()) {
		cout << "Unable to open output file" << endl;
		exit(1);
	}

	//Output into the ofstream.
	for (it = list.begin(); it != list.end(); ++it) {
		
		//Student ID (8 digits)
		output_file << setfill('0') << setw(8) << (*it)->get_id();
		output_file << ' ';
		
		//GPA (5.0 to 9.0)
		output_file << showpoint << setprecision(3) << (*it)->get_gpa();
		output_file << ' ';

		//Options (A to E)
		for (int i = 0; i < option_size;  ++i) {
			output_file << (*it)->get_options().at(i);
			output_file << ' ';
		}
		
		//Priority.
		output_file << (*it)->get_priority();
		output_file << "\n";
	}
	
	cout << "File : " << file_name << " has been created." << endl;

	//Close a file.
	output_file.close();
}

//Place students according to their gpa & output a text file.
//PRE: None.
//POST: Students sorted according to gpa & Output a text file.
//RETURN: vector<shared_ptr<student>&
vector<shared_ptr<student>> studentlist::place_by_gpa(const string filename)
{
	vector<shared_ptr<student>> gpa_list = *(create_list_from_file(filename));
	vector<int> popular_option = { 0, 0, 0, 0, 0 }; /*Counts the number of students in each op.*/

	//Sort the list according to gpa & priority.(lambda expression.)
	//If there are samge gpa value, compare priority(1 is prior to 2).
	sort(gpa_list.begin(), gpa_list.end(), [](const shared_ptr<student> first, const shared_ptr<student> second) -> bool
	{ return first->get_priority() == second->get_priority() ? first->get_gpa() > second->get_gpa() : first->get_priority() < second->get_priority(); });

	for (it = gpa_list.begin(); it != gpa_list.end(); ++it) {
		const int first_option{ 0 };
		int count_retry{ 1 };
		bool flag{ false };
		char val = (*it)->get_options().at(first_option);

	retry: 
		if (flag == true) {
			val = (*it)->get_options().at(count_retry);
			(*it)->set_unhappiness(count_retry); /*When retry, increase 1 unhappiness.*/
			count_retry++;
		}

		switch (val) {
		case 'A':
			if ((popular_option.at(0)++) < 25) {
				(*it)->set_final_option('A');
				break;
			}
			flag = true;
			goto retry;

		case 'B':
			if ((popular_option.at(1)++) < 25) {
				(*it)->set_final_option('B');
				break;
			}
			flag = true;
			goto retry;

		case 'C':
			if ((popular_option.at(2)++) < 25) {
				(*it)->set_final_option('C');
				break;
			}
			flag = true;
			goto retry;

		case 'D':
			if ((popular_option.at(3)++) < 25) {
				(*it)->set_final_option('D');
				break;
			}
			flag = true;
			goto retry;

		case 'E':
			if ((popular_option.at(4)++) < 25) {
				(*it)->set_final_option('E');
				break;
			}
			flag = true;
			goto retry;
		}
	}

	//Output.
	output_txt(gpa_list, "gpa.txt");

	return gpa_list;
}

//Replace students again to minimize thier unhappiness level.
//PRE: None.
//POST: Decrease unhappiness level of stduents & output a text file.
//RETURN: vector<shared_ptr<student>>&
vector<shared_ptr<student>>& studentlist::minimize_unhappiness(vector<shared_ptr<student>>& orderedlist)
{
	const int limit{ 1 };
	const int second_option{ 1 };
	const int one{ 0 };
	const int default_happiness{ 1 };
	const int a{ 0 };
	const int b{ 1 };
	const int c{ 2 };
	const int d{ 3 };
	const int e{ 4 };
	int happy_level{ 0 };
	int count_retry{ 1 };
	bool flag{ true };
	vector<option> popular_option;
	vector<option> reserved_seat;
	vector<shared_ptr<student>> unhappy_ppl;/*Stores only the students who feel unhappy*/

	//Copy ordered list according to gpa.
	vector<shared_ptr<student>> ordered_list = orderedlist;
	happy_level = get_entire_unhappiness(ordered_list);
	
	cout << "Before minimize unhappiness: " << happy_level << endl;
	
	//Initialize counters.
	reserved_seat.resize(option_size);
	popular_option.resize(option_size);

	//Extract students who have at least 1 unhappiness.
	//And Count the remaning seats for each op.
	for (it = ordered_list.begin(); it != ordered_list.end(); ++it) {
		
		//Unhappiness value is 1 or more.
		if ((*it)->get_unhappiness() >= limit) {
			
			(*it)->set_unhappiness(default_happiness);
			unhappy_ppl.push_back(*it);

			switch ((*it)->get_options().at(second_option))
			{
			case 'A':
				popular_option.at(a).total_num++;
				break;
			case 'B':
				popular_option.at(b).total_num++;
				break;
			case 'C':
				popular_option.at(c).total_num++;
				break;
			case 'D':
				popular_option.at(d).total_num++;
				break;
			case 'E':
				popular_option.at(e).total_num++;
				break;
			}
		
		//Unhappiness is 0.
		} else {

			switch ((*it)->get_final_option())
			{
			case 'A':
				reserved_seat.at(a).total_num++;
				break;
			case 'B':
				reserved_seat.at(b).total_num++;
				break;
			case 'C':
				reserved_seat.at(c).total_num++;
				break;
			case 'D':
				reserved_seat.at(d).total_num++;
				break;
			case 'E':
				reserved_seat.at(e).total_num++;
				break;
			}
		
		}
	}

	//Set Options for each index.
	popular_option.at(a).op = 'A';
	popular_option.at(b).op = 'B';
	popular_option.at(c).op = 'C';
	popular_option.at(d).op = 'D';
	popular_option.at(e).op = 'E';
	reserved_seat.at(a).op = 'A';
	reserved_seat.at(b).op = 'B';
	reserved_seat.at(c).op = 'C';
	reserved_seat.at(d).op = 'D';
	reserved_seat.at(e).op = 'E';

	//Sort popularity counter by ascending order.
	sort(popular_option.begin(), popular_option.end(), [](const option& op1, const option& op2) { return op1.total_num < op2.total_num; });

	for (it = unhappy_ppl.begin(); it != unhappy_ppl.end(); ++it) {
		for (int i = 0; i < option_size; ++i) {
			int j = { 1 };
		retry:
			if (flag == true) {
				j++;
				count_retry++;
				//cout << setw(8) << setfill('0') << (*it)->get_id() << endl;
				//cout << "Count " << count_retry << endl;
				(*it)->set_unhappiness(count_retry); /*When retry, increase 1 unhappiness.*/
			}

			if (popular_option.at(i).op == (*it)->get_options().at(j)) {
					
				switch (popular_option.at(i).op)
				{
				case 'A':
					 if (reserved_seat.at(a).total_num <= seat_size) {
						(*it)->set_final_option('A');
						count_retry = initalizer;
						flag = false;
						break;
					 }
					 else {
						 flag = true;
						 goto retry;
					 }

				case 'B':
					if (reserved_seat.at(b).total_num <= seat_size) {
						(*it)->set_final_option('B');
						count_retry = initalizer;
						flag = false;
						break;
					}
					 else {
						 flag = true;
						 goto retry;
					}	

				case 'C':
					 if (reserved_seat.at(c).total_num <= seat_size) {
						 (*it)->set_final_option('C');
						 count_retry = initalizer;
						 flag = false;
						 break;
					 }
					 else {
						 flag = true;
						 goto retry;
					 }

				case 'D':
					 if (reserved_seat.at(a).total_num <= seat_size) {
						 (*it)->set_final_option('D');
						 count_retry = initalizer;
						 flag = false;
						 break;
					 }
					 else {
						 flag = true;
						 goto retry;
					 }

				case 'E':
					if (reserved_seat.at(a).total_num <= seat_size) {
						(*it)->set_final_option('E');
						count_retry = initalizer;
						flag = false;
						break;
					}
					else {
						flag = true;
						goto retry;
					}
				}
			}

			if (flag == false) {
				break;
			}
		}	
	}

	cout << "After : " << get_entire_unhappiness(ordered_list) << endl;
	
	//Output.
	output_txt(ordered_list, "maxhappy.txt");
	
	return ordered_list;
}

//Calculate total unhapiness level of students.
//PRE: Ordered list is passed to the function.
//POST: Return total unhapiness level.
//RETURN: Total unhappiness level(int).
const int studentlist::get_entire_unhappiness(vector<shared_ptr<student>>& ordered_list)
{
	int total{0};
	for (it = ordered_list.begin(); it != ordered_list.end(); ++it) {
		total += (*it)->get_unhappiness();
	}
	return total;
}

//Output passed list.
//PRE: A list & desired output name is passed.
//POST: Create a text file.
//RETURN: None.
void studentlist::output_txt(vector<shared_ptr<student>>& list, const string filename)
{
	ofstream output_file(filename);

	//Error handling.
	if (!output_file.is_open()) {
		cout << "Unable to open output file" << endl;
		exit(1);
	}

	for (it = list.begin(); it != list.end(); ++it) {
		output_file << setfill('0') << setw(8) << (*it)->get_id();
		output_file << ' ';
		output_file << (*it)->get_final_option();
		output_file << endl;
	}

	cout << "File : " << filename << " has been created." << endl;

	//Close a file.
	output_file.close();
}


