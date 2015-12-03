//
//  dijkstras-hull.cpp
//  
//
//  Created by Illya Hicks on 9/10/12.
//  Copyright (c) 2012 Rice University. All rights reserved.
//
// Updated by Tim Becker, Randy Davila, Boris Brimkov 9/12/14
//

#include <time.h> 
#include<math.h> 
#include <stdio.h> 
#include <fstream> 
#include <iostream> 
#include <string.h> 
#include <cstring> 
#include <stdlib.h> 
#include <ext/hash_map>
#include <set>
#include "Graph1.h"
using namespace std;

int main(int argc, char* argv[]){
	
  if(argv[1]==NULL || argc < 2){
    fprintf(stderr,"can't open file %s \n", argv[1]);
    cerr<<"Usage:  dijkstra graphfile\n";
    return 1;
  }
  

  int n, m, *end1, *end2;
  ifstream f_in;
  f_in.open(argv[1]);
  
  if(f_in.is_open()){
    f_in>>n>>m;
    
    end1=new int[m];
    end2=new int[m];
    double *weight=new double[m];
    
    for(int i=0; i<m; i++){
      f_in>>end1[i]>>end2[i]>>weight[i];
    }
    
    Graph G(n, m, end1, end2, weight);
    
    delete []end1;
    delete []end2;
    delete []weight;
    
    int *y=new int[n];
    for(int i=0; i<n; i++){
      y[i]=-1; //initialize y values to "infinity"
      y[0]=0;
    }
    
    //insert your code here to perform Dijkstra's Algorithm from node 0
    
    
    
    //choose v from S with y_v minimum and delete v from S. Then scan v.
    int min = 1000000;
    int min_index = 0;
    int S = n-1; // Indicator if the set S is empty
    int j;
    int last = atoi(argv[2]);
    
    while(S != 0){  
      for(int i = 0; i < n; i++){
	if(G.nlist[i].inset == false){
	  if(y[i] < min && y[i] >= 0){
	    min = y[i];
	    min_index = i;
	  }
	}
      }
      
      G.nlist[min_index].inset = true;
      S--;
      
      //Make the edge between the previous node and this node set to true
      
      //scan v (min_index) so check all edges incident to v to see if y_v + c_vw >= y_w
      //Only check nodes still in S
      for(int k = 0; k < G.edges; k++){
	if(G.elist[k].tail() == min_index || G.elist[k].head() == min_index){
	  j = G.elist[k].otherend(min_index);
	  if(y[min_index] + G.elist[k].weight < y[j] || y[j] < 0){
	    y[j] = y[min_index] + G.elist[k].weight;
	    if(G.nlist[j].parent != -1){
	      for(int l = 0; l < G.edges; l++){
		if((G.elist[l].tail() == j && G.elist[l].head() == G.nlist[j].parent) || (G.elist[l].head() == j && G.elist[l].tail() == G.nlist[j].parent)){
		  G.elist[l].inset = false;
		}
	      }
	    }
	    G.nlist[j].parent = min_index;
	    G.elist[k].inset = true;
	  }
	}
      }
      
      //Reset S to check size of the set again
      min = 10000000;
      last = min_index;
    }

    /*    cerr<<"Optimal feasible potential \n";
    for(int i=0; i<n; i++){
      cerr<<"y["<<i<<"]= "<<y[i]<<endl;
      }*/
    cerr<<"Optimal tree with weight \n";		
    for(int i=0; i<G.edges; i++){
      if(G.elist[i].inset==true){

	cerr<<"("<<G.elist[i].tail()<<","<<G.elist[i].head()<<") with weight "<<G.elist[i].weight<<endl;
      }
    }
  }
  
  return 0;
}
