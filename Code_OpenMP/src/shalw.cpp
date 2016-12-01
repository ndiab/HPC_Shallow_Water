#include <stdlib.h>
#include <shalw.h>
#include <parse_args.hpp>
#include <memory.h>
#include <init.h>
#include <forward.h>
#include <export.h>
#include <time.h>
#include <mpi.h>
#include <share_lines.h>
#include <sys/time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

double *hFil, *uFil, *vFil, *hPhy, *uPhy, *vPhy;
int size_x, size_y, nb_steps;
double dx, dy, dt, pcor, grav, dissip, hmoy, alpha, height, epsilon;
bool file_export;
std::string export_path;


int NP, rang, decalage,root, size_x_base;
MPI_Status status;

double my_gettimeofday(){
  struct timeval tmp_time;
  gettimeofday(&tmp_time, NULL);
  return tmp_time.tv_sec + (tmp_time.tv_usec * 1.0e-6L);
}


int main(int argc, char **argv) {
  double start, stop;
  start = my_gettimeofday();

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &NP);
  MPI_Comm_rank(MPI_COMM_WORLD, &rang);


  parse_args(argc, argv);
  printf("Command line options parsed\n");


  size_x_base = size_x;						// on enregistre le size_x initial
  decalage = size_x/NP*size_y;					// Le decalage correspond à la taille d'un tableau d'un processus
  size_x = size_x/NP + (rang>0?1:0) + (rang<NP-1?1:0);		// Nous mettons maintenant le size_x adequat pour chaque processus

  alloc();

  printf("Memory allocated \n");
  

  gauss_init();

  printf("Gauss initialized\n");

  share_lines();

  forward();

  dealloc();

  MPI_Finalize();

  stop = my_gettimeofday(); 
  fprintf(stdout, "Temps total de calcul : %g sec\n", stop - start);
  
 
  return EXIT_SUCCESS;
}
