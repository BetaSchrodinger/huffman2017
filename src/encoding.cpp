#include "encoding.h"
#include "mymap.h"
#include "pqueue.h"
#include "filelib.h"
void decodeDataHelper(ibitstream &input, HuffmanNode *encodingTree, ostream &output, HuffmanNode *root);

MyMap buildFrequencyTable(istream& input) {
    MyMap freqTable;
    int character = input.get();
    while (!input.eof()) {
        //read the file til the end
        if (!freqTable.containsKey(character)) {
            //if the character is not in the map, put it in the map and set the count to 1
            freqTable.put(character, 1);
            character = input.get();
        }else {
            //if the charcter is in the map already, take out the count and plus 1 and put it back
            int count = freqTable.get(character);
            count += 1;
            freqTable.put(character, count);
            character = input.get();
        }
    }
    //now we have to deal with EOF
    freqTable.put(256, 1);
    return freqTable;
}

HuffmanNode* buildEncodingTree(const MyMap& freqTable) {
    PriorityQueue<HuffmanNode*> freqList;
    Vector<int>keys = freqTable.keys();
    for (int key:keys) {
        HuffmanNode *charNode = new HuffmanNode;
        charNode->character = key;
        charNode->count = freqTable.get(key);
        freqList.enqueue(charNode, charNode->count);
    }
    //now we have a priorityqueue with nodes(storing the char) sorted from the least frequent to the most frequent
    while (!(freqList.size() == 1 && freqList.peek()->character == NOT_A_CHAR)) {
        //if the queue has not only the root, create a new node and give it 1 or 2 branches
        HuffmanNode* curr = new HuffmanNode;
        curr->zero = freqList.dequeue();
        //the new node may have only one branch if there's only one character in the queue
        if (freqList.size() > 0) {curr->one = freqList.dequeue();}

        curr->count = curr->zero->count + curr->one->count; //the priority of the new node is the sum of its branches
        freqList.enqueue(curr, curr->count); //enqueue the new node
    }
    return freqList.dequeue();
}

void buildEncodingMap(Map<int, string> &encodingMap, HuffmanNode* temp, string value) {
    //a helper function to recursively traverse the encodingTree
    if (temp->zero == nullptr && temp->one == nullptr) {
        //base case: if the temp is pointing to a leaf, map the leaf
        encodingMap[temp->character] = value;
        return;

    }else {
        if (temp->zero != nullptr) {
            buildEncodingMap(encodingMap, temp->zero, value + "0");
            //add 0 every time traverse down the left branches
        }
        if (temp->one != nullptr) {
            buildEncodingMap(encodingMap, temp->one, value + "1");
            //add 0 every time traverse down the right branches
        }
    }
    return;
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    HuffmanNode* temp = encodingTree;
    string value = "";
    //initiate value for the helper function
    buildEncodingMap(encodingMap, temp, value);//helper function
    return encodingMap;
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    int currChar = input.get();
    while (!input.eof()) {
        for (char bit: encodingMap[currChar]) {
            //traverse through the
            if (bit == '0') {
                output.writeBit(0);
            }else if (bit == '1') {
                output.writeBit(1);
            }
        }
        currChar = input.get();
    }
    //deal with EOF
    for (char bit: encodingMap[256]) {
        if (bit == '0') {
            output.writeBit(0);
        }else if (bit == '1') {
            output.writeBit(1);
        }
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    HuffmanNode* root = encodingTree;
    decodeDataHelper(input, encodingTree, output, root);
}

void decodeDataHelper(ibitstream& input, HuffmanNode* encodingTree, ostream& output, HuffmanNode* root) {
    if (encodingTree->character == NOT_A_CHAR) {
        int n = input.readBit();
        if (n == -1) {
            return;
        } else if (n == 0) {
               decodeDataHelper(input, encodingTree->zero, output, root);
        } else {
               decodeDataHelper(input, encodingTree->one, output, root);
        }
    } else {
        if (encodingTree->character == PSEUDO_EOF) {
            return;
        }else {
        output.put(encodingTree->character);
        decodeDataHelper(input, root, output, root);
        }
    }
}
void compress(istream& input, obitstream& output) {
    MyMap freqTable = buildFrequencyTable(input);
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    Map<int, string> encodingMap = buildEncodingMap(encodingTree);
    //now we have a map of every character to it's humman code
    rewindStream(input);
    output << freqTable;
    encodeData(input, encodingMap, output);
}

void decompress(ibitstream& input, ostream& output) {
    MyMap freqTable;
    input >> freqTable;
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    decodeData(input, encodingTree, output);
}

void freeTree(HuffmanNode* node) {
    //give back the memory held by the encodingTree
    if (node != nullptr) return;
        freeTree(node->zero);
        freeTree(node->one);
        delete node;
        node = nullptr;
}
