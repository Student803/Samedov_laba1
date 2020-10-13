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
			cout << "Все цехи включены" << endl;
	}

	void Stop() {
		if (quantityInWork > 0)
			quantityInWork--;
		else
			cout << "Все цехи выключены" << endl;
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
		if (!first) cout << "Некорректный ввод, введите еще раз >> ";
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
		if (!first) cout << "Некорректный ввод, введите еще раз >> ";
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
			cout << "1. Добавить трубу" << endl <<
				"2. Добавить КС" << endl <<
				"3. Просмотр всех объектов" << endl <<
				"4. Редактировать трубу" << endl <<
				"5. Редактировать КС" << endl <<
				"6. Сохранить" << endl <<
				"7. Загрузить" << endl <<
				"0. Выход" << endl;
			command = inputPositiveInteger("Введите номер команды: ");
			while (command > 7)
			{
				cout << "Введенное число больше 7! ";
				command = inputPositiveInteger("Введите номер команды: ");
			}
			switch (command) {
			case 1:
			{
				Tube tube1;
				tube1.id = idTube;
				tube1.length = inputPositiveFloat("Введите длину: ");
				tube1.diam = inputPositiveFloat("Введите диаметр: ");
				arrTube.push_back(tube1);
				idTube++;
				break;
			}
			case 2:
			{
				Cs cs1;
				cs1.id = idCs;
				cout << "Введите наименование: ";
				cin >> cs1.name;
				cs1.quantity = inputPositiveInteger("Введите количество цехов: ");
				int cur = inputPositiveInteger("Введите количество цехов в работе: ");
				while (cur > cs1.quantity) {
					cout << "Введенное число больше количества цехов! ";
					cur = inputPositiveInteger("Введите количество цехов в работе: ");
				}
				cs1.quantityInWork = cur;
				cs1.efficiency = inputPositiveFloat("Введите показатель эффективности: ");
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
					cout << "Компрессорная станция №: " << idCs++ << endl;
					cout << "Наименование: " << it.name << endl;
					cout << "Количество цехов: " << it.quantity << endl;
					cout << "Количество цехов в работе: " << it.quantityInWork << endl;
					cout << "Показатель эффективности: " << it.efficiency << endl << endl;
				}
				for (auto it : arrTube) {
					cout << "Труба №: " << idTube++ << endl;
					cout << "Длина: " << it.length << endl;
					cout << "Диаметр: " << it.diam << endl;
					if (!it.repaired)
						cout << "В ремонте: нет" << endl << endl;
					else
						cout << "В ремонте: да" << endl << endl;
				}
				break;
			}
			case 4: 
			{
				int id;
				id = inputPositiveInteger("Введите номер трубы: ");
				if (id > arrTube.size() || id < 1)
				{
					cout << "Такой трубы не существует! " << endl;
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
				id = inputPositiveInteger("Введите номер КС: ");
				if (id > arrCs.size() || id < 1)
				{
					cout << "Такой станции не существует! " << endl;
				}
				else 
				{
					int n;
					id = id - 1;
					n = inputPositiveInteger("Введите 1, чтобы запустить цех, или 2, чтобы остановить цех: ");
					while (n != 1 && n != 2)
					{
						cout << "Введенное число не равно 1 или 2! ";
						n = inputPositiveInteger("Введите номер команды: ");
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
				if (arrCs.size() == 0) fout << "Нет КС!";
				for (auto& it : arrCs)
				{
					fout << "Компрессорная станция №: " << idCs++ << endl;
					fout << "Наименование: " << it.name << endl;
					fout << "Количество цехов: " << it.quantity << endl;
					fout << "Количество цехов в работе: " << it.quantityInWork << endl;
					fout << "Показатель эффективности: " << it.efficiency << endl << endl;
				}


				if (arrTube.size() == 0) fout << "Нет труб!";
				for (auto& it : arrTube)
				{
					fout << "Труба №: " << idTube++ << endl;
					fout << "Длина: " << it.length << endl;
					fout << "Диаметр: " << it.diam << endl;
					fout << (it.repaired ? "В ремонте !" : "Не в ремонте!") << endl << endl;
				}
				cout << "Вывели трубы и КС в файл output.txt" << endl;

				fout.close();
			}
			case 7:
			{
				ifstream fin("input.txt");
				if (!fin.is_open())
					cout << "Файл не может быть открыт!";
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
				cout << "Ввели из файла данные" << endl;
				fin.close();
				break;
			}
			case 0:
				return 0;
		}
	}
}