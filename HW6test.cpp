//CIS554 HW5  Due: 11:59PM, Monday, April 3.
//Jillian Handrahan
// jehandra@syr.edu
//8377009572
#include <iostream>
#include <typeinfo>
using namespace std;

class node {
public:
    int value;
    node* Lchild;
    node* Rchild;
    node(int i) : value(i), Lchild{ nullptr }, Rchild{ nullptr } {}
    node() { Lchild = Rchild = nullptr; }
};
class tree {//Full binary trees: 1, 3, 7, 15 ,   2^k-1 nodes
public:
    node* root;
    tree() { root = nullptr; }
    tree(int n, int m);//constructor
    node* Constructor_helper(int n, int m);
    void InOrderT(node* p);//Inorder Traveral of a subtree whose root is pointed by p
    void PreOrderT(node* p);
    void PostOrderT(node* p);

    //Implement InorderSort, Preordersot, PostorderSort and initializer_list.
    //Recursion is required in all implemenations.
    //In the three sorting implementation, you can use while loop, but not other loop stuctures (such as for).
    pair<node*, node*> InorderSort(node* p);
    pair<node*, node*> PreorderSort(node* p);
    pair<node*, node*> PostorderSort(node* p);
    tree(const initializer_list<int>& I);
    void IL_helper(const initializer_list<int>& I, const int*& p1, node* p2);
    
    //10 11 12 13 14 15 16 17 18 19 20 21 22 23 24

    //           17
    //     13          21
    //  11    15    19    23
    //10 12 14 16  18 20 22 24

    //10 11 12 13 14 15 16

    //      13
    //  11      15
    //10  12  14  16

};
pair<node*, node*> tree::PostorderSort(node* p){
    return pair<node*,node*> {p,p};
}

pair<node*, node*> tree::InorderSort(node* p) {
    if (!p) return {nullptr,nullptr};
    pair<node*,node*> pairLeft = InorderSort(p->Lchild);
    pair<node*,node*> pairRight = InorderSort(p->Rchild);
    if (pairLeft.second && pairLeft.second->value > p->value) {
        int save = p->value;
        p->value = pairLeft.second->value;
        pairLeft.second->value = save;
        InorderSort(root); // sort the entire tree again
    }
    if (pairRight.first && pairRight.first->value < p->value) {
        int save = p->value;
        p->value = pairRight.first->value;
        pairRight.first->value = save;
        InorderSort(root); // sort the entire tree again
    }
    node* passLeft = p;
    node* passRight = p;
    if (pairLeft.first) {
        passLeft= pairLeft.first;
    }
    if (pairRight.second) {
        passRight = pairRight.second;
    }
    pair<node*,node*> myP {passLeft,passRight};
    return myP;
}
//pair<node*, node*> tree::PreorderSort(node* p) { inorder soln
//    if (!p) return {nullptr,nullptr};
//    if (p->Lchild && p->Lchild->value > p->value) {
//        int save = p->value;
//        p->value = p->Lchild->value;
//        p->Lchild->value = save;
//        PreorderSort(p->Lchild);
//    }
//    if (p->Rchild && p->Rchild->value < p->value) {
//        int save = p->value;
//        p->value = p->Rchild->value;
//        p->Rchild->value = save;
//        PreorderSort(p->Rchild);
//    }
//    node* passLeft = p;
//    if (p->Lchild) {
//        auto pairs = PreorderSort(p->Lchild);
//        if (pairs.second) passLeft = pairs.second;
//    }
//    node* passRight = nullptr;
//    if (p->Rchild) passRight = PreorderSort(p->Rchild).first;
//    return {passLeft, passRight};
//}


//pair<node*, node*> tree::PreorderSort(node* p){
//    if (!p) return {nullptr,nullptr};
//    if (p->value < root->value) {
//        int save = root->value;
//        root->value = p->value;
//        p->value = save;
//        PreorderSort(p->Lchild); // sort the entire tree again
//    }
//    while ((p->Lchild && p->Rchild) && ((p->Lchild->value > p->value) || (p->Rchild->value < p->value))){
//        if (p->Lchild->value > p->value){
//            int save = p->value;
//            p->value = p->Lchild->value;
//            p->Lchild->value = save;
//           // PreorderSort(p->Rchild);
//        }
//        if (p->Rchild->value < p->value){
//            int save = p->value;
//            p->value = p->Rchild->value;
//            p->Rchild->value = save;
//            PreorderSort(root->Rchild);
//           // PreorderSort(root);
//        }
//    }
//    if ((p->Lchild) && p->value > p->Lchild->value) {
//        int save = p->Lchild->value;
//        p->Lchild->value = p->value;
//        p->value = save;
//        PreorderSort(p->Lchild); // sort the entire tree again
//    }
//
//    node* bottomLeft = root->Lchild;
//    while (bottomLeft->Rchild) {
//        bottomLeft = bottomLeft->Rchild;
//    }
//    if ((bottomLeft && p->Rchild) && bottomLeft->value > p->Rchild->value) {
//        int save = p->Rchild->value;
//        p->Rchild->value = bottomLeft->value;
//        bottomLeft->value = save;
//        PreorderSort(p->Lchild); // sort the entire tree again
//    }
//    pair<node*,node*> pairLeft = PreorderSort(p->Lchild);
//    node* passLeft = p;
//  //  node* passRight = p;
//    if (pairLeft.second) {
//        passLeft= pairLeft.second;
//    }
//    pair<node*,node*> myP {passLeft,p->Rchild};
//    return myP;
//
pair<node*, node*> tree::PreorderSort(node* p){
    if (!p) return {nullptr,nullptr};
    if (p->value < root->value) {
        int save = root->value;
        root->value = p->value;
        p->value = save;
        PreorderSort(p->Lchild); // sort the entire tree again
    }
    while ((p->Lchild && p->Rchild) && ((p->Lchild->value > p->value) || (p->Rchild->value < p->value))){
        if (p->Lchild->value > p->value){
            int save = p->value;
            p->value = p->Lchild->value;
            p->Lchild->value = save;
           // PreorderSort(p->Rchild);
        }
        if (p->Rchild->value < p->value){
            int save = p->value;
            p->value = p->Rchild->value;
            p->Rchild->value = save;
            PreorderSort(root->Rchild);
           // PreorderSort(root);
        }
    }
    if ((p->Lchild) && p->value > p->Lchild->value) {
        int save = p->Lchild->value;
        p->Lchild->value = p->value;
        p->value = save;
        PreorderSort(p->Lchild); // sort the entire tree again
    }

    node* bottomLeft = root->Lchild;
    while (bottomLeft->Rchild) {
        bottomLeft = bottomLeft->Rchild;
    }
    if ((bottomLeft && p->Rchild) && bottomLeft->value > p->Rchild->value) {
        int save = p->Rchild->value;
        p->Rchild->value = bottomLeft->value;
        bottomLeft->value = save;
        PreorderSort(p->Lchild); // sort the entire tree again
    }
    pair<node*,node*> pairLeft = PreorderSort(p->Lchild);
    node* passLeft = p;
  //  node* passRight = p;
    if (pairLeft.second) {
        passLeft= pairLeft.second;
    }
    pair<node*,node*> myP {passLeft,p->Rchild};
    return myP;
}
tree::tree(const initializer_list<int>& I) {
    int count = 1;
    auto countIt{I.begin()};
    while ((countIt+1) != I.end()) {
        count++;
        countIt++;
    }
    count = count/2;
    auto it{I.begin()};
    while (count) {
        it++;
        count--;
    }
    node* thisRoot = new node{*it};
    this->root = thisRoot;
    IL_helper(I,  it, thisRoot);

}
void tree::IL_helper(const initializer_list<int>& I, const int*& p1, node* p2){
    if (p1 == I.end()) return;
    if (p1 == I.begin()-1) return;
    auto findItR = p1;
    auto findItL = p1;
    int count = 0;
    int countL = count;
    int countR = 0;
    while (findItR != I.end()) {
        count++;
        findItR++;
    }
    while (findItL != I.begin()-1) {
        countL++;
        findItL--;
    }
    if (countL < count) {
        count = countL;
    }
    countL = count/2;
    countR = count/2;
    auto lC = p1;
    auto rC = p1;
    while (countL) {
        lC--;
        countL--;
    }
    while (countR) {
        rC++;
        countR--;
    }
    node* lChi = new node{*lC};
    node* rChi = new node{*rC};
    p2->Lchild = lChi;
    p2->Rchild = rChi;
    if (count > 2)IL_helper(I, lC, p2->Lchild);
    if (count > 2)IL_helper(I, rC, p2->Rchild);
}

tree::tree(int n, int m) {

    root = Constructor_helper(n, m);

}

node* tree::Constructor_helper(int n, int m) {//constructor helper
    if (n == 0) return nullptr;//NULL is nullptr and zero; don't use it anymore
    //int i{ NULL }; i is 0
    node* p{ new node{ rand() % m } };
    p->Lchild = Constructor_helper(n - 1, m);
    p->Rchild = Constructor_helper(n - 1, m);
    return  p;
}


void tree::PostOrderT(node* p) {
    if (!p) return;
    PostOrderT(p->Lchild);
    //cout << p->value << " ";
    PostOrderT(p->Rchild);
    cout << p->value << " ";
}

void tree::PreOrderT(node* p) {
    if (!p) return;
    cout << p->value << " ";
    PreOrderT(p->Lchild);
    //cout << p->value << " ";
    PreOrderT(p->Rchild);
}

void tree::InOrderT(node* p) {
    if (!p) return;
    InOrderT(p->Lchild);
    cout << p->value << " ";
    InOrderT(p->Rchild);
}







int main() {


    tree T1(3 , 9);
    T1.InOrderT(T1.root);      //7 8 4 5 1 8 3   in
    cout << endl;
    T1.PreOrderT(T1.root);     //5 8 7 4 8 1 3   pre
    cout << endl;
    T1.PostOrderT(T1.root);    //7 4 8 1 3 8 5   post
    cout << endl;

    cout << endl;


    T1.InorderSort(T1.root);
    T1.InOrderT(T1.root);    //1 3 4 5 7 8 8
    cout << endl;
    T1.PreOrderT(T1.root);   //5 3 1 4 8 7 8
    cout << endl;
    T1.PostOrderT(T1.root);  //1 4 3 7 8 8 5
    cout << endl;
    cout << endl;

    T1.PreorderSort(T1.root);
    T1.InOrderT(T1.root);   //4 3 5 1 8 7 8
    cout << endl;
    T1.PreOrderT(T1.root);   //1 3 4 5 7 8 8
    cout << endl;
    T1.PostOrderT(T1.root);  //4 5 3 8 8 7 1
    cout << endl;
    cout << endl;


    T1.PostorderSort(T1.root);
    T1.InOrderT(T1.root);   //1 4 3 8 5 8 7
    cout << endl;
    T1.PreOrderT(T1.root);  //8 4 1 3 8 5 7
    cout << endl;
    T1.PostOrderT(T1.root);  //1 3 4 5 7 8 8
    cout << endl;
    cout << endl;
//
//    tree T2{ 10,11,12,13,14,15,16 };
//    T2.InOrderT(T2.root);  //10 11 12 13 14 15 16
//    cout << endl;
//    T2.PreOrderT(T2.root);   //13 11 10 12 15 14 16
//    cout << endl;
//    T2.PostOrderT(T2.root);  //10 12 11 14 16 15 13
//    cout << endl;

    return 0;
}


//7 8 4 5 1 8 3   in
//5 8 7 4 8 1 3   pre
//7 4 8 1 3 8 5   post
//
//1 3 4 5 7 8 8
//5 3 1 4 8 7 8
//1 4 3 7 8 8 5
//
//4 3 5 1 8 7 8
//1 3 4 5 7 8 8
//4 5 3 8 8 7 1
//
//1 4 3 8 5 8 7
//8 4 1 3 8 5 7
//1 3 4 5 7 8 8
//
//10 11 12 13 14 15 16
//13 11 10 12 15 14 16
//10 12 11 14 16 15 13




