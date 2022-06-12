//
// Created by Seb on 11-Jun-2022.
//
#include <string>
#include "HashMap.h"

HashMap::HashMap():arr(new std::string [113]), capacity(113), count(0) {}

HashMap::~HashMap(){
    delete[] arr;
}