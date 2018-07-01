import subprocess
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

import numpy.ctypeslib as npct

subprocess.call(["/home/lucas/OPS/ops_translator/c/ops.py", "convec.cpp"])
subprocess.call(["nvcc", "-w", "-O3", "-Xcompiler", "-fPIC", "-I/home/lucas/OPS/ops/c/include", "-I.", "-c", "-o", "./CUDA/convec_kernels_cu.o", "./CUDA/convec_kernels.cu"])
subprocess.call(["g++-6", "-fopenmp", "-Ofast", "-fPIC", "-I/home/lucas/OPS/ops/c/include", "-L/home/lucas/OPS/ops/c/lib", "-L/lib64", "convec_ops.cpp", "-shared", "-Wl,-soname,libconvec.so", "-o", "libconvec.so", "./CUDA/convec_kernels_cu.o", "-lcudart", "-lops_cuda"])

lib = npct.load_library("libconvec", '.')
fun = getattr(lib,"main")
print(fun())

u0=[]
file_u0 = open("file_u0.txt", "r")
jmax = int(file_u0.readline())
imax = int(file_u0.readline())
for line in file_u0.readlines():
    u0.append(float(line))
file_u0.close()
#subprocess.call(["rm", "file_u0.txt"])
u0_2d = np.reshape(u0, (jmax,imax))


u=[]
file_u = open("file_u.txt", "r")
jmax = int(file_u.readline())
imax = int(file_u.readline())
for line in file_u.readlines():
    u.append(float(line))
file_u.close()
#subprocess.call(["rm", "file_u.txt"])
u_2d  = np.reshape(u,  (jmax,imax))

# plot
X, Y = np.meshgrid(np.linspace(1,imax,imax),np.linspace(1,jmax,jmax))

hf = plt.figure(figsize=(6,8), dpi=100)

ha = hf.add_subplot(211, projection='3d')
ha.plot_surface(X,Y,u0_2d, cmap=cm.viridis)
ha.set_title('initial conditions')
ha.set_xlabel('$x$'), ha.set_ylabel('$y$')

hb = hf.add_subplot(212, projection='3d')
hb.plot_surface(X,Y,u_2d,  cmap=cm.viridis)
hb.set_xlabel('$x$'), hb.set_ylabel('$y$')
hb.set_title('convection nt=100')

plt.show()


