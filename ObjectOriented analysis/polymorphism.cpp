#include<iostream>
using namespace std;

class Vehicle
{
private:
    string color;
    int engine_power;
public:

    Vehicle(){
        this->color = "Unknown color";
        this->engine_power = 0;
    };

    Vehicle(string color, int engine_power){
        this->color = color;
        this->engine_power = engine_power;
    };

    void move(){
        cout<<"I am a vehicle moving"<<endl;
    }

    virtual void horn() = 0;
    

};

class Car : public Vehicle {
    int number_of_seats;
    int number_of_wheels;
    public:    
    //Car() : Vehicle() {}

    
    void move(){
        cout<<"I am a car moving"<<endl;
    }

    void horn(){
        cout<<"I am a car honking"<<endl;
    }
};

int main()
{
    Car car1;
    car1.move();
    car1.horn();
    return 0;
}
