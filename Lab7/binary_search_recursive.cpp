#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

int binaryrsearch(int arr[], int low, int high, int target) {
    if (low > high) {
        return -1;
    }

    int mid = (low + high) / 2;

    if (arr[mid] == target) {
        return mid;
    }

    if (arr[mid] < target) {
        return binaryrsearch(arr, mid + 1, high, target);
    }

    // If arr[mid] > target
    return binaryrsearch(arr, low, mid - 1, target);
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    ofstream outputFile("output_bs.txt");
    if (!outputFile) {
        cerr << "Unable to create output file" << endl;
        return 1;
    }
    
    int n;
    inputFile >> n;
    
    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        inputFile >> arr[i];
    }
    
    int target;
    inputFile >> target;
    
    inputFile.close();
    
    sort(arr, arr + n); // Ensure the array is sorted
    
    int result = binaryrsearch(arr, 0, n - 1, target);
    
    if (result == -1) {
        outputFile << "No Found" << endl;
    } else {
        outputFile << result << endl;
    }
    
    outputFile.close();
    delete[] arr; // Free allocated memory
    
    return 0;
}