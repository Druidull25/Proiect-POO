#pragma once
#include<string>
#include <vector>
#include "A2.h"
#include <utility>
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
    virtual void deliver() = 0;

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

    void determine_road(Agent* agent, char map[200][200], pair<int, int> location)
    {
        
    }

};


