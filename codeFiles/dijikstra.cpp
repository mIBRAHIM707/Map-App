#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <set>
#include <limits>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

struct Graph {
    unordered_map<string, list<pair<string, int>>> adjList;

    void addEdge(const string& src, const string& dest, int weight) {
        adjList[src].push_back(make_pair(dest, weight));
        adjList[dest].push_back(make_pair(src, weight));
    }

    void printGraph() const {
        for (const auto& node : adjList) {
            cout << node.first << " -> ";
            for (const auto& neighbor : node.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    void dijkstra(const string& start, const string& end) const {
        unordered_map<string, int> distances;
        unordered_map<string, string> previous;
        set<pair<int, string>> pq;

        for (const auto& node : adjList) {
            distances[node.first] = numeric_limits<int>::max();
        }
        distances[start] = 0;
        pq.insert(make_pair(0, start));

        while (!pq.empty()) {
            auto [currentDist, currentNode] = *pq.begin();
            pq.erase(pq.begin());

            if (currentNode == end) break;

            for (const auto& neighbor : adjList.at(currentNode)) {
                int newDist = currentDist + neighbor.second;
                if (newDist < distances[neighbor.first]) {
                    pq.erase(make_pair(distances[neighbor.first], neighbor.first));
                    distances[neighbor.first] = newDist;
                    previous[neighbor.first] = currentNode;
                    pq.insert(make_pair(newDist, neighbor.first));
                }
            }
        }

        if (distances[end] == numeric_limits<int>::max()) {
            cout << "There is no path from " << start << " to " << end << "." << endl;
        } else {
            cout << "Shortest path from " << start << " to " << end << " is " << distances[end] << " km." << endl;

            vector<string> path;
            for (string at = end; at != ""; at = previous[at]) {
                path.push_back(at);
                if (at == start) break;
            }
            reverse(path.begin(), path.end());

            cout << "Path: ";
            for (size_t i = 0; i < path.size(); ++i) {
                if (i != 0) cout << " -> ";
                cout << path[i];
            }
            cout << endl;
        }
    }

    void findAllPaths(const string& src, const string& dest) const {
        vector<vector<string>> allPaths;
        vector<string> currentPath;
        unordered_map<string, bool> visited;
        findAllPathsUtil(src, dest, visited, currentPath, allPaths);

        cout << "All paths from " << src << " to " << dest << ":" << endl;
        for (const auto& path : allPaths) {
            for (size_t i = 0; i < path.size(); ++i) {
                if (i != 0) cout << " -> ";
                cout << path[i];
            }
            cout << endl;
        }
    }

    void findAllPathsUtil(const string& src, const string& dest, unordered_map<string, bool>& visited, vector<string>& currentPath, vector<vector<string>>& allPaths) const {
        visited[src] = true;
        currentPath.push_back(src);

        if (src == dest) {
            allPaths.push_back(currentPath);
        } else {
            for (const auto& neighbor : adjList.at(src)) {
                if (!visited[neighbor.first]) {
                    findAllPathsUtil(neighbor.first, dest, visited, currentPath, allPaths);
                }
            }
        }

        currentPath.pop_back();
        visited[src] = false;
    }

    void displayMenu() const {
        cout << "\nGraph Operations Menu:" << endl;
        cout << "1. Add an edge" << endl;
        cout << "2. Print the graph" << endl;
        cout << "3. Find the shortest path (Dijkstra's Algorithm)" << endl;
        cout << "4. Find all paths between two nodes" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
    }
};

void addSampleEdges(Graph& g) {
    g.addEdge("Lahore", "Gujranwala", 70);
    g.addEdge("Lahore", "Sahiwal", 180);
    g.addEdge("Lahore", "Faisalabad", 180);
    g.addEdge("Lahore", "Rawalpindi", 380);
    g.addEdge("Faisalabad", "Sargodha", 90);
    g.addEdge("Faisalabad", "Sahiwal", 110);
    g.addEdge("Gujranwala", "Rawalpindi", 270);
    g.addEdge("Gujranwala", "Sargodha", 150);
    g.addEdge("Rawalpindi", "Sargodha", 190);
    g.addEdge("Sargodha", "Multan", 280);
    g.addEdge("Multan", "Dera Ghazi Khan", 130);
    g.addEdge("Multan", "Bahawalpur", 90);
    g.addEdge("Bahawalpur", "Dera Ghazi Khan", 220);
    g.addEdge("Bahawalpur", "Sahiwal", 220);
    g.addEdge("Dera Ghazi Khan", "Sahiwal", 260);
    g.addEdge("Sialkot", "Gujranwala", 50);
    g.addEdge("Sialkot", "Gujrat", 75);
    g.addEdge("Gujrat", "Gujranwala", 55);
    g.addEdge("Karachi", "Hyderabad", 150);
    g.addEdge("Karachi", "Mirpurkhas", 220);
    g.addEdge("Hyderabad", "Shaheed Benazirabad", 150);
    g.addEdge("Hyderabad", "Mirpurkhas", 80);
    g.addEdge("Mirpurkhas", "Shaheed Benazirabad", 200);
    g.addEdge("Shaheed Benazirabad", "Sukkur", 200);
    g.addEdge("Shaheed Benazirabad", "Larkana", 150);
    g.addEdge("Sukkur", "Larkana", 80);
    g.addEdge("Hyderabad", "Thatta", 100);
    g.addEdge("Thatta", "Badin", 100);
    g.addEdge("Badin", "Mirpurkhas", 100);
    g.addEdge("Nawabshah", "Khairpur", 150);
    g.addEdge("Khairpur", "Sukkur", 50);
    g.addEdge("Peshawar", "Mardan", 60);
    g.addEdge("Peshawar", "Kohat", 70);
    g.addEdge("Mardan", "Hazara", 120);
    g.addEdge("Hazara", "Rawalpindi", 120);
    g.addEdge("Kohat", "Bannu", 110);
    g.addEdge("Bannu", "Dera Ismail Khan", 160);
    g.addEdge("Dera Ismail Khan", "Dera Ghazi Khan", 230);
    g.addEdge("Malakand", "Hazara", 170);
    g.addEdge("Abbottabad", "Mansehra", 30);
    g.addEdge("Mansehra", "Battagram", 50);
    g.addEdge("Battagram", "Thakot", 40);
    g.addEdge("Thakot", "Dasu", 70);
    g.addEdge("Dasu", "Chilas", 80);
    g.addEdge("Quetta", "Kalat", 160);
    g.addEdge("Quetta", "Sibi", 160);
    g.addEdge("Quetta", "Zhob", 330);
    g.addEdge("Kalat", "Makran", 480);
    g.addEdge("Makran", "Rakhshan", 250);
    g.addEdge("Nasirabad", "Sibi", 120);
    g.addEdge("Nasirabad", "Jafarabad", 70);
    g.addEdge("Jafarabad", "Sibi", 80);
    g.addEdge("Rakhshan", "Zhob", 270);
    g.addEdge("Rakhshan", "Makran", 250);
    g.addEdge("Nasirabad", "Kalat", 240);
    g.addEdge("Islamabad", "Rawalpindi", 10);
    g.addEdge("Islamabad", "Murree", 60);
}

int main() {
    Graph g;
    addSampleEdges(g);

    while (true) {
        g.displayMenu();

        int choice;
        cin >> choice;

        string src, dest;
        int weight;

        switch (choice) {
            case 1:
                cout << "Enter source: ";
                cin >> src;
                cout << "Enter destination: ";
                cin >> dest;
                cout << "Enter weight: ";
                cin >> weight;
                g.addEdge(src, dest, weight);
                break;
            case 2:
                g.printGraph();
                break;
            case 3:
                cout << "Enter start node: ";
                cin >> src;
                cout << "Enter end node: ";
                cin >> dest;
                g.dijkstra(src, dest);
                break;
            case 4:
                cout << "Enter start node: ";
                cin >> src;
                cout << "Enter end node: ";
                cin >> dest;
                g.findAllPaths(src, dest);
                break;
            case 5:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}