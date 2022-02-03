# Compromise-View-Model-Multi-Agent-Task-Allocation
* This is an implementation of compromise view model on multi-agent tasks allocation. Given an environment and multiple agents and targets, The agents could allocate targets and plan path using A*. The main program returns the path for each agent and the total distance for all agents.
* This repo uses C++ implementation and Python wrapper. I appreciate all the contributors' effort on C++ implement of A* algorithm. More details about how to use this A* implementation is provided by Zehui in [astar-algorithm-cpp](https://github.com/zehuilu/astar-algorithm-cpp.git).
# Dependencies
For Python
* [astar-algorithm-cpp](https://github.com/tianyuzhou-sam/astar-algorithm-cpp.git)
  - [pybind11](https://github.com/pybind/pybind11)
  - [numpy](https://numpy.org/)
  - [matplotlib](https://matplotlib.org/)
# Build
Note: Since [astar-algorithm-cpp](https://github.com/tianyuzhou-sam/astar-algorithm-cpp.git) is a submodule of this repo, follow the instructions below to build correctly.
```
$ sudo apt install gcc g++ cmake
$ sudo apt install python3-pybind11
$ pip3 install numpy matplotlib
$ git clone https://github.com/tianyuzhou-sam/Compromise-View-Model-Multi-Agent-Task-Allocation.git
$ cd <MAIN_DIRECTORY>
$ git submodule update --init --recursive
$ cd <MAIN_DIRECTORY>/externals/astar-algorithm-cpp
$ mkdir build
$ cd build
$ cmake ..
$ make
```
To build this repo,
```
$ cd <MAIN_DIRECTORY>
$ mkdir build
$ cd build
$ cmake ..
$ make
```
# Example
To run this example:
```
$ cd <MAIN_DIRECTORY>
$ python3 test/test_cv.py
```
Example output:
![compromise_view_example](https://user-images.githubusercontent.com/60674733/152315597-b62d0567-8489-4635-9070-83022ec71ffe.png)
# Citation
The compromise view model for multi-agent tasks allocation is based on the following paper. Appreciate authors for their work.
```
S. Biswas, S. G. Anavatti and M. A. Garratt, 
"Particle swarm optimization based co-operative task assignment and path planning for multi-agent system," 
2017 IEEE Symposium Series on Computational Intelligence (SSCI), 2017, pp. 1-6, doi: 10.1109/SSCI.2017.8280872.
```
