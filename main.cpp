#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stack>
#include <iomanip>

using namespace std;

class Grid {
public:
	Grid(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};
int minimum(int a[], int size) {
	int small = a[0];
	for (int i = 0; i < size; i++)
		if (a[i] < small)
			small = a[i];
	return small;
}

void determineDistances(const char maze[][10], int sr, int sc, int dist[][10]) {
	stack<Grid> gridStack;
	gridStack.push(Grid(sr, sc));
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			dist[i][j] = 99;
		}
	dist[sr][sc] = 0;
	int distArray[11];
	int min;
	int navValue;
	while (!gridStack.empty()) {
		Grid inUse = gridStack.top();
		gridStack.pop();
		const int row = inUse.r();
		const int col = inUse.c();

		cout << "row" << row << "col" << col << endl;
		distArray[0] = dist[row - 1][col];    //      Up
		distArray[1] = dist[row + 1][col];    //      Down
		distArray[2] = dist[row][col - 1];    //      Left
		distArray[3] = dist[row][col + 1];    //      Right
		min = minimum(distArray, 11);

		if (dist[row][col] > min + 1)
			dist[row][col] = min + 1;

		navValue = dist[row][col];
		if ((maze[row - 1][col] == '.') && (dist[row - 1][col] > (navValue + 1))) {
			dist[row - 1][col] = navValue + 1;
			gridStack.push(Grid(row + 1, col));
		}
		if (maze[row + 1][col] == '.' && (dist[row + 1][col] > (navValue + 1))) {
			gridStack.push(Grid(row + 1, col));
		}
		if (maze[row][col + 1] == '.' && (dist[row][col + 1] > (navValue + 1))) {
			dist[row][col + 1] = navValue + 1;
			gridStack.push(Grid(row, col + 1));
		}
		if (maze[row][col - 1] == '.' && (dist[row][col - 1] > (navValue + 1))) {
			dist[row][col - 1] = dist[row][col] + 1;
			gridStack.push(Grid(row, col - 1));
		}
	}
}

int main() {
	string txt[12];
	string line;

	int i = 0;
	ifstream file("maze\src\input_file.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);
			txt[i] = line;
			i++;
		}
	}
	file.close();

	ofstream myfile;
	myfile.open("output_file.txt");

	int height = 11;
	int width = 10;

	string open = ".";
	string start = "S";
	string free = "F";
	string wall = "X";

	string blockArray[11][10] = {
			{"S",".",".",".","X",".",".",".",".","."},
			{".","X","X","X",".",".","X","X","X","."},
			{".","X",".","X",".","X",".","X",".","."},
			{".",".",".","X",".","X",".","X",".","X"},
			{".","X",".","X",".","X",".",".",".","."},
			{".",".",".",".",".","X",".",".","X","."},
			{"X",".",".",".","X",".",".","X","X","."},
			{"X","X","X","X",".","X",".",".",".","X"},
			{".",".","X",".",".",".","X",".","X","."},
			{"X",".",".",".","X",".","X",".",".","."},
			{".",".",".","F","X",".",".",".","X","."},
	};


	for (int i = 0; i < height; i++) {

		// Creates the values
		if (i == 0) {
			myfile << "   ";
			for (int j = 0; j < width; j++) {
				myfile << " " << j << " ";
			}
			myfile << endl;
			myfile << "   ";
			for (int j = 0; j < width; j++) {
				myfile << "_" << "_" << "_";
			}
			myfile << endl;
		}

		// 3x3 block to read if its a wall/clearing/start/finish
		for (int h = 0; h < 3; h++) {

			if (h == 1 && i < 10) {
				myfile << i << " |";
			}
			else if (h == 1 && i >= 10) {
				myfile << i << "|";
			}
			else {
				myfile << "  |";
			}

			for (int j = 0; j < width; j++) {
				for (int k = 0; k < 3; k++) {
					if (k != 1) {
						if (blockArray[i][j] == start) {
							myfile << ".";
						}
						else if (blockArray[i][j] == free) {
							myfile << ".";
						}
						else if (blockArray[i][j] == wall) {
							myfile << "X";
						}
						else if (blockArray[i][j] == open) {
							myfile << ".";
						}
					}
					else {
						if (blockArray[i][j] == start) {
							if (h == 1) {
								myfile << "S";
							}
							else {
								myfile << ".";
							}
						}
						else if (blockArray[i][j] == free) {
							if (h == 1) {
								myfile << "F";
							}
							else {
								myfile << ".";
							}
						}
						else if (blockArray[i][j] == wall) {
							myfile << "X";
						}
						else if (blockArray[i][j] == open) {
							myfile << ".";
						}
					}
				}

			}
			myfile << endl;
		}

	}
	// write maze to file
	myfile.close();

	return 0;
	std::cin.get();
}
