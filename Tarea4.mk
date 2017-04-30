	


Resultados_HW4.pdf : Resultados_HW4.tex *.png
	pdflatex Resultados_HW4.tex
*.png: Plots_Temperatura.py datos.dat
	python Plots_Temperatura.py
datos.dat: a.out 
	./a.out > datos.dat
a.out: DifusionTemperatura.c
	gcc DifusionTemperatura.c
