import argparse
import csv
import matplotlib.pyplot as plt
import numpy as np

parser = argparse.ArgumentParser(description='Create graph')
parser.add_argument('-f', '--file', metavar='F', nargs='+', type=str, help='Name of the input file', required=True)
parser.add_argument('-o', '--output', metavar='O', type=str, help='Name of the output file', default='graph.png')
parser.add_argument('-l', '--limit', metavar='N', type=float, help='Energy display limit')

args = parser.parse_args()

fig, ax1 = plt.subplots(dpi=300, figsize=(15, 8))
ax2 = ax1.twinx()

ymax = None
for file in args.file:
    rows = []
    print(file)
    with open(file) as stats:
        stats_reader = csv.reader(stats, delimiter=' ')
        for row in stats_reader:
            rows.append(list(map(float, row)))
    arr = np.array(rows)

    ymax = np.max(arr[:, 1])
    if args.limit:
        ymax = min([ymax, args.limit])

    ax1.plot(arr[:, 0], arr[:, 1] + 1, color='r', linewidth="1", label="curr", alpha=0.25)
    ax1.plot(arr[:, 0], arr[:, 2] + 1, color='r', linewidth="2", label="best")
    ax1.semilogy()
    ax1.set_ylim([1, ymax])
    ax1.set_ylabel('energy')
    ax2.plot(arr[:, 0], arr[:, 3], color='b', linewidth="2", label="temp")
    ax1.set_xlabel('steps')

    # plt.fill_between(arr[:, 0]/args.scale, arr[:, 2], arr[:,4], alpha=0.5)

    # fig.tight_layout()
    fig.savefig(args.output)
    fig.show()
