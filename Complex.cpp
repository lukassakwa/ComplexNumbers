#include "Complex.h"

//Constructors
Complex::Complex(std::string inTextTemp) : inText(inTextTemp), num(0), im(0)
{
    assigningValue(inText);
}

Complex::Complex(const Complex& complex) : num(complex.num), im(complex.im)
{
}

Complex::~Complex()
{
}

//operators

Complex::operator std::string() {
    return this->inText;
}

Complex Complex::operator+(Complex complex) {
    Complex sum;

    sum.num = this->num + complex.num;
    sum.im = this->im + complex.im;

    return sum;
}

Complex Complex::operator-(Complex complex) {
    Complex sum;

    sum.num = this->num - complex.num;
    sum.im = this->im - complex.im;

    return sum;
}

Complex Complex::operator*(Complex complex) {
    Complex sum;

    sum.num = (this->num * complex.num) + (this->im * complex.im * (-1));
    sum.im = this->num * complex.im + this->im * complex.num;

    return sum;
}

Complex Complex::operator/(Complex complex) {
    Complex sum;

    double divider = complex.num * complex.num + complex.im * complex.im;
    sum.num = (this->num * complex.num) + (this->im * (complex.im * (-1)) * (-1));
    sum.im = this->num * (complex.im * (-1)) + this->im * complex.num;

    sum.num = sum.num / divider;
    sum.im = sum.im / divider;

    return sum;
}

bool Complex::operator==(Complex complex) {
    double epsilon = 0.0000001f;
    if (fabs(this->num - complex.num) < epsilon && fabs(this->im - complex.im) < epsilon)
        return true;
    return false;
}

//text valdation
bool Complex::textValidation(std::string inTextTemp) {
    int i = 1;
    bool count = false;
    std::size_t offset;
    std::string tabCheck = "+-()";

    if (inTextTemp == "" || inTextTemp[inTextTemp.length() - 2] != 'i' || inTextTemp[0] != '(' || inTextTemp[inTextTemp.length() - 1] != ')')
        return false;

    while (i < inTextTemp.length() - 2) {
        if (isdigit(inTextTemp[i])) {
            std::stod(&inTextTemp[i], &offset);

            if (inTextTemp[i - 1] != '+' && inTextTemp[i - 1] != '-' && inTextTemp[i - 1] != '(')
                return false;

            i += offset;
        }
        else {
            for (int a = 0; a < tabCheck.length(); a++) {
                if (inTextTemp[i] == tabCheck[a])
                    count = true;
            }
            if (!count)
                return false;

            count = false;
            ++i;
        }
    }

    return true;
}

//assigning values to num && im
void Complex::assigningValue(std::string inTextTemp) {
    std::size_t offset = 0;
    int count = 0;
    int i = 0;

    while (i < inTextTemp.size()) {
        if (isdigit(inTextTemp[i]) || inTextTemp[i] == '-' && isdigit(inTextTemp[i + 1]) || inTextTemp[i] == '+' && isdigit(inTextTemp[i + 1])) {
            if (count == 0)
                this->num = std::stod(&inTextTemp[i], &offset);
            else
                this->im = std::stod(&inTextTemp[i], &offset);
            ++count;
            i += offset;
        }
        else
            ++i;
        ++offset;
    }
}
