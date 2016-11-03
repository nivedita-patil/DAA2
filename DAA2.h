#include<iostream>
#include<queue>
using namespace std;
void travel(int n, int inputMatrix[5][5], int optTour[6], int minLength);

class Node
{
public: 	
	int level;
	queue<int>path;
	int bound;
	int boundMatrix[5][5];
};

int calBound(Node v);
