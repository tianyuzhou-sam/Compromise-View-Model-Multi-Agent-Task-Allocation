import numpy as np
import matplotlib
import matplotlib.pyplot as plt

def plot_path(path: list, agent_position: list, targets_position: list, map: list, width: int, height: int):
    """
    path_many is a list for the trajectory. [[x[0],y[0],x[1],y[1], ...], [x[0],y[0],x[1],y[1], ...], ...]
    """
    map_array = 0 * np.ones((height, width)).astype(int)
    fig_map, ax_map = plt.subplots(1, 1)

    cmap = matplotlib.colors.ListedColormap(['white','black'])
    ax_map.pcolor(map_array, cmap=cmap, edgecolors='k')

    ax_map.scatter(agent_position[0]+0.5, agent_position[1]+0.5, label="start")
    for idx_target in range(0, int(len(targets_position)/2)):
        ax_map.scatter(targets_position[2*idx_target]+0.5, targets_position[2*idx_target+1]+0.5, label="goal")

    # for idx_path in range(0, len(path)):
    #     ax_map.plot(list(map(lambda x:x+0.5, path[idx_path][0::2])),
    #         list(map(lambda x:x+0.5, path[idx_path][1::2])))

    ax_map.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    ax_map.set_xlabel("x")
    ax_map.set_ylabel("y")
    ax_map.set_aspect('equal')
    ax_map.set_xlim([0, width])
    ax_map.set_ylim([0, height])
    plt.show(block=False)
