import matplotlib.pyplot as plt
import numpy as np

# Data for each case
cases = ["Case 1", "Case 2", "Case 3"]
impl = ["Serial", "One Mutex", "Read-Write lock"]
thread_counts = [1, 2, 4, 8]

data = {
    "Case 1": {
        "Serial": {"Avg": 0.0132, "Std": 0.0003},
        "One Mutex": {"Avg": [0.0154, 0.0284, 0.0293, 0.0318], "Std": [0.0008, 0.0017, 0.0015, 0.0014]},
        "Read-Write lock": {"Avg": [0.0157, 0.0194, 0.0298, 0.0468], "Std": [0.0014, 0.0034, 0.0029, 0.0059]},
    },
    "Case 2": {
        "Serial": {"Avg": 0.0140, "Std": 0.0014},
        "One Mutex": {"Avg": [0.0249, 0.0388, 0.0407, 0.0455], "Std": [0.0005, 0.0010, 0.0014, 0.0020]},
        "Read-Write lock": {"Avg": [0.0252, 0.0299, 0.0345, 0.0385], "Std": [0.0007, 0.0013, 0.0023, 0.0050]},
    },
    "Case 3": {
        "Serial": {"Avg": 0.0338, "Std": 0.0018},
        "One Mutex": {"Avg": [0.0487, 0.0633, 0.0683, 0.0826], "Std": [0.0018, 0.0021, 0.0043, 0.0111]},
        "Read-Write lock": {"Avg": [0.0489, 0.0647, 0.0801, 0.0804], "Std": [0.0017, 0.0050, 0.0113, 0.0079]},
    },
}

# Create individual plots for each case
for case in cases:
    plt.figure(figsize=(10, 6))
    plt.title(f'{case} - Average Execution Time vs. Number of Threads')
    plt.xlabel('Number of Threads')
    plt.ylabel('Average Execution Time')

    for imp in impl:
        avg_times = data[case][imp]["Avg"] if imp != "Serial" else [data[case][imp]["Avg"]] * len(thread_counts)
        std_devs = data[case][imp]["Std"] if imp != "Serial" else [data[case][imp]["Std"]] * len(thread_counts)
        plt.errorbar(thread_counts, avg_times, yerr=std_devs, marker='o', label=imp)

    plt.legend()
    plt.grid(True)
    plt.show()

# Create a single plot with all cases
plt.figure(figsize=(12, 8))
plt.title('All Cases - Average Execution Time vs. Number of Threads')
plt.xlabel('Number of Threads')
plt.ylabel('Average Execution Time')

for case in cases:
    for imp in impl:
        avg_times = data[case][imp]["Avg"] if imp != "Serial" else [data[case][imp]["Avg"]] * len(thread_counts)
        plt.errorbar(thread_counts, avg_times, marker='o', label=f"{imp} - {case}")

plt.legend()
plt.grid(True)
plt.show()
