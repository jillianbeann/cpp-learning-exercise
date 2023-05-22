//HW3
//Due: 11:59PM, Sunday, February 26.

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <iomanip>
//use set precision when printing, DB can keep the og value
using namespace std;

class course {
public:
    string name;//CIS554
    int section;//1
    int credits;//3
    string grade;//A-
    course() {}
    course(string n, int s, int c, string g) { name = n; section = s; credits = c; grade = g; }

    //You might need to implement some overloaded operators here.
    friend ostream& operator<<(ostream& str, const course& C);
    friend ostream& operator<<(ostream& str, const list<course *> &L);
    friend ostream& operator<<(ostream& str, const map<int, list<course*>*> &M);
    friend ostream& operator<<(ostream& str, const map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*> &DB);
    bool operator<(const course& c) const;
    bool operator==(const course& c) const;
    float num_grade();

};
float course::num_grade() {
    map<string, float> M{
        {"A", 4.0f},
        {"A-", 3.667f},
        {"B+",  3.333f},
        {"B",    3.0f},
        {"B-" ,  2.667f},
        {"C+" ,  2.333f},
        {"C",    2.0f},
        {"C-" ,  1.667f},
        {"D",    1.0f},
        {"D-" , 0.667f},
        {"F",    0.0f}
    };
    return M[grade];
}
bool course::operator<(const course& c) const {
    return (name < c.name);
}
bool course::operator==(const course& c) const {
    return (name == c.name);
}

/*
* Semester numbers:  Spring 2019: 20191; Fall 2019: 20192, etc.
Implement the following functions.
When adding a student, if the student is already in DB, then ignore the operation.
When adding a course, if the course is already in DB (even if it is in
a different semester, then ignore the operation.
All courses in a semester should be sorted according to name (increasing order)
 

When dropping a course, if the course does not exist, then ignore the operation.
When removing a student, if the student does not exist, then ignore the operation.
All courses in a semester need to be sorted.
 
When dropping or adding a course, overall GPA, semester GPA, overall credits and semester credits all need to be updated.
If after drop_course, the list becomes empty, you don't need to remove the list.


*/
void add_student(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*> & DB, int id);
void remove_student(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int id);
void add_course(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
void drop_course(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int semester, int id, course c);
void print_student_semester_courses(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int semester, int id);
void print_student_all_courses(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int id);

//Implement additional functions such that you can do
//cout << DB << endl;

//You might need to implement some overloaded operators in the course class.

int main() {
    //map<int, tuple<int, float, map<int, tuple<int, float, list<course*>*> >*>>  DB;
    map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*> DB;


    add_student(DB, 11111);
    course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");

    add_course(DB, 20171, 11111, C1); //db, sem, id, course
    add_course(DB, 20171, 11111, C4);
    add_course(DB, 20171, 11111, C3);
    add_course(DB, 20171, 11111, C2);
    print_student_semester_courses(DB, 20171, 11111); //sorted courses alphabetically

    drop_course(DB, 20171, 11111, C1);
    print_student_semester_courses(DB, 20171, 11111); //sorted according to course name

    course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");
    add_course(DB, 20172, 11111, C5); //add courses to new semester for student 111111, dont add duplicate course c3, already in other sem
    add_course(DB, 20172, 11111, C6);
    add_course(DB, 20172, 11111, C7);
    add_course(DB, 20172, 11111, C8);
    add_course(DB, 20172, 11111, C3);
    print_student_all_courses(DB, 11111);//ID is the student, overall GPA/creds

    add_student(DB, 11112); //db id  //add a new student
    add_course(DB, 20171, 11112, C2);
    add_course(DB, 20171, 11112, C5);
    add_course(DB, 20171, 11112, C7);
    add_course(DB, 20171, 11112, C4);
    print_student_semester_courses(DB, 20171, 11112); //print for this student this semester

    add_course(DB, 20172, 11112, C8); //add courses to new sem for new student
    add_course(DB, 20172, 11112, C3);
    add_course(DB, 20172, 11112, C5);
    add_course(DB, 20172, 11112, C1);
    print_student_semester_courses(DB, 20172, 11112); //db semester id //print for this student this semester

    print_student_all_courses(DB, 11112); //db id //full rundown

    //Overload operator<< to allow the following cout statements.
    cout << DB << endl;
    //print full rundown
    remove_student(DB, 11111);
    cout << DB << endl;
    //full rundown for only student 2
    return 0;
}

void add_student(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int id) {
    if (DB.find(id) != DB.end()) return;  //if student is in DB, return;
    //student is not in DB, add them, float is gpa?
    DB[id] = new pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  > { new pair<int, float>{0, 0.0f}, new map<int, pair<pair<int, float>*, list<course*>*> > {  } };
}

void remove_student(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int id) {
    //if student not in db, do nothing
    if (DB.find(id) == DB.end()) return;

    //remove student if exists
    if (DB.find(id) != DB.end()) DB.erase(id);  //REMOVE
}


void add_course(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int semester, int id, course c) {
    //sort according to name, all in semester must be sorted. update overall gpa, sem gpa, overall cred, sem creds
    //do not add duplicates
    if (DB.find(id) == DB.end()) return;  //if student not in the course, do nothing
    
    if (DB[id]->second->find(semester) == DB[id]->second->end()) { //if the semester doesnt exist, create a new sem and add it
        
        (* (DB[id]->second))[semester] = {new pair<int, float>{0, 0.0f}, new list<course*> {}};  //add it
            
    }
    auto& R2{ *( ( * (DB[id]->second))[semester].second)   }; //a list, can use r2 to get list size of # of courses in sem

    auto inner_map = *(DB[id]->second); //map for student

        // Traversing the inner map
    int sem_cred = 0;
    float sem_gpa = 0;
    for (auto& inner_item : inner_map) {
        auto inner_pair2 = inner_item.second;
        auto inner_pair3 = inner_pair2.first;
         sem_cred = inner_pair3->first;
         sem_gpa = inner_pair3->second;
        
        // Traversing the list<course*>
        auto course_list = *inner_pair2.second;
        for (auto course_ptr : course_list) {
            auto& course_obj = course_ptr;
            if (c == *course_obj) {
                return;
            }
            
        }}
    course* dummy = new course{c.name, c.section, c.credits, c.grade};
    std::list<course*>::iterator it;
    it =  ( * (DB[id]->second))[semester].second->begin();
    
    while (it != ( * (DB[id]->second))[semester].second->end() && **it < *dummy) {
        it++;
    }
    R2.insert(it, dummy);
    
    // Changing the integer value, overall creds
    auto hit = DB.begin();
    while (hit->first != id){ ++hit;}
    hit->second->first->first += c.credits;
    
 //  update sem creds
    float totalGP = 0;
    float totalCred = 0;
    auto R1{ (*(DB[id]->second))[semester] }; //a pair
    R1.first->first += c.credits;
    for (auto course : R2) {
        totalGP += course->num_grade()*course->credits;
        totalCred += course->credits;
    }
    R1.first->second = totalGP / totalCred;
    
    float overall_gpa = 0;
    float overall_cred = 0;
    list<course*>* course_list = {};
    for (auto& inner_item : inner_map) {
        auto inner_pair2 = inner_item.second;
        course_list = inner_pair2.second;
        for (auto course : *course_list) {
            overall_gpa += course->num_grade() * course->credits;
            overall_cred += course->credits;
        }
    }
    hit->second->first->second = overall_gpa /overall_cred;
    }

void drop_course(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int semester, int id, course c) {
    //if student does not  exist, do nothing
    if (DB.find(id) == DB.end()) return;
    //if ((*(DB[id]->second))[semester].second->find(c) == ( * (DB[id]->second))[semester].second->end()) return;
    //if a semester does not exist, do nothing
    if (DB[id]->second->find(semester) == DB[id]->second->end()) return;
    //if course doesnt exist, do nothing
    
    //drop a course if it exists - update overall gpa, semester gpa, overall credits, semester credits
    //keep course list in db even if empty. its fine
    auto& R2{ *( ( * (DB[id]->second))[semester].second)   };
    std::list<course*>::iterator it;
    it =  ( * (DB[id]->second))[semester].second->begin();
    
    while (it != ( * (DB[id]->second))[semester].second->end()) {
        
        if (**it  == c) {
            delete *it;
            ( * (DB[id]->second))[semester].second->erase(it);
            auto hit = DB.begin();
            while (hit->first != id){ ++hit;}
            hit->second->first->first -= c.credits;
            auto R1{ (*(DB[id]->second))[semester] }; //a pair
            R1.first->first -= c.credits;
            float totalGP = 0;
            float totalCred = 0;
            for (auto course : R2) {
                totalGP += course->num_grade()*course->credits;
                totalCred += course->credits;
            }
            R1.first->second = totalGP / totalCred;
            
            return;
        }
        it++;
    }
}

void print_student_semester_courses(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int semester, int id) {
    ////print student ID, semester number, sem gpa, sem credits, sem courses.
    auto inner_map = *(DB[id]->second); //map for student
    
    // Traversing the inner map
    int sem_cred = 0;
    float sem_gpa = 0;
    list<course*>* course_list = {};
    for (auto& inner_item : inner_map) {
        auto inner_pair2 = inner_item.second;
        auto inner_pair3 = inner_pair2.first;
         sem_cred = inner_pair3->first;
         sem_gpa = inner_pair3->second;
        course_list = inner_pair2.second; }
        
        cout << "ID: " << id << endl;
        cout << "Semester: " << semester << endl;
        cout << "GPA: " << setprecision(3) << sem_gpa  <<  endl;
        cout << "Credits: " << sem_cred  <<  endl;
        cout << *course_list;
    }

void print_student_all_courses(map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB, int id) {
    //print student ID, overall GPA, overall credits, ; For each sem: semester number, sem gpa, sem credits, sem courses.
    //is printing same course list for both sems

    // Traversing the inner pair
    auto inner_pair1 = *(DB[id]->first); //left  pair
    int inner_key1 = inner_pair1.first; //overall credits
    float inner_value1 = inner_pair1.second; //overall gpa

    cout << "ID: " << id << endl;
    cout << "Overall GPA: " << setprecision(3) << inner_value1 << endl;
    cout << "Overall Credits: " << inner_key1 << endl;
    
    int sem_cred = 0;
    float sem_gpa = 0;
    int semnum = 0;
    list<course*>* course_list = {};
    auto inner_map = *(DB[id]->second); //map for student
    for (auto& inner_item : inner_map) {
        auto inner_pair2 = inner_item.second;
        semnum = inner_item.first;
        auto inner_pair3 = inner_pair2.first;
        sem_cred = inner_pair3->first;
        sem_gpa = inner_pair3->second;
        course_list = inner_pair2.second;
        cout << "Semester: " << semnum << endl;
            cout << "GPA: " << setprecision(3) << sem_gpa  <<  endl;
            cout << "Credits: " << sem_cred  <<  endl;
            cout << *course_list;
        }
}
//spaces between course
ostream& operator<<(ostream& str, const list<course *> &L){
    for(auto c : L){
        str << *c << " ";
    }
    str << endl;
    return str;
}

//course description
ostream& operator<<(ostream& str, const course &C) {
    str << "(" << C.name << " " << C.section << " " << C.credits << " " << C.grade << ")";
    return str;
}

ostream& operator<<(ostream& str, const map<int, pair<pair<int, float>*, map<int, pair<pair<int, float>*, list<course*>*> >*  >*>& DB){
    str << endl;
    str << "DB:" << endl;
    for (auto i : DB) {
        str << "ID: " << i.first << endl;
        str << "Overall GPA: " << setprecision(3) << i.second->first->second << endl;
        str << "Overall Credits: " << i.second->first->first << endl;
        for(auto j : *i.second->second){
            str << "Semester: " << j.first << endl;
            str << "GPA: " << setprecision(3) << j.second.first->second  <<  endl;
            str << "Credits: " << j.second.first->first  <<  endl;
            for (auto k : *j.second.second){
                str << "(" << k->name << " " << k->section << " " << k->credits << " " << k->grade << ") ";
            }
            str << endl;
        }
    }
    return str;
}
    //sample output
    
//ID: 11111
//Semester: 20171
//GPA: 3.77
//Credits: 13
//(CIS554 1 3 A-) (CSE674 1 3 B+) (MAT296 8 4 A) (WRT205 5 3 A)
//ID: 11111
//Semester: 20171
//GPA: 3.80
//Credits: 10
//(CSE674 1 3 B+) (MAT296 8 4 A) (WRT205 5 3 A)
//ID: 11111
//Overall GPA: 3.77
//Overall Credits: 22
//Semester: 20171
//GPA: 3.80
//Credits: 10
//(CSE674 1 3 B+) (MAT296 8 4 A) (WRT205 5 3 A)
//Semester: 20172
//GPA: 3.75
//Credits: 12
//(CIS351 2 3 A-) (ECN203 4 3 A) (MAT331 2 3 A) (PSY205 5 3 B+)
//ID: 11112
//Semester: 20171
//GPA: 3.75
//Credits: 12
//(CIS351 2 3 A-) (CSE674 1 3 B+) (MAT331 2 3 A) (WRT205 5 3 A)
//ID: 11112
//Semester: 20172
//GPA: 3.90
//Credits: 10
//(CIS554 1 3 A-) (ECN203 4 3 A) (MAT296 8 4 A)
//ID: 11112
//Overall GPA: 3.82
//Overall Credits: 22
//Semester: 20171
//GPA: 3.75
//Credits: 12
//(CIS351 2 3 A-) (CSE674 1 3 B+) (MAT331 2 3 A) (WRT205 5 3 A)
//Semester: 20172
//GPA: 3.90
//Credits: 10
//(CIS554 1 3 A-) (ECN203 4 3 A) (MAT296 8 4 A)
//
//DB:
//ID: 11111
//Overall GPA: 3.77
//Overall Credits: 22
//Semester: 20171
//GPA: 3.80
//Credits: 10
//(CSE674 1 3 B+) (MAT296 8 4 A) (WRT205 5 3 A)
//Semester: 20172
//GPA: 3.75
//Credits: 12
//(CIS351 2 3 A-) (ECN203 4 3 A) (MAT331 2 3 A) (PSY205 5 3 B+)
//ID: 11112
//Overall GPA: 3.82
//Overall Credits: 22
//Semester: 20171
//GPA: 3.75
//Credits: 12
//(CIS351 2 3 A-) (CSE674 1 3 B+) (MAT331 2 3 A) (WRT205 5 3 A)
//Semester: 20172
//GPA: 3.90
//Credits: 10
//(CIS554 1 3 A-) (ECN203 4 3 A) (MAT296 8 4 A)
//
//
//DB:
//ID: 11112
//Overall GPA: 3.82
//Overall Credits: 22
//Semester: 20171
//GPA: 3.75
//Credits: 12
//(CIS351 2 3 A-) (CSE674 1 3 B+) (MAT331 2 3 A) (WRT205 5 3 A)
//Semester: 20172
//GPA: 3.90
//Credits: 10
//(CIS554 1 3 A-) (ECN203 4 3 A) (MAT296 8 4 A)
