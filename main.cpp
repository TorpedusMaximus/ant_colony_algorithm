#include <iostream>
#include "Ant.h"
#include "Map.h"
#include "Simulation.h"

int main() {
    Simulation simulation = Simulation("data/16.tsp", 1, 1, 12);
    simulation.run(1000);
    simulation.results();

    return 0;
}
