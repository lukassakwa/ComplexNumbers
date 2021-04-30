#include "Complex.h"
#include <fstream>

const std::string checkTab = "+-*/";

//Selection functions
void writeSelection();
void optionSelection(char);
void selectOperation(char, std::string);

//Complex numbers tests
void testComplexExpressions();
void testComplexNumbers();

//character validation
bool charValidation(char);

//Complex numbers operation
Complex operationComplex(std::string*, char);

//side functions
void endOutputText(double, double);

std::ostream& operator<<(std::ostream& out, Complex& complex);
std::istream& operator>>(std::istream& in, Complex& complex);

int main() {
    writeSelection();
    char mainCharacter;

    do {

        std::cin >> mainCharacter;
        optionSelection(mainCharacter);

    } while (mainCharacter != 'k');

    return EXIT_SUCCESS;
}

std::ostream& operator<<(std::ostream& out, Complex& complex) {
    if (complex.im > 0)
        out << "(" << complex.num << "+" << complex.im << "i)";
    else if (complex.im < 0)
        out << "(" << complex.num << complex.im << "i)";
    else
        out << "(" << complex.num << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Complex& complex) {
    in >> complex;
    return in;
}

///////////////////////////////////////////
//Selection functions
///////////////////////////////////////////
void writeSelection() {
    std::cout << "w - Uruchom test wyswietlajacy wyrazenia zespolone " << std::endl;
    std::cout << "l - Uruchom test wyswietlajacy liczby zespolone " << std::endl;
    std::cout << "m - Wyswietl menu" << std::endl;
    std::cout << "k - Koniec dzialania programu" << std::endl << std::endl;

    std::cout << "Twoj wybor (m - menu)> ";
}

void optionSelection(char choice) {
    switch (choice) {
    case 'w':
        testComplexExpressions();
        std::cout << "\n";
        writeSelection();
        break;
    case 'l':
        testComplexNumbers();
        std::cout << "\n";
        writeSelection();
        break;
    case 'm':
        std::cout << "\n";
        writeSelection();
        break;
    case 'k':
        std::cout << "\nKoniec programu\n";
        break;
    default:
        std::cout << "\nNie ma takiej opcji\n\n";
        writeSelection();
        break;
    }
}

void selectOperation(char character, std::string data) {
    switch (character)
    {
    case '+':
        std::cout << ":? Podaj operacje dodawania, ktorej wynikiem jest: " << data << std::endl;
        break;
    case '-':
        std::cout << ":? Podaj operacje odejmowania, ktorej wynikiem jest: " << data << std::endl;
        break;
    case '*':
        std::cout << ":? Podaj operacje mnozenia, ktorej wynikiem jest: " << data << std::endl;
        break;
    case '/':
        std::cout << ":? Podaj operacje dzielenia, ktorej wynikiem jest: " << data << std::endl;
        break;

    default:
        break;
    }
}

/////////////////////////////////////////////
//test of Complex variables 
/////////////////////////////////////////////
void testComplexExpressions() {
    std::fstream file;
    file.open("test_wyrazenia_zespolone.dat", std::ios::in);

    double goodAnswer, badAnswer;
    std::string data[2] = { "", "" }, temp = "";
    char character;
    Complex complexUserAnswer, complexGoodAnswer;

    goodAnswer = badAnswer = 0;

    if (file.is_open()) {
        while (file >> data[0]) {
            file >> character;
            file >> data[1];

            if (complexGoodAnswer.textValidation(data[0]) && complexGoodAnswer.textValidation(data[1]) && charValidation(character)) {

                std::cout << ":? Podaj wynik operacji: " << data[0] << " " << character << " " << data[1] << std::endl;

                complexGoodAnswer = operationComplex(data, character);

                do {
                    std::cout << "Twoja odpowiedz: ";
                    std::cin >> temp;

                    if (complexUserAnswer.textValidation(temp))
                        break;

                    std::cout << "\nBlad wprowadzenia wartosci. Sprobuj jeszcze raz.\n\n";
                } while (true);

                complexUserAnswer = temp;

                if (complexUserAnswer == complexGoodAnswer) {
                    std::cout << ":) Odpowiedz poprawna" << std::endl << std::endl;
                    goodAnswer++;
                }
                else {
                    std::cout << ":( Blad. Prawidlowym wynikiem jest: " << complexGoodAnswer << std::endl << std::endl;
                    badAnswer++;
                }
            }
            else {
                std::cout << "Wykryto w pliku bledny zapis operacji. Zostala ona pominieta." << std::endl << std::endl;
            }
        }
        file.close();
    }

    endOutputText(goodAnswer, badAnswer);
}

/////////////////////////////////////
//test of Complex numbers 
/////////////////////////////////////
void testComplexNumbers() {
    std::fstream file;
    file.open("test_liczby_zespolone.dat", std::ios::in);

    char character;
    std::string data = "", temp = "", tab[2] = { "", "" };

    double goodAnswers = 0, badAnswers = 0;

    int count = 0;

    Complex complex, complexUserAnswer;

    if (file.is_open()) {
        while (file >> data) {

            if (complex.textValidation(data)) {

                complex = data;

                selectOperation(checkTab[count], data);

                do {
                    std::cout << "Twoja odpowiedz: ";
                    std::cin >> tab[0] >> character >> tab[1];

                    if (!complex.textValidation(tab[0])) {
                        std::cout << "\nWprowadzony zostal blednie pierwszy argument.\n Sprobuj jeszcze raz.\n" << std::endl;
                        continue;
                    }

                    if (character != checkTab[count]) {
                        std::cout << "\nWprowadzony zotal bledny operator `" << character << "`\nSprobuj jeszcze raz.\n" << std::endl;
                        continue;
                    }

                    if (!complex.textValidation(tab[1])) {
                        std::cout << "\nWprowadzony zostal blednie drugi argument.\n Sprobuj jeszcze raz.\n" << std::endl;
                        continue;
                    }

                    break;

                } while (true);

                if (++count == 4)
                    count = 0;

                complexUserAnswer = operationComplex(tab, character);

                if (complex == complexUserAnswer) {
                    std::cout << ":) Odpowiedz poprawna" << std::endl;
                    goodAnswers++;
                }
                else {
                    std::cout << ":( Blad. Wynikiem tej operacji jest: " << complexUserAnswer << std::endl;
                    badAnswers++;
                }

            }
            else {
                std::cout << "\nWykryto w pliku bledny zapis operacji. Zostala ona pominieta.\n" << std::endl;
            }
        }
        file.close();
    }
    endOutputText(goodAnswers, badAnswers);
}

//////////////////////////////////
//character validation
/////////////////////////////////
bool charValidation(char character) {

    for (int a = 0; a < checkTab.length(); a++) {
        if (character == checkTab[a])
            return true;
    }

    return false;
}

////////////////////////////////////////////
// "+-*/" operations on Complex numbers
//////////////////////////////////////////////
Complex operationComplex(std::string* tab, char character) {
    std::string data = "";
    Complex complex[3] = { data, *tab, *(tab + 1) };

    switch (character)
    {
    case '+':
        complex[0] = complex[1] + complex[2];
        break;
    case '-':
        complex[0] = complex[1] - complex[2];
        break;
    case '*':
        complex[0] = complex[1] * complex[2];
        break;
    case '/':
        complex[0] = complex[1] / complex[2];
        break;
    default:
        break;
    }

    return complex[0];
}

///////////////////////////////////////////
//side functions
//end of test module
///////////////////////////////////////////
void endOutputText(double good, double bad) {
    std::cout << "Koniec testu.\n" << std::endl;
    std::cout << "Ilosc dobrych odpowiedzi: " << good << std::endl;
    std::cout << "Ilosc blednych odpowiedzi: " << bad << std::endl;
    std::cout << "Wynik procentowy poprawnych odpowiedzi: " << (good / (good + bad) * 100) << "%" << std::endl;
}