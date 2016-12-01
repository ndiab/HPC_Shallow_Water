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

double *hFil, *uFil, *vFil, *hPhy, *uPhy, *vPhy;
int size_x, size_y, nb_steps;
double dx, dy, dt, pcor, grav, dissip, hmoy, alpha, height, epsilon;
bool file_export;
std::string export_path;


int NP, rang, decalage,root, size_x_base;
MPI_Status status;


int main(int argc, char **argv) {
  clock_t start, end;
  double cpu_time_used;
  start = clock();

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &NP);
  MPI_Comm_rank(MPI_COMM_WORLD, &rang);


  parse_args(argc, argv);
  printf("Command line options parsed\n");

  if(rang == 0){
    alloc();
  }

  printf("Memory allocated\n");
  

  if(rang == 0){
    gauss_init(); // nous initialisons la bosse de Gauss dans le proc 0
  }

  
  size_x_base = size_x;
  decalage = size_x/NP*size_y;
  size_x = size_x/NP + (rang>0?1:0) + (rang<NP-1?1:0);

  if(rang!=0)
	alloc();
  
  clock_t start_scat,end_scat, start_for, end_for;
  start_scat=clock();
  scat();
  end_scat=clock();
  cpu_time_used = ((double) (end_scat - start_scat)) / CLOCKS_PER_SEC;
  if(rang==0)
    printf("time to scat : %f\n",cpu_time_used);
  

  share_lines();

  start_for = clock();
  forward();
  end_for = clock();
  cpu_time_used = ((double) (end_for - start_for)) / CLOCKS_PER_SEC;
  if(rang==0)
    printf("time to forward : %f\n",cpu_time_used);
  
  dealloc();

  MPI_Finalize();
  
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  if(rang==0)
    printf("time to compute : %f\n",cpu_time_used);
 
  return EXIT_SUCCESS;
}
