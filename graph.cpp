#include "graph.h"

Graph::Graph(){
    this->latestGeneratedEdgeId = 0;
//    this->currentNodeIteratorPosition = 0;
//    this->currentEdgeIteratorPosition = 0;
//    this->currentInboundIteratorPosition = 0;
//    this->currentOutboundIteratorPosition = 0;
}

void Graph::createNode(int nodeId){
    // Adds a new node to the graph with the specified node ID, has no effect if it already exists
    this->nodes[nodeId] = true;
}

bool Graph::removeNode(int nodeId){
    // Removes the node with the specified ID from the graph, along with any incident edges. Returns True if node was removed, False if not in graph

    if(this->nodes.find(nodeId) != this->nodes.end()){
        this->nodes.erase(nodeId);
        return true;
    }
    return false;
}

bool Graph::checkIfNodeExists(int nodeId){
    // Checks if an edge exists between two specified nodes. Returns True if node is in the graph, False otherwise

    if(this->nodes.find(nodeId) != this->nodes.end())
        return true;
    return false;
}

int Graph::checkIfExistsEdgeFromNodeToNode(int source, int destination){
    // Checks if an edge exists between two specified nodes. Returns the Edge ID if found, -1 if does not exist

    for (auto i = edges.cbegin(); i != edges.cend(); i++) {
        int edgeId = i->first;
        std::pair<int, int> endpoints = i->second;
        if (endpoints.first == source and endpoints.second == destination)
            return edgeId;
    }
    return -1;
}

void Graph::addEdge(int source, int destination, int edgeId, int cost){
    std::pair<int, int> endpoints;
    endpoints.first = source;
    endpoints.second = destination;
    this->edges[edgeId] = endpoints;
    this->edgeCosts[edgeId] = cost;
}

bool Graph::removeEdgeById(int edgeId){
    if(this->edges.find(edgeId) != this->edges.end()){
        this->nodes.erase(edgeId);
        return true;
    }
    return false;
}

bool Graph::removeEdgeByNodes(int source, int destination){
    int edgeId = this->checkIfExistsEdgeFromNodeToNode(source, destination);
    if (edgeId == -1)
        return false;
    this->edges.erase(edgeId);
    this->edgeCosts.erase(edgeId);
    return true;
}

void Graph::setEdgeCost(int edgeId, int cost){
    this->edgeCosts[edgeId] = cost;
}

int Graph::getNumberOfNodes() const{
    return this->nodes.size();
}

int Graph::getNumberOfEdges() const{
    return this->edges.size();
}

std::pair<int, int> Graph::getEdgeEndpoints(int edgeId){
    return this->edges[edgeId];
}

bool Graph::hasEdge(int source, int destination){
    return this->checkIfExistsEdgeFromNodeToNode(source, destination) != -1;
}

int Graph::getOutDegree(int source){
    int degree = 0;
    for (auto i = edges.cbegin(); i != edges.cend(); i++) {
        int edgeId = i->first;
        std::pair<int, int> endpoints = i->second;
        if (endpoints.first == source)
            degree++;
    }
    return degree;
}

int Graph::getInDegree(int destination) {
    int degree = 0;
    for (auto i = edges.cbegin(); i != edges.cend(); i++) {
        int edgeId = i->first;
        std::pair<int, int> endpoints = i->second;
        if (endpoints.second == destination)
            degree++;
    }
    return degree;
}

std::unordered_map<int, std::pair<int, int>> Graph::getOutEdges(int source) {
    std::unordered_map<int, std::pair<int, int>> outEdges;
    for (const auto& edge : edges) {
        if (edge.second.first == source) {
            outEdges[edge.first] = edge.second;
        }
    }
    return outEdges;
}

std::unordered_map<int, std::pair<int, int>> Graph::getInEdges(int destination) {
    std::unordered_map<int, std::pair<int, int>> inEdges;
    for (const auto& edge : edges) {
        if (edge.second.second == destination) {
            inEdges[edge.first] = edge.second;
        }
    }
    return inEdges;
}

int  Graph::getEdgeIdPrice(int edgeId){
    return this->edgeCosts[edgeId];
}

int Graph::getEdgeNodesPrice(int source, int destination){
    int edgeId = this->checkIfExistsEdgeFromNodeToNode(source, destination);
    if (edgeId == -1)
        return -1;
    return this->getEdgeIdPrice(edgeId);
}

int Graph::getNodeFromPosition(int nodePosition) {
    int currentPosition = 0;
    for (auto it = this->nodes.begin(); it != this->nodes.end(); ++it) {
        if (currentPosition == nodePosition) {
            return it->first;
        }
        ++currentPosition;
    }
}
int Graph::getEdgeFromPosition(int edgePosition) {
    int currentPosition = 0;
    for (auto it = this->edges.begin(); it != this->edges.end(); ++it) {
        if (currentPosition == edgePosition) {
            return it->first;
        }
        ++currentPosition;
    }
}






std::pair<int, int> Graph::getEdge(int edgeId) {
    return this->edges[edgeId];
}

int Graph::getEdgeCost(int edgeId) {
    auto it = edgeCosts.find(edgeId);
    if (it != edgeCosts.end()) {
        return it->second;
    } else {
        return 0;
    }
}