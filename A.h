#pragma once
#include <iostream>
#include <utility>
#include <cmath>
using namespace std;

int euristic(pair<int, int> a, pair<int, int> b)
{
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}


int Index(pair<int, int> a, int Width)
{
    return a.second * Width + a.first;
}

void road ( int par[100], int node1, int nodeanch)
{

    if(par[node1] != -1)
    {
        road(par, par[node1], nodeanch);

        if(node1 == nodeanch)
        {
        printf("%d ",node1);
   
        }
        else
        {
        printf("%d -> ",node1);
        }
    }
    else
    {
     printf("%d -> ",node1);
    }

}
void A (pair<int, int> start, pair<int, int> goal, char mat[200][200], int Width, int Length)
{

   static pair<int, int> open[400000], closed[400000], aux;
   static int g[400000], h[400000], f[400000], par[400000];

    int nropen = 1, nrclosed = 0;

    open[nropen - 1] = start;
    g[Index(start, Width)] = 0;
    h[Index(start, Width)] = euristic(start, goal);
    f[Index(start, Width)] = g[Index(start, Width)] + h[Index(start, Width)];
    par[Index(start, Width)] = -1;


    while(nropen)
    {
        int min = f[Index(open[0], Width)], index = 0;
        pair<int, int> current = open[0];

        for(int i = 0; i < nropen; i++)
        {
            if(f[Index(open[i], Width)] < min)
            {
                min = f[Index(open[i], Width)];
                current = open[i];
                index = i;
            }

        }

        if( Index(current, Width) == Index(goal, Width))
        {
            road(par, Index(goal, Width), Index(goal, Width));

            return;
        }

        for(int i = index; i < nropen - 1; i++)
        {
            open[i] = open[i + 1];
        }

        nropen--;

        closed[nrclosed] = current;
        nrclosed++;

        for(int i = -1; i <= 1; i++)
        {
            for(int j = -1; j <= 1; j++)
            {

            if (current.second + i >= 0 && current.second + i < Width
                && current.first + j >= 0 && current.first + j < Length
                && current.second + i != current.second && current.first + j !=current.first)
            if (mat[current.second + i][current.first + j] !='#')
            {   
                int ok2 = 0;

                for(int l = 0; l < nrclosed; l++)
                {
                    if(closed[l].second == current.second + i && closed[l].first == current.first + j)
                    {
                        ok2 = 1;
                        break;
                    }
                }

                if(ok2)
                {
                    continue;
                }

                aux.first = current.second + i;
                aux.second = current.first + j;
            
                int auxg = g[Index(current, Width)] + euristic(current , aux);

                int ok = 0;

                for(int l = 0; l < nropen; l++)
                {
                    if(open[l] == aux)
                    {
                        ok = 1;
                    
                    }
                }

                if(!ok)
                {
                    open[nropen] = aux;
                    nropen++;
                }
                else
                {
                    if (auxg >= g[Index(aux, Width)])
                    {
                        continue;
                    } 
                }

                par[Index(aux, Width)] = Index(current, Width);
                g[Index(aux, Width)] = auxg;
                h[Index(aux, Width)] = euristic(aux, goal);
                f[Index(aux, Width)] = g[Index(aux, Width)] + h[Index(aux, Width)];
            }

            }

        }
    }
    printf("Nu exista drum.");
}