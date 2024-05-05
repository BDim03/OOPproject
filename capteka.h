#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "cdate.h"
#include "clekarstva.h"

using namespace std;


class CApteka
{
private:
	string apt_name;
	vector <CLekarstva> vec;
	string chain;
	string deliver;
	int sales;

public:
	CApteka()
	{
		apt_name = "DefaultName";
		vec = {};
		chain = "DefaultChain";
		deliver = "DefaultDeliver";
		sales = 0;
	}

	CApteka(const CApteka& x)
	{
		apt_name = x.apt_name;
		vec = x.vec;
		chain = x.chain;
		deliver = x.deliver;
		sales = x.sales;
	}
	CApteka(string apt, string ch, string d, int s)
	{
		apt_name = apt;
		vec = {};
		chain = ch;
		deliver = d;
		sales = s;
	}

	~CApteka()
	{
	}

	void set_CAptekaName(string n);
	void set_CAptekaVecLekarstva(const vector <CLekarstva>& a);
	void set_CAptekaChain(string ch);
	void set_CAptekaDeliver(string del);
	void set_CAptekaSales(int s);
	
	string getAptName();
	vector <CLekarstva> getAptVec();
	string getAptChain();
	string getAptDeliver();
	int getAptSales();

	friend bool operator > (const CApteka& l, const CApteka& r);

	static void InFileApt(vector<CApteka>& data);
	bool compare(const CApteka& l, const CApteka& r);
	static void IzvejdaneSporedGrupaLekarstva(vector<CApteka>& data, int a);
	void aptdisplay();
	

};

void vecaptdisplay(vector <CApteka> apteki);

string CApteka::getAptName()
{
	return apt_name;
}
vector <CLekarstva> CApteka::getAptVec()
{
	return vec;
}
string CApteka::getAptChain()
{
	return chain;
}
string CApteka::getAptDeliver()
{
	return deliver;
}
int CApteka::getAptSales()
{
	return sales;
}


void CApteka::set_CAptekaName(string n)
{
	apt_name = n;
}
void CApteka::set_CAptekaVecLekarstva(const vector <CLekarstva>& a)
{
	this->vec = a;
}
void CApteka::set_CAptekaChain(string ch)
{
	this->chain = ch;
}
void CApteka::set_CAptekaDeliver(string del)
{
	this->deliver = del;
}
void CApteka::set_CAptekaSales(int s)
{
	this->sales = s;
}


bool CApteka::compare (const CApteka& l, const CApteka& r)
{
	return l.deliver < r.deliver;
}

bool operator > (const CApteka& l, const CApteka& r)
{
	return l.deliver > r.deliver;
}

void CApteka::aptdisplay()
{
	//cout << "/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "| Име на аптеката:   " << setw(20) << left << apt_name << endl;
	cout << "| Брой налични лекарства:   " << setw(20) << left << vec.size()<< endl;
	cout << "| Верига:   " << setw(20) << left << chain  << endl;
	cout << "| Доставчик:   " << setw(20) << left << deliver  << endl;
	cout << "| Продажби:   " << setw(20) << left << sales << endl;
	cout << "---------------------------------------------" << endl;
}
void CApteka::InFileApt(vector<CApteka>& data)
{
	ifstream file; //input file stream за входен поток

	file.open("Apteki.txt", ios::in); // отваряне на текстовия файл с флаг за четене

	if (!(file.is_open())) // проверява дали е отворен файла, ако е отворен връща true ,иначе при false извежда съобщение за проблем
	{
		cout << "Проблем при отварянето на файла." << endl;
	}

	string line; // стринг ,който ще взима целия ред от текстовия файл

	while (getline(file, line)) { // Четем всеки ред от файла
		size_t pos1 = line.find(':'); // Намираме първата позиция на двоеточието
		if (pos1 != string::npos) { // проверява дали е открито :
			size_t pos2 = line.find(':', pos1 + 1); // Намираме втората позиция на двоеточието, като търсенето започва от следващия символ след първия намерен (pos1+1)
			if (pos2 != string::npos) {
				size_t pos3 = line.find(':', pos2 + 1); // Намираме третата позиция на двоеточието
				if (pos3 != string::npos) {
					size_t pos4 = line.find(':', pos3 + 1); // намиране четвъртата позиция на двоеточието
		
						string straptname = line.substr(0, pos1); // Извличане първия подстринг, който започва от позиция 0 до позицията на първото двоеточие, но без него
						string strchain = line.substr(pos1 + 1, pos2 - pos1 - 1); // Извличане втория подстринг, като започва от позицията на първото двоеточие + 1, до другото двоеточие като намира колко символа трябва да прочете като изчислява разликата между позиция 2 и позиция 1 и се изважда 1 за самото двоеточие.
						string strdeliver = line.substr(pos2 + 1, pos3 - pos2 - 1); // Извличаме третия подстринг като започва от следваща позиция след второто двоеточие до разликата на пос3, пос2 и 1
						string strsales = line.substr(pos3 + 1, pos4 - pos3 - 1); // Извличаме четвъртия подстринг
					
						int sales = stoi(strsales); // кастване от низ към цяло число, чрез функцията stoi
					
						CApteka* p = new CApteka(straptname, strchain, strdeliver, sales); //създаване на pointer и обект, чрез експлицитен конструктор на който подаваме като параметри прочетените от файла данни
						data.push_back(*p); // добавяне на обекта към вектора
						delete p; // изтрива обекта
						
					
				}
			}
		}
	}

	
	file.close(); // затваряме файловия поток

	if (file.is_open()) // проверяваме дали е затворен файла
	{
		cout << "Проблем със затварянето на файла." << endl;
	}


}
void CApteka::IzvejdaneSporedGrupaLekarstva(vector<CApteka>& data, int a)
{

	for (int i = 0; i < data.size(); i++) //цикъл, който обхожда вектора с аптеки

	{
		bool flag = false; // флаг, който се вдига когато групата на лекарството е от определен вид
		vector <CLekarstva> tempVec; //временен вектор
		tempVec = data[i].vec; // на него се присвоява вектора с лекарства на дадената аптека за последващите проверки
		for (int k = 0; k < tempVec.size(); k++) // цикъл, който обхожда всички лекарства в дадена аптека
		{

			if (tempVec[k].getType() == a) // ако някое лекарство от всички е от конкретната група флага се вдига
			{
				flag = true;
			}

		}

		if (flag == false) // ако флага не е вдигнат съответно в дадената аптека няма лекарство от този вид
		{
			data[i].aptdisplay(); // извеждане на аптеката
			printVecLekarstva(tempVec); // извеждане на лекарствата в аптеката за справка

		}
	}


}

void SaveInFileApteka(CApteka& x)
{
	ofstream fileObj; // файлов поток за запис
	fileObj.open("Apteki.txt", ios::app); //отваряне на файла
	string all;

	if (!(fileObj.is_open())) // проверка
	{
		cout << "Проблем при отварянето на файла." << endl;
	}
	

	CApteka prob(x); //копиране на обекта ,чрез копиращ конструктор 

	string getName; // временни променливи
	string getChain;
	string getDeliver;
	int getSales;

	getName = prob.getAptName(); // извличане на данните от обекта
	getChain = prob.getAptChain();
	getDeliver = prob.getAptDeliver();
	getSales = prob.getAptSales();

	string sales = to_string(getSales); // обръщане на целочислено в string

	all = "\n" + getName + ":" + getChain + ":" + getDeliver + ":" + sales; //конкатенация на данните за обекта разделени с двоеточие
	fileObj << all; //записване във файла
	fileObj.close(); // затваряне на файла

	if (fileObj.is_open()) //проверка
	{
		cout << "Проблем със затварянето на файла." << endl;
	}

}
void AddApteka (vector <CApteka>& data)
{
	string tempName; //временни променливи
	string tempChain;
	string tempDeliver;
	int tempSales;
	cout << "Въведи име на аптека: ";
	cin.ignore();
	getline(cin, tempName);

	cout << "Въведи име на верига:";
	getline(cin, tempChain);

	cout << "Въведи доставчик: ";
	getline(cin, tempDeliver);

	cout << "Въведи брой продажби: ";
	cin >> tempSales;

	CApteka a(tempName, tempChain, tempDeliver, tempSales); //създаване на обект с дадените параметри използвайки експлицитен конструктор
	data.push_back(a); // запазване във вече заредения вектор с наличните аптеки

	SaveInFileApteka(a); //записване във файла

}
void Prodajbi(vector<CApteka>& data)
{
	vector<CApteka> VecProdajbi; //ветор в, който да се добавят аптеките отговарящи на условията
	for (int i = 0; i < data.size(); i++) // цикъл който да обхожда всички аптеки
	{
	
		int getSales = data[i].getAptSales(); // гетър за броя продажби
		if (getSales > 10000) // ако отговаря на условието
		{
			VecProdajbi.push_back(data[i]); // аптеката се добавя в новия вектор
		}

	}

	vecaptdisplay(VecProdajbi); // извеждане на вектора с продажби над 10 000


}
void LowestProdajbi(vector<CApteka> data)
{
	if (data.empty()) //проверява дали вектора е празен
	{
		cout << "Няма налични аптеки." << endl;
		return;
	}
	CApteka min = data[0]; // взима първия елемент от вектора като мин
	
	for (int i = 1; i < data.size(); i++) //обхожда останалите елементи от вектора
	{
		if (min.getAptSales() > data[i].getAptSales()) // проверява дали мин е по-голямо от следващия елемент 
		{
			min = data[i]; // ако условието е true, присвоява на миин новата аптека
		}

	}
	min.aptdisplay(); // извежда данните за патеката с най-малък брой продажби
}
void AptekiSIztekulSrok(vector <CApteka> data)
{
	
	vector <CLekarstva> IztekliLekarstva; //временен вектор,който да съхранява изтеклите лекарства
	for (int i = 0; i < data.size(); i++) // цикъл, който обхожда вектора с аптеки
	{
		bool flag = false; // флаг следящ за това изпълнени ли са изискванията 
		vector <CLekarstva> tempVec; // временен вектор, в който се копират лекарствата от дадената аптека
		tempVec = data[i].getAptVec();
		

			for (int k = 0; k < tempVec.size(); k++)  // вектор, който обхожда вектора с лекарства
			{
				if ((!tempVec[k]) && (tempVec[k].getType() == 0)) // ако лекарството е изтекло и е от група 0 , флага се вдига и лекарството се добавя във вектора за изтекли лекарства
				{
					flag = true;
					IztekliLekarstva.push_back(tempVec[k]);
				}
				
			}


		if (flag == true) // ако флага е вдигнат, значи в конкретната аптека има изткло лекарство аналгетик
		{
			data[i].aptdisplay(); // извеждане на аптеката
			printVecLekarstva(IztekliLekarstva); // извеждане на изтеклите лекарства
			IztekliLekarstva.clear(); //изтрививане на елементите във вектора ,да е готов за следващата итерация
			cout << endl;
			cout << setfill('#') << setw(68) << "" << setfill(' ') << endl; // разделяне на редовете с 68 '#'
			cout << endl;
			flag = false; // сваляне на флага
		}
	}
}
void IzvejdaneNaLekarstvaVApteka(vector <CApteka> data, string name)
{
	vector <CLekarstva> tempLek; //временен вектор за лекраствата
	for (int i = 0; i < data.size(); i++) // цикъл, който обхожда аптеките
	{
		if (name == data[i].getAptName()) //ако въведеното име от потребителя съвпада с име от съществуващите аптеки
		{
			tempLek = data[i].getAptVec(); //извличане на вектора с лекарства във временния tempLek
			printVecLekarstva(tempLek); // извеждане на лекарствата във временния вектор

		}

	}
}
void vecaptdisplay(vector <CApteka> apteki)
{
	cout << setfill('*') << setw(80) << "" << setfill(' ') << endl; // ред с 80 *

	cout << "| " << setw(20) << left << "Име на аптеката"
		<< "| " << setw(15) << "Брой лекарства"
		<< "| " << setw(20) << "Верига"
		<< "| " << setw(25) << "Доставчик"
		<< "| " << setw(10) << "Продажби" << " |" << endl; // заглавен ред
	
	cout << setfill('*') << setw(80) << "" << setfill(' ') << endl;  // ред с 80 '*'

	for (int i = 0; i < apteki.size(); i++)
	{
		cout << "| " << setw(15) << left << apteki[i].getAptName()
			<< "| " << setw(14) << apteki[i].getAptVec().size()
			<< "| " << setw(14) << apteki[i].getAptChain()
			<< "| " << setw(16) << apteki[i].getAptDeliver()
			<< "| " << setw(8) << apteki[i].getAptSales() << " |" << endl; // извеждане на аптека на един ред 
		
		cout << setfill('-') << setw(80) << "" << setfill(' ') << endl; // разделяне на редовете с 80 '-'
	}
	cout << setfill('*') << setw(80) << "" << setfill(' ') << endl; // // ред с 80 '*'

}

