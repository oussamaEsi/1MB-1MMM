/*****************************************************************************
* Filename:          E:\Code_Doctorat_Virtex5\Base_System/drivers/ip_mmm256_opt_v1_00_a/src/ip_mmm256_opt.h
* Version:           1.00.a
* Description:       ip_mmm256_opt Driver Header File
* Date:              Tue Mar 14 13:56:15 2017 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef IP_MMM256_OPT_H
#define IP_MMM256_OPT_H

/***************************** Include Files *******************************/

#include "xbasic_types.h"
#include "xstatus.h"
#include "xil_io.h"

/************************** Constant Definitions ***************************/


/**
 * User Logic Slave Space Offsets
 * -- SLV_REG0 : user logic slave module register 0
 * -- SLV_REG1 : user logic slave module register 1
 * -- SLV_REG2 : user logic slave module register 2
 */
#define IP_MMM256_OPT_USER_SLV_SPACE_OFFSET (0x00000000)
#define IP_MMM256_OPT_SLV_REG0_OFFSET (IP_MMM256_OPT_USER_SLV_SPACE_OFFSET + 0x00000000)
#define IP_MMM256_OPT_SLV_REG1_OFFSET (IP_MMM256_OPT_USER_SLV_SPACE_OFFSET + 0x00000004)
#define IP_MMM256_OPT_SLV_REG2_OFFSET (IP_MMM256_OPT_USER_SLV_SPACE_OFFSET + 0x00000008)

/**
 * Software Reset Space Register Offsets
 * -- RST : software reset register
 */
#define IP_MMM256_OPT_SOFT_RST_SPACE_OFFSET (0x00000100)
#define IP_MMM256_OPT_RST_REG_OFFSET (IP_MMM256_OPT_SOFT_RST_SPACE_OFFSET + 0x00000000)

/**
 * Software Reset Masks
 * -- SOFT_RESET : software reset
 */
#define SOFT_RESET (0x0000000A)

/**************************** Type Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *******************/

/**
 *
 * Write a value to a IP_MMM256_OPT register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the IP_MMM256_OPT device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void IP_MMM256_OPT_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
 *
 */
#define IP_MMM256_OPT_mWriteReg(BaseAddress, RegOffset, Data) \
 	Xil_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/**
 *
 * Read a value from a IP_MMM256_OPT register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the IP_MMM256_OPT device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	Xuint32 IP_MMM256_OPT_mReadReg(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define IP_MMM256_OPT_mReadReg(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (RegOffset))


/**
 *
 * Write/Read 32 bit value to/from IP_MMM256_OPT user logic slave registers.
 *
 * @param   BaseAddress is the base address of the IP_MMM256_OPT device.
 * @param   RegOffset is the offset from the slave register to write to or read from.
 * @param   Value is the data written to the register.
 *
 * @return  Data is the data from the user logic slave register.
 *
 * @note
 * C-style signature:
 * 	void IP_MMM256_OPT_mWriteSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Value)
 * 	Xuint32 IP_MMM256_OPT_mReadSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define IP_MMM256_OPT_mWriteSlaveReg0(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (IP_MMM256_OPT_SLV_REG0_OFFSET) + (RegOffset), (Xuint32)(Value))
#define IP_MMM256_OPT_mWriteSlaveReg1(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (IP_MMM256_OPT_SLV_REG1_OFFSET) + (RegOffset), (Xuint32)(Value))
#define IP_MMM256_OPT_mWriteSlaveReg2(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (IP_MMM256_OPT_SLV_REG2_OFFSET) + (RegOffset), (Xuint32)(Value))

#define IP_MMM256_OPT_mReadSlaveReg0(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (IP_MMM256_OPT_SLV_REG0_OFFSET) + (RegOffset))
#define IP_MMM256_OPT_mReadSlaveReg1(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (IP_MMM256_OPT_SLV_REG1_OFFSET) + (RegOffset))
#define IP_MMM256_OPT_mReadSlaveReg2(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (IP_MMM256_OPT_SLV_REG2_OFFSET) + (RegOffset))

/**
 *
 * Reset IP_MMM256_OPT via software.
 *
 * @param   BaseAddress is the base address of the IP_MMM256_OPT device.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void IP_MMM256_OPT_mReset(Xuint32 BaseAddress)
 *
 */
#define IP_MMM256_OPT_mReset(BaseAddress) \
 	Xil_Out32((BaseAddress)+(IP_MMM256_OPT_RST_REG_OFFSET), SOFT_RESET)

/************************** Function Prototypes ****************************/


/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the IP_MMM256_OPT instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus IP_MMM256_OPT_SelfTest(void * baseaddr_p);

#endif /** IP_MMM256_OPT_H */
