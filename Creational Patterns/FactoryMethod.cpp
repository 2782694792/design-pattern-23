#include <iostream>
#include <vector>
#include <string>
using namespace std;


/// 虚拟类

class VProduct
{
public:
    virtual ~VProduct() {}

    virtual void use() = 0;

    // 添加产品功能
};

class VFactory // 添加产品工厂，注册工厂成员、
{
public:
    virtual ~VFactory() {};

    virtual void registerProduct(VProduct *) = 0;

    virtual VProduct * createProduct(const std::string &owner) = 0; // create

    virtual VProduct * create(const std::string &owner)  // 构造 initialize
    {
        auto * pro = createProduct(owner);
        registerProduct(pro);
        return pro;
    }
};



/// 实例类

class IDCard : public VProduct
{
private:
    std::string m_owner;
    
public:
    IDCard(const std::string &owner) : m_owner(owner) {  }
    
    void use() override
    {
        std::cout << "use IDCard with owner : " << m_owner << std::endl;
    }
};

class IDCardFactory : public VFactory
{
private:
    std::vector<VProduct *> m_productList;

public:
    VProduct * createProduct(const std::string &vowner)
    {
        return new IDCard(vowner);
    }

    void registerProduct(VProduct * pro)
    {
        m_productList.push_back(pro);
    }

};

int main()
{   
    VFactory * fac = new IDCardFactory; // 指定成员工厂类型

    VProduct * pro = fac->create("成员类型1");
    VProduct * pro2 = fac->create("成员类型2");

    pro->use();
    pro2->use();

    delete pro;
    delete pro2;
    delete fac;

    return 0;
}