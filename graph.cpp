#include "graph.h"

Graph::Graph() : latestGeneratedEdgeId(0){
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
    if(this->nodes.find(nodeId) != this->nodes.end())
        return true;
    return false;
}
