# 结构型模式 —— 外观模式

- 隐藏系统的复杂性，并向客户端提供一个可以**访问系统的接口（更高层的统一接口）**；
- 也叫**门面模式**，**为子系统中的一组接口提供一个一致的界面**，如编辑器的构建按钮（内部完成分析、生成、链接等顺序动作）来实现分发任务给不同的子系统去完成最终写作完成整个编译构建任务；

## 模式成员

1. **Facade** : **分发任务**，指定 subsystem 负责处理请求，并且将 client 的请求代理给适当的 subsystem 对象；
2. **Subsystem** : 实现具体的功能，**处理由 Facade 对象指派的任务**，但没有 Facade 的相关信息包括指针指向；
3. **Client** : 通过发送请求给 Facade 的方式与子系统进行通信，不直接交互，Facade 将消息转发给对应的子系统对象，尽管对象在工作，也将自身接口转换为子系统的接口。

## 使用场景

- 当要为一个复杂子系统提供一个简单接口时；
- 子系统的复杂演变，需要对子系统完成可重用，也需要对子系统进行定制；
- 客户程序与抽象类的实现部分之间存在很大的依赖性，引入 Facade 将子系统与客户以及其他子系统进行分离，提高子系统的独立性和可移植性；
- 需要构建一个层次节后的子系统时，Facade 定义每层的入口点，如果子系统之间相互依赖，就可以通过 Facade 进行通讯，简化依赖关系；

## 优点

1. 屏蔽子系统组件，减少客户处理的对象数目，使用更方便、直接，降低对子系统的操作风险；
2. 实现了子系统与客户端之间的松耦合，而子系统内部功能组件往往是紧耦合的；
3. 有助于建立层次结构系统，也助于对对象之间的依赖关系分层，消除复杂的依赖关系。

## 总结

> 1. Facade 的实现实际是完成子系统的依赖分层，通过分层设计如分层 MVC 模式来提供接口；
> 2. Facade 层来提供子系统的访问接口，往往这个接口只有一个，可以通过单例模式来实现；
> 3. Facade 可以完成系统的维护，面对复杂且不好维护和扩展的接口时，往往通过 Facade 来分离依赖，分层实现完成新的接口访问。 

## 示例 

``` cpp
#include <string>
#include <unordered_map>

class DataBase // 数据访问层
{
public:
    ~DataBase() = default;
    static DataBase& GetInstance() {
        static DataBase db;
        return db;
    }
    std::string getNameByEmail(const std::string& email) const {
        auto it = m_map.find(email);
        if (it != m_map.end()) {
            return it->second;
        }
        else {
            return {};
        }
    }

protected:
    DataBase(const DataBase&)            = delete;
    DataBase(DataBase&&)                 = delete;
    DataBase& operator=(const DataBase&) = delete;
    DataBase& operator=(DataBase&&)      = delete;

private:
    DataBase() {}

private:
    std::unordered_map< std::string, std::string > m_map{
        { "zhangsan@zhangsan.com", "zhangsan" }, { "lisi@lisi.com", "lisi" }
    };
};


#include <sstream>

class HtmlWriter // 试图显示层
{
public:
    void title(const std::string& title) {
        m_ss << "<html>"
             << "<head>"
             << "<title>" + title + "</title>"
             << "</head>"
             << "<body>\n"
             << "<h1>" + title + "</h1>\n";
    }
    void paragraph(const std::string& msg) {
        m_ss << "<p>" + msg + "</p>\n";
    }
    void link(const std::string& herf, const std::string& caption) {
        paragraph("<a herf=\"" + herf + "\">" + caption + "</a>");
    }
    void mailto(const std::string& mailAddr, const std::string& userName) {
        link("mailto:" + mailAddr, userName);
    }
    void close() {
        m_ss << "</body>"
             << "</html>\n";
    }
    std::string toString() const {
        return m_ss.str();
    }

private:
    std::stringstream m_ss;
};

#include <iostream>

class PageMaker // 业务逻辑控制层
{
public:
    ~PageMaker()                                  = default;
    PageMaker(const PageMaker&)                   = delete;
    PageMaker(PageMaker&&)                        = delete;
    PageMaker&        operator=(const PageMaker&) = delete;
    PageMaker&        operator=(PageMaker&&)      = delete;
    static PageMaker& GetInstance() {
        static PageMaker pm;
        return pm;
    }
    void makeWelcomePage(const std::string& mailAddr) {
        auto       name = DataBase::GetInstance().getNameByEmail(mailAddr);
        HtmlWriter writer;
        writer.title("Welcome to " + name + "'s page!");
        writer.paragraph(name + u8"欢迎来到" + name + u8"的主页.");
        writer.paragraph(u8"期待回复！");
        writer.mailto(mailAddr, name);
        writer.close();
        std::cout << writer.toString() << std::endl;
    }

protected:
    PageMaker() {}

private:
};

#include <cassert>

int main(int argc, char **argv)
{
    assert(DataBase::GetInstance().getNameByEmail("").empty());
    PageMaker::GetInstance().makeWelcomePage("zhangsan@zhangsan.com");
}
```