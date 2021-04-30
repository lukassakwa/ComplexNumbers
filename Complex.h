#ifndef COMPLEX 
#define COMPLEX 1

#include <iostream>
#include <cmath>
#include <string>

class Complex
{
private:
    double num, im;
    std::string inText;

public:
    //Constructors & destructor
    Complex(std::string = "");
    Complex(const Complex&);
    ~Complex();

    //Operators
    operator std::string();

    Complex operator+(Complex);
    Complex operator-(Complex);
    Complex operator*(Complex);
    Complex operator/(Complex);

    bool operator==(Complex);

    //in & out operation
    friend std::ostream& operator<<(std::ostream&, Complex&);
    friend std::istream& operator>>(std::istream&, Complex&);

    //text validation
    bool textValidation(std::string);

    //assigning values to num && im
    void assigningValue(std::string);
};

#endif