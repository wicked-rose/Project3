//
// Created by Kyle on 7/27/2020.
//

#ifndef PROJECT3_ALPHABETTREE_H
#define PROJECT3_ALPHABETTREE_H

#include <string>
#include <iostream>
#include "AlphabetNode.h"

using namespace _AlphabetNode;
using namespace std;

class AlphabetTree {
private:
    AlphabetNode* topNode;

public:
    AlphabetTree();
    void addWord(string word); // Adds a word into the tree, returns the word's new count.
    int getCount(string word);
    void printWords();
};


#endif //PROJECT3_ALPHABETTREE_H