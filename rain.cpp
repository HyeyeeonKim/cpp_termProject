#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int screenWidth = 80;
const int screenHeight = 25;

struct WordInfo {
    string word;
    int x, y;
    WordInfo() : x(0), y(0) {}
    WordInfo(const string& w, int startX, int startY) : word(w), x(startX), y(startY) {}
};

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void drawWord(const string& word, int x, int y) {
    gotoxy(x, y);
    cout << word;
}

void clearWord(int x, int y, int length) {
    gotoxy(x, y);
    for (int i = 0; i < length; ++i) {
        cout << " ";
    }
}

void drawScoreAndLife(int score, int life) {
    gotoxy(screenWidth, screenHeight); 
    cout << "Life: " << life << " / " << "Score: " << score << " ";
}

void drawUserInput(const string& userInput) {
    gotoxy(screenWidth - 80, screenHeight - 1);
    cout << "Input: " << userInput;
}

class StringGenerator {
public:
    virtual string generateString() = 0;
    virtual ~StringGenerator() = default;
};

class DefaultStringGenerator : public StringGenerator {
public:
    string generateString() override {
        const string characters = "abcdefghijklmnopqrstuvwxyz0123456789@#*^";
        string result;
        for (int i = 0; i < 7; ++i) {
            int index = rand() % characters.length();
            result += characters[index];
        }

        return result;
    }
};

class StringDecorator : public StringGenerator {
protected:
    StringGenerator* baseGenerator;

public:
    StringDecorator(StringGenerator* generator) : baseGenerator(generator) {}
};

class AlphabetDecorator : public StringDecorator {
public:
    AlphabetDecorator(StringGenerator* generator) : StringDecorator(generator) {}

    string generateString() override {
        const string alphabet = "abcdefghijklmnopqrstuvwxyz";
        string result;

        for (int i = 0; i < 7; ++i) {
            int index = rand() % alphabet.length();
            result += alphabet[index];
        }

        return result;
    }
};

class NumericDecorator : public StringDecorator {
public:
    NumericDecorator(StringGenerator* generator) : StringDecorator(generator) {}

    string generateString() override {
        const string numeric = "0123456789";
        string result;

        for (int i = 0; i < 7; ++i) {
            int index = rand() % numeric.length();
            result += numeric[index];
        }

        return result;
    }
};

class SpecialCharDecorator : public StringDecorator {
public:
    SpecialCharDecorator(StringGenerator* generator) : StringDecorator(generator) {}

    string generateString() override {
        const string specialChars = "@#*^";
        string result;

        for (int i = 0; i < 7; ++i) {
            int index = rand() % specialChars.length();
            result += specialChars[index];
        }

        return result;
    }
};

class AlphaNumericDecorator : public StringDecorator {
public:
    AlphaNumericDecorator(StringGenerator* generator) : StringDecorator(generator) {}

    string generateString() override {
        const string alphaNumeric = "abcdefghijklmnopqrstuvwxyz0123456789";
        string result;

        for (int i = 0; i < 7; ++i) {
            int index = rand() % alphaNumeric.length();
            result += alphaNumeric[index];
        }

        return result;
    }
};

class AlphaSpecialDecorator : public StringDecorator {
public:
    AlphaSpecialDecorator(StringGenerator* generator) : StringDecorator(generator) {}

    string generateString() override {
        const string alphaSpecial = "abcdefghijklmnopqrstuvwxyz@#*^";
        string result;

        for (int i = 0; i < 7; ++i) {
            int index = rand() % alphaSpecial.length();
            result += alphaSpecial[index];
        }

        return result;
    }
};

class NumericSpecialDecorator : public StringDecorator {
public:
    NumericSpecialDecorator(StringGenerator* generator) : StringDecorator(generator) {}

    string generateString() override {
        const string numericSpecial = "0123456789@#*^";
        string result;

        for (int i = 0; i < 7; ++i) {
            int index = rand() % numericSpecial.length();
            result += numericSpecial[index];
        }

        return result;
    }
};

class AlphaNumericSpecialDecorator : public StringDecorator {
public:
    AlphaNumericSpecialDecorator(StringGenerator* generator) : StringDecorator(generator) {}

    string generateString() override {
        const string alphaNumericSpecial = "abcdefghijklmnopqrstuvwxyz0123456789@#*^";
        string result;

        for (int i = 0; i < 7; ++i) {
            int index = rand() % alphaNumericSpecial.length();
            result += alphaNumericSpecial[index];
        }

        return result;
    }
};

StringGenerator* chooseDecorator(int option) {
    StringGenerator* generator = new DefaultStringGenerator();
    switch (option) {
    case 1:
        generator = new AlphabetDecorator(generator);
        break;
    case 2:
        generator = new NumericDecorator(generator);
        break;
    case 3:
        generator = new SpecialCharDecorator(generator);
        break;
    case 4:
        generator = new AlphaNumericDecorator(generator);
        break;
    case 5:
        generator = new AlphaSpecialDecorator(generator);
        break;
    case 6:
        generator = new NumericSpecialDecorator(generator);
        break;
    case 7:
        generator = new AlphaNumericSpecialDecorator(generator);
        break;
    }
    return generator;
}

string generateStringWithOption(int option) {
    StringGenerator* generator = chooseDecorator(option);
    string result = generator->generateString();
    delete generator;
    return result;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int option;
    const int numWords = 6;
    const int initialLife = 100;
    const int initialScore = 0;
    int score = initialScore;
    int life = initialLife;

    cout << "Enter Option (1~7) : ";
    cin >> option;

    WordInfo words[numWords];

    int speed = 1;
    int change = 0;
    const int speedChangeInterval = 3; 

    while (life > 0) {
        for (int i = 0; i < numWords; ++i) {
            words[i].x = rand() % (screenWidth / 4) + (screenWidth / 4) * (rand() % 4);
            words[i].y = 0;

            words[i].word = generateStringWithOption(option);

            while (words[i].y < screenHeight) {
                drawWord(words[i].word, words[i].x, words[i].y);
                drawScoreAndLife(score, life);

                Sleep(1000 / speed);

                if (_kbhit()) {
                    string userInput = "";
                    for (int j = 0; j < words[i].word.length(); ++j) {
                        char ch = _getch();
                        userInput += ch;
                        drawUserInput(userInput);
                    }

                    if (userInput == words[i].word) {
                        clearWord(words[i].x, words[i].y, words[i].word.length());
                        userInput = "";
                        score += 10;
                        break;
                    }
                    
                }
                else {
                    clearWord(words[i].x, words[i].y, words[i].word.length());
                    words[i].y += screenHeight / 10;

                    if (words[i].y == screenHeight-1) {
                        life -= 10;
                    }
                    if (life == 0) {
                        cout << "Game Over! / " << " Your Score : " << score << endl;
                        return 0;
                    }
                }
            }
        }
        change++;
        if (change == speedChangeInterval) {
            speed = rand() % 3 + 1; 
            change = 0;
        }
    }

    return 0;
}