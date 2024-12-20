// Graph.cpp
#include <queue>
#include <map>
#include <cmath>
#include <limits>
#include <algorithm>
#include "Graph.hpp"

Node::Node() : id(-1), name(""), position(0.f, 0.f) {}

Node::Node(int id, const std::string& name, const sf::Vector2f& pos)
    : id(id), name(name), position(pos) {}

void Graph::addNode(int id, const std::string& name, const sf::Vector2f& position) {
    nodes[id] = Node(id, name, position);
}

void Graph::addEdge(int from,int to) {
    adjacencyList[from].push_back(to);
    adjacencyList[to].push_back(from); 
}

const std::vector<int>& Graph::getNeighbors(int nodeId) const {
    if (adjacencyList.find(nodeId) == adjacencyList.end()) {
        throw std::out_of_range("Node ID not found in adjacency list: " + std::to_string(nodeId));
    }
    return adjacencyList.at(nodeId);
}

Node& Graph::getNode(int id) {
    if (nodes.find(id) == nodes.end()) {
        throw std::out_of_range("Node ID not found in the graph.");
    }
    return nodes.at(id);
}

const std::unordered_map<int, Node>& Graph::getNodes() const {
    return nodes;
}

// A*:

float Graph::heuristic(long long fromNodeId, long long toNodeId) {
    const sf::Vector2f& fromPos = nodes[fromNodeId].position;
    const sf::Vector2f& toPos = nodes[toNodeId].position;
    return std::sqrt(std::pow(toPos.x - fromPos.x, 2) + std::pow(toPos.y - fromPos.y, 2));
}

std::vector<long long> Graph::findPath(long long startNodeId, long long goalNodeId) {
    std::priority_queue<NodeState> openSet;
    std::unordered_map<long long, NodeState> allNodes;

    NodeState startNodeState = {startNodeId, 0.0f, heuristic(startNodeId, goalNodeId), -1};
    openSet.push(startNodeState);
    allNodes[startNodeId] = startNodeState;

    while (!openSet.empty()) {
        NodeState current = openSet.top();
        openSet.pop();

        if (current.nodeId == goalNodeId) {
            return reconstructPath(current.nodeId, allNodes);
        }

        for (const auto& neighbor : adjacencyList[current.nodeId]) {
            float tentativeGCost = current.g_cost + 1.0f;  
            if (allNodes.find(neighbor) == allNodes.end() || tentativeGCost < allNodes[neighbor].g_cost) {
                NodeState nextNode = {neighbor, tentativeGCost, tentativeGCost + heuristic(neighbor, goalNodeId), current.nodeId};
                openSet.push(nextNode);
                allNodes[neighbor] = nextNode;
            }
        }
    }

    return {}; 
}

std::vector<long long> Graph::reconstructPath(long long goalNodeId, const std::unordered_map<long long, NodeState>& allNodes) {
    std::vector<long long> path;
    long long currentNodeId = goalNodeId;
    
    while (currentNodeId != -1) {
        path.push_back(currentNodeId);
        currentNodeId = allNodes.at(currentNodeId).parentId;
    }

    std::reverse(path.begin(), path.end());
    return path;
}
