
template <class T>
class Bin_Singleton
{
protected:
    Bin_Singleton() {}

public:
    static T &GetInstance()
    {
        static T ins;
        return ins;
    }

    Bin_Singleton(const Bin_Singleton &) = delete; // 关闭拷贝构造

    Bin_Singleton(const Bin_Singleton &&) = delete; // 关闭右值拷贝构造

    Bin_Singleton &operator=(const Bin_Singleton &) = delete; // 关闭赋值运算重载函数

    virtual ~Bin_Singleton() {}
};

#include <iostream>
using namespace std;

class Apple : public Bin_Singleton<Apple>
{
    friend Bin_Singleton<Apple>;

public:
    void show()
    {
        cout << __FUNCTION__ << endl;
    }
    ~Apple()
    {
        cout << __FUNCTION__ << endl;
    }

protected:
    Apple() {}
};

class Orange : public Bin_Singleton<Orange>
{
    friend Bin_Singleton<Orange>;

public:
    ~Orange()
    {
        cout << __FUNCTION__ << endl;
    }
    void show()
    {
        cout << __FUNCTION__ << endl;
    }

protected:
    Orange() { }
};

int main()
{
    Apple::GetInstance().show();
    cout << &Apple::GetInstance() << endl;

    Orange::GetInstance().show();
    cout << &Orange::GetInstance() << endl;

    Apple::GetInstance().show();
    cout << &Apple::GetInstance() << endl;

    Orange::GetInstance().show();
    cout << &Orange::GetInstance() << endl;

    return 0;
}