#pragma once 

#include <vector>
namespace cs225_fp {
class MinHeap {
    private:
    struct MinHeapNode {
        MinHeapNode(void) : v(0), dist(0) {};
        // ordered by key (which is the distance from src node for our specific use case)
        MinHeapNode(size_t key, double value) : v(key), dist(value) {}
        size_t v;    // Key
        double dist; // Value 
    };
    public:
    MinHeap(void);
    MinHeap(const std::vector<double>& shortest_dist_arr);

    void updateKey(size_t key, double new_value);
    std::pair<size_t, double> top(void) const;
    void pop(void);
    bool empty(void);
    bool hasKey(size_t v);

    private:
    std::vector<MinHeapNode> elems_;

    // heap position vector used to keep track of index positions of the graph vertices in the MinHeap
    std::vector<size_t> heap_pos_;

    // private helper functions
    /**
     * Helper function that return the index that points to the root node in 
     * heap util vector implementation.
     */
    size_t root() const;
    
    /**
     * Helper function that returns the index of the left child of a
     * node in the heap. Required for grading purposes! (And it should
     * be useful to you as well).
     *
     * @param currentIdx The index of the current node.
     * @return The index of the left child of the current node.
     */
    size_t leftChild(size_t currentIdx) const;

    /**
     * Helper function that returns the index of the right child of a
     * node in the heap. Required for grading purposes! (And it should
     * be useful to you as well).
     *
     * @param currentIdx The index of the current node.
     * @return The index of the right child of the current node.
     */
    size_t rightChild(size_t currentIdx) const;

    /**
     * Helper function that returns the index of the parent of a node
     * in the heap.
     *
     * @param currentIdx The index of the current node.
     * @return The index of the parent of the current node.
     */
    size_t parent(size_t currentIdx) const;

    /**
     * Helper function that determines whether a given node has a
     * child.
     *
     * @param currentIdx The index of the current node.
     * @return A boolean indicating whether the current node has a
     *  child or not.
     */
    bool hasAChild(size_t currentIdx) const;

    /**
     * Helper function that returns the index of the child with the
     * highest priority as defined by the higherPriority() functor.
     *
     * For example, if T == int and the left child of the current node
     * has data 5 and the right child of the current node has data 9,
     * this function should return the index of the left child (because
     * the default higherPriority() behaves like operator<).
     *
     * This function assumes that the current node has children.
     *
     * @param currentIdx The index of the current node.
     * @return The index of the highest priority child of this node.
     */
    size_t maxPriorityChild(size_t currentIdx) const;

    /**
     * Helper function that restores the heap property by sinking a
     * node down the tree as necessary.
     *
     * @param currentIdx The index of the current node that is being
     *  sunk down the tree.
     */
    void heapifyDown(size_t currentIdx);

    /**
     * Helper function that restores the heap property by bubbling a
     * node up the tree as necessary.
     *
     * @param currentIdx The index of the current node that is being
     *  bubbled up the tree.
     */
    void heapifyUp(size_t currentIdx);

    
};
}