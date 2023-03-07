#  创建型模式 —— 单例模式
1. 在整个系统声明周期内，一个类只能生产一个实例，确保该类的唯一性；
2. 保证程序的线程安全（共享资源上锁、让线程也拥有资源避免争夺）；
3. 两种单例实现方式：饿汉式、懒汉式。
4. 特点：
   1. 构造和析构函数属于私有类型，禁止外部调用；
   2. 拷贝构造和赋值构造属于私有类型，确保实例的唯一性；
   3. 提供一个获取实例的静态方法，可以全局访问；

## 分类
**饿汉式**和**懒汉式**，区别在于创建实例的时间不同。

`懒汉式`

系统运行中实例并不存在，当需要时才会去创建并使用实例，延迟加载，时间换空间，需要考虑线程安全。
```cpp
SingleInstance * SingleInstance::GetInstance()
{

    //  使用两个 if 判断语句的技术称为双检锁；
    //  避免每次调用 GetInstance 的方法都加锁，减少开销
    if (m_SingleInstance == nullptr) 
    {
        std::unique_lock<std::mutex> lock(m_Mutex); // 智能独锁
        if (m_SingleInstance == nullptr)
        {
            m_SingleInstance = new (std::nothrow) SingleInstance();
        }
    }

    return m_SingleInstance;
}

void SingleInstance::deleteInstance()
{
    std::unique_lock<std::mutex> lock(m_Mutex); 
    if (m_SingleInstance)
    {
        delete m_SingleInstance;
        m_SingleInstance = nullptr;
    }
}
```

`饿汉式`

系统一运行就创建实例，需要时直接调用，空间换时间，时间本身属于线程安全。

```cpp
// .h
private: 
    static SingleInstance * g_pSingleton;
public:
    static SingleInstance * GetInstance();

// .cpp
SingleInstance * SingleInstance::g_pSingleton = new (std::nothrow) SingleInstance();

// 使用 C++11 std::call_once 实现单例（C++11 线程安全）
#inlude <memory>
#inlude <mutex>

static std::shared_ptr<SingleInstance> singleton = nullptr;
static std::once_flag singletonFlag;

std::shared_ptr<SingleInstance> SingleInstance::GetInstance()
{
    std::call_once(singletonFlag, [&] // once_flag 唯一标签
    { // 确保函数或代码片段在多线程环境下，只需要执行一次
        singleton = std::shared_ptr<SingleInstance>(new SingleInstance());
    });
    return singleton;
}
```

## 区别
定义时：如果类定义类静态成员对象变量，程序则在运行之初便分配类空间完成了初始化，调用了构造函数，属于饿汉式；若定义类静态成员对象指针变量，程序运行之初也会分配空间，但仅仅是指针的空间，非对象的空间，只有进一步实例化才会进行对象空间分配，这便是懒汉式。