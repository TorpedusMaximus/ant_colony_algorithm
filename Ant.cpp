#include <iostream>
#include "Ant.h"


Ant::Ant(int id, int mode) {
    this->id = id;
    this->mode = mode;
    this->position_id = 0;
}

Ant::~Ant() {

}

void Ant::reset() {
    visited_vertices.clear();
    move_to(0);
}

void Ant::move_to(int new_position_id) {
    this->position_id = new_position_id;
    visited_vertices.push_back(new_position_id);
}

int Ant::choose_new_position(std::vector<int> path_list) {
    /*
     * Ants chose new position based on sorted vector of highest pheromone.
     * Based on random value, and conformity factor, ant chooses to get the best path, 2nd best path, or 3rd best path
     */
    for (auto position: visited_vertices) {
        auto found_element = std::find(path_list.begin(), path_list.end(), position);
        if (found_element != path_list.end()) {
            path_list.erase(found_element);
        }
    }

    if (path_list.size() == 0) {
        return position_id;
    }

    int new_position;
    int conformity = (std::rand() % 100);
    if (conformity > this->conformity_factor_1 || path_list.size() == 1) {
        new_position = path_list[0];
    } else {
        if (conformity > conformity_factor_2 || path_list.size() == 2) {
            new_position = path_list[1];
        } else {
            new_position = path_list[2];
        }
    }

    this->move_to(new_position);
    return new_position;
}


float Ant::leave_pheromone(float distance) {
    /*
     * Amount of pheromone left is decided by path distance, and chosen mode.
     */
    float added_pheromone = 0.0f;

    switch (mode) {
        case 0:
            added_pheromone = distance;
            break;
        case 1:
            added_pheromone = pheromone_value / distance;
            break;
        case 2:
            added_pheromone = pheromone_value;
            break;
        default:
            //exception
            std::cout << "Wrong ant mode" << std::endl;
            break;
    }


    return added_pheromone;
}

