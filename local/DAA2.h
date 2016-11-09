#include<iostream>
#include<deque>
#include<vector>
using namespace std;
//void travel(int n, int inputMatrix[5][5], int optTour[6]);
void travel(int n, vector<vector<int> > inputMatrix, int optTour[6]);
class Node
{
public: 	
	int level;
	deque<int>path;
	int bound;
	vector<vector<int> > boundMatrix;
	//int boundMatrix[5][5];
	int src[5]={0};
	int dst[5]={0};
	int pathCost=0;
};

int calBound(Node v, int n);

int calMatrix(Node u, int n);

int pathLength(Node u);

int findMissing(Node u);

int findNext(Node v, int key);
