#include<iostream>
using namespace std;

class Roman {
public:
    friend ostream& operator<<(ostream&, Roman&);

    Roman() =default;
    Roman(const char* romanChar) {
        if (isRomanNumber(romanChar)) charToInt(romanChar);
        else cout << "Error." << endl;
    }

    Roman operator+(const Roman& obj) {
        Roman obj2;
        obj2.romanInt = romanInt + obj.romanInt;
        return obj2;
    }
    Roman operator-(const Roman& obj) {
        Roman obj2;
        obj2.romanInt = romanInt - obj.romanInt;
        return obj2;
    }
    Roman operator*(const Roman& obj) {
        Roman obj2;
        obj2.romanInt = romanInt * obj.romanInt;
        return obj2;
    }
    Roman operator/(const Roman& obj) {
        Roman obj2;
        obj2.romanInt = romanInt / obj.romanInt;
        return obj2;
    }

    bool operator==(const Roman& obj) {
        return (romanInt == obj.romanInt ? 1 : 0);
    }
    bool operator!=(const Roman& obj) {
        return (romanInt != obj.romanInt ? 1 : 0);
    }
    bool operator<(const Roman& obj) {
        return (romanInt < obj.romanInt ? 1 : 0);
    }
    bool operator>(const Roman& obj) {
        return (romanInt > obj.romanInt ? 1 : 0);
    }

    Roman operator++(int) {
        Roman obj = *this;
        romanInt++;
        return obj;
    }
    Roman operator++() {
        ++romanInt;
        return *this;
    }

    Roman operator=(const char* romanChar) {
        if (isRomanNumber(romanChar)) charToInt(romanChar);
        else cout << "Error." << endl;
        return *this;
    }
private:
    int romanInt;

    bool isRomanNumber(const char* romanChar) {
        int index = 0;
        while (romanChar[index] != '\0') {
            bool containRoman = false;

            if (romanChar[index] == 'M') containRoman = true;
            else if (romanChar[index] == 'D') containRoman = true;
            else if (romanChar[index] == 'C') containRoman = true;
            else if (romanChar[index] == 'L') containRoman = true;
            else if (romanChar[index] == 'X') containRoman = true;
            else if (romanChar[index] == 'V') containRoman = true;
            else if (romanChar[index] == 'I') containRoman = true;

            if (!containRoman) {
                return false;
            }
        
            index++;
        }

        return true;
    }

    char* regrow(char* arr, char data) {
        char* temp;
        int index;
    
        if (arr==nullptr) {
            index = 1;
            temp = new char[index + 1];
            temp[0] = data;
        }
        else {
            index = 0;
            while (arr[index] != '\0') index++;

            temp = new char[index + 2];
            for (int i = 0; i < index; i++) {
                temp[i] = arr[i];
            }

            delete[] arr;
            arr = nullptr;

            temp[index] = data;
            index++;
        }

        temp[index] = '\0';

        return temp;
    }

    char* intToChar() {
        char* temp = nullptr;

        int subtractor = 1000;
        while (romanInt != 0) {
            if (romanInt < 1000 && romanInt >= 900) {
                temp = specialCase(temp);
            }
            if (romanInt < subtractor) {
                changeSub(subtractor);
            }
            else {
                while ((romanInt - subtractor) >= 0) {
                    romanInt -= subtractor;
                    temp = charAdder(subtractor, temp);
                    temp = specialCase(temp);
                }
            }
        }
        
        return temp;
    }

    char* charAdder(int compare, char* arr) {
        if (compare == 1000) arr = regrow(arr, 'M');
        else if (compare == 500) arr = regrow(arr, 'D');
        else if (compare == 100) arr = regrow(arr, 'C');
        else if (compare == 50) arr =regrow(arr, 'L');
        else if (compare == 10) arr =regrow(arr, 'X');
        else if (compare == 5) arr =regrow(arr, 'V');
        else if (compare == 1) arr = regrow(arr, 'I');

        return arr;
    }

    char* specialCase(char* arr) {
        int compare = 10;

        while (compare < romanInt) {
            compare *= 10;
        }

        compare /= 10;

        if (romanInt / compare == 4 || romanInt / compare == 9) {
            romanInt += compare;
            arr = charAdder(compare, arr);
        }

        return arr;
    }

    void changeSub(int& num) {
        static bool flag = true;
        if (flag) {
            num /= 2;
            flag = false;
        }
        else {
            num /= 5;
            flag = true;
        }
    }

    void charToInt(const char* romanChar) {
        romanInt = 0;

        char temp = *(romanChar);
        while (temp != '\0') {
            if (temp == 'M') romanInt += 1000;
            else if (temp == 'D') romanInt += 500;
            else if (temp == 'C') {
                if (*(romanChar + 1) == 'M') {
                    romanInt += 900;
                    ++romanChar;
                }
                else if (*(romanChar + 1) == 'D') {
                    romanInt += 400;
                    ++romanChar;
                }
                else{
                    romanInt += 100;
                }
            }
            else if (temp == 'L') romanInt += 50;
            else if (temp == 'X') {
                if (*(romanChar + 1) == 'C') {
                    romanInt += 90;
                    ++romanChar;
                }
                else if (*(romanChar + 1) == 'L') {
                    romanInt += 40;
                    ++romanChar;
                }
                else{
                    romanInt += 10;
                }
            }
            else if (temp == 'V') romanInt += 5;
            else if (temp == 'I') {
                if (*(romanChar + 1) == 'X') {
                    romanInt += 9;
                    ++romanChar;
                }
                else if (*(romanChar + 1) == 'V') {
                    romanInt += 4;
                    ++romanChar;
                }
                else{
                    romanInt += 1;
                }
            }

            temp = *(++romanChar);
        }
    }
};

ostream& operator<<(ostream& print, Roman& obj) {
    print << obj.intToChar() << endl;
    return print;
}
