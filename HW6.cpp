//HW6, Due: 11:59pm, Wednesday, March 12, 2023
//Recursive Operation with Trees
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
pair<node*, node*> tree::InorderSort(node* p) {
    if (!(p->Lchild)) return {p,p};
    pair<node*,node*> pairPar = {p->Lchild, p->Rchild};
    pair<node*,node*> pairLeft = InorderSort(p->Lchild);
    pair<node*,node*> pairRight = InorderSort(p->Rchild);
    cout << "pairpar: " << pairPar.first->value << " " << pairPar.second->value << endl;
    cout << "pairleft2: " << pairLeft.first->value << " " << pairLeft.second->value << endl;
    cout << "pairirght2: " << pairRight.first->value << " " << pairRight.second->value << endl;
    cout << endl;
    while ((p->Lchild->value > p->value) || (p->Rchild->value < p->value)){
        if (p->Lchild->value > p->value){
            int save = p->value;
            p->value = p->Lchild->value;
            p->Lchild->value = save;
        }
        if (p->Rchild->value < p->value){
            int save = p->value;
            p->value = p->Rchild->value;
            p->Rchild->value = save;
        }
    }

    





//
//
//
//
////    //p left inner
////    node* lChi = p->Lchild;
//////    while (lChi->Rchild) {
////        if (lChi ->Rchild) lChi = lChi->Rchild;
//////    }
////    //p right inner
////    node* rChi = p->Rchild;
//////    while (rChi->Lchild) {
////       if (rChi->Lchild) rChi = rChi->Lchild;
//////    }
////    while (p->value > rChi->value || p->value < lChi->value){
////        if (lChi->value > root->value) {
////            int save = p->value;
////            p->value = lChi->value;
////            lChi->value = save;
////            pair<node*,node*> pairLeft3 = InorderSort(p->Lchild);
////        }
////        if (rChi->value < p->value) {
////            int save = p->value;
////            p->value = rChi->value;
////            rChi->value = save;
////            pair<node*,node*> pairRight3 = InorderSort(p->Rchild);
////
////        }
////        if (rChi->value < lChi->value) {
////            int save = rChi->value;
////            rChi->value = lChi->value;
////            lChi->value = save;
////            pair<node*,node*> pairRight2 = InorderSort(p->Lchild);
////            pair<node*,node*> pairLeft2 = InorderSort(p->Rchild);
////
////        }
////    }
    pair<node*, node*> myP{p->Lchild,p->Rchild};
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


    tree T1(3, 9);
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
//
//    T1.PreorderSort(T1.root);
//    T1.InOrderT(T1.root);   //4 3 5 1 8 7 8
//    cout << endl;
//    T1.PreOrderT(T1.root);   //1 3 4 5 7 8 8
//    cout << endl;
//    T1.PostOrderT(T1.root);  //4 5 3 8 8 7 1
//    cout << endl;
//    cout << endl;
//
//
//    T1.PostorderSort(T1.root);
//    T1.InOrderT(T1.root);   //1 4 3 8 5 8 7
//    cout << endl;
//    T1.PreOrderT(T1.root);  //8 4 1 3 8 5 7
//    cout << endl;
//    T1.PostOrderT(T1.root);  //1 3 4 5 7 8 8
//    cout << endl;
//    cout << endl;
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
