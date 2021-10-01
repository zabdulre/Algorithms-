#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include <memory>
#include "bst.h"


struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, std::shared_ptr<AVLNode<Key, Value>> parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    std::shared_ptr<AVLNode<Key, Value>> getParent_AVL() const;
    std::shared_ptr<AVLNode<Key, Value>> getLeft_AVL() const;
    std::shared_ptr<AVLNode<Key, Value>> getRight_AVL() const;

protected:
    // to store the balance of a given node
    char balance_;
};


    // -------------------------------------------------
    // Begin implementations for the AVLNode class.
    // -------------------------------------------------



// An explicit constructor to initialize the elements by calling the base class constructor and setting
// the color to red since every new node will be red when it is first inserted.

template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, std::shared_ptr<AVLNode<Key, Value>> parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

// A destructor which does nothing.
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

// A getter for the balance of a AVLNode.
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

// A setter for the balance of a AVLNode.
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

// Adds diff to the balance of a AVLNode.
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

// A separate getParent_AVL function other than the base class function due to covariant return types
template<class Key, class Value>
std::shared_ptr<AVLNode<Key, Value>> AVLNode<Key, Value>::getParent_AVL() const
{
    return std::static_pointer_cast< AVLNode<Key, Value> >(this->parent_);
}

// Similar getLeft_AVL function
template<class Key, class Value>
std::shared_ptr<AVLNode<Key, Value>> AVLNode<Key, Value>::getLeft_AVL() const
{
    return std::static_pointer_cast< AVLNode<Key, Value> >(this->left_);
}

// Similar getRight_AVL function
template<class Key, class Value>
std::shared_ptr<AVLNode<Key, Value>> AVLNode<Key, Value>::getRight_AVL() const
{
    return std::static_pointer_cast< AVLNode<Key, Value> >(this->right_);
}


// -----------------------------------------------
// End implementations for the AVLNode class.
// -----------------------------------------------


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    
    void rotateLeft(std::shared_ptr<AVLNode<Key, Value>> p, std::shared_ptr<AVLNode<Key, Value>> n); //TODO
    void rotateRight(std::shared_ptr<AVLNode<Key, Value>> p, std::shared_ptr<AVLNode<Key, Value>> n); //TODO

    // Remember, AVL is a self-balancing BST
    // Resultant tree after the insert and remove function should be a balanced tree
    // Make appropriate calls to rotateLeft(...) and rotateRight(...)
    // in insert and remove for balancing the height of the AVLTree
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    // Helper function already provided to you.
    virtual void nodeSwap( std::shared_ptr<AVLNode<Key,Value>> n1, std::shared_ptr<AVLNode<Key,Value>> n2);
    void insertFix( std::shared_ptr<AVLNode<Key,Value>> p, std::shared_ptr<AVLNode<Key,Value>> n);
    void removeFix( std::shared_ptr<AVLNode<Key,Value>> p, int diff);
    // Add helper functions here
    // Consider adding functions like getBalance(...) given a key in the Tree
    // setBalance(...) given a key to a node and balance value, etc
    
    // You may implement a printRootAVL(...)
    // using the printRoot() function from the BST implementation
};

// Pre condition: p is the parent of n
// Post condition: p is the left child of n
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft (std::shared_ptr<AVLNode<Key, Value>> p, std::shared_ptr<AVLNode<Key, Value>> n)
{
    // TODO
    if (p != n -> getParent_AVL()) return;
    if (p -> getParent_AVL() != nullptr){//might have to do case where n is left child of p but maybe not
    n -> setParent(p -> getParent_AVL());
    (p == p -> getParent_AVL() -> getRight_AVL())? p -> getParent_AVL() -> setRight(n) : p -> getParent_AVL() -> setLeft(n);
    n -> setParent(p -> getParent());
    p -> setParent(n);
    std::shared_ptr<AVLNode<Key, Value>> temporaryNChildHolder = n -> getLeft_AVL();
    if (n -> getLeft_AVL() != nullptr)
    n -> getLeft_AVL() -> setParent(p);
    n -> setLeft(p);
    p -> setRight(temporaryNChildHolder);
    }
    else{
        this -> root_ = n;
        n -> setParent(nullptr);
        p -> setParent(n);
        std::shared_ptr<AVLNode<Key, Value>> temporaryNChildHolder = n -> getLeft_AVL();
        if (n -> getLeft_AVL() != nullptr)
        n -> getLeft_AVL() -> setParent(p);
        p -> setRight(temporaryNChildHolder);
        n -> setLeft(p);
    }
    return;
}

// Pre condition: p is the parent of n
// Post condition: p is the right child of n
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight (std::shared_ptr<AVLNode<Key, Value>> p, std::shared_ptr<AVLNode<Key, Value>> n)
{
    // TODO
    if (p != n -> getParent_AVL()) return;
    if (p -> getParent_AVL() != nullptr){//might have to do case where n is left child of p but maybe not
    n -> setParent(p -> getParent_AVL());
        (p == p -> getParent_AVL() -> getRight_AVL())? p -> getParent_AVL() -> setRight(n) : p -> getParent_AVL() -> setLeft(n);
    n -> setParent(p -> getParent());
    p -> setParent(n);
    std::shared_ptr<AVLNode<Key, Value>> temporaryNChildHolder = n -> getRight_AVL();
    if (n -> getRight_AVL() != nullptr)
    n -> getRight_AVL() -> setParent(p);
    n -> setRight(p);
    p -> setLeft(temporaryNChildHolder);
    }
    else{
        this -> root_ = n;
        n -> setParent(nullptr);
        p -> setParent(n);
        std::shared_ptr<AVLNode<Key, Value>> temporaryNChildHolder = n -> getRight_AVL();
        if (n -> getRight_AVL() != nullptr)
        n -> getRight_AVL() -> setParent(p);
        p -> setLeft(temporaryNChildHolder);
        n -> setRight(p);
    }
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(std::shared_ptr<AVLNode<Key,Value>> p, std::shared_ptr<AVLNode<Key,Value>> n){
    if (p == nullptr || p -> getParent_AVL() == nullptr) return;
 //   if (p -> getBalance() != 0 || n -> getBalance() != 0 ) return;
    std::shared_ptr<AVLNode<Key,Value>> g = p -> getParent_AVL();
    if (p == g -> getLeft_AVL()){
        g -> updateBalance(-1 );
        if( g -> getBalance() == 0) return;
        if (g -> getBalance() == -1) insertFix(g, p);
        if (g -> getBalance() == -2){
            if (((g -> getRight_AVL() == p) && (p -> getRight_AVL() == n)) || ((g -> getLeft_AVL() == p) && (p -> getLeft_AVL() == n))){//zigzig
                if (g -> getLeft_AVL() == p && p != nullptr)
                rotateRight(g, p);//small chance might have to flip variables
                else rotateLeft(g, p);
                g -> setBalance(0);
                p -> setBalance(0);
            }
            else{//zigzag
                if (g -> getLeft_AVL() == p && p != nullptr){
                rotateLeft(p, n);
                rotateRight(g, n);//might have to calculate balance manually for this part
                }
                else{
                    rotateRight(p, n);
                    rotateLeft(g, n);
                }
                if (n -> getBalance() == -1){
                    p -> setBalance(0);
                    g -> setBalance(1);
                    n -> setBalance(0);
                }
                else if (n -> getBalance() == 0){
                    p -> setBalance(0);
                    g -> setBalance(0);
                    n -> setBalance(0);
                }
                else{
                    p -> setBalance(-1);
                    g -> setBalance(0);
                    n -> setBalance(0);
                }
            }
        }
    }
    else{
        g -> updateBalance(1);
        if( g -> getBalance() == 0) return;
        if (g -> getBalance() == 1) insertFix(g, p);//might be a negative one here
        if (g -> getBalance() == 2){//maybe a negative here
            if (((g -> getRight_AVL() == p) && (p -> getRight_AVL() == n)) || ((g -> getLeft_AVL() == p) && (p -> getLeft_AVL() == n))){//zigzig
                    if (g -> getRight_AVL() == p && p != nullptr)//might not need this statement
                    rotateLeft(g, p);//small chance might have to flip variables
                    else rotateRight(g, p);
                    g -> setBalance(0);
                    p -> setBalance(0);
                }
                else{//zigzag
                    if (g -> getLeft_AVL() == p && p != nullptr){
                    rotateLeft(p, n);
                    rotateRight(g, n);//might have to calculate balance manually for this part
                    }
                    else{
                        rotateRight(p, n);
                        rotateLeft(g, n);
                    }
                    if (n -> getBalance() == 1){
                        p -> setBalance(0);
                        g -> setBalance(-1);
                        n -> setBalance(0);
                    }
                    else if (n -> getBalance() == 0){
                        p -> setBalance(0);
                        g -> setBalance(0);
                        n -> setBalance(0);
                    }
                    else{
                        p -> setBalance(1);
                        g -> setBalance(0);
                        n -> setBalance(0);
                    }
                }
        }
    }
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    if (this -> root_ == nullptr){
        this -> root_ = std::make_shared<AVLNode<Key, Value>>(AVLNode<Key, Value>(new_item.first, new_item.second, nullptr));
        std::static_pointer_cast< AVLNode<Key, Value> > (this -> root_) -> setBalance(0);
        return;
    }
    if (this -> internalFind(new_item.first) != nullptr){
        this -> internalFind(new_item.first) -> getItem().second = new_item.second;
        return;
    }
    std::shared_ptr<AVLNode<Key, Value>> keyValuePair = std::make_shared<AVLNode<Key, Value>>(AVLNode<Key, Value>(new_item.first, new_item.second, nullptr));

        std::shared_ptr<AVLNode<Key, Value>> cursor = std::static_pointer_cast< AVLNode<Key, Value> > (this -> root_);//might have inheritance issue here
        std::shared_ptr<AVLNode<Key, Value>> prev = std::static_pointer_cast< AVLNode<Key, Value> > (this -> root_);
        while (cursor != nullptr){
            prev = cursor;
            if (keyValuePair -> getItem().first < cursor -> getKey()){
                cursor = cursor -> getLeft_AVL();
            }
            else if (keyValuePair -> getItem().first == cursor -> getKey()){
                cursor -> setValue(keyValuePair -> getItem().second);
                break;
            }
            else{
                cursor = cursor -> getRight_AVL();
            }
        }
        if (keyValuePair -> getItem().first < prev -> getKey()){
            prev -> setLeft(std::make_shared<AVLNode<Key, Value>>(AVLNode<Key, Value>(keyValuePair -> getItem().first, keyValuePair -> getItem().second, prev)));
            cursor = prev -> getLeft_AVL();
//            cursor -> getParent_AVL() -> updateBalance(-1);
        }
        else{
            prev -> setRight(std::make_shared<AVLNode<Key, Value>>(AVLNode<Key, Value>(keyValuePair -> getItem().first, keyValuePair -> getItem().second, prev)));
            cursor = prev -> getRight_AVL();
//            cursor -> getParent_AVL() -> updateBalance(1);
        }
    
    
    cursor -> setBalance(0);
    
    if (cursor -> getParent_AVL() -> getBalance() == -1 || cursor -> getParent_AVL() -> getBalance() == 1) cursor -> getParent_AVL() -> setBalance(0);
    else{
        cursor -> getParent_AVL() -> updateBalance((cursor == cursor -> getParent_AVL() -> getRight_AVL())? 1 : -1);
        insertFix(cursor -> getParent_AVL(), cursor);
    }
    return;
}

template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key) {
    // TODO
//    if (this -> internalFind(6) != nullptr)
//    std::cout << (int)std::static_pointer_cast< AVLNode<Key, Value> >(this -> internalFind(6)) -> getBalance() << std::endl;
    int diff = 0;
    if (this -> root_ == nullptr) return;
        std::shared_ptr<AVLNode<Key, Value>> cursor = std::static_pointer_cast< AVLNode<Key, Value> >(this -> internalFind(key));
        if (cursor == nullptr) return;//not found or empty tree
//        std::shared_ptr<AVLNode<Key, Value>> p = cursor -> getParent_AVL();//might have to put on bottom
//    if (p != nullptr){
//        if (p -> getRight_AVL() == cursor) diff = -1;
//        else diff = 1;
//    }
            std::shared_ptr<AVLNode<Key, Value>> p = cursor -> getParent_AVL();//might have to put on bottom
        if (cursor -> getLeft_AVL() == nullptr && cursor -> getRight_AVL() == nullptr){//leaf
            if (cursor -> getParent_AVL() == nullptr){
                this -> root_ -> setRight(nullptr);//mem
                this -> root_ -> setLeft(nullptr);//mem
                this -> root_ -> setParent(nullptr);//mem
                this -> root_.reset();
            }
            else{std::shared_ptr<AVLNode<Key, Value>> prev = cursor;
            p = cursor -> getParent_AVL();
                if (p != nullptr){
                    if (p -> getRight_AVL() == cursor) diff = -1;
                    else diff = 1;
                }
                cursor -> setRight(nullptr);//mem
                cursor -> setLeft(nullptr);//mem
            cursor = cursor -> getParent_AVL();
                prev -> setParent(nullptr);//mem
            (cursor -> getRight_AVL() == this -> internalFind(key))? cursor -> setRight(nullptr): cursor -> setLeft(nullptr);//delete
            prev.reset();
//                if (!this -> isBalancedHelper(p)){
//                    while (!this -> isBalancedHelper(p)){
//                        if (p -> getLeft() != nullptr && p -> getRight() != nullptr){
//                            if (this -> height(p -> getLeft()) > this -> height(p -> getRight())){
//                                p = p -> getLeft_AVL();
//                            }
//                            else if (this -> height(p -> getLeft()) < this -> height(p -> getRight())){
//                                p = p -> getRight_AVL();
//                            }
//                        }
//                        else if (p -> getLeft() == nullptr && p -> getRight() != nullptr && p -> getRight_AVL() -> getBalance() != 0) p = p -> getRight_AVL();
//                        else if (p -> getLeft() != nullptr && p -> getRight() == nullptr && p -> getLeft_AVL() -> getBalance() != 0) p = p -> getLeft_AVL();
//                        else break;
//                    }
//                }
            }
        }
        else if (cursor -> getLeft_AVL() != nullptr && cursor -> getRight_AVL() != nullptr)//has both children
        {
            //promote predecessor
            std::shared_ptr<AVLNode<Key, Value>> pred = std::static_pointer_cast< AVLNode<Key, Value> > (this -> predecessor(cursor));
            nodeSwap(cursor, pred);
            p = cursor -> getParent_AVL();
            if (p != nullptr){
                if (p -> getRight_AVL() == cursor) diff = -1;
                else diff = 1;
            }
            if (cursor -> getRight_AVL() != nullptr){//cursor should now only have one leaf
                if (cursor -> getParent_AVL() == nullptr){
                    this -> root_ -> setLeft(nullptr);//memory leaks
                    this -> root_ = cursor -> getRight_AVL();
                    cursor -> setParent(nullptr);//mem
                    cursor -> setRight(nullptr);//mem
                    cursor -> setLeft(nullptr);//mem
                    this -> root_ -> setParent(nullptr);
                }
                else if (cursor == cursor -> getParent_AVL() -> getLeft_AVL()){//cursor is left child
                    cursor -> getParent_AVL() -> setLeft(cursor -> getRight_AVL());
                    cursor -> getRight_AVL() -> setParent(cursor -> getParent_AVL());
                    cursor -> setRight(nullptr);//mem
                    cursor -> setLeft(nullptr);//mem
                    cursor -> setParent(nullptr);//mem
                }
                else{
                    cursor -> getParent_AVL() -> setRight(cursor -> getRight_AVL());
                    cursor -> getRight_AVL() -> setParent(cursor -> getParent_AVL());
                    cursor -> setRight(nullptr);//mem
                    cursor -> setLeft(nullptr);//mem
                    cursor -> setParent(nullptr);//mem
                }
            }
            else if (cursor -> getLeft_AVL() != nullptr){
                if (cursor -> getParent_AVL() == nullptr){
                    this -> root_ -> setRight(nullptr);//memory leaks
                    this -> root_ = cursor -> getLeft_AVL();
                    cursor -> setParent(nullptr);//mem
                    cursor -> setRight(nullptr);//mem
                    cursor -> setLeft(nullptr);//mem
                    this -> root_ -> setParent(nullptr);
                }
                else if (cursor == cursor -> getParent_AVL() -> getLeft_AVL()){//cursor is left child
                    cursor -> getParent_AVL() -> setLeft(cursor -> getLeft_AVL());
                    cursor -> getLeft_AVL() -> setParent(cursor -> getParent_AVL());
                    cursor -> setRight(nullptr);//mem
                    cursor -> setLeft(nullptr);//mem
                    cursor -> setParent(nullptr);//mem
                }
                else{
                    cursor -> getParent_AVL() -> setRight(cursor -> getLeft_AVL());
                    cursor -> getLeft_AVL() -> setParent(cursor -> getParent_AVL());
                    cursor -> setRight(nullptr);//mem
                    cursor -> setLeft(nullptr);//mem
                    cursor -> setParent(nullptr);//mem
                }
            }
           else (cursor -> getParent_AVL() -> getRight_AVL() == cursor)? cursor -> getParent_AVL() -> setRight(nullptr): cursor -> getParent_AVL() -> setLeft(nullptr);//delete
            cursor -> setRight(nullptr);//mem
            cursor -> setLeft(nullptr);//mem
            cursor -> setParent(nullptr);//mem probably redundant before tho
            cursor.reset();
        }
        else//has one child
        {
            if (cursor -> getRight_AVL() != nullptr){
                p = cursor -> getParent_AVL();
                if (p != nullptr){
                    if (p -> getRight_AVL() == cursor) diff = -1;
                    else diff = 1;
                }
                if (cursor -> getParent_AVL() == nullptr){
                    this -> root_ -> setLeft(nullptr);//memory leaks
                    this -> root_ = cursor -> getRight_AVL();
                    cursor -> setParent(nullptr);//mem
                    cursor -> setRight(nullptr);//mem
                    cursor -> setLeft(nullptr);//mem
                    this -> root_ -> setParent(nullptr);
                }
                else if (cursor == cursor -> getParent_AVL() -> getLeft_AVL()){//cursor is left child
                    cursor -> getParent_AVL() -> setLeft(cursor -> getRight_AVL());
                    cursor -> getRight_AVL() -> setParent(cursor -> getParent_AVL());
                    cursor -> setRight(nullptr);//mem
                    cursor -> setLeft(nullptr);//mem
                    cursor -> setParent(nullptr);//mem
                }
                else{
                    cursor -> getParent_AVL() -> setRight(cursor -> getRight_AVL());
                    cursor -> getRight_AVL() -> setParent(cursor -> getParent_AVL());
                    cursor -> setRight(nullptr);//mem
                    cursor -> setLeft(nullptr);//mem
                    cursor -> setParent(nullptr);//mem
                }
            }
            else{//might be a problem with the conditions for the two else statements
                p = cursor -> getParent_AVL();
                if (p != nullptr){
                    if (p -> getRight_AVL() == cursor) diff = -1;
                    else diff = 1;
                }
                if (cursor -> getParent_AVL() == nullptr){
                    this -> root_ -> setRight(nullptr);//memory leaks
                    this -> root_ = cursor -> getLeft_AVL();
                    cursor -> setParent(nullptr);//mem
                    cursor -> setRight(nullptr);//mem
                    cursor -> setLeft(nullptr);//mem
                    this -> root_ -> setParent(nullptr);
                }
                else if (cursor == cursor -> getParent_AVL() -> getLeft_AVL()){//cursor is left child
                    cursor -> getParent_AVL() -> setLeft(cursor -> getLeft_AVL());
                    cursor -> getLeft_AVL() -> setParent(cursor -> getParent_AVL());
                    cursor -> setRight(nullptr);//mem
                    cursor -> setLeft(nullptr);//mem
                    cursor -> setParent(nullptr);//mem
                }
                else{
                    cursor -> getParent_AVL() -> setRight(cursor -> getLeft_AVL());
                    cursor -> getLeft_AVL() -> setParent(cursor -> getParent_AVL());
                    cursor -> setRight(nullptr);//mem
                    cursor -> setLeft(nullptr);//mem
                    cursor -> setParent(nullptr);//mem
                }
            }
            cursor.reset();
        }
    removeFix(p, diff);
        return;
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(std::shared_ptr<AVLNode<Key,Value>> n, int diff){
    if (n == nullptr) return;
    std::shared_ptr<AVLNode<Key,Value>> p = n -> getParent_AVL();
    if (diff == 0) return;
    int diff2 = 0;
    if (p != nullptr) {
        if (p -> getLeft_AVL() == n)
        diff2 = 1;
        else
        diff2 = -1;
    }
    if (diff == -1){
        if (n -> getBalance() - 1 == -2){//left off here, need to replace all calls to getLeft_AVL/right with getAVLLeft/right
            std::shared_ptr<AVLNode<Key,Value>> tall = n -> getLeft_AVL();
            if (tall != nullptr){
            if (tall -> getBalance() == -1){//zig-zig
                rotateRight(n, tall);
                n -> setBalance(0);
                tall -> setBalance(0);
                removeFix(p, diff2);
            }
            else if (tall -> getBalance() == 0){//zig-zig
                rotateRight(n, tall);
                n -> setBalance(-1);
                tall -> setBalance(1);
                return;
            }
            else if (tall -> getBalance() == 1){//zig-zag
                std::shared_ptr<AVLNode<Key,Value>> previousRight = tall -> getRight_AVL();
                rotateLeft(tall, previousRight);
                //if (n -> getParent_AVL() != nullptr)
                rotateRight(n, previousRight);//might have to check calls here
                if (previousRight != nullptr){
                if (previousRight -> getBalance() == 1){
                    n -> setBalance(0);
                    tall -> setBalance(-1);
                    previousRight -> setBalance(0);
                }
                else if (previousRight -> getBalance() == 0){
                    n -> setBalance(0);
                    tall -> setBalance(0);
                    previousRight -> setBalance(0);
                }
                else if (previousRight -> getBalance() == -1){
                    n -> setBalance(1);
                    tall -> setBalance(0);
                    previousRight -> setBalance(0);
                }
                removeFix(p, diff2);
            }
            }
            }
        }
        else if (n -> getBalance() - 1 == -1){
            n -> setBalance(-1);
            return;
        }
        else if (n -> getBalance() - 1 == 0){
            n -> setBalance(0);
            removeFix(p, diff2);
        }
    }
    else if (diff == 1){
        if (n -> getBalance() + 1 == 2){//left off here, need to replace all calls to getLeft_AVL/right with getAVLLeft/right
            std::shared_ptr<AVLNode<Key,Value>> tall = n -> getRight_AVL();
            if (tall != nullptr){
            if (tall -> getBalance() == 1){//zig-zig
                rotateLeft(n, tall);
                n -> setBalance(0);
                tall -> setBalance(0);
                removeFix(p, diff2);
            }
            else if (tall -> getBalance() == 0){//zig-zig
                rotateLeft(n, tall);
                n -> setBalance(1);
                tall -> setBalance(-1);
                return;
            }
            else if (tall -> getBalance() == -1){//zig-zag
                std::shared_ptr<AVLNode<Key,Value>> previousLeft = tall -> getLeft_AVL();
                rotateRight(tall, previousLeft);
                //if (n -> getParent_AVL() != nullptr)
                rotateLeft(n, previousLeft);//might have to check calls here
                if (previousLeft != nullptr){//might have to put at 519
                if (previousLeft -> getBalance() == -1){
                    n -> setBalance(0);
                    tall -> setBalance(1);
                    previousLeft -> setBalance(0);
                }
                else if (previousLeft -> getBalance() == 0){
                    n -> setBalance(0);
                    tall -> setBalance(0);
                    previousLeft -> setBalance(0);
                }
                else if (previousLeft -> getBalance() == 1){
                    n -> setBalance(-1);
                    tall -> setBalance(0);
                    previousLeft -> setBalance(0);
                }
                removeFix(p, diff2);
            }
            }
            }
        }
        else if (n -> getBalance() + 1 == 1){
            n -> setBalance(1);
            return;
        }
        else if (n -> getBalance() + 1 == 0){
            n -> setBalance(0);
            removeFix(p, diff2);
        }
    }
    return;
}

// Function already completed for you
template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( std::shared_ptr<AVLNode<Key,Value>> n1, std::shared_ptr<AVLNode<Key,Value>> n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

#endif
