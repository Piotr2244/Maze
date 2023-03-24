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

	cout << "wybierz klasê:" << endl << endl << "----------" << endl;
	cout << "Wojownik" << endl << "Punkty ¿ycia: 12" << endl << "Si³a: 10" << endl << "Szczêœcie: 1" << endl<<"----------"<<endl;
	cout << "Czarodziej" << endl << "Punkty ¿ycia: 7" << endl << "Si³a: 12" << endl << "Szczêœcie: 2" << endl<<"----------"<<endl;
	cout << "£otr" << endl << "Punkty ¿ycia: 9" << endl << "Si³a: 8" << endl << "Szczêœcie: 3" << endl<<"----------"<<endl;

	cout << "Wybierz Wojownika: 1" << endl << "Wybierz Czarodzieja: 2" << endl << "Wybierz £otra: 3" << endl;
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
				SetStats(9, 8, 3, "£otr");
				f = true;
				break;
			}
			default:
			{
				cout << "Nieprawid³owy numer" << endl;
				
			}
		}

		
	}

	regex nonumber("((\\w*)[0-9]+(\\w*))");


	n = "bohaterek";
	bool done = false;
	getline(cin, n);
	while (done == false)
	{
		cout << "Podaj imiê swojego bohatera:" << endl;
		
		getline(cin, n);
		bool a = regex_match(n, nonumber);
		if (a == true)cout << "Nazwa bohatera nie powinna zawieraæ cyfr" << endl;	
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
	cout << "Si³a: " << STR << endl;
	cout << "Wytrzyma³oœæ: " << HP << endl;
	cout << "Szczêœcie: " << LCK << endl;
	cout << "Z³oto: " << GOLD<<" monet" << endl;
	cout << "--------------------" << endl;
}

/**
* Metoda wyswietla instrukcje gry
* */
void Howtoplay()
{
	system("CLS");
	cout << "Gra polega na pokonywaniu kolejnych komnat labiryntu." << endl;
	cout << "Na pocz¹tku gry tworzysz swojego bohatera, który nastêpnie bêdzie przeprawia³ siê przez labirynt." << endl;
	cout << "Labirynt sk³ada siê z korytarzy i komnat, które wystêpuj¹ przemiennie." << endl;
	cout << "W korytarzach wystêpuj¹ rozwidlenia na których gracz wybiera kierunek podró¿y." << endl;
	cout << "W Komnatach napotkaæ przeciwników, zdobyæ skarby oraz napotkaæ ró¿norakie przygody" << endl;
	cout << "Gracz steruje bohaterem poprzez naciskanie wybranych cyfr i zatwierdzanie ich enterem." << endl;
	cout << "Gracz bêdzie proszony o wykonanie powy¿szych akcji w momencie kiedy wyst¹pi koniecznoœæ podejmowania decyzji." << endl;
	cout << "Bohater posiada okreœlone punkty wytrzyma³oœci. Gra trwa do czasu a¿ spadn¹ one do zera." << endl;
	cout << "Bohater posiada punty si³y, podczas walki z przeciwnikami, si³a bohatera jest porównywana z si³¹ przeciwnika." << endl;
	cout << "Do obu wartoœci dodawany jest wynik rzutu kostk¹. Aby pokonaæ przeciwnika, wynik musi byæ wiêkszy lub równy od jego si³y." << endl;
	cout << "Walki mo¿na unikn¹æ poprzez wydanie punktów szczêœcia. Dziêki temu, bohater mo¿e unikaj¹c walki zabraæ skarby." << endl;
	cout << "Wynik koñcowy gracza okreœlany jest przez zgromadzone podczas przygody z³oto." << endl;
	cout << "MI£EJ ZABAWY!" << endl;
	cout << "naciœnij enter by kontynuowaæ" << endl<<endl;
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
	Printdch("Tego ju¿ by³o zbyt wiele dla dzielnego bohatera.  ");cout << endl;
	Sleep(3000);
	Printdch("Mimo nieopisanej wrêcz wytrwa³oœci, nie jesteœ ju¿ w stanie kontynuowaæ podró¿y.  ");cout << endl;
	Sleep(3000);
	Printdch("Ostatkiem si³ wstajesz na nogi i z dusz¹ na ramieniu uciekasz z labiryntu drog¹, któr¹ tutaj przyby³eœ.  ");cout << endl;
	Sleep(3000);
	Printdch("Twoja podró¿ dobieg³a koñca, jednak poza z³otem uda³o siê z niej wynieœæ coœ wiêcej...  ");cout << endl;
	Sleep(3000); Printdch("To coœ...  "); Sleep(1000); Printdch("to wspomnienie wspania³ej przygody.  ");cout << endl;
	Sleep(4000);
	cout << "naciœnij enter by kontynuowaæ" << endl;
	cin.ignore();
	cin.ignore();
	system("CLS");
	int x;
	bool done = false;
	cout << "Czy chcesz zapisaæ do pliku statystyki Twojego Bohatera?" << endl;
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
	plik << "Zebrane z³oto: " << GOLD << endl;
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
	cout <<"            Rozpocznij now¹ grê: 1   "<<endl;
	cout << "            Instrukcja jak graæ: 2   " << endl;
	cout << "            Wyjœcie z gry:       3      " << endl;
	int x;		
	cin >> x;
    if (!cin.good()) x=4;
    return x;
}