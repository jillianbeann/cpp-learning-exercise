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
//    int level = 0;
//    int members = 0;
    for(int i = 0; i < numNodes/2; i++){
        parent->Lchild = child;
        child = child.lock()->east; //lock weak
        parent->Rchild = child;
        child = child.lock()->east; //lock weak
        parent = parent->east;
    }
    shared_ptr<node> lLeft = root;
    shared_ptr<node> fixL = root;
    shared_ptr<node> fixR = root;
    for (int i = 0; i < n; i++) {
        lLeft = lLeft->Lchild.lock();
        fixR->east = fixL;
        fixL = lLeft;
        fixR = (fixR->Rchild).lock();
        //cout << fixR.use_count()  << endl;

    }
    lLeft.reset();
    fixL.reset();
    fixR.reset();
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
    
    shared_ptr<node> lLeft = root;
    shared_ptr<node> fixL = root;
    shared_ptr<node> fixR = root;
    for (int i = 0; i < levels; i++) {
        lLeft = lLeft->Lchild.lock();
        fixR->east = fixL;
        fixL = lLeft;
        fixR = (fixR->Rchild).lock();
        //cout << fixR.use_count()  << endl;
    }
    lLeft.reset();
    fixL.reset();
    fixR.reset();
    cout << "Initializer List" << endl;
    
}
//I.size for initializer list size *************************************************************************
//copy constructor
tree::tree(const tree& T){
//take new form -> put it into old form -> assemble & fix
    // use iterator from print
    int numNodes = 1;
    shared_ptr<node> user;
    user = T.root;
    shared_ptr<node> ptr;
    shared_ptr<node> newRoot = make_shared<node>(user->value);
    root = newRoot; //root  is shared ptr
    ptr = root;
    //new form is in ptr
    while (user->Lchild.lock()) {
        user = user->Lchild.lock();
        shared_ptr<node> keep = user;
        //str << keep->value << " ";
        ptr->east = make_shared<node>(keep->value);
        numNodes++;
        keep = keep->east;
        while (keep != user) {
            //str << keep->value << " ";
            ptr = ptr->east;
            ptr->east = make_shared<node>(keep->value);
            keep = keep->east;
            numNodes++;
        }
        ptr = ptr->east;
        //ptr->east = make_shared<node>(keep->value);
        keep.reset();
    }
    
    //cout << numNodes << " " << endl;
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
    int levels = 0;
    levels = log2(numNodes);
    levels++;
    shared_ptr<node> lLeft = root;
    shared_ptr<node> fixL = root;
    shared_ptr<node> fixR = root;
    for (int i = 0; i < levels; i++) {
        lLeft = lLeft->Lchild.lock();
        fixR->east = fixL;
        fixL = lLeft;
        fixR = (fixR->Rchild).lock();
    }
    lLeft.reset();
    fixL.reset();
    fixR.reset();
    cout << "Copy Constructor" << endl;
}

//copy assignment (l-value operator)
void tree::operator = (const tree& T) {
    // delete one from each level
    while (root) {
        if (root->Lchild.lock()) {
            shared_ptr<node> delfind = root->Lchild.lock()->east;
    //               weak_ptr<node> delfind = root->Lchild;
            root->Lchild.lock()->east->east.reset();
            //cout << root->Lchild.lock()->east->east.use_count() << endl;
            //cout << root->Lchild.expired() << endl;
            

           // cout << delfind.use_count() << endl;
            //root = delfind.lock();
            root = delfind;
            delfind.reset();
            //root.reset();
            //cout << root->Rchild.expired() << endl;
            //cout << root->Lchild.lock()->east.use_count() << endl;
            //root->Lchild = delfind;
        }
        else { break; }
    }
    //reset root
    root.reset();
    //needs new tree
    int numNodes = 1;
    shared_ptr<node> user;
    user = T.root;
    shared_ptr<node> ptr;
    shared_ptr<node> newRoot = make_shared<node>(user->value);
    root = newRoot; //root  is shared ptr
    ptr = root;
    //new form is in ptr
    while (user->Lchild.lock()) {
        user = user->Lchild.lock();
        shared_ptr<node> keep = user;
        //str << keep->value << " ";
        ptr->east = make_shared<node>(keep->value);
        numNodes++;
        keep = keep->east;
        while (keep != user) {
            //str << keep->value << " ";
            ptr = ptr->east;
            ptr->east = make_shared<node>(keep->value);
            keep = keep->east;
            numNodes++;
        }
        ptr = ptr->east;
        //ptr->east = make_shared<node>(keep->value);
    }
    //cout << numNodes << " " << endl;
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
    int levels = 0;
    levels = log2(numNodes);
    levels++;
    shared_ptr<node> lLeft = root;
    shared_ptr<node> fixL = root;
    shared_ptr<node> fixR = root;
    for (int i = 0; i < levels; i++) {
        lLeft = lLeft->Lchild.lock();
        fixR->east = fixL;
        fixL = lLeft;
        fixR = (fixR->Rchild).lock();
    }
    user.reset();
    lLeft.reset();
    fixL.reset();
    fixR.reset();
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
    // delete one from each level
    while (root) {
        if (root->Lchild.lock()) {
            shared_ptr<node> delfind = root->Lchild.lock()->east;
    //               weak_ptr<node> delfind = root->Lchild;
            root->Lchild.lock()->east->east.reset();
            //cout << root->Lchild.lock()->east->east.use_count() << endl;
            //cout << root->Lchild.expired() << endl;
            

           // cout << delfind.use_count() << endl;
            //root = delfind.lock();
            root = delfind;
            delfind.reset();
            //root.reset();
            //cout << root->Rchild.expired() << endl;
            //cout << root->Lchild.lock()->east.use_count() << endl;
            //root->Lchild = delfind;
        }
        else { break; }
    }
//reset root
root.reset();
    //cout << root.use_count() << " ROOTREF" << endl;
    
    //pull a move constructor
    root = T.root;
    T.root = nullptr;
    cout << "Move Assignment" << endl;
}

//destructor
tree::~tree() {
        // delete one from each level
    while (root) {
        if (root->Lchild.lock()) {
            shared_ptr<node> delfind = root->Lchild.lock()->east;
//               weak_ptr<node> delfind = root->Lchild;
            root->Lchild.lock()->east->east.reset();
            //cout << root->Lchild.lock()->east->east.use_count() << endl;
            //cout << root->Lchild.expired() << endl;
            

           // cout << delfind.use_count() << endl;
            //root = delfind.lock();
            root = delfind;
            delfind.reset();
            //root.reset();
            //cout << root->Rchild.expired() << endl;
            //cout << root->Lchild.lock()->east.use_count() << endl;
            //root->Lchild = delfind;
        }
        else { break; }
    }
    //reset root
    root.reset();
    cout <<  "Destructor" << endl;
}


tree tree::ThreeTimes() {
    tree T {*this};
    //without affecting the rvalue, get the data from rvalue,
    //multiply by 3, and return temp to go into the lval
    
    shared_ptr<node> p = T.root;
    p->value = p->value*3;
    while (p->Lchild.lock()) {
        p = p->Lchild.lock();
        shared_ptr<node> keep = p;
        keep->value = keep->value*3;
        keep = keep->east;
        while (keep != p) {
            keep->value = keep->value*3;
            keep = keep->east;
        }
    }
    cout << "ThreeTimes" << endl;
    p.reset();
    return T;
}
//kth node
shared_ptr<node> tree::operator[](int k) {
    int save = k;
    int numNodesinLevel = 0;
    int level;
    level = 0;
    weak_ptr<node> find = this->root;
    shared_ptr<node> lefty = this->root;
    while (lefty->Lchild.lock() && k > 0) {
        lefty = lefty->Lchild.lock();
        k--;
        level++;
        
        numNodesinLevel = pow(2,level);
        find = lefty;
        while (numNodesinLevel >1 && k > 0) {
            find = find.lock()->east;
            numNodesinLevel--;
            k--;
        }
    }
    if (numNodesinLevel == 1 && k != 0) return nullptr;
    cout << save << "th node: ";
    lefty.reset();
    return find.lock();
}


ostream& operator<<(ostream& str, const tree& T){
    shared_ptr<node> p = T.root;
    str << p->value << " ";
    while (p->Lchild.lock()) {
        p = p->Lchild.lock();
        shared_ptr<node> keep = p;
        str << keep->value << " ";
        keep = keep->east;
        while (keep != p) {
            str << keep->value << " ";
            keep = keep->east;
        }
        keep.reset();
    }
    return str;
}

int main() {
    tree T1(3, 10);
    cout << T1 << endl;
    T1.InorderPrint(T1.root);
    cout << endl;
    tree T2 = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
////
    cout << T2 << endl;
    T2.InorderPrint(T2.root);
    cout << endl;
//
    //fix copy cons
    tree T3{ T2 };
    cout << T3 << endl;
    T3.InorderPrint(T3.root);
    cout << endl;
    tree T4;
//
    //fix copy ass
    T4 = T3;
    cout << T4 << endl;
    T4.InorderPrint(T4.root);
    cout << endl;
////
    T4 = T3.ThreeTimes();
    cout << T4 << endl;
    T4.InorderPrint(T4.root);
    //cout << endl;
    //cout << T3 << endl;
    cout << endl;
  //  for (int i = 0; i < 17; i++) {
   // cout << T2[14]->value << endl;
/// }
    
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
