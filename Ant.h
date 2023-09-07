#pragma once

#include <vector>

class Ant {
public:
    int position_id;
    float pheromone_value = 1.0f;

    Ant(int id, int mode);

    ~Ant();

    int choose_new_position(std::vector<int> path_list);

    void move_to(int new_position_id);

    void reset();

    float leave_pheromone(float distance);

private:
    int id;
    int mode;

    int conformity_factor_1 = 30;
    int conformity_factor_2 = 10;

    std::vector<int> visited_vertices;

};
