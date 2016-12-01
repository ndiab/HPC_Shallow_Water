#include <stdlib.h>
#include <shalw.h>
#include <mm_malloc.h>

void alloc(void) {
  hFil = (double *) _mm_malloc(2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)) * sizeof(double) , 32);
  uFil = (double *) _mm_malloc(2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)) * sizeof(double) , 32);
  vFil = (double *) _mm_malloc(2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)) * sizeof(double) , 32);
  hPhy = (double *) _mm_malloc(2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)) * sizeof(double) , 32);
  uPhy = (double *) _mm_malloc(2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)) * sizeof(double) , 32);
  vPhy = (double *) _mm_malloc(2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)) * sizeof(double) , 32);

  memset(hFil,0,2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)));
  memset(uFil,0,2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)));
  memset(vFil,0,2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)));
  memset(hPhy,0,2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)));
  memset(uPhy,0,2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)));
  memset(vPhy,0,2*(size_x*size_y + (rang>0?size_y:0) + (rang<NP-1?size_y:0)));
}

void dealloc(void) {
  free(hFil);
  free(uFil);
  free(vFil);
  free(hPhy);
  free(uPhy);
  free(vPhy);
}
