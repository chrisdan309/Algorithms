#include <iostream>

void quickSort(int *arr, int left, int right){
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];
    while(i <= j){
        while(arr[i] < pivot){
            i++;
        }
        while(arr[j] > pivot){
            j--;
        }
        if(i <= j){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    if(left < j){
        quickSort(arr, left, j);
    }
    if(i < right){
        quickSort(arr, i, right);
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
    quickSort(arr, 0, 9);
    print(arr, 10);
    return 0;
}