
/****************************************************************************
This program find the Centrality of the graph using Closeness, Harmonic, and
Dangalchev measures

Author: Tim Becker
April 2015

Usage: GenCentrality <graph file> 

***************************************************************************/


#include <stdlib.h> 
#include <iostream> 
#include <fstream>
#include <math.h>
#include <ostream>
#include <stdio.h>
#include <sstream>
#include <time.h> 
#include <string.h> 
#include <cstring> 
#include <ctime>
#include <vector> //needed by Gurobi
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <ctype.h>
#include <ctime>

#define inf 100000000
using namespace std;

//*******************************Floyd-Warshall********************************


void FloydWarshall(float **SP, float *weight, int *a, int *b, int n, int m){

  for(int i = 0; i < n; i++){
    SP[i][i] = 0;
  }

  for(int j = 0; j < m; j++){
    SP[a[j]][b[j]] = weight[j];
    SP[b[j]][a[j]] = weight[j];
  }

  for(int k = 0; k < n; k++){
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
	SP[i][j] = min(SP[i][j],(SP[i][k] + SP[k][j]));
	SP[j][i] = min(SP[i][j],(SP[i][k] + SP[k][j]));
      }
    }
  }
}



//******************************Main Function**********************************

int main(int argc, char* argv[]){

  if(argc != 2){
    cout << "Error: Usage is <graph> " << endl;
    return 1;
  }
  

  string filename(argv[1]);
  int n,m;
  
  ifstream f_in;
  f_in.open(argv[1]);
  
  if(!f_in.is_open()){
    cerr<<"Can't open file\n";
  }
  
  f_in>>n; //number of vertices
  f_in>>m; //number of edges

  int **A;
  A = new int*[n];
  for(int i = 0; i < n; i++){
    A[i] = new int[n];
  }


  int *a = new int[m];
  int *b = new int[m];
  float *weight = new float[m];     
  
  
  for(int i = 0; i < m; i++){
    f_in>>a[i]>>b[i]>>weight[i];
  }


  for(int i = 0; i < n-1; i++){
    for(int j = i; j < n; j++){
      A[i][j] = 0;
    }
  }

  for(int j = 0; j < m; j++){
    A[a[j]][b[j]] = 1;
    A[b[j]][a[j]] = 1;
  }

  for(int i = 0; i < n; i++){
    A[i][i] = 0;
  }


  int *degrees = new int[n];

  for(int i = 0; i < n; i++){
    degrees[i] = 0;
    for(int j = 0; j < n; j++){
      if(A[i][j] == 1){
	degrees[i]++;
      }
    }
  }
  
  float **SP;
  SP = new float*[n];
  for(int i = 0; i < n; i++){
    SP[i] = new float[n];
  }


  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      SP[i][j] = inf;
    }
  }

  FloydWarshall(SP,weight,a,b,n,m);

  //Closeness Centrality
  float *CC = new float[n];
  float sum = 0;
  for(int i = 0; i < n; i++){
    sum = 0;
    for(int j = 0; j < n; j++){
      sum += SP[i][j];
    }
    CC[i] = 1/sum;
  }


  //Harmonic Centrality
  float *HC = new float[n];
  float sum2 = 0;
  for(int i = 0; i < n; i++){
    sum2 = 0;
    for(int j = 0; j < n; j++){
      if(j != i){
	sum2 += (1/SP[i][j]);
      }
    }
    HC[i] = sum2;
  }

  //Dangalchev Centrality
  float *DC = new float[n];
  float sum3 = 0;
  for(int i = 0; i < n; i++){
    sum3 = 0;
    for(int j = 0; j < n; j++){
      if(j != i){
	sum3 += (1/exp2(SP[i][j]));
      }    
    }
    DC[i] = sum3;
  }


  cout << "                   Closeness                               Harmonic                          Dangalchev                Degree" << endl;
  for(int i = 0; i < n; i++){
    printf("Node [%2d]:    %15g                       %15g                  %15g                       %d\n", i+1, CC[i], HC[i], DC[i], degrees[i]);
    //    cout << "Node " << i+1 << ":     " << CC[i]  << "                             " << HC[i] << "                        " << DC[i]<< endl;
  }

  for(int i = 0; i < n; i++){
    delete []SP[i];
    delete []A[i];
  }   

  delete []degrees;
  delete []SP;
  delete []a;
  delete []b;
  delete []CC;
  delete []HC;
  delete []DC;
  return 0;
  
}
