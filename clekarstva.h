#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include "cdate.h"

using namespace std;

enum type
{
	analgetics = 0,
	antibiotics = 1,
	foodAdditives = 2,
	drops = 3,
	syrop = 4,
	probiotic = 5,
	homeopathic = 6,
	undef = 7,
};

class CLekarstva
{
private:
	string name;
	type atype;
	CDate expDate;
	double price;

public:
	CLekarstva()
	{
		name = "empty";
		atype = type(7);
		expDate = CDate(0, 0);
		price = 0.0;

	};
	
	explicit CLekarstva(string n, int m, int y, double p, int type_num)
	{
		name = n;
		atype = set_CLekarstvaType2(type_num);
		expDate.set_CDateM(m);
		expDate.set_CDateY(y);
		price = p;

	}

	CLekarstva(const CLekarstva& t1)
	{
		name = t1.name;
		atype = t1.atype;
		expDate = t1.expDate;
		price = t1.price;
	}

	
	void set_CLekarstvaName(string n);
	void set_CLekarstvaCDate(int  m, int y);
	void set_CLekarstvaPrice(double p);
	void set_CLekarstvaType(int type_num);
	type set_CLekarstvaType2(int type_num);

	string get_CLekarstvaName();
	int getDateM();
	int getDateY();
	double getPrice();
	type getType();
	void display();
	void TillExpDate(int& MonthRes, int thy,int thm);
	
	//void SortCLekarstvaByName(vector <CLekarstva>& data);
	virtual bool Sravnenie(CLekarstva& a);
	virtual void potok(ostream& os);

	CLekarstva& operator = (const CLekarstva& obj);
	bool operator == (const CLekarstva& a);
	friend bool operator > (const CLekarstva& l, const CLekarstva& r);
	bool operator < (const CLekarstva& a);
	bool operator ! ()
	{
		int m = 0;
		TillExpDate(m,0,0);
		if (m < 0)
		{
			return true;
		}
		return false;
	
	}
	

	~CLekarstva()
	{

	};

};

string CoutType(int a);

bool CLekarstva::Sravnenie(CLekarstva& a)
{
	if (this->price == a.price)
	{
		return true;
	}
	else
		return false;
}

CLekarstva& CLekarstva::operator = (const CLekarstva& obj)
{
	
	name = obj.name;
	atype = obj.atype;
	expDate = obj.expDate;
	price = obj.price;
	return *this;
}
bool CLekarstva::operator < (const CLekarstva& a)
{
	return this->price < a.price;
}
bool operator > (const CLekarstva& l, const CLekarstva& r)
{
	return l.name > r.name;
}

bool CLekarstva::operator == (const CLekarstva& a)
{
	return (this->atype == a.atype);
}

void CLekarstva::potok(ostream& os)
{
	string type = CoutType(atype);
	int h = 0;
	if (expDate.get_CDateM() < 10)
	{
		h = 13;
	}
	else
	{
		h = 12;
	}
	os << std::left << std::setw(23) << name << std::setw(21) << type << expDate.get_CDateM() << "/" << expDate.get_CDateY() << std::setw(h) << ' ' 
		 << price << endl;
}

type CLekarstva::getType()
{
	return atype;
}
double CLekarstva::getPrice()
{
	return price;
}
string CLekarstva::get_CLekarstvaName()
{
	return name;
}
int CLekarstva::getDateM()
{
	int month;
	month = expDate.get_CDateM();
	return month;
}
int CLekarstva::getDateY()
{
	int year;
	year = expDate.get_CDateY();
	return year;
}

type CLekarstva::set_CLekarstvaType2(int type_num)
{
	if (type_num == 0)
	{
		return type::analgetics;
	}
	else if (type_num == 1)
	{
		return type::antibiotics;
	}
	else if (type_num == 2)
	{
		return type::foodAdditives;
	}
	else if (type_num == 3)
	{
		return type::drops;
	}
	else if (type_num == 4)
	{
		return type::syrop;
	}
	else if (type_num == 5)
	{
		return type::probiotic;
	}
	else if (type_num == 6)
	{
		return type::homeopathic;
	}
	else
	{
		return type::undef;
	}

}
void CLekarstva::set_CLekarstvaName(string n)
{
	this->name = n;

}
void CLekarstva::set_CLekarstvaCDate(int  m, int y)
{
	expDate.set_CDateM(m);
	expDate.set_CDateY(y);
}
void CLekarstva::set_CLekarstvaPrice(double p)
{
	this->price = p;
}
void CLekarstva::TillExpDate(int& MonthRes,int thy,int thm)
{
	int thisyear = 0;
	int thismonth = 0;
	tm newtime;
	time_t timenow = time(0);
	//Пример: cout << "Number of sec since January 1,1970 is:: " << now << endl;

	localtime_s(&newtime, &timenow);

	if (MonthRes == 0)
	{
		thisyear = 1900 + newtime.tm_year;
		thismonth = 1 + newtime.tm_mon;
	}
	else
	{
		thisyear = thy;
		thismonth = thm;
	}

		int LekarstvoYear = expDate.get_CDateY(); // взима годината от срока на годност на лекарството
		int LekarstvoMonth = expDate.get_CDateM(); // взима месеца от срока на годност на лекарството
		int tempY = 0; // временна променлива за година
		int tempM = 0; // временна променлива за месец
		int temp1 = 0; // временна променлива
		
		LekarstvoYear += 2000; // добавяне на 2000 към годината пр. 2024 = 20+2000
		if ((LekarstvoYear - thisyear) >= 0) // проверка дали е изтекла дадената година
		{
			tempY = LekarstvoYear - thisyear; // оставащи години
			tempM = LekarstvoMonth - thismonth; // оставащи месеци

			if (tempM < 0) // ако месеците са по-малко да заеме от годината
			{
				tempY--;
				tempM = (tempM + 12);
			}

			tempM += (tempY * 12); // обръщане на останалите в месеци
			
			MonthRes = tempM; // присвояване на изчислените оставащи месеци в променливата през която се връща резултата

			temp1 = tempM;
			temp1 = temp1 / 12;
			tempM = tempM - (temp1 * 12);
			//обръща месеците в години, ако се налага да се представят като години и месеци

		}
		else {
			// лекарството е изтекло
			MonthRes = -1;
		}
	
	
}
string CoutType(int a)
{
	if (a == 0)
	{
		return "Analgetics";
	}
	else if (a == 1)
	{
		return "Antibiotics";
	}
	else if (a == 2)
	{
		return "Food Additives";
	}
	else if (a == 3)
	{
		return "Drops";
	}
	else if (a == 4)
	{
		return "Syrop";
	}
	else if (a == 5)
	{
		return "Probiotic";
	}
	else if (a == 6)
	{
		return "Homeopathic";
	}
	else
	{
		return "Undefined";
	}
}
void printVecLekarstva(vector <CLekarstva>& data)
{
	cout << setfill('=') << setw(68) << "" << setfill(' ') << endl; // // ред с 80 '='
	cout << left << setw(20) << "|Name|" << setw(20) << "|Type|" << setw(18) << "|Exp. Date|" << setw(10) << "|Price|" << endl;
	cout << setfill('=') << setw(68) << "" << setfill(' ') << endl; // // ред с 80 '='
	

	int h = 0;

	for (int i = 0; i < data.size(); i++)
	{
		CLekarstva p = data.at(i);
	
		string getName = p.get_CLekarstvaName();
		type getType = p.getType();
		int getDATEY = p.getDateY();
		int getDATEM = p.getDateM();
		double getPrice = p.getPrice();
		string typeLekarstvo = CoutType(getType);

		if (getDATEM < 10) // ако месеца от срока на годност е едноцифрен
		{
			h = 9; // ширината между годината и цената ще е 9 
		}
		else
		{
			h = 8; // ширината между годината и цената ще е 8
		}
		
		cout << left << setw(20) << getName << setw(20) << typeLekarstvo << getDATEM << "/" << setw(8) << getDATEY << setw(h) << ' ' << fixed << setprecision(2) << getPrice << endl;

	}
	cout << setfill('=') << setw(68) << "" << setfill(' ') << endl; // // ред с 80 '='
	
}

void SravnenieLekarstva(vector <CLekarstva> data, string name1, string name2)
{
	CLekarstva temp1;
	CLekarstva temp2;

	for (int i = 0; i < data.size(); i++)
	{
		if (name1 == data[i].get_CLekarstvaName())
		{
			temp1 = data[i];
		}

	}

	for (int i = 0; i < data.size(); i++)
	{
		if (name2 == data[i].get_CLekarstvaName())
		{
			temp2 = data[i];
		}

	}

	if (temp1.Sravnenie(temp2))
	{
		cout << "Цените на лекарствата са равни" << endl;
	}
	else
	{
		cout << "Цените на лекарствата са различни" << endl;
	}

}
void SortiranePoCena(vector <CLekarstva>& data)
{
		sort(data.begin(), data.end(), [](CLekarstva& a, const CLekarstva& b) {
			return (a < b);
			});
}

void SortCLekarstvaByName(vector <CLekarstva>& data)
{
	sort(data.begin(), data.end(), [](const CLekarstva& a, const CLekarstva& b) {return (a > b); });
}

