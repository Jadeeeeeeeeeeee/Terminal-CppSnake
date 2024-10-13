#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>  



void GameOver();
void SpawnFruit();
void game();

std::string grid[10][20] = {
	{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
	{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
    {" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
	{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
	{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
	{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
	{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
	{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
	{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "},
	{" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "}
};

std::vector<std::pair<int, int>> SnakePos;

std::string direction = "up";
bool GameIsOn = true;
char input = 'd';
std::pair<int, int> applePos;


void UpdateSnakePos() {
    for (const auto& pos : SnakePos) {
        grid[pos.first][pos.second] = " ";
    }


    for (size_t i = SnakePos.size() - 1; i > 0; --i) {
        SnakePos[i] = SnakePos[i - 1];
    }

   
    if (input == 'w') {
        if (SnakePos[0].first == 0) {  
            GameOver();
            return;
        }
        SnakePos[0].first--;
    }
    else if (input == 's') {
        if (SnakePos[0].first == 9) {  
            GameOver();
            return;
        }
        SnakePos[0].first++;
    }
    else if (input == 'a') {
        if (SnakePos[0].second == 0) {  
            GameOver();
            return;
        }
        SnakePos[0].second--;
    }
    else if (input == 'd') {
        if (SnakePos[0].second == 19) {  
            GameOver();
            return;
        }
        SnakePos[0].second++;
    }

    for (size_t i = SnakePos.size() - 1; i > 0; i--) {
        if (SnakePos[0].first == SnakePos[i].first && SnakePos[0].second == SnakePos[i].second) {
            GameOver();
        }
    }

    for (size_t j = 0; j < SnakePos.size(); j++) {
        grid[SnakePos[j].first][SnakePos[j].second] = "0";
    }


    if (SnakePos[0].first == applePos.first && SnakePos[0].second == applePos.second) {
        std::pair<int, int> newSegment = SnakePos.back();
        if (input == 'w') newSegment.first++;
        else if (input == 's') newSegment.first--;
        else if (input == 'a') newSegment.second++;
        else if (input == 'd') newSegment.second--;

        SnakePos.push_back(newSegment);
        SpawnFruit(); 
    }
}


void GameOver() {
    system("cls");
    std::string input = " ";
    int finalScore = SnakePos.size() - 3;
    if (finalScore < 0) {
        finalScore = 0;
    }

    std::cout << "Game Over!!!" << std::endl;
    std::cout << "Your score was: " << finalScore << std::endl;
    std::cout << "Do you want to play again? (y/n)" << std::endl;
    std::getline(std::cin, input);

    if (input == "y" || input == "Y") {
        SnakePos.clear();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 19; j++) {
                grid[i][j] = " ";
            }
        }
        applePos = { -1, -1 };
        input = 'w';  
        SnakePos.push_back({ 4, 8 }); 
        SnakePos.push_back({ 5, 8 });
        SnakePos.push_back({ 6, 8 });
        SpawnFruit();  
        GameIsOn = true;
        game();  
    }
    else if (input == "n" || input == "N") {
        exit(0);
    }
}
	

void PrintGrid() {
	std::cout << "          -----------------------" << std::endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			if (j == 19) {
				std::cout << grid[i][j] << "|"; 
			}
			else if (j == 0) {
				std::cout << "          | " << grid[i][j];
			}
			else {
				std::cout << grid[i][j];  
			}
		}
		std::cout << std::endl; 
	}
	std::cout << "          -----------------------" << std::endl;
}
void SpawnFruit() {
    bool spawned = false;
    while (!spawned) {
        int y = rand() % 10; 
        int x = rand() % 20; 
        if (grid[y][x] == " ") { 
            grid[y][x] = "@";
            applePos.first = y;
            applePos.second = x;
            spawned = true;
        
        }
    }
}

void game() {
	while (GameIsOn) {
		if (_kbhit()) {
            char tempInput = tolower(_getch()); 
            if (tempInput == 's' && input != 'w') {
                input = tempInput;
            } if (tempInput == 'w' && input != 's') {
                input = tempInput;
            } if (tempInput == 'd' && input != 'a') {
                input = tempInput;
            } if (tempInput == 'a' && input != 'd') {
                input = tempInput;
            }
            else {
                
            }
		}
		system("CLS");
		UpdateSnakePos();
		PrintGrid();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

int main() {
    srand((unsigned)time(NULL));
    SpawnFruit();
    SnakePos.push_back({ 4, 8 });  
    SnakePos.push_back({ 5, 8 });  
    SnakePos.push_back({ 6, 8 });  
	game();
	return 0;
}