
//Hash Table
#include <iostream>
#include <unordered_set>//Hash Table
#include <unordered_map>//Hash Table
#include <string>
#include <vector>
#include <list>

using namespace std;

struct myFunctorClass {
    unsigned int operator()(const vector<int>& V) const {//hsah funciton for vector<int> keys
        int sum{ 0 };
        //hash<int> h1;
        for (auto& i : V) sum += i;
        return hash<int>{}(sum);//hash<int>{} an anonymous hash function
        //return h1(sum);

    }
    //cout << ThreeD{}{3,4,5} << endl;

    bool operator()(const vector<int>& V1, const vector<int>& V2) const {
        int sum1{ 0 }, sum2{ 0 };

        for (auto& i : V1) sum1 += i;
        for (auto& i : V2) sum2 += i;
        return sum1 == sum2 && V1.size() == V2.size();
    }
};

template <typename T> ostream& operator<<(ostream& str, const vector<T>& V) {
    str << "[ ";
    for (auto& i : V) str << i << " ";
    str << "]";
    return str;
}


int main() {
    //hash is a templated class    std::hash<T>  T: primitive type such as int, string, double, char, etc.

    hash<int> h1;//h1 is a hash function for int keys
    cout << h1(100) << " " << h1(101) << endl;

    hash<string> h2;//hash function for string keys
    cout << h2("CIS554 is very easy.") << " " << h2("CIS554 is  very easy") << endl;

    unordered_set<int> S1{ 7,4,1,3,9,11,67,99,0, 38,21,46,81,92,93, 100, 201,445,99 };
    //unordered_set<int, hash<int>, equal_to<int>> S1{ 7,4,1,3,9,11,67,99,0, 38,21,46,81,92,93, 100, 201,445,99 };
    //hsah<int>
    cout << endl;
    for (auto& i : S1) cout << i << " ";
    cout << endl;

    cout << "******************" << endl;

    cout << S1.bucket_count() << endl;//size of bucket array
    for (unsigned int i = 0; i < S1.bucket_count(); ++i) {
        cout << "bucket " << i << " contains  ";
        for (auto it = S1.begin(i); it != S1.end(i); ++it) cout << *it << " ";
        cout << endl;
    }

    cout << " @@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;


    unordered_map<string, int>  M1{ {"Fox", 1}, {"Rabbit", 2}, {"Butterfly", 3}, {"Dog", 4}, {"Cat", 5}, {"Tiger", 6}, {"Lion", 7}
    , {"Elephant", 8}, {"Snake", 9}, {"Bird", 10} };
    //Will use hash<string>
    cout << "\n\n";
    for (unsigned int i = 0; i < M1.bucket_count(); ++i) {
        cout << "bucket " << i << " contains  ";
        for (auto it = M1.begin(i); it != M1.end(i); ++it) cout << it->first << " " << it->second << "   ";
        cout << endl;
    }

    /*
    unordered_set<int, hash<int>, equal_to<int>> S3 {3,4,5,6,7,8,9,10};


    */

    unordered_set < vector<int>, myFunctorClass, myFunctorClass> S2{ {2,3,4,5}, {3,3,2,6}, {5,6,7,8,9 }, {2,2,2,2,2,5}, {1,4,5,6,7,8,9} };


    //the first functor is for hash and the second functor is for equal_to
        //hash<vector<int>> >?????
    cout << "\n\n\n";

    for (unsigned int i = 0; i < S2.bucket_count(); ++i) {
        cout << "bucket " << i << " contains  ";
        for (auto it = S2.begin(i); it != S2.end(i); ++it) cout << *it << " ";
        cout << endl;
    }

    cout << "\n\n\n";


    return 0;
}
