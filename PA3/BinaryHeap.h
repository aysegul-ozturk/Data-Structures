#pragma once

#include <vector>

struct HeapElement
{
    int     uniqueId;
    double  weight;
};

class BinaryHeap
{
    private:
    std::vector<HeapElement> elements;
    int theSize;
    bool contains(int id);
    void bubbleDown(int hole);
    void buildHeap(); 

    // Do not remove this the tester will utilize this
    // to access the private parts.
    friend class HW3Tester;

    protected:
    public:
        // Constructors & Destructor
                            BinaryHeap();
        //
        bool                Add(int uniqueId, double weight);
        bool                PopHeap(int& outUniqueId, double& outWeight);
        bool                ChangePriority(int uniqueId, double newWeight);
        int                 HeapSize() const;
};