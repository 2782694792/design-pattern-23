# 结构型模式 —— 桥接模式
· **将抽象部分与它的实现部分分离**，使他们都可以独立地变化；
· 利用抽象类和它的派生类来实现自己的对象；
· 也称为柄体模式或接口模式。

## 模式动机
1. 解决继承带来的问题：
对象的继承关系在编译时就定义好，所以无法再运行时改变从父类继承的实现；
而当需要复用子类时，若继承下来的实现不适合解决新的问题，则需要重写父类或替换其他类。
2. 合成/聚合复用原则（CARP）：
`聚合`表示一种弱“拥有”关系，如对象 A 包含对象 B，但 B 不是 A 的一部分；
`合成`则是一种强“拥有”关系，体现严格的部分和整体的关系，拥有同样的声明周期。
3. 降低组合带来的类过载：
设有圆和矩形，有三种颜色：白黑灰，进行图像设计：
（1）两个形状均有对应的三种颜色，生成的类则会有 2 * 3 = 6 个；
（2）将圆和矩形进行抽象派生，对三种颜色进行颜色派生，则会有 2 + 3 = 5 个类。

## 示例
通过抽象类之间的一定依赖性，对抽象与抽象之间进行交互，而进行应用时，
由抽象类和派生类来实现类对象的组合。
```
class Color
{
public:
    Color(){}
    virtual ~Color(){}
    virtual QString Name() = 0;
protected:
    QString m_Name;
};
....

class Shape
{
public:
    Shape(){}
    virtual ~Shape(){}
    void SetColor(Color* color);
    virtual void MyShape() = 0;
protected:
    Color* m_Color;
};
....

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Color* white = new Red();
    Color* black = new Black();

    Shape* rectangle = new Rectangle();
    rectangle->SetColor(white);
    Shape* circle = new Circle();
    circle->SetColor(black);

    rectangle->MyShape();
    circle->MyShape();
    ...
}

```