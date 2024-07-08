#include <iostream>
#include <vector>

#pragma region Interfaces


class Observer
{
public:
    virtual void update(float temperature) = 0;
};


class Subject
{
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

#pragma region WeatherStation
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
            observer->update(temperature);
        }
    }

    void setTemperature(float value)
    {
        temperature = value;
        notifyObservers();
    }

private:
    std::vector<Observer*> observers;

    float temperature;

};

#pragma region Devices
class Device1 : public Observer
{
private:
    Subject* weatherStation;
    float temperature;

    void display()
    {
        std::cout << "1: Weather was changed!\tTemperature now: " << temperature << std::endl;
    }

public:
    Device1(WeatherStation* station):
        weatherStation(station)
    {}

    void update(float newTemparature)
    {
        temperature = newTemparature;
        display();
    }
};


class Device2 : public Observer
{
private:
    Subject* weatherStation;
    float temperature;

    void display()
    {
        std::cout << "2: Weather update!\tTemperature now: " << temperature << std::endl;
    }

public:
    Device2(WeatherStation* station):
        weatherStation(station)
    {}


    void update(float newTemparature)
    {
        temperature = newTemparature;
        display();
    }
};


#pragma region Main
int main()
{
    WeatherStation station(30.2);
    
    Device1 d1(&station);
    Device2 d2(&station);

    station.setTemperature(40);

    station.registerObserver(&d1);
    station.registerObserver(&d2);

    station.setTemperature(90.5);

    station.removeObserver(&d1);

    station.setTemperature(0.45);

    return 0;
}