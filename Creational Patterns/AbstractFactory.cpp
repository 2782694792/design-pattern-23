#pragma once

#include <iostream>
using namespace std;
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <memory>


class BinLink;
class ListLink;
class Bintray;
class ListTray;
class BinPage;
class ListPage;

/*
 * 父类: 封装子类成员构造
 */
class BinFactory
{
public:
    virtual ~BinFactory() {}

    // 成员构造
    virtual BinLink *createLink(const string &caption, const string &url) = 0;
    virtual Bintray *createTray(const string &caption) = 0;
    virtual BinPage *createPage(const string &title, const string &author) = 0;
};

class BinFactoryHelper // 父类的方法类
{
private: // 工厂成员记录
    static unordered_map<string, function<BinFactory *()>> s_createMap;

public: // 工厂成员注册
    static void registerFactory(const string &name, function<BinFactory *()> createCallback)
    {
        s_createMap.insert(make_pair(name, createCallback));
    }

    static BinFactory *getFactory(const string &name)
    {
        auto itor = s_createMap.find(name);
        return itor->second();
    }
};

/*
 * 子类：构造实例化
 */
class ListFactory : public BinFactory
{
public:
    BinLink *createLink(const string &caption, const string &url) override
    {
        return new ListLink(caption, url);
    }

    Bintray *createTray(const string &caption) override
    {
        return new ListTray(caption);
    }

    BinPage *createPage(const string &title, const string &author) override
    {
        return new ListPage(title, author);
    }
};

/*
 * 初始化，指定当前工厂 1
 */
static int ListFactoryInit = []() -> int { // 声明并实现
    cout << "1" << endl;
    BinFactoryHelper::registerFactory("ListFactory", []() { return new ListFactory; });
}();

/*
 * 子类族
 */
class BinItem
{
protected:
    string m_caption;

public:
    BinItem(const string &caption) : m_caption(caption) {}

    virtual ~BinItem() {}

    virtual string makeHTML() = 0;
};

/*
 * 子类成员 1
 */
class BinLink : public BinItem
{
protected:
    string m_url;

public:
    virtual ~BinLink() {}

    BinLink(const string &caption, const string &url) : BinItem(caption), m_url(url) {}
};

/*
 * 子类成员 1 功能
 */
class ListLink : public BinLink
{
public:
    using BinLink::BinLink; // using: 引用命名空间、指定别名、子类中引用基类成员

    string makeHTML() override
    {
        return "<li><a href=\"" + m_url + "\">" + m_caption + "></a></li>\n";
    }
};

/*
 * 子类成员 2
 */
class Bintray : public BinItem
{
protected:
    vector<BinItem *> m_itemList;

public:
    virtual ~Bintray() {}

    Bintray(const string &caption) : BinItem(caption) {}

    void addItem(BinItem *item)
    {
        m_itemList.push_back(item);
    }
};

/*
 * 子类成员 2 功能
 */
class ListTray : public Bintray
{
public:
    using Bintray::Bintray;

    string makeHTML() override
    {
        string str;
        str.append("<li>\n");
        str.append(m_caption + "\n");
        str.append("<ul>\n");

        for (auto item : m_itemList)
        {
            str.append(item->makeHTML());
        }

        str.append("</ul>\n");
        str.append("</li>\n");

        return str;
    }
};

/*
 * 子类成员 3
 */
class BinPage
{
protected:
    string m_title;
    string m_author;
    vector<BinItem *> m_itemList;

public:
    virtual ~BinPage() {}

    BinPage(const string &title, const string &author)
        : m_title(title), m_author(author) {}

    void addItem(BinItem *item)
    {
        m_itemList.push_back(item);
    }

    virtual string makeHTML() = 0;

    void output()
    {
        cout << makeHTML() << endl;
    }
};

/*
 * 子类成员 3 功能
 */
class ListPage : public BinPage
{
public:
    using BinPage::BinPage;

    string makeHTML() override
    {
        std::string str;
        str.append("<html><head><title>" + m_title + "</title></head>\n");
        str.append("<body>\n");
        str.append("<h1>" + m_title + "</h1>\n");
        str.append("<ul>\n");

        for (auto item : m_itemList)
        {
            str.append(item->makeHTML());
        }

        str.append("</ul>\n");
        str.append("<address>" + m_author + "</address>\n");
        str.append("</body>\n");
        str.append("</html>");
        return str;
    }
};

int main()
{
    shared_ptr<BinFactory> factory(BinFactoryHelper::getFactory("ListFactory"));
    assert(factory != nullptr); // 是否初始化父类工厂实例

    std::shared_ptr<BinLink> people(factory->createLink(u8"人民日报", u8"http://www.people.com.cn/"));
    std::shared_ptr<BinLink> gmw(factory->createLink(u8"光明网", u8"http://www.gmw.cn/"));
    std::shared_ptr<BinLink> us_yahoo(factory->createLink(u8"us_yahoo", u8"http://www.yahoo.com/"));
    std::shared_ptr<BinLink> jp_yahoo(factory->createLink(u8"jp_yahoo", u8"http://www.yahoo.com.jp/"));
    std::shared_ptr<BinLink> google(factory->createLink(u8"google", u8"http://www.google.com"));

    shared_ptr<Bintray> trayNews(factory->createTray("news"));
    trayNews->addItem(people.get());
    trayNews->addItem(gmw.get());

    std::shared_ptr<Bintray> trayYahoo(factory->createTray("yahoo!"));
    trayYahoo->addItem(us_yahoo.get());
    trayYahoo->addItem(jp_yahoo.get());

    std::shared_ptr<Bintray> traySearch(factory->createTray("traySearch"));
    trayYahoo->addItem(trayYahoo.get()); // 子类继承，使得子类之间可以相互关联
    trayYahoo->addItem(google.get());   

    shared_ptr<BinPage> page(factory->createPage("LinkPage", "tao"));
    page->addItem(trayNews.get());
    page->addItem(traySearch.get());
    page->output();

    return 0;
}