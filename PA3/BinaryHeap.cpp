#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
{
    // TODO: or not
    theSize = 0;
}

bool BinaryHeap::contains(int id)
{
    for (int i=1; i<theSize+1; i++){
        if (elements[i].uniqueId == id)
            return true;
    }
    return false;
}
    

bool BinaryHeap::Add(int uniqueId, double weight)
{
    // TODO:
    if (contains(uniqueId))
        return false;
    
    if (theSize == 0)
        elements.resize(1);
    elements[0].uniqueId = uniqueId;
    elements[0].weight = weight;
    
    if((theSize + 1) == ((int) elements.size()))
        elements.resize(elements.size( )*2 + 1);
    
    // Percolate up
    int hole = ++theSize;
    for( ; weight < elements[hole/2].weight; hole /= 2 )
        elements[hole] = elements[hole/2];
    elements[hole].uniqueId = uniqueId;
    elements[hole].weight = weight;
    return true;
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    // TODO:
    if (theSize == 0) return false;
    HeapElement tmp = elements[1];
    elements[1] = elements[theSize--];
    bubbleDown(1);
    outUniqueId = tmp.uniqueId;
    outWeight = tmp.weight;
    return true;
}

void BinaryHeap::bubbleDown(int hole) {
    // Internal method to percolate down in the heap.
    // hole is the index at which the percolate begins.
    int child;
    HeapElement tmp = elements[hole];
    
    for( ; hole*2 <= theSize; hole = child) {
        child = hole * 2;
        if(child != theSize && elements[child + 1].weight < elements[child].weight)
            child++;
        if(elements[child].weight < tmp.weight)
            elements[hole] = elements[child];
        else
            break;
    }
    elements[hole] = tmp;
}

void BinaryHeap::buildHeap() {
    // Establish heap-order property from an arbitrary
    // arrangement of items. Runs in linear time.
    for(int i = theSize/2; i > 0; i-- )
        bubbleDown(i);
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    // TODO:
    for (int i=1; i<theSize+1; i++){
        if (elements[i].uniqueId == uniqueId){
            elements[i].weight = newWeight;
            buildHeap();
            return true;
        }
    }
    return false;
}

int BinaryHeap::HeapSize() const
{
    // TODO:
    return theSize;
}