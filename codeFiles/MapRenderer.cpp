#include <cmath>
#include "MapRenderer.hpp"
#include "Graph.hpp"

void drawGraph(sf::RenderWindow& window, Graph& graph, sf::Sprite& mapSprite, const sf::Font& font, 
               const std::string& fromNodeId, const std::string& toNodeId, const std::vector<long long>& path) {
    window.draw(mapSprite);

    if (!fromNodeId.empty() && !toNodeId.empty()) {
        float lineThickness = 5.f;

        for (const auto& nodePair : graph.getNodes()) {
            long long fromId = nodePair.first;
            for (long long toId : graph.getNeighbors(fromId)) {
                const Node& fromNode = graph.getNode(fromId);
                const Node& toNode = graph.getNode(toId);

                if (std::find(path.begin(), path.end(), fromId) != path.end() && 
                    std::find(path.begin(), path.end(), toId) != path.end()) {

                    sf::Vector2f direction = toNode.position - fromNode.position;
                    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                    direction /= length;

                    sf::RectangleShape line(sf::Vector2f(length, lineThickness));
                    line.setPosition(fromNode.position);
                    line.setRotation(std::atan2(direction.y, direction.x) * 180.f / 3.14159f);
                    line.setFillColor(sf::Color::Red);

                    window.draw(line);
                }
            }
        }
    }

    for (const auto& nodePair : graph.getNodes()) {
        const Node& node = nodePair.second;

        sf::CircleShape circle(10);
        if (std::to_string(node.id) == fromNodeId) {
            circle.setFillColor(sf::Color::Blue);
        } else if (std::to_string(node.id) == toNodeId) {
            circle.setFillColor(sf::Color::Blue);
        } else {
            circle.setFillColor(sf::Color::Red);
        }
        
        circle.setPosition(node.position.x - 10, node.position.y - 10);
        window.draw(circle);

        sf::Text label;
        label.setFont(font);
        label.setString(node.name);
        label.setCharacterSize(20);
        label.setFillColor(sf::Color::Black);
        label.setPosition(node.position.x + 15, node.position.y - 10);
        window.draw(label);
    }
}
