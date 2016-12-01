#include <string>
#include <mpi.h>
#include <immintrin.h>
extern double *hFil, *uFil, *vFil, *hPhy, *uPhy, *vPhy;
extern int size_x, size_y, nb_steps;
extern double dx, dy, dt, pcor, grav, dissip, hmoy, alpha, height, epsilon;
extern bool file_export;
extern std::string export_path;

extern int NP, rang, decalage, size_x_base;
extern MPI_Status status;
extern double alp[4], two[4], dx_tab[4], dy_tab[4], hmoy_tab[4], dt_tab[4], *c, *d, zeros[4], pcor_tab[4], mgrav_tab[4], dissip_tab[4], four[4];




#define HFIL(t, i, j) hFil[ (j) +			\
			    (i) * size_y +		\
			    ((t)%2) * (size_x) * size_y ]
#define UFIL(t, i, j) uFil[ (j) +			\
			    (i) * size_y +		\
			    ((t)%2) * (size_x) * size_y ]
#define VFIL(t, i, j) vFil[ (j) +			\
			    (i) * size_y +		\
			    ((t)%2) * (size_x) * size_y ]
#define HPHY(t, i, j) hPhy[ (j) +			\
			    (i) * size_y +		\
			    ((t)%2) * (size_x) * size_y ]
#define UPHY(t, i, j) uPhy[ (j) +			\
			    (i) * size_y +		\
			    ((t)%2) * (size_x) * size_y ]
#define VPHY(t, i, j) vPhy[ (j) +			\
			    (i) * size_y +		\
			    ((t)%2) * (size_x) * size_y ]
