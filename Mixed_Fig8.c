// Mixed_Fig8.c  for Bull, Wichman, Krone
// variables (floats) ending in 'i' are infected, others are free
//  kills all infections at transfer and dilutes pool to 1000 phage, so is
// 	fixed-count dilution

#include <stdio.h>
#include <math.h>
FILE *fp, *fopen();

int main()
{

char out[30];
int dummy,dummy1, I,J,i,j,k,innerloop,totcycles,totaltimesteps,printcycles,K,Klim;

float 
Pa, Pai, Pb, Pbi,  Pg, Pgai,  Pgbi,
Qa, Qai, Qb, Qbi,  Qg, Qgai,  Qgbi,
za, zai, zb, zbi,  zg, zgai,  zgbi,
BA, BB, S, r, bA, bB, bGA, bGB, kaa, kbb, kab, kba, kga, kgb, delta,
h,CA, CB,D;

printf("input h, bacterial r (usually 0.1 or 0.3) and filename for output\n");
scanf("%f %f %s",&h,&r,out);

printf("input specialist burst sizes\n");
scanf("%f %f",&bA,&bB);

fp = fopen(out,"a+");

delta = 1.0;
//r = 0.1;
//bA = 20.0;
//bB = 10.0;
//h = .01;
 kaa= kbb=  kga= kgb = 1E-9;
 kab= kba= 0.0;

totaltimesteps = 1000;

fprintf(fp,"bGA, bGB, pA, pB, pG\n");
Klim = (int)(1.0/h);

for(bGA = 5.0; bGA<=25.0;bGA+=0.5)			{
for(bGB = 5; bGB<=25;bGB+=0.5)				{

Pa= Pai= Pb= Pbi=  Pg= Pgai=  Pgbi=0.0;
Qa= Qai= Qb= Qbi=  Qg= Qgai=  Qgbi=0.0;
za= zai= zb= zbi=  zg= zgai=  zgbi=0.0;

CA = CB = 0.0;

Pa = Pb = 1.0;
Pg = 1.0;

BA = BB = 1E7;



for(I=1;I<=totaltimesteps;I++)					{
for(K=1;K<=Klim;K++)				{   // reciprocal of h

CA = BA + h* (BA * (r - kaa*Pa -  kga*Pg));

CB = BB + h* (BB * (r - kbb*Pb -  kgb*Pg));


Qai = Pai + h*(kaa*Pa*BA  - delta*Pai);  // don't need 'a on a' etc.  Is one culture at a time
Qa = Pa + h*(bA*delta * Pai   - kaa * Pa * BA );


Qbi = Pbi + h*(  kbb * Pb * BB - delta * Pbi);
Qb = Pb + h*(bB *delta *Pbi - kbb * Pb * BB );


Qg = Pg + h*( - kga * Pg *BA - kgb * Pg *BB + bGA * delta * Pgai + bGB * delta * Pgbi);

Qgai = Pgai + h*(  kga *Pg *BA  - delta * Pgai);

Qgbi = Pgbi + h*(  kgb * Pg * BB - delta *Pgbi);


BA = CA;
BB = CB;

Pai = Qai;
Pa = Qa;
Pbi = Qbi;
Pb = Qb;

Pgai = Qgai;
Pgbi = Qgbi;
Pg = Qg;


							}

if (I%20 ==0)	{
BA = 1.0E7;
BB = 1.0E7;

Pai = Pbi = Pgai = Pgbi = 0.0;

S = (Pa+ Pai+ Pb+ Pbi+  Pg+ Pgai+  Pgbi);

S /= 1000.0;   // phages will start at 1000 strong

// this dilution knocks total density back to 1 every 20 steps
// below sets all infections to 0 as if filtering or chloroforming

Pa = (Pa )/S;
//Pai = (Pai )/S;
Pai = 0.0;

Pb = (Pb)/S;
//Pbi = (Pbi)/S;
Pbi = 0.0;

Pg = (Pg )/S;
//Pgai = (Pgai )/S;
Pgai = 0.0;
//Pgbi = Pgbi/S;
Pgbi = 0.0;
			}



if  (I== totaltimesteps)	{

Pai = Pbi = Pgai = Pgbi = 0.0;

D = (Pa+ Pai+ Pb+ Pbi+  Pg+ Pgai+  Pgbi);

fprintf(fp,"%2.1f,  %2.1f, %1.3e, %1.3e, %1.3e\n",bGA,bGB,
(((Pa +Pai )/D)  ),
(((Pb +Pbi )/D)  ),
(((Pg +Pgai +Pgbi)/D) ));

			}

								} // end of I loop
}}

fclose(fp);
}
