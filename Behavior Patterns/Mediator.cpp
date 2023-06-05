#include <string>

class IColleague;

class IMediator {
public:
    virtual ~IMediator() {}
    virtual void convey(int id, const std::string& msg) = 0;
    virtual void registerColleague(int id, IColleague*) = 0;
};

class IColleague {
public:
    virtual ~IColleague() {}
    virtual void receivedMsg(const std::string& msg)     = 0;
    virtual void sendMsg(int id, const std::string& msg) = 0;
    virtual void setMediator(IMediator* mediator)        = 0;
};

#include <unordered_map>

// 具体中介者：对同事对象进行管理（注册申请等）、完成同事之间的交互细节实现
class CMediator : public IMediator {
public:
    virtual void convey(int id, const std::string& msg) override {
        auto it = m_map.find(id);
        if (it != m_map.end()) {
            it->second->receivedMsg(msg);
        }
    }

    virtual void registerColleague(int id, IColleague* colleague) override {
        auto it = m_map.find(id);
        if (it == m_map.end()) {
            m_map.insert(std::make_pair(id, colleague));
            colleague->setMediator(this);
        }
    }

private:
    std::unordered_map< int, IColleague* > m_map;
};

#include <iostream>

// 具体同事类：包含对象之间的公共动作、中介对象指针
class CColleague1 : public IColleague {
public:
    virtual void receivedMsg(const std::string& msg) override {
        std::cout << __FUNCTION__ << " " << msg << std::endl;
    }

    virtual void sendMsg(int id, const std::string& msg) override {
        std::cout << __FUNCTION__ << id << ": " << msg << std::endl;
        if (m_mediator) {
            m_mediator->convey(id, msg); // 由中介者进行转发
        }
    }

    virtual void setMediator(IMediator* mediator) override {
        m_mediator = mediator;
    }

private:
    IMediator* m_mediator = nullptr;
};

class CColleague2 : public IColleague {
public:
    virtual void receivedMsg(const std::string& msg) override {
        std::cout << __FUNCTION__ << " " << msg << std::endl;
    }
    virtual void sendMsg(int id, const std::string& msg) override {
        std::cout << __FUNCTION__ << id << ": " << msg << std::endl;
        if (m_mediator) {
            m_mediator->convey(id, msg);
        }
    }
    virtual void setMediator(IMediator* mediator) override {
        m_mediator = mediator;
    }

private:
    IMediator* m_mediator = nullptr;
};

int main() {
    IColleague* c1 = new CColleague1;
    IColleague* c2 = new CColleague2;
    IMediator*  md = new CMediator;
    md->registerColleague(1, c1);
    md->registerColleague(2, c2);

    c1->sendMsg(2, "Hello c2, i am c1");
    c2->sendMsg(1, "Hello c1, i am c2");
    delete c1;
    delete c2;
    delete md;
    return 0;
}
