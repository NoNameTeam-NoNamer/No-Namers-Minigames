#define NOMINMAX
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include<stdio.h>
#include <limits> // 用于 numeric_limits
using namespace std;
/**
* @brief 彩色输出，请注意输出后续的内容将被清除全部效果，且本输出无自动换行！
* @param Color 颜色代码,用“;”隔开
* @param Text 内容
* @tparam 0 重置 30 黑字 40 黑背
* @tparam 1 高亮 31 红字 41 红背
* @tparam 2 暗淡 32 绿字 42 绿背
* @tparam 4 下划 33 黄字 43 黄背
* @tparam 5 闪烁 34 蓝字 44 蓝背
* @tparam 6 反显 35 紫字 45 紫背
* @tparam 7 反转 36 青字 46 青背
* @tparam 8 隐藏 37 白字 47 白背
*/
static void cprintf(const char* Color,const char* Text){
	printf("\033[0m\033[%sm%s\033[0m",Color,Text);
}

int main()
{
	system("title No Namers' Minigames 0.0.1");
	system("color 02");
	cout << R"(                            (c)
       XXXXXXXXXXXXXXXXXXX
       XXXXXXXXXXXXXXXXXXX
              XXXXX
XXXXX  XX XX  XXXXX      
XXXXXX XX XX  XXXXX      
XXXXXXXXX XX  XXXXX      
XXXXXXXXX XX  XXXXX      
XXXXX XXX XX  XXXXX      
XXXXX  XXXXX  XXXXX      
XXXXX   XXXX  XXXXX      
         XXX  XXXXX      
          XXX XXXXX      
XXXXX      XXXXXXXX      
XXXXXX      XXXXXXX      
XXXXXXX      XXXXXX      
XXXXXXXX                 
XXXXX XXX                
XXXXX  XXX    XXXXX      
XXXXX   XXX   XXXXX      
XXXXX    XXX  XXXXX      
XXXXX     XXX XXXXX      
XXXXX      XXXXXXXX      
XXXXX       XXXXXXX      
XXXXX        XXXXXX)" << endl;
	cout << "\nCopyright No Name Team 2025 all rights reserved." << endl;
	system("pause");
	system("cls");
	cout << "No Namers' Minigame 0.0.1" << endl;
	cout << "This is a debug version,nothing can be sured to add in the final version and the program may crash anytime." << endl;
	cout << "Don't forget check new version on https://github.com/NoNameTeam-NoNamer/No-Namers-Minigames." << endl;
	cout << endl;
	int gameChoice;
	while (1) {
		cprintf("1;34", "Enter number to select the game you want to play:\n");
		cprintf("2;34", "1 = Minesweeper\n");
		cprintf("2;34", "2 = Push Box\n");
		cprintf("2;34", "3 = Sudoku\n");
		cprintf("2;34", "4 = Numbermine\n");
		cprintf("2;34", "5 = Maze\n");
		cprintf("2;36", "6 = Gluttonous Snake\n");
		cprintf("2;36", "7 = Chess\n");
		cprintf("2;32", "8 = Mahjong(Local network needed)\n");
		cprintf("2;32", "9 = Fight The Landlord(Local network needed)\n");
		cprintf("1;34", "10 = Exit\n");
		cin >> noskipws >> gameChoice;
		cin.clear(); // 重置错误标志
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空输入缓冲区
		if (cin.fail() || gameChoice < 1 || gameChoice > 10) { // 检测输入是否失败
			goto invaildChoice;
		}
		if (gameChoice == 10) {
			cprintf("1;33", "Exiting...\n");
			return 0;
		}
		else if (gameChoice == 1) {
			cprintf("1;33", "You've selected Minesweeper.But it is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 2) {
			cprintf("1;33", "You've selected Flying Bird.But it is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 3) {
			cprintf("1;33", "You've selected Sudoku.But it is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 4) {
			cprintf("1;33", "You've selected Numbermine.But it is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 5) {
			cprintf("1;33", "You've selected Maze.But it is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 6) {
			cprintf("1;33", "You've selected Gluttonous Snake.But it is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 7) {
			cprintf("1;33", "You've selected Chess.But it is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 8) {
			cprintf("1;33", "You've selected Mahjong.But it is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 9) {
			cprintf("1;33", "You've selected Fight The Landlord.But it is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else {
			invaildChoice:
			cprintf("1;31", "Invalid choice, please try again.\n");
			system("pause");
		}
		system("cls");
	}
}
