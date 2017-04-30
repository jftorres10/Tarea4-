import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import animation

C1_ab_Tprom = np.loadtxt("C1_abiertas_Tprom.dat")
C1_pe_Tprom = np.loadtxt("C1_periodicas_Tprom.dat")
C1_fi_Tprom = np.loadtxt("C1_fijas_Tprom.dat")

C2_ab_Tprom = np.loadtxt("C2_abiertas_Tprom.dat")
C2_pe_Tprom = np.loadtxt("C2_periodicas_Tprom.dat")
C2_fi_Tprom = np.loadtxt("C2_fijas_Tprom.dat")


plt.figure()
plt.plot(C1_ab_Tprom[:,0],C1_ab_Tprom[:,1], label='abiertas')

plt.plot(C1_pe_Tprom[:,0],C1_pe_Tprom[:,1], label='periodicas')


plt.plot(C1_fi_Tprom[:,0],C1_fi_Tprom[:,1], label='fijas')

plt.title("Caso 1")
plt.ylabel("Temperatura")
plt.xlabel("Tiempo")
plt.legend( loc ='best')
plt.savefig('C1_Tpromedio.png')
plt.close()

##########
plt.figure()
plt.plot(C2_ab_Tprom[:,0],C2_ab_Tprom[:,1], label='abiertas')

plt.plot(C2_pe_Tprom[:,0],C2_pe_Tprom[:,1], label='periodicas')


plt.plot(C2_fi_Tprom[:,0],C2_fi_Tprom[:,1], label='fijas')

plt.title("Caso 2")
plt.ylabel("Temperatura")
plt.xlabel("Tiempo")
plt.legend( loc ='best')
plt.savefig('C2_Tpromedio.png')
plt.close()





C1_ab_xyt = np.genfromtxt("C1_abiertas_x_y_T.dat",comments='T')

n=441;
plt.tripcolor(C1_ab_xyt[0:n+1,0],C1_ab_xyt[0:n+1,1],C1_ab_xyt[0:n+1,2])
plt.title("Caso 1-Abiertas-T 0 ")
plt.ylabel("Y")
plt.xlabel("X")
plt.colorbar()
plt.savefig('C1_ab_T0.png')
plt.close()

plt.tripcolor(C1_ab_xyt[n+1:2*n+1,0],C1_ab_xyt[n+1:2*n+1,1],C1_ab_xyt[n+1:2*n+1,2])
plt.title("Caso 1-Abiertas-T 100 ")
plt.ylabel("Y")
plt.xlabel("X")
plt.colorbar()
plt.savefig('C1_ab_T2.png')
plt.close()

plt.tripcolor(C1_ab_xyt[2*n+1:,0],C1_ab_xyt[2*n+1:,1],C1_ab_xyt[2*n+1:,2])
plt.title("Caso 1-Abiertas-T 2500 ")
plt.ylabel("Y")
plt.xlabel("X")
plt.colorbar()
plt.savefig('C1_ab_T3.png')
plt.close()



####################### periodicas
C1_ab_xyt = np.genfromtxt("C1_periodicas_x_y_T.dat",comments='T')

n=441;

plt.tripcolor(C1_ab_xyt[0:n+1,0],C1_ab_xyt[0:n+1,1],C1_ab_xyt[0:n+1,2])
plt.title("Caso 1-Periodicas-T 0 ")
plt.ylabel("Y")
plt.xlabel("X")
plt.colorbar()
plt.savefig('C1_pe_T0.png')
plt.close()

plt.tripcolor(C1_ab_xyt[n+1:2*n+1,0],C1_ab_xyt[n+1:2*n+1,1],C1_ab_xyt[n+1:2*n+1,2])
plt.title("Caso 1-Periodicas-T 100 ")
plt.ylabel("Y")
plt.xlabel("X")
plt.colorbar()
plt.savefig('C1_pe_T2.png')
plt.close()

plt.tripcolor(C1_ab_xyt[2*n+1:,0],C1_ab_xyt[2*n+1:,1],C1_ab_xyt[2*n+1:,2])
plt.title("Caso 1-Periodicas-T 2500 ")
plt.ylabel("Y")
plt.xlabel("X")
plt.colorbar()
plt.savefig('C1_pe_T3.png')
plt.close()


############## fijas
C1_ab_xyt = np.genfromtxt("C1_fijas_x_y_T.dat",comments='T')

n=441;
plt.tripcolor(C1_ab_xyt[0:n+1,0],C1_ab_xyt[0:n+1,1],C1_ab_xyt[0:n+1,2])
plt.title("Caso 1-Fijas-T 0 ")
plt.ylabel("Y")
plt.xlabel("X")
plt.colorbar()
plt.savefig('C1_fi_T0.png')
plt.close()

plt.tripcolor(C1_ab_xyt[n+1:2*n+1,0],C1_ab_xyt[n+1:2*n+1,1],C1_ab_xyt[n+1:2*n+1,2])
plt.title("Caso 1-Fijas-T 100 ")
plt.ylabel("Y")
plt.xlabel("X")
plt.colorbar()
plt.savefig('C1_fi_T2.png')
plt.close()

plt.tripcolor(C1_ab_xyt[2*n+1:,0],C1_ab_xyt[2*n+1:,1],C1_ab_xyt[2*n+1:,2])
plt.title("Caso 1-Fijas-T 2500 ")
plt.ylabel("Y")
plt.xlabel("X")
plt.colorbar()
plt.savefig('C1_fi_T3.png')
plt.close()


n=441;
n2=21;
animacion = np.genfromtxt("animacion.dat")
def update(i):
	x = animacion[i*n +1:(i+1)*n+1,0]
	y = animacion[i*n +1:(i+1)*n+1,1]
	t = animacion[i*n +1:(i+1)*n+1,2]

	xx=np.reshape(x, (n2,n2))
	yy=np.reshape(y, (n2,n2))
	tt=np.reshape(t, (n2,n2))
	ax.cla()
	ax.plot_surface(xx, yy, tt)

fig = plt.figure()
ax = fig.gca(projection='3d')

anim = animation.FuncAnimation(fig, update,frames=500, interval=20) 

anim.save("animacionbono.mp4")









