#include "Edge.h"


//---------------------------------------------------------------------------------------------------------------------

Edge::Edge(Node& rSrc, Node& rDst) : m_rSrc(rSrc), m_rDst(rDst)
{
    // fügt die Edge (this) in m_outgoingEdges des Source-Node ein.
	rSrc.getOutEdges().push_back(this);
    // fügt die Edge (this) in m_incomingEdges des Destination-Node ein.
	rDst.getInEdges().push_back(this);
}


//---------------------------------------------------------------------------------------------------------------------

Edge::Edge(const Edge& rOther) : m_rSrc(rOther.m_rSrc), m_rDst(rOther.m_rDst)
{
    // macht das Selbe wie 'Edge(Node& rSrc, Node& rDst)'
	m_rSrc.getOutEdges().push_back(this);
	m_rDst.getInEdges().push_back(this);
}


//---------------------------------------------------------------------------------------------------------------------

Edge::~Edge()
{
    // - entfernt die Edge (this) aus m_outgoingEdges im Source-Node
	m_rSrc.getOutEdges().remove(this);
    // - entfernt die Edge (this) aus m_incomingEdges im Destination-Node
	m_rDst.getInEdges().remove(this);
}


//---------------------------------------------------------------------------------------------------------------------

bool Edge::isConnectedTo(const Node& rNode) const
{
    // - gibt true zurück, wenn rNode entweder m_rSrc und m_rDst ist.
	if (&rNode == &m_rSrc || &rNode == &m_rDst) {
		return true;
	}
	else {
		return false;
	}
}


//---------------------------------------------------------------------------------------------------------------------

std::string Edge::toString() const
{
    std::string result;
    result = m_rSrc.getID() + " -> " + m_rDst.getID();
    return result;
}


//---------------------------------------------------------------------------------------------------------------------
