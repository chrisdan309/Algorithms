#include <iostream>

void shellSort(int *arr, int n){
    int i, j, k, temp;
    for(i = n / 2; i > 0; i = i/2){ // saltos
        for(j = i; j < n; j++){
            for(k = j - i; k >= 0; k = k - i){
                if(arr[k + i] >= arr[k]){
                    break;
                } else {
                    temp = arr[k];
                    arr[k] = arr[k + i];
                    arr[k + i] = temp;
                }
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
    shellSort(arr, 10);
    print(arr, 10);
    return 0;
}