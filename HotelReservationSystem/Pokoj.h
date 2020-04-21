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
#include "Kalendarz.h"
#include "Rezerwacja.h"

using namespace std;



class Pokoj
{
private:
	int m_nr_pokoju;
	int m_liczba_osob;
	vector<Rezerwacja> wektor_rezerwacji;

public:
	Pokoj(int nr_pokoju = 2, int liczba_osob = 1) :m_nr_pokoju{ nr_pokoju }, m_liczba_osob{ liczba_osob }
	{}

	int get_nr_pokoju(void) const { return m_nr_pokoju; }
	void set_nr_pokoju(int nr_pokoju) { m_nr_pokoju = nr_pokoju; }
	int get_liczba_osob(void) const { return m_liczba_osob; }
	void set_liczba_osob(int liczba_osob) { m_liczba_osob = liczba_osob; }
	friend ostream& operator<<(ostream& wyj, const Pokoj& pp);
	//friend ostream& operator<<(ostream& wyj, const Rezerwacja& r);

	void wyswietl_rezerwacje(Pokoj p)
	{
		vector<Rezerwacja> pomocniczy;

		pomocniczy = p.zaladuj_rezerwacje();

		ifstream rezerwacje("C:\\Users\\MONIKA\\Desktop\\Hotel reservation system\\rezerwacje.txt");

		string wpisany_nr_rezerwacji = " ";
		string linia_tekstu10;
		int k = 0;

		while (wpisany_nr_rezerwacji.size() != 13)
		{
			cout << "wpisz swoj numer rezerwacji" << endl;
			cin >> wpisany_nr_rezerwacji;

			if (wpisany_nr_rezerwacji.size() != 13)
			{
				cout << "Bledny numer rezerwacji, powinien zawierac 13 znakow" << endl;
			}
			else
				break;
		}

		for (int i = 0; i < pomocniczy.size(); i++)
		{
			if (pomocniczy[i].get_nr_rezerwacji() == wpisany_nr_rezerwacji)
			{
				system("cls");
				cout << endl;
				cout << endl;
				cout << "znaleziono rezerwacje dla numeru " << wpisany_nr_rezerwacji << endl;
				cout << endl;
				cout << "szczegoly rezerwacji:" << endl;
				cout << endl;
				cout << "Nazwa hotelu: " << pomocniczy[i].get_nazwa_hotelu() << endl;
				cout << "Numer pokoju: " << pomocniczy[i].get_nr_pokoju() << endl;
				cout << "Miasto: " << pomocniczy[i].get_nazwa_miasta() << endl;
				cout << "Imie: " << pomocniczy[i].get_imie() << endl;
				cout << "Nazwisko: " << pomocniczy[i].get_nazwisko() << endl;
				cout << "Adres email: " << pomocniczy[i].get_email() << endl;
				cout << "Numer dowodu/paszportu: " << pomocniczy[i].get_nr_ID() << endl;
				cout << "Telefon kontaktowy: " << pomocniczy[i].get_nr_tel() << endl;
				k++;
			}
		}

		if (k == 0)
		{
			cout << "brak rezerwacji o podanym numerze" << endl;
		}

	}

	string generowanie_nr_rezerwacji(string nr_ID)
	{
		srand(time(NULL));
		int random = (rand() % 9000) + 1000;
		string random_pokonwersji = to_string(random);
		string a_nr_rezerwacji = nr_ID + random_pokonwersji;
		cout << "Twoj numer rezerwacji to: " << a_nr_rezerwacji << ". Zapisz go!:)" << endl;
		return a_nr_rezerwacji;
	}

	vector<Rezerwacja> zaladuj_rezerwacje(void)
	{
		ifstream rezerwacje("C:\\Users\\MONIKA\\Desktop\\Hotel reservation system\\rezerwacje.txt");
		Pokoj p1;
		int nr_pokoju = 0;

		while (!rezerwacje.eof())
		{
			Rezerwacja r1;

			string linia_tekstu;
			getline(rezerwacje, linia_tekstu);

			if (linia_tekstu.size() > 0)
			{
				int pozycja1 = linia_tekstu.find("nr_rezerwacji", 0);
				if (pozycja1 >= 0)
				{
					int pozycjaA = linia_tekstu.find("{", pozycja1);
					int pozycjaB = linia_tekstu.find("}", pozycjaA);
					r1.set_nr_rezerwacji(linia_tekstu.substr(pozycjaA + 1, pozycjaB - pozycjaA - 1));
				}

				int pozycja2 = linia_tekstu.find("miasto", pozycja1);
				if (pozycja2 >= 0)
				{
					int pozycjaA = linia_tekstu.find("{", pozycja2);
					int pozycjaB = linia_tekstu.find("}", pozycjaA);
					r1.set_nazwa_miasta(linia_tekstu.substr(pozycjaA + 1, pozycjaB - pozycjaA - 1));
				}
				int pozycja3 = linia_tekstu.find("hotel", pozycja2);
				if (pozycja3 >= 0)
				{
					int pozycjaA = linia_tekstu.find("{", pozycja3);
					int pozycjaB = linia_tekstu.find("}", pozycjaA);
					r1.set_nazwa_hotelu(linia_tekstu.substr(pozycjaA + 1, pozycjaB - pozycjaA - 1));
				}


				int pozycja4 = linia_tekstu.find("nr_pokoju", pozycja3);
				if (pozycja4 >= 0)
				{
					int pozycjaA = linia_tekstu.find("{", pozycja4);
					int pozycjaB = linia_tekstu.find("}", pozycjaA);
					string pomocniczy_nr_pokoju = linia_tekstu.substr(pozycjaA + 1, pozycjaB - pozycjaA - 1);
					int nr_pokoju = stoi(pomocniczy_nr_pokoju, nullptr, 10);
					r1.set_nr_pokoju(nr_pokoju);
				}
				int pozycja5 = linia_tekstu.find("liczba_osob", pozycja4);
				if (pozycja5 >= 0)
				{
					int pozycjaA = linia_tekstu.find("{", pozycja5);
					int pozycjaB = linia_tekstu.find("}", pozycjaA);
					string pomocnicza_liczba_osob = linia_tekstu.substr(pozycjaA + 1, pozycjaB - pozycjaA - 1);
					int liczba_osob = stoi(pomocnicza_liczba_osob, nullptr, 10);
					r1.set_liczba_osob(liczba_osob);
				}



				int pozycja6 = linia_tekstu.find("imie", pozycja5);
				if (pozycja6 >= 0)
				{
					int pozycjaA = linia_tekstu.find("{", pozycja6);
					int pozycjaB = linia_tekstu.find("}", pozycjaA);
					r1.set_imie(linia_tekstu.substr(pozycjaA + 1, pozycjaB - pozycjaA - 1));
				}

				int pozycja7 = linia_tekstu.find("nazwisko", pozycja6);
				if (pozycja7 >= 0)
				{
					int pozycjaA = linia_tekstu.find("{", pozycja7);
					int pozycjaB = linia_tekstu.find("}", pozycjaA);
					r1.set_nazwisko(linia_tekstu.substr(pozycjaA + 1, pozycjaB - pozycjaA - 1));
				}

				int pozycja8 = linia_tekstu.find("od", pozycja7);
				if (pozycja8 >= 0)
				{
					int pozycjaA = linia_tekstu.find("{", pozycja8);
					int pozycjaB = linia_tekstu.find("}", pozycjaA);
					r1.set_poczatek_rezerwacji(linia_tekstu.substr(pozycjaA + 1, pozycjaB - pozycjaA - 1));
				}

				int pozycja9 = linia_tekstu.find("do", pozycja8);
				if (pozycja9 >= 0)
				{
					int pozycjaA = linia_tekstu.find("{", pozycja9);
					int pozycjaB = linia_tekstu.find("}", pozycjaA);
					r1.set_koniec_rezerwacji(linia_tekstu.substr(pozycjaA + 1, pozycjaB - pozycjaA - 1));
				}

				int pozycja10 = linia_tekstu.find("email", pozycja9);
				if (pozycja10 >= 0)
				{
					int pozycjaA = linia_tekstu.find("{", pozycja10);
					int pozycjaB = linia_tekstu.find("}", pozycjaA);
					r1.set_email(linia_tekstu.substr(pozycjaA + 1, pozycjaB - pozycjaA - 1));
				}

				int pozycja11 = linia_tekstu.find("nr_ID", pozycja10);
				if (pozycja11 >= 0)
				{
					int pozycjaA = linia_tekstu.find("{", pozycja11);
					int pozycjaB = linia_tekstu.find("}", pozycjaA);
					r1.set_nr_ID(linia_tekstu.substr(pozycjaA + 1, pozycjaB - pozycjaA - 1));
				}

				int pozycja12 = linia_tekstu.find("nr telefonu", pozycja11);
				if (pozycja12 >= 0)
				{
					int pozycjaA = linia_tekstu.find("{", pozycja12);
					int pozycjaB = linia_tekstu.find("}", pozycjaA);
					string pomocniczy_nr_tel = linia_tekstu.substr(pozycjaA + 1, pozycjaB - pozycjaA - 1);
					int nr_tel = stoi(pomocniczy_nr_tel, nullptr, 10);
					r1.set_nr_tel(nr_tel);
				}

				string pompocz = r1.get_poczatek_rezerwacji();
				string pomkon = r1.get_koniec_rezerwacji();

				if (pozycja1 >= 0)
				{
					r1.set_dlugosc_pobytu(r1.tworzenie_wektoru_dlugosci_pobytu(pompocz, pomkon));

				}

				wektor_rezerwacji.push_back(r1);
			}
		}

		return wektor_rezerwacji;
	}

	void dodaj_rezerwacje(int liczba_osob, int nr_pokoju, string nazwa_miasta, string& poczatek_rezerwacji, string& koniec_rezerwacji, string& imie, string& nazwisko, string& email, string& nr_ID, int& nr_tel, string nazwa_hotelu, Pokoj p)
	{
		Rezerwacja r;

		fstream rezerwacje("C:\\Users\\MONIKA\\Desktop\\Hotel reservation system\\rezerwacje.txt", ios::in | ios::out | ios::app);

		wektor_rezerwacji.clear();
		wektor_rezerwacji = p.zaladuj_rezerwacje();

		int licznik = 0;
		vector <Kalendarz> pomocniczy;
		vector <Kalendarz> daaty;

		while (true)
		{
			cout << "podaj miasto, w ktorym chcesz zarezerwowac pokoj" << endl;
			cin >> nazwa_miasta;
			cout << "podaj nazwe hotelu, w ktorym chcesz zarezerwowac pokoj" << endl;
			cin >> nazwa_hotelu;
			cout << "podaj nr pokoju" << endl;
			cin >> nr_pokoju;

			daaty = r.wprowadzanie_dat(poczatek_rezerwacji, koniec_rezerwacji);

			for (int i = 0; i < wektor_rezerwacji.size(); i++)
			{
				pomocniczy.clear();

				if ((wektor_rezerwacji[i].get_nazwa_miasta() == nazwa_miasta) && (wektor_rezerwacji[i].get_nazwa_hotelu() == nazwa_hotelu) && (wektor_rezerwacji[i].get_nr_pokoju() == nr_pokoju))
				{
					pomocniczy = wektor_rezerwacji[i].get_dlugosc_pobytu();

					for (int j = 0; j < pomocniczy.size(); j++)
					{
						if ((pomocniczy[j] == daaty[0]) || (pomocniczy[j] == daaty[1]) || (daaty[0]< pomocniczy[j] && daaty[1]>pomocniczy[pomocniczy.size() - 1]))
						{
							cout << "Nie mozna dokonac rezerwacji w tym terminie. Pokoj niedostepny" << endl;
							licznik++;
						}

						if (licznik == 1)
						{
							break;
						}
					}
				}
			}

			if (licznik == 0)
			{
				break;
			}
		}

		string pompdzien = to_string(daaty[0].get_dzien());
		if (pompdzien.size() == 1)
		{
			pompdzien = "0" + pompdzien;
		}
		string pompmiesiac = to_string(daaty[0].get_miesiac());
		if (pompmiesiac.size() == 1)
		{
			pompmiesiac = "0" + pompmiesiac;
		}
		string pomprok = to_string(daaty[0].get_rok());

		string pomkdzien = to_string(daaty[1].get_dzien());
		if (pomkdzien.size() == 1)
		{
			pomkdzien = "0" + pomkdzien;
		}
		string pomkmiesiac = to_string(daaty[1].get_miesiac());
		if (pomkmiesiac.size() == 1)
		{
			pomkmiesiac = "0" + pomkmiesiac;
		}
		string pomkrok = to_string(daaty[1].get_rok());

		poczatek_rezerwacji = pompdzien + "." + pompmiesiac + "." + pomprok;
		koniec_rezerwacji = pomkdzien + "." + pomkmiesiac + "." + pomkrok;

		cout << "podaj ilosc osob w pokoju" << endl;
		cin >> liczba_osob;
		cout << "podaj swoje imie" << endl;
		cin >> imie;
		cout << "podaj nazwisko" << endl;
		cin >> nazwisko;
		cout << "podaj swoj adres email" << endl;
		cin >> email;

		while (true)
		{
			cout << "wpisz numer dowodu lub paszportu. Numer powienien zawierac 9 znakow" << endl;
			cin >> nr_ID;

			if (nr_ID.size() != 9)
			{
				cout << "Bledny numer. Powonien zawierac 9 znakow!" << endl;
			}
			else
			{
				break;
			}
		}

		cout << "podaj numer telefonu kontaktowego" << endl;
		cin >> nr_tel;

		r.set_nazwa_miasta(nazwa_miasta);
		r.set_nazwa_hotelu(nazwa_hotelu);
		r.set_nr_pokoju(nr_pokoju);
		r.set_poczatek_rezerwacji(poczatek_rezerwacji);
		r.set_koniec_rezerwacji(koniec_rezerwacji);
		r.set_liczba_osob(liczba_osob);
		r.set_imie(imie);
		r.set_nazwisko(nazwisko);
		r.set_email(email);
		r.set_nr_ID(nr_ID);
		r.set_nr_tel(nr_tel);
		string nr_rezerwacji = generowanie_nr_rezerwacji(nr_ID);
		r.set_nr_rezerwacji(nr_rezerwacji);

		wektor_rezerwacji.push_back(r);

		rezerwacje << "\n";
		rezerwacje << "nr_rezerwacji: {" << r.get_nr_rezerwacji() << "} miasto: {" << r.get_nazwa_miasta() << "} hotel: {" << r.get_nazwa_hotelu() << "} nr_pokoju: {" << r.get_nr_pokoju() << "} liczba_osob: {" << r.get_liczba_osob() << "} imie: {" << r.get_imie() << "} nazwisko: {" << r.get_nazwisko() << "} od: {" << r.get_poczatek_rezerwacji() << "} do: {" << r.get_koniec_rezerwacji() << "} email: {" << r.get_email() << "} nr_ID: {" << r.get_nr_ID() << "} nr telefonu: {" << r.get_nr_tel() << "}";

	}

};

