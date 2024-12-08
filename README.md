# Map App

**Map App** is a C++ application developed using SFML (Simple and Fast Multimedia Library) as part of my Semester 3 Data Structures and Algorithms (DSA) project. This application visualizes graph structures overlaid on a map, enabling users to input 'From' and 'To' node IDs to compute and highlight the shortest path between them.

## 📌 Table of Contents

- [Features](#features)
- [Technologies Used](#technologies-used)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## 🎯 Features

- **Interactive User Interface:**
  - Input boxes for specifying source and destination nodes.
  - Buttons to trigger pathfinding actions.
  - Dynamic window resizing to maintain UI consistency.
  
- **Graph Visualization:**
  - Displays nodes and edges on a map.
  - Highlights the computed shortest path for easy visualization.
  
- **Pathfinding Algorithms:**
  - Implements efficient algorithms (e.g., Dijkstra's) to determine the shortest path between nodes.
  
- **Error Handling:**
  - Provides clear error messages for invalid inputs or when no path is found.
  
- **Responsive Design:**
  - UI elements adjust their positions based on window size changes to ensure a seamless user experience.

## 🛠 Technologies Used

- **C++:** The core programming language used for development.
- **SFML:** Utilized for rendering graphics, handling window events, and managing user interactions.
- **Git:** Version control system to manage and track project changes.

## 📥 Installation

### Prerequisites

- **C++ Compiler:** Ensure you have a C++17 compatible compiler installed (e.g., `g++`, `clang++`).
- **SFML Library:** Install SFML on your system.

## 🚀 Usage

### Launch the Application

1. Run the executable to open the application window.

### Input Node IDs

1. Click on the **From** input box and enter the source node ID.
2. Click on the **To** input box and enter the destination node ID.

### Find Path

1. Click the **Find** button to compute and highlight the shortest path between the specified nodes on the map.

### Error Handling

- If invalid node IDs are entered or no path exists, the application will display appropriate error messages.

##📜 License

This project is licensed under the MIT License. See the LICENSE file for details.

##🙏 Acknowledgements

SFML - For providing the multimedia library used in this project.
Course materials and lectures from my Semester 3 Data Structures and Algorithms class.
GitHub - For hosting the repository and facilitating collaboration.
