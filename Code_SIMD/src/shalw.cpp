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
double alp[4], two[4], dx_tab[4], dy_tab[4], hmoy_tab[4], dt_tab[4], *c, *d, zeros[4], pcor_tab[4], mgrav_tab[4], dissip_tab[4], four[4];

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



  /* Initialisation des tableaux qui nous serviront à faire du calcul vectoriel */
  
  c = (double *) _mm_malloc(4 * sizeof(double) , 32);
  d = (double *) _mm_malloc(4 * sizeof(double) , 32);
 
  for(int k = 0; k<4; k++){
    alp[k] = alpha;
    two[k] = 2; 
    dx_tab[k] = dx;
    dy_tab[k] = dy;
    hmoy_tab[k] = hmoy;
    dt_tab[k] = dt;
    c[k] = 0.;
    d[k] = 0.;
    zeros[k] = 0.;
    pcor_tab[k] = pcor;
    mgrav_tab[k] = -grav;
    dissip_tab[k] = dissip;
    four[k] = 4.;
  }


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
