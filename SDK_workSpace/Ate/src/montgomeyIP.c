#include "opr_code.h"
#include "ip_mmm256_opt.h"

#define MMM_baseadder 0xC2000000


Xuint32 i;
void Modular_Mc(int Modulo[ ], int Mc) {
	IP_MMM256_OPT_mWriteSlaveReg0(MMM_baseadder,0,run_write_modulo_mc);
	for(i = 0; i<9; i++ ) {
		IP_MMM256_OPT_mWriteSlaveReg1(MMM_baseadder,0,Modulo[i]);
	}
	IP_MMM256_OPT_mWriteSlaveReg1(MMM_baseadder,0,Mc);
}

void Montgomery(int A[],int B[],int res[]) {

	IP_MMM256_OPT_mWriteSlaveReg0(MMM_baseadder,0,run_write_A_B);
	for(i = 0; i<9; i++ ) {
		IP_MMM256_OPT_mWriteSlaveReg1(MMM_baseadder,0,A[i]);
	}
	for(i = 0; i<9; i++ ) {
		IP_MMM256_OPT_mWriteSlaveReg1(MMM_baseadder,0,B[i]);
	}

	int temp;
	IP_MMM256_OPT_mWriteSlaveReg0(MMM_baseadder,0,run_MMM);

	temp = IP_MMM256_OPT_mReadSlaveReg2(MMM_baseadder,0);
	while(temp==0xFFFFFFFF) {
		temp = IP_MMM256_OPT_mReadSlaveReg2(MMM_baseadder,0);
	}

	//----------------lecture du résultat
	for(i = 0; i<9; i++ ) {
		res[i]= IP_MMM256_OPT_mReadSlaveReg2(MMM_baseadder,0);
	}

	IP_MMM256_OPT_mWriteSlaveReg0(MMM_baseadder,0,reset_ip_mm);


}
