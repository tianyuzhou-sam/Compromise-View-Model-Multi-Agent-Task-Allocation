#include <iostream>
#include <vector>
#include <iterator>
#include <tuple>
#include <math.h>
#include "compromise_view_model.hpp"
#include "../externals/astar-algorithm-cpp/include/find_path.h"
#include "../externals/astar-algorithm-cpp/include/MapInfo.h"
#include "../externals/astar-algorithm-cpp/include/smooth_path.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

inline std::tuple<std::vector<std::vector<int>>, float > CV_model(
    std::vector<int>& agent_position,
    std::vector<int>& targets_position,
    const std::vector<int> &world_map,
    const int &map_width,
    const int &map_height
    )
{
    const int num_agent = static_cast<int>(agent_position.size() / 2);
    const int num_task = static_cast<int>(targets_position.size() / 2);

    struct MapInfo Map;
    Map.world_map = world_map;
    Map.map_width = map_width;
    Map.map_height = map_height;
    
    
    int* agent_position_array = agent_position.data();
    int* targets_position_array = targets_position.data();
    int agent_start_position[2*num_agent];
    for (int i = 0; i < 2*num_agent; i++) {
        agent_start_position[i] = agent_position[i];
    }
    
    std::vector<int> start_case_vec(2 * num_agent * num_task, -1);
    int *solution = start_case_vec.data(); 

    float cost = 0;

    cv_model(num_agent, num_task, agent_position_array, targets_position_array, solution);

    // each sub-vector is the indices of the assigned tasks, where the order is the execution order
    std::vector<std::vector<int>> allocation_result;
    float total_cost = 0;
    for (int i = 0; i < num_agent; i++) {
        std::vector<int> result_this;
        int start[2];
        start[0] = agent_start_position[i*2];
        start[1] = agent_start_position[i*2+1];
        result_this.push_back(start[0]);
        result_this.push_back(start[1]);
        for (int j = 0; j < num_task; j++) {
            if (solution[i*num_task*2+j*2] >= 0) {
                int end[2];
                end[0] = solution[i*num_task*2+j*2];
                end[1] = solution[i*num_task*2+j*2+1];

                std::vector<int> path;
                float a_star_cost;
                std::tie(path, a_star_cost) = find_path(start, end, Map);
                std::vector<int> path_smooth = smooth_path(path, Map);

                for (int k = 0; k < path_smooth.size() - 2; k+=2) {
                    total_cost += sqrt(pow(path_smooth[k]-path_smooth[k+2], 2) + pow(path_smooth[k+1]-path_smooth[k+3], 2));
                }

                for (int k = 2; k < path_smooth.size(); k++) {
                    result_this.push_back(path_smooth[k]);
                }
                start[0] = end[0];
                start[1] = end[1];
            }
        }
        allocation_result.push_back(result_this);
    }

    return {allocation_result, total_cost};
}


inline PYBIND11_MODULE(CV_model, module) {
    module.doc() = "Python wrapper of CV model";

    module.def("CV_model", &CV_model, "Compromise view model for multi-agent mission planning");
}