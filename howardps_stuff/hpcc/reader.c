#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static const niters = 5;

int main(int argc, char **argv)
{
    int i, nprocs, iters, nfac = 1;
    char buffer[4096], *line;
    long min, max;
    float result[niters], avg_sum = 0.0;
    float avg_f, sample, std;
    FILE *fd;

    if (argc < 2) {
        fprintf(stderr, "need to supply input file name\n");
        return -1;
    }

    if (argc > 2) {
        nfac = atoi(argv[2]);
    }

    fd = fopen(argv[1], "r");
    if (!fd) {
        fprintf(stderr, "unable to open file %s\n", argv[1]);
        return -1;
    }

    iters = 0;
    while (1) {
        line = fgets(buffer, sizeof(buffer), fd);
        if (!line)
            break;
        sscanf(line, "%d,%e", &nprocs, &result[iters]);
#if 0
        fprintf(stderr, "nprocs = %d, result[%d] = %e\n",nprocs, iters, result[iters]);
#endif
            avg_sum +=result[iters];
            if (iters == (niters - 1)) {
                avg_f = (float)avg_sum / (float)niters;
                for (std = 0.0, i = 0; i < niters; i++) {
                    std += ((float)result[i] - avg_f) * ((float)result[i] - avg_f);
                }
                std = sqrtf(std) / (float)(niters-1);
                avg_sum = 0;
                iters = 0;
#if 0
                fprintf(stderr, "nprocs: %d average over %d iters is %e std %e\n", nprocs, niters, avg_f, std);
#endif
                fprintf(stderr, "%d %e std %e\n", nprocs/nfac, avg_f * 1.0e+03, std * 1.0e+03);
            } else {
                iters++;
            }
    }

    return 0;
}

