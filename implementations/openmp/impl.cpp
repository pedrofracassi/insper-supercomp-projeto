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

  // Função auxiliar para verificar se um vértice pode ser adicionado à clique atual
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

  // Função recursiva para busca exaustiva da clique máxima
  void exhaustiveSearch(std::vector<int> &currentClique, std::vector<int> &candidates, int start)
  {
    if (candidates.empty())
    {
      #pragma omp critical
      {
        if (currentClique.size() > maxClique.size())
        {
          maxClique = currentClique;
        }
      }
      return;
    }

    for (int i = start; i < candidates.size(); i++)
    {
      int vertex = candidates[i];
      if (isConnectedToAll(vertex, currentClique))
      {
        currentClique.push_back(vertex);
        exhaustiveSearch(currentClique, candidates, i + 1);
        currentClique.pop_back();
      }
    }
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
        exhaustiveSearch(localClique, candidates, i + 1);
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
    std::cout << "Uso: " << argv[0] << " <arquivo_de_entrada>" << std::endl;
    return 1;
  }

  MaxCliqueFinder finder(argv[1]);

  auto start = std::chrono::high_resolution_clock::now();
  std::vector<int> maxClique = finder.findMaxClique();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << "Tamanho da clique máxima: " << maxClique.size() << std::endl;
  std::cout << "Vértices na clique máxima: ";
  for (int vertex : maxClique)
  {
    std::cout << vertex << " ";
  }
  std::cout << std::endl;
  std::cout << "Tempo de execução: " << duration.count() << " ms" << std::endl;

  return 0;
}
