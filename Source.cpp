#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include<fstream>
const int Size = 100;
using namespace std;
int ListSize = 0;
struct Date {
	int Day;
	int Month;
	int Year;
};
struct container {
	string Title;
	string Details;
	Date DueDate;
	int Priority;
	bool Mark_Done = false;
}Task[Size];
//Add Task
void AddTask(container Task[], int& ListSize)
{
	cout << "Enter the title of the task:";
	cin.ignore();
	getline(cin, Task[ListSize].Title);
	cout << "Enter the Due Date:";
	cin >> Task[ListSize].DueDate.Day >> Task[ListSize].DueDate.Month >> Task[ListSize].DueDate.Year;
	cin.ignore();
	cout << "Enter The Details of the task:";
	getline(cin, Task[ListSize].Details);
	cout << "Enter The prioity of the Task:";
	cin >> Task[ListSize].Priority;
	ListSize++;
}
//Display all tasks
void DisplayAllTasks(container Task[]) {
	if (ListSize == 0)
	{
		cout << "You Have No Tasks";
	}
	else {
		for (int i = 0; i < ListSize; i++)
		{
			cout << '#' << i + 1 << endl;
			cout << "Title: " << Task[i].Title << endl;
			cout << "Details: " << Task[i].Details << endl;
			cout << "Due Date: " << Task[i].DueDate.Day << '\\' << Task[i].DueDate.Month << '\\' << Task[i].DueDate.Year << endl;
			cout << "Priority: " << Task[i].Priority << endl;

		}
	}
}
/*void Priority_Display(container Task[], int ListSize) {
	int max = -1;
	//max priority number
	for (int i = 0; i < ListSize; ++i) {
		if (Task[i].Priority > max)
			max = Task[i].Priority;
	}

	for (int i = 1; i <= max; ++i) {
		for (int j = 0; j < ListSize; ++j) {
			if (Task[j].Priority == i) {
				cout << Task[j].Title << endl;
			}

		}
	}
}*/

void Display_Titles(container Task[]) {
	cout << "Your tasks :";
	for (int i = 0; i < ListSize; i++) {
		cout << i + 1 << "-" << Task[i].Title << endl;
	}

}
//search by title 
void Search_By_Title(container Task[]) {
	string TaskTitle;
	string temp;
	bool found = false;


	cout << " Please enter the task's title to search for: ";
	cin.ignore();
	getline(cin, TaskTitle);
	for (int i = 0; i < ListSize; i++) {
		if (TaskTitle.size() == Task[i].Title.size()) {
			transform(TaskTitle.begin(), TaskTitle.end(), TaskTitle.begin(), ::tolower);
			temp = Task[i].Title;
			transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
			if (TaskTitle.compare(temp) == 0) {
				found = true;
				cout << " Title : " << Task[i].Title << endl;
				cout << " Details :" << Task[i].Details << endl;
				cout << " Date" << Task[i].DueDate.Day << '\\' << Task[i].DueDate.Month << '\\' << Task[i].DueDate.Year << endl;
				cout << " Priority :" << Task[i].Priority << endl;

			}
		}


	}

	if (found == false) {
		cout << "No Item Match Your Search \n";
	}
}

void Mark_Task(container task[]) {
	Display_Titles(Task);
	int Task_No;
	cout << "Enter the Number of Task";
	cin >> Task_No;
	Task[Task_No - 1].Mark_Done = true;
}//Mark task as done

void Display_marked_tasks(container task[]) {
	for (int i = 0; i < ListSize; ++i) {
		if (task[i].Mark_Done == true) {
			cout << task[i].Title << endl;
		}
	}

}//Display marked task

void today_task(time_t now, container Task[]) {
	struct tm nowlocal;
	bool today = false;
	now = time(NULL);//get date and time from operating system
	nowlocal = *localtime(&now);
	nowlocal.tm_mon += 1;
	nowlocal.tm_year += 1900; cin.get();
	for (int i = 0; i < ListSize; i++)
	{
		if (Task[i].DueDate.Year == nowlocal.tm_year&&Task[i].DueDate.Month == nowlocal.tm_mon&&Task[i].DueDate.Day == nowlocal.tm_mday) {
			cout << "Tasks need to be done today are:" << "  " << Task[i].Title << endl << Task[i].Details << endl;
			today = true;
		}

	}
	if (today == false)
	{
		cout << "No Tasks Needed to be done today";
	}
}

void DeleteTask(container Task[], int& ListSize) {
	Display_Titles(Task);
	int Task_No;
	cout << "Enter the Number of Task";
	cin >> Task_No;
	for (int i = Task_No - 1; i < ListSize - 1; i++) {
		Task[i] = Task[i + 1];
	}
	ListSize--;
}
void Overdue(time_t now, container Task[])
{

	struct tm nowlocal;
	now = time(NULL);//get date and time from operating system
	nowlocal = *localtime(&now);
	nowlocal.tm_mon += 1;
	nowlocal.tm_year += 1900; cin.get();
	cout << "OverDue:";
	for (int i = 0; i < ListSize; i++)
	{
		if (Task[i].DueDate.Year < nowlocal.tm_year)
		{
			cout << Task[i].Title << endl;
		}
		else if (Task[i].DueDate.Year == nowlocal.tm_year)
		{
			if (Task[i].DueDate.Month < nowlocal.tm_mon)
			{
				cout << Task[i].Title << endl;
			}
			else if (Task[i].DueDate.Month == nowlocal.tm_mon)
			{
				if (Task[i].DueDate.Day < nowlocal.tm_mday)
				{
					cout << Task[i].Title << endl;
				}
			}
		}
	}




}void edit(container Task[Size]) {
	int Task_No;
	int choice;
	Display_Titles(Task);
	cout << "Enter the Number of Task";
	cin >> Task_No;
	cout << "Enter what do  you want to edit" << endl << "1-Title " << endl << "2-Details" << endl << "3-Date" << endl << "4-Priority";
	cin >> choice;
	if (choice == 1) {
		cout << Task[Task_No - 1].Title << endl << " enter your edit please";
		cin >> Task[Task_No - 1].Title;
		cout << "The new title is :";
		cout << Task[Task_No - 1].Title << endl;
	}
	else if (choice == 2) {
		cout << Task[Task_No - 1].Details << endl << " enter your edit please";
		cin >> Task[Task_No - 1].Details;
		cout << Task[Task_No - 1].Details;
	}
	else if (choice == 3) {
		cout << Task[Task_No - 1].DueDate.Day << '/' << Task[Task_No - 1].DueDate.Month << '/' << Task[Task_No - 1].DueDate.Year;
		cout << "enter the new day please";
		cin >> Task[Task_No - 1].DueDate.Day;
		cout << " enter the new month please";
		cin >> Task[Task_No - 1].DueDate.Month;
		cout << " enter the new year please";
		cin >> Task[Task_No - 1].DueDate.Year;
		cout << Task[Task_No - 1].DueDate.Day << '/' << Task[Task_No - 1].DueDate.Month << '/' << Task[Task_No - 1].DueDate.Year << endl;
	}
	else if (choice == 4) {
		cout << Task[Task_No - 1].Priority << "enter the new edit please";
		cin >> Task[Task_No - 1].Priority;
		cout << Task[Task_No - 1].Priority;
	}
	else {
		cout << "Invalied Number";
	}
}
void ReadFromFile(container Task[], int& ListSize) {
	ifstream in_put;

	in_put.open("My file.txt");
	if (in_put.is_open())
	{
		in_put >> ListSize;
		in_put.ignore();
		for (int i = 0; i < ListSize; i++) {
			getline(in_put, Task[i].Title);
			getline(in_put, Task[i].Details);
			in_put >> Task[i].DueDate.Day;
			in_put >> Task[i].DueDate.Month;
			in_put >> Task[i].DueDate.Year;
			in_put >> Task[i].Mark_Done;
			in_put >> Task[i].Priority;
			in_put.ignore();
		}
		in_put.close();
	}
	else {
		cout << "Error in opening the file";
	}
}
void SaveToFile(container Task[], int ListSize) {
	ofstream out_put;
	out_put.open("My file.txt");
	if (out_put.is_open()) {
		out_put << ListSize << endl;
		for (int i = 0; i < ListSize; i++)
		{
			out_put << Task[i].Title << endl;
			out_put << Task[i].Details << endl;
			out_put << Task[i].DueDate.Day << endl;
			out_put << Task[i].DueDate.Month << endl;
			out_put << Task[i].DueDate.Year << endl;
			out_put << Task[i].Mark_Done << endl;
			out_put << Task[i].Priority << endl;
		}
		cout << "Data is Saved" << endl;
	}
	else {
		cout << "error in saving data" << endl;
	}
	out_put.close();
}

int main() {

	int choice = 0;
	time_t now = time(0);
	char My_File[100] = { "My file.txt" };
	ReadFromFile(Task, ListSize);//ReadFromFile()
	do {
		cout << "Menu :" << endl;
		cout << "1 - Add new Task ." << endl << "2 - Edit task ." << endl << "3 - Delete task ." << endl << "4 - Mark task as done ."
			<< endl << "5 - Display done tasks ." << endl << "6 - Display all tasks ." << endl << " 7 - Display overdue task ." << endl
			<< "8 - Display tasks needed to be done today. " << endl << "9 - To Search by title" << endl <<
			"10-Exit" << endl;
		cout << "Enter Your choice :";

		cin >> choice;
		switch (choice) {
		case 1:
			AddTask(Task, ListSize);
			break;
		case 2:
			edit(Task);
			break;
		case 3:
			DeleteTask(Task, ListSize);
			break;
		case 4:
			Mark_Task(Task);
			break;
		case 5:
			Display_marked_tasks(Task);
			break;
		case 6:
			DisplayAllTasks(Task);
			break;
		case 7:
			Overdue(now, Task);
			break;
		case 8:
			today_task(now, Task);
			break;
		case 9:
			Search_By_Title(Task);
			break;
			/*case 10:
				Priority_Display(Task,ListSize);
				break;*/
		case 10:
			SaveToFile(Task, ListSize);
			//SaVE TO FILE
			break;
		default:
			cout << "Invalied Number";
			break;
		}
	} while (choice != 10);
	system("pause");
	return 0;
}