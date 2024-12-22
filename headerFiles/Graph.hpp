#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

struct Node {
    int id;
    std :: string name;
    sf :: Vector2f position;

    Node();
    Node(int id, const std :: string& name, const sf :: Vector2f& pos);
};

struct NodeState {
    long long int nodeId;
    float g_cost;
    float f_cost;
    long long int parentId;

    bool operator<(const NodeState& other) const {
        return f_cost > other.f_cost;
    }
};

class Graph {
public:
    void addNode(int id, const std :: string& name, const sf :: Vector2f& position);
    void addEdge(int from, int to);
    const std :: vector<int>& getNeighbors(int nodeId) const;
    Node& getNode(int id);
    const std :: unordered_map<int, Node>& getNodes() const;
    std :: vector<long long> findPath(long long startNodeId, long long goalNodeId);
    std :: vector<long long> reconstructPath(long long goalNodeId, const std :: unordered_map<long long, NodeState>& allNodes);
    float heuristic(long long fromNodeId, long long toNodeId);

private:
    std :: unordered_map<int, Node> nodes;
    std :: unordered_map<int, std :: vector<int>> adjacencyList;
};

#endif
