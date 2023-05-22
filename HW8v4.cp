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
        return sum1<sum2;
    }
    
    bool operator() (const set<set<int>*, myCompare>* p1, const set<set<int>*, myCompare>* pw) const {
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
        return sum1 < sum2;
    }
    
    bool operator()( const map <set<set<int>*, myCompare>*, vector<int>*, myCompare> p1,  const map < set<set<int>*, myCompare>*, vector<int>*, myCompare> pw) const {
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
        return sum1 < sum2;
    }
    
    friend ostream& operator<<(ostream& str, const set<map < set<set<int>*, myCompare>*, vector<int>* , myCompare>, myCompare>& S) {
        str << "{ " << endl;
        for (auto i : S) { //for every map in the set
            str << "{ ";
            for (auto setSet : i) {
                str << "< ";
                for (auto& lst : *setSet.first){
                    str << "< ";
                    for (auto val : *lst) {
                        str << val << " ";
                    }
                    str << "> ";
                }
                str << "> ";
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

class myUnorderedCompare {
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
        return sum1<sum2;
    }

    bool operator() (const set<set<int>*, myUnorderedCompare>* p1, const set<set<int>*, myUnorderedCompare>* pw) const {
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
        return sum1 < sum2;
    }
    
    bool operator()( const map <set<set<int>*, myUnorderedCompare>*, vector<int>*, myUnorderedCompare> p1,  const map < set<set<int>*, myUnorderedCompare>*, vector<int>*, myUnorderedCompare> pw) const {
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
        return sum1 < sum2;
    }
    
    unsigned long operator()(const map<set<set<int>*, myUnorderedCompare>*, vector<int>*, myUnorderedCompare> & x) const {
        int sum = 0;
        auto sumPoint{ x.begin() };
        while (sumPoint != x.end()) {
            auto setSetPoint{ sumPoint->first->begin() };
            while (setSetPoint != sumPoint->first->end()) {
                for (auto setP : **setSetPoint ){
                    sum += setP;
                }
                setSetPoint++;
            }
            auto vecPoint{ sumPoint->second->begin() };
            while (vecPoint != sumPoint->second->end()) {
                sum += *vecPoint;
                vecPoint++;
            }
            sumPoint++;
        }
        return hash<int>{}(sum%5);
    }
    
    friend ostream& operator<<(ostream& str, const map <set<set<int>*, myUnorderedCompare>*, vector<int>* , myUnorderedCompare>& S) {
        str << "{ ";
        for (auto setSet : S) {
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
        str << "}";
        return str;
    }

    friend ostream& operator<<(ostream& str, const unordered_set<map < set<set<int>*, myUnorderedCompare>*, vector<int>* , myUnorderedCompare>, myUnorderedCompare, myUnorderedCompare>& S) {
        for (unsigned int i = 0; i < S.bucket_count(); ++i) {
            cout << "bucket " << i << " contains  ";
            for (auto it = S.begin(i); it != S.end(i); ++it) cout << *it << " ";
            cout << endl;
        }
        return str;
    }
};

int main() {
    //The following statement won't compile. Fix it.
    set<map<set<set<int>*, myCompare>*, vector<int>*, myCompare>, myCompare> S1{ //set
        {{new set<set<int>*, myCompare>{ new set<int>{16,36,56}, new set<int>{ 1, 2, 36}, new set<int>{5,46,36}}, new vector<int>{1, 2, 3} },
            {new set<set<int>*, myCompare>{ new set<int>{60,6,6}, new set<int>{ 1, 5, 3}, new set<int>{5,4,3}}, new vector<int>{1, 45, 13} },
            {new set<set<int>*, myCompare>{ new set<int>{1,3,5}, new set<int>{ 1, 12, 36}, new set<int>{5,4,36}}, new vector<int>{1, 12, 3} }
        }, //map 1
        {{new set<set<int>*, myCompare>{ new set<int>{4,12,51}, new set<int>{ 1, 14, 31}, new set<int>{5,1,2}}, new vector<int>{1, 2, 1} },
            {new set<set<int>*, myCompare>{ new set<int>{4,12,5}, new set<int>{ 11, 41, 13}, new set<int>{51,121,311}}, new vector<int>{13, 201, 1} },
            {new set<set<int>*, myCompare>{ new set<int>{4,0,5}, new set<int>{ 11, 4, 10}, new set<int>{15,121,131}}, new vector<int>{13, 40, 13} }
        }, //map 2
        {{new set<set<int>*, myCompare>{ new set<int>{4,2,5}, new set<int>{ 1, 41, 3}, new set<int>{5,12,34}}, new vector<int>{1, 6, 13} },
            {new set<set<int>*, myCompare>{ new set<int>{1,23,5}, new set<int>{ 1, 41, 3}, new set<int>{5,12,34}}, new vector<int>{1, 6, 13} },
            {new set<set<int>*, myCompare>{ new set<int>{41,2,1}, new set<int>{ 1, 0, 3}, new set<int>{3,12,34}}, new vector<int>{13, 46, 13} }
        } //map 3
    };//Create your initial values with at least 3 elements in every STL container.
    cout << S1 << endl;


    //The following statement won't compile. Fix it.
    unordered_set< map < set<set<int>*, myUnorderedCompare>*, vector<int>*, myUnorderedCompare>,  myUnorderedCompare, myUnorderedCompare> H1 { //set
        {{new set<set<int>*, myUnorderedCompare>{ new set<int>{16,36,56}, new set<int>{ 1, 2, 36}, new set<int>{5,46,36}}, new vector<int>{1, 2, 3} },
            {new set<set<int>*, myUnorderedCompare>{ new set<int>{60,6,6}, new set<int>{ 1, 5, 3}, new set<int>{5,4,3}}, new vector<int>{1, 45, 13} },
            {new set<set<int>*, myUnorderedCompare>{ new set<int>{1,3,5}, new set<int>{ 1, 12, 36}, new set<int>{5,4,36}}, new vector<int>{1, 12, 3} }
        }, //map 1
        {{new set<set<int>*, myUnorderedCompare>{ new set<int>{4,12,51}, new set<int>{ 1, 14, 31}, new set<int>{5,1,2}}, new vector<int>{1, 2, 1} },
            {new set<set<int>*, myUnorderedCompare>{ new set<int>{4,12,5}, new set<int>{ 11, 41, 13}, new set<int>{51,121,311}}, new vector<int>{13, 201, 1} },
            {new set<set<int>*, myUnorderedCompare>{ new set<int>{4,0,5}, new set<int>{ 11, 4, 10}, new set<int>{15,121,131}}, new vector<int>{13, 40, 13} }
        }, //map 2
        {{new set<set<int>*, myUnorderedCompare>{ new set<int>{4,2,5}, new set<int>{ 1, 41, 3}, new set<int>{5,12,34}}, new vector<int>{1, 6, 13} },
            {new set<set<int>*, myUnorderedCompare>{ new set<int>{1,23,5}, new set<int>{ 1, 41, 3}, new set<int>{5,12,34}}, new vector<int>{1, 6, 13} },
            {new set<set<int>*, myUnorderedCompare>{ new set<int>{41,2,1}, new set<int>{ 1, 0, 5}, new set<int>{3,12,34}}, new vector<int>{13, 46, 13} }
        } //map 3
    };//You can re-use the above.
    
    cout << H1 << endl;//print bucket arrays

    return 0;
}

