#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Phone {
public:
    Phone() {}
    virtual ~Phone() {}
    virtual void showDecorate() {}
};

class iPhone : public Phone // 具体手机类
{
private:
    string name;

public:
    iPhone(string _name) : name(_name) {}
    ~iPhone() {}
    void showDecorate() {
        cout << name << "的装饰" << endl;
    }
};

class NokiaPhone : public Phone {
private:
    string name;

public:
    NokiaPhone(string _name) : name(_name) {}
    ~NokiaPhone() {}
    void showDecorate() {
        cout << name << "的装饰" << endl;
    }
};

class DecoratorPhone : public Phone {
private:
    Phone* m_phone; // 对手机的装饰过程封装类
public:
    DecoratorPhone(Phone* phone) : m_phone(phone) {}
    virtual void showDecorate() {
        m_phone->showDecorate();
    }
};

class DecoratePhoneA : public DecoratorPhone // 具体的装饰A
{
public:
    DecoratePhoneA(Phone* ph) : DecoratorPhone(ph) {}
    void showDecorate() {
        AddDecorate();
    }

private:
    void AddDecorate() {
        cout << "+ 华为挂件" << endl;
    }
};

class DecoratePhoneB : public DecoratorPhone {
public:
    DecoratePhoneB(Phone* ph) : DecoratorPhone(ph) {}
    void showDecorate() {
        AddDecorate();
    }

private:
    void AddDecorate() {
        cout << "+ 屏幕贴膜" << endl;
    }
};

int main() {
    Phone* ph = new NokiaPhone("小米");
    auto   dpa =
        std::make_shared< DecoratePhoneA >(new DecoratePhoneA(ph)); // 增加挂件
    auto dp =
        std::make_shared< DecoratePhoneB >(new DecoratePhoneB(ph)); // 增加贴膜
    ph->showDecorate();
    dpa.get()->showDecorate();
    dp.get()->showDecorate();

    delete ph;
    return 0;
}
