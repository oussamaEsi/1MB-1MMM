#include "headers.h"

///*********************************** addition / soustraction  **********************************///
unsigned long getBitIndex(unsigned long num,int index){
	unsigned long bit = (num>>index)&1;
	return bit;
}

void add2Op(unsigned long A,unsigned long B,unsigned long *retenue,unsigned long *resultat) {
	unsigned long long r = (unsigned long long) A+B+(*retenue);
	*resultat = (int) r;
	*retenue = r>>32;
}

void sous2Op(unsigned long A, unsigned long B, unsigned long *retenue, unsigned long *resultat) {
	unsigned long long r = (unsigned long long) A+(4294967295-B)+(*retenue);
	*resultat=(int) r;
	*retenue=r>>32;
}

void setIN(unsigned long A[9], unsigned long B[9]) {
	int i;
	for(i=0; i<9; i++)
		B[i] = A[i];
}

/// addition in Fp
unsigned long addFp( unsigned long A[9], unsigned long B[9], unsigned long M[9], unsigned long SZ[9]) {
	unsigned long SZ1[9], SZ2[9];
	unsigned long i, C1=0, C2=1, sign;

	for(i=0; i<9; i++){
		add2Op( A[i], B[i], &C1, &SZ1[i] );
		sous2Op( SZ1[i], M[i], &C2, &SZ2[i]);
	}

	sign = getBitIndex( (C1+C2+3), 1);

	if(sign == 1) setIN( SZ1, SZ);
	else setIN( SZ2, SZ);

	return sign;
}


/// substarction in Fp
unsigned long subFp( unsigned long A[9], unsigned long B[9], unsigned long M[9], unsigned long SZ[9]) {
	unsigned long SZ1[9], SZ2[9];
	unsigned long i, C1=1, C2=0, sign;

	for(i=0; i<9; i++){
		sous2Op( A[i], B[i], &C1, &SZ1[i]);
		add2Op( SZ1[i], M[i], &C2, &SZ2[i]);
	}

	sign = getBitIndex( (C1+3), 0);

	if(sign == 1) setIN( SZ2, SZ);
	else setIN( SZ1, SZ);

	return sign;
}


///******************************************* Operations of Montgomery *********************************///
/*
void multiply ( unsigned long A, unsigned long B, unsigned long *paquetRetenue, unsigned long *resultat) {
	unsigned long long r = (unsigned long long) A*B;
	*resultat = (unsigned long) r;
	*paquetRetenue = r>>32;
}


void add3Op ( unsigned long A, unsigned long B, unsigned long C, unsigned long *retenue, unsigned long *resultat) {
	unsigned long long r = (unsigned long long) A+B+C+(*retenue);
	*resultat = (unsigned long) r;
	*retenue = r>>32;
}

// Multiplication in Fp
void montgomery( unsigned long A[9], unsigned long B[9], unsigned long M[9], unsigned long m, unsigned long Resultat[9]) {
	int S[9] = {0};
	unsigned long Z=0, P=0, C1=0, C2=0;
	unsigned long i, j, q=0, retenue1=0, retenue2=0, tmp=0;

	for( i=0; i<=8; i++ ) {
		C1=0; C2=0; retenue1=0; retenue2=0; tmp=0;//initialisation des retenu dans chaque iteration
		// **************calcul de q
		P = A[i]*B[0];
		Z = P+S[0];
		q = (Z*m);

		//*****calcul de S=A[i]*B +q*M /R
		for( j=0; j<=8; j++ ) {
			tmp = C1; // save la valeur de C1
			multiply( A[i], B[j], &C1, &P); // calcul P = A[i]*B[j] de 32 bits et C1=retenu de 32bit
			add3Op( P, S[j], tmp, &retenue1, &Z); // calcul Z = P+S[j]+tmp les 2bits de retenu save in retenue1
			tmp = C2;// save la valeur de C2
			multiply( q, M[j], &C2, &P); //calcul P = q[i]*M[j] de 32 bits et C2=retenu de 32bit
			add3Op( Z, P, tmp, &retenue2, &P);// calcul P = Z+S[j]+tmp les 2bits de retenu save in retenue2
			if(j!=0) S[j-1] = P;// pour le decalage
		}
		S[j-1] = C1+C2+retenue1+retenue2; // pour ajouter les derniers retenues
	}

	for(i=0; i<=8; i++){
		Resultat[i] = S[i];
	}
}
*/
// Exponontiation in Fp
void expFp (unsigned long a[9], unsigned long exposant[9] ,unsigned long res[9]){
    unsigned long i,j,puis2[9];

    ///******************* INit *******************
    setIN(a,puis2);
    setIN(R,res);
    ///************* exponitiation  ***************
    for(i=0;i<8;i++){
        for(j=0;j<32;j++){
            if(getBitIndex(exposant[i],j) == 1) Montgomery(res,puis2,res);
            Montgomery(puis2,puis2,puis2);
        }
    }

}

// Inverse Exponotiation in Fp
void invFp (unsigned long a[9], unsigned long invA [9]){

    expFp(a,p_2,invA);

}

// Enter in Montgomery field
void transfMongPol (unsigned long A[][9],unsigned long k){
    int i;
    for(i=0;i<k;i++) Montgomery( A[i], R2, A[i]);
}

// Get out Montgomery field
void invTransMongPol (unsigned long A[][9] ,unsigned long B[][9], unsigned long k){
    unsigned long i;
    for(i=0;i<k;i++) Montgomery( A[i], UN, B[i]);
}
