#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include "func.h"

void fermat(mpz_t n, mpz_t k,mpz_t* nbb){
	if(mpz_divisible_ui_p(n,2)){
		gmp_printf("COMPOSÉ, vous devez entrer un nombre impair\n");
		return;
	}
	if(mpz_cmp_ui(n,1)==0){
		gmp_printf("Attention, 1 n'est pas un nombre premier\n");
		return;
	}
   	int i=0;
  	gmp_randstate_t alea;
	gmp_randinit(alea,0,128);
	mpz_t tmp;
	mpz_init(tmp);
	unsigned long graine,res;
	time (&graine);    
	gmp_randseed_ui(alea,graine);
	mpz_t n_1;
	mpz_init(tmp);
	//mpz_sub(n_1,n,UN);
	mpz_sub_ui(n_1,n,1);
	//for(count=5; count; count--)
	unsigned long  v = mpz_get_ui(k);
	for(i=0;i<v;i++){
		mpz_urandomm (tmp,alea, n);
	    //mpz_rrandomb(tmp,alea, n);
	    if(mpz_get_ui(tmp)==1 ||  mpz_get_ui(tmp)==0 ) i--;
	    else{
	     	//gmp_printf("Alea: %Zd\n",tmp);
	      	square_and_multiply(tmp,n,n_1,nbb);
	      	if(mpz_get_ui(*nbb) != 1){
	      	printf("COMPOSÉ\n");
	      	return;
	      	}
	      }
	   }
	    printf("PREMIER\n");

	  gmp_randclear(alea);
	  mpz_clear(n);
	  mpz_clear(tmp);
	  //return 0;
}

int main(int argc,char **argv){ 
 mpz_t k,n,H;
 mpz_init_set_str(k,argv[1],10);
 mpz_init_set_str(n,argv[2],10);  //787 4073 	4079 	4091 	4093 	4099 	4111 	4127 	4129 	4133
 //mpz_init_set_str(H,"541",10);

mpz_t nbb;
mpz_init(nbb);

 fermat(n,k,&nbb);
 //fermat(n,a);
 
 //square_and_multiply(a,n,H,&nbb);
 //mpz_set(nbb,*(square_and_multiply(a,n,H,&nbb)));
 //mpz_set(nbb,*goo(&a));
 //gmp_printf("nbb: %Zd\n",nbb);
 
 return 0;
}
