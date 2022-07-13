//
// Created by Seb on 11-Jun-2022.
//
#ifndef DATASTRUCTURES_HASHMAP_H
#define DATASTRUCTURES_HASHMAP_H
#include <string>
#include <vector>
#include <cmath>


class HashMap{
    /*
     * HashMap stores strings such that search and delete run in O(1) time.
     * Insert's run time depends on the load factor of the table which is
     * smaller than 1/4.
     */

    std::pair<unsigned long long, std::string>* arr;
    int capacity;
    int count;
    const long double phi = (sqrt(5.0)-1.0)/2.0;

    unsigned long long flatten(std::string value);
    int hash1(unsigned long long key);
    int hash2(unsigned long long key);
    std::vector<int> get_indices(const std::string& data, unsigned long long& key);
    int cuckooHash(std::vector<int> indices, unsigned long long key, const std::string& value);
    void clear_table();

public:
    /*
     * HashMap creates a table with 113 entries by default
     * HashMap(capacity) creates a table with a specified capacity
     * insert(data) adds a string to the hashtable
     * contains(data) determines if data is in the hashtable
     */
    HashMap();
    HashMap(int capacity);
    void insert(const std::string& data);
    bool contains(const std::string& data);
    ~HashMap();
};


#endif //DATASTRUCTURES_HASHMAP_H
