#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>


int nb(mpz_t n){
	mpz_t tmp;
	mpz_init(tmp);
	mpz_set(tmp,n);
	int t;
	if(mpz_divisible_ui_p(tmp,2)) t=2;
	if(mpz_divisible_ui_p(tmp,6)) t=1;
	if(mpz_divisible_ui_p(tmp,10)) t=1;

	else t=1;
	mpz_t un;
	mpz_init_set_str(un,"1",10);
	mpz_t deux;
	mpz_init_set_str(deux,"2",10);
	
	if( (mpz_cmp_ui(n,0)==0) || (mpz_cmp_ui(n,1)==0)){
		return 1;
	}  
	while(mpz_cmp_ui(tmp,2)){  
		mpz_cdiv_q_ui(tmp,tmp,2);
		t++;
	}
	return t;
}


// Renvoie le résultat de a exposant H modulo n
void square_and_multiply(mpz_t a, mpz_t n,mpz_t H,mpz_t* nbb){
	//Calcul de la taille en bits du module H
	int taille = nb(H);
	//printf("TAILLE: %d\n",taille);

	//Initialisations
	mpz_t var;
	mpz_init(var);
	mpz_set(var,H);
	unsigned long int tab[taille];
	int x = 0;
	//gmp_printf("Module H: %Zd\n",var);
	mpz_t deux;
	mpz_init_set_str(deux,"2",10);
	mpz_t q;
	mpz_init(q);
	mpz_tdiv_q(q,H,deux);
	//gmp_printf("Quotient q: %Zd\n",q);
	unsigned long int v = mpz_get_ui(var);
	//gmp_printf("Unsigned v : %ld\n",v);
	mpz_t hi;
	mpz_init(hi);
	int i=0;
	int it=taille;

	//Décomposition binaire du module
	if(mpz_cmp_ui(var,0)==0){
		tab[0] = v; 
		//printf("Décomposition: %ld\n",tab[0]);
		//return;
	}
	else{
		while(i<taille){  
			mpz_mod(hi,var,deux);
			v = mpz_get_ui(hi);
			tab[x] = v;
			mpz_tdiv_q(var,var,deux);
			it--;
			x++;
			i++;
		}		
		tab[taille-1] = 1;
		//printf("On passe le else\n");
	
		//printf("Décomposition");
		for(int j=0; j<taille;j++){
			//printf(" %ld",tab[j]);
		}
	}
	//printf("\n");

	//mpz_t R;
	//mpz_init(R);
	//mpz_t r;
	//mpz_init(r);
	/////// Coeur de l'algorithme 
	//printf("SQUARE AND MULTIPLY\n");
	if(mpz_cmp_ui(H,0)==0){
		mpz_t UN;
		mpz_init_set_str(UN,"1",10);
		// mpz_t R;
		// mpz_init(R);
		mpz_mod(*nbb,UN,n);
		//unsigned long int res = mpz_get_ui(R);
		//gmp_printf("%Zd puissance %Zd mod %Zd vaut %Zd \n",a,H,n,R);
		//return res;
		//return &nbb;
	}
	if(mpz_cmp_ui(H,1)==0){
		// mpz_t R;
		// mpz_init(R);
		mpz_mod(*nbb,a,n);
		//unsigned long int res = mpz_get_ui(R);
		//gmp_printf("%Zd puissance %Zd mod %Zd vaut %Zd \n",a,H,n,R);
		//return res;
		//return &nbb;
	}
	// mpz_t r;
	// mpz_init(r);
	mpz_set(*nbb,a);
	for (int i=taille-2;i>(-1);i--){
		mpz_mul(*nbb,*nbb,*nbb);
		mpz_mod(*nbb,*nbb,n);

		if(tab[i]==1){
			mpz_mul(*nbb,*nbb,a);
			mpz_mod(*nbb,*nbb,n);
		}
	}
	//unsigned long int res = mpz_get_ui(*nbb);
	//gmp_printf("%Zd puissance %Zd mod %Zd vaut %Zd \n",a,H,n,*nbb);

	//return res;
	//return &nbb;
	
}