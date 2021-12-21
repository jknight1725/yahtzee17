# Yahtzee implemented in modern C++
yahtzee is owned by Hasbro
*******************************************************
*  Implementation by      :  James Knight                     
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

This program implements a dice game Yahtzee
It consists of a game class composed of players
The player class is composed by a dice class and a scoresheet class
The game is played in turns. Each turn a player rolls all of their dice. They can elect
to roll any number of dice again or score their current dice configuration. They can roll up to three total times before they must score their dice.
There are 13 different scoring options for the player to choose from.


*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
	Driver program that creates a game of a user determined amount of players
The game gives each player 13 turns. Each turn the player rolls all of their dice.They have two chances to re-roll their choice of any amount of die. After their third total roll or at any point in their turn the player selects a position to place their score on their scoresheet. After the score is recorded the turn is complete.

Name:  game.cpp
	The game class maintains a vector of Player Pointers dynamically allocated via a constructor. The turn method iterates over the vector calling each players turn method.
  

Name: player.cpp
	The Player class contains dice and a scoresheet. A player may roll any amount of dice at a time. The player has methods to display its dice and scoresheet. The turn method rolls all of a players dice then gives the player two chances to either roll die again or score the current roll on their scoresheet. The player has methods to ensure their score selection is valid and methods to write the respective score to the selected location.
   
      
Name: dice.cpp
	The dice class maintains an array of 5 ints. It has methods to mutate any of the indices to a number between one and six. It provides methods to view the dice, sort the dice, and return how often a given number appears in the set of dice. 
   The dice.cpp file also maintains a static RNG used by all instances of Dice. 

Name: scoreSheet.cpp
   The ScoreSheet class maintains an array of 15 different scores found on a Yahtzee scoresheet. It has methods to total several different meaningful values out of these scores such has the total score, the upper score, and the lower score. It provides read/write access to its scores. It has an overloaded << operator for neat printing of the scoresheet.
   
   
*******************************************************
*  Circumstances of programs
*******************************************************
   
   The program was compiled and tested with 
   Apple LLVM version 9.1.0 (clang-902.0.39.2) 
   It was developed using JetBrains CLion 

*******************************************************
*  How to build and run the program
*******************************************************
cd build
cmake ..
make
./yahtzee17
