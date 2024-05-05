#pragma once
#include <iostream>
#include <string>
using namespace std;

class CDate
{
private:
	int year;
	int month;
public:
	CDate()
	{
		year = 0;
		month = 0;
	}
	CDate(int a, int b)
	{
		year = a;
		month = b;
	}

	void set_CDateM(int m);
	void set_CDateY(int y);
	int get_CDateM();
	int get_CDateY();

	~CDate()
	{

	}
};



void CDate::set_CDateM(int  m)
{
	this->month = m;
}

void CDate::set_CDateY(int  y)
{
	this->year = y;
}

int CDate::get_CDateM()
{
	return month;
}

int CDate::get_CDateY()
{
	return year;
}


