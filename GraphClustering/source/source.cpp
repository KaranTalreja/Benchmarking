//============================================================================
// Name        : Clustering.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#define getcx getchar_unlocked
#include <vector>
#include<stdio.h>
#include <iostream>
#include <tr1/unordered_set>
using namespace std;
class heapMin;
class UnionFind;
class edge;
class node;
class node {

public:
	node* leader;
	int rank;
	int Id;
	tr1::unordered_set<node*> followers;
	node(int Id)
	{
		this->Id = Id;
		rank=0;
		leader=this;
		followers.insert(tr1::unordered_set<node*>::value_type(this));
	}
	node();
};
class edge
{
public:
	node* first,*second;
	int weight;
	edge()
	{
		first = NULL;
		second = NULL;
		weight = 0;
	}
};
class heapMin
{
std::vector<edge*> heap;
int size;
public:
heapMin()
{
	size = 0;
}
void insert(edge*);
edge* extractMin();
void decompile();
int getSize()
{return size;}
void freeHeap();
};

class UnionFind
{
	std::vector<node*> *Graph;
public:
	UnionFind(std::vector<node*> *Clusters)
	{
		Graph = Clusters;
	}
	UnionFind();
	void Union(int first,int second);
	int Find(int child);
	int decompile(bool toPrint = false);
};


using namespace std;
inline void inp( int &n );//fast input function
inline void inp( int &n )//fast input function
{
	n=0;
	register int ch=getcx();int sign=1;
	while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=getcx();}

	while(  ch >= '0' && ch <= '9' )
		n = (n<<3)+(n<<1) + ch-'0', ch=getcx();
	n=n*sign;
}
vector<node*> *Graph;
int main() {
	int noOfNodes = 0;
	inp(noOfNodes);
	int tempNodeStartVal,tempNodeEndVal,tempWeight;
	edge* tempEdge;
	node *tempNodeStart,*tempNodeEnd;
	heapMin heap;
	Graph=new vector<node*>(noOfNodes);
	int noOfEdges = ((noOfNodes)*(noOfNodes-1))/2;
	for(int i = 0; i<noOfEdges;i++)
	{
		inp(tempNodeStartVal);
		inp(tempNodeEndVal);
		inp(tempWeight);
		tempEdge = new edge();
		tempNodeStart = (NULL == (*Graph)[tempNodeStartVal-1]) ? new node(tempNodeStartVal) : (*Graph)[tempNodeStartVal-1];
		tempNodeEnd = (NULL == (*Graph)[tempNodeEndVal-1]) ? new node(tempNodeEndVal) : (*Graph)[tempNodeEndVal-1];
		tempEdge->first = tempNodeStart;
		tempEdge->second = tempNodeEnd;
		tempEdge->weight = tempWeight;
		(*Graph)[tempNodeStartVal-1] = tempNodeStart;
		(*Graph)[tempNodeEndVal-1] = tempNodeEnd;
		heap.insert(tempEdge);
	}

	int noOfClusters = noOfNodes;
	int requiredClusters = 4;
	UnionFind UF(Graph);
	while(noOfClusters != requiredClusters)
	{
		tempEdge = heap.extractMin();
		tempNodeStartVal = tempEdge->first->Id;
		tempNodeEndVal = tempEdge->second->Id;
		int Firstleader = UF.Find(tempNodeStartVal);
		int Secondleader =UF.Find(tempNodeEndVal);
		if(Firstleader != Secondleader)
		{
			UF.Union(Firstleader,Secondleader);
			noOfClusters --;
		}
		delete tempEdge;
	}
	int maxSpacing;
	while(1)
	{
		tempEdge=heap.extractMin();
		tempNodeStartVal = tempEdge->first->Id;
		tempNodeEndVal = tempEdge->second->Id;
		if(UF.Find(tempNodeStartVal) != UF.Find(tempNodeEndVal))
		{
			maxSpacing = tempEdge->weight;
			delete tempEdge;
			break;
		}
		delete tempEdge;
	}
	cout<<maxSpacing<<endl;
	for(int i = 0;i<noOfNodes ;i++)
		delete ((*Graph)[i]);
	heap.freeHeap();
	return 0;
}
void heapMin::insert(edge* Edge)
{
	int parent,child;
	edge* tempEdge;
	heap.push_back(Edge);
	size++;
	child = size;
	parent = (child)/2;
	while((parent >=1) && (heap[parent-1]->weight > heap[child-1]->weight))
	{
		tempEdge = heap[child-1];
		heap[child-1] = heap[parent-1];
		heap[parent-1] = tempEdge;
		child = parent;
		parent = parent/2;
	}
}

edge* heapMin::extractMin(void)
{
	edge* retVal = heap[0],*tempEdge;
	tempEdge = heap[0];
	heap[0] = heap[size-1];
	heap[size-1] = tempEdge;
	vector<edge*> :: iterator itr = heap.begin();
	itr = itr + size -1;
	heap.erase(itr);
	size--;
	int parent = 1;
	int child = parent;
	while(2*parent < size)
	{
		child = (heap[(2*parent)-1]->weight <= heap[(2*parent)]->weight) ? 2*parent : 2*parent + 1;
		if(heap[child-1]->weight < heap[parent-1]->weight)
		{
			tempEdge = heap[child -1];
			heap[child - 1] = heap[parent - 1];
			heap[parent - 1] = tempEdge;
			parent = child;
		}
		else
			break;
	}
	return retVal;
}
void heapMin::decompile()
{
	for(vector<edge*>::iterator itr = heap.begin();itr!=heap.end();itr++)
	{
		cout<<(*itr)->weight<<" ";
	}
	cout<<endl;

}
void heapMin::freeHeap()
{
	for(unsigned int i = 0;i<heap.size();i++)
		delete (heap[i]);
}
void UnionFind::Union(int first,int second)
{
	if((*Graph)[first-1]->rank > (*Graph)[second-1]->rank)
	{
		(*Graph)[second-1]->leader = (*Graph)[first-1];
		tr1::unordered_set<node*>::iterator itr = (*Graph)[second-1]->followers.begin();
		for(;itr!=(*Graph)[second-1]->followers.end();itr++)
		{
			(*Graph)[first-1]->followers.insert(tr1::unordered_set<node*>::value_type(*itr));
		}
		(*Graph)[first-1]->followers.insert(tr1::unordered_set<node*>::value_type((*Graph)[second-1]));
	}
	else if((*Graph)[first-1]->rank == (*Graph)[second-1]->rank)
	{
		(*Graph)[second-1]->leader = (*Graph)[first-1];
		tr1::unordered_set<node*>::iterator itr = (*Graph)[second-1]->followers.begin();
		for(;itr!=(*Graph)[second-1]->followers.end();itr++)
		{
			(*Graph)[first-1]->followers.insert(tr1::unordered_set<node*>::value_type(*itr));
		}
		(*Graph)[first-1]->followers.insert(tr1::unordered_set<node*>::value_type((*Graph)[second-1]));
		(*Graph)[first-1]->rank++;

	}
	else
	{
		(*Graph)[first-1]->leader = (*Graph)[second-1];
		tr1::unordered_set<node*>::iterator itr = (*Graph)[first-1]->followers.begin();
		for(;itr!=(*Graph)[first-1]->followers.end();itr++)
		{
			(*Graph)[second-1]->followers.insert(tr1::unordered_set<node*>::value_type(*itr));
		}
		(*Graph)[second-1]->followers.insert(tr1::unordered_set<node*>::value_type((*Graph)[first-1]));
	}
}

int UnionFind::Find(int child)
{
	node* startNode = (*Graph)[child-1];
	vector<node*> listOfNodesToUpdate;
	while(startNode->leader != startNode)
	{
		listOfNodesToUpdate.push_back(startNode);
		startNode = startNode->leader;
	}
	node* leader = startNode->leader;
	for(unsigned int i = 0; i < listOfNodesToUpdate.size();i++)
		listOfNodesToUpdate[i]->leader = leader;
	return startNode->Id;
}
int UnionFind::decompile(bool toPrint)
{
	int k=0;
    tr1::unordered_set<int> *hash2;
	hash2 = new tr1::unordered_set<int>;
	for (unsigned int i=0;i<(*Graph).size();i++)
	{
	hash2->insert(tr1::unordered_set<int>::value_type(this->Find((*Graph)[i]->Id)));
	}
	tr1::unordered_set<int>::iterator itr = hash2->begin();
	for(;itr!=hash2->end();itr++)
	{
		k++;
		if(toPrint == true)
		{
		cout<<"leader: "<<(*itr)<<" Followed by ";
		tr1::unordered_set<node*>::iterator iter = (*Graph)[*itr - 1]->followers.begin();
		for(;iter!=(*Graph)[*itr -1]->followers.end();iter++)
		{
			cout<<(*iter)->Id<<" ";
		}
		cout<<endl;
		}
	}
	delete hash2;
	return k;
}
