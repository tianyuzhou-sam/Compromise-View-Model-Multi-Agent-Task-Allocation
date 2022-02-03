#include <stdio.h> 
#include <math.h>
#include <iostream>
#include <vector>


inline float compute_PD(int start[], int end[]) {
    float PD = 0;       // PD is path distance, degined as folowing
    PD = sqrt(pow(start[0]-end[0], 2) + pow(start[1]-end[1], 2));
    return PD;
}


inline void cv_model(const int num_agent, const int num_target, int agent_position[], int target_not_assigned[], int path[]) {
    int iter = 0;
    int num_target_not_assigned = num_target;

    while (num_target_not_assigned > 0) {
        // initialization
        int assigned_target[num_agent*2];
        for (int i = 0; i < num_agent; i++) {
            assigned_target[i*2] = -1;
            assigned_target[i*2+1] = -1;
        }

        float pd_cost[num_agent];
        int num_conflict = num_agent;
        
        // assign one task to each agent
        while (num_conflict != 0) {
            //  All agent choose its first target with the lowest cost.
            num_conflict = 0;
            for (int i = 0; i < num_agent; i++) {
                int this_agent[2];
                this_agent[0] = agent_position[i*2];
                this_agent[1] = agent_position[i*2+1];
                
                if (assigned_target[i*2] == -1 && assigned_target[i*2+1] == -1) {
                    float min_pd = 10E6;
                    for (int j = 0; j < num_target; j++) {
                        int this_target[2];
                        this_target[0] = target_not_assigned[j*2];
                        this_target[1] = target_not_assigned[j*2+1];
                        if (this_target[0] != -1 && this_target[1] != -1) {
                            float new_pd = compute_PD(this_agent, this_target);
                            if (new_pd < min_pd) {
                                min_pd = new_pd;
                                assigned_target[i*2] = this_target[0];
                                assigned_target[i*2+1] = this_target[1];
                            }
                        }
                    }
                    pd_cost[i] = min_pd;
                }

                // check conflict
                for (int k = 0; k < i; k++) {
                    if (assigned_target[i*2] == assigned_target[k*2] && assigned_target[i*2+1] == assigned_target[k*2+1] && assigned_target[k*2] != -1) {
                        if (pd_cost[i] < pd_cost[k]) {
                            assigned_target[k*2] = -1;
                            assigned_target[k*2+1] = -1;
                        } else {
                            assigned_target[i*2] = -1;
                            assigned_target[i*2+1] = -1;
                        }
                        num_conflict++;
                    }
                }
            }
            // remove assigned tasks
            for (int i = 0; i < num_agent; i++) {
                for (int j = 0; j < num_target; j++) {
                    if (assigned_target[i*2] == target_not_assigned[j*2] && assigned_target[i*2+1] == target_not_assigned[j*2+1]) {
                        target_not_assigned[j*2] = -1;
                        target_not_assigned[j*2+1] = -1;
                    }
                }
            }

            if (num_target_not_assigned < num_agent) {
                int finish = 0;
                for (int i = 0; i < num_target; i++) {
                    if (target_not_assigned[i*2] != -1) {
                        finish = -1;
                    }
                }
                if (finish == 0) {
                    num_conflict = 0;
                }
            }           
        }

        num_target_not_assigned -= num_agent;
        // add to path
        for (int i = 0; i < num_agent; i++) {
            path[i*num_target*2+iter*2] = assigned_target[i*2];
            path[i*num_target*2+iter*2+1] = assigned_target[i*2+1];
            if (assigned_target[i*2] != -1) {
                agent_position[i*2] = assigned_target[i*2];
                agent_position[i*2+1] = assigned_target[i*2+1];
            }
        }       
        iter++;

    }
    // for (int i = 0; i < num_agent; i++) {
    //     for (int j = 0; j < num_target; j++) {
    //         std::cout<< path[i*num_target*2+j*2] << "," << path[i*num_target*2+j*2+1] << ";";
    //     }
    //     std::cout<<"\n";
    // }

    return;
}