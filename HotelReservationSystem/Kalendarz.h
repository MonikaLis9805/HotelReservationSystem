#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include <windows.h>
#include <winbase.h>
#include <conio.h>


using namespace std;

class Kalendarz
{
private:
	int m_dzien;
	int m_miesiac;
	int m_rok;

public:
	Kalendarz(int dzien = 100, int miesiac = 100, int rok = 100) : m_dzien{ dzien }, m_miesiac{ miesiac }, m_rok{ rok }
	{}

	int get_dzien(void) { return m_dzien; }
	int get_miesiac(void) const { return m_miesiac; }
	int get_rok(void) const { return m_rok; }

	void set_dzien(int dzien) { m_dzien = dzien; }
	void set_miesiac(int miesiac) { m_miesiac = miesiac; }
	void set_rok(int rok) { m_rok = rok; }

	friend ostream& operator<<(ostream& wyjscie, Kalendarz& k1);
	friend bool operator==(const Kalendarz& d1, const Kalendarz& d2);

	friend bool operator <(const Kalendarz& data1, const Kalendarz& data2);
	friend bool operator >(const Kalendarz& data1, const Kalendarz& data2);

};

