#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <stdlib.h>     /* srand, rand */
#include <time.h> //chasovnika
#include "clekarstva.h"
#include "capteka.h"
#include "cdate.h"

using namespace std;

void OutFile(const CLekarstva& fTemp);
void InFile(vector<CLekarstva>& data);
void LekarstvaNad20meseca(vector <CLekarstva>& data);
void RandomLekarstva(vector <CLekarstva>& data, vector <CLekarstva>& data1, vector <CLekarstva>& data2, vector <CLekarstva>& data3);
void SortByDeliver(vector<CApteka>& data);
void AddVecLekToApt(vector <CApteka>& VecApt, vector <CLekarstva>& data, vector <CLekarstva>& data1, vector <CLekarstva>& data2, vector <CLekarstva>& data3);
void GodniLekarstvaPoVuvedenaData(vector <CLekarstva>& data);
void Menu();
void SubMenu1();
void SubMenu2();
void SubMenu3();
void SubMenu4();
void AddLekarstvo(vector <CLekarstva>& data);
void top3Apteki(vector <CApteka>& vec);



int main()
{
	vector <CLekarstva> data;
	vector <CLekarstva> data1;
	vector <CLekarstva> data2;
	vector <CLekarstva> data3;

	vector <CApteka> VecApteki;
	
	bool flag = false;
	int choice = 0;
	int choice2 = 0;
	//char ch;
	int SrokNaGodnostMonth = 0;

	string name;
	string name2;
	string tipove;
	int enter;

	CApteka::InFileApt(VecApteki); // четене на аптеките от файл
	InFile(data); // четене лекарства от файл към програмата
	RandomLekarstva(data, data1, data2, data3); // разпределяне на лекарствата на случаен принцип в различни вектори
	AddVecLekToApt(VecApteki, data, data1, data2, data3); // добавяне на случаен вектор по аптеките
	

	do {
		
		Menu();
		cout << "Въведи избор: ";
		cin >> choice;
		system("cls"); // Изчистване на конзолата преди всяка нова итерация

		switch (choice)
		{
		case 1: // Функции с извеждане

			do
			{
				SubMenu1(); // подменю 1
				cout << "Въведи избор: ";
				cin >> choice2;
				system("cls"); // Изчистване на конзолата преди всяка нова итерация

				switch (choice2)
				{
				case 1: // Извеждане на наличните аптеки

					vecaptdisplay(VecApteki);

					break;
				case 2: // Извеждане на всички лекарства 

					printVecLekarstva(data);

					break;
				case 3: // Извеждане на аптеките, които не предлагат определна група лекарства 

					if (VecApteki.size() < 1 || data.size() < 1) // проверка дали векторите са празни
					{
						cout << "Няма въведени данни за лекарства или аптеки." << endl;
						break;
					}

					cout << "Избери число от 0-7 за търсената група." << endl;
					for (int i = 0; i < 8; i++)
					{
						tipove = CoutType(i);
					
						cout << i << '.' << tipove << endl;
					} // извеждане на възможните групи, от които потребителят трябва да избере

					cin.ignore(); // игноиране на останали символи в потока
					cin >> enter; // променлиа за избора на потребителя
					CApteka::IzvejdaneSporedGrupaLekarstva(VecApteki, enter); // статична функция 
					break;
				case 4: // Извеждане на аптеките, които притежават аналгетици с изтекъл срок на годност 
					if (VecApteki.size() < 1 || data.size() < 1) //проверка дали векторите са празни
					{
						cout << "Няма въведени данни за лекарства или аптеки." << endl;
						break;
					}

					AptekiSIztekulSrok(VecApteki);

					break;
				case 5: // Извеждане на лекарства в дадена аптека, според въведено име
					cout << "Въведи името на аптеката, от която да бъдат изведени лекарствата: " << endl;
					for (int i = 0; i < VecApteki.size(); ++i)
					{
						name = VecApteki[i].getAptName();
						cout << left << setw(20) << name;
						if ((i + 1) % 2 == 0)
						{ // Нов ред за всяка втора аптека
							cout << endl;
						}
					} //извеждане на възможните избори, които може да направи потребителя

					cin.ignore(); // игноиране на останали символи в потока
					getline(cin, name); //прочитане на въведеното име на аптека от потребителя

					IzvejdaneNaLekarstvaVApteka(VecApteki, name);
					break;


				}

			} while (choice2 != 0); // при въвеждане на 0, излиза от цикъла и се връща в основното меню

			break;


		case 2: // Функции със сортиране

			do
			{
				SubMenu2();
				cout << "Въведи избор: ";
				cin >> choice2;
				system("cls"); // Изчистване на конзолата преди всяка нова итерация

				switch (choice2)
				{
				case 1: //Сортиране на аптеките по доставчици
					SortByDeliver(VecApteki);
					cout << "Аптеки са сортирани по доставчик" << endl;
					break;
				case 2: //Сортиране на лекарствата по цена
					SortiranePoCena(data);
					break;
				case 3: //Лекарства (аналгетици) със срок на годност над 20 месеца от днешната дата
					cout << "Лекарства (аналгетици) със срок на годност над 20 месеца от днешната дата" << endl;
					LekarstvaNad20meseca(data);

					break;
				case 4: //Проверка колко остава от срока на годност при ръчно въвеждане на дата
					GodniLekarstvaPoVuvedenaData(data);

					break;
				case 5:
					cout << "Проверка за разлика в цените при две въведени лекарства. " << endl;
					printVecLekarstva(data); // извеждане на наличните лекаарства от които потребителят трябва да избере

					cout << "Въведи имeто на първото лекарство: " << endl;
					cin.ignore(); // премахване на останали излишни символи в потока
					getline(cin, name);

					cout << "Въведи имeто на второто лекарство: " << endl;
					cin.ignore(); //  // премахване на останали излишни символи в потока
					getline(cin, name2);

					SravnenieLekarstva(data, name, name2);
					break;
				case 6: //  6. Сортиране на лекарствата по имена в низходящ ред
					SortCLekarstvaByName(data);
					break;


				}
			} while (choice2 != 0); // при въвеждане на 0, излиза от цикъла и се връща в основното меню

			break;

		case 3: // Функции с продажби

			do
			{
				SubMenu3();
				cout << "Въведи избор: ";
				cin >> choice2;
				system("cls"); // Изчистване на конзолата преди всяка нова итерация

				switch (choice2)
				{
				case 1: //Аптеки с над 10000 продажби
					cout << "Аптеки с над 10 000 продажби" << endl;
					if (VecApteki.empty()) //проверка дали е празен вектора 
					{
						cout << "Няма въведени данни за аптеки." << endl;
					}

					Prodajbi(VecApteki);
					break;
				case 2: // Аптека с най-малко продажби
					LowestProdajbi(VecApteki);
					break;
				case 3: // Извеждане на 3-те аптеки с най-голям брой продажби

					top3Apteki(VecApteki);

					break;
				}
			} while (choice2 != 0); // при въвеждане на 0, излиза от цикъла и се връща в основното меню

			break;
		case 4: // Функции с добавяне
			do
			{
				SubMenu4();
				cout << "Въведи избор: ";
				cin >> choice2;
				system("cls"); // Изчистване на конзолата преди всяка нова итерация

				switch (choice2)
				{
				case 1: //Добавяне на лекарство
					AddLekarstvo(data);
					break;
				case 2: //Добавяне на аптека
					AddApteka(VecApteki);
					break;

				}
			} while (choice2 != 0); // при въвеждане на 0, излиза от цикъла и се връща в основното меню
			break;
		}
		
	} while (choice != 0); // при въвеждане на 0, излиза от цикъла и затваря програмата

	return 0;

	}



	void OutFile(const CLekarstva& fTemp)
	{
		ofstream fileObj; //файлов поток
		fileObj.open("Input.txt", ios::app); //отваряне на края на файла за запис

		if (!(fileObj.is_open())) // проверка за правилно отваряне
		{
			cout << "Проблем при отварянето на файла." << endl;
		}

		string all; // деклариране на временни променливи

		CLekarstva prob(fTemp);
		string getName;
		type getType;
		int getDATEY;
		int getDATEM;
		double getPrice;
		string typeLekarstvo;

		getName = prob.get_CLekarstvaName(); //сетъри за данните от временния оебкт ,който е подаден като параметър
		getType = prob.getType();
		getDATEY = prob.getDateY();
		getDATEM = prob.getDateM();
		getPrice = prob.getPrice();

		string a = to_string(getType); //обръщането им в стрингови променливи
		string b = to_string(getDATEM);
		string c = to_string(getDATEY);
		string d = to_string(getPrice);

		all = getName + ":" + a + ":" + b + ":" + c + ":" + d + "\n"; // конкатенация на всички променливи ,но разделение с двоеточие
		fileObj << all; // записване на конкатенирания стринг във файла
		fileObj.close(); // затваряне на файловия поток


		if (fileObj.is_open()) // проверка за правилно затваряне
		{
			cout << "Проблем със затварянето на файла." << endl;
		}


	}
	void InFile(vector<CLekarstva>& data)
	{
		ifstream file; // файлов поток

		file.open("Input.txt", ios::in); //отваряне на файл Input.txt за четене
	
		string line; // стрингова променлива в която да се чете цял ред информация за конкретно лекарство

		while (getline(file, line)) { // Четем всеки ред от файла
			size_t pos1 = line.find(':'); // Намиране на първата позиция на двоеточието
			if (pos1 != string::npos) {
				size_t pos2 = line.find(':', pos1 + 1); // Намиране на втората позиция на двоеточието
				if (pos2 != string::npos) {
					size_t pos3 = line.find(':', pos2 + 1); // Намиране на третата позиция на двоеточието
					if (pos3 != string::npos) {
						size_t pos4 = line.find(':', pos3 + 1); // Намиране на четвъртата позиция на двоеточието
						if (pos4 != string::npos) {

							string str1 = line.substr(0, pos1); // Извличане на първи стринг
							string str2 = line.substr(pos1 + 1, pos2 - pos1 - 1); // Извличане на втори стринг
							string str3 = line.substr(pos2 + 1, pos3 - pos2 - 1); // Извличане на трети стринг
							string str4 = line.substr(pos3 + 1, pos4 - pos3 - 1); // Извличане на четвърти стринг
							string str5 = line.substr(pos4 + 1); // Извличане на пети стринг

							string setName = str1; 
							int settypeLekarstvo = stoi(str2); // Cast-ване на стринговете в числови променливи
							int setDATEM = stoi(str3);
							int setDATEY = stoi(str4);
							double setPrice = stod(str5);

							CLekarstva* p = new CLekarstva(setName, setDATEM, setDATEY, setPrice, settypeLekarstvo); // създване на обект с наличната информация
							data.push_back(*p); // добавяне към вектора на обекта
							delete p; // изтриване на временния обект
							
						}
					}
				}
			}
		}


		file.close();

	}

	void LekarstvaNad20meseca(vector <CLekarstva>& data)
	{
		vector <CLekarstva> temp;
		int count = 0;
		int m = 0;

		for (int i = 0; i < data.size(); i++)
		{
			data[i].TillExpDate(m, 0, 0);
			if ( (m >= 20) && (data[i].getType() == 0))
			//if ((m >= 20))
			{
				temp.push_back(data[i]);
				m = 0;
			}
			m = 0;
		}

		// Заглавия на колоните
		cout << std::left << std::setw(20) << "| Име на лекарството | "
			<< std::setw(15) << "Вид на лекарството | "
			<< std::setw(10) << "Срок на годност |"
			<< std::setw(10) << "Цена |"
			<< std::endl;


		for (int i = 0; i < temp.size(); i++)
		{
			temp[i].potok(cout);
		}

		count = temp.size();
		cout << '\n' << "Брой аналгетици със срок на годност над 20 месеца: " << count << endl;
	}
	void RandomLekarstva(vector <CLekarstva>& data, vector <CLekarstva>& data1, vector <CLekarstva>& data2, vector <CLekarstva>& data3)
	{
	
		srand(time(0)); //инициализиране на генератора на случайни числа , time(0) връща времето в секунди от 1 януари 1970 година насам

		for (int i = 0; i < data.size(); i++)
		{

			int x = rand() % 10; // генерира случайно число в интервала 0 - 10

			if (x < 3) // ако числото е по-малко от 3 лекарството се добавя във вектор data1
			{
				data1.push_back(data[i]);
			}
			else if (x > 3 && x < 7) // ако числото е по-голямо от 3 е по-малко от 7 лекарството се добавя във вектор data2
			{
				data2.push_back(data[i]);
			}
			else // ако числото е по-голямо от 6  лекарството се добавя във вектор data3
			{
				data3.push_back(data[i]);
			}

		}
	}
	void SortByDeliver(vector<CApteka>& data)
	{
		sort(data.begin(), data.end(), [](CApteka& l, CApteka& r)
			{
				return (l.getAptDeliver() < r.getAptDeliver());
			});
	}
	void AddVecLekToApt(vector <CApteka>& VecApt, vector <CLekarstva>& data, vector <CLekarstva>& data1, vector <CLekarstva>& data2, vector <CLekarstva>& data3)
	{
		for (int i = 0; i < VecApt.size(); i++)
		{
			int x = rand() % 4 + 1; // генерира числа от 1 до 4
			if (x == 1) //ако генерираното число е равно на 1, вектора със всички лекарства се подава на аптеката [i]
			{
				VecApt[i].set_CAptekaVecLekarstva(data);
			}
			else if (x == 2) //ако генерираното число е равно на 2, вектора data1 се подава на аптеката [i]
			{
				VecApt[i].set_CAptekaVecLekarstva(data1);
			}
			else if (x == 3) //ако генерираното число е равно на 3, вектора data2 се подава на аптеката [i]
			{
				VecApt[i].set_CAptekaVecLekarstva(data2);
			}
			else //ако не влезе в никой от другите ифове, вектора data3 се подава на аптеката [i]
			{
				VecApt[i].set_CAptekaVecLekarstva(data3);
			}

		}

	}

	void GodniLekarstvaPoVuvedenaData(vector <CLekarstva>& data)
	{

		int m = 1; // променлива, която указва на функцията TillExpDate какво трябва да извърши 
		int year = 0;
		int month = 0;

		cout << "Въведи желаната година: (пример: 2025)" << endl;
		cin >> year;
		cout << "Въведи желания месец:  (пример: 3)" << endl;
		cin >> month;

		for (int i = 0; i < data.size(); i++)
		{
			data[i].TillExpDate(m, year, month); //функцията която изчислява месеците се извиква за всяко лекарство
			if ((m > 0)) //ако то ще е в срок в зависимост от въведената дата се извежда името и оставащите месеци
			{
				cout << "До изтичането на срока на годност на лекарство ";
				cout << data[i].get_CLekarstvaName() << " остават: " << m << " месеца. " << endl;
			}
		}

	}
	void Menu()
	{
		cout << setfill('*') << setw(30) << "" << setfill(' ') << endl;
		cout << "* 1. Функции с извеждане   *" << endl;
		cout << "* 2. Фунцкии със сортиране *" << endl;
		cout << "* 3. Функции с продажби    *" << endl;
		cout << "* 4. Функция с добавяне    *" << endl;
		cout << setfill('*') << setw(30) << "" << setfill(' ') << endl; // като го няма втория сетфилл и ендл не работи
	}
	void SubMenu1()
	{
		cout << setfill('*') << setw(100) << "" << setfill(' ') << endl;
		cout << "1. Извеждане на наличните аптеки." << endl;
		cout << "2. Извеждане на всички лекарства" << endl;
		cout << "3. Извеждане на аптеките, които не предлагат определена група лекарства" << endl;
		cout << "4. Извеждане на аптеките, които притежават аналгетици с изтекъл срок на годност. " << endl;
		cout << "5. Извеждане на лекарства в дадена аптека, според въведено име. " << endl;
		cout << "0. Връщане в главното меню" << endl;
		cout << setfill('*') << setw(100) << "" << setfill(' ') << endl; // като го няма втория сетфилл и ендл не работи
	}
	void SubMenu2()
	{
		cout << setfill('*') << setw(100) << "" << setfill(' ') << endl;
		cout << "1. Сортиране на аптеките по доставчици " << endl;
		cout << "2. Сортиране на лекарствата по цена" << endl;
		cout << "3. Лекарства(аналгетици) с оставащ срок на годност над 20 месеца" << endl;
		cout << "4. Проверка колко остава от срока на годност при ръчно въвеждане на дата" << endl;
		cout << "5. Проверка за разлика в цените при две въведени лекарства" << endl;
		cout << "6. Сортиране на лекарствата по имена в низходящ ред" << endl;
		cout << "0. Връщане в главното меню" << endl;
		cout << setfill('*') << setw(100) << "" << setfill(' ') << endl; 
	}
	void SubMenu3()
	{
		cout << setfill('*') << setw(100) << "" << setfill(' ') << endl;
		cout << "1. Аптеки с над 10 000 продажби." << endl;
		cout << "2. Аптека с най-малко продажби." << endl;
		cout << "3. Извеждане на 3-те аптеки с най-голям брой продажби." << endl;
		cout << "0. Връщане в главното меню" << endl;
		cout << setfill('*') << setw(100) << "" << setfill(' ') << endl; // като го няма втория сетфилл и ендл не работи
	}
	void SubMenu4()
	{
		cout << setfill('*') << setw(100) << "" << setfill(' ') << endl;
		cout << "1. Добавяне на лекарство" << endl;
		cout << "2. Добавяне на аптека" << endl;
		cout << "0. Връщане в главното меню" << endl;
		cout << setfill('*') << setw(100) << "" << setfill(' ') << endl; 
	}



	void AddLekarstvo(vector <CLekarstva>& data)
	{
		string tempName; // временни променливи, които да съхраняват данните за обекта 
		int tempType;
		int tempMonth;
		int tempYear;
		string tempInputPrice;
		double tempPrice;
		cout << "Въведи име на лекарство:";
		cin.ignore();
		getline(cin, tempName);

		do { //валидация на данни
			cout << "Въведи валиден срок на годност (месец (1-12)/година 20(00-99))" << endl;
			cout << "Месец: ";
			cin >> tempMonth;
			cout << "Година: ";
 			cin >> tempYear;
		} while ((tempMonth <= 0 || tempMonth > 12) || (tempYear <= 0 || tempYear > 99));

		do { // валидация на данни
			cout << "Избери тип:" << endl;
			cout << "1: Analgetics 2: Antibiotics 3: Food Additives" << endl;
			cout << "4:Drops 5:Syrop 6:Homeopathic 7:Undefined | Въведи число (1-7) " << endl;
			cin >> tempType;
		} while (tempType > 8 || tempType < 1);


		cout << "Въведи цена:";
		cin.ignore();
		cin >> tempInputPrice;

		for (char& c : tempInputPrice) {
			if (c == ',') {
				c = '.';
			}
		}

		tempPrice = stod(tempInputPrice);

		CLekarstva r(tempName, tempMonth, tempYear, tempPrice, tempType); // създаване на временен обект
		data.push_back(r); //добавяне към вектора на вече съществуващите лекарства

		OutFile(r); // функция за добавяне на обекта към тесктовия файл
		
	}


	void top3Apteki(vector <CApteka>& vec)
	{
		
		vector <CApteka> copy = vec; // Създаване на копие на входния вектор 
		vector <CApteka> temp; // вектор, който ще съдържа трите аптеки с най-голям брой продажби
		
		CApteka max1; // Променливи, които ще съхраняват трите аптеки с най-голям брой продажби
		CApteka max2;
		CApteka max3;

		
		for (int i = 0; i < copy.size(); i++) // Обхождане на вектора 
		{
			
			if (max1.getAptSales() < copy[i].getAptSales()) // Проверка дали текущата аптека има повече продажби от max1
			{
			
				max3 = max2; // ако има аптеките се изместват с една нататък
				max2 = max1;
				max1 = copy[i];
			}
			
			else if (max2.getAptSales() < copy[i].getAptSales()) // проверка дали текущата аптека има повече продажби от max2, но по-малко от max1
			{
			
				max3 = max2; //изместване с една нататък 
				max2 = copy[i]; // като текущата се присвоява на max2
			}
			
			else if (max3.getAptSales() < copy[i].getAptSales()) // Проверка дали текущата аптека има повече продажби от max3, но по-малко от max2
			{
				max3 = copy[i]; // Присвояване на текущата аптека към max3
			}
		}

		// Добавяне на трите аптеки с най-голям брой продажби към вектора temp
		temp.push_back(max1);
		temp.push_back(max2);
		temp.push_back(max3);

		vecaptdisplay(temp); // Извеждане на информацията за трите аптеки
	}



