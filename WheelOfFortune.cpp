//
// Created by Hannah Sheridan on 2/5/23.
//
#include "WheelOfFortune.h"
#include "Player.h"

WheelOfFortune::WheelOfFortune() {
    phrase = "";
    category = "";
    lettersGuessed = {};
    categories = {};
    phrases = {};
    vowelsGuessed = 0;

    // Fill players vector
    currentPlayer = 0;
    Player player1("Player 1");
    Player player2("Player 2");
    setPlayers(player1, player2);

    srand(time(nullptr));

}

string WheelOfFortune::getPhrase() {
    return this->phrase;
}

string WheelOfFortune::getCategory() {
    return this->category;
}

vector<string> WheelOfFortune::getCategories() {
    return this->categories;
}
vector<string> WheelOfFortune::getPhrases() {
    return this->phrases;
}

char WheelOfFortune::getLastGuessed() {
    return (char) toupper(lastGuessed);
}

vector<char> WheelOfFortune::getLettersGuessed() {
    return this->lettersGuessed;
}

vector<Player> WheelOfFortune::getPlayers() {
    return this->players;
}

Player WheelOfFortune::getCurrentPlayer() {
    return players[currentPlayer];
}

void WheelOfFortune::setPhrase (string p) {
    vowelsGuessed = 0;
    lettersGuessed.clear();
    this->phrase = p;
}

void WheelOfFortune::setCategory(string c) {
    this->category = c;
}

void WheelOfFortune::setPlayers(Player player1, Player player2) {
    players.clear();
    players.push_back(player1);
    players.push_back(player2);
}
void WheelOfFortune::setCurrentPlayer(int index) {
    this->currentPlayer = index;
}

void WheelOfFortune::setCurrentPlayerBalance(int bal) {
    players[currentPlayer].setBalance(bal);
}

void WheelOfFortune::addGuessed(char letter) {
    lettersGuessed.push_back(toupper(letter));
}

void WheelOfFortune::printGameOptions(ostream& outs) {
    if (!(players[currentPlayer].sufficientFunds()) || vowelsGuessed == 5) {
        outs << endl << "<><><>Options<><><>" << endl;
        outs << "C - Guess a consonant" << endl << "P - Solve the puzzle!" << endl << "E - Exit game" << endl;
        outs << "<><><><><><><><><><>" << endl << endl;
    }
    else {
        outs << endl << "<><><>Options<><><>" << endl;
        outs << "C - Guess a consonant" << endl << "V - Buy a vowel for $250" << endl << "P - Solve the puzzle!" << endl << "E - Exit game" << endl;
        outs << "<><><><><><><><><><>" << endl << endl;
    }

}

char WheelOfFortune::getOption(ostream& outs, istream& ins) {
    string option;

    bool valid = false;

    printGameOptions(outs);

    outs << "Choose an option: ";
    getline(ins, option);

    if (!(players[currentPlayer].sufficientFunds()) || vowelsGuessed == 5) {
        while (!valid) {
            if (option == "") {
                valid = false;
                outs << "No input. Please choose an option: ";
                ins.clear();
                getline(ins, option);
            } else if (toupper(option[0]) == 'V' && vowelsGuessed == 5) {
                valid = false;
                outs << "There are no vowels left to guess! Please choose another option: ";
                ins.clear(0);
                getline(ins, option);
            } else if (toupper(option[0]) == 'V') {
                valid = false;
                outs << "You do not have enough money to buy a vowel. Please choose another option: ";
                ins.clear(0);
                getline(ins, option);
            } else if (option.length() != 1 ||
                       toupper(option[0]) != 'C' && toupper(option[0]) != 'P' && toupper(option[0]) != 'E') {
                valid = false;
                outs << "Did you even look at the options? Here they are again: " << endl;
                printGameOptions(outs);

                ins.clear();
                outs << "Choose an option: ";
                getline(ins, option);
            } else {
                valid = true;
            }
        }
    }
    else {
        while (!valid) {
            if (option == "") {
                valid = false;
                outs << "No input. Please choose an option: ";
                ins.clear();
                getline(ins, option);
            }
            else if (option.length() != 1 || toupper(option[0]) != 'C' && toupper(option[0]) != 'V' && toupper(option[0]) != 'P' && toupper(option[0]) != 'E') {
                valid = false;
                outs << "Did you even look at the options? Here they are again: " << endl;
                printGameOptions(outs);

                ins.clear();
                outs << "Choose an option: ";
                getline(ins, option);
            }
            else {
                valid = true;
            }
        }
    }
    return toupper(option[0]);
}

void WheelOfFortune::printRoundOptions(ostream& outs) {
    outs << endl << "<><><>Options<><><>" << endl;
    outs << "S - Spin the wheel!" << endl << "E - Exit game" << endl;
    outs << "<><><><><><><><><><>" << endl << endl;
    outs << "Choose an option: ";
}

bool WheelOfFortune::activePlayer(ostream& outs, istream& ins) {
    string active;
    bool valid = false;
    printRoundOptions(outs);
    getline(ins, active);

    while (!valid) {
        if (active == ""){
            valid = false;
            outs << "No input. Choose an option: ";
            ins.clear();
            getline(ins, active);
        }
        else if (active.length() != 1) {
            valid = false;
            outs << "That is not an option! Choose one from the list below: " << endl;
            printRoundOptions(outs);
            ins.clear();
            getline(ins, active);
        }

        else if (toupper(active[0]) != 'E' && toupper(active[0]) != 'S') {
            valid = false;
            outs << "That is not an option! Choose one from the list below: " << endl;
            printRoundOptions(outs);
            ins.clear();
            getline(ins, active);
        }
        else {
            valid = true;
        }

    }

    if (active == "S" || active == "s") {
        return true;
    }
    else {
        return false;
    }
}

bool WheelOfFortune::readFile(string filename) {
    phrases.clear();
    categories.clear();
    ifstream inFile;
    inFile.open(filename);

    char comma, quote;

    if (!inFile) {
        return false;
    }

    while (inFile && inFile.peek() != EOF) {
        if (inFile.peek() == '"') {
            inFile >> quote;
            getline(inFile, category, '"');
            inFile >> comma;
        }
        else {
            getline(inFile, category, ',');
        }

        if (inFile.peek() == '"') {
            inFile >> quote;
            getline(inFile, phrase, '"');
            inFile >> comma;
        }
        else {
            getline(inFile, phrase, '\n');
        }

        categories.push_back(category);
        phrases.push_back(phrase);
    }
    inFile.close();

    return true;
}

void WheelOfFortune::setRandom() {
    int index = rand() % phrases.size();
    vowelsGuessed = 0;
    lettersGuessed.clear();
    phrase = phrases[index];
    category = categories[index];
}

int WheelOfFortune::guessConsonant(ostream& outs, istream& ins) {
    int guessed = 0;
    bool valid = false;

    string letter;

    outs << "Guess a consonant: ";
    getline(ins, letter);

    while (!valid) {
        if (letter == "") {
            valid = false;

            outs << "No input. Guess a consonant: ";
            ins.clear();
            getline(ins, letter);
        }
        else if (letter.length() != 1 || !isalpha(letter[0]) || find(vowels.begin(), vowels.end(), toupper(letter[0])) != vowels.end()){
            valid = false;

            outs << "That is not a consonant! Try again: ";
            ins.clear();
            getline(ins, letter);
        }
        else if (find(lettersGuessed.begin(), lettersGuessed.end(), toupper(letter[0])) != lettersGuessed.end()) {
            valid = false;

            outs << "That letter has already been guessed!";
            outs << " Try again: ";
            ins.clear();
            getline(ins, letter);
        }
        else {
            valid = true;
        }
    }

    for (int i = 0; i < phrase.length(); ++i) {
        if (toupper(phrase[i]) == toupper(letter[0])) {
            ++guessed;
        }
    }

    lastGuessed = letter[0];
    lettersGuessed.push_back((char) toupper(letter[0]));

    // Update balance of the current player
    players[currentPlayer].guessConsonant(guessed);

    return guessed;


}

int WheelOfFortune::guessVowel(ostream& outs, istream& ins) {
    int guessed = 0;
    string letter;
    bool valid = false;

    outs << "Guess a vowel: ";

    getline(ins, letter);

    while (!valid) {
        if (letter == "") {
            valid = false;
            cout << "No input. Guess a vowel: ";
            ins.clear();
            getline(ins, letter);
        }
        else if (letter.length() != 1 || find(vowels.begin(), vowels.end(), toupper(letter[0])) == vowels.end()) {
            valid = false;
            cout << "That is not a vowel! Try again: ";
            ins.clear();
            getline(ins, letter);
        }
        else if (find(lettersGuessed.begin(), lettersGuessed.end(), toupper(letter[0])) != lettersGuessed.end()) {
            valid = false;
            cout << "That letter has already been guessed! Try again: ";
            ins.clear();
            getline(ins, letter);
        }
        else {
            valid = true;
        }

    }

    for (int i = 0; i < phrase.length(); ++i) {
        if (toupper(phrase[i]) == toupper(letter[0])) {
            guessed++;
        }
    }
    lastGuessed = letter[0];
    lettersGuessed.push_back((char) toupper(letter[0]));

    // Update current player balance (- 250)
    players[currentPlayer].buyVowel();
    ++vowelsGuessed;

    return guessed;

}

void WheelOfFortune::printPhrase(ostream& outs) {
    int length = 0;
    /*
    outs << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
    outs << "<>                                                      <>" << endl;*/
    outs << "            ";
    //outs << setw(53) << left;
    bool guessed = false;
    for (int i = 0; i < phrase.size(); ++i) {
        for (int j = 0; j < lettersGuessed.size(); ++j) {
            if (toupper(phrase[i]) == toupper(lettersGuessed[j])) {
                guessed = true;
            }
        }
        if (guessed) {
            outs << (char) toupper(phrase[i]) << " ";
        }
        else if (!isalpha(phrase[i])) {
            outs << phrase[i] << " ";
        }
        else if (isspace(phrase[i])) {
            outs << "   ";
        }
        else {
            outs << "_ ";
        }
        guessed = false;
        ++length;
    }

    outs << endl;
    outs  << "            " << "<><><> " << category << " <><><>" << endl;
    printLettersGuessed(outs);
    /*
    outs << endl << "<>                                                      <>" << endl;
    outs << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;*/
}

void WheelOfFortune::printLettersGuessed(ostream& outs) {
    // Print ascii values of 65-90
    outs << endl;
    outs << "            --------------------------" << endl;
    outs << "            ";
    for (int alpha = 65; alpha <= 90; ++alpha) {
        if (find(lettersGuessed.begin(), lettersGuessed.end(), alpha) != lettersGuessed.end()) {
            outs << ":: ";
        }
        else {
            outs << char(alpha) << " ";
        }
        if (alpha == 77) {
            outs << endl << "            ";
        }
    }
    outs << endl << "            --------------------------";
    outs << endl;
}

bool WheelOfFortune::solvePuzzle(string guess) {
    int flag = 0;

    for (int i = 0; i < phrase.size(); ++i) {
        if (toupper(phrase[i]) == toupper(guess[i])) {
            ++flag;
        }
    }

    if (flag == phrase.size()) {
        for (char ch : phrase){
            lettersGuessed.push_back(ch);
        }
        players[currentPlayer].winner();
        return true;
    }
    else {
        return false;
    }
}

bool WheelOfFortune::guessedPhrase() {
    int flag = 0;
    for (int i = 0; i < phrase.length(); ++i) {
        if (!isalpha(phrase[i])) {
            ++flag;
        }
        for (int j = 0; j < lettersGuessed.size(); ++j) {
            if (toupper(phrase[i]) == toupper(lettersGuessed[j])) {
                ++flag;
            }
        }
    }

    if (flag == phrase.length()) {
        players[currentPlayer].winner();
        return true;
    }
    else {
        return false;
    }
}

bool WheelOfFortune::playAgain(ostream& outs, istream& ins) {
    string ans;
    outs << "Play again? (y/n) ";
    getline(ins, ans);

    while (ans.length() != 1 || toupper(ans[0]) != 'Y' && toupper(ans[0]) != 'N') {
        outs << "Invalid input. Please type y or n: " << endl;
        ins.clear();
        getline(ins, ans);
    }

    if (toupper(ans[0]) == 'Y') {
        lettersGuessed = {};
        return true;
    }
    else {
        return false;
    }
}

void WheelOfFortune::switchPlayers() {
    if (currentPlayer == 0) {
        ++currentPlayer;
    }
    else if (currentPlayer == 1){
        --currentPlayer;
    }
    else {
        currentPlayer = 0;
    }
}

void WheelOfFortune::printCurrentPlayerBalance(ostream& outs) {
    outs << players[currentPlayer] << "'s Balance: $" << players[currentPlayer].getBalance() << endl;
}
void WheelOfFortune::printFinalStats(ostream& outs) {
    outs << players[0] << "'s Wins: " << players[0].getNumWins() << endl;
    outs << players[1] << "'s Wins: " << players[1].getNumWins() << endl;
    outs << endl;
    outs << players[0] << "'s Final Balance: $" << players[0].getBalance() << endl;
    outs << players[1] << "'s Final Balance: $" << players[1].getBalance() << endl;
}
bool WheelOfFortune::setPlayerNames(string player1, string player2) {
    // If no input, set to default name
    if (player1 == "" && player2 == "") {
        player1 = "Player 1";
        player2 = "Player 2";
    }
    else if (player1 == "") {
        player1 = "Player 1";
    }
    else if (player2 == "") {
        player2 = "Player 2";
    }

    // If the names are the same, return false
    // Only jump into loop if the strings are suspicious
    if (player1.length() == player2.length()) {
        int flag = 0;
        for (int i = 0; i < player1.length(); ++i) {
            if (toupper(player1[i]) == toupper(player2[i])) {
                ++flag;
            }
        }
        if (flag == player1.length()) {
            return false;
        }
    }

    players[0].setName(player1);
    players[1].setName(player2);
    return true;

}

void WheelOfFortune::printCurrentPlayer(ostream& outs) {
    outs << "Current Player: " << players[currentPlayer] << endl;
}

int WheelOfFortune::spinWheel() {
    int wedge = wheel.spin();
    if (wedge == 0) {
        players[currentPlayer].bankrupt();
    }

    players[currentPlayer].setPrize(wedge);
    return wedge;

}