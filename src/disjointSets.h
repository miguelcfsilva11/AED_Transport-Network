
#ifndef _DISJOINTSETS_H_
#define _DISJOINTSETS_H_

#include <unordered_map>

/**
 * Class to store information about disjoint sets
 * @tparam T a template type
 */
template <class T>
class DisjointSets {

    /**
     * Struct to store information about nodes
     */
    struct Node {
        T parent;
        int myrank; // to use on union by rank
    };

    unordered_map<T, Node> a;

public:

    /**
     * Function to create a set with a single element x
     * @param x the element
     */
    void makeSet(const T& x);

    /**
     * Function that finds the representative of the set of element x
     * @param x the element
     * @return returns the representative of the set of element x
     */
    T find(const T& x);

    /**
     * Function to merge the sets of elements x and y
     * @param x one of the elements
     * @param y one of the elements
     */
    void unite(const T& x, const T& y);

};



template <class T>
void DisjointSets<T>::makeSet(const T& x) {
    a[x].parent = x;
}

template <class T>
T DisjointSets<T>::find(const T& x) {
    if (a[x].parent == x) return x;
    else return find(a[x].parent);
}

template <class T>
void DisjointSets<T>::unite(const T& x, const T& y) {
    T xRoot = find(x);
    T yRoot = find(y);
    a[yRoot].parent = xRoot;
}

#endif
