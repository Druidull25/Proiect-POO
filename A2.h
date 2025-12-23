#pragma once
#include <iostream>
#include <utility>
#include <cmath>
#include <vector> // Added for safer dynamic arrays if needed
using namespace std;

// Heuristic: Euclidean distance
int euristic(pair<int, int> a, pair<int, int> b)
{
    // Consider using Manhattan distance (abs(dx) + abs(dy)) if 4-way movement, 
    // but Euclidean is fine for 8-way.
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

// Helper to flatten 2D coordinates to 1D index
int Index(pair<int, int> a, int Width)
{
    return a.second * Width + a.first;
}

// Recursive function to print the path
int road(int* par, int node1, int nodeanch, int Width)
{
    if (par[node1] != -1)
    {

      //  printf("(%d %d)-> ", node1 % Width, node1 / Width);
        
        return 1 + road(par, par[node1], nodeanch, Width);
    }
    else
    {
        //printf("(%d %d)", node1 % Width, node1 / Width);
        return 0;
    }
}

int A(pair<int, int> start, pair<int, int> goal, char mat[200][200], int Width, int Length)
{

    static pair<int, int> open[400000];
    static pair<int, int> aux;
    
    // Using a boolean array for "closed" set is O(1) vs O(N) for linear search
    // We allocate this dynamically or use a large static array.
    // Here is a safe way using a simple array based on your max expected size.
    bool closedList[400000]; 
    bool openListMask[400000]; // Optimization to check if node is in open list quickly

    // Reset arrays for safety if function is called multiple times
    for(int k=0; k<Width*Length; k++) 
    {
        closedList[k] = false;
        openListMask[k] = false;
    }

    static int g[400000], h[400000], f[400000], par[400000];

    int nropen = 0; // Fixed initialization to 0, incremented below

    // Add start node
    open[nropen++] = start;
    int startIndex = Index(start, Width);
    g[startIndex] = 0;
    h[startIndex] = euristic(start, goal);
    f[startIndex] = g[startIndex] + h[startIndex];
    par[startIndex] = -1;
    openListMask[startIndex] = true;

    while (nropen > 0)
    {
        // 1. Find node with lowest f in open list
        int min_f = 999999999;
        int index = -1;
        pair<int, int> current;

        for (int i = 0; i < nropen; i++)
        {
            int idx = Index(open[i], Width);
            if (f[idx] < min_f)
            {
                min_f = f[idx];
                current = open[i];
                index = i;
            }
        }

        // 2. Check Goal
        if (Index(current, Width) == Index(goal, Width))
        {
            return road(par, Index(goal, Width), Index(goal, Width), Width);

        }

        openListMask[Index(current, Width)] = false; 
        for (int i = index; i < nropen - 1; i++)
        {
            open[i] = open[i + 1];
        }
        nropen--;

        closedList[Index(current, Width)] = true;

        for (int i = -1; i <= 1; i++) 
        {
            for (int j = -1; j <= 1; j++) 
            {
                if ((i == 0 && j == 0 ) || i == j) continue;

                aux.first = current.first + j;   
                aux.second = current.second + i; 

                if (aux.first >= 0 && aux.first < Width &&
                    aux.second >= 0 && aux.second < Length)
                {
                    // Check Obstacles
                    if (mat[aux.second][aux.first] != '#')
                    {
                        int auxIdx = Index(aux, Width);

                        // Check if already in Closed List (Optimization)
                        if (closedList[auxIdx]) continue;

                        int auxg = g[Index(current, Width)] + euristic(current, aux);

                        // Check if already in Open List with a better G
                        if (openListMask[auxIdx])
                        {
                            if (auxg >= g[auxIdx]) continue;
                        }
                        else
                        {
                            open[nropen++] = aux;
                            openListMask[auxIdx] = true;
                        }

                        par[auxIdx] = Index(current, Width);
                        g[auxIdx] = auxg;
                        h[auxIdx] = euristic(aux, goal);
                        f[auxIdx] = g[auxIdx] + h[auxIdx];
                    }
                }
            }
        }
    }

    printf("Nu exista drum.");
}