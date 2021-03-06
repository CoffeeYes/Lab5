#include <iostream>
#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include "Route.h"
#include "Taxi.h"
#include "UI.h"


using namespace std;

int main()
{
	//----------------------------------- initialise graph ----------------------------------------------------------------
	Graph graph;

	Node alex("Alexanderplatz");
	Node funkTurm("Funkturm");
	Node wannSee("Strandbad Wannsee");
	Node bTor("Brandenburger Tor");
	Node ostKreuz("Ostkreuz");
	Node grun("Gruenau");
	Node grenz("Grenzallee");
	Node zit("Zitadelle Spandau");

	Route* edge1 = new Route(alex,funkTurm,10.2);
	Route* edge2 = new Route(funkTurm,wannSee,11.2);
	Route* edge3 = new Route(wannSee,alex,18.0);
	Route* edge4 = new Route(bTor,alex,2.3);
	Route* edge5 = new Route(alex,ostKreuz,6.2);
	Route* edge6 = new Route(ostKreuz,grun,14.6);
	Route* edge7 = new Route(grun,grenz,12.8);
	Route* edge8 = new Route(grenz,alex,11.2);
	Route* edge9 = new Route(grenz,funkTurm,14.9);
	Route* edge10 = new Route(funkTurm,zit,8.5);

	graph.addEdge(edge1);
	graph.addEdge(edge2);
	graph.addEdge(edge3);
	graph.addEdge(edge4);
	graph.addEdge(edge5);
	graph.addEdge(edge6);
	graph.addEdge(edge7);
	graph.addEdge(edge8);
	graph.addEdge(edge9);
	graph.addEdge(edge10);

	//----------------------------------------------------------------------------------------------------------------------

	Taxi* taxi1 = new Taxi();
	Taxi* taxi2 = new Taxi();

	std::list<Taxi*> taxiList = { taxi1,taxi2 };

	UI UI;

	while (1) {
		UI.chooseOption(taxiList,&graph);
	}

	

	return 0;
}

