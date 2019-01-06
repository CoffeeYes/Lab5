#include "Taxi.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <sstream>

//statische counter initialisieren
int Taxi::m_currentTaxiCount = 0;
int Taxi::m_totalTaxiCount = 0;

//default constructor
Taxi::Taxi()
	: m_maxTank(50), m_verbrauch(10), m_fahrPreis(10)
{
	m_currentTaxiCount++;
	m_totalTaxiCount++;

	m_geldBilanz = 0;
	m_tagesKilometer = 0;
	m_tankinhalt = 50;

	//Taxi name mit counter am ende setzen
	std::stringstream taxi_id;
	taxi_id << "Taxi_" << std::setw(3) << std::setfill('0') << m_totalTaxiCount;
	setName(taxi_id.str());
}
//kopier Constructor
Taxi::Taxi(const Taxi& copyTaxi)
	: m_maxTank(copyTaxi.m_maxTank), m_verbrauch(copyTaxi.m_verbrauch), m_fahrPreis(copyTaxi.m_fahrPreis)
{
	//counter incrementieren
	m_currentTaxiCount++;
	m_totalTaxiCount++;

	//variable werte kopieren
	m_geldBilanz = copyTaxi.m_geldBilanz;
	m_tagesKilometer = copyTaxi.m_tagesKilometer;
	m_tankinhalt = copyTaxi.m_tankinhalt;
	m_taxiName = copyTaxi.m_taxiName;
}
//custom constructor
Taxi::Taxi(const int maxTank, const double verbrauch, const double fahrPreis, std::string taxiName, double geldbilanz)
	: m_maxTank(maxTank), m_verbrauch(verbrauch), m_fahrPreis(fahrPreis), m_tagesKilometer(0), m_tankinhalt(maxTank), m_geldBilanz(geldbilanz)
{
	setName(taxiName);

	m_currentTaxiCount++;
	m_totalTaxiCount++;
}

Taxi::~Taxi()
{
	m_currentTaxiCount--;
}
/*
void Taxi::initialize(int maxTank,double verbrauch, double fahrPreis) {
	m_verbrauch = verbrauch;
	m_fahrPreis = fahrPreis;
	m_maxTank = maxTank;
	m_tagesKilometer = 0;
	m_tankinhalt = m_maxTank;
	m_geldBilanz = 0;
}
*/
const void Taxi::bookTrip(double distanz, bool passengers) {

	//benzin verbrauch fuer trip berechnen
	double tripUsage = (distanz / 100) * m_verbrauch;

	//wenn benzin nicht ausreichend ist fehler ausschreiben
	if (tripUsage > m_tankinhalt) {
		std::cout << "\nFEHLER : fuer diese fahrt ist nicht genug benzin im tank\n\n";
	}
	//wenn benzin reicht
	else {
		//verbrauch von tankinhalt abziehen
		m_tagesKilometer += distanz;
		m_tankinhalt -= tripUsage;
		//falls gaeste im Taxi wahren, fahrt kosten zu geldbilanz hinzufuegen
		if (passengers) {
			m_geldBilanz += m_fahrPreis * distanz;
		}
	}
}

const void Taxi::fillUp(double benzinPreis) {
	//kosten um tank komplett aufzufuellen berechnen
	double max_fill_price = (m_maxTank - m_tankinhalt) * benzinPreis;

	//wenn geld bilanz ausreichend ist tank max auffuellen und kosten von bilanz abziehen
	if (m_geldBilanz > max_fill_price) {

		m_geldBilanz -= max_fill_price;
		m_tankinhalt = m_maxTank;
	}
	//wenn geld nicht ausreichend ist, maximal liter berechnen und auffuellen, und kosten abziehen
	else {
		int max_liter = m_geldBilanz / benzinPreis;
		m_geldBilanz -= max_liter * benzinPreis;
		m_tankinhalt += max_liter;
	}
}

const std::string Taxi::getState() {

	//stringstream formatieren , std::fixed + std::toprecision limitiert auf 2 dezimalstellen
	std::stringstream output;
	output << std::setw(11) << m_taxiName + " >>" << std::setw(12) << " " << std::fixed << std::setprecision(2) << m_tagesKilometer << " km," << std::setw(11) << " " << std::fixed << std::setprecision(2) << m_tankinhalt << " l," << " " << std::setw(13) << " " << std::fixed << std::setprecision(2) << m_geldBilanz << " Euro";

	//stringstream als string zuruckgeben
	return output.str();
}

void Taxi::setName(std::string name) {
	try {
		if (name.length() <= 8) {
			m_taxiName = name;
		}
		//exception werfen wenn name laenger als 8 Charakter ist, und ersten 8 charakter als name nehmen.
		else {
			m_taxiName = name.substr(0, 8);
			throw std::invalid_argument("Ihr Taxiname war laenger als 8 Charakter, dieser wurde auf 8 Charakter gekurzt\n");
		}
	}
	//diese exception an die console ausgeben.
	catch (std::exception& ex) {
		std::cout << "Fehler : " << ex.what() << std::endl;
	}
}

std::string Taxi::getName() {
	return m_taxiName;
}