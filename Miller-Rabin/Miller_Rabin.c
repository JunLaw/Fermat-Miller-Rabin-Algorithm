#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include "func.h"


void miller_rabin(mpz_t n, mpz_t k,mpz_t* nbb){
	if(mpz_divisible_ui_p(n,2)){
		gmp_printf("COMPOSÉ, vous devez entrer un nombre impair\n");
		return;
	}
	if(mpz_cmp_ui(n,1)==0){
		gmp_printf("Attention, 1 n'est pas un nombre premier\n");
		return;
	}
	//Décomposition de n-1 en 2^s*t
	mpz_t n_1;
	mpz_init(n_1);
	mpz_sub_ui(n_1,n,1);
	mpz_t s,t;
	mpz_init(s);
	mpz_init(t);
	while(mpz_divisible_ui_p(n_1,2)){
		mpz_add_ui(s,s,1);
		mpz_tdiv_q_ui(n_1,n_1,2);
	}
	mpz_set(t,n_1);
	unsigned long int s_1 = mpz_get_ui(s);
	//gmp_printf("S vaut %Zd, T vaut: %Zd\n",s,t);
	//Fin Décomposition de n-1 en 2^s*t

	//Initialisation de variables
	mpz_t deux;
	mpz_init_set_str(deux,"2",10);
	unsigned long  v = mpz_get_ui(k);
	int i=0;
	gmp_randstate_t alea;
	gmp_randinit(alea,0,128);
	mpz_t a;
	mpz_init(a);
	unsigned long graine,res;
	time (&graine);    
	gmp_randseed_ui(alea,graine);
	mpz_init(a);
	for(i=0;i<v;i++){  // Boucle pour i de 1 à k
		mpz_urandomm(a,alea,n);
		if(mpz_get_ui(a)==0) i--;
		square_and_multiply(a,n,t,nbb);	//nbb <-- a^t mod n	
		if((mpz_get_ui(*nbb) != 1) && ((mpz_get_ui(*nbb)!=(-1)))){
			for(int j=1;j<s_1-1; ++j){ // Boucle pour j de 1 à s-1
				square_and_multiply(*nbb,n,deux,nbb); //nbb <-- nbb^2 mod n
				if((mpz_get_ui(*nbb)) == 1){ 
					gmp_printf("COMPOSÉ1\n");
					return;
				}
				if((mpz_get_ui(*nbb)) == -1){
					break;
				}
			} // Fin Boucle pour j de 1 à s-1
			if(mpz_get_ui(*nbb)==0 || mpz_get_ui(*nbb) == (mpz_get_ui(n)-1));
			else{
				gmp_printf("COMPOSÉ2\n");
				return;
			}
			
		}
	} // Fin Boucle pour i de 1 à k
	gmp_printf("PREMIER\n");
}   

int main(int argc,char **argv){ 
 mpz_t k,n,H;
 mpz_init_set_str(k,argv[1],10);
 mpz_init_set_str(n,argv[2],10);  //787 4073 	4079 	4091 	4093 	4099 	4111 	4127 	4129 	4133
 //mpz_init_set_str(H,"541",10);

mpz_t nbb;
mpz_init(nbb);

 //fermat(n,a,&nbb);
 miller_rabin(n,k,&nbb);
 //fermat(n,a);
 
 //square_and_multiply(a,n,H,&nbb);
 //mpz_set(nbb,*(square_and_multiply(a,n,H,&nbb)));
 //mpz_set(nbb,*goo(&a));
 gmp_printf("nbb: %Zd\n",nbb);
 
 return 0;
}