//
// Created by Seb on 11-Jun-2022.
//
#include <iostream>
#include <sstream>
#include "HashMap.h"

using namespace std;

int main(){
    HashMap hmap = HashMap(10);
    string line;
    string cmd;

    while(getline(cin, line)){
        istringstream line_stream{line};
        line_stream >> cmd;

        if (cmd == "a") {                                                             // add
            string data;
            line_stream >> data;
            hmap.insert(data);
        } else if (cmd == "r") {                                                      // remove
            string data;
            line_stream >> data;
            hmap.remove(data);
        } else if (cmd == "f"){                                                       // find
            string data;
            line_stream >> data;
            if (hmap.contains(data)){
                cout << "t" << endl;
            } else {
                cout << "f" << endl;
            }
        } else if (cmd == "q"){
            break;
        }
    }
}