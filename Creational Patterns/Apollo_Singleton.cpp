#include <mutex>

// 5. 根据宏参数 name 创建一个同名的类型萃取模板类，并检查模板类型参数 T 中是否包含
//      与宏参数 func 同名的方法，若包含，则模板类的 value 成员被置为 true

#define DEFINE_TYPE_TRAIT(name, func)                     \
  template <typename T>                                   \
  struct name {                                           \
    template <typename Class>                             \
    static constexpr bool Test(decltype(&Class::func)*) { \
      return true;                                        \
    }                                                     \
    template <typename>                                   \
    static constexpr bool Test(...) {                     \
      return false;                                       \
    }                                                     \
                                                          \
    static constexpr bool value = Test<T>(nullptr);       \
  };                                                      \
                                                          \
  template <typename T>                                   \
  constexpr bool name<T>::value;

// 4. 创建类型萃取模板类 HasShutdown可检查模板类型参数 T 中是否包含 Shutdown 方法
DEFINE_TYPE_TRAIT(HasShutdown, Shutdown)

// 3. 类型萃取（type traits）进行重载，模板参数存在对应 value 值时返回模板类型
template <typename T>
typename std::enable_if<HasShutdown<T>::value>::type CallShutdown(T *instance)
{
  instance->Shutdown();
}
template <typename T>
typename std::enable_if<!HasShutdown<T>::value>::type CallShutdown(
    T *instance)
{
  (void)instance;
}

#define DISALLOW_COPY_AND_ASSIGN(classname)          \
    classname(const classname&)            = delete; \
    classname& operator=(const classname&) = delete;

#define DECLARE_SINGLETON(classname)                                       \
public:                                                                    \
    static classname* Instance(bool create_if_needed = true) {             \
        static classname* instance = nullptr;                              \
        if (!instance && create_if_needed) {                               \
            static std::once_flag flag;                                    \
            std::call_once(                                                \
                flag, [&] { instance = new (std::nothrow) classname(); }); \
        }                                                                  \
        return instance;                                                   \
    }                                                                      \
                                                                           \
    static void CleanUp() {                                                \
        auto instance = Instance(false);                                   \
        if (instance != nullptr) {                                         \
            CallShutdown(instance);                                        \
        }                                                                  \
    }                                                                      \
                                                                           \
private:                                                                   \
    classname();                                                           \
    DISALLOW_COPY_AND_ASSIGN(classname)

// 懒汉实现方式，实例指针的动态内存分配放到了访问点中
// 1. std::call_once 通过间接调用 pthread_once 函数来确保传入的可调用对象即使
//      在多线程场景下也只能被执行一次，pthread_once 的底层实现基于互斥锁和条件变量
// 2. 调用 CleanUp 方法时，若发现实例指针不为空，则会调用 CallShutdown 模板函数

