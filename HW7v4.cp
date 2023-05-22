//CIS554 HW7 Due: 11:59pm, Wednesday, April 19.
//Jillian Handrahan
// jehandra@syr.edu
//8377009572
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <functional> //to use function

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
        node<T>* p2{ new node<T>{*p1} };
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
        cout << "pee " << sum1;
        
        return sum1<sum2;

        //return a bool value;
    }

    //map<list<int>*, vector<int>, myFunctorClass>*
    bool operator()(const map<list<int>*, vector<int>, myFunctorClass>* p1, const map<list<int>*, vector<int>, myFunctorClass>* pw) const {
        //For comparisons, compare the sums of all int values in the structures.
        int sum1 = 0;
        int sum2 = 0;
        auto sumPoint{ p1->begin() };
        while (sumPoint != p1->end()) {
            auto listPoint{ sumPoint->first->begin() };
            while (listPoint != sumPoint->first->end()) {
                sum1 += *listPoint;
                listPoint++;
            }
            auto vecPoint{ sumPoint->second.begin() };
            while (vecPoint != sumPoint->second.end()) {
                sum1 += *vecPoint;
                vecPoint++;
            }
            sumPoint++;
        }
        sumPoint = pw->begin();
        while (sumPoint != pw->end()) {
            auto listPoint{ sumPoint->first->begin() };
            while (listPoint != sumPoint->first->end()) {
                sum2 += *listPoint;
                listPoint++;
            }
            auto vecPoint{ sumPoint->second.begin() };
            while (vecPoint != sumPoint->second.end()) {
                sum2 += *vecPoint;
                vecPoint++;
            }
            sumPoint++;
        }
       // cout << sum1 << endl;
       // cout << sum2 << endl;
        //return a bool value.
        return sum1 < sum2;
    }
    
    friend ostream& operator<<(ostream& str, const map<map<list<int>*, vector<int>, myFunctorClass>*, int, myFunctorClass>& M) {
        str << "{ " << endl;
        for (auto i : M) { //for every map in the map
            str << "{ ";
            for (auto listVecPair : *i.first) {
                str << "< ";
                for (auto lst : *listVecPair.first){
                    str << lst << " ";
                }
                str << "> ";
                str << "[ ";
                for (auto vec : listVecPair.second){
                    str << vec << " ";
                }
                str << "] ";
            }
            str << i.second << " ";
            str << "}" << endl;
        }
        str << "}" << endl;
        return str;
    }
};

 class myCompareClass
{
public:
    template <typename T>
     bool operator()(T x, T y) {
        return x > y;
    }
};

template <typename T> ostream& operator<<(ostream& str, const LinkedList<T>& L) {
    str << "{ ";
    node<T>* p1 {L.head};
    while (p1) {
        str << p1->value << " ";
        p1 = p1->next;
    }
    str << "}";
    return str;
}
template <typename T, typename T2>
void Sort(LinkedList<T>& lst, T2 func) {
    bool sorted = false;
    node<T>* p1 = nullptr;

    while (!sorted) {
        sorted = true;
        p1 = lst.head;

        while (p1->next) {
            if (func(p1->value, p1->next->value)) {
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

auto SomeLambda = []<typename T>(T x, T y) {
    return x < y;
  };

template <typename T> bool f1(T x,  T y){
    x = x%5;
    y = y%5;
    return x>y;
}


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
    //LinkedList<float> a1{ 10.1,2.1,0.0,14.12,43.34,25.34,183.3,1.123,5.5,45.54 };
  //  LinkedList<char> a3 {'c', 'b', 'a', 'd', 'e'};
    cout << a1 << endl;
    cout << endl;

    Sort(a1, SomeLambda);//You need to implement the lambda DONE
    cout << a1 << endl;
    cout << endl;
    LinkedList<int> a2{ 10,2,0,14,43,25,18,1,5,45 };
    cout << a2 <<endl;
    cout <<endl;
    Sort(a2, myCompareClass{}); //DONE
    cout << a2 << endl;
    cout << endl;

    LinkedList<int> a3{ 10,2,0,14,43,25,18,1,5,45 };
    cout << a3 << endl;
    cout << endl;

    Sort(a3, f1<int>);//You need to implement f1.
    cout << a3 << endl;
    cout << endl;




    /*
    Remember that map will always sort elements by comparing the first part of each element (i.e., the key part).
    Implement functors in class myFunctorClass classes to allow the following map declaration to work.
    In both classes, when comparing two keys, count the sums of all int values at all levels, and compare the sums.
    */
    map<map<list<int>*, vector<int>, myFunctorClass>*, int, myFunctorClass> M1 {
        {new map<list<int>*, vector<int>, myFunctorClass>
            {{new list<int>{1,2,3}, {5,6,7,8}}, {new list<int> {4,5,6}, {2,4,76,83}}, {new list<int> {7,8,9}, {1,3,2,6}} }, 1},
        
        {new map<list<int>*, vector<int>, myFunctorClass>
            {{new list<int>{11,12,13}, {51,61,71,81}}, {new list<int> {14,15,16}, {21,41,74,80}}, {new list<int> {17,18,19}, {11,31,12,16}} }, 2},
        
        {new map<list<int>*, vector<int>, myFunctorClass>
            {{new list<int>{1,2,1}, {1,2,3,6}}, {new list<int> {2,3,1}, {2,4,6,8}}, {new list<int> {1,5,9}, {1,9,0,2}} }, 3}
    };

    //You need to create your initial data for M1.
    //For map, list and vector, at least three elements are required.
    //Implement the needed overloading operator<< to support the following printing.
    cout << M1 << endl;
    cout << endl;


    return 0;
}
