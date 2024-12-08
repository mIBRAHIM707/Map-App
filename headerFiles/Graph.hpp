#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

// Node struct: Represents each waypoint on the map
struct Node {
    int id;
    std::string name;
    sf::Vector2f position;

    // Default constructor
    Node();

    // Parameterized constructor
    Node(int id, const std::string& name, const sf::Vector2f& pos);
};

// NodeState struct: Represents the state of a node during A* pathfinding
struct NodeState {
    long long int nodeId;
    float g_cost;  // Cost from start node
    float f_cost;  // Estimated total cost (g + heuristic)
    long long int parentId;  // Parent node in the path

    // For priority queue comparison (A* needs the lowest f_cost priority)
    bool operator<(const NodeState& other) const {
        return f_cost > other.f_cost;  // Reverse order, so lower f_cost has higher priority
    }
};

// Graph class: Represents the entire map with nodes and edges
class Graph {
public:
    // Add a node to the graph
    void addNode(int id, const std::string& name, const sf::Vector2f& position);

    // Add an edge (path) between two nodes
    void addEdge(int from, int to);

    // Get all neighboring nodes for a specific node
    const std::vector<int>& getNeighbors(int nodeId) const;

    // Get a node by its ID
    Node& getNode(int id);

    // Getter for the nodes (const reference to avoid modification)
    const std::unordered_map<int, Node>& getNodes() const;

    // A* Pathfinding methods
    std::vector<long long> findPath(long long startNodeId, long long goalNodeId);
    std::vector<long long> reconstructPath(long long goalNodeId, const std::unordered_map<long long, NodeState>& allNodes);
    float heuristic(long long fromNodeId, long long toNodeId);

private:
    std::unordered_map<int, Node> nodes;  // To store nodes by ID
    std::unordered_map<int, std::vector<int>> adjacencyList;  // Adjacency list for edges
};

#endif
