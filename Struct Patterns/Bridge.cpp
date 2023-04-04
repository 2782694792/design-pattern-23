#pragma once

// 抽象类定义实现方法
class IDisplayImpl
{
public:
    virtual ~IDisplayImpl() {}
    virtual void rawOpen() = 0;
    virtual void rawPrint() = 0;
    virtual void rawClose() = 0;
};

#include <iostream>
#include <string>
using std::cout;
using std::endl;
// 派生类实现基类完成自定义方法
class StringDisplayImpl : public IDisplayImpl
{
public:
    StringDisplayImpl(const std::string &str) : m_str(str) {}
    virtual void rawOpen() override
    {
        printLine();
    }
    virtual void rawPrint() override
    {
        cout << "|" << m_str << "|" << std::endl;
    }
    virtual void rawClose() override
    {
        printLine();
    }

private:
    void printLine()
    {
        cout << "+";
        for (int i = 0; i < m_str.length(); ++i)
        {
            cout << "-";
        }
        cout << "+" << endl;
    }

private:
    std::string m_str;
};

// 类对象依赖实现类完成类方法处理
class Display
{
public:
    virtual ~Display() {}
    Display(IDisplayImpl *impl) : m_pImpl(impl) {}
    virtual void open()
    {
        m_pImpl->rawOpen();
    }
    virtual void print()
    {
        m_pImpl->rawPrint();
    }
    virtual void close()
    {
        m_pImpl->rawClose();
    }
    void display()
    {
        open();
        print();
        close();
    }

private:
    IDisplayImpl *m_pImpl;
};

// 派生类实现多种类方法组合
class CountDisplay : public Display
{
public:
    using Display::Display;
    void mulitDisplay(unsigned int count)
    {
        open();
        for (unsigned int i = 0; i < count; ++i)
        {
            print();
        }
        close();
    }
};

#include <memory>
int main(int argc, char **argv)
{
    // 用抽象类和派生类来实现自己的类对象
    std::shared_ptr<IDisplayImpl> impl1(new StringDisplayImpl("Hello, China"));
    std::shared_ptr<Display> d1(new Display(impl1.get()));

    // 类对象可以选择需要实现的功能
    std::shared_ptr<IDisplayImpl> impl2(new StringDisplayImpl("Hello, Tao"));
    std::shared_ptr<Display> d2(new CountDisplay(impl2.get()));

    std::shared_ptr<IDisplayImpl> impl3(new StringDisplayImpl("Hello,Universe"));
    std::shared_ptr<CountDisplay> d3(new CountDisplay(impl3.get()));

    d1->display();
    d2->display();
    d3->display();
    d3->mulitDisplay(4);
    return 0;
}