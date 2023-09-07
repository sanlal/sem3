#include<bits/stdc++.h>
using namespace std;
class HashTable {
private:
    static const int TABLE_SIZE = 10;  // Define the size of the hash table
    list<int> table[TABLE_SIZE];  // Array of linked lists as buckets

    // Hash function: h(k) = (2k + 3) % TABLE_SIZE
    int hashFunction(int key) {
        return (2 * key + 3) % TABLE_SIZE;
    }

public:
    // Method to insert a key into the hash table
    void insert(int key) {
        int index = hashFunction(key);  // Get the index (bucket) for the key
        table[index].push_back(key);    // Add the key to the linked list at the index
    }

    // Method to display the contents of the hash table
    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "Bucket " << i << ": ";
            for (const auto& key : table[i]) {
                cout << key << " ";  // Print each key in the linked list
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable hashTable;  // Create an instance of the HashTable class
    int keys[] = {3, 2, 9, 6, 11, 13, 7, 12};  // Array of keys to insert
    int numKeys = sizeof(keys) / sizeof(keys[0]);  // Calculate the number of keys

    // Insert each key into the hash table
    for (int i = 0; i < numKeys; ++i) {
        hashTable.insert(keys[i]);
    }

    // Display the contents of the hash table
    hashTable.display();

    return 0;  // Exit the program
}
