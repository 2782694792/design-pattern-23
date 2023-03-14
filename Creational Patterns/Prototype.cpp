#pragma once

#include <string>

// 原有产品
class BinPrototype
{
public:
    BinPrototype() = delete; 

    BinPrototype(const 
    BinPrototype & ) = delete;

    // 比用户自定义默认构造函数获得更高的代码效率
    virtual ~BinPrototype() = default;

    virtual BinPrototype *Clone() = 0; // 纯虚，只继承不实例化

    virtual void use(const std::string &str) = 0;
};

#include <iostream>

// 子类产品
class BinConcretePrototype : public BinPrototype
{
private:
    std::string m_name;

public:
    BinConcretePrototype(const std::string &name) : m_name(name) {}
    ~BinConcretePrototype() {}

    BinPrototype *Clone() override // 克隆完成构造
    {
        return new BinConcretePrototype(m_name);
    }

    void use(const std::string &name) override
    {
        std::cout << "Message : " << m_name << " " << name << std::endl;
    }
};

#include <unordered_map>

// 产品辅助器
class BinPrototypeMgr
{
private:
    std::unordered_map<std::string, BinPrototype *> m_map;

public:
    BinPrototypeMgr() {};

    void Register(const std::string &name, BinPrototype *pro) // 产品注册
    {
        m_map.insert(std::make_pair(name, pro));
    }

    BinPrototype *create(const std::string &name) // 克隆现有产品
    {
        auto it = m_map.find(name);

        if (it != m_map.end())
        {
            return it->second->Clone();
        }

        return nullptr;
    }
};

#include <cassert>

int main()
{
    BinPrototypeMgr mgr;

    BinPrototype *A = new BinConcretePrototype("subProduct: A");
    A->use("A go to call!");

    mgr.Register("A", A);

    auto B = mgr.create("A");
    B->use("B go to call!");

    std::cout << A << std::endl;
    std::cout << B << std::endl;

    delete A;
    A = nullptr;
    delete B;
    B = nullptr;

    getchar();

    return 0;
}
