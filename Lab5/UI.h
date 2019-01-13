#pragma once
#include <iostream>
#include "Taxi.h"
#include <list>
#include "Node.h"
#include <Graph.h>

class UI
{
public:
	UI();
	~UI();
	void printTaxi(Taxi eingabe);
	void chooseOption(Taxi &taxi, Taxi &taxi2,Graph* inputGraph);
};

