#include <iostream>
#include <fstream>
using namespace std;

void bubblesort(int arr[], int n) {
    bool swap;
    for (int i = 0; i < n - 1; i++) {
        swap = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swap = true;
            }
        }
        if (!swap)
            break;
    }
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open input file" << endl;
        return 1;
    }
    
    int n;
    inputFile >> n;
    
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        inputFile >> arr[i];
    }
    
    inputFile.close();
    
    bubblesort(arr, n);
    
    ofstream outputFile("output_bubble.txt");
    if (!outputFile) {
        cerr << "Unable to create output file" << endl;
        delete[] arr;
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        outputFile << arr[i];
        if (i < n - 1) {
            outputFile << " ";
        }
    }
    outputFile << endl;
    
    outputFile.close();
    delete[] arr;
    
    return 0;
}