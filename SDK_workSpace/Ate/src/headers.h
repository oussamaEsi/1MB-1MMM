#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED


unsigned long UN[9];
unsigned long m;//N(-1)
unsigned long p[9];
unsigned long r[9]; //ordre
unsigned long R[9];
unsigned long R2[9];

unsigned long redFp[9];

unsigned long t[2];
unsigned long s[2];
unsigned long tr_1[9]; // tr-1
unsigned long L;

unsigned long p_2[9]; // p-2

unsigned long y11[9],y12[9],y13[9],y14[9],y15[9]; // Frobenius parametres
unsigned long y21[9],y22[9],y23[9],y24[9],y25[9];
//unsigned long y31[9],y32[9],y33[9],y34[9],y35[9];

typedef struct PointFp2{
    unsigned long x[2][9];
    unsigned long y[2][9];
    unsigned long z[2][9];
} PointFp2;

typedef struct PointFp{
    unsigned long x[9];
    unsigned long y[9];
} PointFp;

typedef struct elemFp4{
    unsigned long v0[2][9];
    unsigned long v1[2][9];
}elemFp4;

typedef struct elemFp6{
    unsigned long v0[2][9];
    unsigned long v1[2][9];
    unsigned long v2[2][9];
} elemFp6;

typedef struct elemFp12{
    elemFp6 w0;
    elemFp6 w1;
} elemFp12;

#endif // HEADERS_H_INCLUDED
