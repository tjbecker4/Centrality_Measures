/*
 *  Graph.h
 *  
 *
 *  Created by Illya VaShun Hicks on 5/30/12.
 *  Copyright 2012 Rice University. All rights reserved.
 *
 */

class node{
public:
	int index, degree, color, parent, mark;
	bool inset;
	int *adj;
	double weight;
	node(int c=-1);
	~node();
};

node::node(int c)
{
	index=c;
	degree=0;
	color=0;
	mark=0;
	weight=0.0;
	inset=false;
}

node:: ~node()
{
	if(adj != NULL) delete []adj;
}

class edge{
	public:
	edge(int c=-1, int e1=-1, int e2=-1);
	int end1, end2, index; 
	int color;
	bool match, inset;
	double weight;
	int otherend(int end);
	int tail();
	int head();
};

edge::edge(int c, int e1, int e2)
{
	end1=e1;
	end2=e2;
	index=c;
	color=0;
	weight=0.0;
	match=false;
	inset=false;
}

int edge:: otherend(int end)
{
	return end1+end2-end;
}

int edge:: tail()
{
	return end1;
}

int edge:: head()
{
	return end2;
}

class Graph{
public:
	Graph(int n=0, int m=0, int *e1=NULL, int *e2=NULL, double *ew=NULL, double *nw=NULL);
	~Graph();
	int nodes, edges;
	node *nlist;
	edge *elist;
};

Graph:: ~Graph()
{	
	if (nlist != NULL) delete []nlist;
	if (elist != NULL) delete []elist;
}

Graph:: Graph(int n, int m, int *e1, int *e2, double *ew, double *nw)
{
	nodes=n;
	edges=m;
	nlist=NULL;
	elist=NULL;
	if(nodes > 0) nlist=new node[nodes];
	if(edges > 0) elist=new edge[edges];
	
	
	for(int i=0; i<nodes; i++){
		nlist[i].index=i;
                nlist[i].adj=NULL;
		nlist[i].degree=0;
		nlist[i].color=0;
		nlist[i].mark=0;
		nlist[i].weight=0.0;
		nlist[i].parent=-1;
		nlist[i].inset=false;
		if(nw!= NULL) nlist[i].weight=nw[i];
	}
	
	for(int i=0; i<edges; i++){
		elist[i].end1=e1[i];
		nlist[elist[i].end1].degree++;
		elist[i].end2=e2[i];
		if(e1[i]!=e2[i]){
			nlist[elist[i].end2].degree++;
		}
		elist[i].index=i;
		elist[i].color=0;
		elist[i].weight=0.0;
		elist[i].match=false;
		elist[i].inset=false;
		if(ew != NULL) elist[i].weight=ew[i];
	}
	
	
	for(int i=0; i<edges; i++){
		int end1=elist[i].end1;
		int end2=elist[i].end2;
		if(nlist[end1].adj==NULL){
			nlist[end1].adj=new int[nlist[end1].degree];
			nlist[end1].degree=0;
		}
		if(nlist[end2].adj==NULL){
			nlist[end2].adj=new int[nlist[end2].degree];
			nlist[end2].degree=0;
		}
		nlist[end1].adj[nlist[end1].degree]=i;
		nlist[end1].degree++;
		if(end1 != end2){
			nlist[end2].adj[nlist[end2].degree]=i;
			nlist[end2].degree++;
		}
	}
	
}
