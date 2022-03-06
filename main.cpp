#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdint>

/* Block Size per Audio Channel */
#define NUM_SAMPLES (128)

/* Number of stereo channels */
#define NUM_RX_SLOTS 2
#define NUM_TX_SLOTS 2

/* Size of each channel */
#define RX_BLOCK_SIZE (NUM_SAMPLES * NUM_RX_SLOTS)
#define TX_BLOCK_SIZE (NUM_SAMPLES * NUM_TX_SLOTS)

#define PCI  0x00080000
#define OFFSET 0x00080000


/* SPORT RX DMA destination buffers */
int RxBlock_A0[RX_BLOCK_SIZE];
int RxBlock_A1[sizeof(RxBlock_A0)];

/* SPORT Tx DMA source buffers */
int TxBlock_A0[TX_BLOCK_SIZE];
int TxBlock_A1[sizeof(TxBlock_A0)];

/* SPORT RX DMA destination buffers */
int RxBlock_B0[RX_BLOCK_SIZE];
int RxBlock_B1[sizeof(RxBlock_B0)];

/* SPORT Tx DMA source buffers */
int TxBlock_B0[TX_BLOCK_SIZE];
int TxBlock_B1[sizeof(TxBlock_B0)];

/* Set up the TCBs to rotate automatically */
unsigned int TCB_RxBlock_A0[4] = { NULL, sizeof(RxBlock_A0), 1, NULL};
unsigned int TCB_RxBlock_A1[4] = { NULL, sizeof(RxBlock_A0), 1, NULL};

unsigned int TCB_TxBlock_A0[4] = { NULL, sizeof(TxBlock_A0), 1, NULL};
unsigned int TCB_TxBlock_A1[4] = { NULL, sizeof(TxBlock_A0), 1, NULL};

unsigned int TCB_RxBlock_B0[4] = { NULL, sizeof(RxBlock_B0), 1, NULL};
unsigned int TCB_RxBlock_B1[4] = { NULL, sizeof(RxBlock_B0), 1, NULL};

unsigned int TCB_TxBlock_B0[4] = { NULL, sizeof(TxBlock_B0), 1, NULL};
unsigned int TCB_TxBlock_B1[4] = { NULL, sizeof(TxBlock_B0), 1, NULL};

int main()
{
    std::cout << "Hello, World!" << std::endl;
    /* Set up "ping-pong" chained DMAs for CS4272 */

    /* Proceed from Block A0 to Block A1 */
    /* Extract 19-bits of the receive buffer A1 address with setting PCI bit */
    TCB_RxBlock_A0[0] = (uintptr_t) TCB_RxBlock_A1 + 3 - OFFSET + PCI ;
    TCB_RxBlock_A0[3] = (uintptr_t) RxBlock_A0 - OFFSET ;

    printf("%d\n", TCB_RxBlock_A0[0]);
    printf("%d\n", TCB_RxBlock_A0[1]);
    printf("%d\n", TCB_RxBlock_A0[2]);
    printf("%d\n", TCB_RxBlock_A0[3]);

    std::cout << "Hello World" << std::endl;

//    /* Proceed from Block A1 to Block A0 */
//    /* Extract 19-bits of the receive buffer A0 address with setting PCI bit */
//    TCB_RxBlock_A1[0] = (unsigned int)(size_t) TCB_RxBlock_A0 + 3 - OFFSET + PCI ;
//    TCB_RxBlock_A1[3] = (int)(size_t) RxBlock_A1 - OFFSET ;
//
//    /* Proceed from Block A0 to Block A1*/
//    /* Extract 19-bits of the transmit buffer A1 address */
//    TCB_TxBlock_A0[0] = (unsigned int)(size_t) TCB_TxBlock_A1 + 3 - OFFSET ;
//    TCB_TxBlock_A0[3] = (int)(size_t) TxBlock_A0 - OFFSET ;
//
//    /* Proceed from Block A1 to Block A0 */
//    /* Extract 19-bits of the transmit buffer A0 address */
//    TCB_TxBlock_A1[0] = (unsigned int)(size_t) TCB_TxBlock_A0 + 3 - OFFSET ;
//    TCB_TxBlock_A1[3] = (int)(size_t) TxBlock_A1 - OFFSET ;
//
//    /* Proceed from Block B0 to Block B1 */
//    /* Extract 19-bits of the receive buffer B1 address with setting PCI bit */
//    TCB_RxBlock_B0[0] = (unsigned int)(size_t) TCB_RxBlock_B1 + 3 - OFFSET + PCI ;
//    TCB_RxBlock_B0[3] = (int)(size_t) RxBlock_B0 - OFFSET ;
//
//    /* Proceed from Block B1 to Block B0 */
//    /* Extract 19-bits of the receive buffer B0 address with setting PCI bit */
//    TCB_RxBlock_B1[0] = (unsigned int)(size_t) TCB_RxBlock_B0 + 3 - OFFSET + PCI ;
//    TCB_RxBlock_B1[3] = (int)(size_t) RxBlock_B1 - OFFSET ;
//
//    /* Proceed from Block B0 to Block B1 */
//    /* Extract 19-bits of the transmit buffer B1 address */
//    TCB_TxBlock_B0[0] = (unsigned int)(size_t) TCB_TxBlock_B1 + 3 - OFFSET ;
//    TCB_TxBlock_B0[3] = (int)(size_t) TxBlock_B0 - OFFSET ;
//
//    /* Proceed from Block B1 to Block B0 */
//    /* Extract 19-bits of the transmit buffer B0 address */
//    TCB_TxBlock_B1[0] = (unsigned int)(size_t) TCB_TxBlock_B0 + 3 - OFFSET ;
//    TCB_TxBlock_B1[3] = (int)(size_t) TxBlock_B1 - OFFSET ;
}


//#include "filt.h"

//int main(int argc, char *argv[])
//{
//    FILE *fd_in, *fd_out;
//    Filter *my_filter;
//    short samp_dat;
//    double out_val;
//    int num_read;
//    char outfile1[80] = "taps.txt";
//    char outfile2[80] = "freqres.txt";
//
//    my_filter = new Filter(LPF, 51, 44.1, 2.0);
//    //my_filter = new Filter(HPF, 51, 44.1, 3.0);
//    //my_filter = new Filter(BPF, 51, 44.1, 3.0, 6.0);
//
//    fprintf(stderr, "error_flag = %d\n", my_filter->get_error_flag() );
//    if( my_filter->get_error_flag() < 0 ) exit(1);
//    my_filter->write_taps_to_file( outfile1 );
//    my_filter->write_freqres_to_file( outfile2 );
//
//    fd_in = fopen("cut.raw", "r");
//    fd_out = fopen("filtered.raw", "w");
//
//    while(1){
//        num_read = fread(&samp_dat, sizeof(short), 1, fd_in);
//        if(num_read != 1) break;
//        out_val = my_filter->do_sample( (double) samp_dat );
//        samp_dat = (short) out_val;
//        fwrite(&samp_dat, sizeof(short), 1, fd_out);
//    }
//
//    fclose(fd_in);
//    fclose(fd_out);
//    delete my_filter;
//}