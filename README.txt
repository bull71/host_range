This file explains notation and other properties of the figure files from Bull, Wichman, Krone

The files are:
Mixed_Fig8.c		Parallel_Fig5.c		Parallel_Figs123.c
Parallel_Fig4.nb	Parallel_Fig6.c		Sequential_Fig7.c
figs_ggplot.R

The R file was used with RStudio RStudio 2022.07.2 Build 576 to create all figures except Fig. 4.

The Mathematica file (Parallel_Fig4.nb) largely follows the notation in Eqn (1) of the text, except that the infected state is denoted 'In' and the generalist phage is subscripted with 'G' instead of 'AB'.  


The 5 C files use the following notation:

Free phage states are denoted as 'Pxy' where 
x can be 'a' (A-specialist), 'b' (B-specialist), or 'g' (generalist).
y can be 'a' (host A) or 'b' (host B)

Infected states are denoted as 'Pxyi' where x and y are as above.

burst size of the A-specialist is bA
burst size of the B-specialist is bB
burst size of the generalist on A (B) is bGA (bGB)

adsoprtion rates of phage x on host y are kxy

Bacterial densities are BA (host A), BB (host B)

delta corresponds to lambda in Eqn (1)

Variables beginning with Q correspond to those beginning with P to prevent changing the P values in the middle of updates

Variables  beginning with C correspond to those beginning with B to prevent changing the B values during updates

'h' is the Euler increment, input as 0.001
