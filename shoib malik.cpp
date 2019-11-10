#include<iostream>
#include<conio.h>
#include<fstream>
#include<windows.h>
using namespace std;
const int MAX_LENGTH = 15;
void GoToXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void printLetter(char ch, int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	cout << ch << " ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
int matchHorizontalForward(int row, int col, char grid[][MAX_LENGTH], char word[]) {
	//check forward
	bool found = true;
	for (int i = col, j = 0; word[j] != NULL && found; i++, j++)
	{
		if (i >= MAX_LENGTH)
			return -1;
		if (grid[row][i] != toupper(word[j])) {
			found = false;
		}
	}
	if (found)
		return 1;
	else
		return -1;
}
int matchHorizontalReverse(int row, int col, char grid[][MAX_LENGTH], char word[]) {
	//check reverse
	bool found = true;
	for (int i = col, j = 0; word[j] != NULL && found; i--, j++)
	{
		if (i < 0)
			return -1;
		if (grid[row][i] != toupper(word[j])) {
			found = false;
		}
	}
	if (found)
		return 2;
	else
		return -1;
}
int matchVerticalForward(int row, int col, char grid[][MAX_LENGTH], char word[]) {
	bool found = true;
	for (int i = row, j = 0; word[j] != NULL && found; i++, j++)
	{
		if (i >= MAX_LENGTH)
			return -1;
		if (grid[i][col] != toupper(word[j])) {
			found = false;
		}
	}
	if (found)
		return 3;
	else
		return -1;
}
int matchVerticalReverse(int row, int col, char grid[][MAX_LENGTH], char word[]) {
	bool found = true;
	for (int i = row, j = 0; word[j] != NULL && found; i--, j++)
	{
		if (i < 0)
			return -1;
		if (grid[i][col] != toupper(word[j])) {
			found = false;
		}
	}
	if (found)
		return 4;
	else
		return -1;
}
int matchDiagonalForward(int row, int col, char grid[][MAX_LENGTH], char word[]) {
	bool found = true;
	int direction = 0;
	for (int i = row, j = col, k = 0; word[k] != NULL && found; k++, i++, j++) {
		if (i >= MAX_LENGTH || j >= MAX_LENGTH) {
			found = false;
			break;
		}
		if (grid[i][j] != toupper(word[k])) {
			found = false;
		}
	}
	if (found == true) {
		direction = 5;
	}
	if (!found) {
		found = true;
		for (int i = row, j = col, k = 0; word[k] != NULL && found; k++, i++, j--) {
			if (i >= MAX_LENGTH || j < 0) {
				found = false;
				break;
			}
			if (grid[i][j] != toupper(word[k])) {
				found = false;
			}
		}
		if (found == true) {
			direction = 6;
		}
	}
	if (found)
		return direction;
	else
		return -1;
}
int matchDiagonalReverse(int row, int col, char grid[][MAX_LENGTH], char word[]) {
	bool found = true;
	int direction = 0;
	for (int i = row, j = col, k = 0; word[k] != NULL && found; k++, i--, j--) {
		if (i < 0 || j < 0) {
			found = false;
			break;
		}
		if (grid[i][j] != toupper(word[k])) {
			found = false;
		}
	}
	if (found == true) {
		direction = 7;
	}
	if (!found) {
		found = true;
		for (int i = row, j = col, k = 0; word[k] != NULL && found; k++, i--, j++) {
			if (i < 0 || j >= MAX_LENGTH) {
				found = false;
				break;
			}
			if (grid[i][j] != toupper(word[k])) {
				found = false;
			}
		}
		if (found == true) {
			direction = 8;
		}
	}
	if (found)
		return direction;
	else
		return -1;
}
int matchWord(char grid[][MAX_LENGTH], char word[], int& found) {

	int foundWord = -1;
	int index = 0;
	for (int i = 0; i < MAX_LENGTH; i++) {
		for (int j = 0; j < MAX_LENGTH; j++) {
			if (grid[i][j] == word[0])
			{
				foundWord = matchHorizontalForward(i, j, grid, word);
				if (foundWord != -1)
					break;

				foundWord = matchHorizontalReverse(i, j, grid, word);
				if (foundWord != -1)
					break;

				foundWord = matchVerticalForward(i, j, grid, word);
				if (foundWord != -1)
					break;

				foundWord = matchVerticalReverse(i, j, grid, word);
				if (foundWord != -1)
					break;

				foundWord = matchDiagonalForward(i, j, grid, word);
				if (foundWord != -1)
					break;

				foundWord = matchDiagonalReverse(i, j, grid, word);
				if (foundWord != -1)
					break;

			}
			index++;
		}
		if (foundWord != -1)
		{
			break;
		}
	}
	if (foundWord != -1) {
		found = foundWord;
		return index;
	}
	else {
		return foundWord;
	}
}
void printGrid(char grid[][MAX_LENGTH], int gridCount[][MAX_LENGTH]) {
	for (int i = 0; i < MAX_LENGTH; i++) {
		for (int j = 0; j < MAX_LENGTH; j++) {
			if (gridCount[i][j] == 0) {
				printLetter(grid[i][j], 15);
			}
			else if (gridCount[i][j] == 1) {
				printLetter(grid[i][j], 14);
			}
			else if (gridCount[i][j] == 2) {
				printLetter(grid[i][j], 9);
			}
			else if (gridCount[i][j] > 2) {
				printLetter(grid[i][j], 12);
			}
		}
		cout << endl;
	}
}
int main() {
	cout << "Press S to solve the puzzle at once." << endl;
	cout << "Press T to solve the puzzle step by step." << endl;
	cout << "Press X to print puzzle statistics." << endl;

	char option ;
	cin >> option;

	if (option == 'S' || option == 's' || option == 'T' || option == 't' || option == 'X' || option == 'x')
	{
		ifstream fin("b.txt.txt");
		char grid[MAX_LENGTH][MAX_LENGTH];
		int gridCount[MAX_LENGTH][MAX_LENGTH];
		char words[100][16];

		for (int i = 0; i < MAX_LENGTH; i++) {
			for (int j = 0; j < MAX_LENGTH; j++) {
				gridCount[i][j] = 0;
			}
		}

		for (int i = 0; i < MAX_LENGTH; i++) {
			for (int j = 0; j < MAX_LENGTH; j++) {
				fin >> grid[i][j];
			}
		}
		int index = 0;
		char buffer[20];
		while (!fin.eof()) {
			fin >> buffer;
			if (strlen(buffer) > 0)
			{
				int i = 0;
				for (; i < strlen(buffer) - 1; i++) {
					words[index][i] = buffer[i];
				}
				words[index][i] = NULL;
				index++;
			}
		}
		fin.close();
		words[index][0] = NULL;

		int x = 0, y = 0;
		int direction;
		int position = 0;

		char step;
		int shortest = 999;
		int longest = 0;
		int sum = 0;
		int count = 0;
		int verticalU = 0;
		int verticalD = 0;
		int horizontalL = 0;
		int horizontalR = 0;
		int DiagonalU = 0;
		int DiagonalD = 0;


		if (option == 'T' || option == 't') {
			cout << "Press Enter." << endl;
			GoToXY(0, 4);
			printGrid(grid, gridCount);
		}

		for (int i = 0; words[i][0] != NULL; i++) {
			direction = -1;
			count++;
			sum += strlen(words[i]);
			if (strlen(words[i]) < shortest)
			{
				shortest = strlen(words[i]);
			}
			if (strlen(words[i]) > longest)
			{
				longest = strlen(words[i]);
			}
			int position = matchWord(grid, words[i], direction);
			x = 0;
			y = 0;
			if (direction != -1) {
				y = position % MAX_LENGTH;
				x = position / MAX_LENGTH;

				if (direction == 1)
				{
					horizontalR++;
				}
				else if (direction == 2)
				{
					horizontalL++;
				}
				else if (direction == 3)
				{
					verticalD++;
				}
				else if (direction == 4)
				{
					verticalU++;
				}
				else if (direction == 5 || direction == 6) {
					DiagonalD++;
				}
				else if (direction == 7 || direction == 8) {
					DiagonalU++;
				}


				for (int j = 0; j < strlen(words[i]); j++)
				{
					gridCount[x][y]++;
					if (direction == 1)//horizontal forward direction
					{
						y++;
					}
					else if (direction == 2)//horizontal reverse direction
					{
						y--;
					}
					else if (direction == 3)//vertical forward direction
					{
						x++;
					}
					else if (direction == 4)//vertical reverse direction
					{
						x--;
					}
					else if (direction == 5)//diagonal bottom right direction
					{
						x++;
						y++;
					}
					else if (direction == 6)//diagonal bottom left direction
					{
						x++;
						y--;
					}
					else if (direction == 7)//diagonal top left direction
					{
						x--;
						y--;

					}
					else if (direction == 8)//diagonal top right direction
					{
						x--;
						y++;
					}
				}
			}
			if (option == 'T' || option == 't') {

				step = _getch();
				while (step != 13) {
					GoToXY(20, 3);
					cout << "Invalid key pressed";
					step = _getch();
				}
				GoToXY(20, 3);
				cout << "                   ";
				GoToXY(0, 4);
				printGrid(grid, gridCount);
			}
		}
		if (option == 'S' || option == 's' || option == 'X' || option == 'x')
		{
			printGrid(grid, gridCount);
		}
		char leftover[16];
		int f = 0;
		for (int i = 0; i < MAX_LENGTH; i++) {
			for (int j = 0; j < MAX_LENGTH; j++) {
				if (gridCount[i][j] == 0)
				{
					leftover[f] = grid[i][j];
					f++;
				}
			}
		}
		leftover[f] = NULL;
		cout << endl;
		cout << "Teleword: " << leftover << endl;
		if (option == 'X' || option == 'x')
		{
			cout << "Shortest Word Length: " << shortest << endl;
			cout << "Longest Word Length: " << longest << endl;
			cout << "Average Word Length: " << float(sum) / count << endl;
			cout << "Word Distribution: ";
			cout << "Horizontal(" << horizontalR << ", " << horizontalL << ") ";
			cout << "Vertical(" << verticalD << ", " << verticalU << ") ";
			cout << "Diagonal(" << DiagonalD << ", " << DiagonalU << ") " << endl;
		}
	}
	system("pause");
	return 0;
}