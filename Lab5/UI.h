#pragma once
#include <iostream>
#include "Taxi.h"
class UI
{
public:
	UI();
	~UI();
	void printTaxi(Taxi eingabe);
	void chooseOption(Taxi &taxi, Taxi &taxi2);
};

