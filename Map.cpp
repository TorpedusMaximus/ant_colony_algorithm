#include <iostream>
#include <utility>
#include <fstream>
#include <tuple>
#include "Map.h"

Map::Map(const std::string &path, int mode) {
    this->mode = mode;
    float min_distance = this->load_map(path);

    this->pheromone_map = std::vector(this->number_of_vertices, std::vector<float>(this->number_of_vertices, 0));
    for (int i = 0; i < number_of_vertices; i++) {
        for (int ii = 0; ii < number_of_vertices; ii++) {
            if (i == ii) {
                pheromone_map[i][ii] = -inf;
            }
            pheromone_map[i][ii] = min_distance / distances[i][ii];
        }
    }

}

Map::~Map() {

}

void Map::add_pheromone(int position_1, int position_2, float value) {
    this->pheromone_map[position_1][position_2] += value;
    this->pheromone_map[position_2][position_1] += value;

}

void Map::reduce_pheromone_on_all_paths() {
    /*
     * Reducing pheromone is crucial to erase worse paths.
     * Pheromones are reduced differently based on chosen mode.
     */
    for (int i = 0; i < this->number_of_vertices; i++) {
        for (int ii = 0; ii < this->number_of_vertices; ii++) {
            switch (this->mode) {
                case 0:
                    this->pheromone_map[i][ii] -= reduce_number;
                    break;
                case 1:
                    this->pheromone_map[i][ii] *= (1 - reduce_factor);
                    break;
                default:
                    //exception
                    std::cout << "Wrong map_mode" << std::endl;

            }

        }
    }
}

void Map::calculate_best_path() {
    /*
     * Best path is the path with the highest sum of pheromone
     */
    std::vector<int> current_path;
    current_path.push_back(0);
    float current_path_sum = 0;
    int current_position = 0;

    while (current_path.size() < number_of_vertices) {
        auto positions = get_highest_pheromone_list_from_vertex(current_position);
        for (auto position: current_path) {
            auto found_element = std::find(positions.begin(), positions.end(), position);
            if (found_element != positions.end()) {
                positions.erase(found_element);
            }
        }
        int new_position = positions[0];
        current_path.push_back(new_position);
        current_path_sum += distances[current_position][new_position];
        current_position = new_position;

    }

    current_path_sum += distances[current_path[number_of_vertices - 1]][0];


    if (current_path_sum < best_path_sum) {
        best_path_sum = current_path_sum;
        best_path_vertices = current_path;
    }
}

float Map::get_distance_on_path(int position_1, int position_2) {
    return this->distances[position_1][position_2];
}

std::vector<int> Map::get_highest_pheromone_list_from_vertex(int position) {
    std::vector<std::pair<int, float>> paths_list;
    for (int i = 0; i < this->number_of_vertices; i++) {
        if (i == position) {
            continue;
        }
        std::pair<int, float> point = std::make_pair(i, this->pheromone_map[position][i]);
        paths_list.push_back(point);
    }
    std::vector<int> vertices;

    std::sort(paths_list.begin(), paths_list.end(),
              [](const std::pair<int, float> &a, const std::pair<int, float> &b) {
                  return a.second > b.second;
              });

    for (auto point: paths_list) {
        vertices.push_back(point.first);
    }

    return vertices;
}

std::vector<int> Map::get_best_path_vertices() {
    return this->best_path_vertices;
}

float Map::load_map(const std::string &path) {
    std::ifstream file;
    file.open(path, std::ios::in);

    std::string filename;
    float min_distance = inf;
    if (file) {
        file >> filename;
        file >> this->number_of_vertices;
        this->distances = std::vector(this->number_of_vertices, std::vector<float>(this->number_of_vertices, 0));

        for (int i = 0; i < this->number_of_vertices; i++) {
            for (int ii = 0; ii < this->number_of_vertices; ii++) {
                float distance;
                file >> distance;
                this->distances[i][ii] = distance;
                if (distance < min_distance && distance > 0) {
                    min_distance = distance;
                }
            }
        }
        file >> this->global_best_path_sum;
    } else {
        // exception
        std::cout << "No map found" << std::endl;
    }

    file.close();
    return min_distance;
}

int Map::get_best_path_sum() {
    return this->best_path_sum;
}

Map::Map() {}// Why do i need this???

