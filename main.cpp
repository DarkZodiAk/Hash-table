#include<iostream>
#include<limits>
#include"table.h"

using namespace std;

struct Hasher {
    int operator()(const int &item, int capacity) const {
        return item % capacity;
    }
};
struct HasherProbe {
    int operator()(const int &item, int capacity) const {
        return item % capacity;
    }
};

void clearConsole(){
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int inputNumber(){
	int k;
	while(!(cin >> k)){
		cout << "Wrong number! Try again: ";
		clearConsole();
	}
	return k;
}

int main(){
    Hasher h1;
    HasherProbe h2;
    int emptyItem = INT_MIN, deletedItem = INT_MAX;

    HashTable<int, Hasher, HasherProbe> table(h1, h2, emptyItem, deletedItem);
    
    int k = -1, number;

    while(1){
        cout << "Choose operation:\n 1 - Add number\n 2 - Delete number\n 3 - Find number"
        "\n 4 - Clear table\n 5 - Size of table\n 6 - Full info about table\n 0 - Exit\n> ";
        k = inputNumber();
        system("cls");
        if(k == 0) break;
        switch(k) {
            case 1:
                cout << "Enter number to add: ";
                number = inputNumber();
                if(table.Add(number)){
                    cout << "Number was added to table\n\n";
                } else {
                    cout << "This number is already in table\n\n";
                }
                
                break;
            case 2:
                cout << "Enter number to delete: ";
                number = inputNumber();
                if(table.Delete(number)){
                    cout << "Number was deleted from table\n\n";
                } else {
                    cout << "Number is not in table\n\n";
                }
                
                break;
            case 3:
                cout << "Enter number to find: ";
                number = inputNumber();
                if(table.Contains(number)){
                    cout << "Number have found\n\n";
                } else {
                    cout << "Number have NOT found\n\n";
                }
                break;
            case 4:
                table.Clear();
                cout << "Table was cleared\n\n";
                break;
            case 5:
                cout << "Size is " << table.Size() << "\n\n";
                break;
            case 6:
                table.DebugInfo();
                break;
            default:
                cout << "Error. Wrong number.\n\n";
			    break;
        }
    }

    system("pause");
    return 0;
}