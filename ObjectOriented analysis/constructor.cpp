#include <iostream>
#include <string>
using namespace std;


class car{
    int number_of_doors;
    int engine_power;
    string color;
    string brand;
   
    public:
    //default constructor
    car() {
        number_of_doors = 4;
        engine_power = 50;
        color = "black";
        brand = "toyota";
    }

    //parametarized constructor
    car(int doors, int power, string c, string b) {
        number_of_doors = doors;
        engine_power = power;
        color = c;
        brand = b;
    }

    //getters
    int getNumberOfDoors() {
        return this->number_of_doors;
    }

    string getBrand() {
        return this->brand;
    }

    string getColor() {
        return this->color;
    }

    int getEnginePower() {
        return this->engine_power;
    }

    //setters
    void setNumberOfDoors(int doors) {
        this->number_of_doors = doors;
    }

    void setBrand(string b) {
        this->brand = b;
    }

    void setColor(string c) {
        this->color = c;
    }

    void setEnginePower(int power) {
        this->engine_power = power;
    }
};

int main() {
    car car1(4, 150, "Red", "Toyota");
    car car2(2, 200, "Blue", "Ford");
    car EngPalma(6, 30, "Black", "Telsa");

    cout << "Car 1: " << car1.getNumberOfDoors() << " doors, " << car1.getBrand() << endl;
    cout << "Car 2: " << car2.getNumberOfDoors() << " doors, " << car2.getBrand() << endl;
    cout << "EngPalma: " << EngPalma.getNumberOfDoors() << " doors, " << EngPalma.getBrand() << endl;

    return 0;
}