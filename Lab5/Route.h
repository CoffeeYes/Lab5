#pragma once
#include <Edge.h>
class Route : public Edge
{
private:
	double m_weight;
public:
	Route(Node& rSrc, Node& rDst, double weight) : Edge(rSrc, rDst),m_weight(weight) {};
	~Route();
	virtual double getWeight() { return m_weight; };
};

