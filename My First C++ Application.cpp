#define NOMINMAX
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include<stdio.h>
#include <regex>
#include <random>
#include <ctime> // 用于随机数种子
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

// 生成 [min, max] 范围内的随机整数
static int getRand(int min, int max) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

static bool isNumber(const std::string& str) {
	// 匹配整数、小数和带正负号的数字
	std::regex pattern(R"(([-+]?\d+(\.\d+)?))");
	return std::regex_match(str, pattern);
}
int main()
{
	system("title No Namers' Minigames");
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
	cout << "\nCopyright No Name Team 2025,all rights reserved." << endl;
	// 播放低音 do
	Beep(262, 150);
	// 播放中音 mi
	Beep(330, 150);
	// 播放高音 so
	Beep(392, 150);
	system("pause");
	system("cls");
	system("title No Namers' Minigames");
	cout << "No Namers' Minigames 0.1.0" << endl;
	cout << "This is a debug version,nothing can be sured to add in the final version and the program may crash anytime." << endl;
	cout << "Don't forget check new version on https://github.com/NoNameTeam-NoNamer/No-Namers-Minigames." << endl;
	cout << endl;
	int gameChoice;
	while (1) {
		cprintf("1;34", "Enter number to select the game you want to play:\n");
		cprintf("2;34", "1 = Minesweeper\n");
		cprintf("2;34", "2 = Push Box\n");
		cprintf("2;34", "3 = Sudoku\n");
		cprintf("1;34", "4 = Numbermine\n");
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
			// 播放高音 so
			Beep(392, 150);
			// 播放中音 mi
			Beep(330, 150);
			// 播放低音 do
			Beep(262, 150);
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
            system("cls");
			system("title No Namers' Minigames 0.1.0 -- Numberbomb");
			constexpr int MIN_NUMBER = std::numeric_limits<int>::min();
			constexpr int MAX_NUMBER = std::numeric_limits<int>::max();
			int Nu_aimNumber = getRand(MIN_NUMBER, MAX_NUMBER), Nu_gameCount = 0,Nu_inputNumber,Nu_Min = MIN_NUMBER,Nu_Max = MAX_NUMBER,Nu_botNumber;
            char Nu_aimNumberStr[256];
			string Nu_inputStr;
            snprintf(
                Nu_aimNumberStr, sizeof(Nu_aimNumberStr),
                "In this game,you will guess the aim number with a bot,it's an integer between %d to %d.\n",
				MIN_NUMBER, MAX_NUMBER
            );
            cprintf("1;34", Nu_aimNumberStr);
			cprintf("1;33", "BUT DO NOT input the aim number,or you will step on the Numbermine and lose the game!\n");
			system("pause");
			while (1)
			{
				Nu_gameCount++;
			Nu_Input:
				system("cls");
				system("title No Namers' Minigames 0.1.0 -- Numberbomb");
				snprintf(
					Nu_aimNumberStr, sizeof(Nu_aimNumberStr),
					"Min:%d | Max:%d | Round:%d\n\n",
					Nu_Min, Nu_Max, Nu_gameCount
				);
				cprintf("1;35", Nu_aimNumberStr);
				cprintf("1;34", "Please input number:\n");
				
				cin >> noskipws >> Nu_inputStr;
				cin.clear(); // 重置错误标志
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空输入缓冲区
				if (isNumber(Nu_inputStr)) { // 检测输入是否是数字
					try{
					Nu_inputNumber = stoi(Nu_inputStr); // 将字符串转换为整数
					}
					catch (const std::out_of_range&) {
						cprintf("1;31", "Input number is out of range.\n");
						system("pause");
						goto Nu_Input; // 如果转换失败，重新输入
					}
					catch (const std::invalid_argument&) {
						cprintf("1;31", "Invalid input, please enter a valid integer.\n");
						system("pause");
						goto Nu_Input; // 如果转换失败，重新输入
					}
					if (Nu_inputNumber < Nu_Min || Nu_inputNumber > Nu_Max) {
						cprintf("1;31", "Invalid input, please enter a number between \"Min\" and \"Max\".\n");
						system("pause");
						goto Nu_Input; // 如果输入不在范围内，重新输入
					}
					if (Nu_inputNumber == Nu_aimNumber) {
						cprintf("1;31", "Boom! You step on the Numbermine!\n");
						break; // 炸了，退出循环
					}
					else if (Nu_inputNumber < Nu_aimNumber) {
						cprintf("1;32", "Your guess is lower than the Numbermine.\n");
						system("pause");
						Nu_Min = Nu_inputNumber + 1; // 更新最小值
					Nu_bot:
						Nu_botNumber = getRand(Nu_Min, Nu_Max); // 让bot猜测
						snprintf(
							Nu_aimNumberStr, sizeof(Nu_aimNumberStr),
							"Bot:%d\n",
							Nu_botNumber
						);
						cprintf("1;34", Nu_aimNumberStr);
						system("pause");
						if (Nu_botNumber == Nu_aimNumber) {
							cprintf("1;31", "Boom! Bot step on the Numbermine!\n");
							break; // 炸了，退出循环
						}
						else if (Nu_botNumber < Nu_aimNumber) {
							cprintf("1;36", "Bot's guess is lower than the Numbermine.\n");
							system("pause");
							Nu_Min = Nu_botNumber + 1; // 更新最小值
						}
						else {
							cprintf("1;36", "Bot's guess is higher than the Numbermine.\n");
							system("pause");
							Nu_Max = Nu_botNumber - 1; // 更新最大值
						}
					}
					else {
						cprintf("1;32", "Your guess is higher than the Numbermine.\n");
						system("pause");
						Nu_Max = Nu_inputNumber - 1; // 更新最大值
						goto Nu_bot; // 让bot猜测
					}
				}
				else {
					cprintf("1;31", "Invalid input, please enter a valid integer.\n");
					system("pause");
					goto Nu_Input; // 如果非法，重新输入
				}
			}
			byte Nu_beepTime = 64;
			while (Nu_beepTime > 0)
			{
				int Nu_beepLength = 2048 / Nu_beepTime; // 计算每次 beep 的持续时间
				Beep(1660, Nu_beepLength);
				Nu_beepTime--;
			}
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
			Beep(880, 200);
			system("pause");
		}
		system("cls");
		system("title No Namers' Minigames");
	}
}
