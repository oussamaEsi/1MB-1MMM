#include <stdio.h>
#include "headers.h"


int main() {

	/// 2370fb04 9d410fbe 4e761a98 86e50241 7d023f40 18000001 7e806000 00000001
	p[0]=1;
	p[1]=0x7e806000;
	p[2]=0x18000001;
	p[3]=0x7d023f40;
	p[4]=0x86e50241;
	p[5]=0x4e761a98;
	p[6]=0x9d410fbe;
	p[7]=0x2370fb04;
	p[8]=0;

	m=0xffffffff;

    Modular_Mc(p, m);// M , N'

	/// 20586450 8ffae3b9 ac8ae3e2 c465f114 9e563912 251d0a57 b373bff8 c6dc068a
	R[0]=0xc6dc068a;
	R[1]=0xb373bff8;
	R[2]=0x251d0a57;
	R[3]=0x9e563912;
	R[4]=0xc465f114;
	R[5]=0xac8ae3e2;
	R[6]=0x8ffae3b9;
	R[7]=0x20586450;
	R[8]=0;

	/// 205ebc6 14cbee97 27941620 596d1c6b 2d6bf940 7035bb4b 4c7fb319 27a43416
	R2[0]=0x27a43416;
	R2[1]=0x4c7fb319;
	R2[2]=0x7035bb4b;
	R2[3]=0x2d6bf940;
	R2[4]=0x596d1c6b;
	R2[5]=0x27941620;
	R2[6]=0x14cbee97;
	R2[7]=0x205ebc6;
	R2[8]=0;

	initNul(UN);
	UN[0]=1;

	initNul(redFp);
	redFp[0]=5;
	subFp(p,redFp,p,redFp); //redFp = -5

	subFp(p,UN,p,p_2);
	subFp(p_2,UN,p,p_2); // p-2

	/// 3fc01000 00000000
	t[0] = 0;
	t[1] = 0x3fc01000;

	/// 1 7e806000 00000002
	s[0] = 2;
	s[1] = 0x7e806000;
	/// s[2]=1;

	/// y1i
	/// bf9d596 17679d84 765b517a e4e5f422 9a8932f9 b1b3e4ff 3cae1133 5a6abeb2
	y11[0]=0x5a6abeb2;
	y11[1]=0x3cae1133;
	y11[2]=0xb1b3e4ff;
	y11[3]=0x9a8932f9;
	y11[4]=0xe4e5f422;
	y11[5]=0x765b517a;
	y11[6]=0x17679d84;
	y11[7]=0xbf9d596;
	y11[8]=0;

	/// 2370fb04 9d410fbe 074d0d4c 43728120 5f408fd0 05ffffff 40bfd000 00000000
	y12[0]=0;
	y12[1]=0x40bfd000;
	y12[2]=0x5ffffff;
	y12[3]=0x5f408fd0;
	y12[4]=0x43728120;
	y12[5]=0x74d0d4c;
	y12[6]=0x9d410fbe;
	y12[7]=0x2370fb04;
	y12[8]=0;

	///a6a1689 91bf611a 1a4dba88 bb5c4b1a 96e9f833 6a4488b4 64d5aa9b 1e46a58e
	y13[0]=0x1e46a58e;
	y13[1]=0x64d5aa9b;
	y13[2]=0x6a4488b4;
	y13[3]=0x96e9f833;
	y13[4]=0xbb5c4b1a;
	y13[5]=0x1a4dba88;
	y13[6]=0x91bf611a;
	y13[7]=0xa6a1689;
	y13[8]=0;

	/// 2370fb04 9d410fbe 074d0d4c 43728120 5f408fd0 05ffffff 40bfcfff ffffffff
	y14[0]=0xffffffff;
	y14[1]=0x40bfcfff;
	y14[2]=0x5ffffff;
	y14[3]=0x5f408fd0;
	y14[4]=0x43728120;
	y14[5]=0x74d0d4c;
	y14[6]=0x9d410fbe;
	y14[7]=0x2370fb04;
	y14[8]=0;

	/// 21e13bf8 1798d353 f26883a6 5d5b5939 79630479 d090a3b6 a6a7f967 c3dbe6dd
	y15[0]=0xc3dbe6dd;
	y15[1]=0xa6a7f967;
	y15[2]=0xd090a3b6;
	y15[3]=0x79630479;
	y15[4]=0x5d5b5939;
	y15[5]=0xf26883a6;
	y15[6]=0x1798d353;
	y15[7]=0x21e13bf8;
	y15[8]=0;

	/// y2i
	/// 2370fb04 9d410fbe 074d0d4c 43728120 5f408fd0 05ffffff 40bfd000 00000000
	y21[0]=0;
	y21[1]=0x40bfd000;
	y21[2]=0x5ffffff;
	y21[3]=0x5f408fd0;
	y21[4]=0x43728120;
	y21[5]=0x74d0d4c;
	y21[6]=0x9d410fbe;
	y21[7]=0x2370fb04;
	y21[8]=0;

	/// 2370fb04 9d410fbe 074d0d4c 43728120 5f408fd0 05ffffff 40bfcfff ffffffff
	y22[0]=0xffffffff;
	y22[1]=0x40bfcfff;
	y22[2]=0x5ffffff;
	y22[3]=0x5f408fd0;
	y22[4]=0x43728120;
	y22[5]=0x74d0d4c;
	y22[6]=0x9d410fbe;
	y22[7]=0x2370fb04;
	y22[8]=0;

	/// 2370fb04 9d410fbe 4e761a98 86e50241 7d023f40 18000001 7e806000 00000000
	y23[0]=0;
	y23[1]=0x7e806000;
	y23[2]=0x18000001;
	y23[3]=0x7d023f40;
	y23[4]=0x86e50241;
	y23[5]=0x4e761a98;
	y23[6]=0x9d410fbe;
	y23[7]=0x2370fb04;
	y23[8]=0;

	/// 47290d4c 43728121 1dc1af70 12000002 3dc09000 00000001
	y24[0]=0x1;
	y24[1]=0x3dc09000;
	y24[2]=0x12000002;
	y24[3]=0x1dc1af70;
	y24[4]=0x43728121;
	y24[5]=0x47290d4c;
	y24[6]=0;
	y24[7]=0;
	y24[8]=0;

	/// 47290d4c 43728121 1dc1af70 12000002 3dc09000 00000002
	y25[0]=0x2;
	y25[1]=0x3dc09000;
	y25[2]=0x12000002;
	y25[3]=0x1dc1af70;
	y25[4]=0x43728121;
	y25[5]=0x47290d4c;
	y25[6]=0;
	y25[7]=0;
	y25[8]=0;


	// Entrer les parametres dans le domaine Montgomery
	Montgomery(redFp,R2,redFp);

	Montgomery(y11,R2,y11);
	Montgomery(y12,R2,y12);
	Montgomery(y13,R2,y13);
	Montgomery(y14,R2,y14);
	Montgomery(y15,R2,y15);

	Montgomery(y21,R2,y21);
	Montgomery(y22,R2,y22);
	Montgomery(y23,R2,y23);
	Montgomery(y24,R2,y24);
	Montgomery(y25,R2,y25);


    /// **************************  Q  ****************
    PointFp2 Q;
    /// **************************   Q.x  ********************
    /// 19B0BEA4 AFE4C330 DA93CC35 33DA38A9 F430B471 C6F8A536 E81962ED 967909B5
    Q.x[0][8]=0;
    Q.x[0][7]=0x19B0BEA4;
    Q.x[0][6]=0xAFE4C330;
    Q.x[0][5]=0xDA93CC35;
    Q.x[0][4]=0x33DA38A9;
    Q.x[0][3]=0xF430B471;
    Q.x[0][2]=0xC6F8A536;
    Q.x[0][1]=0xE81962ED;
    Q.x[0][0]=0x967909B5;

    /// A1CF585 585A61C6 E9880B1F 2A5C539F 7D906FFF 238FA634 1E1DE1A2 E45C3F72
    Q.x[1][8]=0;
    Q.x[1][7]=0xA1CF585;
    Q.x[1][6]=0x585A61C6;
    Q.x[1][5]=0xE9880B1F;
    Q.x[1][4]=0x2A5C539F;
    Q.x[1][3]=0x7D906FFF;
    Q.x[1][2]=0x238FA634;
    Q.x[1][1]=0x1E1DE1A2;
    Q.x[1][0]=0xE45C3F72;

    /// ************************  Q.y   ********************
    /// 17ABD366 EBBD6533 3E49C711 A80A0CF6 D24ADF1B 9B3990EE DCC91731 384D2627
    Q.y[0][8]=0;
    Q.y[0][7]=0x17ABD366;
    Q.y[0][6]=0xEBBD6533;
    Q.y[0][5]=0x3E49C711;
    Q.y[0][4]=0xA80A0CF6;
    Q.y[0][3]=0xD24ADF1B;
    Q.y[0][2]=0x9B3990EE;
    Q.y[0][1]=0xDCC91731;
    Q.y[0][0]=0x384D2627;

    ///  EE97D6D E9902A27 D00E9522 32A78700 863BC9AA 9BE960C3 2F5BF9FD 0A32D345
    Q.y[1][8]=0;
    Q.y[1][7]=0xEE97D6D;
    Q.y[1][6]=0xE9902A27;
    Q.y[1][5]=0xD00E9522;
    Q.y[1][4]=0x32A78700;
    Q.y[1][3]=0x863BC9AA;
    Q.y[1][2]=0x9BE960C3;
    Q.y[1][1]=0x2F5BF9FD;
    Q.y[1][0]=0x0A32D345;

    /// ***********************  Q.z   ***********************
    initNul2D(Q.z,2,9);
    Q.z[0][0]=1;


    ///**********************  P ******************
    PointFp P;
    ///********************* P.x = 1  ***********************
    initNul(P.x);
    P.x[0]=1;

    ///********************* P.y = racine(6)  **********************
    ///  d45589b 158faaf6 ab0e4ad3 8d998e99 82e7ff63 964ee146 0342a592 677cccb0
    P.y[8]=0;
    P.y[7]=0xd45589b;
    P.y[6]=0x158faaf6;
    P.y[5]=0xab0e4ad3;
    P.y[4]=0x8d998e99;
    P.y[3]=0x82e7ff63;
    P.y[2]=0x964ee146;
    P.y[1]=0x0342a592;
    P.y[0]=0x677cccb0;

    P.isInfinity = 0;


    elemFp12 f;
    transfMongPointFp2(&Q);
    transfMongPointFp(&P);

    optAte(Q,P,&f);

    invTransMongFp12(f,&f);
    printHexFp12(f);


    return 0;
}
