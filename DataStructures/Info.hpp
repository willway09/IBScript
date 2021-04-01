#ifndef _INFO_HPP
#define _INFO_HPP

#include <string>

class Info {
  private:
    std::string name;
    int age;
    double height;
  public:
  
	Info(std::string n, int a, double h) : name(n), age(a), height(h) { };
  
    std::string getName() { return name; };
    void setName(std::string n) { name = n; };

    int getAge() { return age; };
    void setAge(int a) { age = a; };

    double getHeight() { return height; };
    void setHeight(double h) { height = h; };

};

#endif //_INFO_HPP
