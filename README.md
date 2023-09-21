# Connect Four Game

This is a C++ implementation of the classic game Connect Four. The game is designed to be played on the console and includes various features such as saving and loading games, high score tracking, and a simple menu system.

## Prerequisites

Before you begin, ensure you have the following libraries installed:
- iostream
- string
- vector
- tuple
- unordered_set
- algorithm
- fstream
- chrono
- windows.h
- iomanip
- conio.h

## How to Play

1. Compile and run the program.
2. Use the menu to select one of the following options:
   - Start a New Game
   - Save This Game
   - Load a Game
   - Back To The Game
   - Print Dash Board
   - Exit
3. If you start a new game, you can choose the number of rows and columns (minimum 4x4) or use the default 6x7 grid.
4. You can play with two players or against the computer (randomized moves for player 'o').
5. In the game, enter the column number where you want to place your token. The game will switch between players ('x' and 'o') automatically.
6. The game ends when one player connects four tokens vertically, horizontally, or diagonally, or when the grid is full (a draw).
7. You can save the game at any time or load a previously saved game.

## Features

- Two-player mode or play against the computer.
- Game saves the current time and date when saving.
- High scores are recorded and displayed on the dashboard.
- Randomized computer moves for added challenge.

## High Scores

The program records high scores in a file called "High Scores.txt." The top 10 players and their scores are displayed on the dashboard.

## Saving and Loading Games

You can save a game in progress and load it later. Saved games are stored in a file named "Saved.txt." The game state, including the board configuration and player scores, is saved.

## Enjoy the Game!

This Connect Four game provides hours of entertainment and a chance to test your strategic skills. Have fun playing and trying to achieve the highest score on the leaderboard!
