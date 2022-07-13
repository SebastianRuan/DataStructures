//
// Created by Seb on 11-Jun-2022.
//
#include <string>
#include <iostream>
#include "HashMap.h"

using namespace std;

void HashMap::clear_table() {
    for (int i = 0; i < capacity; ++i) {
        arr[i] = pair<unsigned long long, string>(0,"");
    }
}

HashMap::HashMap():arr(new pair<unsigned long long, string> [113]), capacity(113), count(0) {
    clear_table();
}

HashMap::HashMap(int capacity):arr(new pair<unsigned long long, string>[capacity]), capacity(capacity), count(0) {
    clear_table();
}

// flatten converts value into a number which will be used to insert value into the hash map
unsigned long long HashMap::flatten(std::string value){
    unsigned long long key = 0;
    for (int i = 0; i < value.length(); ++i) {
        int charNum = value[i] - 31;
        key += charNum * (unsigned long long) pow(32, value.length()-i-1);
    }
    return key;
}

int HashMap::hash1(unsigned long long key){ return key % capacity;}
int HashMap::hash2(unsigned long long key){
    return floor(capacity * (double) (phi * key - floor(phi*key)));
}

int HashMap::cuckooHash(std::vector<int> indices, unsigned long long key, const string& value){
    auto newEntry = pair<unsigned long long, string>(key,value);
    int hashFn = 0;
    for (int i = 0; i < 2 * capacity; ++i) {
        int idx = indices[hashFn];
        if (arr[idx].first == 0){
            arr[idx] = newEntry;
            return 0;
        } else {
            auto tmp = arr[idx];
            arr[idx] = newEntry;
            newEntry = tmp;
            indices[0] = hash1(newEntry.first);
            indices[1] = hash2(newEntry.first);
        }
        hashFn = 1 - hashFn;
    }

    // temporarily place ousted entry at first open space
    for (int i = 0; i < capacity; ++i) {
        if(arr[i].first == 0){
            arr[i] = newEntry;
            break;
        }
    }
    return 1;
}


// get_indices calculates the two possible indices of data
vector<int> HashMap::get_indices(const string& data, unsigned long long& key){
    key = flatten(data);
    return vector<int>({hash1(key), hash2(key)});
}

void HashMap::insert(const string& data){
    ++count;
    unsigned long long key = 0;
    vector<int> indices = get_indices(data, key);

    if (cuckooHash(indices, key, data) || (count+1) / (double) capacity >= 0.25 ){
        std::pair<unsigned long long, std::string>* old_arr = arr;
        arr = new pair<unsigned long long, string> [113];
        capacity = capacity * 2;

        for (int i = 0; i < capacity / 2; ++i) {
            int h1 = hash1(old_arr[i].first);
            int h2 = hash2(old_arr[i].first);
            cuckooHash(vector<int>({h1, h2}),old_arr[i].first, old_arr[i].second);
        }
        delete[] old_arr;
    }
}

bool HashMap::contains(const std::string &data) {
    unsigned long long key = 0;
    vector<int> indices = get_indices(data, key);
    return data == arr[indices[0]].second || data == arr[indices[1]].second;
}

void HashMap::remove(const std::string &data) {
    unsigned long long key = 0;
    vector<int> indices = get_indices(data, key);

    if(data == arr[indices[0]].second){
        arr[indices[0]] = pair<unsigned long long, string>(0,"");
    } else if(data == arr[indices[1]].second){
        arr[indices[1]] = pair<unsigned long long, string>(0,"");
    }
}

HashMap::~HashMap(){
    delete[] arr;
}