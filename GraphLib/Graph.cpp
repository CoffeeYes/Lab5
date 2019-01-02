#include "Graph.h"
#include <list>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iostream>
#include <map>


//---------------------------------------------------------------------------------------------------------------------

Node* Graph::findNode(const std::string& id)
{
    // - soll einen Node mit der gegebenen id in m_nodes suchen
    // - gibt den Pointer auf den Node zurück, wenn er gefunden wurde.
    // - gibt NULL zurück, falls kein Node mit der id gefunden wurde.

	std::list<Node*>::iterator nodeIt;

	for (nodeIt = m_nodes.begin(); nodeIt != m_nodes.end(); nodeIt++) {
		std::string current_id = (*nodeIt)->getID();

		if (current_id.compare(id) == 0) {
			return *nodeIt;
		}
	}
    return NULL;

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend ein paar Nodes im Graph suchen.
    // Prüfen Sie, ob der Node gefunden wurden und geben Sie die ID auf der Kommandozeile aus!
}


//---------------------------------------------------------------------------------------------------------------------

Node& Graph::addNode(Node* pNewNode)
{
    // bitte diese Zeile entfernen, wenn Sie die Funktion implementieren:
    //return *new Node("");

	if (findNode(pNewNode->getID()) != NULL) {
		std::string error("Ein knoten mit diesem bezeichner existiert schon im Graph");
		throw error;
	}
	else {
		//node hinten in der liste einfugen
		m_nodes.push_back(pNewNode);
		//referenze auf node aus liste zuruckgeben
		return *(m_nodes.back());
	}

    // Überprüfen Sie, ob schon ein Node mit der gegeben id im Graph vorhanden ist!
    // Falls ja:
    //  - Exception werfen
    // Falls nein:
    //  - den neuen Node 'pNewNode' in m_nodes einfügen
    //  - Referenz auf den neuen Node zurück geben

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes in main.cpp erstellen
    // Testen Sie mit der Funktion 'findNode', ob die hinzugefügten Nodes im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

Edge& Graph::addEdge(Edge* pNewEdge)
{
    // bitte diese Zeile entfernen, wenn Sie die Funktion implementieren:
    //return *new Edge(*new Node(), *new Node());

    // - die neue Edge 'pNewEdge' in m_edges einfügen
	m_edges.push_back(pNewEdge);


	// - Testen Sie ob der Source- und Destination-Node von 'pNewEdge' schon im Graph vorhanden ist.
	// -> fügen Sie diese Nodes hinzu, falls nicht (nutzen Sie dafür Graph::addNode)
	
	 if (findNode(pNewEdge->getSrcNode().getID()) == NULL) {
		//node einfugen
		Node* nodeptr = &(pNewEdge->getSrcNode());
		addNode(&pNewEdge->getSrcNode());
	}

	 if (findNode(pNewEdge->getDstNode().getID()) == NULL) {
		 Node* nodeptr = &(pNewEdge->getDstNode());
		 addNode(nodeptr);
	 }
    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // Testen Sie mit der Funktion 'findEdges', ob die hinzugefügten Edges im Graph vorhanden sind.


	 // - Referenz auf die neue Edge zurück geben
	 return *m_edges.back();
}


//---------------------------------------------------------------------------------------------------------------------

Graph::~Graph()
{
    // - soll alle Edges im Graph löschen (delete)
	while (!m_edges.empty()) {
		delete m_edges.front();
		m_edges.pop_front();
	}
    // - soll alle Nodes im Graph löschen (delete)
	std::cout << "\n graph destroyed\n ";
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Node& rNode)
{
    // - alle Edges, die mit rNode verbunden sind, müssen entfernt werden!
	// - finden sie den Pointer mit der Adresse von 'rNode' in m_nodes.
    // 		- der Pointer auf rNode soll aus m_nodes entfernt werden!
    // 		- der Pointer auf rNode muss mit 'delete' freigegeben werden!

	
	std::list<Edge*>::iterator edgeIt;
	edgeIt = m_edges.begin();
	//alle edges loschen die mit rNode verbunden sind
	while (edgeIt != m_edges.end()) {
		if (&((*edgeIt)->getDstNode()) == &rNode || &((*edgeIt)->getSrcNode()) == &rNode) {
			delete *edgeIt;
			edgeIt = m_edges.erase(edgeIt);
		}
		else {
			edgeIt++;
		}
	}

	std::list<Node*>::iterator nodeIt;
	nodeIt = m_nodes.begin();
	while (nodeIt != m_nodes.end()) {
		if (*nodeIt == &rNode) {
			nodeIt = m_nodes.erase(nodeIt);
		}
		else {
			nodeIt++;
		}
	}
    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend einzelne Nodes wieder löschen.
    // Testen Sie mit der Funktion 'findNode', ob die gelöschten Nodes noch im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Edge& rEdge)
{
    // - der Pointer auf rEdge muss aus m_edges entfernt werden!
    // - der Pointer auf rEdge muss mit 'delete' freigegeben werden!
	std::list<Edge*>::iterator edgeIt;

	for (edgeIt = m_edges.begin(); edgeIt != m_edges.end(); edgeIt++) {

		if ( *(edgeIt) == &rEdge ) {
			//edge loeschen
			 delete *edgeIt;
			 edgeIt = m_edges.erase(edgeIt);
		}
	}

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend einzelne Edges wieder löschen.
    // Testen Sie mit der Funktion 'findEdges', ob die gelöschten Edges noch im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

std::vector<Edge*> Graph::findEdges(const Node& rSrc, const Node& rDst)
{
    std::vector<Edge*> ret;

    // - findet alle edges, mit rSrc als Source-Node und rDst als Destination-Node.
    // - füge die Zeiger der Edges in den vector 'ret' ein.

	std::list<Edge*>::iterator edgeIt = m_edges.begin();

	while (edgeIt != m_edges.end()) {
		if (&((*edgeIt)->getSrcNode()) == &rSrc && &((*edgeIt)->getDstNode()) == &rDst) {
			ret.push_back(*edgeIt);
		}
		edgeIt++;
	}

	return ret;
    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend ein paar Edges im Graph suchen.
    // Prüfen Sie, ob Edges gefunden wurden und geben Sie die gefunden Edges auf der Kommandozeile aus!
}

//---------------------------------------------------------------------------------------------------------------------

void Graph::findShortestPathDijkstra(std::deque<Edge*>& rPath, const Node& rSrcNode, const Node& rDstNode)
{
/*
Ein häufiges Anwendungsproblem für Graphen-Anwendungen besteht darin, 
den Pfad zwischen verschiedenen Nodes zu finden, die direkt oder indirekt über Edges miteinander verbunden sind.
Um den optimalsten Pfad(den mit den geringsten Kantengewichten) zu finden, gibt es den Dijkstra-Algorithmus!
Pseudocode (Quelle: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
>>>
function Dijkstra(Graph, source):

      create vertex set Q

      for each vertex v in Graph:             // Initialization
          dist[v] ← INFINITY                  // Unknown distance from source to v
          prev[v] ← UNDEFINED                 // Previous node in optimal path from source
          add v to Q                          // All nodes initially in Q (unvisited nodes)

      dist[source] ← 0                        // Distance from source to source

      while Q is not empty:
          u ← vertex in Q with min dist[u]    // Source node will be selected first
          remove u from Q

          for each neighbor v of u:           // where v is still in Q.
              alt ← dist[u] + length(u, v)
              if alt < dist[v]:               // A shorter path to v has been found
                  dist[v] ← alt
                  prev[v] ← u

      return dist[], prev[]
<<<

Betrachten Sie den Pseudocode und setzen Sie ihn in C++ um.
Sortieren Sie am Ende das Ergebnis in die richtige Reihenfolge um 
und geben sie die kürzeste Route zwischen rSrcNode und rDstNode als Liste von Edges zurück.

TEST:
Testen Sie diese Funktion, indem Sie einen Graph in main.cpp erstellen
und sich die kürzesteste Route zwischen 2 Nodes zurückgeben lassen.
*/
	/*
	std::list<Node*> visited;
	std::list<Node*> unvisited = m_nodes;
	std::list<Node*>::iterator nodeIt;
	while (nodeIt != unvisited.end()) {
		Node* currentNode = *nodeIt;

		std::list<Edge*> connectedEdges;

		for (auto edgeIt = m_edges.begin(); edgeIt != m_edges.end(); edgeIt++) {
			if ((*edgeIt)->isConnectedTo(*currentNode) && &( (*edgeIt)->getSrcNode() ) == &(*currentNode)){
				connectedEdges.push_back(*edgeIt);
			}
		}
	}
	*/
	
	//populate distances with "infinite" value to begin with
	std::map<Node*, double> distances;
	std::list<Node*>::iterator nodeIt = m_nodes.begin();
	
	while (nodeIt != m_nodes.end()) {
		//exclude source node
		if ((*nodeIt) != &rSrcNode) {
			distances[*nodeIt] = INT_MAX;
		}
	}
	
	//lists to keep track of visited and unvisited nodes
	std::list<Node*> visited;
	std::list<Node*> unvisited;
	
	// give nodes directly connected to the starting node a distance value based on edge weight
	for (auto edgeIt = m_edges.begin(); edgeIt != m_edges.end(); edgeIt++) {
		//all edges which have rSrcNode as a source node
		if ((*edgeIt)->isConnectedTo(rSrcNode) && &((*edgeIt)->getSrcNode()) == &(rSrcNode)) {
			//assign distances of destination nodes the edge weight
			distances[&((*edgeIt)->getDstNode())] = (*edgeIt)->getWeight();
		}
	}
	
	while (!visited.empty()) {
		Node* currentNode = distances.begin()->first;

		//finds node with smallest distance in distances map
		for (auto it = distances.begin(); it != distances.end(); it++) {
			//if the distance to the iterator node is smaller than the current node, and it is a member of unvisited
			if (distances[currentNode] < it->second && std::find(unvisited.begin(), unvisited.end(), it->first) != unvisited.end()) {
				currentNode = it->first;
			}
		}

		for (auto edgeIt = m_edges.begin(); edgeIt != m_edges.end(); edgeIt++) {
			//finds all edges where the source node is our currentNode
			if ((*edgeIt)->isConnectedTo(*currentNode) && &((*edgeIt)->getSrcNode()) == &(*currentNode)) {
				//if the distance of currentNode + edgeweight is smaller than the distance of the destination node, update its distance
				if (distances[currentNode] + (*edgeIt)->getWeight() < distances[&((*edgeIt)->getDstNode())] ) {
					distances[&((*edgeIt)->getDstNode())] = distances[currentNode] + (*edgeIt)->getWeight();
				}
			}
		}

		//update lists
		visited.push_back(currentNode);
		unvisited.remove(currentNode);
	}
	

	for (auto it2 = distances.begin(); it2 != distances.end(); it2++) {
		std::cout << it2->first << " " << it2->second << "  |  ";
	}
	
}


//---------------------------------------------------------------------------------------------------------------------

