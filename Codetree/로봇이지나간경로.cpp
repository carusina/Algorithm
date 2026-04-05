// https://www.codetree.ai/ko/frequent-problems/hsat/problems/robot-passed-path/description

#define MAX_H 25
#define MAX_W 25
#define MOVE_COUNT 2

#include <iostream>
#include <string>
#include <queue>

constexpr int dy[] = { -1, 1, 0, 0 };
constexpr int dx[] = { 0, 0, -1, 1 };
const std::string cmdLT[4][4] = {
	{"A", "LLA", "LA", "RA"},
	{"LLA", "A", "RA", "LA"},
	{"RA", "LA", "A", "LLA"},
	{"LA", "RA", "LLA", "A"},
};

struct Pos {
	int y, x;
	int dir;
};

int H, W;
char grid[MAX_H + 1][MAX_W + 1];
bool visited[MAX_H + 1][MAX_W + 1];

Pos startPos;
std::string cmd;

inline int GetDirToNum(char dir) {
	int dirToNum = -1;

	if (dir == '^')      dirToNum = 0;
	else if (dir == 'v') dirToNum = 1;
	else if (dir == '<') dirToNum = 2;
	else if (dir == '>') dirToNum = 3;

	return dirToNum;
}

inline char GetDirToChar(int dir) {
	int dirToChar = 'x';

	if (dir == 0)      dirToChar = '^';
	else if (dir == 1) dirToChar = 'v';
	else if (dir == 2) dirToChar = '<';
	else if (dir == 3) dirToChar = '>';

	return dirToChar;
}

inline bool IsValid(int y, int x) {
	return 1 <= y && y <= H &&
		   1 <= x && x <= W;
}

Pos FindStartPos() {
	for (int r = H; r >= 1; --r)
	{
		for (int c = W; c >= 1; --c)
		{
			if (grid[r][c] == '#')
			{
				int sharpCount = 0;
				int dir = -1;

				for (int d = 0; d < 4; ++d)
				{
					int ny = r + dy[d];
					int nx = c + dx[d];

					if (IsValid(ny, nx) && grid[ny][nx] == '#')
					{
						sharpCount++;
						dir = d;
					}
				}

				if (sharpCount == 1)
				{
					return { r, c, dir };
				}
			}
		}
	}

	return { -1, -1, -1 };
}

void BFS() {
	std::queue<Pos> q;

	visited[startPos.y][startPos.x] = true;
	q.push(startPos);

	while (!q.empty())
	{
		Pos curr = q.front();
		q.pop();

		for (int d = 0; d < 4; ++d)
		{
			int ny = curr.y + dy[d];
			int nx = curr.x + dx[d];

			if(IsValid(ny + dy[d], nx + dx[d]) && !visited[ny][nx])
			{ 
				if (grid[ny][nx] == '#')
				{
					visited[ny][nx] = visited[ny + dy[d]][nx + dx[d]] = true;
					q.push({ ny + dy[d], nx + dx[d], d });
					cmd += cmdLT[curr.dir][d];
				}
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> H >> W;
	for (int r = 1; r <= H; ++r)
	{
		for (int c = 1; c <= W; ++c)
		{
			std::cin >> grid[r][c];
		}
	}

	startPos = FindStartPos();
	BFS();

	std::cout << startPos.y << " " << startPos.x << "\n";
	std::cout << GetDirToChar(startPos.dir) << "\n";
	std::cout << cmd;

	return 0;
}