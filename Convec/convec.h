
void set_one(double *d_u) {
    d_u[OPS_ACC0(0,0)] = 1.0;
}

void set_two(double *d_u) {
    d_u[OPS_ACC0(0,0)] = 2.0;
}

void make_copy(double *d_un, const double *d_u) {
    d_un[OPS_ACC0(0,0)] = d_u[OPS_ACC1(0,0)];
}

void apply_stencil(const double *d_un, double *d_u) {
    d_u[OPS_ACC1(0,0)] = d_un[OPS_ACC0(0,0)]
                - dt/dx*(d_un[OPS_ACC0(0,0)] - d_un[OPS_ACC0(-1,0)]) 
                - dt/dy*(d_un[OPS_ACC0(0,0)] - d_un[OPS_ACC0(0,-1)]);
}
