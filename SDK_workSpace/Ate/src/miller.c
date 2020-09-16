#include "headers.h"

#include "xtmrctr.h"
#include "xtmrctr_i.h"

int cpt; //Timer

// Doublement + tangent
void pointDoubLineEval (PointFp2 Q, PointFp P, elemFp12 *l, PointFp2 *T){

    ///***********     1          ***********///
    unsigned long tmp0[2][9];
    squarFp2 (Q.x, tmp0);

    ///***********     2          ***********///
    unsigned long tmp1[2][9];
    squarFp2(Q.y, tmp1);

    ///***********     3          ***********///
    unsigned long tmp2[2][9];
    squarFp2(tmp1, tmp2);

    ///***********     4          ***********///
    unsigned long tmp3[2][9];
    addFp2(tmp1,Q.x,tmp3);
    squarFp2(tmp3, tmp3);
    subFp2(tmp3,tmp0,tmp3);
    subFp2(tmp3,tmp2,tmp3);

    ///***********     5          ***********///
    addFp2(tmp3,tmp3,tmp3);

    ///***********     6          ***********///
    unsigned long tmp4[2][9];
    addFp2(tmp0,tmp0,tmp4);
    addFp2(tmp4,tmp0,tmp4);

    ///***********     7          ***********///
    unsigned long tmp6[2][9];
    addFp2(tmp4,Q.x, tmp6, p);

    ///***********     8          ***********///
    unsigned long tmp5[2][9];
    squarFp2(tmp4, tmp5);

    ///***********     9          ***********///
    subFp2(tmp5,tmp3,(*T).x);
    subFp2((*T).x,tmp3,(*T).x);

    ///***********     10          ***********///
    unsigned long Zq2[2][9];
    addFp2(Q.y,Q.z,(*T).z);
    squarFp2((*T).z,(*T).z);
    subFp2((*T).z,tmp1,(*T).z);
    squarFp2(Q.z,Zq2);
    subFp2((*T).z,Zq2,(*T).z);

    ///***********     11          ***********///
    addFp2(tmp2,tmp2,tmp2);
    addFp2(tmp2,tmp2,tmp2);
    addFp2(tmp2,tmp2,tmp2);
    subFp2(tmp3,(*T).x,(*T).y);
    karatsubaFp2((*T).y,tmp4,(*T).y);
    subFp2((*T).y,tmp2,(*T).y);

    ///***********     12          ***********///
    karatsubaFp2(tmp4,Zq2,tmp3);
    addFp2(tmp3,tmp3,tmp3);
    oppFp2(tmp3,tmp3);

    ///***********     13          ***********///
    /// !!!!!!!!  affectation l10  !!!!!!!!!!
    mulCFp2(tmp3,P.x,(*l).w1.v0);

    ///***********     14          ***********///
    squarFp2(tmp6,tmp6);
    subFp2(tmp6,tmp0,tmp6);
    subFp2(tmp6,tmp5,tmp6);
    addFp2(tmp1,tmp1,tmp1);
    addFp2(tmp1,tmp1,tmp1);
    ///!!!!!!!!   affectation l11 !!!!!!!!!!!!
    subFp2(tmp6,tmp1,(*l).w1.v1);

    ///***********     15          ***********///
    karatsubaFp2((*T).z,Zq2,tmp0);
    addFp2(tmp0,tmp0,tmp0);

    ///***********     16          ***********///
    ///!!!!!!!!! affectation l00  !!!!!!!!
    mulCFp2(tmp0,P.y,(*l).w0.v0);

    ///***********     17          ***********///
    /// a0 six numbers , a1 six numbers

    ///***********     18          ***********///
    unsigned long i,j;
    for(j=0;j<2;j++) for(i=0;i<9;i++) (*l).w0.v1[j][i]=0;
    for(j=0;j<2;j++) for(i=0;i<9;i++) (*l).w0.v2[j][i]=0;

    ///***********     19          ***********///
    for(j=0;j<2;j++) for(i=0;i<9;i++) (*l).w1.v2[j][i]=0;

}

// Addition + Line
void pointAddLineEval (PointFp2 Q, PointFp2 R, PointFp P, elemFp12 *l, PointFp2 *T){

    ///***********     1          ***********///
    unsigned long t0[2][9], zr2[2][9];
    squarFp2(R.z,zr2);
    karatsubaFp2(Q.x,zr2,t0);

    ///***********     2          ***********///
    unsigned long t1[2][9], yq2[2][9];
    squarFp2(Q.y,yq2);
    addFp2(Q.y,R.z,t1);
    squarFp2(t1,t1);
    subFp2(t1,yq2,t1);
    subFp2(t1,zr2,t1);

    ///***********     3          ***********///
    karatsubaFp2(t1,zr2,t1);

    ///***********     4          ***********///
    unsigned long t2[2][9];
    subFp2(t0,R.x,t2);

    ///***********     5          ***********///
    unsigned long t3[2][9];
    squarFp2(t2,t3);

    ///***********     6          ***********///
    unsigned long t4[2][9];
    addFp2(t3,t3,t4);
    addFp2(t4,t4,t4);

    ///***********     7          ***********///
    unsigned long t5[2][9];
    karatsubaFp2(t4,t2,t5);

    ///***********     8          ***********///
    unsigned long t6[2][9];
    subFp2(t1,R.y,t6);
    subFp2(t6,R.y,t6);

    ///***********     9          ***********///
    unsigned long t9[2][9];
    karatsubaFp2(t6,Q.x,t9);

    ///***********     10          ***********///
    unsigned long t7[2][9];
    karatsubaFp2(t4,R.x,t7);

    ///***********     11          ***********///
    squarFp2(t6,(*T).x);
    subFp2((*T).x,t5,(*T).x);
    subFp2((*T).x,t7,(*T).x);
    subFp2((*T).x,t7,(*T).x);

    ///***********     12          ***********///
    addFp2(R.z,t2,(*T).z);
    squarFp2((*T).z,(*T).z);
    subFp2((*T).z,zr2,(*T).z);
    subFp2((*T).z,t3,(*T).z);

    ///***********     13          ***********///
    unsigned long t10[2][9];
    addFp2(Q.y,(*T).z,t10);

    ///***********     14          ***********///
    unsigned long t8[2][9];
    subFp2(t7,(*T).x,t8);
    karatsubaFp2(t8,t6,t8);

    ///***********     15          ***********///
    karatsubaFp2(R.y,t5,t0);
    addFp2(t0,t0,t0);

    ///***********     16          ***********///
    subFp2(t8,t0,(*T).y);

    ///***********     17          ***********///
    ///!!!!!!!!!!!!!!! zt2 == t2 !!!!!!!!!!!!!!!!!!!
    squarFp2((*T).z,t2);
    squarFp2(t10,t10);
    subFp2(t10,yq2,t10);
    subFp2(t10,t2,t10);

    ///***********     18          ***********///
    addFp2(t9,t9,t9);
    ///!!!!!!!!!  affection  l11   !!!!!!!!!
    subFp2(t9,t10,(*l).w1.v1);

    ///***********     19          ***********///
    mulCFp2((*T).z,P.y,t10);
    ///!!!!!!!!    affectation  l00  !!!!!!!
    addFp2(t10,t10,(*l).w0.v0);

    ///***********     20          ***********///
    oppFp2(t6,t6);

    ///***********     21          ***********///
    mulCFp2(t6,P.x,t1);
    ///!!!!!!!   affectation l10  !!!!!!!!
    addFp2(t1,t1,(*l).w1.v0);

    ///***********     22          ***********///

    ///***********     23          ***********///
    int i,j;
    for(j=0;j<2;j++) for(i=0;i<9;i++) (*l).w0.v1[j][i]=0;
    for(j=0;j<2;j++) for(i=0;i<9;i++) (*l).w0.v2[j][i]=0;

    ///***********     23          ***********///
    for(j=0;j<2;j++) for(i=0;i<9;i++) (*l).w1.v2[j][i]=0;

}

// Final Exponontiation
void finalExpo (elemFp12 *f){

    ///************* 1 *********************
    elemFp12 f1;
    conjugFp12(*f,&f1);
    ///************* 2 *********************
    elemFp12 f2;
    invFp12(*f,&f2);
    ///************* 3 *********************
    mulFp12(f1,f2,f);
    ///************* 4 *********************
    elemFp12 ft1;
    frob_p2(*f,&ft1);
    mulFp12(ft1,*f,f);
    ///************* 5 *********************
    expTFp12(*f,&ft1);
    ///************* 6 *********************
    elemFp12 ft2;
    expTFp12(ft1,&ft2);
    ///************* 7 *********************
    elemFp12 ft3;
    expTFp12(ft2,&ft3);
    ///************* 8 *********************
    elemFp12 fp1;
    frob_p(*f,&fp1);
    ///************* 9 *********************
    elemFp12 fp2;
    frob_p(fp1,&fp2);
    ///************* 10 *********************
    elemFp12 fp3;
    frob_p(fp2,&fp3);
    //frob_p3(*f,&fp3);
    ///************* 11 *********************
    elemFp12 y0;
    mulFp12(fp1,fp2,&y0);
    mulFp12(y0,fp3,&y0);
    ///************* 12 *********************
    elemFp12 y1;
    conjugFp12(*f,&y1);  /// y1 == inv(f)
    ///************* 13 *********************
    elemFp12 y2;
    frob_p2(ft2,&y2);
    ///************* 14 *********************
    elemFp12 y3;
    frob_p(ft1,&y3);
    ///************* 15 *********************
    conjugFp12(y3,&y3);
    ///************* 16 *********************
    elemFp12 y4;
    frob_p(ft2,&y4);
    mulFp12(y4,ft1,&y4);
    ///************* 17 *********************
    conjugFp12(y4,&y4);
    ///************* 18 *********************
    elemFp12 y5;
    conjugFp12(ft2,&y5);
    ///************* 19 *********************
    elemFp12 y6;
    frob_p(ft3,&y6);
    mulFp12(y6,ft3,&y6);
    ///************* 20 *********************
    conjugFp12(y6,&y6);
    ///************* 21 *********************
    elemFp12 t0;
    squarFp12_V2(y6,&t0);
    mulFp12(t0,y4,&t0);
    mulFp12(t0,y5,&t0);
    ///************* 22 *********************
    elemFp12 t1;
    mulFp12(y3,y5,&t1);
    mulFp12(t1,t0,&t1);
    ///************* 23 *********************
    mulFp12(t0,y2,&t0);
    ///************* 24 *********************
    squarFp12_V2(t1,&t1);
    mulFp12(t1,t0,&t1);
    squarFp12_V2(t1,&t1);
    ///************* 25 *********************
    mulFp12(t1,y1,&t0); /// y1 == inv(f)
    ///************* 26 *********************
    mulFp12(t1,y0,&t1);
    ///************* 27 *********************
    squarFp12_V2(t0,&t0);
    ///************* 28 *********************
    mulFp12(t1,t0,f);

}


// Ate pairing
void ate (PointFp2 Q, PointFp P, elemFp12 *f){

    XTmrCtr deley;
    Xuint32 satus=XTmrCtr_Initialize(&deley,0x83c00000); //declaration de l'adresse du timer
    cpt=0;

    XTmrCtr_SetResetValue(&deley,1,0);
    XTmrCtr_Start(&deley,1);

    int j;
    elemFp12 l;
    PointFp2 T;

    affPointFp2(Q,&T);
    initNulFp12(f);
    setIN(R,(*f).w0.v0[0]);


    for(j=29;j>=0;j--){
    	squaFp12(*f,f);
        pointDoubLineEval(T,P,&l,&T);
        mulFp12_b0b1(*f,l,f);
        if(getBitIndex(tr_1[3],j)==1){
            pointAddLineEval(Q,T,P,&l,&T);
            mulFp12_b0b1(*f,l,f);
        }
    }
    for(j=31;j>=0;j--){
    	squaFp12(*f,f);
        pointDoubLineEval(T,P,&l,&T);
        mulFp12_b0b1(*f,l,f);
        if(getBitIndex(tr_1[2],j)==1){
            pointAddLineEval(Q,T,P,&l,&T);
            mulFp12_b0b1(*f,l,f);
        }
    }
    for(j=63;j>=0;j--){
    	squaFp12(*f,f);
        pointDoubLineEval(T,P,&l,&T);
        mulFp12_b0b1(*f,l,f);
    }

    XTmrCtr_Stop(&deley,1);
    cpt=XTmrCtr_GetValue(&deley,1);
    xil_printf(" point : %d\n\r",cpt);

    finalExpo(f);

}
