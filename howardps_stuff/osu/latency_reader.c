#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

static const niters = 5;

int main(int argc, char **argv)
{
    int i, nprocs, iters, nfac = 1, size;
    char buffer[4096], *line;
    char filename[4096];
    long min, max, avg[niters], avg_sum = 0L;
    float avg_f, sample, std, latency[30], latency_sum[30], latency_min[30], latency_max[30];
    FILE *fd;

    if (argc < 2) {
        fprintf(stderr, "need to supply input file name\n");
        return -1;
    }

    if (argc > 2) {
        nfac = atoi(argv[2]);
    }

    for (i=0;i<30;i++) {
         latency_sum[i] = 0.0;
         latency_min[i] = FLT_MAX;
         latency_max[i] = -1;
    }

    for (i = 1; i <= niters; i++) {
        snprintf(filename, sizeof(filename), "%s%d.txt", argv[1], i);
        fd = fopen(filename, "r");
        if (!fd) {
            fprintf(stderr, "unable to open file %s\n", filename);
            return -1;
        }

        fprintf(stderr, "reading from file %s\n", filename);
    iters = 0;
    while (1) {
        line = fgets(buffer, sizeof(buffer), fd);
        if (!line)
            break;

        if (!strstr(line, "#")) {
            sscanf(line, "%d %f", &size, &latency[iters]);
            latency_sum[iters] += latency[iters];
            if (latency_max[iters] < latency[iters]) latency_max[iters] = latency[iters];
            if (latency_min[iters] > latency[iters]) latency_min[iters] = latency[iters];
#if 0
            fprintf(stderr, "iters %d size = %d latency = %e\n", iters, size, latency[iters]);
#endif
#if 0
            avg_sum +=avg[iters];
            if (iters == (niters - 1)) {
                avg_f = (float)avg_sum / (float)niters;
                for (std = 0.0, i = 0; i < niters; i++) {
                    std += ((float)avg[i] - avg_f) * ((float)avg[i] - avg_f);
                }
                std = sqrtf(std) / (float)(niters-1);
                avg_sum = 0;
                iters = 0;
                fprintf(stderr, "%d %e std %e\n", nprocs/nfac, avg_f, std);
#endif
           iters++;
        }
    }

    fclose(fd);
    }

    for (i=0;i<iters;i++) {
#if 0
        fprintf(stderr, "message size %ld avg latency is %e\n", i, latency_sum[i]/(float)niters);
#endif
        fprintf(stderr, "%ld %e %e %e\n", i, latency_sum[i]/(float)niters, latency_min[i], latency_max[i]);
    }

    return 0;
}

