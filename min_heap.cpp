/**
 * @file min_heap.cpp
 * Implementation of an Priority Queue structure. 
 *
 * @author Ravi Patel 
 */

#include "min_heap.h"

#include <cmath> // std::floor

#include <iostream> // std::err 

namespace cs225_fp {
/*
Implementation -- Zero-based root indexing 
*/

// default constructor 
MinHeap::MinHeap(void) : elems_({}) {
    ///   not need modifying
}

MinHeap::MinHeap(const std::vector<double>& vertex_dist_arr) {
    elems_ = std::vector<MinHeapNode>(vertex_dist_arr.size()); 
    heap_pos_ = std::vector<size_t>(vertex_dist_arr.size());

    for (size_t v = 0; v < elems_.size(); ++v) {
        elems_[v] = MinHeapNode(v, vertex_dist_arr[v]);
        heap_pos_[v] = v;
    }
}

void MinHeap::updateKey(size_t v, double new_dist) {
    int index_in_heap = heap_pos_[v];
    elems_[index_in_heap].dist = new_dist;
    heapifyUp(index_in_heap);
}

std::pair<size_t, double> MinHeap::top(void) const {
    const MinHeapNode& top = elems_[root()];
    return std::make_pair(top.v, top.dist);
}

void MinHeap::pop(void) {
    if (!empty()) {
        MinHeapNode root_node = elems_[root()];
        MinHeapNode last_node = elems_[elems_.size()-1];
        elems_.pop_back();
        elems_[root()] = last_node;

        // update positions of node root and last nodes
        heap_pos_[root_node.v] = elems_.size();
        heap_pos_[last_node.v] = root();
        heapifyDown(root());
    }
}

bool MinHeap::hasKey(size_t v) {
    return heap_pos_[v] < elems_.size();
}

bool MinHeap::empty(void) {
    return elems_.size() == 0;
}

size_t MinHeap::root(void) const {
    return 0;
}

size_t MinHeap::leftChild(size_t currentIdx) const {
    return 2 * currentIdx + 1;
}

size_t MinHeap::rightChild(size_t currentIdx) const {
    return 2 * currentIdx + 2;
}

size_t MinHeap::parent(size_t currentIdx) const {
    return std::floor((currentIdx-1)/2);
}

bool MinHeap::hasAChild(size_t currentIdx) const {
    size_t leftChildIndex = 2 * currentIdx + 1;
    return leftChildIndex < elems_.size();
}

size_t MinHeap::maxPriorityChild(size_t currentIdx) const {
    // assuming the node at currentIdx is NOT a leaf node 
    size_t leftChildIndex = leftChild(currentIdx);
    size_t rightChildIndex = rightChild(currentIdx);
    if (rightChildIndex < elems_.size()) 
        if (elems_[leftChildIndex].dist > elems_[rightChildIndex].dist)
            return rightChildIndex;
    return leftChildIndex;
}

void MinHeap::heapifyDown(size_t currentIdx) {
    if (!hasAChild(currentIdx))
        return;
    size_t minChildIdx = maxPriorityChild(currentIdx);
    if (elems_[minChildIdx].dist < elems_[currentIdx].dist) {
        // swap the vertex positions in heap representation given by heap_pos_
        heap_pos_[elems_[minChildIdx].v] = currentIdx;
        heap_pos_[elems_[currentIdx].v] = minChildIdx;
        std::swap(elems_[currentIdx], elems_[minChildIdx]);
        heapifyDown(minChildIdx);
    }
}

void MinHeap::heapifyUp(size_t currentIdx) {
    size_t parentIdx = parent(currentIdx);
    while (currentIdx != root() && elems_[currentIdx].dist < elems_[parentIdx].dist) {
        // swap the vertex positions in heap representation given by heap_pos_
        // std::cout << currentIdx << ", " << parentIdx << std::endl;
        // std::cout << elems_[currentIdx].v << ",, " << elems_[parentIdx].v << std::endl;

        heap_pos_[elems_[currentIdx].v] = parentIdx;
        heap_pos_[elems_[parentIdx].v] = currentIdx;
        std::swap(elems_[currentIdx], elems_[parentIdx]);
        // shift the currentIdx to point to the parentIdx
        currentIdx = parent(currentIdx);
        parentIdx = parent(currentIdx);
    }

}
}