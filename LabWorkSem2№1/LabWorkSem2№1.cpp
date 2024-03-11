#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

int room = 0; 
const int maxStudents = 30;//Кол-во студентов, что можно ввести.
//const int N = 5; // Кол-во оценок, что можно ввести.

using namespace std;

struct addInfoStudents
{
	string nonresident;
	int finance;
};

struct grades
{
	int exam[3];
	int test[5];
};

struct student
{
	string FullName;
	string gender;
	int GroupNum;    
	int GroupList;
	grades studGrades;
	addInfoStudents addInfo;
};

void createStudents(student students[], int &ch) {
    bool exit = false;
    while (!exit && room < maxStudents) {
        cout << "\tStudent " << room + 1 << endl;
        cout << "Full name: ";
        cin.ignore();
        getline(cin, students[room].FullName);
        cout << endl;
        cout << "Gender: ";
        getline(cin, students[room].gender);
        cout << endl;
        cout << "Group number: ";
        cin >> students[room].GroupNum;
        cout << endl;
        cout << "Group list number: ";
        cin >> students[room].GroupList;
        cout << endl;
        cin.ignore();
		cout << "Exam scores: ";
		for (short i = 0; i < 3; i++) {
			cin >> students[room].studGrades.exam[i];
		}
		cout << "Test scores: ";
		for (short i = 0; i < 5; i++) {
			cin >> students[room].studGrades.test[i];
		}
        cout << endl;
        
        if (ch == 1) {
            cout << "\nFinish filling out the list? [1-Yes, 2-No]\n";
            int choice;
            cin >> choice;
            if (choice == 1) {
                exit = true; 
                system("cls");
            }
            else if (choice == 2) {
                exit = false; 
                system("cls");
            }
            else {
                cout << "Error" << endl;
            }
        } else {
            exit = true;
        }

        room++;
    }
}

void data(student students[], int number) {
	for (int i = number; i < room; i++) {
		cout << "\tStudent " << i + 1 << endl;
		cout << "Full name: " << students[i].FullName << endl;
		cout << "Gender: " << students[i].gender << endl;
		cout << "Group number: " << students[i].GroupNum << endl;
		cout << "Group list number: " << students[i].GroupList << endl;
		cout << "Exam scores ";
		for (short j = 0; j < 3; j++) {
			cout << students[i].studGrades.exam[j] << " ";
		}
		cout << "\nTest scores: ";
		for (short j = 0; j < 5; j++) {
			cout << students[i].studGrades.test[j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void sortGroup(student students[]) {
	cout << "There are group students on the list: ";
	int arr[maxStudents];
	for (short i = 0; i < room; i++)
	{
		arr[i] = students[i].GroupNum;
	}
	for (short i = 0; i < room - 1; i++)
	{
		for (short j = 0; j < room - i - 1; j++)
		{
			if (arr[j] > arr[j+1])
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
	for (short i = 0; i < room; i++)
	{
		if (arr[i] != arr[i+1])
		{
			cout << arr[i] << ", ";
		}
	}
	cout << endl;
	cout << "What group of students do you want to find?\n" << endl;
	int numG; cin >> numG;
	//bool presStud = false;
	
	for (short i = 0; i < room; i++)
	{
		if (students[i].GroupNum == numG)
		{
			int buf = room;
			room = i + 1;
			data(students, i);
			room = buf;
		}
		if ( students[i].GroupNum != numG && i == room - 1)
		{
			cout << "Group number not found." << endl;
		}
	}
}

void topStudents(student students[]) {
	const int topStud = 3; //Кол-во лучших студентов, что выведит программа
	double sred[maxStudents];
	int serialNum[maxStudents];
	for (short i = 0; i < room; i++)
	{
		double sum = 0;
		for (short j = 0; j < 5; j++)
		{
			sum += students[i].studGrades.test[j];
		}
		for (short j = 0; j < 3; j++)
		{
			sum += students[i].studGrades.exam[j];
		}
		sred[i] = sum / 7;
		serialNum[i] = i;
	}
	for (short i = 0; i < room; i++)
	{
		for (short j = 0; j < room - 1; j++)
		{
			if (sred[j] < sred[j + 1])
			{
				swap(sred[j], sred[j + 1]);
				swap(serialNum[j], serialNum[j + 1]);
			}
		}
	}
	cout << "\tTop " << topStud <<" best students.\n" << endl;
	for (short i = 0; i < topStud; i++)
	{
		int buf = serialNum[i];
		cout << "Student " << serialNum[i] + 1 << " Name: " << students[buf].FullName << endl;
		cout << "Average score " << sred[i] << endl;
		cout << "Exam scores ";
		for (short j = 0; j < 3; j++) {
			cout << students[buf].studGrades.exam[j] << " ";
		}
		cout << "\nTest scores: ";
		for (short j = 0; j < 5; j++) {
			cout << students[buf].studGrades.test[j] << " ";
		}
		cout << endl << endl;
	}
}

void numManAndWoman(student students[]) {
	short numMen = 0, numWomen = 0;
	for (short i = 0; i < room; i++)
	{
		if (students[i].gender == "man" || students[i].gender == "Man")
		{
			numMen++;
		}
		if (students[i].gender == "woman" || students[i].gender == "Woman")
		{
			numWomen++;
		}
	}
	cout << "Number of men: " << numMen << endl;
	cout << "Number of women: " << numWomen << endl;
}

void grants(student students[]) {
	cout << "Students not receiving a scholarship.\n" << endl;
	for (short i = 0; i < room; i++)
	{
		short badMarks = 0;
		for (short j = 0; j < 3; j++)
		{
			if (students[i].studGrades.exam[j] < 4)
			{
				badMarks++;
			}
		}
		for (short j = 0; j < 5; j++)
		{
			if (students[i].studGrades.test[j] < 4)
			{
				badMarks++;
			}
		}
		if (badMarks == 8)
		{
			int buf = room;
			room = i + 1;
			data(students, i);
			room = buf;
		}
	}
	cout << "Students who only achieve 'good' and 'excellent' grades." << endl;
	for (short i = 0; i < room; i++)
	{
		short goodMarks = 0;
		for (short j = 0; j < 3; j++)
		{
			if (students[i].studGrades.exam[j] >= 4)
			{
				goodMarks++;
			}
		}
		for (short j = 0; j < 5; j++)
		{
			if (students[i].studGrades.test[j] >= 4)
			{
				goodMarks++;
			}
		}
		if (goodMarks == 8)
		{
			int buf = room;
			room = i + 1;
			data(students, i);
			room = buf;
		}
	}
	cout <<"Students who study only 'excellently'." << endl;
	for (short i = 0; i < room; i++)
	{
		short bestMarks = 0;
		for (short j = 0; j < 3; j++)
		{
			if (students[i].studGrades.exam[j] == 5)
			{
				bestMarks++;
			}
		}
		for (short j = 0; j < 5; j++)
		{
			if (students[i].studGrades.test[j] == 5)
			{
				bestMarks++;
			}
		}
		if (bestMarks == 8)
		{
			int buf = room;
			room = i + 1;
			data(students, i);
			room = buf;
		}
	}

}

void numInList(student students[]) {
	cout << "Enter the student number in the list." << endl;
	short num; cin >> num;
	for (short i = 0; i < room; i++)
	{
		if (students[i].GroupList == num)
		{
			int buf = room;
			room = i + 1;
			data(students, i);
			room = buf;
		}
	}
}

void textFile(student students[]) {
	ofstream file("data.txt");
	if (file.is_open()) {
		file << "\nStudents:\t";
		for (short i = 0; i < room; i++) {
			file << "student: " << i + 1 << "\t";
		}
		file << "\nFullName:\t";
		for (short i = 0; i < room; i++) {
			file << students[i].FullName << "\t\t";
		}
		file << "\nGender:\t\t";
		for (short i = 0; i < room; i++) {
			file << students[i].gender << "\t\t";
		}
		file << "\nGroup Number:\t";
		for (short i = 0; i < room; i++) {
			file << students[i].GroupNum << "\t\t";
		}
		file << "\nGroupList:\t";
		for (short i = 0; i < room; i++) {
			file << students[i].GroupList << "\t\t";
		}
		file << "\nExam scores:\t";
		for (short i = 0; i < room; i++) {
			for (short j = 0; j < 3; j++) {
				file << students[i].studGrades.exam[j] << " ";
			}
			file << "\t\t";
		}
		file << "\nTest scores:\t";
		for (short i = 0; i < room; i++) {
			for (short j = 0; j < 5; j++) {
				file << students[i].studGrades.test[j] << " ";
			}
			file << "\t";
		}
		file.close();
	}
	else {
		cout << "error" << endl;
	}
}

void dormitory(student students[]) {
	cout << "\tEnter additional information about the student" << endl;
	cout << "Is the student an international student? [Yes/No]" << endl;
	cout << "Family income." << endl;
	for (short i = 0; i < room; i++) {
		cout << "Student " << i + 1 << endl;
		cin >> students[i].addInfo.nonresident;
		cin >> students[i].addInfo.finance;
	}
	short income = 10000; //Мин. доход
	for (short i = 0; i < room; i++)
	{
		if ((students[i].addInfo.nonresident == "Yes" || students[i].addInfo.nonresident == "yes") && students[i].addInfo.finance <= income)
		{
			int buf = room;
			room = i + 1;
			students[i].addInfo.nonresident;
			students[i].addInfo.finance;
			cout << endl;
			data(students, i);
			room = buf;
		}
	}
}

int main() {
	struct student students[maxStudents];
	while (true)
	{
		cout << "\n[1]Create a new student record." << endl;
		cout << "[2]Making changes to an existing record." << endl;
		cout << "[3]Displays all student data." << endl;
		cout << "[4]Display information about all students in group N." << endl;
		cout << "[5]Displaying the top most successful students with the highest rated average score for the last session." << endl;
		cout << "[6]Displaying the number of male and female students." << endl;
		cout << "[7]Displaying data about students who do not receive a scholarship;" << endl;
		cout << "[8]Displaying data about students who have a number on the list. - k" << endl;
		cout << "[9]Writing data to a text file" << endl;
		cout << "[10]IDZ№1" << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:system("cls");  createStudents(students, choice); break;
		case 2:
			system("cls");
			cout << "What student number do you want to change?" << endl;
			int num;
			cin >> num;
			num--;
			system("cls");
			if (num >= 0 && num < maxStudents)
			{
				int buf = room;
				room = num;
				createStudents(students, choice);
				room = buf;
			}
			else {
				cout << "error2" << endl;
			}
			break;
		case 3: system("cls"); data(students, 0); break;
		case 4: system("cls"); sortGroup(students); break;
		case 5:system("cls"); topStudents(students); break;
		case 6: system("cls"); numManAndWoman(students); break;
		case 7: system("cls"); grants(students); break;
		case 8: system("cls"); numInList(students); break;
		case 9: system("cls"); textFile(students); break;
		case 10: system("cls"); dormitory(students); break;
		default: system("cls"); cout << "erro" << endl; break;
		}
	}
}
