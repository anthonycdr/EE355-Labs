#include <iostream>
#include <fstream>
using namespace std;

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++){
        if (arr[j] <= pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(int arr[], int low, int high){
    if (low < high){
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
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
    
    quicksort(arr, 0, n - 1);
    
    ofstream outputFile("output_qs.txt");
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