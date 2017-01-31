#include <math.h>
#include <iostream>
using namespace std;
  
const int size = 1024;  
float data[size][size] = { { 0 } };
float newData[size][size] = { { 0 } };

float& at(int row, int col){
  return data[row][col];
}

void toString(){
  for (int row = 0; row < size; row++){
    for (int col = 0; col < size; col++){
      cout << "|" << data[row][col];
    }
    cout  << "|" << endl;
  }
}


void init(float val){ // initialize a grid with edge values of 0 and middle values of @param val
  for (int row = 1; row < size-1; row++){
    for (int col = 1; col < size -1; col++){
      data[row][col] = val;
    }
  }
}

float nAvg(int row, int col){
  return (data[row-1][col] + data[row+1][col] + data[row][col-1] + data[row][col+1])/4;
}

float stability(){
  float result = -1;
  for (int row = 1; row < size-1; row++){
    for (int col = 1; col < size-1; col++){
      float tmp = fabs( nAvg(row,col) - data[row][col]);
      if(tmp > result) { // doesnt meet the tol, return
	result = tmp;
      } 
      if (tmp > 0.1){
	return tmp;
      }
    }
  }
  return result;
}

void copy(){
  for (int row = 0; row < size; row++){
    for (int col = 0; col < size; col++){
      data[row][col] = newData[row][col];
    }
  }
}

void iterate(){
  for (int row = 1; row < size-1; row++){
    for (int col = 1; col < size -1; col++){
      newData[row][col] = nAvg(row,col);
    }
  }
  copy();
  //toString();
}

int main(){
  int iterations = 0;
    
  init(50);
  float stabl = stability ();
  //cout << "Initial stability: " << stabl << "\n"; 
  //toString();
  while(stabl >= 0.1){
    //cout << iterations <<"stability: " << stabl << "\n";
    iterate();
    stabl = stability();
    iterations++;
  }

  //toString();
  
  cout << iterations << "\n";
  return 0;
}
