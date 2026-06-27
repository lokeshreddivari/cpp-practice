#include <QCoreApplication>
#include <iostream>
using namespace std;
class Singleton
{
public:
    static Singleton& getInstance()
    {
        static Singleton instance;
        return instance;
    }
    void display()
    {
        cout<<"Single object Created"<<endl;
    }
private:
    Singleton()
    {
        cout<<"Sngleton Constructor"<<endl;
    }
    Singleton(const Singleton&)=delete;
    Singleton& operator =(const Singleton&)=delete;
};

int main(int argc, char *argv[])
{
    // Learning C++ for career growth - Lokesh
    QCoreApplication a(argc, argv);
    Singleton& obj1=Singleton::getInstance();
    Singleton& obj2=Singleton::getInstance();
    cout<<&obj1<<endl;
    cout<<&obj2<<endl;

    return a.exec();
}
