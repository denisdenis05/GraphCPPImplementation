#pragma once
#include <unordered_map>


class Graph {
private:
    std::unordered_map<int, bool> nodes; // nodes = {nodeId1: True, nodeId2: True, ...}
    std::unordered_map<int, std::pair<int, int>> edges; // edge[edgeId] = (source, destination)
    std::unordered_map<int, int> edgeCosts; // edge[edgeId] = cost of edge
    int latestGeneratedEdgeId;

public:
    Graph();
    void createNode(int nodeId);
    bool removeNode(int nodeId);
    bool checkIfNodeExists(int nodeId);

};