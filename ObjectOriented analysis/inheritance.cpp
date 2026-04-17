#include<iostream>
using namespace std;

class Animals
{
private:
    string name;
    string sound;
    string habitat;
public:
    Animals(){
        this->name = "Unknown Animals";
        this->sound = "Unknown sound";
        this->habitat = "Unknown habitat";
    };

    Animals(string name, string sound, string habitat){
        this->name = name;
        this->sound = sound;
        this->habitat = habitat;
    };

    void eat(){
        cout<<"Animal Eating"<<endl;
    }

};

class Reptile : public Animals {
    bool lays_eggs; 
    int number_of_scales;

    public:    
    Reptile() : Animals() {}

   // Reptile(string name, string sound, string habitat) : Animals(name, sound, habitat) {}
};

int main()
{
    Reptile snake;
    Animals ee = Reptile();//  this will call the default constructor of Reptile, which in turn calls the default constructor of Animals
    snake.eat();
    return 0;
}
