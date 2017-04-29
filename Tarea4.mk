	






imagen.png: Plots_Temperatura.py datos.dat
	python Plots_Temperatura.py
datos.dat: a.out 
	./a.out > datos.dat
a.out: DifusionTemperatura.c
	gcc DifusionTemperatura.c
