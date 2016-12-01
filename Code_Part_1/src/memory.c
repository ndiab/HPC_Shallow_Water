#include <stdlib.h>
#include <shalw.h>

void alloc(void) {
  hFil = (double *) calloc(2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)), sizeof(double));
  uFil = (double *) calloc(2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)), sizeof(double));
  vFil = (double *) calloc(2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)), sizeof(double));
  hPhy = (double *) calloc(2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)), sizeof(double));
  uPhy = (double *) calloc(2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)), sizeof(double));
  vPhy = (double *) calloc(2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)), sizeof(double));
}

void dealloc(void) {
  free(hFil);
  free(uFil);
  free(vFil);
  free(hPhy);
  free(uPhy);
  free(vPhy);
}
