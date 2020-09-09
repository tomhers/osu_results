#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

static const niters = 5;

int main(int argc, char **argv)
{
    int i, nprocs, iters, nfac = 1, size, set;
    char buffer[4096], *line;
    char filename[4096];
    long min, max, avg[niters], avg_sum = 0L;
    float avg_f, sample, std, msg_rate[2][30], msg_rate_sum[2][30], msg_rate_min[2][30], msg_rate_max[2][30], foo;
    float set1_msg_rate, set2_msg_rate;
    FILE *fd;

    if (argc < 3) {
        fprintf(stderr, "need to supply input file names \n");
        return -1;
    }

    if (argc > 2) {
        nfac = atoi(argv[2]);
    }

    for(set=0;set<2;set++) {
    for (i=0;i<30;i++) {
         msg_rate_sum[set][i] = 0.0;
         msg_rate_min[set][i] = FLT_MAX;
         msg_rate_max[set][i] = -1;
    }
    }

    for(set = 0; set < 2; set++) {

    for (i = 1; i <= niters; i++) {
        snprintf(filename, sizeof(filename), "%s%d.txt", argv[1+set], i);
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
            sscanf(line, "%d %f %f", &size, &foo, &msg_rate[set][iters]);
            msg_rate_sum[set][iters] += msg_rate[set][iters];
            if (msg_rate_max[set][iters] < msg_rate[set][iters]) msg_rate_max[set][iters] = msg_rate[set][iters];
            if (msg_rate_min[set][iters] > msg_rate[set][iters]) msg_rate_min[set][iters] = msg_rate[set][iters];
            iters++;
        }
    }

    fclose(fd);
    }
    }

    for (set=0;set<2;set++) {
    for (i=0;i<iters;i++) {
#if 0
        fprintf(stderr, "message size %ld avg msg_rate is %e\n", i, msg_rate_sum[i]/(float)niters);
#endif
        fprintf(stderr, "%ld %e %e %e\n", i, msg_rate_sum[set][i]/(float)niters, msg_rate_min[set][i], msg_rate_max[set][i]);
    }
    }

    fprintf(stderr, "normalized to first set results:\n");
    for (i=0;i<iters;i++) {
        set1_msg_rate = msg_rate_sum[0][i]/(float)niters;
        set2_msg_rate = msg_rate_sum[1][i]/(float)niters;
        fprintf(stderr, "%e\n", set2_msg_rate / set1_msg_rate);
    }
    return 0;
}

