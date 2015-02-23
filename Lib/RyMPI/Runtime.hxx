/******************************************************************************
 * RyMPI Library
 * BSD 2 Clause License
 *
 * This file contains runtime data structures and routines for MPI3
 * ***************************************************************************/
#ifndef RYMPI_RUNTIME_HXX
#define RYMPI_RUNTIME_HXX

#include <mpi.h>
#include <unordered_map>

namespace RyMPI
{
  struct CommInfo
  {
    MPI_Comm comm;
    int rank, size;
  };

  class Runtime
  {
    public:
      Runtime(int*, char***);

      CommInfo commInfo(MPI_Comm = MPI_COMM_WORLD);
   
    private:
      std::unordered_map<MPI_Comm, CommInfo> comm_info_map;
  };

  template<class Container>
  MPI_Win 
  containerWindow(Container c, MPI_Comm comm, MPI_Info info = MPI_INFO_NULL);

  template<class Iter>
  void
  containerGet(Iter begin, Iter end, int tgt, size_t tgt_off, MPI_Win win);

  template<class T>
  void
  scalarGet(T *s, int tgt, size_t tgt_off, MPI_Win win);
}

#include "Runtime.hpp"

#endif
