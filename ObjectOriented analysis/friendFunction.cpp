#include <iostream>
using namespace std;
class Student {
    public:
        string name;
        int age;
        string grade;
        int knowledge;
  
    public:
      Student(string name, int age, string grade) {
        this->name = name;
        this->age = age;
        this->grade = grade;
        this->knowledge = 0;}
       // Student(std::string name, int age, std::string grade);
        friend void study(Student &s);
};


void study(Student &s) {
    s.knowledge += s.knowledge * 1;
}

int main() {
    Student student1("Alice", 20, "A");
    cout << "Initial knowledge: " << student1.knowledge << endl;
    study(student1);
    cout << "Knowledge after studying: " << student1.knowledge << endl;
    return 0;
}