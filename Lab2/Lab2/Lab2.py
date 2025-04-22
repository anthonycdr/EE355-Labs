import numpy as np
import pickle

class MatrixOperations:
    def __init__(self, matrix):
        self.matrix = matrix
        self.rows, self.cols = matrix.shape
        
    def find_row(self, first_num):
        max_val = np.max(self.matrix)
        min_val = np.min(self.matrix)
        found_row = -1

        for i in range(1, self.rows):  
            if first_num in self.matrix[i]:
                found_row = i
                break

        return (found_row + 1 if found_row != -1 else -1), max_val, min_val
       
    def matrix_addition(self, other):
        result = np.zeros((self.rows, self.cols), dtype=int)
        for i in range(self.rows):
            for j in range(self.cols):
                result[i][j] = self.matrix[i][j] + other.matrix[i][j]
        return result
        
    def matrix_multiplication(self, other):
        result = np.zeros((self.rows, other.cols), dtype=int)
        for i in range(self.rows):
            for j in range(other.cols):
                for k in range(self.cols):  # Common dimension
                    result[i][j] += self.matrix[i][k] * other.matrix[k][j]
        return result
        
    def save_to_file(self, filename, matrix):
        with open(filename, "w") as f:
            f.write("-------------------------------------------------------------------------------\n")
            for row in matrix:
                f.write(" ".join(map(str, row)) + "\n")
            f.write("-------------------------------------------------------------------------------\n")


if __name__ == "__main__":
    mat1 = np.loadtxt("matrix_1.txt", dtype=int)
    mat2 = np.loadtxt("matrix_2.txt", dtype=int)

    matrix1 = MatrixOperations(mat1)
    matrix2 = MatrixOperations(mat2)

    first_num = mat1[0, 0]
    row_idx_mat1, max_mat1, min_mat1 = matrix1.find_row(first_num)
    row_idx_mat2, max_mat2, min_mat2 = matrix2.find_row(first_num)
    
    with open("output_Q1_1.txt", "w") as f1, open("output_Q1_2.txt", "w") as f2:
        f1.write("-------------------------------------------------------------------------------\n")
        f1.write("Target value in matrix is shown in row {}\n".format(row_idx_mat1 if row_idx_mat1 != -1 else 'not shown'))
        f1.write("Maximum value is {}\n".format(max_mat1))
        f1.write("Minimum value is {}\n".format(min_mat1))
        f1.write("-------------------------------------------------------------------------------\n")


        f2.write("-------------------------------------------------------------------------------\n")
        f2.write("Target value in matrix is shown in row {}\n".format(row_idx_mat2 if row_idx_mat2 != -1 else 'not shown'))
        f2.write("Maximum value is {}\n".format(max_mat2))
        f2.write("Minimum value is {}\n".format(min_mat2))
        f2.write("-------------------------------------------------------------------------------\n")


    mat_add = matrix1.matrix_addition(matrix2)
    matrix1.save_to_file("output_Q2.txt", mat_add)

    mat_mul = matrix1.matrix_multiplication(matrix2)
    matrix1.save_to_file("output_Q3.txt", mat_mul)

    results = {
        'idx_row_mat_1': row_idx_mat1,
        'max_mat_1': max_mat1,
        'min_mat_1': min_mat1,
        'idx_row_mat_2': row_idx_mat2,
        'max_mat_2': max_mat2,
        'min_mat_2': min_mat2,
        'mat_add': mat_add,
        'mat_mul': mat_mul
    }
    
    with open("output_py.pickle", "wb") as f:
        pickle.dump(results, f)

    print("Results saved to output_py.pickle")
