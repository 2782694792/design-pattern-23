# 结构型模式 —— 装饰器模式

- 允许向一个现有的对象添加新的功能，同时不改变其结构；
- 用于现有类的包装，并在保持类方法签名完整性的前提下，提供额外的功能；
- 动态地给一个对象添加一些额外的职责。

## 模式组成

1. 原生类：定义抽象接口；
2. 派生类：实现抽象接口；
3. 装饰器：包含原生类指针，使得装饰器再次派生扩展时，仍然保持着原生类调用原生接口，并不改变接口，装饰角色的接口与抽象构建角色的接口一致，完全透明。
    
``` 
装饰模式重点在装饰，对核心功能的装饰作用；将继承中对子类的扩展转化为功能类的组合，从而将需要对子类的扩展转嫁给用户去进行调用组合，用户如何组合由用户去决定。
```

## 使用场景

1. 扩展类功能，或增加附加责任；
2. 动态给对象增加功能，还可以动态撤销。

## 区别桥接模式
1. 都是为了防止过度继承，但子类剧增；
2. 桥接属于结构与实现分离或属于与基于属性的行为进行分离；装饰者模式是对基于属性的行为进行封闭成独立的类，从而实现类的装饰（扩展）。如：异常类与异常处理类之间进行桥接，异常处理类多种形式处理装饰或多种异常处理扩展；
3. 桥接属于横向行为，行为彼此之间无关联，而装饰者模式之间的行为具有可叠加性，其表现出来的结果是一个整体。

## 示例：日志文件的记录与多种形式

```
#include<iostream>
using namespace std;

class log {          //整个日志类
    public:
        virtual void log_out(string filename, string  value) {
            cout<<"输出日志"<<value<<"到"<<filename<<"文件"<<endl;
        }
};

class errlog:public log {    //错误日志输出类
    public:
    void log_out(string filename, string  value) {
            cout<<"输出错误日志"<<value<<"到"<<filename<<"文件"<<endl;
        }
};

class debuglog:public log {  //debug日志输出类
    public:
    void log_out(string filename, string  value) {
            cout<<"输出debug日志"<<value<<"到"<<filename<<"文件"<<endl;
        }
};

class decoratorlog:public log {//日志输出装饰器
    public:
        log *m_logout;
        decoratorlog() {}
        decoratorlog(log *logout) {
            this->m_logout = logout;
        }
        void log_out(string filename, string  value) {
                cout<<"输出debug日志"<<value<<"到"<<filename<<"文件"<<endl;
        }
};

class jsondecorator:public decoratorlog {//json日志输出装饰器
    public:
        jsondecorator(log *logout) {
            this->m_logout = logout;
        }
        void log_out(string filename, string  value) {
            cout<<"value进行了json转换"<<endl;  
            m_logout->log_out(filename,value);
        }
};

class xmldecorator:public decoratorlog { //json日志输出装饰器
    public:
        xmldecorator(log *logout) {
            this->m_logout = logout;
        }
        void log_out(string filename, string  value) {
            cout<<"value进行了xml转换"<<endl;
            m_logout->log_out(filename,value);
        }
};
int main() {
    log *log1 = new jsondecorator( new debuglog());
    log1->log_out("1.json","hello");
    log *log2 = new xmldecorator( new errlog());
    log2->log_out("1.xml","world");
    return 0;
}
```
