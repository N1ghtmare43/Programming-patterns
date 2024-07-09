#include <iostream>
#include <string>

/*
===========================================================================
    #pragma region Beverage
    Определим абстрактный класс напитков Beverage.
*/

class Beverage
{
private:
    std::string description;

public:
    virtual std::string getDescription()
    {
        return description;
    }
    
    void setDescription(std::string desc)
    {
        description = desc;
    }

    virtual float cost() = 0;   //  Функция cost будет переопределяться каждым напитком в отдельности.
};


//  Определим конкретный вид напитка
class DarkCoffe : public Beverage
{
public:
    DarkCoffe()
    {
        setDescription("Dack coffe");
    }

    //  переопределим функцию cost
    float cost() override
    {
        return 0.99;
    }
};


/*
==========================================================================
    #pragma region Decorators
    Определим класс Декораторов, унаследованный от Beverage
*/

class CondimentDecorator : public Beverage
{
public:
    Beverage* beverage;

    CondimentDecorator(Beverage* beverage) :
        beverage(beverage)
    {}

    //  переопределим метод getDescription, чтобы тот рекурсивно выводил полный состав напитка
    std::string getDescription() override
    {
        return beverage->getDescription() + " " + Beverage::getDescription();
    }
};


class Milk : public CondimentDecorator
{
public:
    Milk(Beverage* beverage):
        CondimentDecorator(beverage)
    {
        setDescription("Milk");
    }

    //  стоимость будем считать рекурсивно
    float cost() override
    {
        return 0.5 + beverage->cost();
    }
};

class Chocolate : public CondimentDecorator
{
public:
    Chocolate(Beverage* beverage):
        CondimentDecorator(beverage)
    {
        setDescription("Chocolate");
    }

    float cost() override
    {
        return 0.39 + beverage->cost();
    }
};


/*
==============================================================
#pragma region Main
*/

int main()
{
    Beverage* order = new DarkCoffe();
    std::cout << order->getDescription() << ". cost: " << order->cost() << "\n" << std::endl;

    order = new Milk(order);
    std::cout << order->getDescription() << ". cost: " << order->cost() << "\n" << std::endl;

    order = new Chocolate(order);
    std::cout << order->getDescription() << ". cost: " << order->cost() << "\n" << std::endl;

    order = new Chocolate(order);
    std::cout << order->getDescription() << ". cost: " << order->cost() << std::endl;

    return 0;
}