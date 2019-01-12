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
	std::list<Node*>::iterator nodeIt;

	//check if node with matching id is found in the list and return it if so
	for (nodeIt = m_nodes.begin(); nodeIt != m_nodes.end(); nodeIt++) {
		std::string current_id = (*nodeIt)->getID();

		if (current_id.compare(id) == 0) {
			return *nodeIt;
		}
	}
	//if no node is found return null
    return NULL;
}


//---------------------------------------------------------------------------------------------------------------------

Node& Graph::addNode(Node* pNewNode)
{
	//check if node is found in list
	if (findNode(pNewNode->getID()) != NULL) {
		std::string error("Ein knoten mit diesem bezeichner existiert schon im Graph");
		throw error;
	}
	else {
		//insert node at the back of the list
		m_nodes.push_back(pNewNode);
		//return reference to node from the back of the list
		return *(m_nodes.back());
	}
}


//---------------------------------------------------------------------------------------------------------------------

Edge& Graph::addEdge(Edge* pNewEdge)
{
    // add edge to m_edges
	m_edges.push_back(pNewEdge);

	//check if nodes connected to pNewEdge exist in graph, if not add them
	 if (findNode(pNewEdge->getSrcNode().getID()) == NULL) {
		Node* nodeptr = &(pNewEdge->getSrcNode());
		addNode(nodeptr);
	}
	 if (findNode(pNewEdge->getDstNode().getID()) == NULL) {
		 Node* nodeptr = &(pNewEdge->getDstNode());
		 addNode(nodeptr);
	 }
	 // return reference to new edge
	 return *m_edges.back();
}


//---------------------------------------------------------------------------------------------------------------------

Graph::~Graph()
{
	
    // - soll alle Edges im Graph löschen (delete)
	while (!m_edges.empty()) {
		m_edges.pop_front();
	}

    // - soll alle Nodes im Graph löschen (delete) FALSCH
	while (!m_nodes.empty()) {
		m_nodes.pop_front();
		/*man kann auf nodes nicht delete aufrufen weil wir referenzen von nodes zulassen,
		also konnen wir nicht garantieren dass die eingabe nodes dynamisch erstellt wurden
		bzw. ein dereferenzierter pointer ubergeben wurde*/
	}

}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Node& rNode)
{

	std::list<Edge*>::iterator edgeIt;
	edgeIt = m_edges.begin();
	//delete and remove all edges attached to rNode
	while (edgeIt != m_edges.end()) {
		if ((*edgeIt)->isConnectedTo(rNode)) {
			delete *edgeIt;
			edgeIt = m_edges.erase(edgeIt);
		}
		else {
			edgeIt++;
		}
	}

	//remove node from m_nodes
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

}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Edge& rEdge)
{
	std::list<Edge*>::iterator edgeIt;

	//find and delete edge
	for (edgeIt = m_edges.begin(); edgeIt != m_edges.end(); edgeIt++) {

		if ( *(edgeIt) == &rEdge ) {
			 delete *edgeIt;
			 edgeIt = m_edges.erase(edgeIt);
		}
	}
}


//---------------------------------------------------------------------------------------------------------------------

std::vector<Edge*> Graph::findEdges(const Node& rSrc, const Node& rDst)
{
    std::vector<Edge*> ret;
	
	std::list<Edge*>::iterator edgeIt = m_edges.begin();

	//finds all edges with rSrc as source node AND rDst as destination node and adds them to ret
	while (edgeIt != m_edges.end()) {
		if ( ( &((*edgeIt)->getSrcNode()) == &rSrc ) && ( &((*edgeIt)->getDstNode()) == &rDst ) ) {
			ret.push_back(*edgeIt);
		}
		edgeIt++;
	}
	
	return ret;
}

//---------------------------------------------------------------------------------------------------------------------

void Graph::findShortestPathDijkstra(std::deque<Edge*>& rPath, const Node& rSrcNode, const Node& rDstNode)
{
	//Source: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
	
	//lists to keep track of visited and unvisited nodes
	std::list<Node*> visited;
	std::list<Node*> unvisited;
	
	//populate distances with "infinite" value to begin with
	std::map<Node*, double> distances;
	std::list<Node*>::iterator nodeIt = m_nodes.begin();

	//map to keep track of previous nodes, used at the end to find shortest path to destination node
	std::map<Node*, Node*> previousNode;

	while (nodeIt != m_nodes.end()) {
		//give all nodes a value of infinity, except source node which recieves a value of 0
		if ((*nodeIt) != &rSrcNode) {
			distances[*nodeIt] = INT_MAX;
			previousNode[*nodeIt] = NULL;
		}
		else {
			distances[*nodeIt] = 0;
		}
		unvisited.push_back(*nodeIt);
		nodeIt++;
	}

	while (!unvisited.empty()) {
		//arbibtrarily set currentNode so comparison is possible
		Node* currentNode = *(unvisited.begin());

		//finds node with smallest distance in distances map and sets currentNode to it
		for (auto it = distances.begin(); it != distances.end(); it++) {
			//if the distance to the iterator node is smaller than the current node, and it is a member of unvisited make it our currentNode
			if (it->second < distances[currentNode] && std::find(unvisited.begin(), unvisited.end(), it->first) != unvisited.end()) {
				currentNode = it->first;
			}
		}

		for (auto edgeIt = m_edges.begin(); edgeIt != m_edges.end(); edgeIt++) {
			//finds all edges where the source node is our currentNode
			if ((*edgeIt)->isConnectedTo(*currentNode) && &((*edgeIt)->getSrcNode()) == &(*currentNode)) {
				//if the distance of currentNode + edgeweight is smaller than the distance of the destination node, update its distance and make its previousNode our currentNode
				if (distances[currentNode] + (*edgeIt)->getWeight() < distances[&((*edgeIt)->getDstNode())] ) {
					distances[&((*edgeIt)->getDstNode())] = distances[currentNode] + (*edgeIt)->getWeight();
					previousNode[&((*edgeIt)->getDstNode())] = currentNode;
				}
			}
		}

		//update lists
		visited.push_back(currentNode);
		unvisited.remove(currentNode);
	}
	
	//set outputnode to destination node, has to be done via iterator because rDstNode is a const node.
	Node* outputNode = NULL;
	for (auto it = m_nodes.begin(); it != m_nodes.end(); it++) {
		if (*it == &rDstNode) {
			outputNode = *it;
		}
	}

	//check if destination node is disconnected from the rest of the path / doesnt have a previousnode
	if (previousNode.find(outputNode)->second != NULL) {

		//deque for order of node path from srcnode to dstnode
		std::deque<Node*> outputlist;
		//push dstnode as first node on deque, all other nodes get pushed before it
		outputlist.push_back(outputNode);

		//iterate from destination node to source node, push each previousnode to the front of the deque so that the correct order path from srcnode to dstnode is produced
		while (outputNode != &rSrcNode) {
			Node* addNode = previousNode.find(outputNode)->second;
			outputlist.push_front(addNode);
			outputNode = addNode;
		}

		for (auto it = outputlist.begin(); it != outputlist.end() - 1; it++) {

			//find edges connected to current node and next node
			auto nextIt = it + 1;
			std::vector<Edge*> attachedEdges = findEdges(**it, **(nextIt));

			Edge* currentEdge = *attachedEdges.begin();
			//find edge between the two nodes with smallest weight
			for (auto it2 = attachedEdges.begin(); it2 != attachedEdges.end(); it2++) {
				if ((*it2)->getWeight() < currentEdge->getWeight()) {
					currentEdge = *it2;
				}
			}


			//add edge to path (input deque)
			rPath.push_back(currentEdge);
		}
	}
	

}


//---------------------------------------------------------------------------------------------------------------------

