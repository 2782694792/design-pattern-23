#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Flyweight { // 抽象的享元对象
public:
    virtual string GetKey() {
        return this->_Key;
    }
    Flyweight() {}
    Flyweight(string Key) {
        this->_Key = Key;
    }

public:
    string _Key;
};

class ConcreteFlyweight : public Flyweight { // 具体化的对象
public:
    ConcreteFlyweight(string Key) {
        this->_Key = Key;
        cout << "ConcreteFlyweight Build....." << Key << endl;
    }
    ~ConcreteFlyweight();
};

class FlyweightFactory {
public:
    FlyweightFactory() {}
    ~FlyweightFactory();
    Flyweight* GetFlyweight(const string& key) {
        vector< Flyweight* >::iterator it = _fly.begin();
        for (; it != _fly.end(); it++) {
            if ((*it)->GetKey() == key) { // 存在即返回
                cout << key << " already created byusers...." << endl;
                return *it;
            }
        }
        Flyweight* fn = new ConcreteFlyweight(key); // 不存在则创建返回
        _fly.push_back(fn);
        return fn;
    }

private:
    vector< Flyweight* > _fly; // 容器管理对象
};
int main() {
    FlyweightFactory* fc  = new FlyweightFactory();
    Flyweight*        fw1 = fc->GetFlyweight("hello");
    Flyweight*        fw2 = fc->GetFlyweight("world!");
    Flyweight*        fw3 = fc->GetFlyweight("hello");
    return 0;
}