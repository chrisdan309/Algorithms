#include <iostream>

void bubbleSort(int *arr, int n){
    int i, j;
    for(i = 0; i < n - 1; i ++){
        for(j = 0; j < n - i - 1; j ++){
            if (arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
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
    bubbleSort(arr, 10);
    print(arr, 10);
    return 0;
}