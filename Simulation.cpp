//
// Created by deus on 01.09.23.
//

#include <iostream>
#include <memory>
#include "Simulation.h"
#include "include/tqdm/tqdm.hpp"

Simulation::Simulation(const std::string &path, int map_mode, int ant_mode, int number_of_ants) {
    this->ant_mode = ant_mode;
    this->map = Map(path, map_mode);

    this->number_of_ants = number_of_ants;
    create_ants();


}

void Simulation::create_ants() {
    Ant *ant;
    int i = 0;
    while (ants.size() < number_of_ants) {
        ant = new Ant(i, ant_mode);
        ant->move_to(0);
        ants.push_back(ant);
        i++;
    }
}


Simulation::~Simulation() {
    for (auto ant: ants) {
        delete ant;
    }

}

void Simulation::run(int number_of_epochs) {
    for (int a: tq::trange(number_of_epochs)) {
        for (int ii = 1; ii < map.number_of_vertices; ii++) {
            for (auto ant: ants) {//Move each ant to the best possible destination from current location
                int current_position = ant->position_id;
                auto positions = map.get_highest_pheromone_list_from_vertex(current_position);
                int new_position = ant->choose_new_position(positions);//Ants decide next location based on pheromones and luck
                float distance = map.get_distance_on_path(current_position, new_position);
                map.add_pheromone(current_position, new_position, ant->leave_pheromone(distance));//Ants leave different amounts of pheromone based on mode
            }
        }

        map.calculate_best_path();
        map.reduce_pheromone_on_all_paths();
        for (auto ant: ants) {
            ant->reset();
        }

    }

}

void Simulation::results() {
    map.calculate_best_path();

    auto sum = map.get_best_path_sum();
    auto path = map.get_best_path_vertices();
    auto best = map.global_best_path_sum;

    double worse_by = ((1.0 * sum / best) - 1) * 100;

    std::cout << "\nResults:\nSum: " << sum << "\nBest sum overall: " << best << "\nResult worse by: " << worse_by
              << "%\nPath:" << std::endl;
    for (auto position: path) {
        std::cout << position << "->";
    }
    std::cout << "0";


};

