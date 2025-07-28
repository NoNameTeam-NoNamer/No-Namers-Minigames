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
	system("title 某个不想起名的小游戏集");
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
	cout << "\n(c)No Name Team 2025,保留所有权利。" << endl;
	// 播放低音 do
	Beep(262, 150);
	// 播放中音 mi
	Beep(330, 150);
	// 播放高音 so
	Beep(392, 150);
	system("pause");
	system("cls");
	system("title 某个不想起名的小游戏集");
	cout << "某个不想起名的小游戏集 0.1.0" << endl;
	cout << "此版本为开发版本，不代表最终品质，程序随时可能崩溃。" << endl;
	cout << "别忘了前往 https://github.com/NoNameTeam-NoNamer/No-Namers-Minigames 关注最新版本进展！" << endl;
	cout << endl;
	int gameChoice;
	while (1) {
		cprintf("1;34", "输入数字选择以下操作：\n");
		cprintf("2;34", "1 = 扫雷\n");
		cprintf("2;34", "2 = 魔盒\n");
		cprintf("2;34", "3 = 数独\n");
		cprintf("1;34", "4 = 数雷\n");
		cprintf("2;34", "5 = 迷宫\n");
		cprintf("2;36", "6 = 贪吃蛇\n");
		cprintf("2;36", "7 = 国象\n");
		cprintf("2;32", "8 = 麻将（需要局域网）\n");
		cprintf("2;32", "9 = 斗地主（需要局域网）\n");
		cprintf("1;34", "10 = 退出\n");
		cin >> noskipws >> gameChoice;
		cin.clear(); // 重置错误标志
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空输入缓冲区
		if (cin.fail() || gameChoice < 1 || gameChoice > 10) { // 检测输入是否失败
			goto invaildChoice;
		}
		if (gameChoice == 10) {
			cprintf("1;33", "正在退出...\n");
			// 播放高音 so
			Beep(392, 150);
			// 播放中音 mi
			Beep(330, 150);
			// 播放低音 do
			Beep(262, 150);
			return 0;
		}
		else if (gameChoice == 1) {
			cprintf("1;33", "开发中，敬请期待！\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 2) {
			cprintf("1;33", "开发中，敬请期待！\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 3) {
			cprintf("1;33", "开发中，敬请期待！\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 4) {
            system("cls");
			system("title 某个不想起名的小游戏集 0.1.0 -- 数雷");
			constexpr int MIN_NUMBER = std::numeric_limits<int>::min();
			constexpr int MAX_NUMBER = std::numeric_limits<int>::max();
			int Nu_aimNumber = getRand(MIN_NUMBER, MAX_NUMBER), Nu_gameCount = 0,Nu_inputNumber,Nu_Min = MIN_NUMBER,Nu_Max = MAX_NUMBER,Nu_botNumber;
            char Nu_aimNumberStr[256];
			string Nu_inputStr;
            snprintf(
                Nu_aimNumberStr, sizeof(Nu_aimNumberStr),
                "在本游戏中，您需要和一个人机一起找出一个介于%d到%d的整数。\n",
				MIN_NUMBER, MAX_NUMBER
            );
            cprintf("1;34", Nu_aimNumberStr);
			cprintf("1;33", "但是千万不要说出这个数，不然您将激活地雷！\n");
			system("pause");
			while (1)
			{
				Nu_gameCount++;
			Nu_Input:
				system("cls");
				system("title 某个不想起名的小游戏集 0.1.0 -- 数雷");
				snprintf(
					Nu_aimNumberStr, sizeof(Nu_aimNumberStr),
					"最小：%d | 最大：%d | 回合：%d\n\n",
					Nu_Min, Nu_Max, Nu_gameCount
				);
				cprintf("1;35", Nu_aimNumberStr);
				cprintf("1;34", "请输入一个数：\n");
				
				cin >> noskipws >> Nu_inputStr;
				cin.clear(); // 重置错误标志
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空输入缓冲区
				if (isNumber(Nu_inputStr)) { // 检测输入是否是数字
					try{
					Nu_inputNumber = stoi(Nu_inputStr); // 将字符串转换为整数
					}
					catch (const std::out_of_range&) {
						cprintf("1;31", "您输入的数超出了限制！\n");
						Beep(880, 200);
						system("pause");
						goto Nu_Input; // 如果转换失败，重新输入
					}
					catch (const std::invalid_argument&) {
						cprintf("1;31", "无效输入，请您输入数字！\n");
						Beep(880, 200);
						system("pause");
						goto Nu_Input; // 如果转换失败，重新输入
					}
					if (Nu_inputNumber < Nu_Min || Nu_inputNumber > Nu_Max) {
						cprintf("1;31", "您输入的数不在“最小”与“最大”之间！\n");
						Beep(880, 200);
						system("pause");
						goto Nu_Input; // 如果输入不在范围内，重新输入
					}
					if (Nu_inputNumber == Nu_aimNumber) {
						cprintf("1;31", "砰！你踩中了数雷！\n");
						break; // 炸了，退出循环
					}
					else if (Nu_inputNumber < Nu_aimNumber) {
						cprintf("1;32", "您的数字比数雷的小。\n");
						system("pause");
						Nu_Min = Nu_inputNumber + 1; // 更新最小值
					Nu_bot:
						Nu_botNumber = getRand(Nu_Min, Nu_Max); // 让bot猜测
						snprintf(
							Nu_aimNumberStr, sizeof(Nu_aimNumberStr),
							"人机：%d\n",
							Nu_botNumber
						);
						cprintf("1;34", Nu_aimNumberStr);
						system("pause");
						if (Nu_botNumber == Nu_aimNumber) {
							cprintf("1;31", "砰！人机踩中了数雷！\n");
							break; // 炸了，退出循环
						}
						else if (Nu_botNumber < Nu_aimNumber) {
							cprintf("1;36", "人机的数字比数雷的小。\n");
							system("pause");
							Nu_Min = Nu_botNumber + 1; // 更新最小值
						}
						else {
							cprintf("1;36", "人机的数字比数雷的大。\n");
							system("pause");
							Nu_Max = Nu_botNumber - 1; // 更新最大值
						}
					}
					else {
						cprintf("1;32", "您的数字比数雷的大。\n");
						system("pause");
						Nu_Max = Nu_inputNumber - 1; // 更新最大值
						goto Nu_bot; // 让bot猜测
					}
				}
				else {
					cprintf("1;31", "无效输入！请您输入数字！\n");
					Beep(880, 200);
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
			cprintf("1;33", "开发中，敬请期待！\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 6) {
			cprintf("1;33", "开发中，敬请期待！\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 7) {
			cprintf("1;33", "开发中，敬请期待！\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 8) {
			cprintf("1;33", "开发中，敬请期待！\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 9) {
			cprintf("1;33", "开发中，敬请期待！\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else {
			invaildChoice:
			cprintf("1;31", "输入无效，请重试！\n");
			Beep(880, 200);
			system("pause");
		}
		system("cls");
		system("title 某个不想起名的小游戏集");
	}
}
