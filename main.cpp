#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include "filt.h"

int main(int argc, char *argv[])
{
    FILE *fd_in, *fd_out;
    Filter *my_filter;
    short samp_dat;
    double out_val;
    int num_read;
    char outfile1[80] = "taps.txt";
    char outfile2[80] = "freqres.txt";

    my_filter = new Filter(LPF, 51, 44.1, 2.0);
    //my_filter = new Filter(HPF, 51, 44.1, 3.0);
    //my_filter = new Filter(BPF, 51, 44.1, 3.0, 6.0);

    fprintf(stderr, "error_flag = %d\n", my_filter->get_error_flag() );
    if( my_filter->get_error_flag() < 0 ) exit(1);
    my_filter->write_taps_to_file( outfile1 );
    my_filter->write_freqres_to_file( outfile2 );

    fd_in = fopen("cut.raw", "r");
    fd_out = fopen("filtered.raw", "w");

    while(1){
        num_read = fread(&samp_dat, sizeof(short), 1, fd_in);
        if(num_read != 1) break;
        out_val = my_filter->do_sample( (double) samp_dat );
        samp_dat = (short) out_val;
        fwrite(&samp_dat, sizeof(short), 1, fd_out);
    }

    fclose(fd_in);
    fclose(fd_out);
    delete my_filter;
}