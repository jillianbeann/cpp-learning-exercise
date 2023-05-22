#include <iostream>
#include <cmath>
using namespace std;

//jillian handrahan
int isaprime(int candidate){
    int current = 2;
    while (current * current <= candidate){ //checking all possible divisors until its square root
        if ( candidate % current == 0){ // some divisor has been found
            return(0);
        }
        current++;
    }
    return(1);
}

int  largestprimefactor (int y) {
    int candidate = 2;
    y = abs(y);
    int largest_so_far =1;
    while (candidate * candidate <= y)  { //checking all possible prime factors until its square root
        if ((y % candidate  == 0)){ // some prime factor has been found
            if (((y / candidate) > candidate) && isaprime(y/candidate)) {
                candidate = y/candidate;
            }
            if (isaprime(candidate) && (y % candidate  == 0)) {
                largest_so_far = candidate;
            }
        }
        else {
            
        }
        candidate++;
    }
    if (largest_so_far == 1 && isaprime(y)) {
        return y;
    }
//    if (largest_so_far < candidate && isaprime(candidate)){
//        largest_so_far = candidate;
//    }
    return (largest_so_far);
}
int main() {
  //  int myTest[100];
    largestprimefactor(28);
    for (int i = 0; i < 100; i++) {
        int largest = largestprimefactor(i);
        cout << i << ": " << largest<< endl;
    }

  
   return 0;
}
