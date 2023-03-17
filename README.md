# Hannah Sheridan - Open-Ended Project
This program is a Wheel of Fortune game with two players. It has a WheelOfFortune class that holds functions of the game and validates all user input. The WheelOfFortune class "Has-A" Player and a Wheel. The component Player class holds fields and methods specific to each player, like balance, number of wins, and name. This has allowed me to add two players to the game and create new prizes like "Bankrupt" and "Lose a Turn". The Wheel class fills the wheel with different prizes and can spin the wheel. The players are given a puzzle taken randomly from a file and are prompted to guess consonants and vowels. For every letter guessed, that letter will be printed to the console and the current player's balance will be updated. Whichever player solves the puzzle wins the game! 

### Module 2 Concepts Used:
* Component Class Relationship
* File Input

### Known Bugs:
* Game still prompts user to guess a consonant even if all possible consonants have been guessed
* Category does not print centered under the puzzle

### Future Expansions:
* Add a set of game rules for the user
* Improve visual aspects of the game
* Add a component class to represent the puzzle board

### Expected grade: 75
I believe my program is sufficiently complex for an Open-Ended Project. All input is validated correctly and the testing program has multiple test cases for all non-trivial methods that do not take user input. I used multiple concepts from Module 2, including file input and two component classes. My program is organized and has comments, and I began making my Module 2 edits a week before the due date. 

### Citations:
Puzzle file - https://github.com/nelkha2/Project_3/blob/master/Data/Wheel%20of%20Fortune%20Phrases%20Database.csv
toupper() - https://www.programiz.com/cpp-programming/library-function/cctype/toupper
