#pragma once
#include <string>
class Taxi
{
public:
	Taxi();
	Taxi(const Taxi& copyTaxi);
	Taxi(const int maxTank, const double verbrauch, const double fahrPreis, std::string taxiName, double geldBilanz = 0);
	~Taxi();
	//void initialize(int maxTank,double verbrauch, double fahrPreis);
	const void bookTrip(double distanz, bool passengers);
	const void fillUp(double benzinPreis);
	const std::string getState();
	void setName(std::string name);
	std::string getName();
private:
	static int m_currentTaxiCount;
	static int m_totalTaxiCount;

	double m_tagesKilometer;
	double m_tankinhalt;
	const int m_maxTank;
	const double m_verbrauch;
	const double m_fahrPreis;
	double m_geldBilanz;
	std::string m_taxiName;
};