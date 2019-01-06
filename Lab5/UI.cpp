#include "UI.h"
#include <string>
#include <limits>

UI::UI()
{
}


UI::~UI()
{
}
//nur an dieser stelle muss die toString funktion von Taxi auf getState veraendert werden, dammit es ueberall im Programm so angezeigt wird wie verlangt.
void UI::printTaxi(Taxi eingabe) {
	std::cout << eingabe.getState() << std::endl;
}

void UI::chooseOption(Taxi &taxi1, Taxi &taxi2) {
	int option = 0;
	int taxiChoice = 0;
	Taxi *usingTaxi;

	//Taxi auswaehlen
	std::cout << "Welches Taxi Moechten sie nehmen? (1: " << taxi1.getName() << " / 2 : " << taxi2.getName() << ")\n";
	std::cin >> taxiChoice;

	//fehler ueberpruefung
	while (taxiChoice != 1 && taxiChoice != 2 || !taxiChoice) {
		//eingabe loeschen falls kein integer eingegeben wurde, um unendliche schleife zu vermeiden.
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//wiederholte eingabe
		std::cout << "Sie haben keine zulaessige eingabe eingegeben, bitte geben sie 1 oder 2 ein\n\n";
		std::cout << "Welches Taxi Moechten sie nehmen? (1/2):\n";
		std::cin >> taxiChoice;
	}

	//taxi pointer je nach auswahl setzen
	if (taxiChoice == 1) {
		usingTaxi = &taxi1;
	}
	else {
		usingTaxi = &taxi2;
	}

	//option auswaehlen
	std::cout << "Was Moechten sie tun? : \n\n" << "1.Fahrt mit Gast buchen\n2.Fahrt ohne gast buchen\n3.Tanken\n4.Taxi Status anzeigen\n5.Programm beenden\n\n";
	std::cin >> option;

	//fehler ueberprufung auf options auswahl
	while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5) {
		//eingabe loeschen falls kein integer eingegeben wurde, um unendliche schleife zu vermeiden.
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//wiederholte eingabe
		std::cout << "Sie haben keine zulaessige eingabe ausgewaehlt.\n";
		std::cout << "Was Moechten sie tun? : \n\n" << "1.Fahrt mit Gast buchen\n2.Fahrt ohne gast buchen\n3.Tanken\n4.Taxi Status anzeigen\n\n";
		std::cin >> option;
	}

	//option ausfuehren
	switch (option) {
		//fahrt mit gaeste
	case 1:
	{
		double distanz;
		std::cout << "Wie weit ist die fahrt?\n";
		std::cin >> distanz;
		usingTaxi->bookTrip(distanz, true);
		break;
	}
	//fahrt ohne gaeste
	case 2:
	{
		double distanz;
		std::cout << "Wie weit ist die fahrt?\n";
		std::cin >> distanz;
		usingTaxi->bookTrip(distanz, false);
		break;
	}
	//tanken
	case 3:
		double preis;
		std::cout << "Was ist der benzinpreis momentan?\n";
		std::cin >> preis;
		usingTaxi->fillUp(preis);
		break;
		//taxi ausgeben
	case 4:
		this->printTaxi(*usingTaxi);
		break;
		//programm beenden
	case 5:
		exit(0);
		delete &taxi1;
		delete &taxi2;
		break;
	}
}