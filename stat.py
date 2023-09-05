import numpy as np

filename = "./results/oneMutex_3t.txt"

data = []
with open(filename, "r") as file:
    for line in file:
        val = float(line.split()[0])
        data.append(val)

data = np.array(data)

print(f"Stats for {filename}")
print(f"Average: {np.mean(data)}")
print(f"STD: {np.std(data)}")
