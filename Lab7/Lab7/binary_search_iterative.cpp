#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

int binaryisearch(int arr[], int n, int target) {
    int left = 0;
    int right = n-1;

    while (left <= right){
       int mid = (left + right)/2;
       
       if (arr[mid] == target){
        return mid;
       }

       if(arr[mid] < target){
        left = mid + 1;
       }

       else{
        right = mid - 1;
       }
    }
    return - 1;
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
    
    int result = binaryisearch(arr, n, target);
    
    if (result == -1) {
        outputFile << "No Found" << endl;
    } else {
        outputFile << result << endl;
    }
    
    outputFile.close();
    delete[] arr; // Free allocated memory
    
    return 0;
}