#include<iostream>
#include<queue>
#include<deque>
#include<algorithm>
#include<vector>
#include"DAA2.h"
using namespace std;

template<typename T> void print_queue(T& q) 
{
	while(!q.empty()) 
	{
		std::cout << q.front() << " ";
		q.pop_front();
	}
	std::cout << '\n';
}

bool operator<(const Node& a, const Node& b)
{
	return a.bound > b.bound;
}

	int inputMatrix[5][5] = {
					{0, 14, 4, 10, 20},
					{14, 0, 7, 8, 7},
					{4, 5, 0, 7, 16},
					{11, 7, 9, 0, 2},
					{18, 7, 17, 4, 0}
				};

int main()
{
	int optTour[6];
	int minLength = 99;
	
	travel(5, inputMatrix, optTour, minLength);
	
	return 0;
}

void travel(int n, int inputMatrix[5][5], int optTour[6], int minLength)
{
	Node u,v;
	priority_queue<Node>q;

	v.level = 0;
	v.path.push_front(-1);
	v.path.push_front(1);
	v.src[0]=1;
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
	minLength = 9999;	
	q.push(v);
	
//cout<<v.path.front()<<"\n";	

/*	cout<<"Iteration 1 Matrix: \n";
		for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			cout<<v.boundMatrix[i][j]<<"\t";
		}
		cout<<"\n";
	}
*/

	while (!q.empty())
	{
		//cout<<"here ";
		deque<int>::iterator it;
		v = q.top();
		q.pop();
		if (v.bound < minLength)
		{
			u.level = v.level + 1;
			//cout<<"U LEVEL: "<<u.level<<endl;
			if (u.level == n-1)
			{
				u.path = v.path;
				u.path.pop_back();
				u.path.push_front(findMissing(u));
				u.path.push_front(1);
				if (pathLength(u)<minLength)
				{
					//cout<<"\n\n"<<"== FINAL ==\n"<<pathLength(u)<<endl;
					//print_queue(u.path);
					//cout<<"\n\n";
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
						copy(&v.src[0], &v.src[5], &u.src[0]);
						//u.src = v.src;
						copy(&v.dst[0], &v.dst[5],&u.dst[0]);
						//u.dst = v.dst;
						u.path.push_front(g);
						u.dst[g-1] = 1;
						u.src[v.path.front()-1] = 1;
						//u.src[u.path[u.path.size()-1]] = 1;

						//calc bound

						copy(&v.boundMatrix[0][0], &v.boundMatrix[0][0]+25, &u.boundMatrix[0][0]);
						//copy(&inputMatrix[0][0], &inputMatrix[0][0]+25, &u.boundMatrix[0][0]);
						u.bound = calMatrix(u);						
						cout<<"**"<<u.bound<<"**\n";
						if(u.bound < minLength)
						{
							q.push(u);
							cout<<"Path till now: ";
							print_queue(u.path);
						}	
						//cout<<"level"<<u.level<<"\n";
					}
				}
			}
		}
	}
	for(int s=0; s<u.path.size(); s++)
	{
		cout<<" "<<optTour[s];
	}
	cout<<"\n";

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
			if(v.boundMatrix[i][j]<min)
			{
				if(v.boundMatrix[i][j]>=0)
					min = v.boundMatrix[i][j];
			}			
		}
		if(min == 9999)
		{
			//cout<<"####"<<inputMatrix[v.path[v.path.size()-2]-1][v.path.front()-1]<<endl<<v.path.size()<<endl<<v.path.front()<<endl;
			min = inputMatrix[v.path[v.path.size()-2]-1][v.path.front()-1];
		}
		sum+=min;
	}
	return sum;
}

int calMatrix(Node u)
{
	int res;
	cout<<"Iteration"<<u.level<<" Matrix: \n";
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
				if (u.dst[j]==1 || u.src[i]==1)
				{
					u.boundMatrix[i][j]=-1;
				}
				if (j==0 && u.dst[i]==1)
				{
					u.boundMatrix[i][j]=-1;
				}
				cout<<u.boundMatrix[i][j]<<"\t";	
		}
		cout<<"\n";
	}
	res = calBound(u);
	
	return res;
}

int pathLength(Node u)
{
	int len=0;
	for(int i=0; i<u.path.size()-1; i++)
	{
		cout<<"i: "<<i<<"\tsrc: "<<u.path[i]<<"\tdst: "<<u.path[i+1]<<"\tlen: "<<inputMatrix[u.path[i]-1][u.path[i+1]-1]<<"\n";
		//cout<<"----"<<i<<" : "<<u.path[i];
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
