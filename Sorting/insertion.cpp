#include <iostream>
#include <time.h>
#include <stdlib.h> 

void insertionSort(int *arr, int n){
    int i, key, j;
    for(i = 1; i < n; i ++){
        key = arr[i];
        j = i - 1;
        while(j >= 0 && key < arr[j]){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


void print(int *arr, int n){
    for(int i = 0; i < n; i ++){
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}



int main(){
    srand(time(NULL));
    int *arr = new int(10);
    for(int i = 0; i < 10; i ++){
        arr[i] = rand() % 100;
    }
    print(arr, 10);
    insertionSort(arr, 10);
    print(arr, 10);
    return 0;
}