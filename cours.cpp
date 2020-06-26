#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

struct Student{
	string name;
	string surname;
	int day;
	int month;
	int year;
};

int main() {
	int x;
	cin >> x;
	vector<Student> list;
	for (int i = 0; i < x; i++){
		string na;
		string surna;
		int da;
		int mon;
		int yea;
		cin >> na >> surna >> da >> mon >> yea;
		list.push_back({na, surna, da, mon, yea});
	}
	x = 0;
	cin >> x;
	for (int i = 0; i < x; i++){
		string com;
		int n;
		cin >> com >> n;
		if (com == "name" && n > 0 && n <= list.size()){
			cout << list[n - 1].name << ' ' << list[n - 1].surname << endl;
		}
		else if (com == "date" && n > 0 && n <= list.size()){

			cout << list[n - 1].day << '.' << list[n - 1].month << '.' << list[n - 1].year << endl;
		}
		else{
			cout << "bad request\n";
		}
	}
	return 0;
}
