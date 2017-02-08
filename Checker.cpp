//============================================================================
// Name        : solver.cpp
// Author      : Jake Hansen
// Version     : 1.0
// Description : Phase2 for IT515R-Supercomputing, Simulates a hotplate-like problem.
//============================================================================

#include <iostream>
#include <math.h>
#include <cstdint>

//using namespace std;
using std::cout;
using std::endl;

class grid {
private:
  float *data;
  float *newData;
  float Eps;
  int rsize, csize;
public:

  grid(int arg1, int arg2, float eps) {
    Eps = eps;
    rsize = arg1;
    csize = arg2;
    data = new float[arg1 * arg2]{ 0 };
    newData = new float[arg1 * arg2]{ 0 };
  }

  void deleteGrid(){ //free grid pointers.
    delete []data;
    delete []newData;
  }

  float& at(int row, int col) {//returns teh address of the cell [row][col]
    return data[row * csize + col];
  }

  void init(float val){ // initialize a grid with edge values of 0 and middle values of @param val
    for (int row = 1; row < rsize-1; row++){
      for (int col = 1; col < csize -1; col++){
	at(row,col) = val;
      }
    }
  }

  void readInGrid(uint32_t r, uint32_t c){ //reads in a grid from standard in
    float tmp;
    int rsize = (int)r;  
    int csize = (int)c;
    for (int row = 0; row < rsize; row++){
      for (int col = 0; col < csize; col++){
	std::cin.read(reinterpret_cast<char *>(&tmp), sizeof(float));
        at(row,col) = tmp;
      }
    }
  }


  float nAvg(int row, int col){ //Computes the average of the nearest neighbors. 
    return (at(row-1,col) + at(row+1,col) + at(row,col-1) + at(row,col+1))/4;
  }  

  float stability(){ //scans the grid for cells that have epsilon larger than the target tolerance.
    float tmp = 0;
    for (int row = 1; row < rsize-1; row++){
      for (int col = 1; col < csize-1; col++){
	tmp = fabs( nAvg(row,col) - at(row,col) );
	if (tmp > Eps){
	  return tmp;
	}
      }
    }
    return tmp;
  }

  uint32_t updateCells(uint32_t itr){ //iterate the grid one step and check for stability within epsilon tolerance.
    uint32_t iterations = itr;
    float stabl = stability();
    while(stabl >= Eps){
      for (int row = 1; row < rsize-1; row++){
	for (int col = 1; col < csize -1; col++){
	  newData[row * csize + col] = nAvg(row,col);
	}
      }
      iterations++;
      std::swap(newData,data);
      stabl = stability();
    }

    return iterations;
  }

  void toBinary(){ //writes the grid to std::cout in binary.
    float tmp;
    
    for (int col = 0; col < csize; col++){
      for (int row = 0; row < rsize; row++){
	at(row,col) = tmp;
	std::cout.write(reinterpret_cast<char *>(&tmp), sizeof(float));
      }
    }
  }

  void toString(){ // this function for testing purposes only.
    for (int row = 0; row < rsize; row++){
      for (int col = 0; col < csize; col++){
		cout << "|" << this->at(row,col);
      }
      cout  << "|" << endl;
    }
  }

};

int main() {
  float eps;
  uint32_t iterations; 
  uint32_t ncol;
  uint32_t nrow;
  std::cin.read(reinterpret_cast<char *>(&iterations), sizeof(uint32_t));
  std::cin.read(reinterpret_cast<char *>(&eps), sizeof(float));
  std::cin.read(reinterpret_cast<char *>(&nrow), sizeof(uint32_t));
  std::cin.read(reinterpret_cast<char *>(&ncol), sizeof(uint32_t));


  cout <<"file gives I: "<< iterations << endl;
  cout <<"file gives E: "<< eps << endl;
  cout <<"file gives R: "<< nrow << endl;
  cout <<"file gives C: "<< ncol<< endl;
 
  grid* myGrid =  new grid((int)nrow, (int)ncol, eps);
  //cout<< "started, size: " << myGrid->rsize <<"x" << myGrid->csize << endl;
  //cout << "grid obj created" << endl;
  //grid* myGrid =  new grid(5,10, eps);
  //myGrid->init(50);
  myGrid->readInGrid(nrow,ncol);
  //cout<< "grid initialized \n";

  myGrid->toString();
  iterations = myGrid->updateCells(iterations);
  cout << "@@@@@@@@@@@@@@@ #itr:" <<iterations << endl;
  myGrid->toString();

  //std::cout.write(reinterpret_cast<char const *>(&iterations), sizeof(uint32_t));
  //std::cout.write(reinterpret_cast<char *>(&eps), sizeof(float));
  //std::cout.write(reinterpret_cast<char *>(&nrow), sizeof(uint32_t));
  //std::cout.write(reinterpret_cast<char *>(&ncol), sizeof(uint32_t));
  //myGrid->toBinary();

  myGrid->deleteGrid();
  delete myGrid;
  return 0;
}




