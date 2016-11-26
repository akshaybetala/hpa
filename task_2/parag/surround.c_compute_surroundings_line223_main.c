#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <surround.c_compute_surroundings_line223_1.h>
#include <common.h>
#include <timer.h>

extern void* getCycleArray(unsigned long long heapSize, int iterations);
extern void* deleteCycleArray(void *cycleArray);
extern uint64_t findMedian(uint64_t *cycleArray, int size);
extern void standardDeviation(uint64_t *cycleArray, int size, uint64_t *mean, uint64_t *stdv);
extern void* mallocMemoryChunk(char* fileName, void* startAddr, void* endAddr, unsigned  long long size);
extern void resetHeapData(void* startAddr, void* endAddr, unsigned  long long size);
extern void deleteMemoryMapping(void* oldBrk, void *addr, unsigned long long length, int iterations);
extern void* saveCurrentStackToHeap(void* curSP, void* preBottom, long long*);
extern void* loadBenchStackToCurrentStack(char *stackDataFile, void* benchStackPtr, unsigned long long size);
extern void* getSavedAddress(void *heapAddr);
extern void restoreCurrentStack(void* heapAddr, unsigned long long size);

extern void loop();
extern void* dummy(int num, ...);

int n;
int  left_corner[19] = {0};
int left_corners;
int  right_corner[19] = {0};
int right_corners;
char  mn[20 * 20] = {0};
int bottom_row;

int main(int argc, char** argv)
{
    int inputIndices[10];
    FILE* pFile_;
    int iterations = 1;
    uint64_t *cycleArray;
    void *oldBrk;

    static uint64_t tsc_start = 0, tsc_end, loop_cycles = 0;
    static uint64_t min_tsc_cycles = LLONG_MAX, max_tsc_cycles = 0;
    static uint64_t mean_tsc_cycles = 0, median_tsc_cycles, stdv_tsc_cycles;

    if (argc < 3)
    {
        printf("Usage: %s path_to_data_files iterations\n", argv[0]);
        exit(1);
    }

    iterations = atoi(argv[2]);

    for (int it = 0; it < iterations; it++)
    {
        memcpy(&bottom_row, &bottom_row_, sizeof(bottom_row_));
        int mn_dimension_sizes[1];
        memcpy(&right_corners, &right_corners_, sizeof(right_corners_));

        /*----------------- read data for right_corner----------------------*/
        char right_corner_dataFileName[] = "/dataFile/surround.c_compute_surroundings_line223_1.right_corner.dat";
        char right_corner_dataFileWithPath[256];
        sprintf (right_corner_dataFileWithPath, "%s/%s", argv[1], right_corner_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(right_corner_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/surround.c_compute_surroundings_line223_1.right_corner.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                right_corner_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for right_corner------------------*/
        memcpy(right_corner, right_corner_, sizeof(right_corner_));
        memcpy(&left_corners, &left_corners_, sizeof(left_corners_));

        /*----------------- read data for left_corner----------------------*/
        char left_corner_dataFileName[] = "/dataFile/surround.c_compute_surroundings_line223_1.left_corner.dat";
        char left_corner_dataFileWithPath[256];
        sprintf (left_corner_dataFileWithPath, "%s/%s", argv[1], left_corner_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(left_corner_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/surround.c_compute_surroundings_line223_1.left_corner.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                left_corner_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for left_corner------------------*/
        memcpy(left_corner, left_corner_, sizeof(left_corner_));

        if (it < 1)
            cycleArray = getCycleArray(0, iterations);

        tsc_start = rdtsc();

#if defined(ITERATIONS)
        for (int it = 0; it < ITERATIONS; it++)
        {
#endif
            loop();
#if defined(ITERATIONS)
        }
#endif
        tsc_end = rdtsc();

        loop_cycles = tsc_end - tsc_start;
        cycleArray[it] = loop_cycles;

        if (loop_cycles < min_tsc_cycles)
            min_tsc_cycles = loop_cycles;

        if (loop_cycles > max_tsc_cycles)
            max_tsc_cycles = loop_cycles;

    }

    standardDeviation(cycleArray, iterations, &mean_tsc_cycles, &stdv_tsc_cycles);
    median_tsc_cycles = findMedian(cycleArray, iterations);

    deleteCycleArray(cycleArray);

    unsigned char MD5_mn[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext_mn;
    MD5_Init (&mdContext_mn);
    for (int i0 = 0; i0 < 20 * 20; i0++)
    {
        MD5_Update(&mdContext_mn, &mn[i0], sizeof(char));
    }
    MD5_Final(MD5_mn, &mdContext_mn);
    printf("Int array MD5_mn: ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        printf("%02x", MD5_mn[i]);
    }
    printf("\n");

    printf("\n");
    printf("Scalar n: %d\n", n);


    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
