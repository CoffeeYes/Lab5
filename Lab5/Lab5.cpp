#include <iostream>
#include "Node.h"
#include "Edge.h"
#include "Graph.h"


using namespace std;

int main()
{

	Graph* graph1 = new Graph();

	Node node1("one");
	Node node2("two");
	Node node3("three");
	Node node4("four");

	Edge* edge1 = new Edge(node1, node2);
	Edge* edge2 = new Edge(node1, node3);
	Edge* edge3 = new Edge(node1, node4);

	graph1->addEdge(edge1);
	graph1->addEdge(edge2);
	graph1->addEdge(edge3);

	list<Edge*> edgelist = graph1->getEdges();
	list<Edge*>::iterator edgeit;
	list<Node*> nodelist = graph1->getNodes();
	list<Node*>::iterator nodeit;

	for (edgeit = edgelist.begin(); edgeit != edgelist.end(); edgeit++) {
		cout << (*edgeit)->toString() << " | ";
	}

	cout << "\n";

	graph1->remove(*edge2);

	graph1->remove(node4);

	edgelist = graph1->getEdges();

	for (edgeit = edgelist.begin(); edgeit != edgelist.end(); edgeit++) {
		cout << (*edgeit)->toString() << " | ";
	}

	nodelist = graph1->getNodes();
	for (nodeit = nodelist.begin(); nodeit != nodelist.end(); nodeit++) {
		cout << " " << (*nodeit)->getID() << " ";
	}
	/*
	std::deque<Edge*> test;

	graph1->findShortestPathDijkstra(test,node1,node4);
	*/
	delete graph1;
	system("pause");
	return 0;
}

