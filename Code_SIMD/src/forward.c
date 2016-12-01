#include <stdio.h>
#include <math.h>
#include <shalw.h>
#include <export.h>
#include <share_lines.h>
#ifdef _OPENMP
#include <omp.h>
#endif
#include <immintrin.h>



__m256d  hFil_forward(int t, int i, int j) {
  //Phase d'initialisation du filtre
  //HPHY(t - 1, i, j) est encore nul
  __m256d hF;

  if (t <= 2){
    hF = _mm256_load_pd(&HPHY(t, i, j));
    return hF;
  }
  hF = _mm256_add_pd((_mm256_load_pd(&HPHY(t - 1, i, j))),(_mm256_fmadd_pd((_mm256_load_pd(&alp[0])),(_mm256_load_pd(&(HFIL(t - 1, i, j)))),(_mm256_fmsub_pd(_mm256_load_pd(&two[0]),(_mm256_load_pd(&HPHY(t - 1, i, j))),_mm256_load_pd(&HPHY(t, i, j)))))));
    return hF;
}

__m256d uFil_forward(int t, int i, int j) {
  //Phase d'initialisation du filtre
  //UPHY(t - 1, i, j) est encore nul
  __m256d uF;
  if (t <= 2){
    uF = _mm256_load_pd(&UPHY(t, i, j));
    return uF;
  }
   uF = _mm256_add_pd((_mm256_load_pd(&UPHY(t - 1, i, j))),(_mm256_fmadd_pd((_mm256_load_pd(&alp[0])),(_mm256_load_pd(&(UFIL(t - 1, i, j)))),(_mm256_fmsub_pd(_mm256_load_pd(&two[0]),(_mm256_load_pd(&UPHY(t - 1, i, j))),_mm256_load_pd(&UPHY(t, i, j)))))));
  return uF;
}

__m256d vFil_forward(int t, int i, int j) {
  __m256d vF;
  //Phase d'initialisation du filtre
  //VPHY(t - 1, i, j) est encore nul
  if (t <= 2){
    vF = _mm256_load_pd(&VPHY(t, i, j));
  }
 vF = _mm256_add_pd((_mm256_load_pd(&VPHY(t - 1, i, j))),(_mm256_fmadd_pd((_mm256_load_pd(&alp[0])),(_mm256_load_pd(&(VFIL(t - 1, i, j)))),(_mm256_fmsub_pd(_mm256_load_pd(&two[0]),(_mm256_load_pd(&VPHY(t - 1, i, j))),_mm256_load_pd(&VPHY(t, i, j)))))));
 return vF;
}

__m256d hPhy_forward(int t, int i, int j) {
  __m256d hP;


  if (i > 0)
    _mm256_store_pd(&c[0],_mm256_load_pd(&UPHY(t - 1, i - 1, j)));

  if (j < size_y - 4){
    //_mm256_store_pd(&d[0],_mm256_load_pd(&VPHY(t - 1, i, j + 1))); // Nous ne pouvons pas écrire sur cette addresse car elle n'est pas allignée !
    d[0] = VPHY(t - 1, i, j + 1);
    d[1] = VPHY(t - 1, i, j + 2);
    d[2] = VPHY(t - 1, i, j + 3);
    d[3] = VPHY(t - 1, i, j + 4);
  }

 hP = _mm256_sub_pd(_mm256_load_pd(&HFIL(t - 1, i, j)) ,_mm256_mul_pd(_mm256_load_pd(&dt_tab[0]),_mm256_mul_pd( _mm256_load_pd(&hmoy_tab[0]) , _mm256_add_pd(_mm256_div_pd(_mm256_sub_pd(_mm256_load_pd(&UPHY(t - 1, i, j)),_mm256_load_pd(&c[0])), _mm256_load_pd(&dx_tab[0])) ,_mm256_div_pd(_mm256_sub_pd(_mm256_load_pd(&d[0]),_mm256_load_pd(&VPHY(t - 1, i, j))), _mm256_load_pd(&dy_tab[0]))))));
 return hP;
}

__m256d uPhy_forward(int t, int i, int j) {
  __m256d uP, b, e, f , g;
  double tmp_tab[4];
  if (i == size_x - 1){
    uP = _mm256_load_pd(&zeros[0]);
    return uP;
    //return 0.;
  }

  b = _mm256_load_pd(&zeros[0]);
  if (i < size_x - 1)
    b = _mm256_load_pd(&HPHY(t - 1, i + 1, j));

  e = _mm256_load_pd(&zeros[0]);
  if (j < size_y - 4){
    tmp_tab[0] = VPHY(t - 1, i, j + 1);
    tmp_tab[1] = VPHY(t - 1, i, j + 2);
    tmp_tab[2] = VPHY(t - 1, i, j + 3);
    tmp_tab[2] = VPHY(t - 1, i, j + 4);
    e = _mm256_load_pd(&tmp_tab[0]);
  }


  f = _mm256_load_pd(&zeros[0]);
  if (i < size_x - 1)
    f = _mm256_load_pd(&VPHY(t - 1, i + 1, j));

  g = _mm256_load_pd(&zeros[0]);
  if (i < size_x - 1 && j < size_y - 4){
    tmp_tab[0] = VPHY(t - 1, i + 1, j + 1);
    tmp_tab[1] = VPHY(t - 1, i + 1, j + 2);
    tmp_tab[2] = VPHY(t - 1, i + 1, j + 3);
    tmp_tab[3] = VPHY(t - 1, i + 1, j + 4);
    g = _mm256_load_pd(&tmp_tab[0]);
  }

  uP = _mm256_fmadd_pd(_mm256_load_pd(&dt_tab[0]),_mm256_fmadd_pd(_mm256_div_pd(_mm256_load_pd(&mgrav_tab[0]),_mm256_load_pd(&dx_tab[0])),_mm256_sub_pd(_mm256_load_pd(&b[0]),_mm256_load_pd(&HPHY(t - 1, i, j))) ,_mm256_fmsub_pd( _mm256_div_pd(_mm256_load_pd(&pcor_tab[0]),_mm256_load_pd(&four[0])), _mm256_add_pd(_mm256_add_pd(_mm256_load_pd(&VPHY(t - 1, i, j)),_mm256_load_pd(&e[0])),_mm256_add_pd(_mm256_load_pd(&f[0]),_mm256_load_pd(&g[0]))), _mm256_mul_pd(_mm256_load_pd(&dissip_tab[0]),_mm256_load_pd(&UFIL(t - 1, i, j))))),_mm256_load_pd(&UFIL(t - 1, i, j)));

 return uP;
}

__m256d vPhy_forward(int t, int i, int j) {
  __m256d vP, c, d, e, f;
  double tmp_tab[4];

  if (j == 0)
    return _mm256_load_pd(&zeros[0]);

  c = _mm256_load_pd(&zeros[0]);
  if (j > 0){
    tmp_tab[0] = HPHY(t - 1, i, j - 1);
    tmp_tab[1] = HPHY(t - 1, i, j );
    tmp_tab[2] = HPHY(t - 1, i, j + 1);
    tmp_tab[3] = HPHY(t - 1, i, j + 2);
    c = _mm256_load_pd(&tmp_tab[0]);
  }

  d = _mm256_load_pd(&zeros[0]);
  if (i > 0 && j > 0){
    tmp_tab[0] = UPHY(t - 1, i -1, j -1);
    tmp_tab[1] = UPHY(t - 1, i -1, j );
    tmp_tab[2] = UPHY(t - 1, i -1, j + 1);
    tmp_tab[3] = UPHY(t - 1, i -1, j + 2);
    d = _mm256_load_pd(&tmp_tab[0]);
  }

  e = _mm256_load_pd(&zeros[0]);
  if (i > 0)
    e = _mm256_load_pd(&(UPHY(t - 1, i - 1, j)));

  f = _mm256_load_pd(&zeros[0]);
  if (j > 0){
    tmp_tab[0] = UPHY(t - 1, i, j - 1);
    tmp_tab[1] = UPHY(t - 1, i, j );
    tmp_tab[2] = UPHY(t - 1, i, j + 1);
    tmp_tab[3] = UPHY(t - 1, i, j + 2);
    f = _mm256_load_pd(&tmp_tab[0]);
  }

   vP = _mm256_sub_pd(_mm256_add_pd(_mm256_load_pd(&VFIL(t - 1, i, j)), _mm256_fmsub_pd(_mm256_load_pd(&dt_tab[0]), _mm256_mul_pd(_mm256_div_pd(_mm256_load_pd(&mgrav_tab[0]),_mm256_load_pd(&dy_tab[0])), _mm256_sub_pd(_mm256_load_pd(&HPHY(t - 1, i, j)), c )),_mm256_mul_pd(_mm256_div_pd(_mm256_load_pd(&pcor_tab[0]),_mm256_load_pd(&four[0])), _mm256_add_pd(_mm256_add_pd(d,e),_mm256_add_pd(f,_mm256_load_pd(&UPHY(t - 1, i, j))))))), _mm256_mul_pd(_mm256_load_pd(&dissip_tab[0]),_mm256_load_pd(&VFIL(t - 1, i, j))));
   return vP;
}

void forward(void) {
  
  FILE *file = NULL;
  double svdt = 0.;
  int t = 0;
    
  for (t = 1; t < nb_steps; t++) {
    if (t == 1) {
      svdt = dt;
      dt = 0;
    }
    if (t == 2){
      dt = svdt / 2.;
    }
    
    int i,j;
    /* Pour activer OpenMP en plus de SIMD, décommenter les prochaines lignes */
    //#pragma omp parallel num_threads(2) private(j) firstprivate(size_y,size_x,t)
    //{
      //#pragma omp for nowait
      for (i = 0; i < size_x; i++) {
        for (j = 0; j < size_y; j+=16) {
          _mm256_store_pd(&HFIL(t, i, j),hFil_forward(t, i, j));
          _mm256_store_pd(&HFIL(t, i, j+4),hFil_forward(t, i, j+4));
          _mm256_store_pd(&HFIL(t, i, j+8),hFil_forward(t, i, j+8));
          _mm256_store_pd(&HFIL(t, i, j+12),hFil_forward(t, i, j+12));
          _mm256_store_pd(&HPHY(t, i, j),hPhy_forward(t, i, j));
          _mm256_store_pd(&HPHY(t, i, j+4),hPhy_forward(t, i, j+4));
          _mm256_store_pd(&HPHY(t, i, j+8),hPhy_forward(t, i, j+8));
          _mm256_store_pd(&HPHY(t, i, j+12),hPhy_forward(t, i, j+12)); 
          _mm256_store_pd(&UPHY(t, i, j),uPhy_forward(t, i, j)); 
          _mm256_store_pd(&UPHY(t, i, j+4),uPhy_forward(t, i, j+4)); 
          _mm256_store_pd(&UPHY(t, i, j+8),uPhy_forward(t, i, j+8)); 
          _mm256_store_pd(&UPHY(t, i, j+12),uPhy_forward(t, i, j+12)); 
          _mm256_store_pd(&VPHY(t, i, j),vPhy_forward(t, i, j)); 
          _mm256_store_pd(&VPHY(t, i, j+4),vPhy_forward(t, i, j+4)); 
          _mm256_store_pd(&VPHY(t, i, j+8),vPhy_forward(t, i, j+8)); 
          _mm256_store_pd(&VPHY(t, i, j+12),vPhy_forward(t, i, j+12));
          _mm256_store_pd(&UFIL(t, i, j),uFil_forward(t, i, j));
          _mm256_store_pd(&UFIL(t, i, j+4),uFil_forward(t, i, j+4));
          _mm256_store_pd(&UFIL(t, i, j+8),uFil_forward(t, i, j+8));
          _mm256_store_pd(&UFIL(t, i, j+12),uFil_forward(t, i, j+12));
          _mm256_store_pd(&VFIL(t, i, j),vFil_forward(t, i, j));
          _mm256_store_pd(&VFIL(t, i, j+4),vFil_forward(t, i, j+4));
          _mm256_store_pd(&VFIL(t, i, j+8),vFil_forward(t, i, j+8));
          _mm256_store_pd(&VFIL(t, i, j+12),vFil_forward(t, i, j+12));
        }
      }
    //}

    MPI_Barrier(MPI_COMM_WORLD);
   
    share_lines();

    
    if (t == 2) {
      dt = svdt;
    }
  }

  if (file_export && rang == 0) {
    finalize_export(file);
  }
}
