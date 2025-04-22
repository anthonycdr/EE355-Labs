#include <iostream>
#include <fstream>
#include <time.h> 

using namespace std;

void allocate_matrix(int** &M, int size) {
    M = new int*[size];
    for (int i = 0; i < size; i++)
        M[i] = new int[size]();
}

void free_matrix(int** &M, int size) {
    for (int i = 0; i < size; i++)
        delete[] M[i];
    delete[] M;
}

int next_power_of_2(int n) {
    int power = 1;
    while (power < n) power *= 2;
    return power;
}

void pad_matrix(int** &M, int old_size, int new_size) {
    int** padded;
    allocate_matrix(padded, new_size);
    for (int i = 0; i < old_size; i++)
        for (int j = 0; j < old_size; j++)
            padded[i][j] = M[i][j];

    free_matrix(M, old_size);
    M = padded;
}

void read_file(const char* filename, int** &A, int** &B, int &size) {
    ifstream file(filename);
    file >> size;

    int padded_size = next_power_of_2(size);
    allocate_matrix(A, padded_size);
    allocate_matrix(B, padded_size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            file >> A[i][j];

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            file >> B[i][j];

    file.close();
    
    pad_matrix(A, size, padded_size);
    pad_matrix(B, size, padded_size);
    size = padded_size;
}

void write_file(const char* filename, int** M, int original_size) {
    ofstream file(filename);
    for (int i = 0; i < original_size; i++) {
        for (int j = 0; j < original_size; j++)
            file << M[i][j] << " ";
        file << endl;
    }
    file.close();
}

void multiply_dc(int** A, int** B, int** &C, int size) {
    allocate_matrix(C, size);
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mid = size / 2;
    int **A11, **A12, **A21, **A22;
    int **B11, **B12, **B21, **B22;
    int **C11, **C12, **C21, **C22;
    int **temp1, **temp2;

    allocate_matrix(A11, mid);
    allocate_matrix(A12, mid);
    allocate_matrix(A21, mid);
    allocate_matrix(A22, mid);
    allocate_matrix(B11, mid);
    allocate_matrix(B12, mid);
    allocate_matrix(B21, mid);
    allocate_matrix(B22, mid);
    allocate_matrix(C11, mid);
    allocate_matrix(C12, mid);
    allocate_matrix(C21, mid);
    allocate_matrix(C22, mid);
    allocate_matrix(temp1, mid);
    allocate_matrix(temp2, mid);

    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    multiply_dc(A11, B11, temp1, mid);
    multiply_dc(A12, B21, temp2, mid);
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++)
            C11[i][j] = temp1[i][j] + temp2[i][j];

    multiply_dc(A11, B12, temp1, mid);
    multiply_dc(A12, B22, temp2, mid);
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++)
            C12[i][j] = temp1[i][j] + temp2[i][j];

    multiply_dc(A21, B11, temp1, mid);
    multiply_dc(A22, B21, temp2, mid);
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++)
            C21[i][j] = temp1[i][j] + temp2[i][j];

    multiply_dc(A21, B12, temp1, mid);
    multiply_dc(A22, B22, temp2, mid);
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++)
            C22[i][j] = temp1[i][j] + temp2[i][j];

    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }

    free_matrix(A11, mid);
    free_matrix(A12, mid);
    free_matrix(A21, mid);
    free_matrix(A22, mid);
    free_matrix(B11, mid);
    free_matrix(B12, mid);
    free_matrix(B21, mid);
    free_matrix(B22, mid);
    free_matrix(C11, mid);
    free_matrix(C12, mid);
    free_matrix(C21, mid);
    free_matrix(C22, mid);
    free_matrix(temp1, mid);
    free_matrix(temp2, mid);
}

int main() {
    int **A, **B, **C1, **C2, size;
    read_file("input.txt", A, B, size);

    time_t start1, end1;
    start1 = clock();
    multiply_dc(A, B, C1, size);
    end1 = clock();
    int time_dc = end1 - start1;

    write_file("output_m1.txt", C1, 3);

    time_t start2, end2;
    start2 = clock();
    multiply_dc(A, B, C2, size);
    end2 = clock();
    int time_strassen = end2 - start2;

    write_file("output_m2.txt", C2, 3);

    ofstream output_q3("output_q3.txt");
    output_q3 << time_dc << " " << time_strassen;
    output_q3.close();

    cout << "Results saved to output_m1.txt, output_m2.txt, and output_q3.txt" << endl;
    return 0;
}
