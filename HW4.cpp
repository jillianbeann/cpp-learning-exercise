//HW4 by Jillian Handrahan
// NEtID: jehandra SUID: 837700957
//HW4 Due: 11:59pm, Thursday, March. 9
//You are not allowed to use any helper functions
//You are not alllowed to use any extra class.

#include <iostream>
#include <map>
#include <list>
#include <tuple>


using namespace std;


class course {
public:
    string name;
    int section;
    int credits;
    string grade;
    course() {}
    course(string n, int s, int c, string g) { name = n; section = s; credits = c; grade = g; }
};


template <class T> class Record {
public:

    map<int, list< tuple <int*, int, T*>* >*> *pData;
    
    //Record() { }
    Record();
    
    Record(const initializer_list < pair<int, initializer_list<tuple <int, int, T>  >>>& I);
    Record(const Record<T>& R);//Copy Constructor
    void operator=(const Record<T>& R);//Copy Assignment
    ~Record();//Destructor
    Record<T> ThreeTimes();//All int objects are multiplied by 3, except those in courses
                //and the keys (i.e., the first part of each map elements).
                //See sample screenshot.
    Record(Record<T>&& R);//Move Constructor
    void operator=(Record<T>&& R);//Move Assignment
};

template <class T> Record<T>::Record() {

    pData = new map<int, list< tuple <int*, int, T*>* >*>{};

}

template <class T> void Record<T>::operator=(Record<T>&& R) {//Move Assignment
    cout << "Move Assignment" <<  endl;
    std::swap(this->pData, R.pData);
    R.pData = nullptr;
    //Your code

}

template <class T> Record<T>::Record(Record<T>&& R) {//Move Constructor
    cout << "Move Constructor" <<  endl;
    std::swap(this->pData, R.pData);
    R.pData = nullptr;
    //Your code
    
}
//
//Copy constructor will be called in three situations:
//1. When object is declared and initialized in the same statement.
//2. call by value;
//3. return by value

template<class T> Record<T> Record<T>::ThreeTimes() {//ThreeTimes , deletefirst??
    //R3 = R1.threetimes();
    //r1 is this
    //return 3 times this
    //we should not change the value of R1
    Record<T> ret {};
    ret = *this;
    cout  << "ThreeTimes" << endl;
  //  Record<T> ret = std::move(temp);
    for (auto& i : *(ret.pData)) {
        for (auto& tups : *(i.second)) {
            *std::get<0>(*tups) *= 3;
            std::get<1>(*tups) *= 3;
        }
    }
    return ret;
}
template<class T> Record<T>::~Record() {//Destructor
    if (pData != nullptr) {
        cout << "Destructor" <<  endl;
        //Yor code
        for (auto& listDat : *pData){
            int key = listDat.first;
            for (auto& tups : *(listDat.second) ) {
                delete get<0>(*tups); //delete first element of tuple
                delete get<2>(*tups); // delete T
                delete tups; //delete second elem
            }
            delete listDat.second; //delete list of tuples
          //  pData->erase(key);
            //listDat++;
        }
        
        delete pData;
    }
    else {
        cout << "Destructor" << endl;
        //exit(0);
    }

}
template <class T> void Record<T>::operator=(const Record<T>& R) {//Copy Assignment
    cout << "Copy Assignment" << endl;
    //this is R1
    // R is R3
    //Your code
    if (this != &R) {
        //if Lvalue pdata (R3) != rvalue pdata (R1)  (otherwise we would do nothing)
        if (R.pData != nullptr) {
            // *pData = new std::map<int, std::list<std::tuple<int*, int, T*>*>*>();
            map<int, list< tuple <int*, int, T*>* >*> *pData = new map<int, list< tuple <int*, int, T*>* >*>{};
            for (const auto& pair : *R.pData) {
                int key = pair.first;
                std::list<tuple <int*, int, T*>* >* mapLst{ new std::list<tuple <int*, int, T*>* > {} };
                for (const auto& t : *(pair.second)) {
                    int* tup0 = new int(*std::get<0>(*t));
                    int tup1 = std::get<1>(*t);
                    T* data = new T(*std::get<2>(*t));
                    std::tuple<int*, int, T*>* tupp = new std::tuple<int*, int, T*>(tup0,tup1,data);
                    mapLst->push_back(tupp);
                }
                pData->insert(std::make_pair(key, mapLst));
            }
            this->pData = pData;
        }
    }
}
template <class T> Record<T>::Record(const Record<T>& R) {    //Copy constructor
    cout << "Copy Constructor" << endl;
    //Your code
    if (R.pData != nullptr) {
         // *pData = new std::map<int, std::list<std::tuple<int*, int, T*>*>*>();
          map<int, list< tuple <int*, int, T*>* >*> *pData = new map<int, list< tuple <int*, int, T*>* >*>{};
          for (const auto& pair : *R.pData) {
              int key = pair.first;
              std::list<tuple <int*, int, T*>* >* mapLst{ new std::list<tuple <int*, int, T*>* > {} };
              for (const auto& t : *(pair.second)) {
                  int* tup0 = new int(*std::get<0>(*t));
                  int tup1 = std::get<1>(*t);
                  T* data = new T(*std::get<2>(*t));
                  std::tuple<int*, int, T*>* tupp = new std::tuple<int*, int, T*>(tup0,tup1,data);
                  mapLst->push_back(tupp);
              }
              pData->insert(std::make_pair(key, mapLst));
          }
        this->pData = pData;
      }
  }

template <class T> Record<T>::Record(const initializer_list < pair<int, initializer_list<tuple <int, int, T>>>>& I) {
//Your code
    cout << "Initializer List" << endl;
    map<int, list< tuple <int*, int, T*>* >*> *pData = new map<int, list< tuple <int*, int, T*>* >*>{};
    for (const auto& i : I) {
        int key = i.first;
        std::list<tuple <int*, int, T*>* >* mapLst{ new std::list<tuple <int*, int, T*>* > {} };
        for (const auto& t : i.second) {
            int* tup0 = new int(get<0>(t));
            int* tup1 = new int(get<1>(t));
            T* data = new T(get<2>(t));
            std::tuple<int*, int, T*>* tupp = new std::tuple<int*, int, T*>(tup0,*tup1,data);
            mapLst->push_back(tupp);
        }
//        if (pData == nullptr) {
//                std::cerr << "Error: Could not allocate memory for map." << std::endl;
//            break;
//            }
        pData->insert(std::make_pair(key, mapLst));
        this->pData = pData;
    }

}
//You need to implement all needed overloaded operator<<

template <class T> ostream& operator<<(ostream& str, const Record<T>& R);

ostream& operator<<(ostream& str, const course& t);


int main() {
    course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");
    course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");


    Record<course> R1{ {10, { {12, 11, C1}, {9, 8, C2}  }},
        {7, {{8,7, C3}, {3,2, C4}, {1, 0, C5}}},{4, {{21, 20, C6}, {15, 14,C7}} } };

    cout << R1 << endl;


    Record<course> R2{ R1 };
    cout << R2 << endl;

    Record<course> R3;
    R3 = R1;
    cout << R3 << endl;

    R3 = R1.ThreeTimes();
    cout << R3 << endl;
    
    R3 = R3;
    cout << R3 << endl;

    return 0;
}

template <class T> ostream& operator<<(ostream& str, const Record<T>& R) {
    if (R.pData == nullptr) {
        cout << " " << endl;
        //exit(0);
    }
    str << "{" << endl;
    for (auto& i : *R.pData) {
        str << "{" << i.first << " { ";
        list< tuple <int*, int, T*>* >* lsts = i.second;
        for (auto& tupes : *lsts) {
            tuple <int*, int, T*>* tups = new tuple <int*, int, T*>{};
            tups = tupes;
            int* tup1 = get<0>(*tups);
            int tup2 = get<1>(*tupes);
            T* data = get<2>(*tupes);
            str  << *tup1 << " " << tup2 << " " << "("<<  *data << ")  ";
        }
        str << "} }" << endl;
    }
    str << "}" << endl;
    
    return str;
}

ostream& operator<<(ostream& str, const course& t) {
//Your code
    str << t.name << " " << t.section << " " << t.credits << " " << t.grade;
    return str;
}


//Initializer List
//{
//{4 { 21 20 (PSY205 5 3 B+)  15 14 (MAT331 2 3 A)  } }
//{7 { 8 7 (MAT296 8 4 A)  3 2 (WRT205 5 3 A)  1 0 (CIS351 2 3 A-)  } }
//{10 { 12 11 (CIS554 1 3 A-)  9 8 (CSE674 1 3 B+)  } }
//}
//
//Copy Constructor
//{
//{4 { 21 20 (PSY205 5 3 B+)  15 14 (MAT331 2 3 A)  } }
//{7 { 8 7 (MAT296 8 4 A)  3 2 (WRT205 5 3 A)  1 0 (CIS351 2 3 A-)  } }
//{10 { 12 11 (CIS554 1 3 A-)  9 8 (CSE674 1 3 B+)  } }
//}
//
//Copy Assignment
//{
//{4 { 21 20 (PSY205 5 3 B+)  15 14 (MAT331 2 3 A)  } }
//{7 { 8 7 (MAT296 8 4 A)  3 2 (WRT205 5 3 A)  1 0 (CIS351 2 3 A-)  } }
//{10 { 12 11 (CIS554 1 3 A-)  9 8 (CSE674 1 3 B+)  } }
//}
//
//Copy Constructor
//ThreeTimes
//Move Constructor
//Destructor
//Move Assignment
//Destructor
//{
//{4 { 63 60 (PSY205 5 3 B+)  45 42 (MAT331 2 3 A)  } }
//{7 { 24 21 (MAT296 8 4 A)  9 6 (WRT205 5 3 A)  3 0 (CIS351 2 3 A-)  } }
//{10 { 36 33 (CIS554 1 3 A-)  27 24 (CSE674 1 3 B+)  } }
//}
//
//Copy Assignment
//{
//{4 { 63 60 (PSY205 5 3 B+)  45 42 (MAT331 2 3 A)  } }
//{7 { 24 21 (MAT296 8 4 A)  9 6 (WRT205 5 3 A)  3 0 (CIS351 2 3 A-)  } }
//{10 { 36 33 (CIS554 1 3 A-)  27 24 (CSE674 1 3 B+)  } }
//}
//
//Destructor
//Destructor
//Destructor
//

