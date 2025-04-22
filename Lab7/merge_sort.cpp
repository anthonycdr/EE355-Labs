#include <iostream>
#include <fstream>
using namespace std;

void merge(int arr[], int left, int mid, int right){
    int ltemp = mid - left + 1;
    int rtemp = right - mid;

    int* larr = new int[ltemp];
    int* rarr = new int[rtemp];

    for (int i = 0; i < ltemp; i++){
        larr[i] = arr[left + i];
    }
    
    for(int j = 0; j < rtemp; j++){
        rarr[j] = arr[mid + 1 + j];
    }

    int i = 0;    
    int j = 0; 
    int k = left; 

    while (i < ltemp && j < rtemp){
        if(larr[i] <= rarr[j]){
            arr[k] = larr[i];
            i++;
        }
        else{
            arr[k] = rarr[j];
            j++;
        }
        k++;
    }
    
    while (i < ltemp){
        arr[k] = larr[i];
        i++;
        k++;
    }

    while (j < rtemp){
        arr[k] = rarr[j];
        j++;
        k++;
    }

    delete[] larr;
    delete[] rarr;
}

void mergesort(int arr[], int left, int right){
    if (left >= right){
        return;
    }

    int mid = (left + right)/2;

    mergesort(arr, left, mid);  
    mergesort(arr, mid + 1, right); 
    
    merge(arr, left, mid, right);
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
    
    mergesort(arr, 0, n - 1);
    
    ofstream outputFile("output_ms.txt");
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