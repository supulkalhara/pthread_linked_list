import os
import numpy as np
import matplotlib.pyplot as plt

# Define the directory where your result files are located
results_dir = "./results2"

# Define the cases, implementations, and thread counts
cases = ["Case1", "Case2", "Case3"]
implementations = ["OneMutex", "ReadWrite"]
thread_counts = [1, 2, 4, 8]

# Create a dictionary to store the results
results = {}

# Loop through each case, implementation, and thread count
for case in cases:
    results[case] = {}
    for implementation in implementations:
        results[case][implementation] = {}
        for threads in thread_counts:
            results[case][implementation][threads] = {
                "Avg": 0.0,
                "Std": 0.0,
            }

            filename_pattern = (
                f"parallel{implementation.replace('-', '')}_c{case[-1]}_{threads}t.txt"
            )
            print("filename_pattern: ", filename_pattern)
            data = []

            for filename in os.listdir(results_dir):
                if filename.startswith(filename_pattern):
                    file_path = os.path.join(results_dir, filename)
                    with open(file_path, "r") as file:
                        for line in file:
                            val = float(line.split()[0])
                            data.append(val)

            if data:
                data = np.array(data)
                results[case][implementation][threads]["Avg"] = np.mean(data)
                results[case][implementation][threads]["Std"] = np.std(data)

header = "Impl\t\t|\t\t1\t\t|\t\t2\t\t|\t\t4\t\t|\t\t8"
print("\n\n\n", header)

for case in cases:
    print("\n", case)

    for implementation in implementations:
        row = f"{implementation}\t\t|\t\t"
        for threads in thread_counts:
            avg = results[case][implementation][threads]["Avg"]
            std = results[case][implementation][threads]["Std"]
            row += f"Avg:{avg:.6f} Std:{std:.6f}\t\t|\t\t"
        print(row)

# Plot the average execution time against the number of threads for each case
for case in cases:
    for implementation in implementations:
        avg_times = [
            results[case][implementation][threads]["Avg"] for threads in thread_counts
        ]
        plt.plot(
            thread_counts, avg_times, marker="o", label=f"{implementation} - {case}"
        )

plt.xlabel("Number of Threads")
plt.ylabel("Average Execution Time")
plt.title("Average Execution Time vs. Number of Threads")
plt.legend()
plt.grid(True)
plt.show()
