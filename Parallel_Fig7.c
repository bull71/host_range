// Parallel_Fig6.c for Bull, Wichman, Krone
// types ending in 'i' are infected, others are free
// Fixed count dilution applied to A and B cultures before pooling

#include <stdio.h>
#include <math.h>
FILE *fp, *fopen();

int main()
{

char out[] = "20X";
int dummy,dummy1, I,J,i,j,k,innerloop,totcycles,totaltimesteps,printcycles,K,Klim;

float 
Paa, Paai, Pab, Pabi, Pbb, Pbbi, Pba, Pbai, Pga, Pgai, Pgb, Pgbi,
Qaa, Qaai, Qab, Qabi, Qbb, Qbbi, Qba, Qbai, Qga, Qgai, Qgb, Qgbi,
BA, BB, SA,SB, r, bA, bB, bGA, bGB, kaa, kbb, kab, kba, kga, kgb, delta,
h,CA, CB,D;


printf("input h, bacterial r (usually 0.1 or 0.3) and filename for output\n");
scanf("%f %f %s",&h,&r,out);
Klim = (int)(1.0/h);

printf("input specialist burst sizes \n");
scanf("%f %f",&bA,&bB);


fp = fopen(out,"a+");

delta = 1.0;
 kaa= kbb=  kga= kgb = 1E-9;
 kab= kba= 0.0;

totaltimesteps = 1000;

fprintf(fp,"bGA, bGB, pA, pB, pG\n");

for(bGA = 5.0; bGA<=25.0;bGA+=0.5)			{
for(bGB = 5; bGB<=25;bGB+=0.5)				{

Paa= Paai= Pab= Pabi= Pbb= Pbbi= Pba= Pbai= Pga= Pgai= Pgb= Pgbi=0.0;
Qaa= Qaai= Qab= Qabi= Qbb= Qbbi= Qba= Qbai= Qga= Qgai= Qgb= Qgbi= 0.0;

CA = CB = 0.0;

Paa = Pbb = 1;
Pga = Pgb = 0.5;

BA = BB = 1E7;




for(I=1;I<=totaltimesteps;I++)					{
for(K=1;K<=Klim;K++)				{   // reciprocal of h

CA = BA + h* BA * (r - kaa*Paa - kba*Pba - kga*Pga);

CB = BB + h* BB * (r - kbb*Pbb - kab*Pab - kgb*Pgb);

Qaai = Paai + h*(kaa*Paa*BA - delta*Paai);
Qaa = Paa + h*(bA*delta * Paai   - kaa * Paa * BA);

Qabi = Pabi + h*( kab * Pab * BB - delta*Pabi);
Qab = Pab + h*(- kab * Pab * BB + bA*delta*Pabi);

Qbbi = Pbbi + h*(  kbb * Pbb * BB - delta * Pbbi);
Qbb = Pbb + h*( - kbb * Pbb * BB + bB*delta * Pbbi);

Qbai = Pbai + h*( kba * Pba * BA - delta *Pbai);
Qba = Pba + h*(- kba * Pba * BA + bB*delta *Pbai);

Qgai = Pgai + h*(  kga *Pga *BA - delta * Pgai);
Qga = Pga + h*( - kga *Pga *BA + bGA*delta * Pgai);

Qgbi = Pgbi + h*(  kgb * Pgb * BB - delta *Pgbi);
Qgb = Pgb + h*( - kgb * Pgb * BB + bGB*delta *Pgbi);

BA = CA;
BB = CB;
Paai = Qaai;
Paa = Qaa;
Pabi = Qabi;
Pab = Qab;
Pbbi = Qbbi;
Pbb = Qbb;
Pbai = Qbai;
Pba = Qba;
Pgai = Qgai;
Pga = Qga;
Pgbi = Qgbi;
Pgb = Qgb;


							}

if (I%20 ==0)	{
BA = 1.0E7;
BB = 1.0E7;

Paai = Pabi = Pbbi = Pbai = Pgai = Pgbi = 0.0;

SA = (Paa+ Paai + Pba+ Pbai+ Pga+ Pgai);
SB = ( Pab+ Pabi+ Pbb+ Pbbi+ Pgb+ Pgbi);
SA /= 1000.0;
SB /= 1000.0;
// this dilution knocks density back to 1000 in each culture

Paa = (Paa/SA + Pab/SB )/2.0;
Paai = (Paai/SA + Pabi/SB)/2.0;;
Pabi = Paai;
Pab = Paa;

Pbb = (Pbb/SB+ Pba/SA)/2.0;
Pbbi = (Pbbi/SB + Pbai/SA)/2.0;
Pba = Pbb;
Pbai = Pbbi;

Pga = (Pga/SA + Pgb/SB)/2.0;
Pgai = (Pgai/SA + Pgbi/SB)/2.0;
Pgb = Pga;
Pgbi = Pgai;

			}

if  (I== totaltimesteps)	{

Paai = Pabi = Pbbi = Pbai = Pgai = Pgbi = 0.0;

D = Paa +Paai +Pab +Pabi+Pbb +Pbbi +Pba +Pbai+Pga +Pgai +Pgb +Pgbi;
fprintf(fp,"%2.1f, %2.1f, %1.3e, %1.3e, %1.3e\n",bGA,bGB, (Paa +Paai +Pab +Pabi)/D, (Pbb +Pbbi +Pba +Pbai)/D, (Pga +Pgai +Pgb +Pgbi)/D);

			}

								} // end of I loop
}}

fclose(fp);
}
