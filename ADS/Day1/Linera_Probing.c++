#include <bits/stdc++.h>
using namespace std;

class HashTable
{
private:
    static const int TABLE_SIZE = 10;
    int table[TABLE_SIZE];

    int hashFunction(int key)
    {
        return (2 * key + 3) % TABLE_SIZE;
    }

public:
    HashTable()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            table[i] = -1; // Initialize all slots to -1 (indicating empty)
        }
    }

    void insert(int key)
    {
        int index = hashFunction(key);

        // Linear probing to find an empty slot
        int i = 0;
        while (table[(index + i) % TABLE_SIZE] != -1)
        {
            i = (i + 1) % TABLE_SIZE; // Increment i in a circular manner
        }

        table[(index + i) % TABLE_SIZE] = key; // Insert key into the empty slot
    }

    int findFirstFreeLocation(int key)
    {
        int index = hashFunction(key);

        // Linear probing to find the first free location
        int i = 0;
        while (table[(index + i) % TABLE_SIZE] != -1)
        {
            i = (i + 1) % TABLE_SIZE; // Increment i in a circular manner
        }

        return (index + i) % TABLE_SIZE;
    }

    void display()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            cout << "Bucket " << i << ": " << table[i] << endl;
        }
    }
};

int main()
{
    HashTable hashTable;
    int keys[] = {3, 2, 9, 6, 11, 13, 7, 12};
    int numKeys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < numKeys; ++i)
    {
        hashTable.insert(keys[i]);
    }

    hashTable.display();

    int userKey;
    cout << "Enter a key to find its first free location: ";
    cin >> userKey;

    int freeLocation = hashTable.findFirstFreeLocation(userKey);
    cout << "The first free location for key " << userKey << " is Bucket " << freeLocation << endl;
    hashTable.insert(userKey);
     hashTable.display();
    return 0;
}

// #include <iostream>

// class HashTable {
// private:
//     static const int TABLE_SIZE = 10;
//     int table[TABLE_SIZE];

//     int hashFunction(int key) {
//         return (2 * key + 3) % TABLE_SIZE;
//     }

// public:
//     HashTable() {
//         for (int i = 0; i < TABLE_SIZE; ++i) {
//             table[i] = -1;  // Initialize all slots to -1 (indicating empty)
//         }
//     }

//     void insert(int key) {
//         int index = hashFunction(key);

//         // Linear probing to find an empty slot
//         int i = 0;
//         while (table[(index + i) % TABLE_SIZE] != -1) {
//             i = (i + 1) % TABLE_SIZE;  // Increment i in a circular manner
//         }

//         table[(index + i) % TABLE_SIZE] = key;  // Insert key into the empty slot
//     }

//     void display() {
//         for (int i = 0; i < TABLE_SIZE; ++i) {
//             cout << "Bucket " << i << ": " << table[i] << endl;
//         }
//     }
// };

// int main() {
//     HashTable hashTable;
//     int keys[] = {3, 2, 9, 6, 11, 13, 7, 12};
//     int numKeys = sizeof(keys) / sizeof(keys[0]);

//     for (int i = 0; i < numKeys; ++i) {
//         hashTable.insert(keys[i]);
//     }

//     hashTable.display();

//     return 0;
// }
