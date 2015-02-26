
inline RyMPI::Runtime::Runtime(int *argc, char ***argv)
{
  MPI_Init(argc, argv);  
}

inline RyMPI::CommInfo RyMPI::Runtime::commInfo(MPI_Comm comm)
{
  auto it = comm_info_map.find(comm);

  if(it == comm_info_map.end())
  {
    CommInfo ci;
    ci.comm = comm;
    MPI_Comm_rank(comm, &ci.rank);
    MPI_Comm_size(comm, &ci.size);
    comm_info_map[comm] = ci;
    return ci;
  }

  return it->second;
}
  
template<class Container>
MPI_Win 
RyMPI::containerWindow(Container c, MPI_Comm comm, MPI_Info info)
{
  MPI_Win win;

  MPI_Win_create(
      c.data(), 
      c.size() * sizeof(typename Container::value_type),
      sizeof(typename Container::value_type), 
      info, 
      comm, 
      &win);

  return win;
}
  
template<class T>
MPI_Win
RyMPI::pointerWindow(T *p, size_t N, MPI_Comm comm, MPI_Info info)
{
  MPI_Win win;

  MPI_Win_create(
      p,
      N * sizeof(T),
      sizeof(T),
      info,
      comm,
      &win);

  return win;
}

template<class T> MPI_Datatype mpitype(); 

#define mpitype_gen(__NATIVE_TY__, __MPI_TY__) \
  template<> inline \
  MPI_Datatype mpitype<__NATIVE_TY__>() { return __MPI_TY__; }

mpitype_gen(short, MPI_SHORT)
mpitype_gen(unsigned short, MPI_UNSIGNED_SHORT)
mpitype_gen(int, MPI_INT)
mpitype_gen(unsigned int, MPI_UNSIGNED)
mpitype_gen(long, MPI_LONG)
mpitype_gen(unsigned long, MPI_UNSIGNED_LONG)
mpitype_gen(float, MPI_FLOAT)
mpitype_gen(double, MPI_DOUBLE)
mpitype_gen(long double, MPI_LONG_DOUBLE)
mpitype_gen(long long int, MPI_LONG_LONG_INT)
mpitype_gen(unsigned long long, MPI_UNSIGNED_LONG_LONG)

template<class Iter>
void
RyMPI::containerGet(Iter begin, Iter end, int tgt, size_t tgt_off, MPI_Win win)
{
  MPI_Datatype ty = mpitype<typename std::iterator_traits<Iter>::value_type>();
  size_t cnt = end-begin;
  MPI_Get(
      &(*begin),
      cnt,
      ty,
      tgt,
      tgt_off,
      cnt,
      ty,
      win);
}
  
template<class T>
void
RyMPI::scalarGet(T *s, int tgt, size_t tgt_off, MPI_Win win)
{
  MPI_Datatype ty = mpitype<decltype(T{})>();
  MPI_Get(
    &s,
    1,
    ty,
    tgt,
    tgt_off,
    1,
    ty,
    win);
}

