// Sequential_Fig7.c to accompany Bull, Wichman, Krone
// types ending in 'i' are infected, others are free
// fixed-count dilution to 1000

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

if (I%40==0) {
	BA = 1.0E7;
	BB = 0.0;
		}
if ((I+20)%40==0) {
	BB = 1.0E7;
	BA = 0.0;
		}

Pai = Pbi = Pgai = Pgbi = 0.0;


S = (Pa+ Pai+ Pb+ Pbi+  Pg+ Pgai+  Pgbi);
S /= 1000.0;

// this dilution knocks total density back to 1000 every 20 steps

Pa = (Pa )/S;
Pai = (Pai )/S;

Pb = (Pb)/S;
Pbi = (Pbi)/S;

Pg = (Pg )/S;
Pgai = (Pgai )/S;
Pgbi = Pgbi/S;
			}


if  (I== totaltimesteps-20)     {  // totaltimesteps better be evenly divisible by 20

Pai = Pbi = Pgai = Pgbi = 0.0;  // kills infections

D = (Pa+ Pai+ Pb+ Pbi+  Pg+ Pgai+  Pgbi);
za = Pa /D;
zai = Pai /D;
zb = Pb /D;
zbi = Pbi /D;
zg = Pg /D;
zgai = Pgai /D;
zgbi = Pgbi/D;
                        }

if  (I== totaltimesteps)	{

Pai = Pbi = Pgai = Pgbi = 0.0;
D = (Pa+ Pai+ Pb+ Pbi+  Pg+ Pgai+  Pgbi);

fprintf(fp,"%2.1f,  %2.1f, %1.3e, %1.3e, %1.3e\n",bGA,bGB,
(((Pa +Pai )/D) + za + zai )/2.0,
(((Pb +Pbi )/D) + zb + zbi )/2.0 ,
(((Pg +Pgai +Pgbi)/D) +  zg + zgai + zgbi)/2.0);

			}

								} // end of I loop
}}

fclose(fp);
}
