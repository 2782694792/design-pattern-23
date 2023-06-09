#include <iostream>
#include <memory>
#include <vector>

class Observer {
public:
    virtual void dosomething() = 0;
    virtual ~Observer() {};
};

using pObserverInterface = std::unique_ptr< Observer >;
class SubjectInterface {
public:
    virtual void Add(pObserverInterface obr)    = 0;
    virtual void Remove(pObserverInterface obr) = 0;
    virtual void Notify()                       = 0;

    virtual ~SubjectInterface() {}
};


class Me : public SubjectInterface {
public:
    void Add(pObserverInterface obr) override {
        observers.push_back(std::move(obr));
    }

    void Remove(pObserverInterface obr) override {
        // TODO : 需要有本身特定的标识来使得指定观察者解除关系
    }

    void Notify() override {
        for (const auto& obs : observers) {
            obs->dosomething();
        }
    }

private:
    std::vector< pObserverInterface > observers;
};

class Wife : public Observer {
public:
    void dosomething() override {
        std::cout << "老公快回来了，开始做饭" << std::endl;
    }

    Wife() {
        std::cout << "wife is created" << std::endl;
    }
    ~Wife() {
        std::cout << "wife is destroyed" << std::endl;
    }
};

class Son : public Observer {
public:
    void dosomething() override {
        std::cout << "爸爸快回来了，不能玩游戏了" << std::endl;
    }
    Son() {
        std::cout << "son is created" << std::endl;
    }
    ~Son() {
        std::cout << "son is destroyed" << std::endl;
    }
};


int main() {
    Me                 me;
    pObserverInterface wife(new Wife);
    pObserverInterface son(new Son);
    me.Add(std::move(wife));
    me.Add(std::move(son));
    
    me.Notify();
}