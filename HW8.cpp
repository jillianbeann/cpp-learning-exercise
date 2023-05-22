//HW8.  Due: Thursday, April 27 at 11:59pm
//Jillian Handrahan
// jehandra@syr.edu
//8377009572
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

//when comparing equality of two structures, always compare sums of all int values in the structures
//When Hashing a structure, always hash the sum of all int values in the structure
//For printing, map: { ...}  vector: [...]  set(or unordered set): <...>



class myCompare {
public:
    bool operator() (const set<int>* p1, const set<int>* pw) const {
        int sum1;
        int sum2;
        sum1 = 0;
        sum2 = 0;
        for (auto i: *p1) {
            sum1+= i;
        }
        for (auto i : *pw) {
            sum2 += i;
        }
        cout << "hi" << endl;
        return sum1<sum2;
    }
    
    bool operator() (const set<set<int>*>* p1, const set<set<int>*>* pw) const {
        int sum1= 0;
        int sum2 = 0;
        for (auto& i : *p1) {
            for (auto j : *i) {
                sum1+= j;
            }
        }
        for (auto& i : *pw) {
            for (auto j : *i) {
                sum2+= j;
            }
        }
        cout << "ji " << sum1;
        cout << "pee " << sum2;
        return sum1 < sum2;
    }
    
    bool operator()( const map < set<set<int>*>*, vector<int>* , myCompare> p1,  const map < set<set<int>*>*, vector<int>*, myCompare > pw) const {
        //For comparisons, compare the sums of all int values in the structures.
        int sum1 = 0;
        int sum2 = 0;
        auto sumPoint{ p1.begin() };
        while (sumPoint != p1.end()) {
            auto setSetPoint{ sumPoint->first->begin() };
            while (setSetPoint != sumPoint->first->end()) {
                for (auto setP : **setSetPoint ){
                    sum1 += setP;
                    
                }
                setSetPoint++;
            }
            auto vecPoint{ sumPoint->second->begin() };
            while (vecPoint != sumPoint->second->end()) {
                sum1 += *vecPoint;
                vecPoint++;
            }
            sumPoint++;
        }
        sumPoint = pw.begin();
        while (sumPoint != pw.end()) {
            auto setSetPoint{ sumPoint->first->begin() };
            while (setSetPoint != sumPoint->first->end()) {
                for (auto setP : **setSetPoint ){
                    sum2 += setP;
                    
                }
                setSetPoint++;
            }
            auto vecPoint{ sumPoint->second->begin() };
            while (vecPoint != sumPoint->second->end()) {
                sum2 += *vecPoint;
                vecPoint++;
            }
            sumPoint++;
        }
//        cout << sum1 << endl;
//        cout << sum2 << endl;
        //return a bool value.
        return sum1 < sum2;
    }
    
    friend ostream& operator<<(ostream& str, const set<map < set<set<int>*>*, vector<int>* , myCompare>, myCompare>& S) {
        str << "{ " << endl;
        for (auto i : S) { //for every map in the set
            str << "{ ";
            for (auto setSet : i) {
                for (auto& lst : *setSet.first){
                    str << "< ";
                    for (auto val : *lst) {
                        str << val << " ";
                    }
                    str << "> ";
                }
                str << "[ ";
                for (auto vec : *setSet.second){
                    str << vec << " ";
                }
                str << "] ";
            }
            str << "}" << endl;
        }
        str << "}" << endl;
        return str;
    }

};


int main() {
    //The following statement won't compile. Fix it.
    set<map < set<set<int>*>*, vector<int>*, myCompare >, myCompare> S1{ //set
        {{new set<set<int>*>{ new set<int>{16,36,56}, new set<int>{ 1, 2, 36}, new set<int>{5,46,36}}, new vector<int>{1, 2, 3} }}, //map 1
        {{new set<set<int>*>{ new set<int>{4,2,5}, new set<int>{ 1, 4, 3}, new set<int>{5,12,31}}, new vector<int>{1, 20, 13} }}, //map 2
        {{new set<set<int>*>{ new set<int>{4,2,5}, new set<int>{ 1, 41, 3}, new set<int>{5,12,34}}, new vector<int>{1, 20, 13} }} //map 3
    };//Create your initial values with at least 3 elements in every STL container.
    cout << S1 << endl;


    //The following statement won't compile. Fix it.
//    unordered_set< map < set<set<int>*>*, vector<int>* >> H1 { //set
//        {{new set<set<int>*>{ new set<int>{1,3,5}, new set<int>{ 1, 20, 3}, new set<int>{5,46,3}}, new vector<int>{1, 2, 3} }}, //map 1
//        {{new set<set<int>*>{ new set<int>{4,2,5}, new set<int>{ 1, 4, 3}, new set<int>{5,12,31}}, new vector<int>{1, 20, 13} }}, //map 2
//        {{new set<set<int>*>{ new set<int>{4,2,5}, new set<int>{ 1, 4, 3}, new set<int>{5,12,31}}, new vector<int>{1, 20, 13} }} //map 3
//    };//You can re-use the above.

   // cout << H1 << endl;//print bucket arrays

    return 0;
}
