#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    /* TODO */
      head = NULL;
      size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    /* TODO */
    head = NULL;
    *this = obj; // use operator=
}

template<class T>
LinkedList<T>::~LinkedList()
{
    /* TODO */
    removeAllNodes();
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    /* TODO */
    if (this != &rhs) {
        removeAllNodes(); // head is NULL and size is 0 now
        if (rhs.isEmpty()) return *this;
        
        Node<T> *temp = rhs.getFirstNode();

        do {
            // append increases size
            append(temp->data);
            temp = temp->next;
        }
        while (temp != rhs.getFirstNode());
        size = rhs.size;
    }
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    /* TODO */
      return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    /* TODO */
    // return (head == NULL && size == 0);
    return (head == NULL);
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    /* TODO */
    // if list is initially empty
    if (isEmpty()) return false;
    
    // if given node is NULL
    if (node == NULL) return false;
    
    Node<T> *temp = head;
    
    do {
      //
      //if (temp->data == node->data){
        //if (temp->prev->data == node->prev->data){
          //if (temp->next->data == node->next->data)
            //  return true;
        //}
      //}
      if (temp == node ) return true;
      temp = temp->next;
    }
    while (temp != this->getFirstNode());
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    /* TODO */
    // if list is initially empty
    if (isEmpty()) return NULL;
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    /* TODO */
    // if list is initially empty
    if (isEmpty()) return NULL;
    
    Node<T> *temp = head;
    return temp->prev;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    /* TODO */
    // if list is initially empty
    if (isEmpty()) return NULL;
    
    Node<T> *temp = head;
    do {
      if (temp->data == data)
        return temp;
      temp = temp->next;
    }
    while (temp != this->getFirstNode());
    return NULL;

}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    /* TODO */
    // if list is initially empty or index is out of bounds
    if (isEmpty() || index < 0 || index > size -1) return NULL;
    
    Node<T> *temp = head;
    
    for (int i=0; i<index; i++){
        temp = temp->next;
    }
    return temp;
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    /* TODO */
    /*
    // METHOD 1
    // if list is initially empty
    if (head == NULL){
        head = new Node<T>(data);
        // to make it circular
        head->next = head;
        head->prev = head;
    }
    else{
        Node<T> *front = head;
        Node<T> *tail = front->prev;

        Node<T> *newNode = new Node<T>(data, tail, front);
        front->prev = newNode;
        tail->next = newNode;
    }
    size++;
    */
    // METHOD 2
    if (head == NULL){
        head = new Node<T>(data);
        head->next = head;
        head->prev = head;
        head->data = data;
        size++;
    }
    else{
        insertAfterNode(data, head->prev);
    }
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    /* TODO */
    // if list is initially empty
    if (head == NULL){
        head = new Node<T>(data);
        // to make it circular
        head->next = head;
        head->prev = head;
    }
    else{
        Node<T> *front = head;
        Node<T> *tail = front->prev;
    
        Node<T> *newNode = new Node<T>(data, tail, front);
        front->prev = newNode;
        tail->next = newNode;
    
        head = newNode;
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    /* TODO */
    // if list is initially empty
    if (isEmpty()) return ;
    
    Node<T> *temp = head;

    do {
        if (temp==node){
           Node<T> *newNode = new Node<T>(data, temp, temp->next);
           newNode->data = data;
           temp->next->prev = newNode;
           temp->next = newNode;
           size++;
        }
        temp = temp->next;
    }
    while(temp != this->getFirstNode());
    
    // if node is not in the list
    return ;
    
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    /* TODO */
    // ARTIK ÇALIŞIYOR !!!
    // if list is initially empty or index is out of bounds
    // if (isEmpty() || index > size-1 || index<0) return ;
    if (index > size || index<0) return ;
    
    if (index == 0){
        prepend(data);
        return ;
    }
    
    Node<T> *temp = head;

    for (int i=0; i<index; i++){
        temp = temp->next;
    }
    Node<T> *newNode = new Node<T>(data, temp->prev, temp);
    temp->prev->next = newNode;
    temp->prev = newNode;
    size++;
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    /* TODO */
    // if list is initially empty or if given node is null
    if (isEmpty() || node == NULL) return -1;
    
    Node<T> *temp = head;
    
    int count = 0;
    do {
      // there could be nodes with same data value
      // so don't compare data but compare pointer itself
      if (temp == node)
        return count;
      temp = temp->next;
      count++;
    }
    while (temp != this->getFirstNode());
    return -1;
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    /* TODO */
    if(currentIndex > size-1 || currentIndex<0) return;
    if (newIndex < 0) return ;
    if (currentIndex == newIndex) return;
    if (isEmpty()) return;
    
    // remove current
    Node<T> *current = getNodeAtIndex(currentIndex);
        
    
    if(newIndex > size){
        current->prev->next = current->next;
        current->next->prev = current->prev;
        
        // add current to end
        current->prev= head->prev;
        current->next = head;
        head->prev->next = current;
        head->prev=current;
        return ;
    }
    
    Node<T> *newPlace = getNodeAtIndex(newIndex);
    
    if (newIndex == 0){
        // remove current
        current->prev->next = current->next;
        current->next->prev = current->prev;
        
        current->prev=head->prev;
        current->next=head;
        
        head->prev->next=current;
        head->prev=current;

        // update head
        head = current;
        
        return;

    }
    else if (currentIndex == 0){
        //store head next info
        Node<T> *headNext = head->next;
        
        // remove head
        head->prev->next = head->next;
        head->next->prev=head->prev;
        
        // add current
        current->next=newPlace->next;
        current->prev = newPlace;
        
        newPlace->next->prev= current;
        newPlace->next = current;
        
        // update head
        head = headNext;
        
        return ;
    }
    if(currentIndex<newIndex){
        // remove current
        current->prev->next = current->next;
        current->next->prev=current->prev;
        
        newPlace->next->prev = current;
        current->next = newPlace->next;
        current->prev = newPlace;
        newPlace->next = current;
    }
   else if(currentIndex>newIndex){
        // remove current
        current->prev->next = current->next;
        current->next->prev=current->prev;
        
        newPlace->prev->next = current;
        current->prev = newPlace->prev;
        newPlace->prev = current;
        current->next=newPlace;
   }


}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    /* TODO */
    // if list is initially empty or if given node is null
    if (isEmpty() || node == NULL) return ;
    
    if (containsNode(node)){
        if (node == head) head = head->next;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size--;
    }
    else
        return;
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    /* TODO */
    Node<T> *temp = head;
    if (temp == NULL) return;
    
    // remove all occurences
    do {
        if (temp->data == data){
            if (temp == head) head = head->next;
            Node<T> *oldnode = temp;
            temp = temp->next;
            
            oldnode->prev->next = oldnode->next;
            oldnode->next->prev = oldnode->prev;
            delete oldnode;
            size--;
        }
        else
            temp = temp->next;
    }
    while (temp != this->getFirstNode());
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    /* TODO */
    if (head == NULL || index>size-1 || index<0 ) return ;
    
    Node<T> *oldNode = getNodeAtIndex(index);
    if (index == 0 && size != 1){
        head = head->next;
    }
    else if (index == 0 && size == 1){
        head = NULL;
    }
    oldNode->prev->next = oldNode->next;
    oldNode->next->prev = oldNode->prev;
    oldNode->next = NULL;
    oldNode->prev = NULL;
    delete oldNode;
    size--;
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    /* TODO */
    if (this->isEmpty())
        return ;
    else {
        /*
        for (int i=0; i<size; i++){
            Node<T> * temp = head;
            
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            
            if (i == size-1) head = NULL;
            else head = head->next;
            
            delete temp;
        }
        */
        while (head->next != head ){
            Node<T> * temp = head;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            head = head->next;
            delete temp;
        }
        // delete head;
        Node<T> * temp = head;
        delete temp;

        head = NULL;
        size = 0;
    }
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do {
        std::cout << *node << std::endl;
        node = node->next;
    }
    while (node != this->getFirstNode());
}

#endif //LINKEDLIST_H
