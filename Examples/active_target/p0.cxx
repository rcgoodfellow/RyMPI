#include <RyMPI/Runtime.hxx>
#include <iostream>
#include <array>
#include <fstream>
#include <cassert>

using std::cout;
using std::endl;
using std::array;
using std::ofstream;

using RyMPI::Runtime;
using RyMPI::CommInfo;
using RyMPI::containerWindow;
using RyMPI::containerGet;

int main(int argc, char **argv)
{
  cout << "Active Target Process 0" << endl; 
  array<int, 4> data{1, 2, 0, 0};

  Runtime rt(&argc, &argv);
  CommInfo ci = rt.commInfo();
  MPI_Win win = containerWindow(data, ci.comm);

  MPI_Win_fence(0, win);
  containerGet(data.begin()+2, data.end(), 1, 2, win);
  MPI_Win_fence(0, win);

  ofstream ofs("p0.log");
  ofs << "[0]" << endl;
  for(int i: data) ofs << i << " ";
  ofs << endl;
  
  assert(data[0] == 1);
  assert(data[1] == 2);
  assert(data[2] == 3);
  assert(data[3] == 4);
     
  MPI_Win_free(&win);
}
