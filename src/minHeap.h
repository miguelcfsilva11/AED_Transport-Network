
#ifndef _MINHEAP_H_
#define _MINHEAP_H_

#include <vector>
#include <unordered_map>

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

using namespace std;

/**
 * Binary min-heap to represent integer keys of type K with values (priorities) of type V
 * @tparam K key type
 * @tparam V value type
 */
template <class K, class V>
class MinHeap {

    /**
     * Struct to store an element of the heap: a pair (key, value)
     */
    struct Node {
        K key;
        V value;
    };

    int size;                  // Number of elements in heap
    int maxSize;               // Maximum number of elements in heap
    vector<Node> a;            // The heap array
    unordered_map<K, int> pos; // maps a key into its position on the array a
    const K KEY_NOT_FOUND;

    /**
     * Function that makes a value go "up the tree" until it reaches its position
     * @param i a position
     */
    void upHeap(int i);

    /**
     * Function thar makes a value go "down the tree" until it reaches its position
     * @param i a position
     */
    void downHeap(int i);

    /**
     * Function that swaps two positions of the heap (update their positions)
     * @param i1 a position
     * @param i2 other position
     */
    void swap(int i1, int i2);

public:

    /**
     * Constructor of the class MinHeap
     * @param n max number of pairs (K,V)
     * @param notFound value to be returned when empty
     */
    MinHeap(int n, const K& notFound);

    /**
     * Function that returns the number of elements in the heap
     * @return returns the number of elements in the heap
     */
    int getSize();

    /**
     * Function that returns true if the heap has the key, false otherwise
     * @param key the key to be searched
     * @return returns true if the heap has the key, false otherwise
     */
    bool hasKey(const K& key);

    /**
     * Function that inserts (key, value) on the heap
     * @param key the key
     * @param value the value
     */
    void insert(const K& key, const V& value);

    /**
     * Function that decreases the value of the key
     * @param key the key whose value will be decreased
     * @param value the new value
     */
    void decreaseKey(const K& key, const V& value);

    /**
     * Function that removes and returns the key with the smaller value
     * @return returns the key with the smaller value
     */
    K removeMin();
};




template <class K, class V>
void MinHeap<K,V>::upHeap(int i) {
    while (i>1 && a[i].value < a[PARENT(i)].value) { // while pos smaller than parent, keep swapping to upper position
        swap(i, PARENT(i));
        i = PARENT(i);
    }
}


template <class K, class V>
void MinHeap<K,V>::downHeap(int i) {
    while (LEFT(i) <= size) { // while within heap limits
        int j = LEFT(i);
        if (RIGHT(i)<=size && a[RIGHT(i)].value < a[j].value) j = RIGHT(i); // choose smaller child
        if (a[i].value < a[j].value) break;   // node already smaller than children, stop
        swap(i, j);                    // otherwise, swap with smaller child
        i = j;
    }
}


template <class K, class V>
void MinHeap<K,V>::swap(int i1, int i2) {
    Node tmp = a[i1]; a[i1] = a[i2]; a[i2] = tmp;
    pos[a[i1].key] = i1;
    pos[a[i2].key] = i2;
}



template <class K, class V>
MinHeap<K,V>::MinHeap(int n, const K& notFound) : KEY_NOT_FOUND(notFound), size(0), maxSize(n), a(n+1) {
}


template <class K, class V>
int MinHeap<K,V>::getSize() {
    return size;
}


template <class K, class V>
bool MinHeap<K, V>::hasKey(const K& key) {
    return pos.find(key) != pos.end();
}


template <class K, class V>
void MinHeap<K,V>::insert(const K& key, const V& value) {
    if (size == maxSize) return; // heap is full, do nothing
    if (hasKey(key)) return;     // key already exists, do nothing
    a[++size] = {key, value};
    pos[key] = size;
    upHeap(size);
}


template <class K, class V>
void MinHeap<K,V>::decreaseKey(const K& key, const V& value) {
    if (!hasKey(key)) return; // key does not exist, do nothing
    int i = pos[key];
    if (value > a[i].value) return; // value would increase, do nothing
    a[i].value = value;
    upHeap(i);
}


template <class K, class V>
K MinHeap<K,V>::removeMin() {
    if (size == 0) return KEY_NOT_FOUND;
    K min = a[1].key;
    pos.erase(min);
    a[1] = a[size--];
    downHeap(1);
    return min;
}

#endif
