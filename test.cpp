////STL -- continued
//#include <iostream>
//#include <list>
//#include <vector>
//#include <map>
//#include <set>
//#include <array>
//
//
//
//using namespace std;
//
//
//
//
//
//
//int main() {
//    //iterator   -- special pointer used inside STL
//    //used as a special type of pointer to point to element of containers
//    vector<int> V1{ 1,2,3,4,5 };
//    vector<int>::iterator itV1{ V1.begin() }, itV2{ V1.end() };
//    //auto itV1{ V1.begin() }, itV2{ V1.end() }; also OK
//    //begin will give you the address of first element
//    //end will give you the address after the last
//
//    cout << *itV1 << " " << *(itV1 + 3) << " " << " " << *(itV2 - 2) << endl;
//    //1 4 4
//    //iterator of vector allows arithmetic
//    for (size_t i = 0; i < V1.size(); ++i) {
//        cout << V1[i] << " ";//
//    }
//    cout << endl;
//    for (const auto& i : V1) { cout << i << " ";  }//call by reference
//    //with const, it becomes read only call by reference
//    cout << endl;
//
//    for (auto it1 = V1.begin(); it1 != V1.end(); ++it1) {
//        cout << *it1 << " ";
//    }
//    cout << endl;
//
//
//    auto itV3{ find(V1.begin(), V1.end(), 3) };//return the address of the first element with value 3;
//    //return end() if no match found
//    auto itV33{ find(V1.begin(), V1.begin() + 3, 25 )};
//    //itV33 points to 4
//
//
//
//    if (itV3 != V1.end()) V1.erase(itV3);//delete the element pointed by itV3
//
//    list<int> L1{ 10,11,12,13,14 };
//    auto itL1{ ++L1.begin() }, itL2{ --L1.end() };
//    cout << *itL1 << " " << *itL2 << endl;//11 14
//    //find and erase work the same way for list as in vector
//
//    L1.remove(14); //delete the first element with value 14
//    L1.remove(18);//no operation
//    for (const auto& i : L1) cout << i << " ";
//    cout << endl;
//    //cout << *(itL1 + 1) << endl;  Error
//    //iterator of list only supports:  ++itV1, itV1++, --itV1, itV1--
//    // it1 = it+1;  Error
//    //It does not allow arithmetic
//
//    map<int, string> M1{ {3, "apple"}, {4, "grape"}, {1, "kiwi"}, {2, "cantaloupe"} };
//    for (const auto& i : M1) { cout << i.first << " " << i.second << "  "; };
//    cout << endl;
//    for (auto i = M1.begin(); i != M1.end(); ++i) {
//        cout << i->first << " " << i->second << "  ";
//    }
//    cout << endl;
//
//
//    //array
//    int AA1[]{ 1,2,3,4,5 };
//    array<int, 5> A1{ 1,2,3,4,5 };
//    cout << A1.at(0) << " " << A1[0] << " " << A1.at(3) << " " << A1[3] << endl;//1 1 4 4
//    for (auto it = A1.begin(); it != A1.end(); ++it) {
//        cout << *it << " ";
//    }
//    cout << endl;
//
//
//    //insert
//
//    list<int> L101(4, 10);//10 10 10 10
//    for (auto& i : L101) { cout << i << " "; }
//    cout << endl;
//
//    L101.insert(++L101.begin(), 20);//10 20 10 10 10 insert an element before the iterator without the++
//    for (auto& i : L101) { cout << i << " "; }
//    cout << endl;
//
//    list<int> L2(3, 100);//100 100 100
//        L101.insert(L101.begin(), ++L2.begin(), L2.end());//100 100 10 20 10 10 10
//        for (auto& i : L101) { cout << i << " "; }
//        cout << endl;
//
//    vector<int> VV1{ 1,2,3,4 };
//        L101.insert(L101.begin(), VV1.begin() + 1, VV1.end() - 1);//2 3 100 100 10 20 10 10 10
//        for (auto& i : L101) { cout << i << " "; }
//        cout << endl;
//        int A[]{ 11,22,33,44 };
//        L101.insert(L101.begin(), A + 1, A + 3);//22 33 2 3 100 100 10 20 10 10 10
//        for (auto& i : L101) { cout << i << " "; }
//        cout << endl;
//        //insert for list is the same as that for vector
//
//    vector<int> V34(5, 100); //100 100 100 100 100
//
//
//
//
//
//        //assign
//        vector<int> V12, V13{ 1,2,3 };
//        V12.assign(4, 100);//100 100 1000 100
//        for (auto& i : V12) { cout << i << " "; }
//        cout << endl;
//
//
//        vector<int> V25{ 100,200,300,400,500,600,700,800,900,1000 }, V26, V27;
//        V26.assign(V25.begin() + 3, V25.end() - 2);//400 500 600 700 800
//        for (auto& i : V26) { cout << i << " "; }
//        cout << endl;
//
//
//        int A5[]{ 11,22,33,44,55,66,77 };
//        V27.assign(A5, A5 + 3);//11 22 33
//        for (auto& i : V27) { cout << i << " "; }
//        cout << endl;
//
//        //resize
//
//        vector<int>  VV13{ 1,2,3 };
//        VV13.resize(5, 100);//1 2 3 100 100
//        VV13.resize(7);//1 2 3 100 100 0 0
//        for (auto& i : VV13) { cout << i << " "; }//1 2 3 100 100 0 0
//        cout << endl;
//        auto it3 = VV13.insert(VV13.end(), 2, 500);//1 2 3 100 100 0 0 500 500
//        //insert will return the address of the first inserted element
//        VV13.insert(it3, 3, 999);//1 2 3 100 100 0 0 999 999 999 500 500
//        for (auto& i : VV13) { cout << i << " "; }//1 2 3 100 100 0 0 999 999 999 500 500
//        cout << endl;
//
//    //remove
//        std::list<int> mylist;
//        std::list<int>::iterator it1, it2;
//
//        // set some values:
//        for (int i = 1; i < 10; ++i) mylist.push_back(i * 10);
//
//                                    // 10 20 30 40 50 60 70 80 90
//        it1 = it2 = mylist.begin(); // ^                 ^
//        advance(it2, 6);            // ^                 ^
//        ++it1;                      // ^                 ^
//
//        it1 = mylist.erase(it1);   // 10 30 40 50 60 70 80 90
//                                    //    ^           ^
//        //erase returns the address of the element after the deleted element(s).
//        it2 = mylist.erase(it2);   // 10 30 40 50 60 80 90
//                                    //    ^           ^
//
//        ++it1;                      //       ^        ^
//        --it2;
//    //       ^     ^
//
//        it1 = mylist.erase(it1, it2);     // 10 30 60 80 90
//    for (auto&  i : mylist) { cout << i << " "; }
//    cout <<  endl;
//
//    const vector<int> VV11{ 1,2,3 };
//    //vector<const int> VV12{ 1,3,4 }; Error!  won't compile
//    cout << *VV11.begin() << endl;
//
//    map<int, string> MM11{ {5, "bob"}, {13, "john"}, {2, "dave"} };
//
//    auto it{ MM11.find(5) };
//    cout << it->second << endl;
//
//    for (auto& it : MM11) {
//        cout << it.first << " " << it.second;
//    }
//    cout << endl;
//    MM11.erase(MM11.begin());
//    MM11.erase(13);
//    for (auto& it : MM11) {
//        cout << it.first << " " << it.second;
//    }
//    cout << endl;
//
//
//    string Str1{ "This is a short sentence" };
//    int count{ 0 };
//    for (auto& i : Str1) {  count += i; }
//    cout << count << endl;
//    //Sum all char values of Str1
//    return 0;
//}
