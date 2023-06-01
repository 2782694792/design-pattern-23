#include <iostream>
#include <string>
#include <vector>

// 抽象命令类
class Command {
public:
    virtual ~Command()     = default;
    virtual void execute() = 0;
};

// 命令执行（响应）类
class Receiver { // 可抽象化，派生命令的执行动作类
private:
    int         id;
    std::string name;

public:
    explicit Receiver(int id, std::string name) : id(id), name(name) {}

    void action1() {
        if (id == 0) {
            return;
        }

        std::cout << "ID: " << id << "\nname : " << name << "\nwork: "
                  << "Receiver: executing action 1\n";
    }
    void action2() {
        std::cout << "ID: " << id << "\nname : " << name << "\nwork: "
                  << "Receiver: executing action 2\n";
    }
};

// 具体的命令派生类
class ConcreteCommand1 : public Command {
private:
    Receiver* receiver_; // 存有命令响应指针

public:
    explicit ConcreteCommand1(Receiver* receiver) : receiver_(receiver) {}

    void execute() override {
        receiver_->action1();
    }
};

class ConcreteCommand2 : public Command {
private:
    Receiver* receiver_;

public:
    explicit ConcreteCommand2(Receiver* receiver) : receiver_(receiver) {}

    void execute() override {
        receiver_->action2();
    }
};

// 命令管理（调用者）
class Invoker {
private:
    std::vector< Command* > commands_;

public:
    void addCommand(Command* command) { // 命令申请
        commands_.push_back(command);
    }

    void executeCommands() {
        for (auto command : commands_) {
            command->execute();
        }

        commands_.clear();
    }
};

int main() {
    Receiver* receiver = new Receiver(1, "belien"); // 统一命令执行类
    ConcreteCommand1* command1 = new ConcreteCommand1(receiver);
    ConcreteCommand2* command2 = new ConcreteCommand2(receiver);

    Invoker* invoker = new Invoker; // 统一响应各类命令
    invoker->addCommand(command1);
    invoker->addCommand(command2);

    invoker->executeCommands();

    delete receiver;
    delete command1;
    delete command2;
    delete invoker;

    return 0;
}
