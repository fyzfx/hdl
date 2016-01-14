//----------------------------------------------------------------------------
//      _____
//     *     *
//    *____   *____
//   * *===*   *==*
//  *___*===*___**  AVNET
//       *======*
//        *====*
//----------------------------------------------------------------------------
//
// This design is the property of Avnet.  Publication of this
// design is not authorized without written consent from Avnet.
//
// Please direct any questions to the PicoZed community support forum:
//    http://www.picozed.org/forum
//
// Product information is available at:
//    http://www.picozed.org/product/picozed
//
// Disclaimer:
//    Avnet, Inc. makes no warranty for the use of this code or design.
//    This code is provided  "As Is". Avnet, Inc assumes no responsibility for
//    any errors, which may appear in this code, nor does it make a commitment
//    to update the information contained herein. Avnet, Inc specifically
//    disclaims any implied warranties of fitness for a particular purpose.
//                     Copyright(c) 2015 Avnet, Inc.
//                             All rights reserved.
//
//----------------------------------------------------------------------------
//
// Create Date:         Nov 30, 2015
// Design Name:         PicoZed IIC HDMI Demonstration
// Module Name:         main.c
// Project Name:        PicoZed + FMC2 Carrier
// Target Devices:      Xilinx Zynq-7000
// Hardware Boards:     PicoZed + FMC2 Carrier
//
// Tool versions:       Xilinx Vivado 2015.2
//
// Description:         PicoZed IIC HDMI Demonstration
//
// Dependencies:
//
// Revision:            Nov 30, 2015: 1.00 Initial version
//
//----------------------------------------------------------------------------

#include <stdio.h>
#include "platform.h"
#include "hdmi_demo.h"

// This is the top level demo instance.
iic_hdmi_demo_t demo;

int run_hdmi_test()
{
	int ret;
	int pass_fail = 0;

	xil_printf("\n\r");

	xil_printf("---------------------------------------------------------------------------\n\r");
	xil_printf("--                                                                       --\n\r");
	xil_printf("--                      PZCC-FMC2 HDMI Test Application                  --\n\r");
	xil_printf("--                                                                       --\n\r");
	xil_printf("---------------------------------------------------------------------------\n\r");
	xil_printf("\n\r");
    /* Assign the address for the IIC controller which comes from the address
     * map for hardware peripherals on this platform.
     */
    demo.uBaseAddr_IIC_HDMI        = XPAR_AXI_IIC_0_BASEADDR;

    // Initialize hardware design and prepare devices for normal operation.
    ret = hdmi_demo_init(&demo);
    if (ret != 0){
    	 xil_printf("hdmi_demo_init failed! Test ABORT!\n\r");
    	 pass_fail = -1;
    }

    ret = validate_hdmi(&demo);
    if (ret != 0){
    	 xil_printf("validate_hdmi failed! Test ABORT!\n\r");
    	 pass_fail = -1;
    }

    /* Determine overall test result and print results to test operator.
     */
    xil_printf("\r\n");
    xil_printf("HDMI Test: ");

    if (pass_fail == 0)
    {
        xil_printf("\033[32mPASSED\033[0m\r\n");
        return 0;
    }
    else
    {
        xil_printf("\033[5mFAILED\033[0m\r\n");
        return -1;
    }

    return 0;
}

int main()
{
    init_platform();

    run_hdmi_test();

    cleanup_platform();

    return 0;
}
