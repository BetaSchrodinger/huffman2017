#include "encoding.h"
#include "mymap.h"
#include "bitstream.h"
#include "pqueue.h"

MyMap buildFrequencyTable(istream& input) {
    MyMap frequencyTable;
    int f [257] = {};
    int c = input.get();
    while (c != -1) {
        f[c] += 1;
    }
    for (int i = 0; i < 257; i ++) {
        frequencyTable.put(i, f[i]);
    }
    frequencyTable.put(257, 1);
    return frequencyTable;
}

HuffmanNode* buildEncodingTree(const MyMap& freqTable) {
    PriorityQueue<HuffmanNode*> freqList;
    Vector<int>keys = freqTable.keys();
    for (int key:keys) {
        HuffmanNode *charNode = new HuffmanNode;
        charNode->character = key;
        charNode->count = freqTable.get(key);
        freqList.enqueue(charNode, freqTable.get(key));
    }
    //now we have a priorityqueue with nodes(storing the char) sorted from the least frequent to the most frequent
    while (!(freqList.size() == 1 && freqList.peek()->character == NOT_A_CHAR)) {
        //if the queue has not onl
        HuffmanNode* curr;
        curr->zero = freqList.dequeue();
        curr->one = freqList.dequeue();
        freqList.enqueue(curr, curr->count);
    }
    return freqList.dequeue();
}

Map<int, string> buildEncodingMap(Map<int, string> &encodingMap, HuffmanNode*temp, string value) {
    if (temp->character == PSEUDO_EOF) {
        return encodingMap;
    }
    else {
        if (temp->character != NOT_A_CHAR) {
            encodingMap.add((int)(temp->character), value);
        }
        if (temp->zero->zero != nullptr) {
            buildEncodingMap(encodingMap, temp->zero, value + "0");
        }
        if (temp->one->zero != nullptr) {
            buildEncodingMap(encodingMap, temp->one, value + "1");
        }
        else {
            return encodingMap;
        }
    }
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    HuffmanNode* temp = encodingTree;
    string value = "";
    encodingMap = buildEncodingMap(encodingMap, temp, value);
    return encodingMap;
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
