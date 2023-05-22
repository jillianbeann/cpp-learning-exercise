//CIS554 HW5  Due: 11:59PM, Monday, April 3.
//Jillian Handrahan
// jehandra@syr.edu
//8377009572
#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

class node {
public:
    int value;
    shared_ptr<node> east;
    weak_ptr<node> Lchild;
    weak_ptr<node> Rchild;
    node() {}
    node(int i) { value = i; }
};

class tree {
public:
    shared_ptr<node> root;
    tree() { }
    //tree() { root = nullptr; }

    //Implement all member functions below
    tree(int n, int m);//constructor for n-level tree with random values in 0 ... m-1
    //n=1: 1 node; n-2: 3 nodes; n=3: 7 nodes; n=4: 15 nodes, etc.
    tree(const tree& T);//copy constructor

    ~tree();//destructor
    tree(tree&& T); //move constructor

    tree(const initializer_list<int>& V);//See lecture video recording for this. preorder?
    void operator = (const tree& T);//copy assignment
    void operator = (tree&& T); //move assignment
    tree ThreeTimes(); //return a tree with all node value being three times

    shared_ptr<node> operator[](int k);//The function returns the address of kth node
    //in the overall ring (or cycle).  For example, when k is 0, it returns the address of the
    //root; when k is 1, it returns the address of left child of root; when k is 2, it returns
    //the address of right child of root, etc.
    //For a level 4 tree, when k=14, it returns the address of the very last node of the tree.
    friend ostream& operator<<(ostream& str, const tree& T);//
    //print each level from root to leaves. At each level, print value from left to right.

    void InorderPrint(shared_ptr<node> p);//in-order printing
    void InorderHelp(weak_ptr<node> T);
   // weak_ptr<node> Const_help(int n, int m); // helper from class
};
void tree::InorderHelp(weak_ptr<node> T) {
    if (T.lock()) {
        InorderHelp(T.lock()->Lchild);
        
        cout << T.lock()->value << " ";
        
        InorderHelp(T.lock()->Rchild);
    }
}
//inorder
void tree::InorderPrint(shared_ptr<node> p) {
   // cout << "Inorder" << endl;
    InorderHelp(p->Lchild);
    cout << p->value << " ";
    InorderHelp(p->Rchild);
}


tree::tree(int n, int m) {
    if (n < 1) {
        return;
    }
    int numNodes = pow(2, n) - 1;
    //root = make_shared<node>(rand() % m);
    shared_ptr<node> ptr;
    shared_ptr<node> newRoot = make_shared<node>(rand() % m);
    root = newRoot; //root  is shared ptr
    ptr = root;
    for(int i = 0; i < numNodes-1; i++){
        shared_ptr<node> newN = make_shared<node>(rand() % m);
       // weak_ptr<node> wp1{ newNode };, no... east is shared
        ptr->east = newN;
        ptr = ptr->east;
    }
    ptr->east = root;
    
    shared_ptr<node> parent = root;
    if(!root->east) return; //if only 1 level, we are  done here
    weak_ptr<node> child = root->east;
    int level = 0;
    int members = 0;
    for(int i = 0; i < numNodes/2; i++){
        parent->Lchild = child;
        child = child.lock()->east; //lock weak
        parent->Rchild = child;
        child = child.lock()->east; //lock weak
        parent = parent->east;
    }
  //  root->east = root;
//    root->Lchild.lock()->east = root->Rchild.lock();
//    weak_ptr<node> fixL = root->Lchild;
//    weak_ptr<node> fixR = root->Rchild;
//    for (int i = 1; i < n-1; i++) {
//        fixL = fixL.lock()->Lchild;
//        fixR = fixR.lock()->Rchild;
//        fixR.lock()->east = fixL.lock();
//    }
//    root->east = root;
    cout << "Constructor" << endl;
}

//initializer list
tree::tree(const initializer_list<int>& V) {
    auto p(V.begin());
    int levels;
    levels = 1;
    int numNodes = 0;
    while (p != V.end()) {
        levels++;
        p++;
    }
    numNodes = levels-1;
    levels = log2(levels);
   // cout << levels << endl;
    if (levels < 1) {
        return;
    }
  //  cout << numNodes  <<endl;
    auto it(V.begin());
    auto it2(V.begin());
    
    shared_ptr<node> ptr;
    shared_ptr<node> newRoot = make_shared<node>(*it);
    it++;
    it2++;
    root = newRoot; //root  is shared ptr
    ptr = root;
    for(int i = 0; i < numNodes-1; i++){
        shared_ptr<node> newN = make_shared<node>(*it);
       // weak_ptr<node> wp1{ newNode };, no east is shared
        ptr->east = newN;
        ptr = ptr->east;
        it++;
    }
    ptr->east = root;
    
    shared_ptr<node> parent = root;
    it2++;
    if(!root->east) return; //if only 1 level, we are  done here
    weak_ptr<node> child = root->east;
    for(int i = 0; i < numNodes/2; i++){
        parent->Lchild = child;
        child = child.lock()->east; //lock weak
        parent->Rchild = child;
        child = child.lock()->east; //lock weak
        parent = parent->east;
        it2++;
    }
    cout << "Initializer List" << endl;
    
}

//copy constructor
tree::tree(const tree& T){
    int numNodes;
    numNodes = 1;
    shared_ptr<node> count;
    count = T.root;
    count = count->east;
    while (count!= T.root) {
        count = count->east;
        numNodes++;
    }
   // cout << numNodes << endl;
    shared_ptr<node> user;
    user = T.root;
    shared_ptr<node> ptr;
    shared_ptr<node> newRoot = make_shared<node>(user->value);
    root = newRoot; //root  is shared ptr
    ptr = root;
    user = user->east;
    for(int i = 0; i < numNodes-1; i++){
        shared_ptr<node> newN = make_shared<node>(user->value);
       // weak_ptr<node> wp1{ newNode };, no east is shared
        ptr->east = newN;
        ptr = ptr->east;
        user = user->east;
    }
    ptr->east = root;

    shared_ptr<node> parent = root;
    if(!root->east) return; //if only 1 level, we are  done here
    weak_ptr<node> child = root->east;
    for(int i = 0; i < numNodes/2; i++){
        parent->Lchild = child;
        child = child.lock()->east; //lock weak
        parent->Rchild = child;
        child = child.lock()->east; //lock weak
        parent = parent->east;
    }
    cout << "Copy Constructor" << endl;
}

//copy assignment (l-value operator)
void tree::operator = (const tree& T) {
    //needs destructor, reset the L value
    root.reset();
    //needs new tree
    int numNodes;
    numNodes = 1;
    shared_ptr<node> count;
    count = T.root;
    count = count->east;
    //get the number of nodes
    while (count!= T.root) {
        count = count->east;
        numNodes++;
    }
    //cout << numNodes << endl;
    //user is what we use to look over the other tree (r-val T3) and add to the L-value tree (T4)
    shared_ptr<node> user;
    user = T.root;
    shared_ptr<node> ptr;
    shared_ptr<node> newRoot = make_shared<node>(user->value);
    root = newRoot; //root  is shared ptr
    ptr = root;
    user = user->east;
    for(int i = 0; i < numNodes-1; i++){
        shared_ptr<node> newN = make_shared<node>(user->value);
       // weak_ptr<node> wp1{ newNode };, no east is shared
        ptr->east = newN;
        ptr = ptr->east;
        user = user->east;
    }
    ptr->east = root;

    shared_ptr<node> parent = root;
    if(!root->east) return; //if only 1 level, we are  done here
    weak_ptr<node> child = root->east;
    for(int i = 0; i < numNodes/2; i++){
        parent->Lchild = child;
        child = child.lock()->east; //lock weak
        parent->Rchild = child;
        child = child.lock()->east; //lock weak
        parent = parent->east;
    }
    cout << "Copy Assignment" << endl;
}

//move constructor
tree::tree(tree&& T) {//move constructor
    root = T.root;
    T.root = nullptr;
    cout << "Move Constructor" << endl;
}

//move assignment (r-value operator)
void tree::operator = (tree&& T) {
    //destroy
    root.reset();
    cout << root.use_count() << " ROOTREF" << endl;
    
    //pull a move constructor
    root = T.root;
    T.root = nullptr;
    cout << "Move Assignment" << endl;
}

//destructor
tree::~tree() {
    root.reset();
//    if (root) {
//        shared_ptr<node> del = root;
//        if (del->Rchild.lock()){
//            while (del) {
//                del = del->Rchild.lock();
//                del->east.reset();
//            }
//        }
//    }
//    if (root){
//        shared_ptr<node> findDel = root;
//        while (findDel->east != root) {
//            findDel = findDel->east;
//        }
//        cout << "ref " << findDel.use_count() << endl;
//        findDel.reset();
//        cout << "ref 2 " << findDel.use_count() << endl;
//       // cout << "ref 2 " << findDel->Lchild.use_count() << endl;
//    }
    cout <<  "Destructor" << endl;
}


tree tree::ThreeTimes() {
    tree temp {*this};
    //without affecting the rvalue, get the data from rvalue,
    //multiply by 3, and return temp to go into the lval
    //if i just change the east will it work?
    shared_ptr<node> fakeEast = temp.root;
    temp.root->value = temp.root->value*3;
    fakeEast = fakeEast->east;
    while (fakeEast!=temp.root) {
        fakeEast->value = fakeEast->value*3;
        fakeEast = fakeEast->east;
    }
    cout << "ThreeTimes" << endl;
    
    return temp;
}
//kth node
shared_ptr<node> tree::operator[](int k) {
    int count = 0;
    //if we get an invalid index, return nullptr. First, find how many nodes we are dealing with.
    shared_ptr<node> findLength = this->root;
    while (findLength->east != root) {
        findLength = findLength->east;
        count++;
    }
   // cout << count << endl;
    if (k>count || k < 0) {
        return nullptr;
    }
    
    shared_ptr<node> find = this->root;
    while (k) {
        find = find->east;
        k--;
    }
    cout << "Kth node" << endl;
    return find;
}


ostream& operator<<(ostream& str, const tree& T){
    shared_ptr<node> p = T.root;
    str << p->value << " ";
    p = p->east;
    while (p!= T.root) {
        str << p->value << " ";
        p = p->east;
    }
    return str;
}

int main() {
    tree T1(3, 10);
    cout << T1 << endl;
    T1.InorderPrint(T1.root);
    cout << endl;
    tree T2 = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
//
    cout << T2 << endl;
    T2.InorderPrint(T2.root);
    cout << endl;
//
    tree T3{ T2 };
    cout << T3 << endl;
    T3.InorderPrint(T3.root);
    cout << endl;
    tree T4;
    T4 = T3;
    cout << T4 << endl;
    T4.InorderPrint(T4.root);
    cout << endl;
//
    T4 = T3.ThreeTimes();
    cout << T4 << endl;
    T4.InorderPrint(T4.root);
    cout << endl;
    cout << T2[14]->value << endl;
    
    return 0;
}

//Constructor
//1 7 4 0 9 4 8
//0 7 9 1 4 4 8
//Initializer List
//10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
//17 13 18 11 19 14 20 10 21 15 22 12 23 16 24
//Copy Constructor
//10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
//17 13 18 11 19 14 20 10 21 15 22 12 23 16 24
//Copy Assignment
//10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
//17 13 18 11 19 14 20 10 21 15 22 12 23 16 24
//Copy Constructor
//ThreeTimes
//Move Assignment
//Destructor
//30 33 36 39 42 45 48 51 54 57 60 63 66 69 72
//51 39 54 33 57 42 60 30 63 45 66 36 69 48 72
//Destructor
//Destructor
//Destructor
//Destructor
