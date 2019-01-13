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

void UI::chooseOption(std::list<Taxi*> taxiList,Graph* inputGraph) {
	int option = 0;
	int taxiChoice = 0;
	int taxiCounter = 1;
	Taxi *usingTaxi;

	//print all taxis in the list to the screen
	std::cout << "Welches taxi moechten sie nehmen?\n";
	for (auto taxiIt = taxiList.begin(); taxiIt != taxiList.end(); taxiIt++) {
		std::cout << taxiCounter << ". " << (*taxiIt)->getName() << "\n";
		taxiCounter++;
	}
	std::cin >> taxiChoice;

	//if an invalid entry was made clear the entry and reprint the list 
	while ( !(taxiChoice <= taxiList.size() && taxiChoice > 0)) {
		//clear the input 
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//display options again and allow new input
		std::cout << "\nSie haben keine zulaessige eingabe gemacht,versuchen sie es erneut : \n\n";
		taxiChoice = 0;
		taxiCounter = 1;
		for (auto taxiIt = taxiList.begin(); taxiIt != taxiList.end(); taxiIt++) {
			std::cout << taxiCounter << ". " << (*taxiIt)->getName() << "\n";
			taxiCounter++;
		}
		std::cin >> taxiChoice;
	}

	//iterate through taxilist until we find the taxi that was chosen by the user
	int taxiChoiceCounter = 1;
	auto taxiChoiceIt = taxiList.begin();

	while (taxiChoiceCounter != taxiChoice) {
		taxiChoiceCounter++;
		taxiChoiceIt++;
	}
	//set the found taxi as the taxi being used
	usingTaxi = *taxiChoiceIt;

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
		double distanz = 0;

		//initialise input choice variables
		int sourceChoice;
		int destChoice;
		int choiceCounter;

		//allow user to choose starting node from list
		std::cout << "wo fangen sie an? \n\n";
		choiceCounter = 1;
		std::list<Node*> nodeList = inputGraph->getNodes();
		for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
			std::cout << choiceCounter << "." << (*it)->getID() << "\n";
			choiceCounter++;
		}
		std::cin >> sourceChoice;

		//loop for erroneous input
		while (!(sourceChoice <= nodeList.size() && sourceChoice > 0)) {

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "\n\n Fehler : sie haben keine gultige eingabe gemacht\n\n";
			std::cout << "wo fangen sie an? \n\n";
			choiceCounter = 1;
			for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
				std::cout << choiceCounter << "." << (*it)->getID() << "\n";
				choiceCounter++;
			}
			std::cin >> sourceChoice;
		}


		//allow user to use destination node from list
		std::cout << "wo moechten sie hin? \n\n";
		choiceCounter = 1;
		for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
			std::cout << choiceCounter << "." << (*it)->getID() << "\n";
			choiceCounter++;
		}
		std::cin >> destChoice;

		//loop for erroneous input
		while (!(destChoice <= nodeList.size() && destChoice > 0)) {

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "\n\n Fehler : sie haben keine gultige eingabe gemacht\n\n";
			std::cout << "wo fangen sie an? \n\n";
			choiceCounter = 1;
			for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
				std::cout << choiceCounter << "." << (*it)->getID() << "\n";
				choiceCounter++;
			}
			std::cin >> destChoice;
		}

		//find source node based on user choice
		std::list<Node*>::iterator nodeIt;
		nodeIt = nodeList.begin();
		int counter = 1;
		while (counter < sourceChoice) {
			nodeIt++;
			counter++;
		}
		Node* sourceNode = *nodeIt;

		//find destination node based on user input
		nodeIt = nodeList.begin();
		counter = 1;
		while (counter < destChoice) {
			nodeIt++;
			counter++;
		}
		Node* destNode = *nodeIt;

		//find shortest path and save it
		std::deque<Edge*> path;
		inputGraph->findShortestPathDijkstra(path, *sourceNode, *destNode);

		if (path.size() >= 1) {
			//output path and calculate distanz travelled
			std::cout << "\n";
			for (auto it = path.begin(); it != path.end(); it++) {
				std::cout << (*it)->toString() << " (" << (*it)->getWeight() << "km)  | ";
				distanz = distanz + (*it)->getWeight();
			}
			std::cout << "Gesamt : " << distanz << "km";
			std::cout << "\n\n";
			//book the trip with the total distance, this funktion handles tank check and error if not enough fuel is available
			usingTaxi->bookTrip(distanz, true);
		}
		else {
			std::cout << "es gibt keinen weg von diesem startpunkt zu dem ausgewaehltem Ziel \n";
		}
		break;
	}
	//fahrt ohne gaeste
	case 2:
	{
		double distanz = 0;

		//initialise input choice variables
		int sourceChoice;
		int destChoice;
		int choiceCounter;
		std::list<Node*> nodeList = inputGraph->getNodes();

		//allow user to choose starting node from list
		std::cout << "wo fangen sie an? \n\n";
		choiceCounter = 1;
		for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
			std::cout << choiceCounter << "." << (*it)->getID() << "\n";
			choiceCounter++;
		}
		std::cin >> sourceChoice;

		//loop for erroneous input
		while (!(sourceChoice <= nodeList.size() && sourceChoice > 0)) {

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "\n\n Fehler : sie haben keine gultige eingabe gemacht\n\n";
			std::cout << "wo fangen sie an? \n\n";
			choiceCounter = 1;
			for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
				std::cout << choiceCounter << "." << (*it)->getID() << "\n";
				choiceCounter++;
			}
			std::cin >> sourceChoice;
		}

		//allow user to use destination node from list
		std::cout << "wo moechten sie hin? \n\n";
		choiceCounter = 1;
		for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
			std::cout << choiceCounter << "." << (*it)->getID() << "\n";
			choiceCounter++;
		}
		std::cin >> destChoice;

		//loop for erroneous input
		while (!(destChoice <= nodeList.size() && destChoice > 0)) {

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "\n\n Fehler : sie haben keine gultige eingabe gemacht\n\n";
			std::cout << "wo fangen sie an? \n\n";
			choiceCounter = 1;
			for (auto it = nodeList.begin(); it != nodeList.end(); it++) {
				std::cout << choiceCounter << "." << (*it)->getID() << "\n";
				choiceCounter++;
			}
			std::cin >> destChoice;
		}

		//find source node based on user choice
		std::list<Node*>::iterator nodeIt;
		nodeIt = nodeList.begin();
		int counter = 1;
		while (counter < sourceChoice) {
			nodeIt++;
			counter++;
		}
		Node* sourceNode = *nodeIt;

		//find destination node based on user input
		nodeIt = nodeList.begin();
		counter = 1;
		while (counter < destChoice) {
			nodeIt++;
			counter++;
		}
		Node* destNode = *nodeIt;

		//find shortest path and save it
		std::deque<Edge*> path;
		inputGraph->findShortestPathDijkstra(path, *sourceNode, *destNode);

		//if a path was found
		if (path.size() >= 1) {
			//output path and calculate distanz travelled
			std::cout << "\n";
			for (auto it = path.begin(); it != path.end(); it++) {
				std::cout << (*it)->toString() << " (" << (*it)->getWeight() << "km)  | ";
				distanz = distanz + (*it)->getWeight();
			}
			std::cout << "Gesamt : " << distanz << "km";
			std::cout << "\n\n";
			//book the trip with the total distance, this funktion handles tank check and error if not enough fuel is available
			usingTaxi->bookTrip(distanz, false);
		}
		else {
			std::cout << "\n es gibt keinen weg von diesem startpunkt zu dem ausgewaehltem Ziel \n";
		}
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
		//delete all taxis 
		for (auto it = taxiList.begin(); it != taxiList.end(); it++) {
			delete *it;
			it = taxiList.erase(it);
		}
		exit(0);
		break;
	default:
		break;
	}
}