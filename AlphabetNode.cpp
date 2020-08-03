//
// Created by Kyle on 7/27/2020.
//

#include <iostream>
#include <cstring>
#include "AlphabetNode.h"
using namespace _AlphabetNode;
using namespace std;

// Default constructor
AlphabetNode::AlphabetNode() : letter(0){
    count = 0;
    subletters = map<char, AlphabetNode>();
    parent = nullptr;
}

// Standard Constructor
AlphabetNode::AlphabetNode(char letter, AlphabetNode* parent) : letter(letter){
    this->parent = parent;
    count = 0;
    subletters = map<char, AlphabetNode>();
}

//Copy Constructor
AlphabetNode::AlphabetNode(AlphabetNode *pNode) : letter(pNode->getLetter()){
    this->count = pNode->count;
    this->parent = pNode->parent;
    this->subletters = pNode->subletters;
}

AlphabetNode::~AlphabetNode() {
    this->parent->delSubletter(this->letter);
}

unsigned int AlphabetNode::getCount(){
    return count;
}

// Return the pointer to the subletter
AlphabetNode* AlphabetNode::getSubletter(char subletter){
    if(subletters.count(subletter) == 0)
        return nullptr;
    return &subletters[subletter];
}

// Creates subletter node if one doesn't already exist, always returns a reference to the requested AlphabetNode
AlphabetNode *AlphabetNode::addSubletter(char subletter) {
    if(subletters.count(subletter) == 0)
        subletters[subletter] = new AlphabetNode(subletter, this);
    return &subletters[subletter];
}

void AlphabetNode::delSubletter(char subletter) {
    subletters.erase(subletter);

    // Check if there is a reason to keep this node
    if(count > 0)
        return;
    else if(getSubletters()->empty()){
        delete this;
    }
}

char AlphabetNode::getLetter() {
    return letter;
}

void AlphabetNode::incCount(){
    count++;
}

// Decrements the count and deletes the node if count gets to 0 and there are no subletters
void AlphabetNode::decCount() {
    if(count-- > 0)
        return;
    else if(getSubletters()->empty()){
        delete this;
    }
}


// Recursively print every word in the tree below it
void AlphabetNode::recursivePrint(char* prefix){
    if(letter == 0)
        return;

    unsigned int count = getCount();
    if(count != 0)
        cout << count << " occurrence(s) of the word " << prefix << letter << endl;

    if(subletters.empty())
        return;

    for(auto iter = subletters.begin(); iter != subletters.end(); iter++){
        char * temp;
        if (letter != -1){
            strcpy(temp, prefix);
            strcat(temp, &letter);
        }
        iter->second.recursivePrint(temp);
    }
}

map<char, AlphabetNode>* AlphabetNode::getSubletters() {
    return &subletters;
}

// Prepends this->letter to the outString
void AlphabetNode::selfToAncestorsString(string* outString) {
    if (letter == -1 || letter == 0)
        return;
    outString->insert(0, 1, letter);
    parent->selfToAncestorsString(outString);
}

// Returns the Root-to-Self string, aka a word in correct order
string AlphabetNode::getRootToSelfString(){
    string outString;
    selfToAncestorsString(&outString);
    return outString;
}