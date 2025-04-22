#include <iostream>
#include <fstream>
using namespace std;


    void transform_arr(int* arr, int n) {
    for (int* ptr = arr; ptr < arr + n; ++ptr) {
        if (*ptr % 2 == 0) {
            *ptr *= 2;
        } 
        else {
            *ptr *= *ptr;
        }
    }
}
    
    void min_max(int *arr, int& min, int& max, int n){
        min = *arr;
        max = *arr;
        
        for (int* ptr = arr; ptr < arr + n; ++ptr){
            if (*ptr < min){
                min = *ptr;
            }
            if(*ptr > max){
                max = *ptr;
            }
        }
    }
    
    void prefix_sum(int *arr, int* psum, int n){
        *psum = *arr;
        for (int i = 1; i < n; i++){
            *(psum + i) = *(psum + i - 1) + *(arr + i);
        }
    }
    
    int main(){
        ifstream inputfile ("input.txt"); 
        
        int n;
        inputfile >> n;
        
        int* arr = new int[n];
        int* oriarr = new int[n];
        int* psum = new int[n];
        
        for (int i = 0; i < n; ++i) {
        inputfile >> *(arr + i);
        *(oriarr + i) = *(arr + i);
    }

    inputfile.close();

    transform_arr(arr, n);

    prefix_sum(arr, psum, n);

    int minval, maxval;
    min_max(arr, minval, maxval, n);
    
    ofstream outputfile("output_Q1.txt");

    outputfile << "Original Array: ";
    for (int* ptr = oriarr; ptr < oriarr + n; ++ptr) {
        outputfile << *ptr << " ";
    }

    outputfile << "\n\nModified Array:\n  - Doubled even numbers & Squared odd numbers: ";
    for (int* ptr = arr; ptr < arr + n; ++ptr) {
        outputfile << *ptr << " ";
    }

    outputfile << "\n\nMax Value: " << maxval;
    outputfile << "\nMin Value: " << minval;

    outputfile << "\n\nPrefix Sum Array: ";
    for (int* ptr = psum; ptr < psum + n; ++ptr) {
        outputfile << *ptr << " ";
    }

    outputfile.close();

    delete[] arr;
    delete[] oriarr;
    delete[] psum;

    return 0;
}