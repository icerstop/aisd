#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
#include <chrono>

std::vector<std::vector<int>> generateEulerianGraph(int numVertices)
{
    std::vector<std::vector<int>> graph(numVertices, std::vector<int>(numVertices, 0));

    // Generowanie cyklu Eulera
    std::vector<int> vertices(numVertices);
    for (int i = 0; i < numVertices; i++)
        vertices[i] = i;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(vertices.begin(), vertices.end(), generator);

    for (int i = 0; i < numVertices - 1; i++)
    {
        // Dodawanie krawêdzi miêdzy kolejnymi wierzcho³kami cyklu
        graph[vertices[i]][vertices[i + 1]] = 1;
        graph[vertices[i + 1]][vertices[i]] = 1;
    }

    // Dodanie krawêdzi pomiêdzy ostatnim wierzcho³kiem a pierwszym
    graph[vertices[numVertices - 1]][vertices[0]] = 1;
    graph[vertices[0]][vertices[numVertices - 1]] = 1;

    // Obliczenie maksymalnej liczby krawêdzi
    int maxEdges = numVertices * (numVertices - 1) / 2;

    // Obliczenie po¿¹danej liczby krawêdzi
    int desiredEdges = maxEdges / 2;

    // Dodawanie losowych krawêdzi
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    int numEdges = numVertices - 1; // Liczba krawêdzi w cyklu Eulera
    while (numEdges < desiredEdges)
    {
        int i = std::uniform_int_distribution<int>(0, numVertices - 1)(generator);
        int j = std::uniform_int_distribution<int>(0, numVertices - 1)(generator);

        if (i == j || graph[i][j] == 1)
            continue;

        graph[i][j] = 1;
        graph[j][i] = 1;
        numEdges++;
    }

    return graph;
}

void printGraph(const std::vector<std::vector<int>>& graph)
{
    for (const auto& row : graph)
    {
        for (int val : row)
            std::cout << val << " ";
        std::cout << std::endl;
    }
}

int countEdges(const std::vector<std::vector<int>>& graph)
{
    int numEdges = 0;
    int numVertices = graph.size();

    for (int i = 0; i < numVertices; i++)
    {
        for (int j = i + 1; j < numVertices; j++)
        {
            if (graph[i][j] == 1)
                numEdges++;
        }
    }

    return numEdges;
}

bool isEulerianGraph(const std::vector<std::vector<int>>& graph)
{
    int numVertices = graph.size();

    // Sprawdzenie, czy graf jest spójny
    std::vector<bool> visited(numVertices, false);
    std::queue<int> queue;
    int startVertex = 0;
    int numVisited = 0;

    queue.push(startVertex);
    visited[startVertex] = true;
    numVisited++;

    while (!queue.empty())
    {
        int currentVertex = queue.front();
        queue.pop();

        for (int i = 0; i < numVertices; i++)
        {
            if (graph[currentVertex][i] == 1 && !visited[i])
            {
                queue.push(i);
                visited[i] = true;
                numVisited++;
            }
        }
    }

    if (numVisited != numVertices)
        return false; // Graf jest niespójny, nie jest eulerowski

    // Sprawdzenie stopnia ka¿dego wierzcho³ka
    for (int i = 0; i < numVertices; i++)
    {
        int degree = 0;
        for (int j = 0; j < numVertices; j++)
        {
            degree += graph[i][j];
        }
        // Jeœli stopieñ wierzcho³ka jest nieparzysty, to graf nie jest eulerowski
        if (degree % 2 != 0)
            return false;
    }

    return true;
}

void findHamiltonianCyclesUtil(const std::vector<std::vector<int>>& graph, std::vector<int>& path, std::vector<bool>& visited, int currentVertex, int startVertex, int numVertices, int& count)
{
    visited[currentVertex] = true;
    path.push_back(currentVertex);

    if (path.size() == numVertices)
    {
        // Sprawdzenie, czy istnieje krawêdŸ miêdzy ostatnim wierzcho³kiem a wierzcho³kiem startowym
        if (graph[currentVertex][startVertex] == 1)
        {
            count++;
            //std::cout << "Cykl Hamiltona " << count << ": ";
            //for (int vertex : path)
                //std::cout << vertex << " ";
            //std::cout << startVertex << std::endl;
        }
    }
    else
    {
        for (int i = 0; i < numVertices; i++)
        {
            if (!visited[i] && graph[currentVertex][i] == 1)
            {
                findHamiltonianCyclesUtil(graph, path, visited, i, startVertex, numVertices, count);
            }
        }
    }

    visited[currentVertex] = false;
    path.pop_back();
}

void findHamiltonianCycles(const std::vector<std::vector<int>>& graph)
{
    int numVertices = graph.size();
    std::vector<int> path;
    std::vector<bool> visited(numVertices, false);
    int count = 0;

    for (int i = 0; i < numVertices; i++)
    {
        findHamiltonianCyclesUtil(graph, path, visited, i, i, numVertices, count);
    }
}

void clearGraph(std::vector<std::vector<int>>& graph)
{
    for (auto& row : graph)
        row.clear();
    graph.clear();
}

int main()
{
    for (int i = 1; i < 20; i++) {
        int numVertices = i; // Liczba wierzcho³ków w grafie

        // Generowanie spójnego eulerowskiego grafu
        std::vector<std::vector<int>> eulerianGraph = generateEulerianGraph(numVertices);

        // Wyœwietlanie grafu
        //printGraph(eulerianGraph);
        //std::cout << "Liczba krawedzi: " << countEdges(eulerianGraph) << std::endl;
        if (isEulerianGraph) {
            std::cout << "Graf jest eulerowski" << std::endl;
            //if (!isEulerianGraph) std::cout << "Graf nie jest eulerowski" << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            findHamiltonianCycles(eulerianGraph);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            double executionTime = duration.count();
            std::cout << "Execution time for " << i << " vertices: " << executionTime << std::endl;
            clearGraph(eulerianGraph);
        }
    }
    
    return 0;
}