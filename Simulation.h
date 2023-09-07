#pragma once

#include "Map.h"
#include "Ant.h"

class Simulation {
public:
    Map map;

    Simulation(const std::string &path, int map_mode, int ant_mode, int number_of_ants);

    ~Simulation();

    void run(int number_of_epochs);

    void results();

private:
    int ant_mode;
    int number_of_ants;
    std::vector<Ant *> ants;

    void create_ants();

};
