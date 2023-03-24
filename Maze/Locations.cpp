#include <iostream>
#include <Windows.h>
#undef _HAS_STD_BYTE
#include "Locations.h"
#include "Descriptions.h"


using namespace std;

/**
* Metoda zwraca losowa liczbe w zakresie od 0 do podanego parametru .
* */
int Location::random(int x)
{
	srand(time(NULL));
	return (rand() % x);

}

/**
* Metoda kosmetyczna drukujaca wprowadzony tekst w konsoli z lekkim opoznieniem po kazdym znaku.
* */
void Location::printdc(string a) //konieczne aby na ko�cu tekstu da� dwa odst�py, po nich metoda rozpozna, �e koniec tekstu
{
	int stopper = 0;
	int counter = 0;
	while (stopper == 0)
	{
		cout << a[counter];
		counter++;
		Sleep(2);
		if (a[counter] == ' ' && a[counter + 1] == ' ') stopper++;
	}
}

void Location::setspeed() //obecnie nieu�ywane
{
	cout << "Wybierz pr�dko�� wy�wietlania tekstu" << endl;
	int x, y;
	cout << "Szybko: 1" << endl;
	cout << "Wolno: 2" << endl;
	cout << "Natychmiastowo" << endl;
	cin >> x;
	if (x == 1)y = 1;
	if (x == 2) y = 20;
	if (x == 3) y = 0;
	//text_speed = y;
}
/**
* Metoda zmienia losowo wartosc zmiennej ennumber odpowiedzialnej za dobranie wydarzenia w komnacie lub opisu lokalizacji.
* */
void Hallway::reroll(int x)
{
	ennumber = random(x);
}

/**
* Metoda wyswietla opis korytarza.
* */
void Hallway::description()
{
	int x = ennumber;
	switch (x)
	{
	case 0:
	{
		printdc(h1);
		break;
	}
	case 1:
	{
		printdc(h2);
		break;
	}
	case 2:
	{
		printdc(h3);
		break;
	}
	case 3:
	{
		printdc(h4);
		break;
	}
	case 4:
	{
		printdc(h5);
		break;
	}
	}
	cout << endl;
}

/**
* Metoda zwraca liczbe w zaleznosci od podjetej przez gracza decyzji o wybraniu kierunku na skrzyzowaniu. Zwracana liczba ma wplyw na kolejna lokalizacje w grze.
* */
int Hallway::go_next()
{
	int x,y;
	printdc(gonext);
	cout << endl << "ruszaj na wsch�d(ma�e zagro�enie): 1" << endl << "ruszaj na zach�d(�rednie zagro�enie): 2" << endl << "ruszaj na p�noc(du�e zagro�enie): 3" << endl;
	bool f = false;
	while (f == false)
	{
		cin >> x;
		if (!cin.good()) x = 1;

		switch (x)
		{
		case 1:
		{			
			y = 0;
			f = true;
			break;
		}
		case 2:
		{
			y = 1;
			f = true;
			break;
		}
		case 3:
		{
			y = 3;
			f = true;
			break;
		}
		default:
		{
			cout << "Nieprawid�owy numer" << endl;

		}
		}

	}
	return y;

}

/**
* Metoda wyswietla komunikat o opuszczeniu Komnaty i czeka na reakcje gracza.
* */
void Location::leavechamber()
{
	Sleep(2000);
	printdc(" Opuszczasz komnat�. Zamykasz za sob� drzwi i wyruszasz w dalsze poszukiwania  "); cout << endl;
	cout << "naci�nij enter by kontynuowa� podr�" << endl;
	cin.ignore();
	cin.ignore();
}


/**
* Wyswietla opis sali z przeciwnikiem
* */
void Skirmish_Chamber::description()
{
	int x = ennumber;
	switch (x)
	{
	case 0:
	{
		printdc(s1);
		break;
	}
	case 1:
	{
		printdc(s2);
		break;
	}
	case 2:
	{
		printdc(s3);
		break;
	}
	case 3:
	{
		printdc(s4);
		break;
	}
	case 4:
	{
		printdc(s5);
		break;
	}
	}
	cout << endl;
}


/**
* Rozbudowana metoda przyjmujaca jako argument referencje do obiektu bohatera.
* Podczas dzialania metody, gracz decyduje o podjeciu walki z przeciwnikiem.
* W zaleznosci od wyniku walki, obiekt bohatera jest odpowiednio modyfikowany (utracone HP, zyskane zloto)
* */
void Skirmish_Chamber::player_action(Hero& hero) //str-si�a przeciwnika , gold-nagroda za powodzenie
{
	int str = (hero.XP/4)+random(10)+1; ;
	int gold=hero.XP+10; 
	int x;
	bool done = false;
	printdc("Przeciwnik jeszcze Ci� nie zauwa�y�. Staniesz do walki?  "); cout << endl;printdc("Czy mo�e u�yjesz swego szcz�cia aby ukra�� skarb oraz  "); cout << endl; printdc("jednocze�nie uciec bez walki?  ");cout << endl;
		cout << "Walcz z przeciwnikiem (jego si�a wynosi " << str << "): 1" << endl;
		cout << "u�yj sprytu aby uciec i okra�� przeciwnika: 2" << endl;
		while (done == false)
		{
			cin >> x;
			if (!cin.good()) x = 1;
			if (x == 1)
			{
				bool herowon=false;
				int hstr = hero.STR + random(5);
				int enstr = str + random(5);
				if(hstr>=enstr) herowon=true;
				cout << "Twoja si�a w walce :" << hstr << " vs " << enstr << ": wroga si�a w walce" << endl;
				Sleep(200);

				if (herowon == true)
				{
					printdc("Walka by�a zaciek�a. Mimo straszliwo�ci przeciwnika, uda�o Ci si� go pokona� a jego skarby nale�� do Ciebie  ");
					cout<<endl << "Zdobyte skarby: " << gold * str << endl;
					hero.GOLD += (gold * str);
					hero.XP += (str);
					hero.TotalEnemies++;
					done = true;
				}
				if (herowon == false)
				{
					int damage=(random(3)+1);
					printdc("Walka by�a trudna a przeciwnik okaza� si� silniejszy ni� mo�na si� by�o spodziewa�. Walka jest przegrana.  "); cout << endl; printdc(" mimo wyczerpania, ostatkiem si� uciekasz w stron� drzwi i opuszczasz komnat�.  "); cout << endl;
					cout << "utracone punkty �ycia: " << damage << endl;
					hero.HP -= damage;
					done = true;
				}			
			}
			if (x == 2)
			{
				if (hero.LCK <= 0)
				{
					cout << "Nie masz punkt�w szcz�cia! Nie mo�esz ich u�y� w tej sytuacji!" << endl;
					
				}
				else
				{
					printdc("Dzi�ki swojemu nieopisanemu szcz�ciu, zakradasz si� do przeciwnika i wykradasz jego z�oto.  "); cout << endl; printdc("Kiedy przeciwnik zdaje sobie spraw�, �e zosta� okradziony, Ty spokojnie wymykasz si� z komnaty  "); cout << endl;
					cout << "Zdobyte skarby: " << gold * str << endl;
					hero.GOLD += (gold * str);
					hero.LCK--;
					hero.TotalLuckUsed++;
					done = true;
				}
			}
		}
		Sleep(2000);
		
}

/**
* Metoda zmienia losowo wartosc zmiennej ennumber odpowiedzialnej za dobranie wydarzenia w komnacie lub opisu lokalizacji.
* */
void Skirmish_Chamber::reroll(int x)
{
	ennumber = random(x);
}

/**
* Metoda wyswietla opis sali ze skarbem
* */
void Treasure_Chamber::description()
{
	int x = ennumber;
	switch (x)
	{
	case 0:
	{
		printdc(t1);
		break;
	}
	case 1:
	{
		printdc(t2);
		break;
	}
	case 2:
	{
		printdc(t3);
		break;
	}
	case 3:
	{
		printdc(t4);
		break;
	}
	case 4:
	{
		printdc(t5);
		break;
	}
	}
	cout << endl;
}

/**
* Rozbudowana metoda przyjmujaca jako argument referencje do obiektu bohatera.
* Podczas trwania metody, gracz decyduje o otwarciu znalezionej skrzyni.
* W zaleznosci od czynnikow losowych, skrzynia moze zawierac wszelakie pozytywne lub negatywne przedmioty.
* Po zakonczeniu akcji, obiekt bohatera jest odpowiednio modyfikowany (znalezione zloto, utracone HP)
* */
void Treasure_Chamber::player_action(Hero& hero)
{
	int x = random(5);
	int y;
	switch (x)
	{
	case 0:
	{
	    printdc("Czy chcesz podej�� do skrzyni i spr�bowa� j� otworzy�?  "); cout << endl;
		cout << " Zaryzykuj i otw�rz skrzynk�: 1" << endl;
		cout << " Zostaw skrzynk� i ruszaj dalej: 2" << endl;
		bool done = false;

		while (done == false)
		{
			cin >> y;
			if (!cin.good()) y = 1;
			if (y == 1)
			{
				printdc("Postanawiasz podej�� do skrzynki i j� otworzy�. Powoli zdejmujesz wieki a Twoim oczom ukazuje si� sterta z�otych monet!  "); cout << endl; printdc("Bez zawachania zabierasz wszystkie monety i z u�miechem na twarzy ruszasz w dalsz� podr�.  "); cout << endl;
				int gold = hero.XP * 10 + 100;
				cout << " Zdobyte z�oto: " << gold << " z�otych monet" << endl;
				Sleep(2000);
				hero.GOLD += gold;
				done = true;
			}
			if(y == 2)
			{
				printdc("Postanawiasz nie rusza� skrzyni. Ostro�no�ci nigdy zbyt wiele. By� mo�e w�a�nie uda�o si� unikn�� �miertelnej pu�apki?  "); cout << endl; printdc("Nie my�l�c wiele, zapominasz o skrzyni i ruszasz w kierunku wyj�cia z komnaty  ");
				done = true;
			}
		}
		break;
	}
	case 1:
	{
		printdc("Czy chcesz podej�� do skrzyni i spr�bowa� j� otworzy�?  "); cout << endl;
		cout << " Zaryzykuj i otw�rz skrzynk�: 1" << endl;
		cout << " Zostaw skrzynk� i ruszaj dalej: 2" << endl;
		bool done = false;
		cin >> y;
		if (!cin.good()) y = 1;
		if (y == 1)
		{
			printdc("Postanawiasz podej�� do skrzynki i j� otworzy�. Jednak w momencie dotkni�cia wieka, s�yszysz jak w skrzyni aktywuje si� mechanizm obronny.  "); cout << endl; printdc("Z dziurki na klucz wyskakuje zatruta ig�a, kt�ra kaleczy Ci� bole�nie.  "); cout << endl;
			int damage = (random(3) + 1);
			cout << " Otrzymane obra�enia: " << damage << endl;
			Sleep(1000);
			hero.HP -= damage;
			printdc("Pu�aka jest dezaktywowana. Mo�esz teraz dobra� si� do skarbu, kt�ry znajduje si� na dnie skrzynki  "); cout << endl;
			int gold = hero.XP * 10 + 100;
			cout << " Zdobyte z�oto: " << gold << " z�otych monet" << endl;
			hero.GOLD += gold;
			Sleep(1000);
			done = true;
		}
		if (y == 2)
		{
			printdc("Postanawiasz nie rusza� skrzyni. Ostro�no�ci nigdy zbyt wiele. By� mo�e w�a�nie uda�o si� unikn�� �miertelnej pu�apki?  "); cout << endl; printdc("Nie my�l�c wiele, zapominasz o skrzyni i ruszasz w kierunku wyj�cia z komnaty  "); cout << endl;
			done = true;
		}
		break;
	}
	case 2:
	{
		printdc("Czy chcesz podej�� do skrzyni i spr�bowa� j� otworzy�?  "); cout << endl;
		cout << " Zaryzykuj i otw�rz skrzynk�: 1" << endl;
		cout << " Zostaw skrzynk� i ruszaj dalej: 2" << endl;
		bool done = false;
		cin >> y;
		if (!cin.good()) y = 1;
		if (y == 1)
		{
			printdc("Postanawiasz podej�� do skrzynki i j� otworzy�. Jednak w momencie dotkni�cia wieka, s�yszysz jak w skrzyni aktywuje si� mechanizm obronny.  "); cout << endl; printdc("Z dziurki na klucz wyskakuje zatruta ig�a, kt�ra kaleczy Ci� bole�nie.  "); cout << endl;
			int damage = (random(3) + 1);
			cout << " Otrzymane obra�enia: " << damage << endl;
			Sleep(1000);
			hero.HP -= damage;
			printdc("Pu�aka jest dezaktywowana. Skrzynia natomiast, stoi pusta. Z grymasem na ustach, odchodzisz od pustej skrzyni.  "); cout << endl;
			Sleep(500);
			done = true;
		}
		if (y == 2)
		{
			printdc("Postanawiasz nie rusza� skrzyni. Ostro�no�ci nigdy zbyt wiele. By� mo�e w�a�nie uda�o si� unikn�� �miertelnej pu�apki?  "); cout << endl; printdc("Nie my�l�c wiele, zapominasz o skrzyni i ruszasz w kierunku wyj�cia z komnaty  "); cout << endl;
			done = true;
		}
		break;
	}
	case 3:
	{
		printdc("Czy chcesz podej�� do skrzyni i spr�bowa� j� otworzy�?  "); cout << endl;
		cout << " Zaryzykuj i otw�rz skrzynk�: 1" << endl;
		cout << " Zostaw skrzynk� i ruszaj dalej: 2" << endl;
		bool done = false;
		while (done == false)
		{
			cin >> y;
			if (!cin.good()) y = 1;
			if (y == 1)
			{
				printdc("Postanawiasz podej�� do skrzynki i j� otworzy�. Podnosisz wieko bez oporu. Na dnie skrzynki dostrzegasz fiolk� z eliksirem.  "); cout << endl; printdc("Nie potrafisz rozpozna� dziwnej substancji. Czy chcesz zaryzykowa� i wypi� eliksir?  "); cout << endl;
				cout << "Wypij eliksir: 1" << endl;
				cout << "Nie pij eliksiru: 2" << endl;
				int q, z;
				bool done2 = false;
				z = random(4);
				while (done2 == false)
				{
					cin >> q;
					if (!cin.good()) q = 3;
					if (q == 1)
					{
						if (z == 0)
						{
							printdc("Eliksir dzia�a na Ciebie orze�wiaj�co, czujesz jak Twoje si�y witalne do Ciebie wracaj� a rany lecz� si� same  "); cout << endl;
							int hp = random(5) + 1;
							cout << "Zdobyte punkty �ycia: " << hp << endl;
							Sleep(1000);
							hero.HP += hp;
							done2 = true;
						}
						if (z == 1)
						{
							printdc("Eliksir przepe�nia Ci� si�� i gniewem. Czujesz, �e mo�esz osi�gn�� wszystko i �adne okropno�ci podziemi nie s� dla Ciebie wyzwaniem  "); cout << endl;
							int str = random(2) + 1;
							cout << "Zdobyte punkty si�y: " << str << endl;
							Sleep(1000);
							hero.STR += str;
							done2 = true;
						}
						if (z == 2)
						{
							printdc("Eliksir nie wp�ywa nijak na Ciebie. Po chwili jednak czujesz, �e szcz�cie Ci dopisuje i z jego pomoc� uda Ci si� przetrwa� najwi�ksze okropno�ci podziemi  "); cout << endl;
							cout << "Otrzymujesz dodatkowy punkt szcz�cia!" << endl;
							Sleep(1000);
							hero.LCK++;
							done2 = true;
						}
						if (z == 3)
						{
							printdc("Eliksir okazuje si� trucizn�!  "); cout << endl;
							int damage = (random(2) + 1);
							cout << " Otrzymane obra�enia: " << damage << endl;
							Sleep(1000);
							hero.HP -= damage;
							done2 = true;
						}
						printdc("Odrzucasz pust� fiolk� i ruszasz dalej w drog�  ");
						hero.TotalPotions++;
						done = true;
					}
					if (q == 2)
					{
						printdc("Wolisz nie ryzykowa�. Nikt nie wie czym jest tajemniczy eliksir. Mo�e lepiej tym razem zaniecha� i ruszy� dalej  "); cout << endl; printdc("Odk�adasz fiolk� do skrzyni i ruszasz w dalsz� drog�  "); cout << endl;
						done2 = true;
						done = true;
					}

				}
			}

			if (y == 2)
			{
				printdc("Postanawiasz nie rusza� skrzyni. Ostro�no�ci nigdy zbyt wiele. By� mo�e w�a�nie uda�o si� unikn�� �miertelnej pu�apki?  "); cout << endl; printdc("Nie my�l�c wiele, zapominasz o skrzyni i ruszasz w kierunku wyj�cia z komnaty  "); cout << endl;
				done = true;
			}
		}
		Sleep(1000);
		break;
	}
	case 4:
	{
		printdc("Czy chcesz podej�� do skrzyni i spr�bowa� j� otworzy�?  "); cout << endl;
		cout << " Zaryzykuj i otw�rz skrzynk�: 1" << endl;
		cout << " Zostaw skrzynk� i ruszaj dalej: 2" << endl;
		bool done = false;
		int x;
		while (done == false)
		{
			cin >> x;
			if (x == 1)
			{
				printdc("Wieko skrzyni jest ci�kie, mija d�uga chwila zanim udaje Ci si� je podnie��. Jednak widok, kt�ry zauwa�asz w �rodku zdecydowanie by� wart wysi�ku  "); cout << endl; printdc("Skrzynia jest pe�na z�ota i kosztowno�ci!  "); cout << endl;
				int gold = hero.XP * 20 + 300;
				cout << " Zdobyte z�oto: " << gold << " z�otych monet" << endl;
				Sleep(2000);
				hero.GOLD += gold;
				done = true;
			}
			if (x == 2)
			{
				printdc("Postanawiasz nie rusza� skrzyni. Ostro�no�ci nigdy zbyt wiele. By� mo�e w�a�nie uda�o si� unikn�� �miertelnej pu�apki?  "); cout << endl; printdc("Nie my�l�c wiele, zapominasz o skrzyni i ruszasz w kierunku wyj�cia z komnaty  ");
				done = true;
			}
		}
		break;
	}
	}
	cout << endl;
}

/**
* Metoda zmienia losowo wartosc zmiennej ennumber odpowiedzialnej za dobranie wydarzenia w komnacie lub opisu lokalizacji.
* */
void Treasure_Chamber::reroll(int x)
{
	ennumber = random(x);
}


/**
* Metoda wyswietla opis sali z wydarzeniem.
* */
void Event_Chamber::description()
{
	int x = ennumber;
	switch (x)
	{
	case 0:
	{
		printdc(e1);
		break;
	}
	case 1:
	{
		printdc(e2);
		break;
	}
	case 2:
	{
		printdc(e3);
		break;
	}
	case 3:
	{
		printdc(e4);
		break;
	}
	case 4:
	{
		printdc(e5);
		break;
	}
	}
	cout << endl;
}


/**
* Rozbudowana metoda przyjmujaca jako argument referencje do obiektu bohatera.
* W zaleznosci od czynnikow losowych, gracz napotyka w sali przeszkody lub postacie.
* Efekt oddzialywania wydarzenia na bohatera zalezy od dzialan gracza oraz czynnikow losowych.
* Po zakonczeniu akcji, obiekt bohatera jest odpowiednio modyfikowany (znalezione zloto, utracone HP, zmodyfikowane wartosci)
* */
void Event_Chamber::player_action(Hero& hero)
{
	int x = ennumber;
	int y;
	switch (x)
	{
	case 0:
	{
		printdc("Nad sadzawk� unosi si� tajemnicza aura. Czy zaryzykujesz kompiel?  "); cout << endl;
		bool done = false;
		cout << "Wejd� do sadzawki: 1" << endl;
		cout << "zaniechaj kompieli i ruszaj dalej: 2" << endl;
		int q,z;
		while (done == false)
		{
			bool done2 = false;
			z = random(4);
			while (done2 == false)
			{
				cin >> q;
				if (!cin.good()) q = 3;
				if (q == 1)
				{
					if (z == 0)
					{
						printdc("Zaczarowana woda dzia�a koj�co na Twoje rany. Czujesz, �e wszelkie si�y witalne wracaj� do Ciebie.  "); cout << endl;
						int hp = random(6) + 1;
						cout << "Zdobyte punkty �ycia: " << hp << endl;
						Sleep(1000);
						hero.HP += hp;
						done2 = true;
					}
					if (z == 1)
					{
						printdc("Zimna woda przeszywa Ci� i hartuje. Czujesz jak Twoje mi�nie staj� si� twardsze a odporno�� ro�nie.  "); cout << endl;
						int str = random(2) + 1;
						cout << "Zdobyte punkty si�y: " << str << endl;
						Sleep(1000);
						hero.STR += str;
						done2 = true;
					}
					if (z == 2)
					{
						printdc("Na dnie sadzawki dostrzegasz z�ote monety! Bez zawachania nurkujesz pod wod� i zbierasz je wszystkie.  "); cout << endl;
						int gold = hero.XP * 10 + 200;
						cout << " Zdobyte z�oto: " << gold << " z�otych monet" << endl;
						Sleep(2000);
						hero.GOLD += gold;
						done2 = true;
					}
					if (z == 3)
					{
						printdc("Po zanurzeniu w sadzawce przeszywa Ci� straszliwy b�l. Twoja sk�ra pali Ci� niczym ogie�!  "); cout << endl; printdc("Mimo licznych oparze�, wyskakujesz z sadzawki i resztkami si� ruszasz w stron� wyj�cia z komnaty.  "); cout << endl;
						int damage = (random(2) + 1);
						cout << " Otrzymane obra�enia: " << damage << endl;
						Sleep(1000);
						hero.HP -= damage;
						done2 = true;
					}
					done = true;
					
				}
				if (q == 2)
				{
					printdc("Wolisz nie ryzykowa�. Woda w sadzawce wygl�da podejrzanie, kto wie czym sko�czy� si� mo�e kompiel.  "); cout << endl; printdc("Odwracasz wzrok i ruszasz w kierunku wyj�cia z komnaty.  "); cout << endl;
					done2 = true;
					done = true;
				}

			}
		}
		Sleep(1000);
		break;
	}
	case 1:
	{
		printdc("Czy chcesz zagada� kowala?  "); cout << endl;
		cout << " Zagadaj kowala: 1" << endl;
		cout << " Odejd� w swoj� stron�: 2" << endl;
		bool done = false;
		while (done == false)
		{
			cin >> y;
			if (!cin.good()) y = 3;
			if (y == 1)
			{
				printdc("Kowal obraca si� i patrzy na Ciebie bystrym wzrokiem. Po chwili gasi fajk� i oznajmia, �e wykuwa tutaj or� najlepszej jako�ci  "); cout << endl; printdc("Za odpowiedni� op�at�, kowal sprzeda Ci bro�, kt�ra z �atwo�ci� pokona ka�dego napotkanego wroga  "); cout << endl;
				cout << "Czy chcesz zakupi� now� bro�?" << endl;
				cout << "Cena zwyk�ej broni: 150 Z�ota (si�a zwi�kszona o 1 punkt), [Zakup:1]" << endl;
				cout << "Cena pot�nej broni: 250 Z�ota (si�a zwi�kszona o 2 punkty), [Zakup:2]" << endl;
				cout << "Cena mistrzowskej broni: 500 Z�ota (si�a zwi�kszona o 4 punkty),[Zakup:3]" << endl;
				cout << " Nie mam na to czasu ani pieni�dzy! [Nic nie kupuj:4]" << endl;
				int q;
				bool done2 = false;
				while (done2 == false)
				{
					cin >> q;
					if (!cin.good()) q = 5;
					if (q == 1)
					{
						if (hero.GOLD < 100) cout << "Nie masz tyle z�ota!" << endl;
						else
						{
							hero.GOLD -= 100;
							hero.STR += 1;
								printdc("Zakupi�e� zwyk�� bro�.  "); cout << endl;
								done2 = true;
						}

					}
					if (q == 2)
					{
						if (hero.GOLD < 250) cout << "Nie masz tyle z�ota!" << endl;
						else
						{
							hero.GOLD -= 250;
							hero.STR += 2;
							printdc("Zakupi�e� pot�n� bro�.  "); cout << endl;
							done2 = true;
						}
					}
					if (q == 3)
					{
						if (hero.GOLD < 500) cout << "Nie masz tyle z�ota!" << endl;
						else
						{
							hero.GOLD -= 500;
							hero.STR += 4;
							printdc("Zakupi�e� mistrzowsk� bro�.  "); cout << endl;
							done2 = true;
						}
					}
					if (q == 4)
					{
						printdc("Odst�pujesz od kowala nie dokonuj�� zakupu.  "); cout << endl;
						done2 = true;
					}

				}
				printdc("Wystarczy handlowania na dzisiaj. Pora rusza� dalej  "); cout << endl;

				done = true;
			}
			if (y == 2)
			{
				printdc("Nie ma czasu rozmawia� z nieznajomymi.Pora rusza� dalej.  "); cout << endl; printdc("Odwracasz wzrok i ruszasz w kierunku wyj�cia z sali.  "); cout << endl;
				done = true;
			}
		}
		break;
	}
	case 2:
	{
		printdc("Nieznajomy wci�� patrzy na Ciebie. Czy chcesz podej�� i zagada�?  "); cout << endl;
		cout << "Podejd� bli�ej do tajemniczej postaci: 1" << endl;
		cout << "Odwr�� si� i odejd� w swoj� stron� : 2" << endl;
		bool done = false;
		while (done == false)
		{
			cin >> y;
			if (!cin.good()) y = 1;
			if (y == 1)
			{
				printdc("Zbli�asz si� do nieznajomego. Jego wzrok jest zimny i nieprzyjazny. Posta� wci�� milczy.  "); cout << endl;

				int z;
				bool done2 = false;
				z = random(4);
				

				while (done2 == false)
				{
					
						if (z == 0)
						{
							printdc("Nieznajomy wyci�ga d�o� w Twoj� stron�. Dostrzegasz, �e trzyma w niej sakiewk�. Kiedy zagl�dasz do niej, dostrzegasz szczeroz�ote monety!  "); cout << endl;
							int gold = random(400) + 1;
							cout << "Zdobywasz " << gold << " z�otych monet!" << endl;
							hero.GOLD += gold;
							Sleep(3000);
							printdc("Kiedy zn�w podnosisz wzrok, tajemniczej postaci ju� nie ma w komnacie. Znikn�a lub rozp�yn�a si� w powietrzu.  "); cout << endl;
							done2 = true;
							done = true;
						}
						if (z == 1)
						{
							printdc("Kiedy ruszasz do przodu, tajemnicza posta� robi krok w Twoj� stron�. Zanim jednak zd��y�e� przem�wi�, nieznajomy wyci�gn�� ukryty pod szat� sztylet!  "); cout << endl; printdc("Nie by�o czasu na reakcje. Nieznajomy zadaje Ci bolesny cios sztyletem a nast�pnie znika w mgnieniu oka. Pozostajesz samotnie w pustej sali.  "); cout << endl;
							int dmg = random(4) + 1;
							cout << "Tracisz " << dmg << " punkty �ycia" << endl;
							hero.HP -= dmg;
							Sleep(3000);
							printdc("Wci�� czuj�� b�l po niespodziewanym ataku, ruszasz w kierunku wyj�cia z komnaty  "); cout << endl;
							done2 = true;
							done = true;
						}
						if (z == 2)
						{
							printdc("Tajemnicza posta� wyci�ga d�o� w Twoim kierunku. Dostrzegasz, �e trzyma w niej tajemnicz� fiolk�. Zapewne jest to eliksir.  "); cout << endl; printdc("Kiedy odbierasz fiolk� z d�oni nieznajomego, ten rozp�ywa si� w powietrzu i zostawia Ci� w pustej komnacie  "); cout << endl;
							printdc("Nie potrafisz rozpozna� dziwnej substancji w fiolce. Czy chcesz zaryzykowa� i wypi� eliksir?  "); cout << endl;
							cout << "Wypij eliksir: 1" << endl;
							cout << "Nie pij eliksiru: 2" << endl;
							int j, k;
							bool done3 = false;
							k = random(4);
							while (done3 == false)
							{
								cin >> j;
								if (!cin.good()) j = 3;
								if (j == 1)
								{
									if (k == 0)
									{
										printdc("Eliksir dzia�a na Ciebie orze�wiaj�co, czujesz jak Twoje si�y witalne do Ciebie wracaj� a rany lecz� si� same  "); cout << endl;
										int hp = random(5) + 1;
										cout << "Zdobyte punkty �ycia: " << hp << endl;
										Sleep(1000);
										hero.HP += hp;
										done3 = true;
									}
									if (k == 1)
									{
										printdc("Eliksir przepe�nia Ci� si�� i gniewem. Czujesz, �e mo�esz osi�gn�� wszystko i �adne okropno�ci podziemi nie s� dla Ciebie wyzwaniem  "); cout << endl;
										int str = random(2) + 1;
										cout << "Zdobyte punkty si�y: " << str << endl;
										Sleep(1000);
										hero.STR += str;
										done3 = true;
									}
									if (k == 2)
									{
										printdc("Eliksir nie wp�ywa nijak na Ciebie. Po chwili jednak czujesz, �e szcz�cie Ci dopisuje i z jego pomoc� uda Ci si� przetrwa� najwi�ksze okropno�ci podziemi  "); cout << endl;
										cout << "Otrzymujesz dodatkowy punkt szcz�cia!" << endl;
										Sleep(1000);
										hero.LCK++;
										done3 = true;
									}
									if (k == 3)
									{
										printdc("Eliksir okazuje si� trucizn�!  "); cout << endl;
										int damage = (random(2) + 1);
										cout << " Otrzymane obra�enia: " << damage << endl;
										Sleep(1000);
										hero.HP -= damage;
										done3 = true;
									}
									printdc("Odrzucasz pust� fiolk� i ruszasz dalej w drog�  ");
									hero.TotalPotions++;
									done2 = true;
								}
								if (j == 2)
								{
									printdc("Wolisz nie ryzykowa�. Nikt nie wie czym jest tajemniczy eliksir. Mo�e lepiej tym razem zaniecha� i ruszy� dalej  "); cout << endl;
									done3 = true;
									done2 = true;
								}
								done = true;
							}			
						}
						if (z == 3)
						{
							printdc("Kiedy podchodzisz bli�ej, tajemnicza posta� rozp�ywa si� w powietrzu i zostawia Ci� w pustej sali. Nie zosta�o tutaj nic do roboty, pora rusza� dalej  "); cout << endl;
							done2 = true;
							done = true;
						}
						Sleep(1500);
				}
			}
			if (y == 2)
			{
				printdc("Lepiej nie ufa� nieznajomym. Zw�aszcza takim dziwakom jak ten stoj�cy przed Tob�.  "); cout << endl; printdc("Odwracasz si� na pi�cie i ruszasz w stron� wyj�cia z komnaty.  "); cout << endl;
				done = true;
			}
		}
		break;
	}
	case 3:
	{
		printdc("Mechanizm wygl�da na gro�ny. Musisz jednak znale�� spos�b na przebrni�cie przez pu�apk�.  "); cout << endl;
		cout << "Spr�buj wykona� olbrzymi skok aby przeskoczy� pu�apk� [licz�c na swoj� si��]: 1" << endl;
		cout << " Spr�buj przej�� przez pu�apk� licz�c, �e nie zostanie ona aktywowana [licz�c na swoje szcz�cie]: 2" << endl;
		cout << "Przejd� przez pu�apk� licz�� na to, �e zdo�asz wytrzyma� jej okropie�stwa [licz�� na swoj� wytrzyma�o��]: 3" << endl;
		bool done = false;
		int z = random(2);
		while (done == false)
		{
			cin >> y;
			if (!cin.good()) y = 4;
			if (y == 1)
			{
				printdc("Przygotowujesz si� do skoku. Bierzesz olbrzymi rozbieg i z ca�ych si� wybijasz si� w powietrze  "); cout << endl;
				if (z == 0)
				{
					printdc("Skok ko�czy si� olbrzymim sukcesem! Zr�cznie l�dujesz na ziemi zostawiaj�c pu�apk� za sob�.  "); cout << endl;
				}
				if (z == 1)
				{
					printdc("To nie by� dobry skok. Z�y rozbieg oraz niepoprawne l�dowanie doprowadzi�y do powa�nego zranienia  "); cout << endl; printdc("Uda�o si� pokona� pu�apk�, jednak Twoja si�a uleg�a znacznemu os�anieniu  "); cout << endl;
					cout << "Tracisz 2 punkty si�y!" << endl;
					hero.STR -= 2;
				}
				done = true;
			}
			if (y == 2)
			{
				printdc("Polegaj�c na w�asnym szcz�ciu, powoli zaczynasz stawia� kroki na pu�apce.  "); cout << endl;
				if (hero.LCK > 0)
				{
					printdc("Dzi�ki swojemu szcz�ciu, udaje Ci si� przej�� przez pu�apk� bez aktywowania mechanizmu.  "); cout << endl; printdc("Kosztowa�o Ci� to jednak punkt szcz�cia!  "); cout << endl;
					hero.LCK--;
					hero.TotalLuckUsed++;
				}
				else
				{
					printdc("Niestety, zabrak�o Ci szcz�cia! Po kilku krokach mechanizm uruchomi� si� a z pod�ogi wystrzeli�y zab�jcze kolce!  "); cout << endl;
					int dmg = random(5) + 2;
					cout << "Tracisz " << dmg << " punkt�w �ycia!" << endl;
					Sleep(2000);
					hero.HP -= dmg;
				}
				done = true;
			}
			if (y == 3)
			{
				printdc("Z szalenstwem w oczach wst�pujesz na pu�apk�.  "); cout << endl;
				Sleep(3000);
				if (z == 0)
				{
					printdc("Mimo ostrych kolc�w rani�cych Ci� z ka�dej strony, udaje Ci si� przej�� pu�apk� nie odnosz�� bardzo powa�nych obra�e�.  "); cout << endl;
					int dmg = random(2) + 2;
					cout << "Tracisz " << dmg << " punkt�w �ycia!" << endl;
					Sleep(1000);
					hero.HP -= dmg;
				}
				if (z == 1)
				{
					printdc("To by�o szale�stwo! Ostre kolce pu�apki rani� Ci� z ka�dej strony. Udaje Ci si� przej�� na drug� stron�, jednak otrzyma�e� liczne rany  "); cout << endl;
					int dmg = random(5) + 3;
					cout << "Tracisz " << dmg << " punkt�w �ycia!" << endl;
					Sleep(1000);
					hero.HP -= dmg;
				}
				done = true;
			}
		}
		printdc("Pu�apka pokonana. Mo�esz rusza� dalej  ");cout << endl;
		Sleep(2000);
		break;
	}
	case 4:
	{
		printdc("Totem a� emanuje moc� chaosu. Czy odwa�ysz si� go dotkn��?  "); cout << endl;
		cout << " Dotknij totemu licz�� na b�ogos�awienstwo chaosu: 1" << endl;
		cout << " Zostaw totem i rusz w dalsz� drog�: 2" << endl;
		bool done = false;
		int x;
		int z = random(9);
		while (done == false)
		{
			cin >> x;
			if (x == 1)
			{
				printdc("Powolnym krokiem zbli�asz si� do totemu. Dr��c� rek� dotykasz kamienia i pozwalasz aby moc chaosu zdecydowa�a o Twoim losie...  "); cout << endl;
				switch (z)
				{
				case 0:
				{
					printdc("Moce chaosu obdzieraj� Ci� z si� witalnych!  "); cout << endl;
					Sleep(2000);
					int dmg = random(3) + 1;
					cout << "tracisz " << dmg << " punkt�w �ycia!"<< endl;
					hero.HP -= dmg;
					break;
				}
				case 1:
				{
					printdc("Moce chaosu dodaj� Ci wytrzyma�o�ci!  "); cout << endl;
					Sleep(2000);
					int hp = random(4) + 1;
					cout << "zyskujesz " << hp << " punkt�w �ycia!" << endl;
					hero.HP += hp;
					break;
				}
				case 2:
				{
					printdc("Moce chaosu nagradzaj� Ci� bogactwem!  "); cout << endl;
					Sleep(2000);
					int gold = random(300) + 100;
					cout << "zyskujesz " << gold << " z�otych monet!!" << endl;
					hero.GOLD += gold;
					break;
				}
				case 3:
				{
					printdc("Moce chaosu �miej� si� z Ciebie i odbieraj� Twoje z�oto!  "); cout << endl;
					Sleep(2000);
					int gold = random(300) + 100;
					cout << "Tracisz " << gold << " z�otych monet!!" << endl;
					hero.GOLD -= gold;
					break;
				}
				case 4:
				{
					printdc("Moce chaosu odaj� Twym ramionom si�!  "); cout << endl;
					Sleep(2000);
					int str = random(3) + 1;
					cout << "zyskujesz " << str << " Punkt�w si�y!" << endl;
					hero.STR += str;
					break;
				}
				case 5:
				{
					printdc("Moce chaosu b�d� nad Tob� czuwa�!  "); cout << endl;
					Sleep(2000);
					int lck = random(1) + 1;
					cout << "zyskujesz " << lck << " punkty szcz�cia!" << endl;
					hero.LCK += lck;
					break;
				}
				case 6:
				{
					printdc("Moce chaosu odbieraj� Ci nadziej� na zwyci�stwo...  "); cout << endl;
					Sleep(2000);
					cout << " Tracisz wszystkie punkty szcz�cia!!" << endl;
					hero.LCK = 0;
					break;
				}
				case 7:
				{
					printdc("Moce chaosu mianuj� Ci� swoim wybra�cem!  "); cout << endl;
					Sleep(2000);					
					cout << "Twoja si�a, szcz�cie i wytrzyma�o�c wzrastaj�!! W sakiewce natomiast znajdujesz dodatkowe z�oto." << endl;
					hero.GOLD += 200;
					hero.STR++;
					hero.LCK++;
					hero.HP += 3;
					break;
				}
				case 8:
					printdc("Ziemia si� trz�cie... Czujesz, �e w podziemiach w�a�nie sta�o si� co� straszliwego.  "); cout << endl; printdc(" Wychodzisz z sali, jednak czujesz, �e podziemia szykuj� dla Ciebie test, kt�rego nie spos�b zda�...  "); cout << endl;
					Sleep(3000);
					hero.XP += 100;
					break;

				}
				done = true;
			}
			if (x == 2)
			{
				printdc("Z mocami chaosu nie powinno si� igra�. Odwracasz si� i ruszasz w kierunku wyj�cia.  "); cout << endl; printdc("Wci�� s�yszysz szepty chaosu za plecami. Opuszczasz t� sal� tak szybko jak potrafisz.  ");
				done = true;
			}
		}
		printdc("Nie powinno si� zostawa� w tej komnacie d�u�ej ni� to konieczne. Czas rusza� dalej.  "); cout << endl;
		break;
	}
	}
	cout << endl;
	Sleep(1000);
	 
}

/**
* Metoda zmienia losowo wartosc zmiennej ennumber odpowiedzialnej za dobranie wydarzenia w komnacie lub opisu lokalizacji.
* */
void Event_Chamber::reroll(int x)
{
	ennumber = random(x);
}


void Special_Chamber::description()
{
	int x = ennumber;
	switch (x)
	{
	case 0:
	{
		printdc(sp1);
		break;
	}
	case 1:
	{
		printdc(sp2);
		break;
	}
	case 2:
	{
		printdc(sp3);
		break;
	}
	case 3:
	{
		printdc(sp4);
		break;
	}
	}
	cout << endl;
}

	void Special_Chamber::player_action(Hero & hero)
	{
		int x = ennumber;

		switch (x) 
		{
		case 0:
		{
			printdc("Z�oto nale�y do Ciebie. Mo�esz bez porblem�w zabra� wszystko ze sob�.  ");
			int gold = (hero.TotalChambers * 100);
			cout << endl << "Znalaz�e� " << gold << " sztuk z�ota! To prawdziwe bogactwo!" << endl;
			hero.GOLD += gold;
			break;
		}
		case 1:
		{
			printdc("Czy podejmiesz wyzwanie i zagrasz ze �mierci� o ca�e swoje z�oto?  ");
			int y;
			bool done = false;
			cout << endl << "Zagraj w ko�ci ze �mierci�: 1" << endl;
			cout << "Nie ryzykuj i ruszaj w dalsz� podr�: 2" << endl;
			while (done == false)
			{
				cin >> y;
				if (!cin.good()) y= 1;
				if (y == 1)
				{
					printdc("Postanawiasz postawi� ca�e swoje z�oto i zagra�. Oboje si�gacie po ko�ci i jednocze�nie rzucacie na st�...  ");
					int playerdice;
					int enemydice;
					do
					{
						playerdice = random(5) + 1;
						enemydice = random(5) + 1;
					} while (playerdice == enemydice);
					cout << endl;
					printdc("Wynik na Twojej ko�ci:  "); Sleep(2000); cout << playerdice << endl;
					printdc("Wynik na ko�ci �mierci:  "); Sleep(2000); cout << enemydice << endl;

					if (playerdice > enemydice)
					{
						printdc("Szcz�cie by�o z Tob�! Uda�o Ci si� pokona� �mier� i Twoje z�oto jest teraz podwojone!  "); cout << endl; Sleep(2000);
						hero.GOLD = (hero.GOLD * 2);
						cout << " posiadasz teraz " << hero.GOLD << " z�ota." << endl;
						printdc("�mier� wci�� patrzy w Twoj� stron�. Po chwili oznajmia Ci, �e chce si� odegra� i proponuje rewan� na Tych samych zasadach co poprzednia rozgrywka. Je�eli wygrasz, Twoje z�oto ponownie zostanie podwojone. Je�eli przegrasz, �mier� zabierze ca�e z�oto...  ");
						cout << endl << "Czy przystaniesz na propozycj� �mierci i ponownie postawisz ca�e swoje z�oto?" << endl;
						cout << "Zagraj w ko�ci ponownie: 1" << endl;
						cout << "Odejd� z dotychczasow� wygran�: 2" << endl;
						int q;
						cin >> q;
						if (!cin.good()) q = 1;
						if (q == 1)
						{
							printdc(" Postanawiasz zagra� jeszcze raz  "); cout << endl;
							do
							{
								playerdice = random(5) + 1;
								enemydice = random(5) + 1;
							} while (playerdice == enemydice);
							cout << endl;
							printdc("Wynik na Twojej ko�ci:  "); Sleep(2000); cout << playerdice << endl;
							printdc("Wynik na ko�ci �mierci:  "); Sleep(2000); cout << enemydice << endl;

							if (playerdice > enemydice)
							{
								printdc("Szcz�cie by�o z Tob�! Uda�o Ci si� pokona� �mier� i Twoje z�oto jest teraz podwojone!   "); cout << endl; Sleep(2000);
								hero.GOLD = (hero.GOLD * 2);
								cout << " posiadasz teraz " << hero.GOLD << " z�ota." << endl;
								Sleep(2000);
								printdc("�mier� stoi nieruchomo. Uda�o Ci si� okpi� j� dwukrotnie, pozosta�o jej jedynie odej�cie z opuszczon� g�ow�. Z�oto jest Twoje.   ");

								done = true;
							}
							if (playerdice < enemydice)
							{
								printdc("�mier� �mieje si� g�o�no. Zwyci�stwo nale�y do niej i zgodnie z umow�, ca�e Twoje z�oto przepada!  ");
									cout << endl;
								hero.GOLD = 0;
								done == true;

							}
							
						}
						if (q == 2);
						{
							printdc("To oczywiste, �e �mier� chce Ci� oszuka�! Wygra�e� z�oto i nie masz zamiaru gra� jeszcze raz. Z u�miechem na twarzy zabierasz ca�e z�oto ze sto�u i ruszasz w stron� wyj�cia.  ");
							done = true;
						}

					}
					if (playerdice < enemydice)
					{
						printdc("�mier� �mieje si� g�o�no. Zwyci�stwo nale�y do niej i zgodnie z umow�, ca�e Twoje z�oto przepada!  ");
						cout << endl;
						int goldlost = hero.GOLD;
						hero.GOLD = 0;
						Sleep(2000);
						printdc("Na Twojej twarzy maluje si� smutek i rozgoryczenie. Ca�e Twoje z�oto przepad�o. Po chcili milczenia, �mier� ponownie zabiera g�os. Proponuje Ci rewan�, Je�eli zwyci�zysz, odzyskasz ca�e swoje z�oto. Je�eli jednak przegrasz, �mier� odbierze Ci cz�� swojej duszy jako zap�at�...   ");
						cout << endl << "Stawka jest wysoka. Czy chcesz ponownie zagra� w ko�ci na ustalonych powy�ej warunkach?" << endl;
						cout << "Zagraj o z�oto i swoj� dusz�: 1" << endl;
						cout << "Nie ryzykuj i odejd� bez z�ota: 2" << endl;
						int q;
						cin >> q;
						if (!cin.good()) q = 1;

						if (q == 1);
						{
							printdc("Postanawiasz ponownie zagra�. Z dusz� na ramieniu i strachem w oczach rzucasz ko��mi...   ");
							do
							{
								playerdice = random(5) + 1;
								enemydice = random(5) + 1;
							} while (playerdice == enemydice);
							cout << endl;
							printdc("Wynik na Twojej ko�ci:  "); Sleep(2000); cout << playerdice << endl;
							printdc("Wynik na ko�ci �mierci:  "); Sleep(2000); cout << enemydice << endl;

							if (playerdice > enemydice)
							{
								printdc("Uda�o Ci si� odegra�! Twoje z�oto wraca do Ciebie! �mier� zosta�a pokonana.  ");
								hero.GOLD += goldlost;
								done = true;
								cout << endl;
							}
							if (playerdice < enemydice)
							{
								printdc("�mier� �mieje si� okrutnym g�osem. Czujesz jak k�adzie swoj� d�o� na Twoim ramieniu a si�y �yciowe zaczynaj� Ci� opuszcza�. Ogarnia Ci� ch��d i rozpacz...   ");
								cout << endl << "Tracisz 6 punkt�w �ywotno�ci!" << endl;
								hero.HP -= 6;
								printdc("Po odebraniu zap�aty �mier� znika zostawiaj�c Ci� samego w pustym pomieszczeniu...   ");
								done = true;
							}
						}
						if (q == 2)
						{
							printdc("Ze �mierci� lepiej nie igra�. Lepiej odej�� z pustym mieszkiem ni� pozosta� tutaj na zawsze. Stanowczo odmawiasz zostawiaj�c swoje z�oto na stole.  ");
							done = true;
						}
					}




				}
				if (y == 2)
				{
					printdc("Twoje z�oto nale�y wy��cznie do Ciebie i nie b�dziesz ryzykowa�. Poza tym, jaki cz�owiek chcia�by gra� ze �mierci�? To chyba oczywiste, �e tak pod�a istota b�dzie chcia�a oszukiwa�. Lepiej nie wdawa� si� w takie gierki.  ");
					cout << endl << "odchodzisz od sto�u i zostawiasz �mier� sam�. Ta natomiast nie odwraca si� i nie pr�buje Ci� zatrzymywa�." << endl;
					done = true;
				}
				printdc("W pomieszczeniu wieje groz�, postanawiasz jak najszybciej z niego wyj�� i kontynuowa� podr�.  "); cout << endl;

			}

			break;
		}
		case 2:
		{
			printdc(" Puszka Pandory wci�� stoi zamkni�ta. To od Ciebie zale�y czy zostanie otwarta. Co postanowisz?   ");
			cout << endl << "Otw�rz puszk� pandory: 1" << endl;
			cout << "Pozostaw puszk� zamkni�t� i ruszaj dalej: 2" << endl;
			bool done = false;
			int y;

			while (done == false)
			{
				cin >> y;
				if (!cin.good()) y = 1;

				if (y == 1)
				{
					printdc(" Postanawiasz otworzy� Puszk� Pandory. Z dusz� na ramieniu i strachem w oczach podnosisz wieko skrzyni...   ");
					Sleep(3000);
					int q = random(4);

					switch (q)
					{
					case 0:
					{
						printdc(" Skrzynia zawiera staro�ytn� bro�! Wyci�gasz z niej tajemniczy miecz �wiec�cy si� wszystkimi kolorami. Jego ostrze p�onie a r�koje�� idealnie mie�ci si� w d�oni. Z t� broni� pokonasz ka�dego przeciwnika!  ");
						cout << endl << "Zyskujesz 5 punkt�w si�y!" << endl;
						hero.STR += 5;
						done = true;
						break;

					}
					case 1:
					{
						printdc("Skrzynia zawiera z�oto! Mo�esz je zabra� ze sob�.   ");
						int gold = random(20) * 50;
						cout << endl << "Znajdujesz " << gold << " sztuk z�ota." << endl;
						hero.GOLD += gold;
						done = true;
						break;

					}
					case 2:
					{
						printdc("Po otwarciu skrzyni ca�� sal� wype�niaj� straszliwe j�ki a z puszki uuwalniaj� si� uwi�zione w niej duchy. Z krzykiem padasz na ziemi� czekaj�c a� zjawy znikn�. Wnet jedna z nich dobywa miecza i rani Ci� bole�nie.   ");
						int dmg = random(5) + 1;
						cout << endl << "Tracisz " << dmg << " punkt�w �ycia!" << endl;
						printdc("Po tym nag�ym ataku duchy znikaj� a w sali zapada cisza. Puszka stoi pusta, nie b�dzie z niej ju� �adnego po�ytku. Pora rusza� dalej.   ");
						hero.HP -= dmg;
						done = true;
						break;

					}
					case 3:
					{
						printdc(" Otwierasz Puszk� Pandory. Wieko podnosi si� bez problemu a Twoim oczom ukazuje si� sporych rozmiar�w flakon wype�niony zielon� ciecz�. Na flakonie przyklejona jest etykieta z napisem: 'ELIKSIR ZDROWIA'. By� mo�e rzeczywi�cie butelka zawiera cudownie uzdrawiaj�cy nap�j. Jednak nie znasz si� na eliksirach, wi�c ci�ko stwierdzi� czy mo�e wbrew etykiecie, eliksir jest trucizn� lub czym� gorszym.  ");
						cout << endl << "Czy zaryzykujesz wypice eliksiru?" << endl;
						cout << "Wypij: 1" << endl;
						cout << "Nie pij: 2" << endl;
						int X = random(11);
						int Y;
						cin >> Y;
						if (!cin.good()) Y = 1;
						if (Y == 1)
						{
							printdc("Otwierasz eliksir i wypijasz zawarto�� do dna.  ");
							Sleep(2000);
							if (X > 2)
							{
								printdc("ELiksir rzeczywi�cie posiada uzdrawiaj�ce w�a�ciwo�ci!  ");
								int Z = random(5) + 4;
								cout << "Otrzymujesz " << Z << " punkt�w �ycia." << endl;
								hero.HP += Z;
								
								
							}
							else
							{
								printdc("Eliksir okazuje si� trucizn�!  ");
								int Z = random(4) + 1;
								cout << "Tracisz " << Z << " punkt�w �ycia" << endl;
								hero.HP -= Z;
								
							}
						}
						if (Y == 2)
						{
							printdc("Postanawiasz nie pi� eliksiru. Lepiej nie podejmowa� takiego ryzyka podczas wyprawy.  ");

						}
						done = true;
						break;
					}

					case 4:
					{
						printdc(" Z trudem otwierasz skrzyni�. Wieko jest niesamowicie ci�kie i dopiero po kilku chwilach uda�o Ci si� je podnie��. Ku Twojemu zdziwieniu, w puszcze nie ma �adnych przedmiot�w, zamiast tego dostrzegasz niewielk� skrzydlat� wr�k�. Na Tw�j widok jej twarz wst�puje u�miech. Po chwili wylatuje ze skrzyni i oznajmia Ci, �e zosta�a tutaj uwi�ziona przez z�ego czarownika. Teraz natomiast jest wolna i z przyjemno�ci� spe�ni jedno z Twoich �ycze� w ramach rekompensaty za pomoc.  ");
						cout << endl << "Wr�ka czeka na Twoje �yczenie. Powiedz czego pragniesz najbardziej?" << endl;
						cout << "Pragn� si�y i pot�gi! : 1" << endl;
						cout << "Pragn� z�ota i bogactw! : 2" << endl;
						cout << " Pragn� by� szcz�liwym... : 3" << endl;
						cout << "Chc� aby zdrowie nigdy mnie nie opuszcza�o. : 4" << endl;
						cout << "Nie chc� niczego za ratunek, nie zrobi�em tego dla nagrody. : 5" << endl;
						int Q;
						int giftvalue;
						bool donedone = false;
						
						while (donedone == false)
						{
							cin >> Q;
							
							if (Q == 1)
							{
								printdc(" Wr�na rzuca zakl�cie. Czujesz, �e Twoje ramiona nabieraj� si� a umys� przepe�mia odwaga! Nie straszne Ci s� mroki podziemi, nie ma si�y, kt�ra mo�e Ci� powstrzyma�!  ");
								giftvalue = random(2)+2;
								cout << "Otrzymujesz "<<giftvalue<<" punkty si�y" << endl;
								hero.STR += giftvalue;
								donedone = true;

							}
							if (Q == 2)
							{
								printdc("Wr�ka macha swoj� r�d�k�  a z sufitu zaczyna pada� deszcz z�ota. Monety z d�wi�kiem uderzaj� o posadzk� czekaj�c na Ciebie.  ");
								giftvalue = random(500) + 500;
								cout << "Otrzymujesz " << giftvalue << " sztuk z�ota." << endl;
								hero.GOLD += giftvalue;
								donedone = true;
							}
							if (Q == 3)
							{
								printdc("Wr�ka u�miecha si� serdecznie i rzuca zakl�cie. Wnet czujesz, �e szcz�cie rzeczywi�cie Ci sprzyja i z jego pomoc� zdo�asz si� wymkn�� ze wszelkich tarapat�w.  ");
								giftvalue = random(2) + 1;
								cout << endl << "Twoje szcz�cie wzrasta o warto��: " << giftvalue << endl;
								hero.LCK += giftvalue;
								donedone = true;
							}
							if (Q == 4)
							{
								printdc("Wr�ka rzuca zakl�cie a wszelkie Twoje rany b�yskawicznie zaczynaj� si� leczy�. Wype�nia Ci� si�a witalna i czujesz, �e Twoja odporno�� wzrasta!  ");
								giftvalue = random(4) + 4;
								cout << endl << "Otrzymujesz " << giftvalue << " punkt�w wytrzyma�o�ci" << endl;
								hero.HP += giftvalue;
								donedone == true;
							}
							if (Q == 5)
							{
								int a = random(2);
								if (a == 0)
								{
									printdc("Wr�ka oznajmnia, �e nie spotka�a jeszcze nigdy tak dobrej i bezinteresownej osoby. Postanawia obdarzy� Ci� swoim najsilniejszym zakl�ciem. Tym razem nie pyta o zgod�.  ");
										cout << endl << "Twoja si�a wzrasta o 2 punkty!" << endl;
										cout << "Twoje szcz�cie wzrasta o 2 punkty!" << endl;
										cout << "Twoja wytrzyma�o�� wzrasta o 5 punkt�w!" << endl;
										cout << "Dodatkowo wr�ka zostawia Ci nieco z�ota na drog�" << endl;
										hero.STR += 2;
										hero.HP += 5;
										hero.LCK += 2;
										hero.GOLD += (random(500) + 250);						
								}
								else
								{
									printdc("Wr�ka wzrusza ramionami i oznajmia, �e nie naciska a jej propozycja by�a jednorazowa.  ");

								}
								donedone == true;

							}
							printdc("Po chwili wr�ka rozp�ywa si� w powietrzu pozostawiaj�c Ci� w samotno�ci. Poza pust� skrzyni�, nie ma ju� tutaj nic do roboty. Pora rusza� dalej  ");

							done = true;

						}
						break;
					}
					
					}
				}
				if (y == 2)
				{
					printdc("Nie bez powodu skrzynia stoi zamkni�ta, Lepiej pozostawi� j� w takim stanie...  ");
					cout << endl << "Zostawiasz Puszk� i ruszasz dalej" << endl;

				}
			}
			break;
		}
		case 3:
		{
			printdc("Stra�nik patrzy na Ciebie nieruchomo. Ni umiesz oszacowa� jak silnym jest przeciwnikiem. Czy zaryzykujesz walk�?  ");
			cout << endl << "Zaatakuj stra�nika: 1" << endl;
			cout << "Ruszaj w dalsz� podr�: 2" << endl;
			bool done = false;
			int x;
			while (done == false)
			{
				cin >> x;
				if (x == 1)
				{
					printdc("Dobywasz broni i ruszasz do ataku. �aden stra�nik nie jest Ci straszny kiedy w gr� wchodz� tak wielkie bogactwa!   ");
					int guard = random(20) + 4;
					int herostr = hero.STR + random(5);

					if (guard > herostr)
					{
						printdc("Stra�nik okaza� si� zbyt pot�ny. Mimo zaciek�ej walki nie uda�o Ci si� go pokonac i musisz salwowa� si� ucieczk�. Zapominasz o skarbie i bierzesz nogi za pas  ");
						int losthp = random(4) + 1;
						cout << endl << "Utracone punkty �ycia podczas walki: " << losthp << endl;
						hero.HP -= losthp;
					}
					if (herostr >= guard)
					{
						printdc("Stra�nik wcale nie by� taki silny na jakiego wygl�da�. Po nied�ugiej walce udaje Ci sie obezw�adni� przeciwnika. Mo�esz teraz dobra� si� do strze�onych bogactw.  ");
						int gold = ((random(20)+5) * guard)*5;
						cout << endl << "Zdobywasz " << gold << " sztuk z�ota!" << endl;
						hero.GOLD += gold;
						printdc("Przeciwnik pokonany, czas rusza� dalej.  ");
						cout << endl;
					}
					done = true;
				}
				if (x == 2)
				{
					printdc("Stra�nik wygl�da wyj�tkowo gro�nie. Lepiej nie ryzykowa� i ruszy� dalej w swoj� stron�...   ");
					cout << endl;
					done == true;
				}
			}
		}
		}
		
	}

	void Special_Chamber::reroll(int x)
	{
		ennumber = random(x);
	}