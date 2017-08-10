//Assignment: Huffman Coding
//Name: Yuhao Dong
//Pair programmer: Dehao Tu
#include "mymap.h"
#include "vector.h"
using namespace std;

MyMap::MyMap() {
    nBuckets = 100; //ASCII including the extended ones, have total of 255 characters
    buckets = createBucketArray(nBuckets);
    nElems = 0;
}

MyMap::~MyMap() {
    for (int i=0; i < nBuckets; i++) {
        if (buckets[i] != nullptr) {
            delete buckets[i];
            buckets[i] = nullptr;
        }
    }
}

void MyMap::put(int key, int value) {
    key_val_pair* newK = new key_val_pair;
    newK->key = key;
    newK->value = value;
    newK->next = nullptr;
    //create a new node contains key(character) and value(count)

    int bucketKey = hashFunction(key) % nBuckets;

    if (buckets[bucketKey] != nullptr) {
        //if there's node/nodes in the bucket, add the new node to the linked list

        /* -this part of function looks for the nodes with the key matches the input key - */
        key_val_pair *temp = buckets[bucketKey];
        //temp is used to traverse the linked list in bucket

        while (temp != nullptr) {
            //if there's a key is already exist, replace the key's value with the new input value
            if (temp->key == key) {
                temp->value = value;
                return;
            }else {
                temp = temp->next;
            }
        }
        /* ------------------------------------------------------------------------------ */
        //if there's no exisiting key in the linked list matches the input key, add the new to the
        //front of the linked list
        newK->next = buckets[bucketKey];
        buckets[bucketKey] = newK;
    }else {
        //if the bucket is empty, put the new node right in
        buckets[bucketKey] = newK;
    }
    nElems ++;
}

int MyMap::get(int key) const {
    int bucketKey = hashFunction(key) % nBuckets;
    if (buckets[bucketKey] == nullptr) throw ("The key is not existed in the map yet!");
    //if is no key in the map that matches the key, throw exception
    else {
        key_val_pair *temp = buckets[bucketKey];
        //temp is used to traverse the linked list in bucket

        while (temp != nullptr) {
            if (temp->key == key) return temp->value;
            temp = temp->next;
        }
        throw ("The key is not existed in the map yet!");
    }
}

bool MyMap::containsKey(int key) {
    int bucketKey = hashFunction(key) % nBuckets;
    if (buckets[bucketKey] != nullptr) {
        key_val_pair *temp = buckets[bucketKey];
        while (temp != nullptr) {
            if (temp->key == key) return true;
            temp = temp->next;
        }
    }
    return false;
}

Vector<int> MyMap::keys() const {
     Vector<int> keys;
     for (int i = 0; i < nBuckets; i++) {
         key_val_pair *temp = buckets[i];
         while (temp != nullptr) {
             keys.add(temp->key);
             temp = temp->next;
         }
     }
     return keys;
}

int MyMap::size() {
    return nElems;
}

/**
 * STARTER CODE, DO NOT MODIFY
 */

// copy constructor
MyMap::MyMap(const MyMap &myMap) {
    // make a deep copy of the map
    nBuckets = myMap.nBuckets;

    buckets = createBucketArray(nBuckets);

    // walk through the old array and add all elements to this one
    Vector<int> keys = myMap.keys();
    for (int i=0; i < keys.size(); i++) {
        int key = keys[i];
        int value = myMap.get(key);
        put(key,value);
    }

}

// assignment overload
MyMap& MyMap::operator= (const MyMap &myMap) {
    // make a deep copy of the map

    // watch for self-assignment
    if (this == &myMap) {
        return *this;
    }

    // if data exists in the map, delete it
    for (int i=0; i < nBuckets; i++) {
        MyMap::key_val_pair* bucket = buckets[i];
        while (bucket != nullptr) {
            // walk the linked list and delete each node
            MyMap::key_val_pair* temp = bucket;
            bucket = bucket->next;
            delete temp;
        }
        buckets[i] = nullptr;
    }
    nElems = 0;
    // walk through the old array and add all elements to this one
    Vector<int> keys = myMap.keys();
    for (int i=0; i < keys.size(); i++) {
        int key = keys[i];
        int value = myMap.get(key);
        put(key,value);
    }

    // return the existing object so we can chain this operator
    return *this;
}

ostream &operator<<(ostream &out, MyMap &myMap) {
    out << "{";
    Vector<int> keys = myMap.keys();
    for (int i=0; i < keys.size(); i++) {
        int key = keys[i];
        int value = myMap.get(key);
        out << key << ":" << value;
        if (i < keys.size() - 1) { // print the comma after each pair except the last
            out << ", ";
        }
    }
    out << "}";
    return out;
}

istream &operator>>(istream &in, MyMap &myMap) {
    // assume the format {1:2, 3:4}
    bool done = false;
    in.get(); // get the first char, {
    int nextChar = in.get(); // get the first real character
    while (!done) {
        string nextInput;
        while (nextChar != ',' and nextChar != '}') {
                nextInput += nextChar;
                nextChar = in.get();
        }
        if (nextChar == ',') {
            // read the space as well
            in.get(); // should be a space
            nextChar = in.get(); // get the next character
        } else {
            done = true; // we have reached }
        }
        // at this point, nextInput should be in the form 1:2
        // (we should have two integers separated by a colon)
        // BUT, we might have an empty map (special case)
        if (nextInput != "") {
            vector<string> kvp = stringSplit(nextInput,":");
            myMap.put(stringToInteger(kvp[0]),stringToInteger(kvp[1]));
        }
    }
    return in;
}
/**
 * STARTER CODE, DO NOT MODIFY
 *
 * Given a number of buckets, creates a hashtable (array of linked list heads).
 *
 * @param nBuckets the number of buckets you want in the hashtable.
 * return an array of heads of linked lists of key_val_pairs
 */
MyMap::bucketArray MyMap::createBucketArray(int nBuckets) {
    bucketArray newBuckets = new key_val_pair*[nBuckets];
    for (int i = 0; i < nBuckets; i++) {
        newBuckets[i] = nullptr;
    }
    return newBuckets;
}

/**
 * STARTER CODE
 * The hash function for your HashMap implementation.
 * For an extension, you might want to improve this function.
 *
 * @param input - an integer to be hashed
 * return the hashed integer
 */
int MyMap::hashFunction(int input) const {
    // use unsigned integers for calculation
    // we are also using so-called "magic numbers"
    // see https://stackoverflow.com/a/12996028/561677 for details
    unsigned int temp = ((input >> 16) ^ input) * 0x45d9f3b;
    temp = ((temp >> 16) ^ temp) * 0x45d9f3b;
    temp = (temp >> 16) ^ temp;

    // convert back to positive signed int
    // (note: this ignores half the possible hashes!)
    int hash = (int) temp;
    if (hash < 0) {
        hash *= -1;
    }

    return hash;
}

/**
* @brief MyMap::sanityCheck
*
* Checks a map for internal consistency
*/
void MyMap::sanityCheck(){
  for(int i = 0; i < 1000; i++) {
      put(i,i);
  }
  for(int i = 0; i < 1000; i++) {

      if(!containsKey(i)) {
          string err = integerToString(i) + " should be a key in the map but cannot be found";
      }
      int val;

      try {
          val = get(i);
      } catch(string exception) {
          string err = "Unable to get value for " + integerToString(i);
          throw(err);
      }

      if (i != val) {
          string err = integerToString(i) + " should be mapped to " + integerToString(i) + " but is mapped to " + integerToString(val) + "instead";
          throw(err);
      }
  }
  cout << "Map seems ok" << endl;
}
