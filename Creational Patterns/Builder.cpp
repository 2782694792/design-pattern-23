#include <string>
#include <vector>

// 客户端
#include <iostream>
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)  \
    {                   \
        if (p)          \
        {               \
            delete (p); \
            (p) = NULL; \
        }               \
    }
#endif

// 产品
class Article
{
private:
    std::string m_title;

public:
    void SetTitle(const std::string &title) { m_title = title; }

    std::string getTitle() { return m_title; }
};

// 抽象构造者：发布功能权限，构造用户
class BinBuilder
{
public:
    virtual ~BinBuilder() {}

    virtual void makeTitle(const std::string &title) = 0;
    virtual void makeString(const std::string &str) = 0;
    virtual void makeItems(const std::vector<std::string> &items) = 0;

    virtual Article *getProduct() = 0;

    virtual void close() = 0;
};

// 具体构造者
class TextBuilder : public BinBuilder
{
public:
    TextBuilder()
    {
        if (m_pArticle == nullptr)
        {
            m_pArticle = new Article;
        }
    }

    void makeTitle(const std::string &title) override
    {
        m_str.append("============================\n");
        m_str.append("[" + title + "]\n");
        m_str.append("\n");

        m_pArticle->SetTitle(title);
    }

    void makeString(const std::string &str) override
    {
        m_str.append(" * " + str + "\n");
        m_str.append("\n");
    }

    void makeItems(const std::vector<std::string> &items) override
    {
        for (auto item : items)
        {
            m_str.append(" .  " + item + "\n");
        }
        m_str.append("\n");
    }

    void close() override
    {
        m_str.append("============================\n");
    }

    std::string getResult() const
    {
        return m_str;
    }

    Article *getProduct() override
    {
        return m_pArticle;
    }

private:
    std::string m_str;

    Article *m_pArticle;
};

// 指挥者
class Director
{
public:
    Director(BinBuilder *builder) : m_builder(builder) {}

    void construct()
    {
        m_builder->makeTitle("Greeting");
        m_builder->makeString(u8"从早上到下午");
        m_builder->makeItems(std::vector<std::string>{u8"早上好", u8"下午好"});
        m_builder->makeString(u8"晚上");
        m_builder->makeItems(std::vector<std::string>{u8"晚上好", u8"晚安", u8"再见"});
        m_builder->close();
    }

private:
    BinBuilder *m_builder;
};

int main()
{
    TextBuilder *builder = new TextBuilder; // 构造器

    Director director(builder); // 建立构造器指挥者

    director.construct(); // 指挥组装

    std::string result = builder->getResult(); // 构造结果
    std::cout << result << std::endl;

    Article *article = builder->getProduct(); // 获取构造的产品

    std::string title = article->getTitle(); // 获取产品信息
    std::cout << title << std::endl;

    SAFE_DELETE(article);
    // SAFE_DELETE(director);
    SAFE_DELETE(builder);

    std::getchar();

    return 0;
}