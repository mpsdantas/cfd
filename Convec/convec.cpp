

int ny = 80, nx = 80, nt = 100;
double dx = 2.0 / (nx + 1.0), dy = 2.0 / (ny + 1.0);
double sigma = 0.2, dt = sigma * dx;

#define OPS_2D
#include <ops_seq.h>
#include <iostream>
#include <fstream>
#include "convec.h"

using namespace std;

int main(int argc, char** argv)
{
    ops_init(argc, argv, 1);
  

  //declarations
  double *u0 = (double *)malloc((nx+2) * (ny+2) * sizeof(double));
  double *u = (double *)malloc((nx+2) * (ny+2) * sizeof(double));;
  double *un = NULL;
  
  memset(u0, 0, (nx+2) * (ny+2) * sizeof(double));
  memset(u,  0, (nx+2) * (ny+2) * sizeof(double));

    ops_block grid = ops_decl_block(2, "grid");

    int size[] = {ny, nx};
    int base[] = {0,0};
    int d_m[] = {-1,-1};
    int d_p[] = {1,1};
    ops_dat d_u  = ops_decl_dat(grid, 1, size, base, d_m, d_p, u,  "double", "d_u");
    ops_dat d_u0 = ops_decl_dat(grid, 1, size, base, d_m, d_p, u0, "double", "d_u0");
    ops_dat d_un = ops_decl_dat(grid, 1, size, base, d_m, d_p, un, "double", "d_un");

    int s2d_00[] = {0,0};
    ops_stencil S2D_00 = ops_decl_stencil(2, 1, s2d_00, "stencil_00");
    int s2d_3pt[] = {0,0,0,-1,-1,0};
    ops_stencil S2D_3pt = ops_decl_stencil(2, 3, s2d_3pt, "stencil_3pt");

    ops_decl_const("dt", 1, "double", &dt);
    ops_decl_const("dx", 1, "double", &dx);
    ops_decl_const("dy", 1, "double", &dy);

  int d_mx = int(0.5/dx), d_Mx = int(1/dx + 1);
  int d_my = int(0.5/dy), d_My = int(1/dy + 1);

    int whole_range[] = {-1, nx+1, -1, ny+1};
    int interior_range[] = {0, nx, 0, ny};
    int init_range[]  = {d_mx, d_Mx, d_my, d_My};

  //initialization
    ops_par_loop(set_one, "set_one", grid, 2, whole_range, 
         ops_arg_dat(d_u0, 1, S2D_00, "double", OPS_WRITE));
    
    ops_par_loop(set_two, "set_two", grid, 2, init_range, 
        ops_arg_dat(d_u0, 1, S2D_00, "double", OPS_WRITE));

    ops_par_loop(make_copy, "make_copy", grid, 2, whole_range,
        ops_arg_dat(d_u,  1, S2D_00, "double", OPS_WRITE),
        ops_arg_dat(d_u0, 1, S2D_00, "double", OPS_READ));

  //computation
   for (int t = 0; t < nt; t++){
        ops_par_loop(make_copy, "make_copy", grid, 2, whole_range,
            ops_arg_dat(d_un, 1, S2D_00, "double", OPS_WRITE),
            ops_arg_dat(d_u,  1, S2D_00, "double", OPS_READ));
            
        ops_par_loop(apply_stencil, "apply_stencil", grid, 2, interior_range,
            ops_arg_dat(d_un, 1, S2D_3pt, "double", OPS_READ),
            ops_arg_dat(d_u,  1, S2D_00,  "double", OPS_WRITE));
   }


  ops_get_data(d_u);
  ops_get_data(d_u0);

  //streaming
  ofstream out_u("file_u.txt");
  ofstream out_u0("file_u0.txt");
  out_u  << ny+2 << endl << nx+2 << endl;
  out_u0 << ny+2 << endl << nx+2 << endl; 
  for( int j = 0; j < ny+2; j++ ) {
    for( int i = 0; i < nx+2; i++) {
      out_u  << u[(j)*(nx+2)+i] << endl;
      out_u0 << u0[(j)*(nx+2)+i] << endl;
      //cout << u[(j)*(nx+2)+i] << endl;
    }
  }
  out_u.close(); out_u0.close();

    ops_exit();
  free(u); free(un); free(u0);

  cout << "i've been here!\n";

  return 50;

}