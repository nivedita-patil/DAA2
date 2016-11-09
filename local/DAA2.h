#include<iostream>
#include<deque>
#include<vector>
using namespace std;

void travel(vector<vector<int> > inputMatrix, int optTour[], int ct);
class Node
{
public: 	
	int level;
	deque<int>path;
	int bound;
	vector<vector<int> > boundMatrix;
	vector<int> src;
	vector<int> dst;
	int pathCost=0;
};

int calBound(Node v);

int calMatrix(Node u);

int pathLength(Node u);

int findMissing(Node u);

int findNext(Node v, int key);
