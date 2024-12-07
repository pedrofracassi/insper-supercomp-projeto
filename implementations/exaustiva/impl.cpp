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

  // Função auxiliar para verificar se um vértice pode ser adicionado à clique atual
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

  // Função recursiva para encontrar a clique máxima
  void findMaxCliqueRecursive(std::vector<int> &candidates)
  {
    if (currentClique.size() > maxClique.size())
    {
      maxClique = currentClique;
    }

    std::vector<int> newCandidates;
    for (int i = 0; i < candidates.size(); i++)
    {
      int vertex = candidates[i];

      if (isConnectedToAll(vertex))
      {
        newCandidates.clear();
        for (int j = i + 1; j < candidates.size(); j++)
        {
          if (adjacencyMatrix[vertex][candidates[j]] == 1)
          {
            newCandidates.push_back(candidates[j]);
          }
        }

        currentClique.push_back(vertex);
        findMaxCliqueRecursive(newCandidates);
        currentClique.pop_back();
      }
    }
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

    findMaxCliqueRecursive(candidates);

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