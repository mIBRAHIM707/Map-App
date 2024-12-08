// MapRenderer.hpp
#ifndef MAPRENDERER_HPP
#define MAPRENDERER_HPP

#include <SFML/Graphics.hpp>
#include "Graph.hpp"

// Function to render the graph (nodes and edges) on the map
void drawGraph(sf::RenderWindow& window, Graph& graph, sf::Sprite& mapSprite, const sf::Font& font,
const std::string& fromNodeId, const std::string& toNodeId, const std::vector<long long>& path);

#endif