#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <iterator>

class MaxCliqueFinder
{
private:
  std::vector<std::vector<int>> adjacencyMatrix;
  std::vector<int> currentClique;
  std::vector<int> maxClique;
  int numVertices;

  // Helper function to check if a vertex can be added to current clique
  bool isConnectedToAll(int vertex)
  {
    for (int v : currentClique)
    {
      if (adjacencyMatrix[vertex][v] == 0)
      {
        return false;
      }
    }
    return true;
  }

  // Recursive function to find maximum clique
  void findMaxCliqueRecursive(std::vector<int> &candidates)
  {
    // std::cout << "Finding maximum clique recursively..." << std::endl;

    // Update maximum clique if current is larger
    if (currentClique.size() > maxClique.size())
    {
      std::cout << "Current clique size: " << currentClique.size() << std::endl;
      maxClique = currentClique;
    }

    // Try adding each remaining candidate vertex
    std::vector<int> newCandidates;
    for (int i = 0; i < candidates.size(); i++)
    {
      int vertex = candidates[i];

      // Check if vertex can be added to current clique
      if (isConnectedToAll(vertex))
      {
        // std::cout << "Adding vertex " << vertex + 1 << " to current clique" << std::endl;
        // Create new candidates list for next recursive call
        newCandidates.clear();
        for (int j = i + 1; j < candidates.size(); j++)
        {
          if (adjacencyMatrix[vertex][candidates[j]] == 1)
          {
            newCandidates.push_back(candidates[j]);
          }
        }

        // Add vertex to current clique and recurse
        currentClique.push_back(vertex);
        findMaxCliqueRecursive(newCandidates);
        currentClique.pop_back();
      }
    }
  }

public:
  // Leitura do arquivo -- classes são daora!
  MaxCliqueFinder(const std::string &filename)
  {
    std::ifstream file(filename);
    int numEdges;
    file >> numVertices >> numEdges;

    adjacencyMatrix = std::vector<std::vector<int>>(
        numVertices, std::vector<int>(numVertices, 0));

    // Ler arestas
    std::cout << "Number of edges: " << numEdges << std::endl;

    for (int i = 0; i < numEdges; i++)
    {
      int u, v;
      file >> u >> v;
      // Adjust for 0-based indexing
      u--;
      v--;
      adjacencyMatrix[u][v] = 1;
      adjacencyMatrix[v][u] = 1;

      std::cout << "Edge " << i + 1 << ": " << u + 1 << " " << v + 1 << std::endl;
    }
    file.close();
  }

  std::vector<int> findMaxClique()
  {
    std::cout << "Number of vertices: " << numVertices << std::endl;
    // Initialize candidates with all vertices
    std::vector<int> candidates(numVertices);
    for (int i = 0; i < numVertices; i++)
    {
      std::cout << "Vertex " << i + 1 << std::endl;
      candidates[i] = i;
    }

    // Find maximum clique
    findMaxCliqueRecursive(candidates);

    // Convert to 1-based indexing for output
    for (int &v : maxClique)
    {
      v++;
    }
    return maxClique;
  }
};

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
  }

  std::cout << "Finding maximum clique..." << std::endl;

  MaxCliqueFinder finder(argv[1]);

  // Measure execution time
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<int> maxClique = finder.findMaxClique();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  // Print results
  std::cout << "Maximum clique size: " << maxClique.size() << std::endl;
  std::cout << "Vertices in maximum clique: ";
  for (int vertex : maxClique)
  {
    std::cout << vertex << " ";
  }
  std::cout << std::endl;
  std::cout << "Execution time: " << duration.count() << " ms" << std::endl;

  return 0;
}