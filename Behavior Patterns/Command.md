# 行为型模式 —— 命令模式

- 用于将请求或频繁调用关系管理起来；
- 请求以命令的形式封装在对象中，并传给调用对象，从而使得用不同的请求对客户进行参数化；
- 调用对象寻找可以处理该命令的合适对象并传递命令，由其执行命令；

## 模式组成

1. Command : 命令对象基类，定义命令类的模板以及命令的动作接口 execute 等，以此调用请求接收者的相关操作;
2. Receiver : 命令响应类，执行命令的对象，实施请求相关的操作或响应某个命令的执行动作;
3. ConcreteCommand : 具体执行的命令，持有 receiver 的指针，将接收者对象的动作绑定其中，实现对命令的管理；
4. Invoker : 命令的调用者（请求的发送者），执行命令的对象，存储命令并管理命令申请和响应的整个流程。

## 利弊

`优点`

1. 降低耦合度。将请求发送者和接收者解耦，其结果是更松散的耦合，可以独立地改变请求发送者或接收者中的一个而不会影响其他；
2. 易扩展新的命令。只需创建一个新的具体命令子类即可。遵循“开闭原则”，对扩展开放，对修改关闭；
3. 支持撤销和恢复操作。

`缺点`

1. 增加代码的复杂性。引入了多个新的类和对象；
2. 难以管理。大量的具体命令类会使得系统设计和维护更加困难；
3. 影响系统的性能。由于命令对象需要保存请求和操作，因此需要更多的内存空间。此外，执行命令也可能需要更多的时间。

## 应用场景

1. GUI 中每一个按钮都是一条命令；
2. 模拟 CMD。

## 示例

- 撤销与重做：
```cpp

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
};

class AddCommand : public Command {
private:
    int& value;
    int amount;
public:
    AddCommand(int& value, int amount) : value(value), amount(amount) {}
    void execute() {
        value += amount;
    }
    void undo() {
        value -= amount;
    }
    void redo() {
        execute();
    }
};

class Invoker {
private:
    Command* command;
public:
    void setCommand(Command* command) {
        this->command = command;
    }
    void executeCommand() {
        command->execute();
    }
    void undoCommand() {
        command->undo();
    }
    void redoCommand() {
        command->redo();
    }
};

class SubtractCommand : public Command {
private:
    int& value;
    int amount;
public:
    SubtractCommand(int& value, int amount) : value(value), amount(amount) {}
    void execute() {
        value -= amount;
    }
    void undo() {
        value += amount;
    }
    void redo() {
        execute();
    }
};

int main() {
    int value = 0;

    // 增加 1
    AddCommand addCommand(value, 1);
    invoker.setCommand(&addCommand);
    invoker.executeCommand(); // value = 1

    // 减少 2
    SubtractCommand subtractCommand(value, 2);
    invoker.setCommand(&subtractCommand);
    invoker.executeCommand(); // value = -1

    // 撤销
    invoker.undoCommand(); // value = 1

    // 重做
    invoker.redoCommand(); // value = -1

    return 0;
}

```
