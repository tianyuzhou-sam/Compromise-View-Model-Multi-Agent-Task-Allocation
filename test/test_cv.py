#!/usr/bin/env python3
import os
import sys
sys.path.append(os.getcwd() + '/externals/astar-algorithm-cpp/src')
sys.path.append(os.getcwd() + '/build')
sys.path.append(os.getcwd() + '/src')
import numpy as np
import matplotlib.pyplot as plt
from random import randint
import AStarPython
from Simulator import Simulator
from CV_model import CV_model

if __name__ == "__main__":
    # define the world
    map_width_meter = 20.0
    map_height_meter = 20.0
    map_resolution = 2
    value_non_obs = 0 # the cell is empty
    value_obs = 255 # the cell is blocked
    map_width = int(map_width_meter * map_resolution)
    map_height = int(map_height_meter * map_resolution)
    # create a simulator
    MySimulator = Simulator(map_width_meter, map_height_meter, map_resolution, value_non_obs, value_obs)
    # number of obstacles
    num_obs = 150
    # [width, length] size of each obstacle [meter]
    size_obs = [1, 1]
    # generate random obstacles
    MySimulator.generate_random_obs(num_obs, size_obs)
    # convert 2D numpy array to 1D list
    world_map = MySimulator.map_array.flatten().tolist()

    # define the start and goal
    num_agent = 3
    num_targets = 9
    agent_position, targets_position = MySimulator.generate_multi_agent_and_goals(num_agent, num_targets)
    
    path, cost = CV_model(agent_position, targets_position, world_map, map_width, map_height)
    
    print("Start:")
    print(agent_position)
    print("Targets:")
    print(targets_position)
    print("Path")
    print(path)
    print("Cost")
    print(cost)

    MySimulator.plot_multi_agent_path(path, agent_position, targets_position)

    plt.show()