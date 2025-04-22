import numpy as np
import subprocess

# Load the CSV file
arrs = np.loadtxt("data_table.csv", delimiter=",", dtype=str, skiprows=1)

# Remove empty rows
arrs = [row for row in arrs if len(row[0]) > 0]

# === Array Preparation ===
# Split arrs into two lists (arr1 and arr2), each storing one column of data
arr1 = [float(row[0]) for row in arrs]  
arr2 = [float(row[1]) for row in arrs] 

# Convert arr1 and arr2 to strings with square brackets
arr1 = "[" + ", ".join(map(str, arr1)) + "]"
arr2 = "[" + ", ".join(map(str, arr2)) + "]"

# === Call C Part === (Do not modify this section)
subprocess.run(["gcc", "part3_calc_cov_and_var.c", "-o", "part3_calc_cov_and_var.out"])
direct_output = subprocess.run(["./part3_calc_cov_and_var.out", arr1, arr2], stdout=subprocess.PIPE)

# Print the output from the C program
outprint = str(direct_output.stdout)[2:-3]
print(outprint)
