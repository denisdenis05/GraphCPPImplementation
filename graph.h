#pragma once
#include <unordered_map>
#include <iterator>
#include <vector>

class Graph {
private:
    std::unordered_map<int, bool> nodes; // nodes = {nodeId1: True, nodeId2: True, ...}
    std::unordered_map<int, std::pair<int, int>> edges; // edge[edgeId] = (source, destination)
    std::unordered_map<int, int> edgeCosts; // edge[edgeId] = cost of edge

public:
    int latestGeneratedEdgeId;
    Graph();
    void createNode(int nodeId);
    bool removeNode(int nodeId);
    bool checkIfNodeExists(int nodeId);
    int checkIfExistsEdgeFromNodeToNode(int source, int destination);
    void addEdge(int source, int destination, int edgeId, int cost=0);
    bool removeEdgeById(int edgeId);
    bool removeEdgeByNodes(int source, int destination);
    void setEdgeCost(int edgeId, int cost);
    int getNumberOfNodes() const;
    int getNumberOfEdges() const;
    std::pair<int, int> getEdgeEndpoints(int edgeId);
    bool hasEdge(int source, int destination);
    int getOutDegree(int source);
    int getInDegree(int source);

    int getEdgeIdPrice(int edgeId);
    int getEdgeNodesPrice(int source, int destination);


    std::unordered_map<int, std::pair<int, int>> getOutEdges(int source);
    std::unordered_map<int, std::pair<int, int>> getInEdges(int source);

    std::pair<int, int> getEdge(int edgeId);
    int getEdgeCost(int edgeId);
    int getNodeFromPosition(int nodePosition);
    int getEdgeFromPosition(int edgePosition);
};