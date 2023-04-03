# 结构型模式 - 适配器
```
1. 结构型模式，关注的是如何组合类与对象，以此获得更大的结构；
2. 使得原本由于接口不兼容而不能在一起工作的那些类可以一起工作。
``` 
## 类别
· 适配器模式有三种类别：类模式(继承)、对象模式(组合)、缺省(单接口适配器)。

### 类模式
1. 场景： go 语言支持用同一个接口对 mysql、sqlite3、postgersql 三种数据库进行访问；
2. 统一多个类的接口时，且每个类结构类似时使用继承适配器模式。
3. 需要支持多重继承；
```
class ORM:public mysql,public sqlite3,public postgersql {
    public:
        void orm_select() {
            switch(type) {
                case mysqlType:
                    mysql::select();
                    break;
                case sqlite3Type:
                    sqlite3::select();
                    break;
                case postgersqlType:
                    postgersql::select();
                    break;
                default:
                    break;
            }
        }
};
```
### 对象模式
1. 场景：TypeC 接口的硬件连接 USB 接口的硬盘；
2. 兼容原有的接口内容时，进行添加新特性则使用组合适配器模式（使用频率更高）；
3. 适配过程相比复杂，需进行置换适配者类方法再进行适配。
```
class CAdapter : public CUsbDisk 
{
public:
    CAdapter()
    {
        mpAdaptee = new CTypeCInterface();
    }
    ~CAdapter()
    {
        if (NULL != mpAdaptee) {
            delete mpAdaptee;
        }
    }

    void ConnectDevice()
    {
        if (NULL != mpAdaptee) {
            mpAdaptee->ConnectDevice();
        } else {
            cout << "Adapter abnormal. Connect fail!" << endl;
        }
    }

private:
    CTypeCInterface *mpAdaptee; // 组合，类依赖
};

```
### 接口适配器
1. 更方便的使用接口，实现接口类对象时必须实现接口中的全部方法，但是往往只需要实现其中的某一个方法；
2. 设计抽象类实现接口，并为接口中每个方法提供一个默认实现（空方法），则其子类可以选择性覆盖父类的某些方法。



