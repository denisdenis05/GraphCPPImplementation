#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include "graph.h"


void parseFile(std::string filename, Graph& graph){
    std::ifstream file;
    file.open(filename);


    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        return;
    }
    std::cout<<"Loading...\n";
    int numberOfVertices, numberOfEdges, nodeId, destination, cost;
    file>>numberOfVertices >> numberOfEdges;

    int edgesParsed = 0;
    while(file>>nodeId>>destination>>cost){
        graph.createNode(nodeId);
        graph.latestGeneratedEdgeId += 1;
        edgesParsed += 1;
        int latestGeneratedEdgeId = graph.latestGeneratedEdgeId;
        graph.addEdge(nodeId, destination, latestGeneratedEdgeId, cost);

    }
    file.close();
}

void createRandomGraphFile(const std::string& filename, int numberOfNodes, int numberOfEdges) {
    std::cout << "Loading...\n";

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        return;
    }

    if (numberOfNodes * numberOfNodes < numberOfEdges) {
        file << "Invalid size. A graph with " << numberOfNodes << " nodes can have maximum " << numberOfNodes * numberOfNodes << " edges.";
        file.close();
        return;
    }

    std::vector<std::pair<int, int>> alreadyExistingNodes;
    int addedEdges = 0;
    file << numberOfNodes << " " << numberOfEdges << "\n";

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int nodeId = 0; nodeId < numberOfNodes; ++nodeId) {
        int numberOfEdgesRemaining = (nodeId == numberOfNodes - 1) ? numberOfEdges - addedEdges
                                                                   : 2 * ((numberOfEdges - addedEdges) / (numberOfNodes - nodeId + 1));
        std::vector<int> randomNodes(numberOfNodes);
        std::iota(randomNodes.begin(), randomNodes.end(), 0);
        std::shuffle(randomNodes.begin(), randomNodes.end(), gen);

        for (int edge = 0; edge < numberOfEdgesRemaining; ++edge) {
            int randomNode = randomNodes[edge];
            while (std::find(alreadyExistingNodes.begin(), alreadyExistingNodes.end(), std::make_pair(nodeId, randomNode)) != alreadyExistingNodes.end()) {
                randomNode = randomNodes[++edge];
            }
            alreadyExistingNodes.push_back(std::make_pair(nodeId, randomNode));
            int randomPrice = rd() % 201;
            file << nodeId << " " << randomNode << " " << randomPrice << "\n";
            ++addedEdges;
        }
    }
    file.close();
    std::cout << "Finished generating graph\n\n";
}


void writeGraphToFile(Graph& graph, const std::string& filename){
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        return;
    }
    file << graph.getNumberOfNodes() << " "<< graph.getNumberOfEdges()<<"\n";
    for (int i = 0; i < graph.getNumberOfEdges(); i++) {
        std::pair<int, int> endpoints = graph.getEdge(i);
        if (endpoints.first != -1)
            file << endpoints.first << " " << endpoints.second << " " <<graph.getEdgeCost(i)<<"\n";
    }
}




void displayGraphNodes(Graph& graph){
    std::cout<<"Nodes:\n";
    for (int i = 0; i < graph.getNumberOfNodes(); i++)
        if (graph.getNodeFromPosition(i) != -1)
            std::cout<<graph.getNodeFromPosition(i)<<"\n";

}


void displayGraphEdges(Graph& graph){
    std::cout<<"Edges:\n";
    for (int i = 0; i < graph.getNumberOfEdges(); i++) {
        int edgeId = graph.getEdgeFromPosition(i);
        if (edgeId != -1)
            std::cout << "Edge " << edgeId<<" ("<<graph.getEdge(edgeId).first<<", "<<graph.getEdge(edgeId).second<<"), cost "<<graph.getEdgeCost(edgeId)<<"\n";
    }
}

void displayAllOutboundEdges(Graph& graph, int nodeId){
    std::cout<<"Outbound edges:\n";
    std::unordered_map<int, std::pair<int, int>> outboundEdges = graph.getOutEdges(nodeId);
    for (auto it = outboundEdges.begin(); it != outboundEdges.end(); ++it)
        std::cout<<"Id: "<<it->first<<" ("<<it->second.first<<", "<<it->second.second<<"), cost "<<graph.getEdgeCost(it->first)<<"\n";

}

void displayAllInboundEdges(Graph& graph, int nodeId){
    std::cout<<"Outbound edges:\n";
    std::unordered_map<int, std::pair<int, int>> inboundEdges = graph.getInEdges(nodeId);
    for (auto it = inboundEdges.begin(); it != inboundEdges.end(); ++it)
        std::cout<<"Id: "<<it->first<<" ("<<it->second.first<<", "<<it->second.second<<"), cost "<<graph.getEdgeCost(it->first)<<"\n";

}




void initialMenu(Graph& graph, const std::string& readFromFile, const std::string& randomlyGeneratedFile) {
    int option;
    std::cout << " >> INITIAL MENU <<\nChoose an option:\n1.Read from file\n2.Create random graph\n";
    std::cin >> option;
    if (option == 1) {
        parseFile(readFromFile, graph);
    } else if (option == 2) {
        int numberOfNodes, numberOfEdges;
        std::cout << "Insert the number of vertices the generated graph should have: ";
        std::cin >> numberOfNodes;
        std::cout << "Insert the number of edges the generated graph should have: ";
        std::cin >> numberOfEdges;
        createRandomGraphFile(randomlyGeneratedFile, numberOfNodes, numberOfEdges);
        parseFile(randomlyGeneratedFile, graph);
    }
}


void printModifyMenu() {
    std::cout << "\n>> Choose an option:\n";
    std::cout << "1.Add a node to the graph\n";
    std::cout << "2.Delete a node from the graph\n";
    std::cout << "3.Add an edge to the graph\n";
    std::cout << "4.Delete an edge from the graph\n";
    std::cout << "5.Update the cost of an edge\n";
}


void modifyMenu(Graph& graph) {
    printModifyMenu();
    int option;
    std::cin >> option;
    if (option == 1) {
        int nodeId;
        std::cout << "Insert the node id: ";
        std::cin >> nodeId;
        graph.createNode(nodeId);
    } else if (option == 2) {
        int nodeId;
        std::cout << "Insert the node id: ";
        std::cin >> nodeId;
        graph.removeNode(nodeId);
    } else if (option == 3) {
        int edgeId, sourceNode, destinationNode, cost;
        std::cout << "Insert the edge id: ";
        std::cin >> edgeId;
        std::cout << "Insert the source node: ";
        std::cin >> sourceNode;
        std::cout << "Insert the destination node: ";
        std::cin >> destinationNode;
        std::cout << "Insert the edge cost: ";
        std::cin >> cost;
        graph.addEdge(sourceNode, destinationNode, edgeId, cost);
    } else if (option == 4){
        int edgeId;
        std::cout << "Insert the edge id: ";
        std::cin >> edgeId;
        graph.removeEdgeById(edgeId);
    } else if (option == 5){
        int edgeId, cost;
        std::cout << "Insert the edge id: ";
        std::cin >> edgeId;
        std::cout << "Insert the new cost: ";
        std::cin >> cost;
        graph.setEdgeCost(edgeId, cost);
    }
}

void printMenu() {
    std::cout << "\nChoose an option:\n";
    std::cout << "1.Display the nodes\n";
    std::cout << "2.Display the edges\n";
    std::cout << "3.Display the outbound edges for a node\n";
    std::cout << "4.Display the inbound edges for a node\n";
    std::cout << "5.Write the graph inside graph.txt file\n";
    std::cout << "6.Modify the graph\n";
}

void menu(Graph& graph) {
    while (true) {
        printMenu();
        int option;
        std::cin >> option;
        if (option == 1) {
            displayGraphNodes(graph);
        } else if (option == 2) {
            displayGraphEdges(graph);
        } else if (option == 3) {
            int nodeId;
            std::cout<<"Insert the source node: ";
            std::cin>>nodeId;
            displayAllOutboundEdges(graph, nodeId);
        } else if (option == 4) {
            int nodeId;
            std::cout<<"Insert the source node: ";
            std::cin>>nodeId;
            displayAllInboundEdges(graph, nodeId);
        } else if (option == 5) {
            writeGraphToFile(graph, "/home/denis/CLionProjects/graphsLab1/graph.txt");
        } else if (option == 6) {
            modifyMenu(graph);
        }
    }
}

int main() {
    Graph graph;
    std::string readFromFile = "/home/denis/CLionProjects/graphsLab1/graph1m.txt";
    std::string randomlyGeneratedFile = "/home/denis/CLionProjects/graphsLab1/randomlyGeneratedFile.txt";
    initialMenu(graph, readFromFile, randomlyGeneratedFile);
    menu(graph);
}