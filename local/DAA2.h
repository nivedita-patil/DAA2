#include<iostream>
#include<deque>
using namespace std;
void travel(int n, int inputMatrix[5][5], int optTour[6]);

class Node
{
public: 	
	int level;
	deque<int>path;
	int bound;
	int boundMatrix[5][5];
	int src[5]={0};
	int dst[5]={0};
	int pathCost=0;
};

int calBound(Node v);

int calMatrix(Node u);

int pathLength(Node u);

int findMissing(Node u);

int findNext(Node v, int key);
