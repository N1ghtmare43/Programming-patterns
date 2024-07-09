#include <iostream>
#include <vector>

#pragma region Interfaces

/* 
==========================================================================================
    Определим интересующие нас интерфейсы
*/

//  Интерфейс наблюдатель
class Observer
{
public:
    virtual void update() = 0;                              //  обновление наблюдателя (прием сигнала)
    /*
        Необходимые данные можно передавать и в саму функцию update, но это менее гибкий вариант,
        который, однако, позволяет не хранить ссылку на сам Субъект.
    */
};


//  Интерфейс субъекта наблюдения
class Subject
{
public:
    virtual void registerObserver(Observer* observer) = 0;  //  регистрация наблюдателей
    virtual void removeObserver(Observer* observer) = 0;    //  удаление наблюдателей
    virtual void notifyObservers() = 0;                     //  оповещение наблюдателей
                                                            //  =0 обозначает чисто виртуальную функцию,
                                                            //  т.е. от класса, содержащего такую функцию,
                                                            //  невозможно создать объект  
};

#pragma region WeatherStation

/*
==========================================================================================
    Определим конкретные классы, реализующие ранее описанные интерфейсы
*/


//  Класс, реализующий интерфейс Субъект
class WeatherStation: public Subject
{
public:
    WeatherStation(float temperature) :
        temperature(temperature)
    {};

    void registerObserver(Observer* observer) override
    {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) override
    {
        for (auto member = observers.begin(); member != observers.end(); member++)
            if ((*member) == observer)
                observers.erase(member);
    }

    void notifyObservers() override
    {
        for (auto observer : observers)
        {
            observer->update();
        }
    }

    void setTemperature(float value)
    {
        temperature = value;
        notifyObservers();
    }

    float getTemperature()
    {
        return temperature;
    }

private:
    std::vector<Observer*> observers;

    float temperature;

};

#pragma region Devices

//  Классы, реализующие интерфейс Наблюдатель
class Device1 : public Observer
{
private:
    WeatherStation* weatherStation; //  храним ссылку на субъект для доступа к его данным
    float temperature;

    void display()
    {
        std::cout << "1: Weather was changed!\tTemperature now: " << temperature << std::endl;
    }

public:
    Device1(WeatherStation* station):
        weatherStation(station)
    {}

    void update() override
    {   
        //  принимаем сигнал о наличии изменений и обрабатываем необходимые нам данные
        temperature = weatherStation->getTemperature();
        display();
    }
};


class Device2 : public Observer
{
private:
    WeatherStation* weatherStation;
    float temperature;

    void display()
    {
        std::cout << "2: Weather update!\tTemperature now: " << temperature << std::endl;
    }

public:
    Device2(WeatherStation* station):
        weatherStation(station)
    {}


    void update()
    {
        temperature = weatherStation->getTemperature();
        display();
    }
};


#pragma region Main

/*
===========================================================================================================
*/

int main()
{
    WeatherStation* station = new WeatherStation(10.1);
    
    Device1* d1 = new Device1(station);
    Device2* d2 = new Device2(station);

    station->setTemperature(40);

    station->registerObserver(d1);
    station->registerObserver(d2);

    station->setTemperature(90.5);

    station->removeObserver(d1);

    station->setTemperature(0.45);

    delete station, d1, d2;

    return 0;
}