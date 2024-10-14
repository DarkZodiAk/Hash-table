#include<vector>
#include<iostream>

#define MIN_CAPACITY 8
#define MAX_RATIO 0.75
#define MIN_RATIO 0.25

template <class T, class H1, class H2>
class HashTable{
    private:
        std::vector<T> table;
        int size;
        int capacity;
        T deletedItem;
        T emptyItem;

        H1 hasher;
        H2 hasherProbe;

        void resize(int new_capacity){
            int oldCapacity = capacity;
            size = 0;
            capacity = new_capacity;

            std::vector<T> oldTable(new_capacity, emptyItem);

            std::swap(oldTable, table);

            for(int i = 0; i < oldCapacity; i++){
                if(oldTable[i] != deletedItem && oldTable[i] != emptyItem){
                    Add(oldTable[i]);
                }
            }
        }

    public:
        HashTable(const H1& hasher, const H2& hasherProbe, const T& emptyItem, const T& deletedItem) :
            table(MIN_CAPACITY, emptyItem),
            capacity(MIN_CAPACITY),
            emptyItem(emptyItem),
            deletedItem(deletedItem),
            hasher(hasher),
            hasherProbe(hasherProbe),
            size(0) {}
        
        bool Add(const T& item){
            int h1 = hasher(item, capacity);

            if (table[h1] == emptyItem || table[h1] == deletedItem) {
                table[h1] = item;
                size++;
                if (size / (double)capacity >= MAX_RATIO) {
                    resize(capacity * 2);
                }
                return true;
            }
            if (table[h1] == item) {
                return false;
            }
            
            int h2 = hasherProbe(item, capacity);
            for (int i = 1; i != capacity; i++) {
                h1 = (h1 + h2) % capacity;
                if (table[h1] == item) {
                    return false;
                }
                if (table[h1] == emptyItem || table[h1] == deletedItem) {
                    table[h1] = item;
                    size++;
                    if (size / (double)capacity >= MAX_RATIO) {
                        resize(capacity * 2);
                    }
                    return true;
                }
            }
            return false;
        }
        bool Contains(const T& item) const {
            int h1 = hasher(item, capacity);

            if(table[h1] == item){
                return true;
            }

            if(table[h1] == emptyItem){
                return false;
            }

            int h2 = hasherProbe(item, capacity);
            int i = 1;

            while(i < capacity && table[h1] != emptyItem){
                h1 = (h1 + h2) % capacity;
                if (table[h1] == item && table[h1] != deletedItem)
                    return true;
                i++;
            } 

            return false;
        }
        bool Delete(const T& item){
            int h1 = hasher(item, capacity);

            if (table[h1] == item) {
                size--;
                table[h1] = deletedItem;
                if(size / (double)capacity <= MIN_RATIO && capacity > MIN_CAPACITY){
                    resize(capacity / 2);
                }
                return true;
            }
            if(table[h1] == emptyItem){
                return false;
            }

            int h2 = hasherProbe(item, capacity);
            for (int i = 1; i != capacity; i++) {
                h1 = (h1 + h2) % capacity;
                if (table[h1] == item) {
                    table[h1] = deletedItem;
                    size--;
                    if(size / (double)capacity <= MIN_RATIO && capacity > MIN_CAPACITY){
                        resize(capacity / 2);
                    }
                    return true;
                }
                if (table[h1] == emptyItem) {
                    return false;
                }
            }
            return false;
        }
        int Size() const { return size; }
        void Clear(){
            capacity = MIN_CAPACITY;
            table.resize(MIN_CAPACITY);
            table.clear();
            for(int i = 0; i < capacity; i++){
                table[i] = emptyItem;
            }
            size = 0;
        }

        void DebugInfo() const {
            std::cout << "capacity = " << capacity << "\n";
            std::cout << "size = " << size << "\n";
            std::cout << "current ratio = " << size / (double)capacity << "\n";
            std::cout << "table structure:\n";
            for(int i = 0; i < capacity; i++){
                if(table[i] == emptyItem) {
                    std::cout << "0 ";
                    continue;
                }
                if(table[i] == deletedItem) {
                    std::cout << "D ";
                    continue;
                }
                std::cout << "I ";
            }
            std::cout << "\n\n";
        }
};