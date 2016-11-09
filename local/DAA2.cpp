#include<iostream>
#include<queue>
#include<deque>
#include<algorithm>
#include<vector>
#include<fstream>
#include<ctime>
#include"DAA2.h"
using namespace std;

bool operator<(const Node& a, const Node& b)
{
	return a.bound > b.bound;
}

vector<vector<int> > inputMatrix;
int n = 0;
int ct = 1;
int main()
{
	ifstream infile("input.txt");
	int row, column, value;
	string strIp;
	if (infile.is_open())
	{
		while(true)
		{
			if(infile.eof()) break;
			infile>>strIp;
			n = atoi(strIp.c_str());
			if(n==0) break;
			inputMatrix.resize(n);
			for(int l=0; l<n; l++)
			{
				inputMatrix[l].resize(n);
			}
			for(int i=0; i<n*n; i++)
			{
				infile>>strIp;
				row = atoi(strIp.c_str());
				infile>>strIp;
				column = atoi(strIp.c_str());
				infile>>strIp;
				value = atoi(strIp.c_str());
				inputMatrix[row][column] = value;
			}
			int optTour[n+1];
			travel(inputMatrix, optTour, ct);
			ct++;	
		}
		infile.close();
	}
	
	return 0;
}

void travel(vector<vector<int> > inputMatrix, int optTour[], int ct)
{
	clock_t start_s = clock();

	int counter=0;
	Node u,v;
	priority_queue<Node>q;

	v.level = 0;
	v.path.push_front(-1);
	v.path.push_front(1);
	v.src.resize(n);
	v.dst.resize(n);
	v.src[0]=1;
	v.boundMatrix = vector<vector<int> >(inputMatrix);

	for(int k=0; k<n; k++)
	{
		for(int l=0; l<n; l++)
		{
			if(k==l)
				v.boundMatrix[k][l] = -1;
		}
	}

	v.bound = calBound(v);	
	int minLength = 9999;	
	q.push(v);
	counter++;

	int hold;

	while (!q.empty())
	{
		deque<int>::iterator it;
		v = q.top();
		q.pop();	
		if (v.bound < minLength)
		{
			u.level = v.level + 1;
			if (u.level == n-1)
			{
				u.path = v.path;
				u.path.pop_back();
				u.path.push_front(findMissing(u));
				u.path.push_front(1);
				reverse(u.path.begin(),u.path.end());
				if (pathLength(u)<minLength)
				{
					minLength = pathLength(u);
					for(int w=0; w<u.path.size(); w++)
					{
						optTour[w]=u.path[w];
					}
				}
			}
			else
			{
				for(int g=2; g<=n; g++)
				{
					it = find (v.path.begin(), v.path.end(), g);
					if(it == v.path.end())
					{
						//not found
						
						u.path = v.path;
						
						u.src = vector<int>(v.src);
						u.dst = vector<int>(v.dst);
						
						hold = u.path.front();
						u.path.push_front(g);
						u.pathCost = v.pathCost + inputMatrix[hold-1][u.path.front()-1];
						u.dst[g-1] = 1;
						u.src[v.path.front()-1] = 1;

						//calc bound

						u.boundMatrix = vector<vector<int> >(v.boundMatrix);
						
						u.bound = calMatrix(u);	
						
						if(u.bound < minLength)
						{
							q.push(u);
							counter++;
						}	
					}
				}
			}
		}
	}
	clock_t stop_s = clock();
	
	cout<<ct<<" "<<n<<" "<<minLength<<" "<<counter<<" "<<(stop_s-start_s)*1000/double(CLOCKS_PER_SEC)<<endl;
	if(n<=14)
	{
		for(int s=0; s<u.path.size()-1; s++)
		{
			cout<<optTour[s]<<endl;
		}
	}
}

int calBound(Node v)
{
	int min;
	int sum=0;

	for(int i=0; i<n; i++)
	{
		min = 9999;
		for(int j=0; j<n; j++)
		{
			if(v.boundMatrix[i][j]<min)
			{
				if(v.boundMatrix[i][j]>=0)
					min = v.boundMatrix[i][j];
			}			
		}
		if(min == 9999)
		{
			min=0;
		}
		sum = min + sum;
	}
	sum = sum + v.pathCost;
	
	return sum;
}

int calMatrix(Node u)
{
	int res;

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
				if (u.dst[j]==1 || u.src[i]==1)
				{
					u.boundMatrix[i][j]=-1;
				}
				if (j==0 && u.dst[i]==1)
				{
					u.boundMatrix[i][j]=-1;
				}
		}
	}
	res = calBound(u);
	
	return res;
}

int pathLength(Node u)
{
	int len=0;
	for(int i=0; i<u.path.size()-1; i++)
	{
		len+=inputMatrix[u.path[i]-1][u.path[i+1]-1];
	}
	return len;
}

int findMissing(Node u)
{
	sort(u.path.begin(), u.path.end());
	for(int i=0; i<=u.path.size(); i++)
	{
		if(u.path[i]!=i+1)
			return i+1;
	}
	return 0;
}
