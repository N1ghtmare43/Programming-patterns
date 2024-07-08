#include <iostream>

#pragma region Behaviors
class FlyBehavior
{
public:
    virtual void fly() {}
};

class QuackBehavior
{
public:
    virtual void quack() {}
};


class FlyWithWings: public FlyBehavior
{
public:
    void fly() override
    {
        std::cout << "I`m flying with wings!" << std::endl;
    }
};

class FlyNoWay: public FlyBehavior
{
public:
    void fly() override
    {
        std::cout << "I can`t fly!" << std::endl;
    }
};


class Quack: public QuackBehavior
{
public:
    void quack() override
    {
        std::cout << "Quack!" << std::endl;    
    }
};

class MuteQuack: public QuackBehavior
{
public:
    void quack() override
    {
        std::cout << "Silence..." << std::endl;
    }
};


#pragma region Ducks
class Duck
{
private:
    FlyBehavior* flyBehavior;
    QuackBehavior* quackBehavior;

public:
    Duck(FlyBehavior* fly, QuackBehavior* quack) : 
        flyBehavior(fly),
        quackBehavior(quack)
    {};

    ~Duck()
    {
        delete flyBehavior;
        delete quackBehavior;
    }

    void setFlyBehavior(FlyBehavior* newFlyBehavior)
    {
        delete flyBehavior;
        flyBehavior = newFlyBehavior;
    }

    void setQuackBehavior(QuackBehavior* newQuackBehavior)
    {
        delete quackBehavior;
        quackBehavior = newQuackBehavior;
    }

    void swim() 
    {
        std::cout << "i`m swimming!" << std::endl;
    }

    void permormFly()
    {
        flyBehavior->fly();
    }

    void performQuack()
    {
        quackBehavior->quack();
    }
};


class BrownDuck: public Duck
{
public:
    BrownDuck() : 
        Duck(new FlyWithWings(), new Quack())
    {}
};


class RubberDuck: public Duck
{
public:
    RubberDuck():
        Duck(new FlyNoWay(), new MuteQuack())
    {}
};

#pragma region Main
int main()
{
    BrownDuck brownDuck;
    RubberDuck rubberDuck;

    brownDuck.performQuack();
    brownDuck.setQuackBehavior(new MuteQuack);
    brownDuck.performQuack();

    return 0;
}