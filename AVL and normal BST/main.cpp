#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('d',10));
    bt.insert(std::make_pair('b',5));
    bt.insert(std::make_pair('a',20));
    bt.insert(std::make_pair('c',15));

    cout << "Binary Search Tree contents:" << endl;
    bt.print();
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    bt.print();
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    bt.print();
    cout << "Erasing b" << endl;
    bt.remove('b');
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    bt.print();
//    BinarySearchTree<int, double> bst;
//    bst.insert(std::make_pair(1, 1.0));
//    bst.insert(std::make_pair(2, 1.0));
//    bst.insert(std::make_pair(3, 1.0));
//    bst.print();
//    bst.remove(1);
    BinarySearchTree<int, double> bst;
    bst.insert(std::make_pair(5, 1.0));
    bst.insert(std::make_pair(2, 1.0));
    bst.insert(std::make_pair(6, 1.0));
    bst.insert(std::make_pair(4, 1.0));
    bst.print();
    bst.remove(5);
    bst.print();
    
    BinarySearchTree<int, int> testTree;

    testTree.insert(std::make_pair(2, 8));
    testTree.insert(std::make_pair(1, -50));
    testTree.insert(std::make_pair(3, 0));
    testTree.insert(std::make_pair(10, 0));
    testTree.insert(std::make_pair(15, 0));
    testTree.print();
    testTree.remove(-1);
    testTree.print();
    testTree.remove(2);
    testTree.print();
    testTree.remove(10);
    testTree.print();
    testTree.remove(1);
    testTree.print();
    testTree.remove(3);
    testTree.print();
    testTree.remove(15);
    testTree.print();
    testTree.remove(15);
    testTree.print();
    
    
    
    
    
    
    BinarySearchTree<int, std::string> b, c, d;
    std::pair<int, std::string> item5(5, "five");
    std::pair<int, std::string> item3(3, "three");
    std::pair<int, std::string> item7(7, "seven");
    std::pair<int, std::string> item4(4, "four");
    std::pair<int, std::string> item6(6, "six");
    std::pair<int, std::string> item9(9, "nine");
    std::pair<int, std::string> item10(10, "ten");
    std::pair<int, std::string> item2(2, "two");
    std::pair<int, std::string> item8(8, "eight");
    std::pair<int, std::string> item13(13, "thirteen");
    std::pair<int, std::string> item11(11, "eleven");
    std::pair<int, std::string> item12(12, "twelve");
    std::pair<int, std::string> item15(15, "fifteen");
    std::pair<int, std::string> item14(14, "fourteen");
    std::pair<int, std::string> item16(16, "sixteen");
    std::pair<int, std::string> item17(17, "seventeen");

    b.print();
    b.insert(item5);
    b.print();

    b.remove(7);
    b.print();

    b.remove(5);
    b.print();

    b.insert(item5);
    b.insert(item3);
    b.print();

    b.remove(5);
    b.print();

    b.remove(3);
    b.print();


    b.insert(item5);
    b.insert(item3);
    b.insert(item7);
    b.print();

    b.remove(5);
    b.print();

    b.remove(7);
    b.print();

    b.remove(3);
    b.print();

    b.insert(item5);
    b.insert(item3);
    b.insert(item7);
    b.insert(item4);
    b.print();

    b.remove(5);
    b.print();

    b.clear();
    b.print();

    b.insert(item5);
    b.insert(item3);
    b.insert(item7);
    b.insert(item4);
    b.insert(item6);
    b.print();

    b.remove(6);
    b.print();

    b.remove(4);
    b.print();

    b.clear();
    b.print();

    b.insert(item5);
    b.insert(item3);
    b.insert(item7);
    b.insert(item4);
    b.insert(item6);
    b.insert(item9);
    b.print();

    b.remove(5);
    b.print();

    b.remove(7);
    b.print();

    b.remove(6);
    b.print();

    b.clear();
    b.print();

    b.insert(item5);
    b.insert(item3);
    b.insert(item7);
    b.insert(item4);
    b.insert(item6);
    b.insert(item9);
    b.insert(item10);
     b.print();

    b.remove(5);
    b.print();

    b.remove(9);
    b.print();

    b.remove(3);
    b.print();

    b.remove(7);
    b.print();

    b.remove(4);
    b.print();

    b.remove(10);
    b.print();

    b.remove(10);
    b.print();

    b.remove(6);
    b.print();

    b.insert(item5);
    b.insert(item3);
    b.insert(item7);
    b.insert(item4);
    b.insert(item6);
    b.insert(item9);
    b.insert(item10);
    b.insert(item2);
    b.insert(item8);
    b.print();

    b.insert(item13);
    b.print();

    b.insert(item12);
    b.print();

    b.insert(item11);
    b.print();

    b.remove(13);
    b.print();
    
    b.remove(12);
    b.print();

    b.remove(10);
    b.remove(13);
    b.remove(7);
    b.remove(8);
    b.remove(7);
    b.print();


    d.insert(item10);
    d.insert(item3);
    d.insert(item2);
    d.insert(item15);
    d.insert(item12);
    d.insert(item11);
    d.insert(item14);
    d.insert(item13);
    d.insert(item16);
    d.insert(item17);

    d.print();

    d.remove(15);

    d.print();

    d.remove(10);
    d.print();
    c.print();
    c.insert(item5);
        c.print();
    c.insert(item3);
        c.print();
    c.insert(item7);
        c.print();
    c.insert(item4);
        c.print();
    c.insert(item6);
        c.print();
    c.insert(item9);
        c.print();
    c.insert(item10);
        c.print();
    c.insert(item2);
        c.print();
    c.insert(item8);
        c.print();
    c.insert(item15);
        c.print();
    c.insert(item11);
        c.print();
    c.insert(item14);
        c.print();
    c.insert(item13);
        c.print();
    c.insert(item12);
        c.print();

    c.print();
    c.remove(15);
    c.print();
    c.remove(14);

    c.print();

    
    
    
    
    
    
    
    
    
    
    
    
    
    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('c',2));
    at.insert(std::make_pair('b',3));
    at.print();
    at.insert(std::make_pair('d',1));
    at.insert(std::make_pair('e',10));
    at.print();
    cout << endl;
    
    at.remove('a');
    
    AVLTree<uint16_t, uint16_t> ttestTree;

    ttestTree.insert(std::make_pair(5, 8));
    ttestTree.insert(std::make_pair(3, 159));
    ttestTree.insert(std::make_pair(1, 9));
    ttestTree.insert(std::make_pair(3, 0x5a));
    ttestTree.insert(std::make_pair(15, 0xb));
    ttestTree.insert(std::make_pair(1, 4));
    ttestTree.insert(std::make_pair(3, 159));
    ttestTree.print();
    cout << "AVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing a" << endl;
    at.print();
    at.remove('a');
    at.print();

    
    AVLTree<int, std::string> bb;
    bb.insert(item5);
    bb.insert(item3);
    bb.insert(item7);
    bb.insert(item4);
    bb.insert(item6);
    bb.insert(item9);
    bb.insert(item10);
    bb.print();
    bb.remove(5);
    bb.print();
    bb.remove(9);
    bb.print();
    bb.remove(3);
    bb.print();
    bb.remove(7);//might not update correctly here
    bb.print();
    bb.remove(4);
    bb.print();
    bb.clear();
    bb.insert(item5);
    bb.insert(item3);
    bb.insert(item7);
    bb.insert(item4);
    bb.insert(item6);
    bb.insert(item9);
    bb.insert(item10);
    bb.insert(item2);
    bb.insert(item8);
    bb.insert(item13);
    bb.insert(item12);
    bb.insert(item11);
    bb.print();
    bb.remove(13);
    bb.print();
    

    return 0;
}
