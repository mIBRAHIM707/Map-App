#include <cmath>
#include "MapRenderer.hpp"
#include "Graph.hpp"

void drawGraph(sf::RenderWindow& window, Graph& graph, sf::Sprite& mapSprite, const sf::Font& font, 
            const std::string& fromNodeId, const std::string& toNodeId, const std::vector<long long>& path) {
    // Step 1: Draw the map as the background
    window.draw(mapSprite);

    // Step 2: Draw the edges (connections between nodes)
    if (!fromNodeId.empty() && !toNodeId.empty()) {
        float lineThickness = 5.f;  // Set the thickness of the lines (adjust as needed)

        for (const auto& nodePair : graph.getNodes()) {  // Use the getter to access nodes
            long long fromId = nodePair.first;
            for (long long toId : graph.getNeighbors(fromId)) {
                const Node& fromNode = graph.getNode(fromId);  // Get the 'from' node
                const Node& toNode = graph.getNode(toId);      // Get the 'to' node

                // Only draw the edge if it's part of the path
                if (std::find(path.begin(), path.end(), fromId) != path.end() && 
                    std::find(path.begin(), path.end(), toId) != path.end()) {

                    // Calculate the distance and direction
                    sf::Vector2f direction = toNode.position - fromNode.position;
                    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                    direction /= length;  // Normalize direction

                    // Create a rectangle for the edge (thicker line)
                    sf::RectangleShape line(sf::Vector2f(length, lineThickness));  // lineThickness controls the thickness
                    line.setPosition(fromNode.position);
                    line.setRotation(std::atan2(direction.y, direction.x) * 180.f / 3.14159f);  // Set the angle
                    line.setFillColor(sf::Color::Red);  // Line color

                    window.draw(line);  // Draw the line as a rectangle
                }
            }
        }
    }


    // Step 4: Draw the nodes (waypoints) as circles
    for (const auto& nodePair : graph.getNodes()) {  // Use the getter to access nodes
        const Node& node = nodePair.second;

        // Highlight the "from" and "to" nodes by checking if they match the input IDs
        sf::CircleShape circle(10);  // Radius of 10px for the circle
        if (std::to_string(node.id) == fromNodeId) {
            circle.setFillColor(sf::Color::Blue);  // Highlight "from" node in green
        } else if (std::to_string(node.id) == toNodeId) {
            circle.setFillColor(sf::Color::Blue);  // Highlight "to" node in blue
        } else {
            circle.setFillColor(sf::Color::Red);  // Default node color (red)
        }
        
        circle.setPosition(node.position.x - 10, node.position.y - 10);  // Adjust position for center
        window.draw(circle);  // Draw the node as a circle

        // Step 5: Draw the node label
        sf::Text label;
        label.setFont(font);  // Set the font
        label.setString(node.name);  // Set the node's name as the label
        label.setCharacterSize(20);  // Font size
        label.setFillColor(sf::Color::Black);  // Label color (black)
        label.setPosition(node.position.x + 15, node.position.y - 10);  // Position the label next to the node
        window.draw(label);  // Draw the label
    }
}
