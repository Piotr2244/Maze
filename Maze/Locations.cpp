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
void Location::printdc(string a) //konieczne aby na koñcu tekstu daæ dwa odstêpy, po nich metoda rozpozna, ¿e koniec tekstu
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

void Location::setspeed() //obecnie nieu¿ywane
{
	cout << "Wybierz prêdkoœæ wyœwietlania tekstu" << endl;
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
	cout << endl << "ruszaj na wschód(ma³e zagro¿enie): 1" << endl << "ruszaj na zachód(œrednie zagro¿enie): 2" << endl << "ruszaj na pó³noc(du¿e zagro¿enie): 3" << endl;
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
			cout << "Nieprawid³owy numer" << endl;

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
	printdc(" Opuszczasz komnatê. Zamykasz za sob¹ drzwi i wyruszasz w dalsze poszukiwania  "); cout << endl;
	cout << "naciœnij enter by kontynuowaæ podró¿" << endl;
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
void Skirmish_Chamber::player_action(Hero& hero) //str-si³a przeciwnika , gold-nagroda za powodzenie
{
	int str = (hero.XP/4)+random(10)+1; ;
	int gold=hero.XP+10; 
	int x;
	bool done = false;
	printdc("Przeciwnik jeszcze Ciê nie zauwa¿y³. Staniesz do walki?  "); cout << endl;printdc("Czy mo¿e u¿yjesz swego szczêœcia aby ukraœæ skarb oraz  "); cout << endl; printdc("jednoczeœnie uciec bez walki?  ");cout << endl;
		cout << "Walcz z przeciwnikiem (jego si³a wynosi " << str << "): 1" << endl;
		cout << "u¿yj sprytu aby uciec i okraœæ przeciwnika: 2" << endl;
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
				cout << "Twoja si³a w walce :" << hstr << " vs " << enstr << ": wroga si³a w walce" << endl;
				Sleep(200);

				if (herowon == true)
				{
					printdc("Walka by³a zaciek³a. Mimo straszliwoœci przeciwnika, uda³o Ci siê go pokonaæ a jego skarby nale¿¹ do Ciebie  ");
					cout<<endl << "Zdobyte skarby: " << gold * str << endl;
					hero.GOLD += (gold * str);
					hero.XP += (str);
					hero.TotalEnemies++;
					done = true;
				}
				if (herowon == false)
				{
					int damage=(random(3)+1);
					printdc("Walka by³a trudna a przeciwnik okaza³ siê silniejszy ni¿ mo¿na siê by³o spodziewaæ. Walka jest przegrana.  "); cout << endl; printdc(" mimo wyczerpania, ostatkiem si³ uciekasz w stronê drzwi i opuszczasz komnatê.  "); cout << endl;
					cout << "utracone punkty ¿ycia: " << damage << endl;
					hero.HP -= damage;
					done = true;
				}			
			}
			if (x == 2)
			{
				if (hero.LCK <= 0)
				{
					cout << "Nie masz punktów szczêœcia! Nie mo¿esz ich u¿yæ w tej sytuacji!" << endl;
					
				}
				else
				{
					printdc("Dziêki swojemu nieopisanemu szczêœciu, zakradasz siê do przeciwnika i wykradasz jego z³oto.  "); cout << endl; printdc("Kiedy przeciwnik zdaje sobie sprawê, ¿e zosta³ okradziony, Ty spokojnie wymykasz siê z komnaty  "); cout << endl;
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
	    printdc("Czy chcesz podejœæ do skrzyni i spróbowaæ j¹ otworzyæ?  "); cout << endl;
		cout << " Zaryzykuj i otwórz skrzynkê: 1" << endl;
		cout << " Zostaw skrzynkê i ruszaj dalej: 2" << endl;
		bool done = false;

		while (done == false)
		{
			cin >> y;
			if (!cin.good()) y = 1;
			if (y == 1)
			{
				printdc("Postanawiasz podejœæ do skrzynki i j¹ otworzyæ. Powoli zdejmujesz wieki a Twoim oczom ukazuje siê sterta z³otych monet!  "); cout << endl; printdc("Bez zawachania zabierasz wszystkie monety i z uœmiechem na twarzy ruszasz w dalsz¹ podró¿.  "); cout << endl;
				int gold = hero.XP * 10 + 100;
				cout << " Zdobyte z³oto: " << gold << " z³otych monet" << endl;
				Sleep(2000);
				hero.GOLD += gold;
				done = true;
			}
			if(y == 2)
			{
				printdc("Postanawiasz nie ruszaæ skrzyni. Ostro¿noœci nigdy zbyt wiele. Byæ mo¿e w³aœnie uda³o siê unikn¹æ œmiertelnej pu³apki?  "); cout << endl; printdc("Nie myœl¹c wiele, zapominasz o skrzyni i ruszasz w kierunku wyjœcia z komnaty  ");
				done = true;
			}
		}
		break;
	}
	case 1:
	{
		printdc("Czy chcesz podejœæ do skrzyni i spróbowaæ j¹ otworzyæ?  "); cout << endl;
		cout << " Zaryzykuj i otwórz skrzynkê: 1" << endl;
		cout << " Zostaw skrzynkê i ruszaj dalej: 2" << endl;
		bool done = false;
		cin >> y;
		if (!cin.good()) y = 1;
		if (y == 1)
		{
			printdc("Postanawiasz podejœæ do skrzynki i j¹ otworzyæ. Jednak w momencie dotkniêcia wieka, s³yszysz jak w skrzyni aktywuje siê mechanizm obronny.  "); cout << endl; printdc("Z dziurki na klucz wyskakuje zatruta ig³a, która kaleczy Ciê boleœnie.  "); cout << endl;
			int damage = (random(3) + 1);
			cout << " Otrzymane obra¿enia: " << damage << endl;
			Sleep(1000);
			hero.HP -= damage;
			printdc("Pu³aka jest dezaktywowana. Mo¿esz teraz dobraæ siê do skarbu, który znajduje siê na dnie skrzynki  "); cout << endl;
			int gold = hero.XP * 10 + 100;
			cout << " Zdobyte z³oto: " << gold << " z³otych monet" << endl;
			hero.GOLD += gold;
			Sleep(1000);
			done = true;
		}
		if (y == 2)
		{
			printdc("Postanawiasz nie ruszaæ skrzyni. Ostro¿noœci nigdy zbyt wiele. Byæ mo¿e w³aœnie uda³o siê unikn¹æ œmiertelnej pu³apki?  "); cout << endl; printdc("Nie myœl¹c wiele, zapominasz o skrzyni i ruszasz w kierunku wyjœcia z komnaty  "); cout << endl;
			done = true;
		}
		break;
	}
	case 2:
	{
		printdc("Czy chcesz podejœæ do skrzyni i spróbowaæ j¹ otworzyæ?  "); cout << endl;
		cout << " Zaryzykuj i otwórz skrzynkê: 1" << endl;
		cout << " Zostaw skrzynkê i ruszaj dalej: 2" << endl;
		bool done = false;
		cin >> y;
		if (!cin.good()) y = 1;
		if (y == 1)
		{
			printdc("Postanawiasz podejœæ do skrzynki i j¹ otworzyæ. Jednak w momencie dotkniêcia wieka, s³yszysz jak w skrzyni aktywuje siê mechanizm obronny.  "); cout << endl; printdc("Z dziurki na klucz wyskakuje zatruta ig³a, która kaleczy Ciê boleœnie.  "); cout << endl;
			int damage = (random(3) + 1);
			cout << " Otrzymane obra¿enia: " << damage << endl;
			Sleep(1000);
			hero.HP -= damage;
			printdc("Pu³aka jest dezaktywowana. Skrzynia natomiast, stoi pusta. Z grymasem na ustach, odchodzisz od pustej skrzyni.  "); cout << endl;
			Sleep(500);
			done = true;
		}
		if (y == 2)
		{
			printdc("Postanawiasz nie ruszaæ skrzyni. Ostro¿noœci nigdy zbyt wiele. Byæ mo¿e w³aœnie uda³o siê unikn¹æ œmiertelnej pu³apki?  "); cout << endl; printdc("Nie myœl¹c wiele, zapominasz o skrzyni i ruszasz w kierunku wyjœcia z komnaty  "); cout << endl;
			done = true;
		}
		break;
	}
	case 3:
	{
		printdc("Czy chcesz podejœæ do skrzyni i spróbowaæ j¹ otworzyæ?  "); cout << endl;
		cout << " Zaryzykuj i otwórz skrzynkê: 1" << endl;
		cout << " Zostaw skrzynkê i ruszaj dalej: 2" << endl;
		bool done = false;
		while (done == false)
		{
			cin >> y;
			if (!cin.good()) y = 1;
			if (y == 1)
			{
				printdc("Postanawiasz podejœæ do skrzynki i j¹ otworzyæ. Podnosisz wieko bez oporu. Na dnie skrzynki dostrzegasz fiolkê z eliksirem.  "); cout << endl; printdc("Nie potrafisz rozpoznaæ dziwnej substancji. Czy chcesz zaryzykowaæ i wypiæ eliksir?  "); cout << endl;
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
							printdc("Eliksir dzia³a na Ciebie orzeŸwiaj¹co, czujesz jak Twoje si³y witalne do Ciebie wracaj¹ a rany lecz¹ siê same  "); cout << endl;
							int hp = random(5) + 1;
							cout << "Zdobyte punkty ¿ycia: " << hp << endl;
							Sleep(1000);
							hero.HP += hp;
							done2 = true;
						}
						if (z == 1)
						{
							printdc("Eliksir przepe³nia Ciê si³¹ i gniewem. Czujesz, ¿e mo¿esz osi¹gn¹æ wszystko i ¿adne okropnoœci podziemi nie s¹ dla Ciebie wyzwaniem  "); cout << endl;
							int str = random(2) + 1;
							cout << "Zdobyte punkty si³y: " << str << endl;
							Sleep(1000);
							hero.STR += str;
							done2 = true;
						}
						if (z == 2)
						{
							printdc("Eliksir nie wp³ywa nijak na Ciebie. Po chwili jednak czujesz, ¿e szczêœcie Ci dopisuje i z jego pomoc¹ uda Ci siê przetrwaæ najwiêksze okropnoœci podziemi  "); cout << endl;
							cout << "Otrzymujesz dodatkowy punkt szczêœcia!" << endl;
							Sleep(1000);
							hero.LCK++;
							done2 = true;
						}
						if (z == 3)
						{
							printdc("Eliksir okazuje siê trucizn¹!  "); cout << endl;
							int damage = (random(2) + 1);
							cout << " Otrzymane obra¿enia: " << damage << endl;
							Sleep(1000);
							hero.HP -= damage;
							done2 = true;
						}
						printdc("Odrzucasz pust¹ fiolkê i ruszasz dalej w drogê  ");
						hero.TotalPotions++;
						done = true;
					}
					if (q == 2)
					{
						printdc("Wolisz nie ryzykowaæ. Nikt nie wie czym jest tajemniczy eliksir. Mo¿e lepiej tym razem zaniechaæ i ruszyæ dalej  "); cout << endl; printdc("Odk³adasz fiolkê do skrzyni i ruszasz w dalsz¹ drogê  "); cout << endl;
						done2 = true;
						done = true;
					}

				}
			}

			if (y == 2)
			{
				printdc("Postanawiasz nie ruszaæ skrzyni. Ostro¿noœci nigdy zbyt wiele. Byæ mo¿e w³aœnie uda³o siê unikn¹æ œmiertelnej pu³apki?  "); cout << endl; printdc("Nie myœl¹c wiele, zapominasz o skrzyni i ruszasz w kierunku wyjœcia z komnaty  "); cout << endl;
				done = true;
			}
		}
		Sleep(1000);
		break;
	}
	case 4:
	{
		printdc("Czy chcesz podejœæ do skrzyni i spróbowaæ j¹ otworzyæ?  "); cout << endl;
		cout << " Zaryzykuj i otwórz skrzynkê: 1" << endl;
		cout << " Zostaw skrzynkê i ruszaj dalej: 2" << endl;
		bool done = false;
		int x;
		while (done == false)
		{
			cin >> x;
			if (x == 1)
			{
				printdc("Wieko skrzyni jest ciê¿kie, mija d³uga chwila zanim udaje Ci siê je podnieœæ. Jednak widok, który zauwa¿asz w œrodku zdecydowanie by³ wart wysi³ku  "); cout << endl; printdc("Skrzynia jest pe³na z³ota i kosztownoœci!  "); cout << endl;
				int gold = hero.XP * 20 + 300;
				cout << " Zdobyte z³oto: " << gold << " z³otych monet" << endl;
				Sleep(2000);
				hero.GOLD += gold;
				done = true;
			}
			if (x == 2)
			{
				printdc("Postanawiasz nie ruszaæ skrzyni. Ostro¿noœci nigdy zbyt wiele. Byæ mo¿e w³aœnie uda³o siê unikn¹æ œmiertelnej pu³apki?  "); cout << endl; printdc("Nie myœl¹c wiele, zapominasz o skrzyni i ruszasz w kierunku wyjœcia z komnaty  ");
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
		printdc("Nad sadzawk¹ unosi siê tajemnicza aura. Czy zaryzykujesz kompiel?  "); cout << endl;
		bool done = false;
		cout << "WejdŸ do sadzawki: 1" << endl;
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
						printdc("Zaczarowana woda dzia³a koj¹co na Twoje rany. Czujesz, ¿e wszelkie si³y witalne wracaj¹ do Ciebie.  "); cout << endl;
						int hp = random(6) + 1;
						cout << "Zdobyte punkty ¿ycia: " << hp << endl;
						Sleep(1000);
						hero.HP += hp;
						done2 = true;
					}
					if (z == 1)
					{
						printdc("Zimna woda przeszywa Ciê i hartuje. Czujesz jak Twoje miêœnie staj¹ siê twardsze a odpornoœæ roœnie.  "); cout << endl;
						int str = random(2) + 1;
						cout << "Zdobyte punkty si³y: " << str << endl;
						Sleep(1000);
						hero.STR += str;
						done2 = true;
					}
					if (z == 2)
					{
						printdc("Na dnie sadzawki dostrzegasz z³ote monety! Bez zawachania nurkujesz pod wodê i zbierasz je wszystkie.  "); cout << endl;
						int gold = hero.XP * 10 + 200;
						cout << " Zdobyte z³oto: " << gold << " z³otych monet" << endl;
						Sleep(2000);
						hero.GOLD += gold;
						done2 = true;
					}
					if (z == 3)
					{
						printdc("Po zanurzeniu w sadzawce przeszywa Ciê straszliwy ból. Twoja skóra pali Ciê niczym ogieñ!  "); cout << endl; printdc("Mimo licznych oparzeñ, wyskakujesz z sadzawki i resztkami si³ ruszasz w stronê wyjœcia z komnaty.  "); cout << endl;
						int damage = (random(2) + 1);
						cout << " Otrzymane obra¿enia: " << damage << endl;
						Sleep(1000);
						hero.HP -= damage;
						done2 = true;
					}
					done = true;
					
				}
				if (q == 2)
				{
					printdc("Wolisz nie ryzykowaæ. Woda w sadzawce wygl¹da podejrzanie, kto wie czym skoñczyæ siê mo¿e kompiel.  "); cout << endl; printdc("Odwracasz wzrok i ruszasz w kierunku wyjœcia z komnaty.  "); cout << endl;
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
		printdc("Czy chcesz zagadaæ kowala?  "); cout << endl;
		cout << " Zagadaj kowala: 1" << endl;
		cout << " OdejdŸ w swoj¹ stronê: 2" << endl;
		bool done = false;
		while (done == false)
		{
			cin >> y;
			if (!cin.good()) y = 3;
			if (y == 1)
			{
				printdc("Kowal obraca siê i patrzy na Ciebie bystrym wzrokiem. Po chwili gasi fajkê i oznajmia, ¿e wykuwa tutaj orê¿ najlepszej jakoœci  "); cout << endl; printdc("Za odpowiedni¹ op³at¹, kowal sprzeda Ci broñ, która z ³atwoœci¹ pokona ka¿dego napotkanego wroga  "); cout << endl;
				cout << "Czy chcesz zakupiæ now¹ broñ?" << endl;
				cout << "Cena zwyk³ej broni: 150 Z³ota (si³a zwiêkszona o 1 punkt), [Zakup:1]" << endl;
				cout << "Cena potê¿nej broni: 250 Z³ota (si³a zwiêkszona o 2 punkty), [Zakup:2]" << endl;
				cout << "Cena mistrzowskej broni: 500 Z³ota (si³a zwiêkszona o 4 punkty),[Zakup:3]" << endl;
				cout << " Nie mam na to czasu ani pieniêdzy! [Nic nie kupuj:4]" << endl;
				int q;
				bool done2 = false;
				while (done2 == false)
				{
					cin >> q;
					if (!cin.good()) q = 5;
					if (q == 1)
					{
						if (hero.GOLD < 100) cout << "Nie masz tyle z³ota!" << endl;
						else
						{
							hero.GOLD -= 100;
							hero.STR += 1;
								printdc("Zakupi³eœ zwyk³¹ broñ.  "); cout << endl;
								done2 = true;
						}

					}
					if (q == 2)
					{
						if (hero.GOLD < 250) cout << "Nie masz tyle z³ota!" << endl;
						else
						{
							hero.GOLD -= 250;
							hero.STR += 2;
							printdc("Zakupi³eœ potê¿n¹ broñ.  "); cout << endl;
							done2 = true;
						}
					}
					if (q == 3)
					{
						if (hero.GOLD < 500) cout << "Nie masz tyle z³ota!" << endl;
						else
						{
							hero.GOLD -= 500;
							hero.STR += 4;
							printdc("Zakupi³eœ mistrzowsk¹ broñ.  "); cout << endl;
							done2 = true;
						}
					}
					if (q == 4)
					{
						printdc("Odstêpujesz od kowala nie dokonuj¹æ zakupu.  "); cout << endl;
						done2 = true;
					}

				}
				printdc("Wystarczy handlowania na dzisiaj. Pora ruszaæ dalej  "); cout << endl;

				done = true;
			}
			if (y == 2)
			{
				printdc("Nie ma czasu rozmawiaæ z nieznajomymi.Pora ruszaæ dalej.  "); cout << endl; printdc("Odwracasz wzrok i ruszasz w kierunku wyjœcia z sali.  "); cout << endl;
				done = true;
			}
		}
		break;
	}
	case 2:
	{
		printdc("Nieznajomy wci¹¿ patrzy na Ciebie. Czy chcesz podejœæ i zagadaæ?  "); cout << endl;
		cout << "PodejdŸ bli¿ej do tajemniczej postaci: 1" << endl;
		cout << "Odwróæ siê i odejdŸ w swoj¹ stronê : 2" << endl;
		bool done = false;
		while (done == false)
		{
			cin >> y;
			if (!cin.good()) y = 1;
			if (y == 1)
			{
				printdc("Zbli¿asz siê do nieznajomego. Jego wzrok jest zimny i nieprzyjazny. Postaæ wci¹¿ milczy.  "); cout << endl;

				int z;
				bool done2 = false;
				z = random(4);
				

				while (done2 == false)
				{
					
						if (z == 0)
						{
							printdc("Nieznajomy wyci¹ga d³oñ w Twoj¹ stronê. Dostrzegasz, ¿e trzyma w niej sakiewkê. Kiedy zagl¹dasz do niej, dostrzegasz szczeroz³ote monety!  "); cout << endl;
							int gold = random(400) + 1;
							cout << "Zdobywasz " << gold << " z³otych monet!" << endl;
							hero.GOLD += gold;
							Sleep(3000);
							printdc("Kiedy znów podnosisz wzrok, tajemniczej postaci ju¿ nie ma w komnacie. Zniknê³a lub rozp³ynê³a siê w powietrzu.  "); cout << endl;
							done2 = true;
							done = true;
						}
						if (z == 1)
						{
							printdc("Kiedy ruszasz do przodu, tajemnicza postaæ robi krok w Twoj¹ stronê. Zanim jednak zd¹¿y³eœ przemówiæ, nieznajomy wyci¹gn¹³ ukryty pod szat¹ sztylet!  "); cout << endl; printdc("Nie by³o czasu na reakcje. Nieznajomy zadaje Ci bolesny cios sztyletem a nastêpnie znika w mgnieniu oka. Pozostajesz samotnie w pustej sali.  "); cout << endl;
							int dmg = random(4) + 1;
							cout << "Tracisz " << dmg << " punkty ¿ycia" << endl;
							hero.HP -= dmg;
							Sleep(3000);
							printdc("Wci¹¿ czuj¹æ ból po niespodziewanym ataku, ruszasz w kierunku wyjœcia z komnaty  "); cout << endl;
							done2 = true;
							done = true;
						}
						if (z == 2)
						{
							printdc("Tajemnicza postaæ wyci¹ga d³oñ w Twoim kierunku. Dostrzegasz, ¿e trzyma w niej tajemnicz¹ fiolkê. Zapewne jest to eliksir.  "); cout << endl; printdc("Kiedy odbierasz fiolkê z d³oni nieznajomego, ten rozp³ywa siê w powietrzu i zostawia Ciê w pustej komnacie  "); cout << endl;
							printdc("Nie potrafisz rozpoznaæ dziwnej substancji w fiolce. Czy chcesz zaryzykowaæ i wypiæ eliksir?  "); cout << endl;
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
										printdc("Eliksir dzia³a na Ciebie orzeŸwiaj¹co, czujesz jak Twoje si³y witalne do Ciebie wracaj¹ a rany lecz¹ siê same  "); cout << endl;
										int hp = random(5) + 1;
										cout << "Zdobyte punkty ¿ycia: " << hp << endl;
										Sleep(1000);
										hero.HP += hp;
										done3 = true;
									}
									if (k == 1)
									{
										printdc("Eliksir przepe³nia Ciê si³¹ i gniewem. Czujesz, ¿e mo¿esz osi¹gn¹æ wszystko i ¿adne okropnoœci podziemi nie s¹ dla Ciebie wyzwaniem  "); cout << endl;
										int str = random(2) + 1;
										cout << "Zdobyte punkty si³y: " << str << endl;
										Sleep(1000);
										hero.STR += str;
										done3 = true;
									}
									if (k == 2)
									{
										printdc("Eliksir nie wp³ywa nijak na Ciebie. Po chwili jednak czujesz, ¿e szczêœcie Ci dopisuje i z jego pomoc¹ uda Ci siê przetrwaæ najwiêksze okropnoœci podziemi  "); cout << endl;
										cout << "Otrzymujesz dodatkowy punkt szczêœcia!" << endl;
										Sleep(1000);
										hero.LCK++;
										done3 = true;
									}
									if (k == 3)
									{
										printdc("Eliksir okazuje siê trucizn¹!  "); cout << endl;
										int damage = (random(2) + 1);
										cout << " Otrzymane obra¿enia: " << damage << endl;
										Sleep(1000);
										hero.HP -= damage;
										done3 = true;
									}
									printdc("Odrzucasz pust¹ fiolkê i ruszasz dalej w drogê  ");
									hero.TotalPotions++;
									done2 = true;
								}
								if (j == 2)
								{
									printdc("Wolisz nie ryzykowaæ. Nikt nie wie czym jest tajemniczy eliksir. Mo¿e lepiej tym razem zaniechaæ i ruszyæ dalej  "); cout << endl;
									done3 = true;
									done2 = true;
								}
								done = true;
							}			
						}
						if (z == 3)
						{
							printdc("Kiedy podchodzisz bli¿ej, tajemnicza postaæ rozp³ywa siê w powietrzu i zostawia Ciê w pustej sali. Nie zosta³o tutaj nic do roboty, pora ruszaæ dalej  "); cout << endl;
							done2 = true;
							done = true;
						}
						Sleep(1500);
				}
			}
			if (y == 2)
			{
				printdc("Lepiej nie ufaæ nieznajomym. Zw³aszcza takim dziwakom jak ten stoj¹cy przed Tob¹.  "); cout << endl; printdc("Odwracasz siê na piêcie i ruszasz w stronê wyjœcia z komnaty.  "); cout << endl;
				done = true;
			}
		}
		break;
	}
	case 3:
	{
		printdc("Mechanizm wygl¹da na groŸny. Musisz jednak znaleŸæ sposób na przebrniêcie przez pu³apkê.  "); cout << endl;
		cout << "Spróbuj wykonaæ olbrzymi skok aby przeskoczyæ pu³apkê [licz¹c na swoj¹ si³ê]: 1" << endl;
		cout << " Spróbuj przejœæ przez pu³apkê licz¹c, ¿e nie zostanie ona aktywowana [licz¹c na swoje szczêœcie]: 2" << endl;
		cout << "PrzejdŸ przez pu³apkê licz¹æ na to, ¿e zdo³asz wytrzymaæ jej okropieñstwa [licz¹æ na swoj¹ wytrzyma³oœæ]: 3" << endl;
		bool done = false;
		int z = random(2);
		while (done == false)
		{
			cin >> y;
			if (!cin.good()) y = 4;
			if (y == 1)
			{
				printdc("Przygotowujesz siê do skoku. Bierzesz olbrzymi rozbieg i z ca³ych si³ wybijasz siê w powietrze  "); cout << endl;
				if (z == 0)
				{
					printdc("Skok koñczy siê olbrzymim sukcesem! Zrêcznie l¹dujesz na ziemi zostawiaj¹c pu³apkê za sob¹.  "); cout << endl;
				}
				if (z == 1)
				{
					printdc("To nie by³ dobry skok. Z³y rozbieg oraz niepoprawne l¹dowanie doprowadzi³y do powa¿nego zranienia  "); cout << endl; printdc("Uda³o siê pokonaæ pu³apkê, jednak Twoja si³a uleg³a znacznemu os³anieniu  "); cout << endl;
					cout << "Tracisz 2 punkty si³y!" << endl;
					hero.STR -= 2;
				}
				done = true;
			}
			if (y == 2)
			{
				printdc("Polegaj¹c na w³asnym szczêœciu, powoli zaczynasz stawiaæ kroki na pu³apce.  "); cout << endl;
				if (hero.LCK > 0)
				{
					printdc("Dziêki swojemu szczêœciu, udaje Ci siê przejœæ przez pu³apkê bez aktywowania mechanizmu.  "); cout << endl; printdc("Kosztowa³o Ciê to jednak punkt szczêœcia!  "); cout << endl;
					hero.LCK--;
					hero.TotalLuckUsed++;
				}
				else
				{
					printdc("Niestety, zabrak³o Ci szczêœcia! Po kilku krokach mechanizm uruchomi³ siê a z pod³ogi wystrzeli³y zabójcze kolce!  "); cout << endl;
					int dmg = random(5) + 2;
					cout << "Tracisz " << dmg << " punktów ¿ycia!" << endl;
					Sleep(2000);
					hero.HP -= dmg;
				}
				done = true;
			}
			if (y == 3)
			{
				printdc("Z szalenstwem w oczach wstêpujesz na pu³apkê.  "); cout << endl;
				Sleep(3000);
				if (z == 0)
				{
					printdc("Mimo ostrych kolców rani¹cych Ciê z ka¿dej strony, udaje Ci siê przejœæ pu³apkê nie odnosz¹æ bardzo powa¿nych obra¿eñ.  "); cout << endl;
					int dmg = random(2) + 2;
					cout << "Tracisz " << dmg << " punktów ¿ycia!" << endl;
					Sleep(1000);
					hero.HP -= dmg;
				}
				if (z == 1)
				{
					printdc("To by³o szaleñstwo! Ostre kolce pu³apki rani¹ Ciê z ka¿dej strony. Udaje Ci siê przejœæ na drug¹ stronê, jednak otrzyma³eœ liczne rany  "); cout << endl;
					int dmg = random(5) + 3;
					cout << "Tracisz " << dmg << " punktów ¿ycia!" << endl;
					Sleep(1000);
					hero.HP -= dmg;
				}
				done = true;
			}
		}
		printdc("Pu³apka pokonana. Mo¿esz ruszaæ dalej  ");cout << endl;
		Sleep(2000);
		break;
	}
	case 4:
	{
		printdc("Totem a¿ emanuje moc¹ chaosu. Czy odwa¿ysz siê go dotkn¹æ?  "); cout << endl;
		cout << " Dotknij totemu licz¹æ na b³ogos³awienstwo chaosu: 1" << endl;
		cout << " Zostaw totem i rusz w dalsz¹ drogê: 2" << endl;
		bool done = false;
		int x;
		int z = random(9);
		while (done == false)
		{
			cin >> x;
			if (x == 1)
			{
				printdc("Powolnym krokiem zbli¿asz siê do totemu. Dr¿¹c¹ rek¹ dotykasz kamienia i pozwalasz aby moc chaosu zdecydowa³a o Twoim losie...  "); cout << endl;
				switch (z)
				{
				case 0:
				{
					printdc("Moce chaosu obdzieraj¹ Ciê z si³ witalnych!  "); cout << endl;
					Sleep(2000);
					int dmg = random(3) + 1;
					cout << "tracisz " << dmg << " punktów ¿ycia!"<< endl;
					hero.HP -= dmg;
					break;
				}
				case 1:
				{
					printdc("Moce chaosu dodaj¹ Ci wytrzyma³oœci!  "); cout << endl;
					Sleep(2000);
					int hp = random(4) + 1;
					cout << "zyskujesz " << hp << " punktów ¿ycia!" << endl;
					hero.HP += hp;
					break;
				}
				case 2:
				{
					printdc("Moce chaosu nagradzaj¹ Ciê bogactwem!  "); cout << endl;
					Sleep(2000);
					int gold = random(300) + 100;
					cout << "zyskujesz " << gold << " z³otych monet!!" << endl;
					hero.GOLD += gold;
					break;
				}
				case 3:
				{
					printdc("Moce chaosu œmiej¹ siê z Ciebie i odbieraj¹ Twoje z³oto!  "); cout << endl;
					Sleep(2000);
					int gold = random(300) + 100;
					cout << "Tracisz " << gold << " z³otych monet!!" << endl;
					hero.GOLD -= gold;
					break;
				}
				case 4:
				{
					printdc("Moce chaosu odaj¹ Twym ramionom si³!  "); cout << endl;
					Sleep(2000);
					int str = random(3) + 1;
					cout << "zyskujesz " << str << " Punktów si³y!" << endl;
					hero.STR += str;
					break;
				}
				case 5:
				{
					printdc("Moce chaosu bêd¹ nad Tob¹ czuwaæ!  "); cout << endl;
					Sleep(2000);
					int lck = random(1) + 1;
					cout << "zyskujesz " << lck << " punkty szczêœcia!" << endl;
					hero.LCK += lck;
					break;
				}
				case 6:
				{
					printdc("Moce chaosu odbieraj¹ Ci nadziejê na zwyciêstwo...  "); cout << endl;
					Sleep(2000);
					cout << " Tracisz wszystkie punkty szczêœcia!!" << endl;
					hero.LCK = 0;
					break;
				}
				case 7:
				{
					printdc("Moce chaosu mianuj¹ Ciê swoim wybrañcem!  "); cout << endl;
					Sleep(2000);					
					cout << "Twoja si³a, szczêœcie i wytrzyma³oœc wzrastaj¹!! W sakiewce natomiast znajdujesz dodatkowe z³oto." << endl;
					hero.GOLD += 200;
					hero.STR++;
					hero.LCK++;
					hero.HP += 3;
					break;
				}
				case 8:
					printdc("Ziemia siê trzêcie... Czujesz, ¿e w podziemiach w³aœnie sta³o siê coœ straszliwego.  "); cout << endl; printdc(" Wychodzisz z sali, jednak czujesz, ¿e podziemia szykuj¹ dla Ciebie test, którego nie sposób zdaæ...  "); cout << endl;
					Sleep(3000);
					hero.XP += 100;
					break;

				}
				done = true;
			}
			if (x == 2)
			{
				printdc("Z mocami chaosu nie powinno siê igraæ. Odwracasz siê i ruszasz w kierunku wyjœcia.  "); cout << endl; printdc("Wci¹¿ s³yszysz szepty chaosu za plecami. Opuszczasz t¹ salê tak szybko jak potrafisz.  ");
				done = true;
			}
		}
		printdc("Nie powinno siê zostawaæ w tej komnacie d³u¿ej ni¿ to konieczne. Czas ruszaæ dalej.  "); cout << endl;
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
			printdc("Z³oto nale¿y do Ciebie. Mo¿esz bez porblemów zabraæ wszystko ze sob¹.  ");
			int gold = (hero.TotalChambers * 100);
			cout << endl << "Znalaz³eœ " << gold << " sztuk z³ota! To prawdziwe bogactwo!" << endl;
			hero.GOLD += gold;
			break;
		}
		case 1:
		{
			printdc("Czy podejmiesz wyzwanie i zagrasz ze œmierci¹ o ca³e swoje z³oto?  ");
			int y;
			bool done = false;
			cout << endl << "Zagraj w koœci ze œmierci¹: 1" << endl;
			cout << "Nie ryzykuj i ruszaj w dalsz¹ podró¿: 2" << endl;
			while (done == false)
			{
				cin >> y;
				if (!cin.good()) y= 1;
				if (y == 1)
				{
					printdc("Postanawiasz postawiæ ca³e swoje z³oto i zagraæ. Oboje siêgacie po koœci i jednoczeœnie rzucacie na stó³...  ");
					int playerdice;
					int enemydice;
					do
					{
						playerdice = random(5) + 1;
						enemydice = random(5) + 1;
					} while (playerdice == enemydice);
					cout << endl;
					printdc("Wynik na Twojej koœci:  "); Sleep(2000); cout << playerdice << endl;
					printdc("Wynik na koœci œmierci:  "); Sleep(2000); cout << enemydice << endl;

					if (playerdice > enemydice)
					{
						printdc("Szczêœcie by³o z Tob¹! Uda³o Ci siê pokonaæ œmieræ i Twoje z³oto jest teraz podwojone!  "); cout << endl; Sleep(2000);
						hero.GOLD = (hero.GOLD * 2);
						cout << " posiadasz teraz " << hero.GOLD << " z³ota." << endl;
						printdc("Œmieræ wci¹¿ patrzy w Twoj¹ stronê. Po chwili oznajmia Ci, ¿e chce siê odegraæ i proponuje rewan¿ na Tych samych zasadach co poprzednia rozgrywka. Je¿eli wygrasz, Twoje z³oto ponownie zostanie podwojone. Je¿eli przegrasz, œmieræ zabierze ca³e z³oto...  ");
						cout << endl << "Czy przystaniesz na propozycjê œmierci i ponownie postawisz ca³e swoje z³oto?" << endl;
						cout << "Zagraj w koœci ponownie: 1" << endl;
						cout << "OdejdŸ z dotychczasow¹ wygran¹: 2" << endl;
						int q;
						cin >> q;
						if (!cin.good()) q = 1;
						if (q == 1)
						{
							printdc(" Postanawiasz zagraæ jeszcze raz  "); cout << endl;
							do
							{
								playerdice = random(5) + 1;
								enemydice = random(5) + 1;
							} while (playerdice == enemydice);
							cout << endl;
							printdc("Wynik na Twojej koœci:  "); Sleep(2000); cout << playerdice << endl;
							printdc("Wynik na koœci œmierci:  "); Sleep(2000); cout << enemydice << endl;

							if (playerdice > enemydice)
							{
								printdc("Szczêœcie by³o z Tob¹! Uda³o Ci siê pokonaæ œmieræ i Twoje z³oto jest teraz podwojone!   "); cout << endl; Sleep(2000);
								hero.GOLD = (hero.GOLD * 2);
								cout << " posiadasz teraz " << hero.GOLD << " z³ota." << endl;
								Sleep(2000);
								printdc("Œmieræ stoi nieruchomo. Uda³o Ci siê okpiæ j¹ dwukrotnie, pozosta³o jej jedynie odejœcie z opuszczon¹ g³ow¹. Z³oto jest Twoje.   ");

								done = true;
							}
							if (playerdice < enemydice)
							{
								printdc("Œmieræ œmieje siê g³oœno. Zwyciêstwo nale¿y do niej i zgodnie z umow¹, ca³e Twoje z³oto przepada!  ");
									cout << endl;
								hero.GOLD = 0;
								done == true;

							}
							
						}
						if (q == 2);
						{
							printdc("To oczywiste, ¿e œmieræ chce Ciê oszukaæ! Wygra³eœ z³oto i nie masz zamiaru graæ jeszcze raz. Z uœmiechem na twarzy zabierasz ca³e z³oto ze sto³u i ruszasz w stronê wyjœcia.  ");
							done = true;
						}

					}
					if (playerdice < enemydice)
					{
						printdc("Œmieræ œmieje siê g³oœno. Zwyciêstwo nale¿y do niej i zgodnie z umow¹, ca³e Twoje z³oto przepada!  ");
						cout << endl;
						int goldlost = hero.GOLD;
						hero.GOLD = 0;
						Sleep(2000);
						printdc("Na Twojej twarzy maluje siê smutek i rozgoryczenie. Ca³e Twoje z³oto przepad³o. Po chcili milczenia, Œmieræ ponownie zabiera g³os. Proponuje Ci rewan¿, Je¿eli zwyciêzysz, odzyskasz ca³e swoje z³oto. Je¿eli jednak przegrasz, œmieræ odbierze Ci czêœæ swojej duszy jako zap³atê...   ");
						cout << endl << "Stawka jest wysoka. Czy chcesz ponownie zagraæ w koœci na ustalonych powy¿ej warunkach?" << endl;
						cout << "Zagraj o z³oto i swoj¹ duszê: 1" << endl;
						cout << "Nie ryzykuj i odejdŸ bez z³ota: 2" << endl;
						int q;
						cin >> q;
						if (!cin.good()) q = 1;

						if (q == 1);
						{
							printdc("Postanawiasz ponownie zagraæ. Z dusz¹ na ramieniu i strachem w oczach rzucasz koœæmi...   ");
							do
							{
								playerdice = random(5) + 1;
								enemydice = random(5) + 1;
							} while (playerdice == enemydice);
							cout << endl;
							printdc("Wynik na Twojej koœci:  "); Sleep(2000); cout << playerdice << endl;
							printdc("Wynik na koœci œmierci:  "); Sleep(2000); cout << enemydice << endl;

							if (playerdice > enemydice)
							{
								printdc("Uda³o Ci siê odegraæ! Twoje z³oto wraca do Ciebie! Œmieræ zosta³a pokonana.  ");
								hero.GOLD += goldlost;
								done = true;
								cout << endl;
							}
							if (playerdice < enemydice)
							{
								printdc("Œmieræ œmieje siê okrutnym g³osem. Czujesz jak k³adzie swoj¹ d³oñ na Twoim ramieniu a si³y ¿yciowe zaczynaj¹ Ciê opuszczaæ. Ogarnia Ciê ch³ód i rozpacz...   ");
								cout << endl << "Tracisz 6 punktów ¿ywotnoœci!" << endl;
								hero.HP -= 6;
								printdc("Po odebraniu zap³aty Œmieræ znika zostawiaj¹c Ciê samego w pustym pomieszczeniu...   ");
								done = true;
							}
						}
						if (q == 2)
						{
							printdc("Ze Œmierci¹ lepiej nie igraæ. Lepiej odejœæ z pustym mieszkiem ni¿ pozostaæ tutaj na zawsze. Stanowczo odmawiasz zostawiaj¹c swoje z³oto na stole.  ");
							done = true;
						}
					}




				}
				if (y == 2)
				{
					printdc("Twoje z³oto nale¿y wy³¹cznie do Ciebie i nie bêdziesz ryzykowa³. Poza tym, jaki cz³owiek chcia³by graæ ze Œmierci¹? To chyba oczywiste, ¿e tak pod³a istota bêdzie chcia³a oszukiwaæ. Lepiej nie wdawaæ siê w takie gierki.  ");
					cout << endl << "odchodzisz od sto³u i zostawiasz Œmieræ sam¹. Ta natomiast nie odwraca siê i nie próbuje Ciê zatrzymywaæ." << endl;
					done = true;
				}
				printdc("W pomieszczeniu wieje groz¹, postanawiasz jak najszybciej z niego wyjœæ i kontynuowaæ podró¿.  "); cout << endl;

			}

			break;
		}
		case 2:
		{
			printdc(" Puszka Pandory wci¹¿ stoi zamkniêta. To od Ciebie zale¿y czy zostanie otwarta. Co postanowisz?   ");
			cout << endl << "Otwórz puszkê pandory: 1" << endl;
			cout << "Pozostaw puszkê zamkniêt¹ i ruszaj dalej: 2" << endl;
			bool done = false;
			int y;

			while (done == false)
			{
				cin >> y;
				if (!cin.good()) y = 1;

				if (y == 1)
				{
					printdc(" Postanawiasz otworzyæ Puszkê Pandory. Z dusz¹ na ramieniu i strachem w oczach podnosisz wieko skrzyni...   ");
					Sleep(3000);
					int q = random(4);

					switch (q)
					{
					case 0:
					{
						printdc(" Skrzynia zawiera staro¿ytn¹ broñ! Wyci¹gasz z niej tajemniczy miecz œwiec¹cy siê wszystkimi kolorami. Jego ostrze p³onie a rêkojeœæ idealnie mieœci siê w d³oni. Z t¹ broni¹ pokonasz ka¿dego przeciwnika!  ");
						cout << endl << "Zyskujesz 5 punktów si³y!" << endl;
						hero.STR += 5;
						done = true;
						break;

					}
					case 1:
					{
						printdc("Skrzynia zawiera z³oto! Mo¿esz je zabraæ ze sob¹.   ");
						int gold = random(20) * 50;
						cout << endl << "Znajdujesz " << gold << " sztuk z³ota." << endl;
						hero.GOLD += gold;
						done = true;
						break;

					}
					case 2:
					{
						printdc("Po otwarciu skrzyni ca³¹ salê wype³niaj¹ straszliwe jêki a z puszki uuwalniaj¹ siê uwiêzione w niej duchy. Z krzykiem padasz na ziemiê czekaj¹c a¿ zjawy znikn¹. Wnet jedna z nich dobywa miecza i rani Ciê boleœnie.   ");
						int dmg = random(5) + 1;
						cout << endl << "Tracisz " << dmg << " punktów ¿ycia!" << endl;
						printdc("Po tym nag³ym ataku duchy znikaj¹ a w sali zapada cisza. Puszka stoi pusta, nie bêdzie z niej ju¿ ¿adnego po¿ytku. Pora ruszaæ dalej.   ");
						hero.HP -= dmg;
						done = true;
						break;

					}
					case 3:
					{
						printdc(" Otwierasz Puszkê Pandory. Wieko podnosi siê bez problemu a Twoim oczom ukazuje siê sporych rozmiarów flakon wype³niony zielon¹ ciecz¹. Na flakonie przyklejona jest etykieta z napisem: 'ELIKSIR ZDROWIA'. Byæ mo¿e rzeczywiœcie butelka zawiera cudownie uzdrawiaj¹cy napój. Jednak nie znasz siê na eliksirach, wiêc ciê¿ko stwierdziæ czy mo¿e wbrew etykiecie, eliksir jest trucizn¹ lub czymœ gorszym.  ");
						cout << endl << "Czy zaryzykujesz wypice eliksiru?" << endl;
						cout << "Wypij: 1" << endl;
						cout << "Nie pij: 2" << endl;
						int X = random(11);
						int Y;
						cin >> Y;
						if (!cin.good()) Y = 1;
						if (Y == 1)
						{
							printdc("Otwierasz eliksir i wypijasz zawartoœæ do dna.  ");
							Sleep(2000);
							if (X > 2)
							{
								printdc("ELiksir rzeczywiœcie posiada uzdrawiaj¹ce w³aœciwoœci!  ");
								int Z = random(5) + 4;
								cout << "Otrzymujesz " << Z << " punktów ¿ycia." << endl;
								hero.HP += Z;
								
								
							}
							else
							{
								printdc("Eliksir okazuje siê trucizn¹!  ");
								int Z = random(4) + 1;
								cout << "Tracisz " << Z << " punktów ¿ycia" << endl;
								hero.HP -= Z;
								
							}
						}
						if (Y == 2)
						{
							printdc("Postanawiasz nie piæ eliksiru. Lepiej nie podejmowaæ takiego ryzyka podczas wyprawy.  ");

						}
						done = true;
						break;
					}

					case 4:
					{
						printdc(" Z trudem otwierasz skrzyniê. Wieko jest niesamowicie ciê¿kie i dopiero po kilku chwilach uda³o Ci siê je podnieœæ. Ku Twojemu zdziwieniu, w puszcze nie ma ¿adnych przedmiotów, zamiast tego dostrzegasz niewielk¹ skrzydlat¹ wró¿kê. Na Twój widok jej twarz wstêpuje uœmiech. Po chwili wylatuje ze skrzyni i oznajmia Ci, ¿e zosta³a tutaj uwiêziona przez z³ego czarownika. Teraz natomiast jest wolna i z przyjemnoœci¹ spe³ni jedno z Twoich ¿yczeñ w ramach rekompensaty za pomoc.  ");
						cout << endl << "Wró¿ka czeka na Twoje ¿yczenie. Powiedz czego pragniesz najbardziej?" << endl;
						cout << "Pragnê si³y i potêgi! : 1" << endl;
						cout << "Pragnê z³ota i bogactw! : 2" << endl;
						cout << " Pragnê byæ szczêœliwym... : 3" << endl;
						cout << "Chcê aby zdrowie nigdy mnie nie opuszcza³o. : 4" << endl;
						cout << "Nie chcê niczego za ratunek, nie zrobi³em tego dla nagrody. : 5" << endl;
						int Q;
						int giftvalue;
						bool donedone = false;
						
						while (donedone == false)
						{
							cin >> Q;
							
							if (Q == 1)
							{
								printdc(" Wró¿na rzuca zaklêcie. Czujesz, ¿e Twoje ramiona nabieraj¹ si³ a umys³ przepe³mia odwaga! Nie straszne Ci s¹ mroki podziemi, nie ma si³y, która mo¿e Ciê powstrzymaæ!  ");
								giftvalue = random(2)+2;
								cout << "Otrzymujesz "<<giftvalue<<" punkty si³y" << endl;
								hero.STR += giftvalue;
								donedone = true;

							}
							if (Q == 2)
							{
								printdc("Wró¿ka macha swoj¹ ró¿d¿k¹  a z sufitu zaczyna padaæ deszcz z³ota. Monety z dŸwiêkiem uderzaj¹ o posadzkê czekaj¹c na Ciebie.  ");
								giftvalue = random(500) + 500;
								cout << "Otrzymujesz " << giftvalue << " sztuk z³ota." << endl;
								hero.GOLD += giftvalue;
								donedone = true;
							}
							if (Q == 3)
							{
								printdc("Wró¿ka uœmiecha siê serdecznie i rzuca zaklêcie. Wnet czujesz, ¿e szczêœcie rzeczywiœcie Ci sprzyja i z jego pomoc¹ zdo³asz siê wymkn¹æ ze wszelkich tarapatów.  ");
								giftvalue = random(2) + 1;
								cout << endl << "Twoje szczêœcie wzrasta o wartoœæ: " << giftvalue << endl;
								hero.LCK += giftvalue;
								donedone = true;
							}
							if (Q == 4)
							{
								printdc("Wró¿ka rzuca zaklêcie a wszelkie Twoje rany b³yskawicznie zaczynaj¹ siê leczyæ. Wype³nia Ciê si³a witalna i czujesz, ¿e Twoja odpornoœæ wzrasta!  ");
								giftvalue = random(4) + 4;
								cout << endl << "Otrzymujesz " << giftvalue << " punktów wytrzyma³oœci" << endl;
								hero.HP += giftvalue;
								donedone == true;
							}
							if (Q == 5)
							{
								int a = random(2);
								if (a == 0)
								{
									printdc("Wró¿ka oznajmnia, ¿e nie spotka³a jeszcze nigdy tak dobrej i bezinteresownej osoby. Postanawia obdarzyæ Ciê swoim najsilniejszym zaklêciem. Tym razem nie pyta o zgodê.  ");
										cout << endl << "Twoja si³a wzrasta o 2 punkty!" << endl;
										cout << "Twoje szczêœcie wzrasta o 2 punkty!" << endl;
										cout << "Twoja wytrzyma³oœæ wzrasta o 5 punktów!" << endl;
										cout << "Dodatkowo wró¿ka zostawia Ci nieco z³ota na drogê" << endl;
										hero.STR += 2;
										hero.HP += 5;
										hero.LCK += 2;
										hero.GOLD += (random(500) + 250);						
								}
								else
								{
									printdc("Wró¿ka wzrusza ramionami i oznajmia, ¿e nie naciska a jej propozycja by³a jednorazowa.  ");

								}
								donedone == true;

							}
							printdc("Po chwili wró¿ka rozp³ywa siê w powietrzu pozostawiaj¹c Ciê w samotnoœci. Poza pust¹ skrzyni¹, nie ma ju¿ tutaj nic do roboty. Pora ruszaæ dalej  ");

							done = true;

						}
						break;
					}
					
					}
				}
				if (y == 2)
				{
					printdc("Nie bez powodu skrzynia stoi zamkniêta, Lepiej pozostawiæ j¹ w takim stanie...  ");
					cout << endl << "Zostawiasz Puszkê i ruszasz dalej" << endl;

				}
			}
			break;
		}
		case 3:
		{
			printdc("Stra¿nik patrzy na Ciebie nieruchomo. Ni umiesz oszacowaæ jak silnym jest przeciwnikiem. Czy zaryzykujesz walkê?  ");
			cout << endl << "Zaatakuj stra¿nika: 1" << endl;
			cout << "Ruszaj w dalsz¹ podró¿: 2" << endl;
			bool done = false;
			int x;
			while (done == false)
			{
				cin >> x;
				if (x == 1)
				{
					printdc("Dobywasz broni i ruszasz do ataku. ¯aden stra¿nik nie jest Ci straszny kiedy w grê wchodz¹ tak wielkie bogactwa!   ");
					int guard = random(20) + 4;
					int herostr = hero.STR + random(5);

					if (guard > herostr)
					{
						printdc("Stra¿nik okaza³ siê zbyt potê¿ny. Mimo zaciek³ej walki nie uda³o Ci siê go pokonac i musisz salwowaæ siê ucieczk¹. Zapominasz o skarbie i bierzesz nogi za pas  ");
						int losthp = random(4) + 1;
						cout << endl << "Utracone punkty ¿ycia podczas walki: " << losthp << endl;
						hero.HP -= losthp;
					}
					if (herostr >= guard)
					{
						printdc("Stra¿nik wcale nie by³ taki silny na jakiego wygl¹da³. Po nied³ugiej walce udaje Ci sie obezw³adniæ przeciwnika. Mo¿esz teraz dobraæ siê do strze¿onych bogactw.  ");
						int gold = ((random(20)+5) * guard)*5;
						cout << endl << "Zdobywasz " << gold << " sztuk z³ota!" << endl;
						hero.GOLD += gold;
						printdc("Przeciwnik pokonany, czas ruszaæ dalej.  ");
						cout << endl;
					}
					done = true;
				}
				if (x == 2)
				{
					printdc("Stra¿nik wygl¹da wyj¹tkowo groŸnie. Lepiej nie ryzykowaæ i ruszyæ dalej w swoj¹ stronê...   ");
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