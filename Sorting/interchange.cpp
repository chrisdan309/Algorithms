#include <iostream>

void interchangeSort(int *arr, int n){
    int i, j;
    for(i = 0; i < n - 1; i ++){
        for(j = i + 1; j < n; j ++){
            if(arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
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
    interchangeSort(arr, 10);
    print(arr, 10);           
}
