
#include "encoding.h"
#include "mymap.h"
#include "pqueue.h"


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

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    Map<int, string> encodingMap;   // this is just a placeholder so it will compile
    return encodingMap;             // this is just a placeholder so it will compile
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
