#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <move_reasons.c_find_connection_line145_1.h>
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

int k;
int next_connection;
int  conn_worm1[4 * 2 * 19 * 19 / 3] = {0};
int worm1;
int  conn_worm2[4 * 2 * 19 * 19 / 3] = {0};
int worm2;

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
        memcpy(&worm2, &worm2_, sizeof(worm2_));

        /*----------------- read data for conn_worm2----------------------*/
        char conn_worm2_dataFileName[] = "/dataFile/move_reasons.c_find_connection_line145_1.conn_worm2.dat";
        char conn_worm2_dataFileWithPath[256];
        sprintf (conn_worm2_dataFileWithPath, "%s/%s", argv[1], conn_worm2_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(conn_worm2_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/move_reasons.c_find_connection_line145_1.conn_worm2.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                conn_worm2_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for conn_worm2------------------*/
        memcpy(conn_worm2, conn_worm2_, sizeof(conn_worm2_));
        memcpy(&worm1, &worm1_, sizeof(worm1_));

        /*----------------- read data for conn_worm1----------------------*/
        char conn_worm1_dataFileName[] = "/dataFile/move_reasons.c_find_connection_line145_1.conn_worm1.dat";
        char conn_worm1_dataFileWithPath[256];
        sprintf (conn_worm1_dataFileWithPath, "%s/%s", argv[1], conn_worm1_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(conn_worm1_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/move_reasons.c_find_connection_line145_1.conn_worm1.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                conn_worm1_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for conn_worm1------------------*/
        memcpy(conn_worm1, conn_worm1_, sizeof(conn_worm1_));
        memcpy(&next_connection, &next_connection_, sizeof(next_connection_));

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

    printf("\n");
    printf("Scalar k: %d\n", k);


    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
