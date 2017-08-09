// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "mymap.h"
#include "bitstream.h"

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
    // TODO: implement this function
    return NULL;   // this is just a placeholder so it will compile
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
