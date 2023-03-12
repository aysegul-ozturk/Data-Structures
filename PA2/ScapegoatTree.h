#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T> &obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    ScapegoatTree<T> &operator=(const ScapegoatTree<T> &rhs);

    void balance();

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    void make_copy(Node<T> * r1, Node<T> * r2);
    int count(Node<T> *node) const;
    void removeAllNodesHelper(Node<T> *node);
    int getHeightHelper(Node<T> *node) const;
    const T & getHelper(Node<T> *node,const T &element) const;
    bool heightCondition() const;
    bool boundCondition();
    bool insertHelper(Node<T> *node, const T &element);
    bool removeHelper(Node<T> *t, const T &element);
    void putInArray(Node<T> *node, T * A, int &i);
    void makeItBalanced(Node<T> *&r, T * A, int n, int &i);
    void balanceHelper(Node<T> *node);

private: // DO NOT CHANGE THIS PART.
    Node<T> *root;

    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    /* TODO */
    root = NULL;
    upperBound = 0;
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
    /* TODO */
    if(obj.root == NULL){
        root = NULL;
        upperBound = 0;
    }
    else{
        make_copy(root,obj.root);
        upperBound = obj.upperBound;
    }
}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    /* TODO */
    removeAllNodes();
    upperBound = 0;

}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    /* TODO */
    if (root == NULL)
        return true;
    return false;
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    /* TODO */
    return getHeightHelper(root);
}

template<class T>
int ScapegoatTree<T>::getHeightHelper(Node<T> *node) const {
    if (node == NULL)
		return -1;
		/*
    else {
        int lHeight = getHeightHelper(root->left);
        int rHeight = getHeightHelper(root->right);
  
        if (lHeight > rHeight)
            return (lHeight + 1);
        else
            return (rHeight + 1);
    }
    */
    else return (std::max(getHeightHelper(node->left), getHeightHelper(node->right)) + 1);
}

template<class T>
int ScapegoatTree<T>::getSize() const {
    /* TODO */
    return count(root);
}

template<class T>
int ScapegoatTree<T>::count(Node<T> *node) const {
    if (node == NULL)
        return 0;
    return 1 + count(node->left) + count(node->right);
}

template<class T>
bool ScapegoatTree<T>::insert(const T &element) {
    /* TODO */
    return insertHelper(root, element);
}

template<class T>
bool ScapegoatTree<T>::heightCondition() const{
    double num = (log(upperBound)) / (log(3) - log(2));
    if (getHeight() > num)
        return true;
    else 
        return false;
}

template<class T>
bool ScapegoatTree<T>::boundCondition(){
    if (upperBound > 2 * getSize())
        return true;
    else 
        return false;
}

template<class T>
bool ScapegoatTree<T>::insertHelper(Node<T> *node, const T &element) {
    if (node == NULL) {
        root = new Node<T>();
        root->element = element;
        upperBound++;
        return true;
    }
    if (node->element == element)
		return false; // Duplicate
	else if (node->element > element) 
	{
		insertHelper(node->left, element);
		/*
		if( heightCondition()){
		    if (3 * count(node->left) > 2 * count(node)) 
                balanceHelper(node);
		}
		*/
	}
	else if(node->element < element)
	{
		insertHelper(node->right, element);
		/*
        if( heightCondition()){
            if (3 * count(node->right) > 2 * count(node))
                balanceHelper(node);
        }
        */
	}
	return true;

}

template<class T>
bool ScapegoatTree<T>::remove(const T &element) {
    /* TODO */
    return removeHelper(root, element);

}

template<class T>
bool ScapegoatTree<T>::removeHelper(Node<T> *t, const T &element) {
    if (t == NULL )
		return false;   // Item not found; do nothing
		
		
	if(element < t->element )
		removeHelper(t->left, element ); 
	else if( t->element < element )
		removeHelper(t->right, element );

	//else if( t->left != NULL && t->right != NULL ) // Two children
	//{
	//	t->element = getMin( t->right )->element;
	//	removeHelper(t->right, t->element );
	//}
	
	else if(t->element == element) { // only left or right child
		Node<T> *oldNode = t;
		t = ( t->left != NULL ) ? t->left : t->right;
		delete oldNode;
	}
	else{
	    throw new NoSuchItemException();
	    return false;
	} 
	    
	    
		
	// balance( t );
	return true;
}

template<class T>
void ScapegoatTree<T>::removeAllNodes() {
    /* TODO */
    removeAllNodesHelper(root);
    root = NULL;
    upperBound = 0;
}

template<class T>
void ScapegoatTree<T>::removeAllNodesHelper(Node<T> *node) {
    if (node == NULL)
        return;
    removeAllNodesHelper(node->left);
    removeAllNodesHelper(node->right);
    delete node;
    // node = NULL;
}

template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {
    /* TODO */
    return getHelper(root, element);

}

template<class T>
const T & ScapegoatTree<T>::getHelper(Node<T> *node,const T &element) const {
   if (node == NULL){
       throw NoSuchItemException();
   }
   if (node != NULL){
       if (node->element == element)
            return node->element;
       else if (node->element < element){
           return getHelper(node->right, element);
       }
       else if (node->element > element){
           return getHelper(node->left, element);
       }
   }

}

template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
            
            
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } 
    
    else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } 
    
    else if (tp == postorder) {
        /* TODO */
              // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        if (node == NULL)
            return;
        if (node->left) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t"<<node->element ;
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        print(node->right, preorder);

        
    } 
    
    else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
          return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        
        
        if (node->left) {
            std::cout << "," << std::endl;
        }
        // then, output the node.
        std::cout << "\t" << node->element;
        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        
        
        print(node->right, inorder);
    }
    
    
    else if (tp == postorder) {
        /* TODO */
        if (node == NULL)
            return;
        print(node->left, postorder);
        print(node->right, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t"<<node->element ;
        if (node->right) {
            std::cout << "," << std::endl;
        }
    
    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
void ScapegoatTree<T>::make_copy(Node<T> * r1, Node<T> * r2) {
    if(r2!=NULL)
    {
        r1=new Node<T>(r2->element, NULL, NULL);
        make_copy(r1->left,r2->left);
        make_copy(r1->right,r2->right);
    }
    else{
        r1=NULL;
    }
        
}

template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
    /* TODO */
    if(this != &rhs)
    {
        removeAllNodes();
        make_copy(root,rhs.root);
        upperBound = rhs.upperBound;
    }
    return *this;
}

template<class T>
void ScapegoatTree<T>::balance() {
    /* TODO */
    return balanceHelper(root);
}

template<class T>
void ScapegoatTree<T>::balanceHelper(Node<T> *node) {
    int i=0;
    int j=0;
    T *array = new T[count(node)];
    putInArray(node, array, i);
    removeAllNodesHelper(node);
    makeItBalanced(node, array, i, j);
    delete [] array;
}

template<class T>
void ScapegoatTree<T>::makeItBalanced(Node<T> *&r, T * A, int n, int &i) {
    if (n>0){
        r = new Node<T>();
        makeItBalanced(r->left, A, (n-1)/2, i);
        r->element = A[i];
        i++;
        makeItBalanced(r->right, A, n/2, i);
    }
    
}

template<class T>
void ScapegoatTree<T>::putInArray(Node<T> *node, T *A , int &i){
    if (node!= NULL){
        putInArray(node->left, A, i);
        A[i++] = node->element;
        putInArray(node->right, A, i);
    }
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {
    /* TODO */
}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {
    /* TODO */
}

template<class T>
const T &ScapegoatTree<T>::getMin() const {
    /* TODO */
    /* loop down to find the rightmost leaf */
    if (root == NULL)
        throw new NoSuchItemException();
    Node<T> * current = root;
    while (current->left != NULL)
        current = current->left;
     
    return (current->element);
}

template<class T>
const T &ScapegoatTree<T>::getMax() const {
    /* TODO */
    /* loop down to find the rightmost leaf */
    if (root == NULL)
        throw new NoSuchItemException();
    Node<T> * current = root;
    while (current->right != NULL)
        current = current->right;
     
    return (current->element);
}

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {
    /* TODO */
}
