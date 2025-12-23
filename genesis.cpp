#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include "A2.h"
#include <utility>
#include "flood.h"
using namespace std;

class Map
{
    private:
    char map[200][200];
    int Length, Width;

    public:

    void setLocation(char c, int x,  int y)
    {
        if(x < this->Width && y < this->Length)
        {
            map[y][x] = c;
        }
    }

    void setWidth( int val)
    {
        this->Width = val;
    }
    void setLength( int val)
    {
        this->Length = val;
    }

    char getLocation( int x,  int y)
    {
        return map[y][x];
    }

     int getLenght()
    {
        return this->Length;
    }

     int getWidth()
    {
        return this->Width;
    }
void FloodAlgorythm(int x, int y, char v[200][200]) 
{
    if (x < 0 || x >= this->Width || y < 0 || y >= this->Length)
        return;


    if (v[y][x] == '#' || v[y][x] == '0')
        return;

    v[y][x] = '0';

    FloodAlgorythm(x + 1, y, v);     
    FloodAlgorythm(x - 1, y, v);     
    FloodAlgorythm(x, y + 1, v);     
    FloodAlgorythm(x, y - 1, v);     
    
    FloodAlgorythm(x + 1, y + 1, v); 
    FloodAlgorythm(x - 1, y - 1, v);
    FloodAlgorythm(x + 1, y - 1, v);
    FloodAlgorythm(x - 1, y + 1, v);
}
};
class iMapGenerator
{
    public:
    virtual void PlaceHq( int x,  int y) = 0;
    virtual void PlaceWall( int x,  int y,  int Length, bool direction) = 0;
    virtual void PlaceClient( int x,  int y) = 0;
    virtual void PlaceRechargeStation( int x,  int y) = 0;
    virtual bool CheckValidity() = 0;

};

class MapBuilder : public iMapGenerator
{
    

    public:
    Map map;

    MapBuilder( int Length,  int Width)
    {
        map.setLength(Length);
        map.setWidth(Width);
        cout << map.getWidth() << " " << map.getLenght() <<endl;
        for(int i = 0; i < Length; i++)
        {
            for(int j = 0; j < Width; j++)
            {
                map.setLocation('.', j, i);
            }

        }
    }

    void PlaceHq( int x,  int y) override
    {
        cout<<"!!! " << x << " " << y << endl;
        map.setLocation('B', x, y );
    }

    void PlaceWall( int x,  int y,  int Length, bool direction) override
    {
        if(direction)
        {
            for(int i = 0; i < Length; i++)
            {
                if(map.getLocation(x, y + i) != '.' || map.getLenght() == i + y)
                {
                    break;
                }
                else
                {
                    map.setLocation('#', x, y + i);
                }
            }


        }
        else
        {
            for(int i = 0; i < Length; i++)
            {
                if(map.getLocation(x + i, y) != '.' || map.getWidth() == i + x)
                {
                    break;
                }
                else
                {
                    map.setLocation('#', x + i, y);
                }
            } 
        }


    }

    void PlaceClient( int x,  int y) override
    {
        map.setLocation('D', x, y );
    }

    void PlaceRechargeStation( int x,  int y) override
    {
        map.setLocation('S', x, y );
    }

    bool CheckValidity() override
    {
        const int x = map.getWidth(), y = map.getLenght();
        int xhq, yhq;
        char aux[200][200];

        for(int i = 0; i < y; i++)
        {
            for(int j = 0; j < x; j++)
            {
                aux[i][j] = map.getLocation(j, i);
                if(map.getLocation(j, i) == 'B')
                {
                    xhq = j;
                    yhq = i;
                }
            }
        }
        map.FloodAlgorythm(xhq, yhq, aux);



        for(int i = 0; i < y; i++)
        {
            for(int j = 0; j < x; j++)
            {
                if(aux[j][i] == 'D' || aux[j][i] == 'S')
                {
                    return 0;
                }
            }
        }

        return 1;
    }

    void getInstance(Map &aux)
    {
       
       aux.setLength(map.getLenght());
       aux.setWidth(map.getWidth());

       for(int i = 0; i < map.getLenght(); i++)
       {
            for(int j = 0; j < map.getWidth(); j++)
            {
                aux.setLocation(map.getLocation(j,i),j,i);
            }
       }

    }

};

class CityAssembler
{

    public:

    void assembleCity(Map &aux)
    {
        bool ok = 0;
        do
        {
        srand(time(0));

        int Lenght = rand() % 80 + 20,
        Width = rand()%80 + 20,
        chargind_station_number = rand() % 15 + 10;

        MapBuilder *builder = new MapBuilder(Lenght, Width);


        int auxX, auxY;


        for(int i = 0; i < chargind_station_number - 1; i++)
        {
            do
            {
                auxX = rand() % Width;
                auxY = rand() % Lenght;

            } while (builder->map.getLocation(auxX, auxY) != '.');

            builder->PlaceRechargeStation(auxX, auxY);
        }

        if(builder->map.getLocation(builder->map.getWidth() / 2 + builder->map.getWidth() % 2, builder->map.getLenght() / 2 + builder->map.getLenght() % 2))
        {
            builder->PlaceRechargeStation(builder->map.getWidth() / 2 + builder->map.getWidth() % 2, builder->map.getLenght() / 2 + builder->map.getLenght() % 2);
        }

            do
            {
                auxX = rand() % Width;
                auxY = rand() % Lenght;

            } while (builder->map.getLocation(auxX, auxY) != '.');

        builder->PlaceHq(auxX, auxY);


        for(int i = 0; i < 20; i++)
        {
            builder->PlaceWall(rand() % Width, rand() % Lenght, 7, rand() % 2);
        }

        for(int i = 0 ; i < 10; i++)
        {
            do
            {
                auxX = rand() % Width;
                auxY = rand() % Lenght;

            } while (builder->map.getLocation(auxX, auxY) != '.');
            
            builder->PlaceClient(auxX, auxY);

        }


        ok = builder->CheckValidity();

        if(!ok)
        {
            delete builder;
        }
        else
        {
            builder->getInstance(aux);
        }

        } while(!ok);

    }

};

class MapLoader
{
    public:

    void LoadMap (Map &Map, string path)
    {
        ifstream cin;
        char aux[100];

        cin.open(path);

        cin.getline(aux, 100);
        cin.get();

        char *p = strtok(aux, " ");
        p = strtok(NULL, " ");

        Map.setWidth(atoi(p));
//      -------------------------
        cin.getline(aux, 100);
        cin.get();

        p = strtok(aux, " ");
        p = strtok(NULL, " ");

        Map.setLength(atoi(p));
//      -------------------------

        for( int i = 0; i < Map.getLenght(); i++)
        {
            cin.getline(aux, 100);
            cin.get();
            for( int j = 0; j < Map.getWidth(); j++)
            {
                Map.setLocation(aux[j], j, i);
            }
        }

        cin.close();
    }

};


int main()
{
    CityAssembler a;
    Map buc;
    MapLoader idk;
    string path = "map.txt";
    Agent* agent = new Drone;

    cout<<"!!!: " << agent->getCurrentBattery() / agent->getBatteryConsumption() * agent->getSpeed() <<endl;

    idk.LoadMap(buc, path);
   // a.assembleCity(buc);
    char aux[200][200];

    

    cout << buc.getWidth() << " " << buc.getLenght()<<endl;

    for(int i = 0; i < buc.getLenght(); i++) 
    {
        for(int j = 0; j < buc.getWidth(); j++) 
        {
            aux[i][j] = buc.getLocation(j,i);
            cout << buc.getLocation(j, i);
        }
        cout << endl;
    }

    pair <int,int> Base = {0,0}, Dest = {0, 60};

    int length = A(Base, Dest, aux, buc.getWidth(), buc.getLenght());

    vector<pair<int,int>> stops;

    HiveMind Glados;

    Glados.determine_road(agent, aux, Base, Dest, buc.getWidth(), buc.getLenght(), stops);

    cout<<stops.size();
    for(int i = 0; i < stops.size(); i++)
    {
        cout<<"("<<stops[i].first<<" " << stops[i].second<<") ";
    }



    //cout << buc.getWidth();

        
}
