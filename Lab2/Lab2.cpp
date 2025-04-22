#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Matrix {
private:
    vector<vector<int>> mat;
    int rows, cols;

public:
    Matrix(int r, int c) : rows(r), cols(c), mat(r, vector<int>(c, 0)) {}

    void input_mat(const string &newfile) {
        ifstream theMat(newfile);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                theMat >> mat[i][j];
            }
        }
        theMat.close(); 
    }
    
    int get_first_element() const {
        return mat[0][0];
    }

    void find_row(int first_num, const string &newfile) {
        int foundRow = -1;
        int maxVal = mat[0][0];
        int minVal = mat[0][0];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (mat[i][j] > maxVal) {
                    maxVal = mat[i][j];
                }
                if (mat[i][j] < minVal) {
                    minVal = mat[i][j];
                }
                if (mat[i][j] == first_num && i != 0 && foundRow == -1) {
                    foundRow = i;
                }
            }
        }

        ofstream outfile(newfile); // ofstream to make the file
        outfile << "-------------------------------------------------------------------------------" << endl;
        if (foundRow != -1) {
            outfile << "Target value in matrix is shown in row " << (foundRow + 1) << endl;
        } else {
            outfile << "Target value in matrix is not shown" << endl;
        }
        outfile << endl << "Maximum value is " << maxVal << endl;
        outfile << "Minimum value is " << minVal << endl;
        outfile << "-------------------------------------------------------------------------------" << endl;
        outfile.close();
    }

    Matrix matrix_addition(const Matrix &next) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.mat[i][j] = mat[i][j] + next.mat[i][j];
            }
        }
        return result;
    }
    
    Matrix matrix_multiplication(const Matrix &next) {
        Matrix result(rows, next.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < next.cols; j++) {
                result.mat[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    result.mat[i][j] += mat[i][k] * next.mat[k][j];
                }
            }
        }
        return result;
    }

    void save(const string &newfile) {
        ofstream outfile(newfile);
        outfile << "-------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                outfile << mat[i][j] << " ";
            }
            outfile << endl;
        }
        outfile << endl << "-------------------------------------------------------------------------------" << endl;
        outfile.close();
    }
    
};

int main() {
    int r = 10, c = 10; // Matrix size
    Matrix mat1(r, c), mat2(r, c);
    
    mat1.input_mat("matrix_1.txt");
    mat2.input_mat("matrix_2.txt");
    
    int first_num = mat1.get_first_element();
    mat1.find_row(first_num, "output_Q1_1.txt");
    mat2.find_row(first_num, "output_Q1_2.txt");
    
    Matrix add_result = mat1.matrix_addition(mat2);
    add_result.save("output_Q2.txt");
    
    Matrix mult_result = mat1.matrix_multiplication(mat2);
    mult_result.save("output_Q3.txt");

    
    return 0;
}
