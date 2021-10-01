#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <memory>

// A templated class for a Node in a search tree.
// The getters for parent/left/right are virtual so
// that they can be overridden for future kinds of
// search trees, such as Red Black trees, Splay trees,
// and AVL trees.
 
// Think carefully when implementing ths BST class functionalities
// as you would be using them for the next part of the assignment.
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, std::shared_ptr<Node<Key, Value>> parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual std::shared_ptr<Node<Key, Value>> getParent() const;
    virtual std::shared_ptr<Node<Key, Value>> getLeft() const;
    virtual std::shared_ptr<Node<Key, Value>> getRight() const;

    void setParent(std::shared_ptr<Node<Key, Value>> parent);
    void setLeft(std::shared_ptr<Node<Key, Value>> left);
    void setRight(std::shared_ptr<Node<Key, Value>> right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    std::shared_ptr<Node<Key, Value>> parent_;
    std::shared_ptr<Node<Key, Value>> left_;
    std::shared_ptr<Node<Key, Value>> right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/


// Explicit constructor for a node.
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, std::shared_ptr<Node<Key, Value>> parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/*
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
std::shared_ptr<Node<Key, Value>> Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
std::shared_ptr<Node<Key, Value>> Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
std::shared_ptr<Node<Key, Value>> Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(std::shared_ptr<Node<Key, Value>> parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(std::shared_ptr<Node<Key, Value>> left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(std::shared_ptr<Node<Key, Value>> right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;
public:
    
    // An internal iterator class for traversing the contents of the BST.
    // Complete the required implementations 
    // Additional functions are not necessary for this class.
    // Although, you may add them if you need any.
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value> & operator*() const;
        std::shared_ptr<std::pair<const Key,Value>> operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(std::shared_ptr<Node<Key,Value>> ptr);
        std::shared_ptr<Node<Key, Value>> current_;
    };

public:

    //Functions already completed for you
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions you need to complete
    std::shared_ptr<Node<Key, Value>> internalFind(const Key& k) const; // TODO
    std::shared_ptr<Node<Key, Value>> getSmallestNode() const;  // TODO
    static std::shared_ptr<Node<Key, Value>> predecessor(std::shared_ptr<Node<Key, Value>> current); // TODO
    static std::shared_ptr<Node<Key, Value>> successor(std::shared_ptr<Node<Key, Value>> current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Helper functions completed for you
    virtual void printRoot (std::shared_ptr<Node<Key, Value>> r) const;
    virtual void nodeSwap( std::shared_ptr<Node<Key,Value>> n1, std::shared_ptr<Node<Key,Value>> n2) ;


    // Add helper functions here
    // Consider adding simple helper functions like hasParent(...), isLeftChild(...), isRightChild(...)
    // Or functions like getHeight(...), removeInternal(...), etc
    void deleteHelp(std::shared_ptr<Node<Key,Value>> ptr);
    int height(std::shared_ptr<Node<Key,Value>> ptr) const;
    bool isBalancedHelper(std::shared_ptr<Node<Key,Value>> ptr) const;
protected:
    std::shared_ptr<Node<Key, Value>> root_;
    // You should not add other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

// Explicit constructor that initializes an iterator with a given node pointer.
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(std::shared_ptr<Node<Key,Value>> ptr) :
    current_(ptr)
{
    // TODO
}

// A default constructor that initializes the iterator to NULL.
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() :
    current_(NULL)
{
    // TODO
}


//Provides access to the item.
template<class Key, class Value>
std::pair<const Key,Value> & BinarySearchTree<Key, Value>::iterator::operator*() const
{
    // TODO
    return current_->getItem();
}

// Provides access to the address of the item.
template<class Key, class Value>
std::shared_ptr<std::pair<const Key,Value>> BinarySearchTree<Key, Value>::iterator::operator->() const
{
    // TODO
    return std::make_shared<std::pair<const Key,Value>>((this -> current_ -> getItem()));//might have to remove &
}


// Checks if 'this' iterator's internals have the same value as 'rhs'
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator==( const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (rhs.current_ == current_) return true;
    return false;
}

// Checks if 'this' iterator's internals have a different value as 'rhs'
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (rhs.current_ == current_) return false;
    return true;
}

// Advances the iterator's location using an in-order sequencing
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    this -> current_ = BinarySearchTree::successor(this -> current_);
    return *this;
}

// -------------------------------------------------------------
// End implementations for the BinarySearchTree::iterator class.
// -------------------------------------------------------------


// -----------------------------------------------------
// Begin implementations for the BinarySearchTree class.
// -----------------------------------------------------

// Default constructor for a BinarySearchTree, which sets the root to NULL.
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
    // TODO
    this -> root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    this -> clear();
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::deleteHelp(std::shared_ptr<Node<Key,Value>> ptr)
{
    if (ptr == nullptr) return;
    deleteHelp(ptr -> getLeft());
    deleteHelp(ptr -> getRight());
    ptr -> setParent(nullptr);
    ptr -> setLeft(nullptr);
    ptr -> setRight(nullptr);
    ptr.reset();
    return;
}


// Returns true if tree is empty 
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

// print the tree using the provided printRoot function
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}


// Returns an iterator to the "smallest" item in the tree
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

// Returns an iterator whose value means INVALID
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}


// Returns an iterator to the item with the given key, k 
// or the end iterator if k does not exist in the tree
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key & k) const
{
    std::shared_ptr<Node<Key, Value>> curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

// An insert method to insert into a Binary Search Tree.
// If the key is already present in the tree,
// update the current value with the new value.
// The tree may not remain balanced when inserting.
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    if (this -> root_ == nullptr) root_ = std::make_shared<Node<Key, Value>>(Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr));
    else{
        std::shared_ptr<Node<Key, Value>> cursor = this -> root_;
        std::shared_ptr<Node<Key, Value>> prev = this -> root_;
        while (cursor != nullptr){
            prev = cursor;
            if (keyValuePair.first < cursor -> getKey()){
                cursor = cursor -> getLeft();
            }
            else if (keyValuePair.first == cursor -> getKey()){
                cursor -> setValue(keyValuePair.second);
                return;
            }
            else{
                cursor = cursor -> getRight();
            }
        }
        if (keyValuePair.first < prev -> getKey()){
            prev -> setLeft(std::make_shared<Node<Key, Value>>(Node<Key, Value>(keyValuePair.first, keyValuePair.second, prev)));
        }
        else{
            prev -> setRight(std::make_shared<Node<Key, Value>>(Node<Key, Value>(keyValuePair.first, keyValuePair.second, prev)));
        }
    }
    return;
}


// A remove method to remove a specific key from a Binary Search Tree.
// Does nothing if key not found.
// The tree may not remain balanced after removal.
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    if (root_ == nullptr) return;
    std::shared_ptr<Node<Key, Value>> cursor = internalFind(key);
    if (cursor == nullptr) return;//not found or empty tree
    if (cursor -> getLeft() == nullptr && cursor -> getRight() == nullptr){//leaf
        if (cursor -> getParent() == nullptr){ root_.reset();
            return;}
        std::shared_ptr<Node<Key, Value>> prev = cursor;
        cursor = cursor -> getParent();
        prev -> setParent(nullptr);//memory leaks
        (cursor -> getRight() == internalFind(key))? cursor -> setRight(nullptr): cursor -> setLeft(nullptr);//delete
        prev.reset();
        return;
    }
    else if (cursor -> getLeft() != nullptr && cursor -> getRight() != nullptr)//has both children
    {
        //promote predecessor
        std::shared_ptr<Node<Key, Value>> pred = predecessor(cursor);
        nodeSwap(cursor, pred);
//        if (cursor -> getLeft() != nullptr){
////            nodeSwap(cursor, cursor -> getLeft());
////             }
//            cursor -> getParent() -> setLeft(cursor -> getLeft());
//            cursor -> getLeft() -> setParent(cursor -> getParent());
//        }
//        else if (cursor -> getRight() != nullptr){
////            nodeSwap(cursor, cursor -> getRight());
//        }
        if (cursor -> getRight() != nullptr){
            if (cursor -> getParent() == nullptr){
                //root_ -> setRight(nullptr);//memory leaks
                root_ -> setLeft(nullptr);//memory leaks
                root_ = cursor -> getRight();
                cursor -> setParent(nullptr);//mem
                cursor -> setRight(nullptr);//mem
                cursor -> setLeft(nullptr);//mem
                root_ -> setParent(nullptr);
                return;
            }
            if (cursor == cursor -> getParent() -> getLeft()){//cursor is left child
                cursor -> getParent() -> setLeft(cursor -> getRight());
                cursor -> getRight() -> setParent(cursor -> getParent());
                cursor -> setRight(nullptr);//mem
                cursor -> setLeft(nullptr);//mem
                cursor -> setParent(nullptr);//mem
            }
            else{
                cursor -> getParent() -> setRight(cursor -> getRight());
                cursor -> getRight() -> setParent(cursor -> getParent());
                cursor -> setRight(nullptr);//mem
                cursor -> setLeft(nullptr);//mem
                cursor -> setParent(nullptr);//mem
            }
        }
        else if (cursor -> getLeft() != nullptr){
            if (cursor -> getParent() == nullptr){
                root_ -> setRight(nullptr);//memory leaks
                //root_ -> setLeft(nullptr);//memory leaks
                root_ = cursor -> getLeft();
                cursor -> setParent(nullptr);//mem
                cursor -> setRight(nullptr);//mem
                cursor -> setLeft(nullptr);//mem
                root_ -> setParent(nullptr);
                return;
            }
            if (cursor == cursor -> getParent() -> getLeft()){//cursor is left child
                cursor -> getParent() -> setLeft(cursor -> getLeft());
                cursor -> getLeft() -> setParent(cursor -> getParent());
                cursor -> setRight(nullptr);//mem
                cursor -> setLeft(nullptr);//mem
                cursor -> setParent(nullptr);//mem
            }
            else{
                cursor -> getParent() -> setRight(cursor -> getLeft());
                cursor -> getLeft() -> setParent(cursor -> getParent());
                cursor -> setRight(nullptr);//mem
                cursor -> setLeft(nullptr);//mem
                cursor -> setParent(nullptr);//mem
            }
        }
       else (cursor -> getParent() -> getRight() == cursor)? cursor -> getParent() -> setRight(nullptr): cursor -> getParent() -> setLeft(nullptr);//delete
        cursor -> setParent(nullptr);//mem
        cursor -> setRight(nullptr);//mem
        cursor -> setLeft(nullptr);//mem
        cursor.reset();
    }
    else//has one child
    {
        //promote child
//        if (cursor -> getLeft() != nullptr){
//            if (cursor -> getParent() == nullptr){
//                root_ = cursor -> getLeft();
//                root_ -> setParent(nullptr);
//                return;
//            }
//            while (cursor -> getLeft() != nullptr)
//            nodeSwap(cursor, cursor -> getLeft());
//            if (cursor -> getRight() != nullptr){
//                cursor -> getParent() -> setLeft(cursor -> getRight());
//                cursor -> getRight() -> setParent(cursor -> getParent());
//            }
//            else cursor -> getParent() -> setLeft(nullptr);
//            cursor -> setParent(nullptr);
//            cursor.reset();
//        }
//        else{
//            if (cursor -> getParent() == nullptr){
//                root_ = cursor -> getRight();
//                root_ -> setParent(nullptr);
//                return;
//            }
//            while (cursor -> getRight() != nullptr)
//            nodeSwap(cursor, cursor -> getRight());
//            if (cursor -> getLeft() != nullptr){
//                cursor -> getParent() -> setRight(cursor -> getLeft());
//                cursor -> getLeft() -> setParent(cursor -> getParent());
//            }
//            else cursor -> getParent() -> setRight(nullptr);
//            cursor -> setParent(nullptr);
//            cursor.reset();
//        }
        if (cursor -> getRight() != nullptr){
            if (cursor -> getParent() == nullptr){
                //root_ -> setRight(nullptr);//memory leaks
                root_ -> setLeft(nullptr);//memory leaks
                root_ = cursor -> getRight();
                cursor -> setParent(nullptr);//mem
                cursor -> setRight(nullptr);//mem
                cursor -> setLeft(nullptr);//mem
                root_ -> setParent(nullptr);
                return;
            }
            if (cursor == cursor -> getParent() -> getLeft()){//cursor is left child
                cursor -> getParent() -> setLeft(cursor -> getRight());
                cursor -> getRight() -> setParent(cursor -> getParent());
                cursor -> setRight(nullptr);//mem
                cursor -> setLeft(nullptr);//mem
                cursor -> setParent(nullptr);//mem
            }
            else{
                cursor -> getParent() -> setRight(cursor -> getRight());
                cursor -> getRight() -> setParent(cursor -> getParent());
                cursor -> setRight(nullptr);//mem
                cursor -> setLeft(nullptr);//mem
                cursor -> setParent(nullptr);//mem
            }
        }
        else{
            if (cursor -> getParent() == nullptr){
                root_ -> setRight(nullptr);//memory leaks
                //root_ -> setLeft(nullptr);//memory leaks
                root_ = cursor -> getLeft();
                cursor -> setParent(nullptr);//mem
                cursor -> setRight(nullptr);//mem
                cursor -> setLeft(nullptr);//mem
                root_ -> setParent(nullptr);
                return;
            }
            if (cursor == cursor -> getParent() -> getLeft()){//cursor is left child
                cursor -> getParent() -> setLeft(cursor -> getLeft());
                cursor -> getLeft() -> setParent(cursor -> getParent());
                cursor -> setRight(nullptr);//mem
                cursor -> setLeft(nullptr);//mem
                cursor -> setParent(nullptr);//mem
            }
            else{
                cursor -> getParent() -> setRight(cursor -> getLeft());
                cursor -> getLeft() -> setParent(cursor -> getParent());
                cursor -> setRight(nullptr);//mem
                cursor -> setLeft(nullptr);//mem
                cursor -> setParent(nullptr);//mem
            }
        }
        cursor.reset();
        return;
    }
//    //need to find leaf
//    if (predecessor(cursor) == nullptr){
////        while (cursor -> getLeft() != nullptr){
////            this -> print();
////            nodeSwap(cursor, cursor -> getLeft());
////        }
//        root_ = cursor -> getLeft();
//        root_ -> setParent(nullptr);//might have to swap all the way down instead
//     //   root_ -> setParent(nullptr);
//        this -> print();//fix loop that happens sometimes with the root node
////        cursor -> getParent() -> setLeft(nullptr);
////        cursor.reset();
//        return;
//    }
//    nodeSwap(cursor, predecessor(cursor));//might have to switch up the variables
////    if (cursor -> getParent() != nullptr){ cursor = cursor -> getParent();
////        (cursor -> getRight() == internalFind(key))? cursor -> setRight(nullptr): cursor -> setLeft(nullptr);}
////    else {root_ = internalFind(key);
////        cursor.reset();
////    }//delete
//    if (cursor -> getLeft() != nullptr){
//        cursor = cursor -> getLeft();
//        while(cursor -> getLeft() != nullptr){
//            nodeSwap(cursor -> getParent(), cursor -> getLeft());
//        }
//        cursor -> getParent() -> setRight(nullptr);
//        cursor.reset();
//    }
//    else{
//        cursor -> getParent() -> setRight(nullptr);
//        cursor.reset();
//    }
    return;
}

template<class Key, class Value>
std::shared_ptr<Node<Key, Value>> BinarySearchTree<Key, Value>::successor(std::shared_ptr<Node<Key, Value>> current)
{
    // TODO
    if (current == nullptr) return nullptr;
    if (current -> getRight() != nullptr){std::shared_ptr<Node<Key, Value>> cursor = current -> getRight();
        while (cursor -> getLeft() != nullptr){
            cursor = cursor -> getLeft();
        }
        return cursor;
    }
    else{
        std::shared_ptr<Node<Key, Value>> cursor = current -> getParent();
        std::shared_ptr<Node<Key, Value>> prev = current;
        if (cursor == nullptr) return nullptr;
        if (current == ((cursor -> getLeft()))) return cursor;
        while (cursor != nullptr && (cursor -> getParent() != nullptr) && (prev == ((prev -> getParent() -> getRight()))) ){
            cursor = cursor -> getParent();
            prev = prev -> getParent();
        }
        if (cursor -> getParent() == nullptr && (cursor -> getItem().first <= current -> getItem().first)) return nullptr;
        return cursor;
    }
}

template<class Key, class Value>
std::shared_ptr<Node<Key, Value>> BinarySearchTree<Key, Value>::predecessor(std::shared_ptr<Node<Key, Value>> current)
{
    // TODO
    if (current == nullptr) return nullptr;
    if (current -> getLeft() != nullptr){std::shared_ptr<Node<Key, Value>> cursor = current -> getLeft();
        while (cursor -> getRight() != nullptr){
            cursor = cursor -> getRight();
        }
        return cursor;
    }
    else{
        std::shared_ptr<Node<Key, Value>> cursor = current -> getParent();
        std::shared_ptr<Node<Key, Value>> prev = current;
        if (cursor == nullptr) return nullptr;//root case
        if (current == ((cursor -> getRight()))) return cursor;
        while (cursor != nullptr && (cursor -> getParent() != nullptr) && (prev == ((prev -> getParent() -> getLeft()))) ){
            cursor = cursor -> getParent();
            prev = prev -> getParent();
        }
        if (cursor -> getParent() == nullptr && (cursor -> getItem().first >= current -> getItem().first)) return nullptr;
        return cursor;
    }
}

// A method to remove all contents of the tree and
// reset the values in the tree for use again.
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    this -> deleteHelp(this -> root_);
    this -> root_ = nullptr;
    return;
}


// A helper function to find the smallest node in the tree.
template<typename Key, typename Value>
std::shared_ptr<Node<Key, Value>> BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    if (root_ == nullptr) return root_;
    if (root_ -> getLeft() == nullptr) return root_;
    std::shared_ptr<Node<Key, Value>> cursor = root_;
    while (cursor -> getLeft() != nullptr){
        cursor = cursor -> getLeft();
    }
    return cursor;
}


// Helper function to find a node with given key, k and
// return a pointer to it or nullptr if no item with that key exists
template<typename Key, typename Value>
std::shared_ptr<Node<Key, Value>> BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    if (root_ == nullptr) return nullptr;
    std::shared_ptr<Node<Key, Value>> cursor = root_;
    if (key == this -> root_ -> getItem().first) return root_;
    while (cursor != nullptr && cursor -> getItem().first != key){
        if (key < cursor -> getItem().first){
            cursor = cursor -> getLeft();
        }
        else cursor = cursor -> getRight();
    }
    return cursor;
}

// Return true iff the BST is balanced. 
// You may use additional helper functions
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    return isBalancedHelper(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(std::shared_ptr<Node<Key,Value>> ptr) const{
    if (ptr == nullptr) return true;
    int l = height(ptr -> getLeft());
    int r = height(ptr -> getRight());
    if((l - r > 1) || (l - r < - 1)){ return false;}
    if (isBalancedHelper(ptr -> getLeft()) && isBalancedHelper(ptr -> getRight())){
        return true;
    }
    else return false;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height(std::shared_ptr<Node<Key,Value>> ptr) const
{
    if (ptr == nullptr) return 0;
    int l = height(ptr -> getLeft());
    int r = height(ptr -> getRight());
    return (1 + ((l >= r)? l: r));
}

// Function already implemented for you
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( std::shared_ptr<Node<Key,Value>> n1, std::shared_ptr<Node<Key,Value>> n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    std::shared_ptr<Node<Key, Value>> n1p = n1->getParent();
    std::shared_ptr<Node<Key, Value>> n1r = n1->getRight();
    std::shared_ptr<Node<Key, Value>> n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    std::shared_ptr<Node<Key, Value>> n2p = n2->getParent();
    std::shared_ptr<Node<Key, Value>> n2r = n2->getRight();
    std::shared_ptr<Node<Key, Value>> n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    std::shared_ptr<Node<Key, Value>> temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"


// ---------------------------------------------------
// End implementations for the BinarySearchTree class.
// ---------------------------------------------------


#endif
