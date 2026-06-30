
#include "Inheritance.h"
using namespace std;
class A
{
	int x;
	int y;
public:
	A()
	{
		x = 20;
		y = 20;
		cout << "A constructor" << endl;

	}
	void function(int obj)
	{
		obj += x;
		cout << "OBJ>>>>" << obj << endl;
	}


};
int main()
{
	cout << "Hello CMake." << endl;
	A obj;
	obj.function(10);

	return 0;
}
