#include <iostream>
#include <string>
#include <unordered_map>

class Context;

// 抽象语法书节点类
class Expression { // 递归节点
public:
    virtual int interpret(Context* ctx) = 0;
    virtual ~Expression() {}
};

// 加法表达式
class Add : public Expression { // 非终结符表达式类
public:
    Add(Expression* left, Expression* right) : m_left(left), m_right(right) {}
    virtual int interpret(Context* ctx) override {
        return m_left->interpret(ctx) + m_right->interpret(ctx);
    }

private:
    Expression *m_left, *m_right;
};

// 减法表达式
class Sub : public Expression // 非终结符表达式类
{
public:
    Sub(Expression *left, Expression *right) : m_left(left), m_right(right) {}
    virtual int interpret(Context *ctx) override
    {
        return m_left->interpret(ctx) - m_right->interpret(ctx);
    }

private:
    Expression *m_left, *m_right;
};

class Context { // 上下文分析类
public:
    void registerVariable(class Variable* var, int value) {
        m_map.insert({ var, value });
    }
    int lookUpValue(class Variable* var) {
        auto itor = m_map.find(var);
        if (itor != m_map.end()) {
            return itor->second;
        }
        return 0;
    }

private:
    std::unordered_map< Variable*, int > m_map;
};

// 变量表达式
class Variable : public Expression { // 终结符表达式类
public:
    virtual int interpret(Context* ctx) override {
        return ctx->lookUpValue(this);
    }
};

// 常量表达式
class Constant : public Expression // 终结符表达式类
{
public:
    Constant(int value) : m_value(value) {}
    virtual int interpret(Context *ctx) override
    {
        return m_value;
    }

private:
    int m_value;
};


#include <iostream>
int main()
{
    Context ctx;
    Variable a;
    Variable b;
    Constant c(1024);
    ctx.registerVariable(&a, 22);
    ctx.registerVariable(&b, 11);
    Expression *e1 = new Add(&a, &b); // 33
    Expression *e2 = new Sub(&a, &b); // 11
    Expression *e3 = new Add(e2, &c); // 1035
    Expression *e = new Sub(e1, e3); // -1002
    std::cout << e->interpret(&ctx) << std::endl;

    delete e1, e2, e3, e;
    return 0;
}