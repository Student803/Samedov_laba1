#include <iostream>
#include <fstream>
#include <vector>
#include <regex>	
using namespace std;

struct Cs {
	int id;
	string name;
	int quantity;
	int quantityInWork;
	float efficiency;
	void Launch() {
		if (quantityInWork < quantity)
			quantityInWork++;
		else
			cout << "��� ���� ��������" << endl;
	}

	void Stop() {
		if (quantityInWork > 0)
			quantityInWork--;
		else
			cout << "��� ���� ���������" << endl;
	}
};

struct Tube {
	int id;
	float length;
	float diam;
	bool repaired = false;
	void Edit() {
		this->repaired = !this->repaired;
	}
};

bool isPositiveFloat(const string& s)
{
	const regex digit_regex("^[\+]?[0-9]+(\,[0-9])?[0-9]*$");
	return regex_match(s, digit_regex);
}

bool isPositiveInteger(const string& s)
{
	const regex digit_regex("^[\+]?[0-9]+$");
	return regex_match(s, digit_regex);
}

float inputPositiveFloat(const string& msg)
{
	char str[100];
	bool first = true;
	do {
		if (!first) cout << "������������ ����, ������� ��� ��� >> ";
		cout << msg;
		cin >> str;
		first = false;
	} while (!isPositiveFloat(str));
	return atof(str);
}

int inputPositiveInteger(const string& msg) {
	char str[100];
	bool first = true;
	do {
		if (!first) cout << "������������ ����, ������� ��� ��� >> ";
		cout << msg;
		cin >> str;
		first = false;
	} while (!isPositiveInteger(str));
	return atoi(str);
}

int main() {
	setlocale(LC_ALL, "Russian");
	vector<Cs> arrCs;
	vector<Tube> arrTube;
	int	idCs = 1;
	int idTube = 1;
	for (;;) {
			int command;
			cout << "1. �������� �����" << endl <<
				"2. �������� ��" << endl <<
				"3. �������� ���� ��������" << endl <<
				"4. ������������� �����" << endl <<
				"5. ������������� ��" << endl <<
				"6. ���������" << endl <<
				"7. ���������" << endl <<
				"0. �����" << endl;
			command = inputPositiveInteger("������� ����� �������: ");
			while (command > 7)
			{
				cout << "��������� ����� ������ 7! ";
				command = inputPositiveInteger("������� ����� �������: ");
			}
			switch (command) {
			case 1:
			{
				Tube tube1;
				tube1.id = idTube;
				tube1.length = inputPositiveFloat("������� �����: ");
				tube1.diam = inputPositiveFloat("������� �������: ");
				arrTube.push_back(tube1);
				idTube++;
				break;
			}
			case 2:
			{
				Cs cs1;
				cs1.id = idCs;
				cout << "������� ������������: ";
				cin >> cs1.name;
				cs1.quantity = inputPositiveInteger("������� ���������� �����: ");
				int cur = inputPositiveInteger("������� ���������� ����� � ������: ");
				while (cur > cs1.quantity) {
					cout << "��������� ����� ������ ���������� �����! ";
					cur = inputPositiveInteger("������� ���������� ����� � ������: ");
				}
				cs1.quantityInWork = cur;
				cs1.efficiency = inputPositiveFloat("������� ���������� �������������: ");
				cout << endl;
				arrCs.push_back(cs1);
				idCs++;
				break;
			}
			case 3:
			{
				int	idCs = 1;
				int idTube = 1;
				for (auto it : arrCs) {
					cout << "������������� ������� �: " << idCs++ << endl;
					cout << "������������: " << it.name << endl;
					cout << "���������� �����: " << it.quantity << endl;
					cout << "���������� ����� � ������: " << it.quantityInWork << endl;
					cout << "���������� �������������: " << it.efficiency << endl << endl;
				}
				for (auto it : arrTube) {
					cout << "����� �: " << idTube++ << endl;
					cout << "�����: " << it.length << endl;
					cout << "�������: " << it.diam << endl;
					if (!it.repaired)
						cout << "� �������: ���" << endl << endl;
					else
						cout << "� �������: ��" << endl << endl;
				}
				break;
			}
			case 4: 
			{
				int id;
				id = inputPositiveInteger("������� ����� �����: ");
				if (id > arrTube.size() || id < 1)
				{
					cout << "����� ����� �� ����������! " << endl;
				}
				else
				{
					id = id - 1;
					arrTube[id].Edit();
				}
				break;
			}
			case 5:
			{
				int id;
				id = inputPositiveInteger("������� ����� ��: ");
				if (id > arrCs.size() || id < 1)
				{
					cout << "����� ������� �� ����������! " << endl;
				}
				else 
				{
					int n;
					id = id - 1;
					n = inputPositiveInteger("������� 1, ����� ��������� ���, ��� 2, ����� ���������� ���: ");
					while (n != 1 && n != 2)
					{
						cout << "��������� ����� �� ����� 1 ��� 2! ";
						n = inputPositiveInteger("������� ����� �������: ");
					}
					if (n == 1)
						arrCs[id].Launch();
					else
						arrCs[id].Stop();
				}
				break;
			}
			case 6: 
			{
				ofstream fout;
				fout.open("output.txt");
				int idTube = 1;
				int idCs = 1;
				if (arrCs.size() == 0) fout << "��� ��!";
				for (auto& it : arrCs)
				{
					fout << "������������� ������� �: " << idCs++ << endl;
					fout << "������������: " << it.name << endl;
					fout << "���������� �����: " << it.quantity << endl;
					fout << "���������� ����� � ������: " << it.quantityInWork << endl;
					fout << "���������� �������������: " << it.efficiency << endl << endl;
				}


				if (arrTube.size() == 0) fout << "��� ����!";
				for (auto& it : arrTube)
				{
					fout << "����� �: " << idTube++ << endl;
					fout << "�����: " << it.length << endl;
					fout << "�������: " << it.diam << endl;
					fout << (it.repaired ? "� ������� !" : "�� � �������!") << endl << endl;
				}
				cout << "������ ����� � �� � ���� output.txt" << endl;

				fout.close();
			}
			case 7:
			{
				ifstream fin("input.txt");
				if (!fin.is_open())
					cout << "���� �� ����� ���� ������!";
				else
				{
					arrTube.clear();
					arrCs.clear();
					Tube tube1;
					Cs cs1;
					string buff;
					int idTube = 1;
					int idCs = 1;
					while (fin >> buff)
					{
						if (buff == "tube")
						{
							tube1.id = idTube++;
							fin >> tube1.length;
							fin >> tube1.diam;
							arrTube.push_back(tube1);
						}
						else
						{
							Cs cs1;
							cs1.id = idCs++;
							fin >> cs1.name;
							fin >> cs1.quantity;
							fin >> cs1.quantityInWork;
							fin >> cs1.efficiency;
							arrCs.push_back(cs1);
						}
					}
				}
				cout << "����� �� ����� ������" << endl;
				fin.close();
				break;
			}
			case 0:
				return 0;
		}
	}
}