#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


struct position {
	int row;
	int column;
};


void saveGame(struct position p) {
	FILE* file2;
	file2 = fopen("./savedGame.txt", "w");

	if (file2 != NULL) {
		fprintf(file2, "%d %d", p.row, p.column);
		fclose(file2);
	}
	else
	{
		printf("Unable to open file1\n");
	}
}

struct position loadGame() {
	FILE* file2;
	// fopen: 1st param. is the relative path of the file
	file2 = fopen("./savedGame.txt", "r");

	if (file2 != NULL) {
		int r, c;
		fscanf(file2, "%d %d", &r, &c);
		fclose(file2);

		struct position p;
		p.row = r;
		p.column = c;

		return p;
	}
	else
	{
		printf("Unable to open file1\n");
		struct position p;
		p.row = -1;
		p.column = -1;

		return p;
	}
}


char getDir(int dir) {

	if (dir == 65 || dir == 97) {
		return 'l';
	}
	else if (dir == 68 || dir == 100) {
		return 'r';
	}
	else if (dir == 87 || dir == 119) {
		return 'u';
	}
	else if (dir == 83 || dir == 115) {
		return 'd';
	}
	else {
		return ' ';
	}
}

void initMap(char map[20][30], int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			map[i][j] = '_';
		}
	}
}

void printMap(char map[20][30], int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void setPlayer(char map[20][30], int rows, int cols, int posX, int posY) {

	if ((posX >= 0 && posX < cols) &&
		(posY >= 0 && posY < rows)) {
		map[posY][posX] = 'O';
	}

}


int main()
{
	char map[20][30];

	int pX = 10;
	int pY = 10;

	initMap(map, 20, 30);
	setPlayer(map, 20, 30, pX, pY);
	printMap(map, 20, 30);

	char key;
	//printf("Press a key: \n");
	scanf_s("%c", &key);

	while (key != 'q' && key != 'Q') {
		//printDir(key);
		//printf("Press a key: \n");
		char dir = getDir(key);

		// Check the movement direction and move the player accordingly
		switch (dir) {
		case 'l':
			pX--;
			break;
		case 'r':
			pX++;

			break;
		case 'u':
			pY--;

			break;
		case 'd':
			pY++;

			break;
		default:
			break;
		}

		if (key == 'k') {
			struct position posPlayer;
			posPlayer.row = pX;
			posPlayer.column = pY;

			saveGame(posPlayer);
		}
		else if (key == 'l') {
			struct position loadedPos;
			loadedPos = loadGame();
			pX = loadedPos.row;
			pY = loadedPos.column;
		}

		system("CLS");
		initMap(map, 20, 30);

		// Check of the player is inside the map
		if (pX < 0) { pX = 0; }
		else if (pX > 29) { pX = 29; }

		if (pY < 0) { pY = 0; }
		else if (pY > 19) { pY = 19; }

		setPlayer(map, 20, 30, pX, pY);
		printMap(map, 20, 30);

		scanf_s(" %c", &key);
	}

	return 0;
}