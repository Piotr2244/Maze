#include <iostream>
#include <regex>
#include <windows.h>
#undef _HAS_STD_BYTE
#include "Hero.h"
using namespace std;

/**
* Metoda ustawia wprowadzone parametry jako statystyki bohatera
* */
void Hero::SetStats(int H, int S, int L, string P)
{
	HP = H;
	STR = S;
	LCK = L;
	PROF = P;
}
/**
* Metoda przeprowadza gracza przez proces tworzenia bohatera
* */
void Hero::CreateHero()
{
	system("cls");
	int x;

	cout << "wybierz klas�:" << endl << endl << "----------" << endl;
	cout << "Wojownik" << endl << "Punkty �ycia: 12" << endl << "Si�a: 10" << endl << "Szcz�cie: 1" << endl<<"----------"<<endl;
	cout << "Czarodziej" << endl << "Punkty �ycia: 7" << endl << "Si�a: 12" << endl << "Szcz�cie: 2" << endl<<"----------"<<endl;
	cout << "�otr" << endl << "Punkty �ycia: 9" << endl << "Si�a: 8" << endl << "Szcz�cie: 3" << endl<<"----------"<<endl;

	cout << "Wybierz Wojownika: 1" << endl << "Wybierz Czarodzieja: 2" << endl << "Wybierz �otra: 3" << endl;
	bool f = false;
	string n;
	
	while (f== false) 
	{
		cin >> x;
		if (!cin.good()) x = 1;
		
			switch (x)
		{
			case 1:
			{
				SetStats(12, 10, 1, "Wojownik");
				f = true;
				break;
			}
			case 2:
			{
				SetStats(7, 12, 2, "Czarodziej");
				f = true;
				break;
			}
			case 3:
			{
				SetStats(9, 8, 3, "�otr");
				f = true;
				break;
			}
			default:
			{
				cout << "Nieprawid�owy numer" << endl;
				
			}
		}

		
	}

	regex nonumber("((\\w*)[0-9]+(\\w*))");


	n = "bohaterek";
	bool done = false;
	getline(cin, n);
	while (done == false)
	{
		cout << "Podaj imi� swojego bohatera:" << endl;
		
		getline(cin, n);
		bool a = regex_match(n, nonumber);
		if (a == true)cout << "Nazwa bohatera nie powinna zawiera� cyfr" << endl;	
		else done = true;
	}
	NAME = n;
	system("cls");
}

/**
* Metoda kosmetyczna drukujaca wprowadzony tekst w konsoli z lekkim opoznieniem po kazdym znaku.
* */
void Hero::Printdch(string a)
{
	int stopper = 0;
	int counter = 0;
	while (stopper == 0)
	{
		cout << a[counter];
		counter++;
		Sleep(5);
		if (a[counter] == ' ' && a[counter + 1] == ' ') stopper++;
	}
}

/**
* Metoda wyswietlajaca panel z obecnymi statystykami bohatera
* */
void Hero::ShowHero()
{
	cout << "--------------------" << endl;
	cout << "     " << NAME << "     " << endl;
	cout << "Profesja: " << PROF << endl;
	cout << "Si�a: " << STR << endl;
	cout << "Wytrzyma�o��: " << HP << endl;
	cout << "Szcz�cie: " << LCK << endl;
	cout << "Z�oto: " << GOLD<<" monet" << endl;
	cout << "--------------------" << endl;
}

/**
* Metoda wyswietla instrukcje gry
* */
void Howtoplay()
{
	system("CLS");
	cout << "Gra polega na pokonywaniu kolejnych komnat labiryntu." << endl;
	cout << "Na pocz�tku gry tworzysz swojego bohatera, kt�ry nast�pnie b�dzie przeprawia� si� przez labirynt." << endl;
	cout << "Labirynt sk�ada si� z korytarzy i komnat, kt�re wyst�puj� przemiennie." << endl;
	cout << "W korytarzach wyst�puj� rozwidlenia na kt�rych gracz wybiera kierunek podr�y." << endl;
	cout << "W Komnatach napotka� przeciwnik�w, zdoby� skarby oraz napotka� r�norakie przygody" << endl;
	cout << "Gracz steruje bohaterem poprzez naciskanie wybranych cyfr i zatwierdzanie ich enterem." << endl;
	cout << "Gracz b�dzie proszony o wykonanie powy�szych akcji w momencie kiedy wyst�pi konieczno�� podejmowania decyzji." << endl;
	cout << "Bohater posiada okre�lone punkty wytrzyma�o�ci. Gra trwa do czasu a� spadn� one do zera." << endl;
	cout << "Bohater posiada punty si�y, podczas walki z przeciwnikami, si�a bohatera jest por�wnywana z si�� przeciwnika." << endl;
	cout << "Do obu warto�ci dodawany jest wynik rzutu kostk�. Aby pokona� przeciwnika, wynik musi by� wi�kszy lub r�wny od jego si�y." << endl;
	cout << "Walki mo�na unikn�� poprzez wydanie punkt�w szcz�cia. Dzi�ki temu, bohater mo�e unikaj�c walki zabra� skarby." << endl;
	cout << "Wynik ko�cowy gracza okre�lany jest przez zgromadzone podczas przygody z�oto." << endl;
	cout << "MI�EJ ZABAWY!" << endl;
	cout << "naci�nij enter by kontynuowa�" << endl<<endl;
	cin.ignore();
	cin.ignore();
	system("CLS");

}

/**
* Metoda wywolywana po utracie wszystkich punktow zycia przez bohatera.
* Przeprowadza ona gracza przez proces konczenia gry
* */
void Hero::Endgame()
{
	system("CLS");
	Printdch("Tego ju� by�o zbyt wiele dla dzielnego bohatera.  ");cout << endl;
	Sleep(3000);
	Printdch("Mimo nieopisanej wr�cz wytrwa�o�ci, nie jeste� ju� w stanie kontynuowa� podr�y.  ");cout << endl;
	Sleep(3000);
	Printdch("Ostatkiem si� wstajesz na nogi i z dusz� na ramieniu uciekasz z labiryntu drog�, kt�r� tutaj przyby�e�.  ");cout << endl;
	Sleep(3000);
	Printdch("Twoja podr� dobieg�a ko�ca, jednak poza z�otem uda�o si� z niej wynie�� co� wi�cej...  ");cout << endl;
	Sleep(3000); Printdch("To co�...  "); Sleep(1000); Printdch("to wspomnienie wspania�ej przygody.  ");cout << endl;
	Sleep(4000);
	cout << "naci�nij enter by kontynuowa�" << endl;
	cin.ignore();
	cin.ignore();
	system("CLS");
	int x;
	bool done = false;
	cout << "Czy chcesz zapisa� do pliku statystyki Twojego Bohatera?" << endl;
	cout << "Tak [1]" << endl << "Nie [2]" << endl;

	while (done == false)
	{
		cin >> x;
		if (!cin.good()) x = 3;
		switch (x)
		{
		case 1:
		{
			SaveStats();
			done = true;
			break;
		}
		case 2:
		{
			done = true;
			break;
		}
		default:
		{
			cout << "niepoprawny numer" << endl;
		}
		}
	}
}

/**
* Metoda zapisujaca statystyki bohatera do pliku tekstowego w katalogu znajdujacym sie w folderze programu
* */
void Hero::SaveStats()
{
	filesystem::path bohater{ "Bohater"};
	filesystem::create_directories(bohater);
	bohater.append("Statystyki bohatera.txt");
	ofstream plik(bohater);
	plik << "----- " << NAME << " -----" << endl;
	//
	plik << "Profesja: " << PROF << endl;
	plik << "Zebrane z�oto: " << GOLD << endl;
	plik << "Przebyte komnaty: " << TotalChambers << endl;
	plik << "Pokonani przeciwnicy: " << TotalEnemies << endl;
	

}


/**
* Metoda wyswietlajaca menu glowne i zwracajaca numer decydujacy o rozpoczeciu gry, wyswietleniu instrukcji lub o zamknieciu programu.
* */
int  MainMenu()
{
	system("CLS");
	cout <<"          ----------LABIRYNT----------" << endl;
	cout <<"            Rozpocznij now� gr�: 1   "<<endl;
	cout << "            Instrukcja jak gra�: 2   " << endl;
	cout << "            Wyj�cie z gry:       3      " << endl;
	int x;		
	cin >> x;
    if (!cin.good()) x=4;
    return x;
}