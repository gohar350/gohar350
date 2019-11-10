#include<iostream>
#include<fstream>
#include <windows.h>
#include<conio.h>

using namespace std;




////////////////////////////////printletters//////////////////////////////////
void printcharacters(char ch, int rang) {
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rang);
	cout << ch << " ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


///////////////////////////////coloring/////////////////////////

void GoToXY(int x, int y) {

	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


///////////////////////////////Forward///////////////////////////////////////
int Forward(int row, int colom, char puzzel[][15], char word[]) {

	bool found = true;
	int i = colom, j = 0;
	while (word[j] != NULL && found) 
	{
		if (i >= 15)
			return -1;
		
		if (puzzel[row][i] != toupper(word[j])) {
			found = false;
		}
		i++, j++;
	}
	if (found)
		return 1;
	else
		return -1;
}
////////////////////////////////Backword//////////////////////////////////////////

int backwards(int row, int colom, char puzzel[][15], char word[]) {
	
	bool found = true;
	int i = colom, j = 0;
	while ( word[j] != NULL && found) 
	{
		if (i < 0)
			return -1;
		if (puzzel[row][i] != toupper(word[j])) {
			found = false;
		}
		i--, j++;
	}
	if (found)
		return 2;
	else
		return -1;
}


////////////////////////////////upward////////////////////////////////////////////

int upward(int row, int colom, char puzzel[][15], char word[]) {
	bool found = true;
	int i = row, j = 0;
	while ( word[j] != NULL && found) 
	{
		if (i >= 15)
			return -1;
		if (puzzel[i][colom] != toupper(word[j])) {
			found = false;
		}
		i++, j++;
	}
	if (found)
		return 3;
	else
		return -1;
}

///////////////////////////////////Downward//////////////////////////////

int downward(int row, int colom, char puzzel[][15], char word[]) {
	bool found = true;
	int i = row, j = 0;
	while ( word[j] != NULL && found)
	{
		if (i < 0)
			return -1;
		if (puzzel[i][colom] != toupper(word[j])) {
			found = false;
		}
		i--, j++;
	}
	if (found)
		return 4;
	else
		return -1;
}

////////////////////////////////Daigonal1/////////////////////////////////

int diagonal1(int row, int colom, char puzzel[][15], char word[]) {
	bool found = true;
	int direction = 0;
	int i = row, j = colom, k = 0;
	while ( word[k] != NULL && found) {
		if (i >= 15 || j >= 15) {
			found = false;
			word[k] == NULL;
		}
		if (puzzel[i][j] != toupper(word[k])) {
			found = false;
		}
		k++, i++, j++;
	}
	if (found == true) {
		direction = 5;
	}
	if (!found) {
		found = true;
		i = row, j = colom, k = 0;
		while ( word[k] != NULL && found) {
			if (i >= 15 || j < 0) {
				found = false;
				word[k]==NULL;
			}
			if (puzzel[i][j] != toupper(word[k])) {
				found = false;
			}
			k++, i++, j--;
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

//////////////////////////////////////diagonal2///////////////////////////////////////


int diagonal2(int row, int colom, char puzzel[][15], char word[]) {
	bool found = true;
	int direction = 0;
	int i = row, j = colom, k = 0;
	while ( word[k] != NULL && found)  {
		if (i < 0 || j < 0) {
			found = false;
			word[k]==NULL;
		}
		if (puzzel[i][j] != toupper(word[k])) {
			found = false;
		}
		k++, i--, j--;
	}
	if (found == true) {
		direction = 7;
	}
	if (!found) {
		found = true;
		 i = row, j = colom, k = 0;
		while ( word[k] != NULL && found) {
			if (i < 0 || j >= 15) {
				found = false;
				word[k]==NULL;
			}
			if (puzzel[i][j] != toupper(word[k])) {
				found = false;
			}
			k++, i--, j++;
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

////////////////////////////////////MATCHING////////////////////////////////

int matching(char puzzel[][15], char word[], int& found) {

	int foundWord = -1;
	int index = 0;
	for (int i = 0; i < 15; i++) {
		int j = 0;
		while ( j < 15) {
			if (puzzel[i][j] == word[0])
			{
				foundWord = Forward(i, j, puzzel, word);
				if (foundWord != -1) {

					break;
					
				}
				
					foundWord = backwards(i, j, puzzel, word);
					if (foundWord != -1) {
						break;
					}
						
				foundWord = upward(i, j, puzzel, word);
				if (foundWord != -1) {
					break;
				}
				foundWord = downward(i, j, puzzel, word);
				if (foundWord != -1) {
					break;
				}
				foundWord = diagonal1(i, j, puzzel, word);
				if (foundWord != -1) {
					break;
				}
				foundWord = diagonal2(i, j, puzzel, word);
				if (foundWord != -1) {
					break;
				}
			}
			index++;
     		j++;
		}
		if (foundWord != -1)
		{
			break ;
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



///////////////////////////////////////////PrintingGrid/////////////////

void printing(char puzzel[][15], int gridCount[][15]) {
	for (int i = 0; i < 15; i++) {
		int j = 0; 
		while ( j < 15) {
			if (gridCount[i][j] == 0) {
				printcharacters(puzzel[i][j], 15);
			}
			else if (gridCount[i][j] == 1) {
				printcharacters(puzzel[i][j], 14);
			}
			else if (gridCount[i][j] == 2) {
				printcharacters(puzzel[i][j], 9);
			}
			else if (gridCount[i][j] > 2) {
				printcharacters(puzzel[i][j], 12);
			}
			j++;
		}
		cout << endl;
	}
}

///////////////////////////////////////////////////Starting Program //////////////////////////



int main() {




	system("color F0");



	char puzzel[15][15];
	int Count[15][15];
	char find[100][100];

	/////////////////////////////notepad file////////////////////////////////////////////

	ifstream fin("b.txt.txt");


	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			Count[i][j] = 0;
		}
	}

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			fin >> puzzel[i][j];
		}
	}
	int index = 0;
	char words[20];/////////////////////////////////as buffer
	while (!fin.eof()) {
		fin >> words;
		if (strlen(words) > 0)
		{
			int i = 0;
			while (i < strlen(words) - 1) {
				find[index][i] = words[i];
				i++;
			}
			find[index][i] = NULL;
			index++;
		}
	}
	fin.close();
	find[index][0] = NULL;

	
	cout << endl;

	int x = 0, y = 0;
	int position = 0;
	int direction;

	
	int shortest = 999;
	int longest = 0;
	int sum = 0;
	int count = 0;
	

	//////////////////////////////////asking////////////////////////////////
	cout << "Press S to solve the puzzle at once." << endl;
	cout << "Press T to solve the puzzle step by step." << endl;
	cout << "Press X to print puzzle statistics." << endl;


	char option;
	cin >> option;
	int up = 0;
	int Down = 0;
	int Left = 0;
	int Right = 0;
	int Updiagonal = 0;
	int Downdiagonal = 0;

	//////////////////////////for s//////////////////////////////////////

	if (option == 'T' || option == 't') {

		GoToXY(0, 4);
		printing(puzzel, Count);
		cout << "Press Enter to solve every step :" << endl;
		cout << endl;

	}

	for (int i = 0; find[i][0] != NULL; i++) {
		direction = -1;
		count++;
		sum += strlen(find[i]);
		if (strlen(find[i]) < shortest)
		{
			shortest = strlen(find[i]);
		}
		if (strlen(find[i]) > longest)
		{
			longest = strlen(find[i]);
		}
		int position = matching(puzzel, find[i], direction);
		x = 0;
		y = 0;

		
		if (direction != -1) {
			y = position % 15;
			x = position / 15;

			if (direction == 1)
			{
				Right++;
			}
			else if (direction == 2)
			{
				Left++;
			}
			else if (direction == 3)
			{
				Down++;
			}
			else if (direction == 4)
			{
				up++;
			}
			else if (direction == 5 || direction == 6) {
				Downdiagonal++;
			}
			else if (direction == 7 || direction == 8) {
				Updiagonal++;
			}

			int z = 0;

			while (z < strlen(find[i]))
			{
				Count[x][y]++;
				if (direction == 1)
				{
					y++;
				}
				else if (direction == 2)
				{
					y--;
				}
				else if (direction == 3)
				{
					x++;
				}
				else if (direction == 4)
				{
					x--;
				}
				else if (direction == 5)
				{
					x++;
					y++;
				}
				else if (direction == 6)
				{
					x++;
					y--;
				}
				else if (direction == 7)
				{
					x--;
					y--;

				}
				else if (direction == 8)
				{
					x--;
					y++;
				}
				z++;
			}
		}
		char step;
		if (option == 't' || option == 'T') {

			step = _getch();
			while (step != 13) {
				GoToXY(20, 3);
				cout << "Invalid key pressed please press enter :";
				step = _getch();
			}
			GoToXY(20, 3);
			cout << "                   ";
			GoToXY(0, 4);
			printing(puzzel, Count);
		}
	}
	if (option == 's' || option == 'S')
		
	{
		printing(puzzel, Count);
	}
	char teleword[16];
	int a = 0;
	for (int i = 0; i < 15; i++) {
		int k= 0;
		while ( k < 15) {
			if (Count[i][k] == 0)
			{
				teleword[a] = puzzel[i][k];
				a++;
			}
			k ++;
		}
	}
	teleword[a] = NULL;
	cout << endl;
	cout << " the Teleword is = " << teleword << endl;
	if (option == 'x' || option == 'X')
	{
		cout << " the Shortest Word Length= " << shortest << endl;
		cout << "the Longest Word Length= " << longest << endl;
		cout << " the Average Word Length= " << float(sum) / count << endl;
		cout << "the Word Distribution= ";
		
		cout << "Vertical=(" << Down << ", " << up << ") ";
		cout << "Diagonal=(" << Downdiagonal << ", " << Updiagonal << ") " << endl;
		cout << "the Horizontal=(" << Right << ", " << Left << ") "<<endl;
	}







	system("pause ");
	return 0;

}




