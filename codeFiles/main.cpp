#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Graph.hpp"
#include "MapRenderer.hpp"
#include "Button.hpp"

std::string fromNodeId = "";
std::string toNodeId = "";

bool isFromFocused = false;
bool isToFocused = false;

sf::Text fromText;
sf::Text toText;
sf::RectangleShape fromBox;
sf::RectangleShape toBox;

sf::Color semiTransparentGray(128, 128, 128, 128); // RGBA

int main() {
    // Define window size
    sf::VideoMode windowSize(1100, 669);
    
    // Create the window
    sf::RenderWindow window(windowSize, "DSA Project");
    
    // Retrieve desktop resolution
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    
    // Calculate center position
    sf::Vector2i windowPosition(
        (desktop.width - windowSize.width) / 2,
        (desktop.height - windowSize.height) / 2
    );
    
    // Set window position to center
    window.setPosition(windowPosition);

    sf::Font font;
    if (!font.loadFromFile("assets/Montserrat-Regular.ttf")) {
        return -1;  
    }

    // Calculate right edge and center positioning for the boxes
    float rightEdgeX = window.getSize().x - 200.f;  // 200 is the width of the input box
    float centerY = (window.getSize().y - 60.f) / 2.f; // Center vertically, adjust by box height

    // Set the position of the boxes on the right mid-edge
    fromBox.setSize(sf::Vector2f(200.f, 60.f));  // Larger box for testing
    fromBox.setPosition(rightEdgeX - 40.0f, centerY + 40.f);  // Adjust Y for spacing
    fromBox.setFillColor(sf::Color::White);
    fromBox.setOutlineColor(sf::Color::Black);
    fromBox.setOutlineThickness(2.f);  

    toBox.setSize(sf::Vector2f(200.f, 60.f));  
    toBox.setPosition(rightEdgeX - 40.0f, centerY - 40.f);  // Adjust Y for spacing
    toBox.setFillColor(sf::Color::White);   
    toBox.setOutlineThickness(2.f);          
    toBox.setOutlineColor(sf::Color::Black);    

    fromText.setFont(font);
    fromText.setString("From: ");
    fromText.setCharacterSize(24);  
    fromText.setFillColor(sf::Color::Red);
    fromText.setPosition(rightEdgeX - 27.f, centerY + 55.f);

    toText.setFont(font);
    toText.setString("To: ");
    toText.setCharacterSize(24);  
    toText.setFillColor(sf::Color::Red); 
    // Calculate center position for the "To" input text
    toText.setPosition(rightEdgeX - 27.f, centerY - 25.f);

    // Define error text
    sf::Text errorText;
    errorText.setFont(font);
    errorText.setCharacterSize(20);
    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition(rightEdgeX - 50.0f, centerY + 200.f); // Position as needed

    sf::Text mem1;
    mem1.setFont(font);
    mem1.setCharacterSize(18);
    mem1.setFillColor(sf::Color::Black);
    mem1.setString("============================\nDesigned and Developed by:\n============================");
    mem1.setPosition(rightEdgeX - 70.0f, centerY + 240.f); // Position as needed

    sf::Text mem2;
    mem2.setFont(font);
    mem2.setCharacterSize(18);
    mem2.setFillColor(sf::Color::Black);
    mem2.setString("Muhammad Ibrahim\nZouhair Azam Khan\nTughrul Hussain Khan");
    mem2.setPosition(rightEdgeX - 40.0f, centerY + 300.f); // Position as needed

    // Define border thickness and colors
    const float BORDER_THICKNESS = 2.f;
    sf::Color focusedColor = sf::Color::Green;

    // Define button dimensions and colors
    sf::Vector2f buttonSize(150.f, 50.f);
    sf::Vector2f buttonPosition(rightEdgeX - 15.0f, centerY + 120.f); // Positioned below the "To" input box

    sf::Color buttonColorNormal(100, 100, 250);   // Normal state color
    sf::Color buttonColorHover(150, 150, 255);    // Hover state color
    sf::Color buttonColorPressed(50, 50, 200);    // Pressed state color

    // Create the Highlight Path button
    Button highlightButton(
        buttonSize,
        buttonPosition,
        buttonColorNormal,
        buttonColorHover,
        buttonColorPressed,
        font,
        "Find",
        20 // Character size
    );
    bool highlightPath = false;

    Graph graph;

    std::ifstream file("assets/coordinates.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open coordinates file!" << std::endl;
        return -1;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id_str, lat_str, lon_str;
        double lat, lon;
        int id;  

        if (std::getline(ss, id_str, ',') && std::getline(ss, lat_str, ',') && std::getline(ss, lon_str)) {
            try {
                id = std::stoi(id_str);  
                lat = std::stod(lat_str); 
                lon = std::stod(lon_str); 
            } catch (const std::exception& e) {
                std::cerr << "Error: Could not convert values - " << e.what() << std::endl;
                continue;
            }

            graph.addNode(id, "Building " + std::to_string(id), sf::Vector2f(lat, lon));
        }
    }

    // After loading nodes and before rendering
    std::ifstream edgesFile("assets/edges.txt");
    if (!edgesFile.is_open()) {
        std::cerr << "Error: Could not open edges file!" << std::endl;
        return -1;
    }

    std::string edgeLine;
    while (std::getline(edgesFile, edgeLine)) {
        std::stringstream ss(edgeLine);
        std::string fromStr, toStr;
        int from, to;

        if (std::getline(ss, fromStr, ',') && std::getline(ss, toStr)) {
            try {
                from = std::stoi(fromStr);
                to = std::stoi(toStr);
            } catch (const std::exception& e) {
                std::cerr << "Error: Could not convert edge values - " << e.what() << std::endl;
                continue;
            }

            graph.addEdge(from, to);
        }
    }

    sf::Texture mapTexture;
    if (!mapTexture.loadFromFile("assets/gikiMap.jpg")) {
        return -1;
    }
    sf::Sprite mapSprite(mapTexture);

    std::vector<long long> path;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (fromBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isFromFocused = true;
                    fromBox.setOutlineThickness(BORDER_THICKNESS);
                    fromBox.setOutlineColor(focusedColor);
                    toBox.setOutlineThickness(2.f);          
                    toBox.setOutlineColor(sf::Color::Black);
                    isToFocused = false;
                    highlightPath = false;
                } else if (toBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    isFromFocused = false;
                    toBox.setOutlineThickness(BORDER_THICKNESS);
                    toBox.setOutlineColor(focusedColor);
                    fromBox.setOutlineColor(sf::Color::Black);
                    fromBox.setOutlineThickness(2.f);  
                    isToFocused = true;
                    highlightPath = false;
                } else {
                    isFromFocused = false;
                    isToFocused = false;
                }
            }

            if (event.type == sf::Event::TextEntered) {
                if (isFromFocused) {
                    if (event.text.unicode == 8 && fromNodeId.size() > 0) { 
                        fromNodeId.pop_back();
                        highlightPath = false;
                    } else if (event.text.unicode < 128 && fromNodeId.size() < 3) {  
                        highlightPath = false; // Reset path highlighting on input change
                        fromNodeId += static_cast<char>(event.text.unicode);
                    }
                } else if (isToFocused) {
                    if (event.text.unicode == 8 && toNodeId.size() < 3) {
                        toNodeId.pop_back();
                        highlightPath = false;
                    } else if (event.text.unicode < 128) {  
                        highlightPath = false; // Reset path highlighting on input change
                        toNodeId += static_cast<char>(event.text.unicode);
                    }
                }
            }
            // Update the button with current event
            highlightButton.update(window, event);
        }

        // Check if the button was clicked
        if(highlightButton.isClicked()){
            // After ensuring both node IDs are entered
            if (!fromNodeId.empty() && !toNodeId.empty()) {
                try {
                    long long fromId = std::stoll(fromNodeId);
                    long long toId = std::stoll(toNodeId);

                    // Validate node existence
                    if (graph.getNodes().find(fromId) == graph.getNodes().end()) {
                        errorText.setString("Wrong 'From' Location");
                        fromNodeId = "";
                        highlightPath = false;
                    } else if (graph.getNodes().find(toId) == graph.getNodes().end()) {
                        errorText.setString("Wrong 'To' Location");
                        toNodeId = "";
                        highlightPath = false;
                    } else {
                        path = graph.findPath(fromId, toId);
                        if (path.empty()) {
                            errorText.setString("No path found between the selected nodes.");
                            highlightPath = false;
                        } else {
                            highlightPath = true;
                            errorText.setString(""); // Clear error message
                        }
                    }
                } catch (const std::exception& e) {
                    errorText.setString("Invalid input for node IDs.");
                    highlightPath = false;
                }
            }
        }

        window.clear(semiTransparentGray);
        
        drawGraph(window, graph, mapSprite, font, fromNodeId, toNodeId, (highlightPath ? path : std::vector<long long>()));  // Pass fromNodeId and toNodeId
        window.draw(fromBox);
        window.draw(fromText);
        window.draw(toBox);
        window.draw(toText);

        // Display the current text inside the boxes
        sf::Text fromInputText;
        fromInputText.setFont(font);
        fromInputText.setString(fromNodeId);  // Current text input
        fromInputText.setCharacterSize(24);
        fromInputText.setFillColor(sf::Color::Black);
        fromInputText.setPosition(rightEdgeX + 50.f, centerY + 55.f);  // Align text inside the box
        window.draw(fromInputText);

        sf::Text toInputText;
        toInputText.setFont(font);
        toInputText.setString(toNodeId);  // Current text input
        toInputText.setCharacterSize(24);
        toInputText.setFillColor(sf::Color::Black);
        toInputText.setPosition(rightEdgeX + 20.f, centerY - 25.f);  // Align text inside the box
        window.draw(toInputText);

        highlightButton.draw(window);

        window.draw(errorText);
        window.draw(mem1);
        window.draw(mem2);

        window.display();
    }

    return 0;
}
