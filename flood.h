#pragma once
#include<string>
#include <vector>
#include "A2.h"
#include <utility>
#include<cmath>
using namespace std;
class Agent
{
    protected:
    int speed, max_battery, current_battery,
    battery_consumption, Cost, Capacity;

    std::string state;
    char symbol;

    public:

    virtual void Charge_battery() = 0;
   // virtual void deliver() = 0;




    int getSpeed()
    {
        return this->speed;
    }

    int getCurrentBattery()
    {
        return this->current_battery;
    }

    int getBatteryConsumption()
    {
        return this->battery_consumption;
    }

    int getCost()
    {
        return this->Cost;
    }

    int getCapacity()
    {
        return this->Capacity;
    }

    void setBattery(int charge)
    {
        this->current_battery = charge;
    }
    

    Agent(int speed, int max_battery,
         int battery_consumption, int cost,
         int capacity)
         {
            this->speed = speed;
            this->max_battery = this->current_battery = max_battery;
            this->Cost = cost;
            this->battery_consumption = battery_consumption;
            this->Capacity = capacity;
         }
};


class Drone: public Agent
{
    public:
    Drone() : Agent(3, 100, 10, 15, 1) {}

    void Charge_battery() override
    {
        this->current_battery = 100;
    }


};

class Robot: public Agent
{
    public:
    Robot() : Agent(1, 300, 2, 1, 4) {}

    void Charge_battery() override
    {
        this->current_battery = 300;
    }

};

class Scooter: public Agent
{
    public:
    Scooter() : Agent(2, 200, 5, 4, 2) {}

    void Charge_battery() override
    {
        this->current_battery = 200;
    }
};

class HiveMind
{

    private:
    vector <Agent*> agents;

    public:

    void determine_road(Agent* agent, char map[200][200], pair<int, int> start_point, pair<int, int> destination, int Width, int Length, vector<pair<int,int>> &stops)
    {
        pair<int,int> aux, minPoint = start_point;


        int directionY;
        if(start_point.second - destination.second < 0)
        {
            directionY = -1;
        } 
        else
        {
            directionY = 1;
        }
        int directionX;

        if(start_point.first - destination.first < 0)
        {
            directionX = -1;
        } 
        else
        {
            directionX = 1;
        }
        int min  = A(start_point, destination, map, Width, Length);
        bool ok = 0;
        if(min > agent-> getCurrentBattery() / agent->getBatteryConsumption() * agent->getSpeed())
        {
            for(int i = 1; i < abs(start_point.second - destination.second); i++)
            {
                for(int j = 0 ; j < i ; j++)
                {
                    aux = {start_point.first - i, start_point.second + j * directionY};
                    if(min > A(aux, destination, map, Width, Length) && A(aux, destination, map, Width, Length) < agent->getBatteryConsumption() * agent->getSpeed())
                    {
                        min = A(aux, destination, map, Width, Length);
                        minPoint = aux;
                        ok = 1;
                    }

                    aux = {start_point.first + i, start_point.second + j * directionY};
                    if(min > A(aux, destination, map, Width, Length) && A(aux, destination, map, Width, Length) < agent->getBatteryConsumption() * agent->getSpeed())
                    {
                        min = A(aux, destination, map, Width, Length);
                        minPoint = aux;
                        ok = 1;
                    }
                }

                for(int j = 0; j < i; j++)
                {
                    aux = {start_point.first - j - 1, start_point.second + i * directionY};
                    if(min > A(aux, destination, map, Width, Length) && A(aux, destination, map, Width, Length) < agent->getBatteryConsumption() * agent->getSpeed())
                    {
                        min = A(aux, destination, map, Width, Length);
                        minPoint = aux;
                        ok = 1;
                    }

                    aux = {start_point.first + j + 1, start_point.second + i * directionY};
                    if(min > A(aux, destination, map, Width, Length) && A(aux, destination, map, Width, Length) < agent->getBatteryConsumption() * agent->getSpeed())
                    {
                        min = A(aux, destination, map, Width, Length);
                        minPoint = aux;
                        ok = 1;
                    }
                }

                    aux = {start_point.first , start_point.second + i * directionY};
                    if(min > A(aux, destination, map, Width, Length) && A(aux, destination, map, Width, Length) < agent->getBatteryConsumption() * agent->getSpeed())
                    {
                        min = A(aux, destination, map, Width, Length);
                        minPoint = aux;
                        ok = 1;
                    }


            }
            if(ok)
            {
                cout<<"?? "<<aux.first<<" "<<aux.second<<endl;
                stops.push_back(aux);
                agent->setBattery(agent->getCurrentBattery() - min * agent->getSpeed() / agent->getBatteryConsumption());
                determine_road(agent, map, aux, destination, Width, Length, stops);
            }
            else
            {
                cout << "Nu exista drum";
            }
        }
        else
        {
            stops.push_back(destination);
            cout<<"Wut "<<stops[0].first<<" "<<stops[0].second<<endl;
        }
    }

};


