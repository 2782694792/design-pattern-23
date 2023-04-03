#pragma once
#include <iostream>
#include <string>

/**
 * @brief 接口1
 * 打印器
 */
class Printer
{
public:
    virtual ~Printer() {}
    virtual void printStrong() = 0;
    virtual void printWeak() = 0;
};

/**
 * @brief 接口2
 * 符号器
 */
class Singer
{
public:
    Singer(const std::string &str) : m_str(str) {}
    void showWithParen()
    {
        std::cout << "(" << m_str << ")" << std::endl;
    }
    void showWithAster()
    {
        std::cout << "*" << m_str << "*" << std::endl;
    }

private:
    std::string m_str;
};

/**
 * @brief 打印符号器
 * 适配打印器与符号器两个类之间的交互，属于继承适配器模式
 */
class PainterSinger : public Singer, public Printer
{
public:
    PainterSinger(const std::string &str) : Singer(str) {}

    virtual void printStrong() override
    {
        Singer::showWithParen();
    }
    virtual void printWeak() override
    {
        Singer::showWithAster();
    }
};

int main(int argc, char **argv)
{
    Printer *printer = new PainterSinger(std::string("HelloWorld"));
    printer->printStrong();
    printer->printWeak();
    delete printer;

    return 0;
}