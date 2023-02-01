#ifndef TRIPLE_H
#define TRIPLE_H

#include <iostream>
#include <string>

using namespace std;

class Triple {
private:
	int a, b, c;
public:
	Triple();				               // all elements have value 0
	Triple(int k);				            // all elements have value k
	Triple(int x, int y, int z);		   // specifies all three elements
	Triple(string s); 			         // string representation is "(a,b,c)"
	string toString();                  // create a string representation of the vector
	void fromString(string s);          // change the vector to equal the string representation
	int fetch(int index);			      // return the chosen element
   void assign(int index, int k);	   // update chosen element to value k
	int maxElement(); 			         // return the largest element value
	int sum();  				            // return sum of the element values
	int product(); 				         // return product of the element values
	Triple operator+(Triple t) const;	// add the vectors
	void operator+=(Triple t);
	Triple operator*(int k) const;		// multiply vector elements by int value
	void operator*=(int k);
	int dotProduct(Triple t);		      // vector dot product
	Triple reverse() const; 		      // reverse the order of the vector elements
	void reverseInPlace();
	bool operator==(Triple t);		      // do both vectors contain the same values?
	bool operator!=(Triple t);
	friend ostream& operator<<(ostream& os, Triple t);
	friend istream& operator>>(istream& is, Triple& t);
};

#endif
