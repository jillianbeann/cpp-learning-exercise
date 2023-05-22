//CIS554 HW7 Due: 11:59pm, Wednesday, April 19.
//Jillian Handrahan
// jehandra@syr.edu
//8377009572
#include <iostream>
#include <vector>
#include <list>
#include <map>

//For all printing, { ...} for linked list, {..} for map, <...> for list, and , [...] for vector
using namespace std;

template <typename T>  class node {
public:
    T value;
    node<T>* next;
    node(T i) { value = i; next = nullptr; }
    node() { next = nullptr; }
};

template <typename T> class LinkedList {
public:
    node<T>* head;

    LinkedList<T>() { head = nullptr; }

    LinkedList<T>(const initializer_list<T>& I);//Initializer List

};

template <typename T> LinkedList<T>::LinkedList(const initializer_list<T>& I) : LinkedList<T>() {//Initializer List
    head = nullptr;//not needed with the :Link....
    auto p1{ I.end() - 1 };//initializer_list supports begin() and end()

    while (p1 != I.begin() - 1) {
        node<T>* p2 { new node{*p1}};
    //    node* p2{ new node{*p1} };
        p2->next = head;
        head = p2;
        --p1;
    }
}

class myFunctorClass {
public:
    bool operator()(const list<int>* p1, const list<int>* p2) const {
        //For comparions, compare the sums of all int values in the structures.
        int sum1 = 0;
        int sum2 = 0;
        auto sumPoint {p1->begin()};
        while (sumPoint != p1->end()) {
            sum1 += *sumPoint;
            sumPoint++;
        }
        sumPoint = p2->begin();
        while (sumPoint != p2->end()) {
            sum2 += *sumPoint;
            sumPoint++;
        }
        return sum1>sum2;

        //return a bool value;
    }

    //map<list<int>*, vector<int>, myFunctorClass>*
    bool operator()(const map<list<int>*, vector<int>, myFunctorClass>* p1, const map<list<int>*, vector<int>, myFunctorClass>* pw) {

        //For comparions, compare the sums of all int values in the structures.
        int sum1 = 0;
        int sum2 = 0;
        auto sumPoint{*p1->begin()};
   //     while (sumPoint != *p1->end()) {
            auto listPoint {sumPoint.first->begin()};
            while (listPoint != sumPoint.first->end()){
                sum1+=*listPoint;
                listPoint++;
            }
            auto vecPoint {sumPoint.second.begin()};
            while (vecPoint != sumPoint.second.end()) {
                sum1+=*vecPoint;
                vecPoint++;
            }
        //    sumPoint++;
  //      }

        //return a bool value.
        return sum1>sum2;
    }
    friend ostream& operator<<(ostream& str, const map<map<list<int>*, vector<int>, myFunctorClass>*, int, myFunctorClass>& M) {
        str << "hi" << endl;
        return str;
    }


};
template <typename T1, typename T2> ostream& operator<<(ostream& str, const map<map<list<int>*, vector<int>, myFunctorClass>*, int, myFunctorClass>& M);

class myCompareClass
{
public:
    bool operator()(int x, int y)
    {
        return x > y;
    }
};




template <typename T> ostream& operator<<(ostream& str, const LinkedList<T>& L) {
    str << "{ ";
    node<T>* p1 {L.head};
//    node* p1{ L.head };
    while (p1) {
        str << p1->value << " ";
        p1 = p1->next;
    }
    str << "}";
    return str;
}

template <typename T, typename Compare>
void Sort(LinkedList<T>& lst, Compare comp) {
    bool sorted = false;
    node<T>* p1 = nullptr;

    while (!sorted) {
        sorted = true;
        p1 = lst.head;

        while (p1->next) {
            if (comp(p1->value, p1->next->value)) {
                // swap values
                T temp = p1->value;
                p1->value = p1->next->value;
                p1->next->value = temp;
                sorted = false;
            }
            p1 = p1->next;
        }
    }
}

bool f1(int x, int result) {
    x = x%5;
    result = result%5;
    return x>result;
}
//bool f1(int& x, int& result) {
//    x = x%5;
//    result = result%5;
//    return x>result;
//}

int main() {
    /*
    Write a bubble_sort function, Sort, which takes two arguments:
    a reference to LinkedList<T> and a callable. (See how Sort is called in code below.)
    When the callable is a lambda, the result of sorting is in descending order.
    When the callable is a functor, the result of sorting is in ascending order.
    When the callable is a regular function, the result of sorting is an ascending mod 5 sequence.
    Also see the sample screenshot.
    */
    LinkedList<int> a1{ 10,2,0,14,43,25,18,1,5,45 };
  //  LinkedList<char> a3 {'c', 'b', 'a', 'd', 'e'};
    cout << a1 << endl;
    cout << endl;
    auto SomeLambda = [](int x, int y) {
        return x < y;
      };
    Sort(a1, SomeLambda);//You need to implement the lambda
    cout << a1 << endl;
    cout << endl;
    LinkedList<int> a2{ 10,2,0,14,43,25,18,1,5,45 };
    cout << a2 <<endl;
    cout <<endl;
    Sort(a2, myCompareClass{});
    cout << a2 << endl;
    cout << endl;

    LinkedList<int> a3{ 10,2,0,14,43,25,18,1,5,45 };
    cout << a3 << endl;
    cout << endl;
    Sort(a3, f1);//You need to implement f1.
    cout << a3 << endl;
    cout << endl;




    /*
    Remember that map will always sort elements by comparing the first part of each element (i.e., the key part).
    Implement functors in class myFunctorClass classes to allow the following map declaration to work.
    In both classes, when comparing two keys, count the sums of all int values at all levels, and compare the sums.
    */
//    map<map<list<int>*, vector<int>, myFunctorClass>*, int, myFunctorClass> M1 {
//        { new map<list<int>*, vector<int>, myFunctorClass>{{{7, 5, 1}, {1, 2, 3}}, myFunctorClass()} , 4},
//        { new map<list<int>*, vector<int>, myFunctorClass>{{{2, 4, 2}, {4, 5, 6}}, myFunctorClass()} , 5},
//        { new map<list<int>*, vector<int>, myFunctorClass>{{{9, 1, 2}, {7, 8, 9}}, myFunctorClass()} , 6}
//    };

//    map<map<list<int>*, vector<int>, myFunctorClass>*, int, myFunctorClass> M1 {
//        {{{7, 5, 1}, {1, 2, 3}}, 4},
//        {{{2, 4, 2}, {4, 5, 6}}, 5},
//        {{{9, 1, 2}, {7, 8, 9}}, 6}
//
//    };
    map<list<int>*, vector<int>, myFunctorClass>* innerMap1ptr;
    map<list<int>*, vector<int>, myFunctorClass> innerMap1;
    innerMap1ptr = &innerMap1;
//    map<list<int>*, vector<int>, myFunctorClass>* innerMap2 = new map<list<int>*, vector<int>, myFunctorClass>{};
//    map<list<int>*, vector<int>, myFunctorClass>* innerMap3 = new map<list<int>*, vector<int>, myFunctorClass>{};
    
    list<int>* innerList1ptr;
    list<int> innerList1 = {7,5,1};
    innerList1ptr = &innerList1;
//    list<int>* innerList2{2, 4, 2};
//    list<int>* innerList3{9, 1, 2};
    
    vector<int> innerVec1 {1,2,3};
    vector<int> innerVec2 {4,5,6};
    vector<int> innerVec3 {7,8,9};
    innerMap1[innerList1ptr] = innerVec1;
//    innerMap2[innerList2] = innerVec2;
//    innerMap3[innerList3] = innerVec3;
    

    // Add some data to the inner maps
    map<map<list<int>*, vector<int>, myFunctorClass>*, int, myFunctorClass> M1 {};
    //M1[&innerMap1] = 1;

    
    // Add the inner maps to the outer map
//    std::map<std::map<std::list<int>*, std::vector<int>>, int, myFunctorClass> outerMap;
//    outerMap[innerMap1] = 1;
//    outerMap[innerMap2] = 2;
//    outerMap[innerMap3] = 3;
    //You need to create your initial data for M1.
    //For map, list and vector, at least three elements are required.

    //Implement the needed overloading operator<< to support the following printing.
    cout << M1 << endl;
    cout << endl;


    return 0;
}

//ostream& operator<<(ostream& str, const map<map<list<int>*, vector<int>, myFunctorClass>*, int, myFunctorClass>& M) {
//    str << "hi" << endl;
//    return str;
//}
