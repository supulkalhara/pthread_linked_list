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

# Serial results
serial_results = {
    "Case1": {"Avg": 0.0132, "Std": 0.0003},
    "Case2": {"Avg": 0.0140, "Std": 0.0014},
    "Case3": {"Avg": 0.0338, "Std": 0.0018},
}

# Plot the average execution time against the number of threads for each case
for case in cases:
    plt.figure(figsize=(8, 6))
    plt.subplot(2, 1, 1)
    plt.title(f"{case} - Average Execution Time vs. Number of Threads")
    plt.xlabel("Number of Threads")
    plt.ylabel("Average Execution Time")

    for implementation in implementations:
        avg_times = [
            results[case][implementation][threads]["Avg"] for threads in thread_counts
        ]
        plt.plot(thread_counts, avg_times, marker="o", label=f"{implementation}")

    # Add serial results
    serial_avg = serial_results[case]["Avg"]
    plt.axhline(y=serial_avg, color="r", linestyle="--", label="Serial (1 Thread)")

    plt.legend()
    plt.grid(True)

    plt.subplot(2, 1, 2)
    plt.title(f"{case} - Standard Deviation vs. Number of Threads")
    plt.xlabel("Number of Threads")
    plt.ylabel("Standard Deviation")

    for implementation in implementations:
        std_devs = [
            results[case][implementation][threads]["Std"] for threads in thread_counts
        ]
        plt.plot(thread_counts, std_devs, marker="o", label=f"{implementation}")

    plt.legend()
    plt.grid(True)

    plt.tight_layout()
    plt.show()

# Plot all cases in one graph
plt.figure(figsize=(10, 6))
plt.title("All Cases - Average Execution Time vs. Number of Threads")
plt.xlabel("Number of Threads")
plt.ylabel("Average Execution Time")

for case in cases:
    for implementation in implementations:
        avg_times = [
            results[case][implementation][threads]["Avg"] for threads in thread_counts
        ]
        plt.plot(
            thread_counts, avg_times, marker="o", label=f"{implementation} - {case}"
        )

# Add serial results
for case in cases:
    serial_avg = serial_results[case]["Avg"]
    plt.axhline(
        y=serial_avg, color="r", linestyle="--", label=f"Serial (1 Thread) - {case}"
    )

plt.legend()
plt.grid(True)
plt.show()
