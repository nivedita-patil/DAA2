#include<iostream>
#include<queue>
using namespace std;

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

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

int main()
{
	int inputMatrix[5][5] = {
					{0, 14, 4, 10, 20},
					{14, 0, 7, 8, 7},
					{4, 5, 0, 7, 16},
					{11, 7, 9, 0, 2},
					{18, 7, 17, 4, 0}
				};
	int optTour[6];
	int minLength = 99;
	
	travel(5, inputMatrix, optTour, minLength);
	
	return 0;
}

void travel(int n, int inputMatrix[5][5], int optTour[6], int minLength)
{
	Node u,v;
	priority_queue<int>q;

	v.level = 0;
	v.path.push(1);
	copy(&inputMatrix[0][0], &inputMatrix[0][0]+25, &v.boundMatrix[0][0]);	

	for(int k=0; k<5; k++)
	{
		for(int l=0; l<5; l++)
		{
			if(k==l)
				v.boundMatrix[k][l] = -1;
		}
	}

	v.bound = calBound(v);
	
	cout<<"**"<<v.bound<<"\n";

//cout<<v.path.front()<<"\n";	

		for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			cout<<v.boundMatrix[i][j]<<"\t";
		}
		cout<<"\n";
	}
}

int calBound(Node v)
{
	int min;
	int sum=0;

	for(int i=0; i<5; i++)
	{
		min = 9999;
		for(int j=0; j<5; j++)
		{
			if(v.boundMatrix[i][j]>=0 && v.boundMatrix[i][j]<min)
			{
				min = v.boundMatrix[i][j];
			}
		}
		sum+=min;
	}
	return sum;
}
