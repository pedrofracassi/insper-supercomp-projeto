#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <omp.h>

class MaxCliqueFinder
{
private:
  std::vector<std::vector<int>> adjacencyMatrix;
  std::vector<int> maxClique;
  int numVertices;

  // Helper function to check if a vertex can be added to current clique
  bool isConnectedToAll(int vertex, const std::vector<int> &clique)
  {
    for (int v : clique)
    {
      if (adjacencyMatrix[vertex][v] == 0)
      {
        return false;
      }
    }
    return true;
  }

public:
  MaxCliqueFinder(const std::string &filename)
  {
    std::ifstream file(filename);
    int numEdges;
    file >> numVertices >> numEdges;

    adjacencyMatrix = std::vector<std::vector<int>>(
        numVertices, std::vector<int>(numVertices, 0));

    for (int i = 0; i < numEdges; i++)
    {
      int u, v;
      file >> u >> v;
      u--;
      v--;
      adjacencyMatrix[u][v] = 1;
      adjacencyMatrix[v][u] = 1;
    }
    file.close();
  }

  std::vector<int> findMaxClique()
  {
    std::vector<int> candidates(numVertices);
    for (int i = 0; i < numVertices; i++)
    {
      candidates[i] = i;
    }

#pragma omp parallel
    {
      std::vector<int> localClique;
#pragma omp for schedule(dynamic)
      for (int i = 0; i < numVertices; i++)
      {
        localClique.clear();
        localClique.push_back(candidates[i]);
        for (int j = 0; j < numVertices; j++)
        {
          if (i != j && isConnectedToAll(candidates[j], localClique))
          {
            localClique.push_back(candidates[j]);
          }
        }
#pragma omp critical
        {
          if (localClique.size() > maxClique.size())
          {
            maxClique = localClique;
          }
        }
      }
    }

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

  MaxCliqueFinder finder(argv[1]);

  auto start = std::chrono::high_resolution_clock::now();
  std::vector<int> maxClique = finder.findMaxClique();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

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
