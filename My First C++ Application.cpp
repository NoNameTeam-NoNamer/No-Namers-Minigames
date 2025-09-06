#define NOMINMAX
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <stdio.h>
#include <regex>
#include <random>
#include <ctime> // 用于随机数种子
#include <limits> // 用于 numeric_limits
#include <vector>
#include <cmath>
#include <conio.h>
#include <algorithm>
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
	printf("\033[%sm%s\033[0m",Color,Text);
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

static double Mi_calculateDifficulty(int Width, int Height, int mine) {
	double total_cells = Width * Height - 1;
	double d = static_cast<double>(mine) / total_cells;

	// 基准面积（参考经典高级雷区 30x16=480）
	const double base_area = 480.0;
	double area = Width * Height;

	// 动态调整参数（改进点：非线性归一化 + 抑制过大值）
	double area_factor = sqrt(area / base_area); // 用平方根减缓增长
	double sigma_left = 0.4 + 0.1 * atan(area_factor); // 反正切函数约束增长
	double sigma_right = 0.1 + 0.05 * atan(area_factor);

	// 确保 sigma 不超过合理范围（可选）
	sigma_left = std::min(sigma_left, 0.7);   // 上限 0.7
	sigma_right = std::min(sigma_right, 0.2); // 上限 0.2

	// 分段计算难度（保持原有逻辑）
	double difficulty;
	if (d <= 0.8) {
		difficulty = exp(-pow((d - 0.8) / sigma_left, 2));
	}
	else {
		difficulty = exp(-pow((d - 0.8) / sigma_right, 2));
	}

	return difficulty;
}

// 设置光标到(x, y)
static void setCursorPos(int x, int y) {
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

static void Mi_Draw(vector<vector<bool> > minefield, vector<vector<bool> >openfield, vector<vector<bool> >flagfield, vector<vector<bool> >questionfield,int Height,int Width,int x,int y){
	int drawX = 2 + x * 2; // 2是左边界偏移
	int drawY = 3 + y;     // 3是标题和边框行数
	setCursorPos(drawX, drawY);
	if (flagfield[y][x]) {
		cprintf("1;33", "F ");
	}
	else if (questionfield[y][x]) {
		cprintf("1;36", "? ");
	}
	else if (minefield[y][x] && openfield[y][x]) {
		cprintf("1;31", "X ");
	}
	else if (openfield[y][x]) {
		// 替换原有的统计周围地雷数的代码
		int nearbyMines = 0;
		for (int dy = -1; dy <= 1; ++dy) {
			for (int dx = -1; dx <= 1; ++dx) {
				if (dy == 0 && dx == 0) continue; // 跳过自己
				int ny = y + dy;
				int nx = x + dx;
				if (ny >= 0 && ny < Height && nx >= 0 && nx < Width) {
					if (minefield[ny][nx]) {
						nearbyMines++;
					}
				}
			}
		}
		switch (nearbyMines)
		{
		case 1:
			cprintf("34", "1 ");
			break;
		case 2:
			cprintf("32", "2 ");
			break;
		case 3:
			cprintf("31", "3 ");
			break;
		case 4:
			cprintf("2;34", "4 ");
			break;
		case 5:
			cprintf("2;31", "5 ");
			break;
		case 6:
			cprintf("36", "6 ");
			break;
		case 7:
			cprintf("1;30", "7 ");
			break;
		case 8:
			cprintf("37", "8 ");
			break;
		default:
			cprintf("", "  ");
			break;
		}
	}
	else {
		cprintf("1;34", "# ");
	}
}

static int Mi_countFlags(const vector<vector<bool>>& flagfield) {
	int count = 0;
	for (const auto& row : flagfield) {
		for (bool flagged : row) {
			if (flagged) count++;
		}
	}
	return count;
}

static bool Mi_checkWin(const vector<vector<bool>>& minefield,
	const vector<vector<bool>>& openfield) {
	for (int y = 0; y < minefield.size(); y++) {
		for (int x = 0; x < minefield[0].size(); x++) {
			// 如果这个格子不是地雷但也没有被揭开，则游戏未胜利
			if (!minefield[y][x] && !openfield[y][x]) {
				return false;
			}
		}
	}
	return true;
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
	system("title No Namers' Minigames 1.0.0");
	cout << "No Namers' Minigames 1.0.0" << endl;
	cout << "Some games are developing,please waiting for update!" << endl;
	cout << "Don't forget check new version on https://github.com/NoNameTeam-NoNamer/No-Namers-Minigames." << endl;
	cout << endl;
	int gameChoice = 0;
	while (1) {
		cprintf("1;34", "Enter number to select the game you want to play:\n");
		cprintf("1;34", "1 = Minesweeper\n");
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
			int Mi_Width, Mi_Height,Mi_Mines;
			string Mi_inputStr;
			char Mi_aimNumberStr[256];
			int Mi_cursorX = 0;  // 光标水平位置
			int Mi_cursorY = 0;  // 光标垂直位置
			Mi_input:
			while (1) {
				system("cls");
				system("title No Namers' Minigames 1.0.0 -- Minesweeper");
				cprintf("1;34", "Please input the height of the field:\n");
				cin >> noskipws >> Mi_inputStr;
				cin.clear(); // 重置错误标志
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空输入缓冲区
				if (isNumber(Mi_inputStr)) { // 检测输入是否是数字
					try {
						Mi_Height = stoi(Mi_inputStr); // 将字符串转换为整数
					}
					catch (const std::out_of_range&) {
						cprintf("1;31", "Input number is out of range.\n");
						system("pause");
					}
					catch (const std::invalid_argument&) {
						cprintf("1;31", "Invalid input, please enter a valid integer.\n");
						system("pause");
					}
					if (Mi_Height <= 0 || Mi_Height > 64 ) {
						cprintf("1;31", "Invalid input, please enter a number between 1 and 64.\n");
						system("pause");
					}
					else{
						break; // 炸了，退出循环
					}
				}
			}
			while (1) {
				system("cls");
				system("title No Namers' Minigames 1.0.0 -- Minesweeper");
				cprintf("1;34", "Please input the width of the field:\n");
				cin >> noskipws >> Mi_inputStr;
				cin.clear(); // 重置错误标志
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空输入缓冲区
				if (isNumber(Mi_inputStr)) { // 检测输入是否是数字
					try {
						Mi_Width = stoi(Mi_inputStr); // 将字符串转换为整数
					}
					catch (const std::out_of_range&) {
						cprintf("1;31", "Input number is out of range.\n");
						system("pause");
					}
					catch (const std::invalid_argument&) {
						cprintf("1;31", "Invalid input, please enter a valid integer.\n");
						system("pause");
					}
					if (Mi_Width <= 0 || Mi_Width > 128) {
						cprintf("1;31", "Invalid input, please enter a number between 1 and 128.\n");
						system("pause");
					}
					else {
						break; // 炸了，退出循环
					}
				}
			}
			cprintf("1;33", "Please wait for initialize the field...\n");
			vector<vector<bool> > minefield;
			for (int Ay = 0;Ay < Mi_Height;Ay++) {
				vector<bool> minefieldRow;
				for (int Ax = 0;Ax < Mi_Width;Ax++) {
					minefieldRow.push_back(false);
				}
				minefield.push_back(minefieldRow);
			}
			vector<vector<bool> > flagfield = minefield,questionfield = minefield,openfield = minefield;
			while (1) {
				system("cls");
				system("title No Namers' Minigames 1.0.0 -- Minesweeper");
				cprintf("1;34", "Please input the number of the mines:\n");
				cin >> noskipws >> Mi_inputStr;
				cin.clear(); // 重置错误标志
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空输入缓冲区
				if (isNumber(Mi_inputStr)) { // 检测输入是否是数字
					try {
						Mi_Mines = stoi(Mi_inputStr); // 将字符串转换为整数
					}
					catch (const std::out_of_range&) {
						cprintf("1;31", "Input number is out of range.\n");
						system("pause");
					}
					catch (const std::invalid_argument&) {
						cprintf("1;31", "Invalid input, please enter a valid integer.\n");
						system("pause");
					}
					if (Mi_Mines <= 0 || Mi_Mines > Mi_Width * Mi_Height) {
						snprintf(
							Mi_aimNumberStr, sizeof(Mi_aimNumberStr),
							"Invalid input, please enter a integer between 1 and %d.\n",
							Mi_Width*Mi_Height
						);
						cprintf("1;31", Mi_aimNumberStr);
						system("pause");
					}
					else {
						snprintf(
							Mi_aimNumberStr, sizeof(Mi_aimNumberStr),
							"Height:%d | Width:%d | Mines:%d | Difficulty:%f%%\n\nEnter anything to reset the number of mines,enter \"reset\" to reset all,or press enter key start the game. \n",
							Mi_Height, Mi_Width, Mi_Mines, Mi_calculateDifficulty(Mi_Width, Mi_Height, Mi_Mines)*100
						);
						cprintf("1;32", Mi_aimNumberStr);
						cin >> noskipws >> Mi_inputStr;
						cin.clear(); // 重置错误标志
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空输入缓冲区
						if (Mi_inputStr == "") {
							break;
						}
						else if (Mi_inputStr == "reset" || Mi_inputStr == "Reset") {
							goto Mi_input;
						}
					}
			    }
			}
			vector<int> freeplace;
			for (int By = 0;By < Mi_Height;By++) {
				for (int Bx = 0;Bx < Mi_Width;Bx++) {
					freeplace.push_back(By * Mi_Width + Bx);
				}
			}
			for (int minesummonNumber = 0;minesummonNumber < Mi_Mines;minesummonNumber++) {
				// int randomPlace = freeplace.at(getRand(0, static_cast<int>(freeplace.size() - 1)));
				// 修复 lnt-arithmetic-overflow: 在被分配到更广的类型之前，子表达式可能溢出。
				// 问题：freeplace.size() - 1 可能在 size_t 到 int 转换时溢出。
				// 建议修复如下：先将 size_t 转换为 int64_t，再做减法，最后安全地转换为 int。
				int64_t freeplaceSize = static_cast<int64_t>(freeplace.size());
				int randomIndex = getRand(0, static_cast<int>(freeplaceSize - 1));
				int randomPlace = freeplace.at(randomIndex);

				// 删除 freeplace 中与 randomPlace 相等的那一项
				freeplace.erase(std::remove(freeplace.begin(), freeplace.end(), randomPlace), freeplace.end());
				minefield[randomPlace / Mi_Width][randomPlace % Mi_Width] = true;
			}
		minePrint:
			system("cls");
			system("title No Namers' Minigames 1.0.0 -- Minesweeper");
			// 重新输出整个雷区（和原来一样的输出逻辑）
			snprintf(
				Mi_aimNumberStr, sizeof(Mi_aimNumberStr),
				"Height:%d | Width:%d | Mines:%d\n",
				Mi_Height, Mi_Width, Mi_Mines
			);
			cprintf("1;35", Mi_aimNumberStr);
			cprintf("34", "WASD = Cursor | F = Flag | Q = Question | Space = Open | Esc = Escape or reload\n");
			// 显示地雷位置（刷新）
			cprintf("1;34", "+-");
			for (int Cx = 0;Cx < Mi_Width;Cx++) { cprintf("1;34", "--"); }
			cprintf("1;34", "+\n");
			for (int Cy = 0;Cy < Mi_Height;Cy++) {
				cprintf("1;34", "| ");
				for (int Cx = 0;Cx < Mi_Width;Cx++) {
					// 检查是否是光标位置
					if (Cy == Mi_cursorY && Cx == Mi_cursorX) {
						printf("\033[0m\033[7m");
					}
					Mi_Draw(minefield,openfield,flagfield,questionfield,Mi_Height,Mi_Width,Cx,Cy);
				}
				cprintf("1;34", "|");
				cout << endl;
			}
			cprintf("1;34", "+-");
			for (int Cx = 0;Cx < Mi_Width;Cx++) { cprintf("1;34", "--"); }
			cprintf("1;34", "+\n");
			Sleep(100);
			setCursorPos(1, 3);
			keyCheck:
			while (1) {
				// 检测ESC键（退出游戏）
				if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
					goto EscapeAsk;
				}
				// 检测F键（标记旗帜）
				if (GetAsyncKeyState('F') & 0x8000) {
					if (!openfield[Mi_cursorY][Mi_cursorX]) {
						if (questionfield[Mi_cursorY][Mi_cursorX]) { questionfield[Mi_cursorY][Mi_cursorX] = false; }
						flagfield[Mi_cursorY][Mi_cursorX] = !flagfield[Mi_cursorY][Mi_cursorX];
						snprintf(
							Mi_aimNumberStr, sizeof(Mi_aimNumberStr),
							"Height:%d | Width:%d | Mines:%d                ",
							Mi_Height, Mi_Width, Mi_Mines - Mi_countFlags(flagfield)
						);
						setCursorPos(0, 0);
						cprintf("1;35", Mi_aimNumberStr);
						printf("\033[0m\033[7m");
						Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX, Mi_cursorY);
					}
					break;
				}
				if (GetAsyncKeyState('Q') & 0x8000) {
					if (!openfield[Mi_cursorY][Mi_cursorX]) {
						if (flagfield[Mi_cursorY][Mi_cursorX]) { flagfield[Mi_cursorY][Mi_cursorX] = false; }
						questionfield[Mi_cursorY][Mi_cursorX] = !questionfield[Mi_cursorY][Mi_cursorX];
						setCursorPos(0,0);
						snprintf(
							Mi_aimNumberStr, sizeof(Mi_aimNumberStr),
							"Height:%d | Width:%d | Mines:%d                ",
							Mi_Height, Mi_Width, Mi_Mines - Mi_countFlags(flagfield)
						);
						cprintf("1;35", Mi_aimNumberStr);
						printf("\033[0m\033[7m");
						Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX, Mi_cursorY);
					}
					break;
				}
				// 检测WASD移动
				if (GetAsyncKeyState('W') & 0x8000) {
					if (Mi_cursorY == 0) {
						Mi_cursorY = Mi_Height - 1;
						Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX, 0);
					}
					else {
						Mi_cursorY--;
						Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX, Mi_cursorY+1);
					}
					printf("\033[0m\033[7m");
					Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX, Mi_cursorY);
					break;
				}
				if (GetAsyncKeyState('S') & 0x8000) {
					if (Mi_cursorY == Mi_Height - 1) {
						Mi_cursorY = 0;
						Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX, Mi_Height-1);
					}
					else {
						Mi_cursorY++;
						Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX, Mi_cursorY-1);
					}
					printf("\033[0m\033[7m");
					Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX, Mi_cursorY);
					break;
				}
				if (GetAsyncKeyState('A') & 0x8000) {
					if (Mi_cursorX == 0) {
						Mi_cursorX = Mi_Width - 1;
						Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, 0, Mi_cursorY);
					}
					else {
						Mi_cursorX--;
						Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX+1, Mi_cursorY);
					}
					printf("\033[0m\033[7m");
					Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX, Mi_cursorY);
					break;
				}
				if (GetAsyncKeyState('D') & 0x8000) {
					if (Mi_cursorX == Mi_Width - 1) {
						Mi_cursorX = 0;
						Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_Width-1, Mi_cursorY);
					}
					else {
						Mi_cursorX++;
						Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX-1, Mi_cursorY);
					}
					printf("\033[0m\033[7m");
					Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX, Mi_cursorY);
					break;
				}
				// 检测空格键（翻开格子）
				if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
					if (minefield[Mi_cursorY][Mi_cursorX]) {
						for (auto& row : openfield) {
							std::fill(row.begin(), row.end(), true);
						}
						for (int Cy = 0;Cy < Mi_Height;Cy++) {
							for (int Cx = 0;Cx < Mi_Width;Cx++) {
								// 检查是否是光标位置
								if (Cy == Mi_cursorY && Cx == Mi_cursorX) {
									printf("\033[0m\033[7m");
								}
								Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Cx, Cy);
							}
						}
						setCursorPos(0, 4 + Mi_Height);
						cprintf("1;33", "You stepped on the mine!!!BOOM!\n");
						byte Nu_beepTime = 24;
						while (Nu_beepTime > 0)
						{
							int Nu_beepLength = 2048 / Nu_beepTime; // 计算每次 beep 的持续时间
							Beep(1660, Nu_beepLength);
							Nu_beepTime--;
						}
						system("pause");
						goto Mi_Esc;
					}
					vector<int> readyplace, steadyplace, searchingplace;
					int cursorHistory = Mi_cursorY * Mi_Width + Mi_cursorX;
					readyplace.push_back(cursorHistory);
					while (readyplace.size() != 0) {
						searchingplace = readyplace;
						readyplace.clear();
						for (int search : searchingplace) {
							Mi_cursorX = search % Mi_Width;
							Mi_cursorY = search / Mi_Width;
 							if (!flagfield[Mi_cursorY][Mi_cursorX] && !questionfield[Mi_cursorY][Mi_cursorX] && !openfield[Mi_cursorY][Mi_cursorX]) {
								openfield[Mi_cursorY][Mi_cursorX] = true;
								int nearbyMines = 0;
								for (int dy = -1; dy <= 1; ++dy) {
									for (int dx = -1; dx <= 1; ++dx) {
										if (dy == 0 && dx == 0) continue;
										int ny = Mi_cursorY + dy, nx = Mi_cursorX + dx;
										if (ny >= 0 && ny < Mi_Height && nx >= 0 && nx < Mi_Width) {
											if (minefield[ny][nx]) nearbyMines++;
											else { steadyplace.push_back((Mi_cursorY + dy) * Mi_Width + Mi_cursorX + dx); }
										}
									}
								}
								if (nearbyMines == 0) {
									// 合并 steadyplace 到 readyplace，并去重
									for (int v : steadyplace) {
										if (find(readyplace.begin(), readyplace.end(), v) == readyplace.end()) {
											readyplace.push_back(v);
										}
									}
								}
								steadyplace.clear();
								Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX, Mi_cursorY);
							}
						}
					}
					Mi_cursorX = cursorHistory % Mi_Width;
					Mi_cursorY = cursorHistory / Mi_Width;
					setCursorPos(Mi_cursorX, Mi_cursorY);
					printf("\033[0m\033[7m");
					Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Mi_cursorX, Mi_cursorY);
					if (Mi_checkWin(minefield,openfield)) {
						for (auto& row : openfield) {
							std::fill(row.begin(), row.end(), true);
						}
						for (int Cy = 0;Cy < Mi_Height;Cy++) {
							for (int Cx = 0;Cx < Mi_Width;Cx++) {
								// 检查是否是光标位置
								if (Cy == Mi_cursorY && Cx == Mi_cursorX) {
									printf("\033[0m\033[7m");
								}
								Mi_Draw(minefield, openfield, flagfield, questionfield, Mi_Height, Mi_Width, Cx, Cy);
							}
						}
						setCursorPos(0, 4 + Mi_Height);
						cprintf("1;34", "Nice job!All mines were detected by you!\n");
						Beep(660, 500);
						Sleep(100);
						Beep(660,1000);
						system("pause");
						goto Mi_Esc;
					}
					break;
				}
			}
			setCursorPos(2+Mi_cursorX*2, 3+Mi_cursorY);
			Sleep(128);
			goto keyCheck;
			if (0) {
			EscapeAsk:
				setCursorPos(0, 4 + Mi_Height);
				cprintf("1;33", "Are you really sure to escape???(Enter \"Y\" to ensure,not escape will print all field again)\n");
				cin >> noskipws >> Mi_inputStr;
				cin.clear(); // 重置错误标志
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空输入缓冲区
				if (!(Mi_inputStr == "Y" || Mi_inputStr == "y")) {
					goto minePrint;
				}
			}
		Mi_Esc:	
			system("title No Namers' Minigames 1.0.0");
		}
		else if (gameChoice == 2) {
			cprintf("1;33", "It is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 3) {
			cprintf("1;33", "It is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 4) {
            system("cls");
			system("title No Namers' Minigames 1.0.0 -- Numberbomb");
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
				system("title No Namers' Minigames 1.0.0 -- Numberbomb");
				snprintf(
					Nu_aimNumberStr, sizeof(Nu_aimNumberStr),
					"Min:%d | Max:%d | Round:%d\nYou can enter \"Esc\" to escape.\n",
					Nu_Min, Nu_Max, Nu_gameCount
				);
				cprintf("1;35", Nu_aimNumberStr);
				cprintf("1;34", "Please input number:\n");
				cin >> noskipws >> Nu_inputStr;
				cin.clear(); // 重置错误标志
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空输入缓冲区
				if (Nu_inputStr == "esc" || Nu_inputStr == "Esc") {
					cprintf("1;33", "Back to home page......\n");
					goto Nu_Escape;
				}
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
			{
				byte Nu_beepTime = 64;
				while (Nu_beepTime > 0)
				{
					int Nu_beepLength = 2048 / Nu_beepTime; // 计算每次 beep 的持续时间
					Beep(1660, Nu_beepLength);
					Nu_beepTime--;
				}
			}
		Nu_Escape:
			system("pause");
		}
		else if (gameChoice == 5) {
			cprintf("1;33", "It is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 6) {
			cprintf("1;33", "It is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 7) {
			cprintf("1;33", "It is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 8) {
			cprintf("1;33", "It is developing...\n");
			system("pause");
			// Here you would call the function to start the Minesweeper game
			// For example: startMinesweeper();
		}
		else if (gameChoice == 9) {
			cprintf("1;33", "It is developing...\n");
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
