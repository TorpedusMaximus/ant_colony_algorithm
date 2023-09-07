#pragma once

#include <vector>

class Map {
public:
    int number_of_vertices;
    float global_best_path_sum;

    Map(const std::string &path, int mode);

    Map(); //Why ????

    ~Map();

    int get_best_path_sum();

    std::vector<int> get_best_path_vertices();

    float get_distance_on_path(int position_1, int position_2);

    std::vector<int> get_highest_pheromone_list_from_vertex(int position);

    void calculate_best_path();

    void reduce_pheromone_on_all_paths();

    void add_pheromone(int position_1, int position_2, float value);

private:
    float reduce_factor = 0.2;
    float reduce_number = 1;
    float inf = std::numeric_limits<float>::infinity();

    int mode;

    float best_path_sum = inf;
    std::vector<int> best_path_vertices;

    std::vector<std::vector<float>> distances;
    std::vector<std::vector<float>> pheromone_map;


    float load_map(const std::string &path);
};
