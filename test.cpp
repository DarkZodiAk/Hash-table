#include<iostream>
#include<chrono>
#include<random>
#include"table.h"

using namespace std;

struct Hasher {
    int operator()(const int &item, int capacity) const {
        return item % capacity;
    }
};
struct HasherProbe {
    int operator()(const int &item, int capacity) const {
        return capacity - 1 - (item % (capacity - 1));
    }
};

int randnum(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(min, max);

    return distribution(gen);
}

void generateKeys(HashTable<int, Hasher, HasherProbe> &table, int *arr, int n, int min, int max){
    int key, i = 0;
    
    while(i < n){
        key = randnum(min, max);
        if(table.Add(key)){ 
            arr[i] = key;
            i++;
        }
    }
}

void measureDeleteTime(HashTable<int, Hasher, HasherProbe> &table, int *arr, int size, int min, int max){
    chrono::duration<double, milli> total;
    int item;
    total = total.zero();

    for(int n = size/10; n < size + 1; n += size/10){
        generateKeys(table, arr, n, min, max);

        for(int i = 0; i < 25; i++){
            
            item = arr[randnum(0, n - 1)];

            auto start = chrono::high_resolution_clock::now();

            table.Delete(item);

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> duration = end - start;
            total += duration;
        }
        table.Clear();
        cout << "Delete item with size " << n << " took " << total.count() / 25 << " ms\n";
    }
}


#define N 1000000

int main(){
    Hasher h1;
    HasherProbe h2;
    int emptyItem = INT_MIN, deletedItem = INT_MAX;

    HashTable<int, Hasher, HasherProbe> table(h1, h2, emptyItem, deletedItem);

    int *keys = new int[N];

    measureDeleteTime(table, keys, N, 0, 10000000);

    system("pause");
    return 0;
}