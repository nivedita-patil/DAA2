#include<iostream>
#include<deque>
#include<vector>
using namespace std;
//void travel(int n, int inputMatrix[5][5], int optTour[6]);
void travel(vector<vector<int> > inputMatrix, int optTour[]);
class Node
{
public: 	
	int level;
	deque<int>path;
	int bound;
	vector<vector<int> > boundMatrix;
	//int boundMatrix[5][5];
	vector<int> src;
	vector<int> dst;
//	int src[5]={0};
//	int dst[5]={0};
	int pathCost=0;
};

int calBound(Node v);

int calMatrix(Node u);

int pathLength(Node u);

int findMissing(Node u);

int findNext(Node v, int key);
