#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Mobile {
private:
	string name;
	string producer;
	string *models;
	int n;
public:
	Mobile() :name(" "), producer(" "), n(0), models(NULL) {}
	Mobile(const Mobile&m) {
		name = m.name;
		producer = m.producer;
		n = m.n;
		models = new string[n];
		for (int i = 0; i < n; i++) {
			models[i] = m.models[i];
		}
	}
	~Mobile() { delete[]models; }

	Mobile &operator=(const Mobile &m) {
		if (this != &m) {
			name = m.name;
			producer = m.producer;
			n = m.n;
			models = new string[n];
			for (int i = 0; i < n; i++) {
				models[i] = m.models[i];
			}
		}
		return *this;
	}

	void vvid(istream& in) {
		in >> name >> producer >> n;
		models = new string[n];
		for (int i = 0; i < n; i++) {
			in >> models[i];
		}
	}

	void vyvid(ostream& out) {
		out << name << " " << producer << " ";
		for (int i = 0; i < n; i++) {
			out << models[i] << " ";
		}
		out << endl;
	}

	string get_name()const {
		return name;
	}
	string  get_producer() {
		return producer;
	}
	string get_model(int i)const {
		return models[i];
	}
	int get_n()const {
		return n;
	}
	bool isModel(string mod) {
		for (int i = 0; i < n; i++) {
			if (models[i] == mod) {
				return true;
			}
			return false;
		}
	}
};
//завдання1
string modelProducer(int n, string model, Mobile *mob) {
	for (int i = 0; i < n; i++) {
		if (mob[i].isModel(model)) {
			return mob[i].get_producer();
		}
	}
}
//завдання2
void print(int n, string name, Mobile *mob) {
	for (int i = 0; i < n; i++) {
		if (mob[i].get_name() == name) {
			for (int j = 0; j < mob[i].get_n(); j++) {
				cout << mob[i].get_model(j) << " ";
			}
		}
	}
}
//завдання3 виводить в окремий файл Sorted.txt
void sort(int n, Mobile *mob) {
	Mobile temp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (mob[j].get_producer() > mob[j + 1].get_producer()) {
				temp = mob[j + 1];
				mob[j + 1] = mob[j];
				mob[j] = temp;
			}
		}
	}
	ofstream output("Sorted.txt");
	for (int i = 0; i < n; i++) {
		mob[i].vyvid(output);
	}
	output.close();
}

void main() {
	Mobile *mob;
	int n;
	string model;
	string name;
	cin >> model >> name;
	ifstream input("Mobile.txt");
	input >> n;
	mob = new Mobile[n];
	for (int i = 0; i < n; i++) {
		mob[i].vvid(input);
	}
	input.close();
	cout << modelProducer(n, model, mob) << endl;
	print(n, name, mob);
	sort(n, mob);
	system("pause");
}