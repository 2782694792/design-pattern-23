#include <iostream>
using namespace std;

class AbstractCommonInterface {
public:
    virtual void run() = 0;
};

class MySystem : public AbstractCommonInterface {
public:
    virtual void run() {
        cout << "系统启动成功。。。" << endl;
    }
};

class MySystemProxy : public AbstractCommonInterface {
public:
    MySystemProxy(string User, string Password) {
        user     = User;
        password = Password;
        pSystem  = new MySystem;
    }
    ~MySystemProxy() {
        if (NULL != pSystem) {
            delete pSystem;
        }
    }

    bool checkUsernameAndpassoword() {
        if (user == "root" && password == "admin") {
            return true;
        }

        return false;
    }
    virtual void run() {
        if (checkUsernameAndpassoword()) {
            cout << "登录成功" << endl;
            this->pSystem->run();
        }
        else {
            cout << "登录失败，账号密码错误" << endl;
        }
    }

public:
    MySystem* pSystem;
    string    user;
    string    password;
};

void test() {
    AbstractCommonInterface* Proxy = new MySystemProxy("root", "admin");
    Proxy->run();
}


int main() {
    test();
    return 0;
}
