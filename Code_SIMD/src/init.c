#include <math.h>
#include <shalw.h>

void gauss_init(void) {
  double gmx, gmy, gsx, gsy;

  gmx = size_x_base * dx / 2 ;
  gmy = size_y * dy / 2 ;
  gsx = 25000 ;
  gsy = 25000 ;

  for (int i = 0; i < size_x_base/NP;  i++) {
    for (int j = 0; j < size_y; j++) {
      HFIL(0, i + (rang>0?1:0), j) = height *
	(exp(- pow(((size_x_base/NP+i) * dx - gmx) / gsx, 2) / 2.)) *
	(exp(- pow((j * dy - gmy) / gsy, 2) / 2.)) ;
    }
  }
}
