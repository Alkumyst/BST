//  main.cpp

#include <iostream>
#include <cassert>

template <class T>                                                      //templated Node class
class Node {
public:
    Node(T e) : element(e), left(nullptr), right(nullptr), parent(nullptr) {}           //node constructor
    T element;                                                          //node contents
    Node<T> *left;                                                      //pointer to left
    Node<T> *right;                                                     //pointer to right
    Node<T> *parent;
    ~Node() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        element = NULL;
    }
};

template <class T>
class BSTree {                                                          //templated bianry search tree
public:
    BSTree() {                                                          //bstree constructor
        root = nullptr;                                                 //sets root to null to await input
    }
    ~BSTree() {                                                         //bstree deconstructor
        KillTree(root);                                                 //deletes the tree
        delete root;                                                    //deletes the root
    }
    void KillTree(Node<T> *curr) {                                      //killTree function to delete tree (not be fully functional, but is also not required)
        if (curr == NULL) return;
        KillTree(curr->left);
        KillTree(curr->right);
    }
    void Insert(const T &elem) {                                        //insert function to start with
        if (root == nullptr) {                                          //if root is null
            root = new Node<T>(elem);                                   //set root to elem
        }
        else {
            Insert(root, elem);                                         //if root is not null, run overloaded Insert funct
        }
    }
    void Insert(Node<T> *curr, const T &elem) {                         //overloaded Insert
        if (curr->element == elem) {                                    //if an element equals elem
            std::cout << "\nDuplicated number\n";                       //tell user of duplicate
            return;                                                     //do not insert duplication, exit function early
        }
        if (curr->element > elem) {                                     //if current node is greater than elem
            if (curr->left == nullptr) {                                //if left pointer is null
                curr->left = new Node<T>(elem);                         //set elem to left
                curr->left->parent = curr;                              //sets parent pointer
            }
            else {                                                      //if left contains data
                Insert(curr->left, elem);                               //run insert again to move left
            }
        }
        else {                                                          //if current node is less than elem
            if (curr->right == nullptr) {                               //if right pointer is null
                curr->right = new Node<T>(elem);                        //set elem to right
                curr->right->parent = curr;                             //sets parent pointer
            }
            else {                                                      //if right contains data
                Insert(curr->right, elem);                              //run insert again to move right
            }
        }
    }
    void ViewTree() {                                                   //view tree function to start
        if (root == nullptr) {                                          //if root is null
            std::cout << "Your tree is empty" << std::endl;             //inform user
        }
        else {                                                          //if root contains data
            ViewTree(root);                                             //run ViewTree overloaded function
            std::cout << std::endl;                                     //place a space for readibility
        }
    }
    void ViewTree(Node<T> *curr) {                                      //overloaded view tree function
        if (curr != nullptr) {                                          //if current location is not null
            ViewTree(curr->left);                                       //look to left as far as possible to get highest number
            std::cout << curr->element << " ";                          //print current element
            ViewTree(curr->right);                                      //look right to next highest number
        }
    }
    Node<T>* FindMax() {                                                //find max value function
        if (root == nullptr) {                                          //if root is null
            std::cout << "Your tree is empty" << std::endl;             //inform user
            return nullptr;                                             //return null
        }
        else {                                                          //if root is not nul
            Node<T> *tempFind = FindMax(root);                          //run overloaded FindMax funct
            std::cout << std::endl;                                     //place a space for readibility
            return tempFind;                                            //return address
        }
    }
    Node<T>* FindMax(Node<T> * curr) {                                  //overloaded find max value function
        if (curr != nullptr) {                                          //if current location is not null
            if (curr->right != nullptr) {                               //if node to the right of current is not null
               return FindMax(curr->right);                             //rerun FindMax to move to the right node from current
            }
            else {                                                        //if there is no right node from current
//                std::cout << "The maximum value in this tree is: " << curr->element << std::endl;                        //print current element
                return curr;                                            //return address
            }
        }
        return nullptr;                                                 //return null if not found
    }
    bool Delete (Node<T> *r) {                                          //delet function
        if (isEmpty()) {                                                //if tree is empty
            return false;                                               //return false
        }
        if (r == NULL) {                                                //if the address passed in points to null
            return false;                                               //return false
        }
        else {                                                          //if tree is not empty and address does not point to null
            Node<T> *leftRem = r->left;                                 //create pointer for the left of what is to be removed
            Node<T> *rightRem = r->right;                               //create pointer for the right of what is to be removed
            if (leftRem == nullptr && rightRem == nullptr) {            //if both left and right of the node is null (no children)
                if (r->parent->right == r) {                            //if the node to be removed is the right node of its parent
                    r->parent->right = nullptr;                         //set parent's right node to null
                }
                if (r->parent->left == r) {                             //if the node to be removed is the left node of its parent
                    r->parent->left = nullptr;                          //set parent's left node to null
                }
            } if (leftRem == nullptr && rightRem != nullptr) {          //if only left of the node is null (one child to the right)
                if (r->parent->right == r) {                            //if the node to be removed is the right node of its parent
                    r->parent->right = rightRem;                        //set parent's right node to the node right of the node to be deleted
                    rightRem->parent = r->parent;                       //set the node to the right of the deleted node's parent to the parent of the node to be deleted
                }
                if (r->parent->left == r) {                             //if the node to be removed is the left node of its parent
                    r->parent->left = rightRem;                         //set parent's left node to the node left of the node to be deleted
                    rightRem->parent = r->parent;                       //set the node to the right of the deleted node's parent to the parent of the node to be deleted
                }
            } if (leftRem != nullptr && rightRem == nullptr) {          //if only right of the node is null (one child to the left)
                if (r->parent->right == r) {                            //if the node to be removed is the right node of its parent
                    r->parent->right = leftRem;                         //set parent's right node to the node left of the node to be deleted
                    leftRem->parent = r->parent;                        //set the node to the left of the deleted node's parent to the parent of the node to be deleted
                }
                if (r->parent->left == r) {                             //if the node to be removed is the left node of its parent
                    r->parent->left = leftRem;                          //set parent's left node to the node left of the node to be deleted
                    leftRem->parent = r->parent;                        //set the node to the left of the deleted node's parent to the parent of the node to be deleted
                }
            } if (leftRem != nullptr && rightRem != nullptr) {          //if neither the right or left of the node is null (two children)
                Node<T> *remTemp = FindMax(leftRem);                    //create temp node set to max of the left side of the node to be removed
                if (remTemp->left != nullptr) {                         //if the node left of the temp max node is not null
                    if (remTemp->parent->right == remTemp) {            //if the temp max node is the right node of its parent
                        remTemp->parent->right = remTemp->left;         //set parent's right node to the node left of the temp max node
                        remTemp->left->parent = remTemp->parent;        //set left node's parent to the parent node of the temp max node
                    }
                }
                if (r->parent->right == r) {                            //if the node to be removed is the right node of its parent
                    r->parent->right = remTemp;                         //set parent's right node to the temp max node
                }
                if (r->parent->left == r) {                             //if the node to be removed is the left node of its parent
                    r->parent->left = remTemp;                          //set parent's left node to the temp max node
                }
                remTemp->parent = r->parent;                            //set the temp max node's parent to the node to be deleted's parent
                if (remTemp != leftRem) {                               //if the temp max node is not the node to the left of the node to be deleted
                    remTemp->left = leftRem;                            //set the node to the left of the temp max node to the node left of the node to be deleted
                }
                remTemp->right = rightRem;                              //set the node to the right of the temp max node to the node right of the node to be deleted
            }
            delete r;                                                   //delete the node
            return true;                                                //return true
        }
    }
    Node<T>* Find(T value) {                                        //find function
        Node<T> *tempNode = root;                                   //create tempNode set to root
        while (tempNode != NULL) {                                  //while tempNode is not null
            if (tempNode->element == value) {                       //if the element of tempNode is found
                return tempNode;                                    //return tempNode
            }
            if (tempNode->element < value) {                        //if the value of the root is less than the value passed in
                tempNode = tempNode->right;                         //iterate through to the right
            }
            else if (tempNode->element > value) {                   //else if the value of the root is greater than the value passed in
               tempNode = tempNode->left;                           //iterate through to the left
            }
        }
        std::cout << "The value was not found or the list is empty" << std::endl;   //inform user value was not found
        return NULL;                                                                //return null
    }
    bool isEmpty() {                                                //function to check if tree is empty
        return (root == nullptr);                                   //return true if the root is null
    }
private:
    Node<T> *root;                                                      //root data
};

//int main(int argc, const char * argv[]) {                             //how Xcode initially had main funct
int main() {                                                            //main funct
    char foo;                                                           //junk variable, used in conjunction with cin to simulate system("pause")
    BSTree<int> intTree;                                                //binary search tree as an int
    BSTree<int> *testTree = new BSTree<int>();                          //test tree
    char menu = ' ';                                                    //menu option variable
    int value;                                                          //value to use within menu variable
    
    while (menu != '0') {                                                       //run code as long as menu is not '0'
        std::cout << std::endl << "~~~~~~~~~~ MENU ~~~~~~~~~~" << std::endl;
        std::cout << "1 - Insert number" << std::endl;
        std::cout << "2 - Delete number(WIP)" << std::endl;
        std::cout << "3 - View tree in order" << std::endl;
        std::cout << "4 - Find maximun number" << std::endl;
        std::cout << "5 - Find address" << std::endl;
        std::cout << "6 - Run tests(WIP)" << std::endl;
        std::cout << "0 - Quit program" << std::endl;
        std::cout << "Please enter a command: ";
        std::cin >> menu;                                                       //menu input
        switch (menu) {                                                         //switch case for menu usage
            case '0':                                                           //case 0 - exit
                break;                                                          //immediately breaks out of case and while statement
            case '1':                                                           //case 1 - insert
                std::cout << "\nInsert an int: ";
                std::cin >> value;                                              //set user input to value
                intTree.Insert(value);                                          //run insert function for intTree
                break;                                                          //break case
            case '2': {                                                         //case 2 - delete  WIP  go left and call max, move max to deleted point
                std::cout << "\nInsert an int to delete: ";
                std::cin >> value;                                              //set user input to value
                Node<int> *tempFind = intTree.Find(value);                      //create temp variable of adderess of value to be deleted
                if (tempFind == NULL) {                                                                 //if temp value is null
                    std::cout << "\nThe value was not found or the list is empty" << std::endl;         //inform user value was not found
                }
                else {                                                                                  //if temp value is not null
                    if (intTree.Delete(tempFind)) {                                                     //run delete, if return true:
                        std::cout << "\nThe int was removed" << std::endl;                              //inform user value was removed
                    }
                    else {                                                                              //if delete returns false
                        std::cout << "\nERROR" << std::endl;                                            //inform user of error
                    }
                }
                break;                                                          //break case
            }
            case '3':                                                           //case 3 - view
                intTree.ViewTree();                                             //run ViewTree for intTree
                break;                                                          //break case
            case '4': {                                                         //case 4 - maximum
                Node<int> *maxVal = intTree.FindMax();                          //find max
                 std::cout << "The maximum value in this tree is: " << maxVal->element << std::endl;                        //print current element
                break;                                                          //break case
            }
            case '5': {
                std::cout << "\nWhat int do you wish to find: ";
                std::cin >> value;                                                                      //user input
                Node<int> *found = intTree.Find(value);                                                 //create found node, run find function
                if (found != NULL) {                                                                    //if found node is not null
                    std::cout << "The address for " << value << " is: " << found << std::endl;          //inform user of data
                }
                break;
            }
            case '6': {
                assert (testTree->isEmpty() == true);                                   //tests if the constructor is working
                std::cout << "\nConstructor working successfully" << std::endl;
                std::cout << "Inserting int 5 to test tree\n";
                testTree->Insert(5);                                                    //insert 5 to the tree
                assert (testTree->isEmpty() == false);                                  //tests if insert is working
                std::cout << "Insert working successfully\n" << std::endl;
                std::cout << "Inserting int 10 to test tree\n";
                testTree->Insert(10);
                std::cout << "Inserting duplicate int 5 to test tree (should inform user of duplicate and not add to tree)\n";
                testTree->Insert(5);
                std::cout << "Displaying tree (should contain two ints of 5 and 10):\n";
                testTree->ViewTree();
                std::cout << "Inserting int 1 to test tree\n";
                testTree->Insert(1);
                std::cout << "Displaying tree (should contain three ints of 1, 5, and 10):\n";
                testTree->ViewTree();
                std::cout << "Running FindMax function\n";
                Node<int> *testMax = testTree->FindMax();
                assert(testMax->element == 10);
                std::cout << "FindMax function ran successfully\n";
                std::cout << "Running Delete function... Deleting 10 (no child test)\n";
                Node<int> *tempTest = testTree->Find(10);
                assert(testTree->Delete(tempTest) == true);
                std::cout << "Delete function ran successfully\n";
                std::cout << "Inserting int 2 to test tree\n";
                testTree->Insert(2);
                std::cout << "Running Delete function... Deleting 1 (one child test)\n";
                tempTest = testTree->Find(1);
                assert(testTree->Delete(tempTest) == true);
                std::cout << "Delete function ran successfully\n";
                std::cout << "Inserting int 1 to test tree\n";
                testTree->Insert(1);
                std::cout << "Inserting int 3 to test tree\n";
                testTree->Insert(3);
                std::cout << "Running Delete function... Deleting 2 (two children test)\n";
                tempTest = testTree->Find(2);
                assert(testTree->Delete(tempTest) == true);
                std::cout << "Delete function ran successfully\n";
                std::cout << "\nAll Tests Pass\n";
                break;
            }
            default:                                                            //default case
                std::cout << "\nInvalid input" << std::endl;                    //inform user of invalid input
                break;                                                          //break case
        }
        
    }
    
    std::cout << "Thanks for using this program, please enter any character to exit: ";
    std::cin >> foo;                                                                        //simulates system("pause")
    return 0;
}

