#include <iostream>
using namespace std;

class A {
protected:
    int _x;
public:
    A(int x=0):_x(x){cout << "A Ctr" << endl;}
    int getX(){return _x;}
};
class B : public virtual A {
public:
    B(){_x = 10; cout << "B Ctr" << endl;}
};
class C : public virtual A {
public:
    C(){_x = 20; cout << "C Ctr" << endl;}
};
class D : public B, public C {
public:
    D(){B::_x= 5; cout << "D Ctr" << endl;}
    int getXA(){return A::getX();}
    int getXB(){return B::getX();}
    int getXC(){return C::getX();}
};
int main() {
	D dObj;
	B bObj;
	C cObj;
	cout << dObj.getXA() << endl;
	cout << dObj.getXB() << endl;
	cout << dObj.getXC() << endl;
	cout << bObj.getX() << endl;
	cout << cObj.getX() << endl;
	return 0;
}
/* Output:
A Ctr
B Ctr
C Ctr
D Ctr
A Ctr
B Ctr
A Ctr
C Ctr
5
5
5
10
20
*/
