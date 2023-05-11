#include <iostream>

// 抽象处理类：责任链对象主要组成
class Handler {
public:
    Handler(int level) : level_(level), nextHandler_(nullptr){};
    virtual ~Handler(){};
    void SetNext(Handler* handler) {
        nextHandler_ = handler;
    };
    virtual void HandleRequest(int leaveDays) = 0;

protected:
    int      level_;
    Handler* nextHandler_;
};

class ConcreteHandler1 : public Handler {
public:
    ConcreteHandler1() : Handler(1){};
    virtual ~ConcreteHandler1(){};
    virtual void HandleRequest(int leaveDays) {
        if (leaveDays <= 3) {
            printf("%d 天请假被部门主管批准!\n", leaveDays);
        }
        else {
            if (nextHandler_ != nullptr) {
                nextHandler_->HandleRequest(leaveDays);
            }
            else {
                printf("超过部门主管权限的请假天数!\n");
            }
        }
    }
};

class ConcreteHandler2 : public Handler {
public:
    ConcreteHandler2() : Handler(2){};
    virtual ~ConcreteHandler2(){};
    virtual void HandleRequest(int leaveDays) {
        if (leaveDays > 3) {
            printf("%d 天请假被总经理批准!\n", leaveDays);
        }
        else {
            printf("不需要总经理批准的请假天数!\n");
        }
    }
};

int main() {
    ConcreteHandler1* handler1 = new ConcreteHandler1();
    ConcreteHandler2* handler2 = new ConcreteHandler2();
    handler1->SetNext(handler2);

    handler1->HandleRequest(2);
    handler1->HandleRequest(4);

    delete handler1;
    delete handler2;

    return 0;
}
