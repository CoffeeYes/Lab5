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
	Node node5("five");
	Node node6("not connected");

	Edge* edge1 = new Edge(node1, node2);
	Edge* edge2 = new Edge(node1, node3);
	Edge* edge3 = new Edge(node1, node4);
	Edge* edge4 = new Edge(node4, node5);
	Edge* edge5 = new Edge(node2,node3);
	Edge* edge6 = new Edge(node3,node4);
	
	graph1->addEdge(edge1);
	//graph1->addEdge(edge2);
	//graph1->addEdge(edge3);
	graph1->addEdge(edge4);
	graph1->addEdge(edge5);
	graph1->addEdge(edge6);

	graph1->addNode(&node6);
	
	list<Edge*> edgelist = graph1->getEdges();
	list<Edge*>::iterator edgeit;
	list<Node*> nodelist = graph1->getNodes();
	list<Node*>::iterator nodeit;
	/*
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
	*/
	std::deque<Edge*> test;

	graph1->findShortestPathDijkstra(test,node1,node6);

	for (auto it = test.begin(); it != test.end(); it++) {
		cout << (*it)->toString();
	}

	delete graph1;
	system("pause");
	return 0;
}

