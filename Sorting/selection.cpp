#include <iostream>

void selectionSort(int *arr, int n){
    int i, j, min;
    for(i = 0; i < n - 1; i ++){
        min = i;
        for(j = i + 1; j < n; j ++){
            if(arr[j] < arr[min]){
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

void print(int *arr, int n){
    for(int i = 0; i < n; i ++){
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main(){
    int *arr = new int(10);
    for(int i = 0; i < 10; i ++){
        arr[i] = rand() % 100;
    }
    print(arr, 10);
    selectionSort(arr, 10);
    print(arr, 10);
    return 0;
}