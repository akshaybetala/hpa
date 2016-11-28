#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <readconnect.c_find_connection_moves_line716_1.h>
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

int i;
int num_moves;
int  distances[362] = {0};
int j;
int  moves[362] = {0};

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
        int moves_dimension_sizes[1];

        /*----------------- read data for moves----------------------*/
        char moves_dataFileName[] = "/dataFile/readconnect.c_find_connection_moves_line716_1.moves.dat";
        char moves_dataFileWithPath[256];
        sprintf (moves_dataFileWithPath, "%s/%s", argv[1], moves_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(moves_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/readconnect.c_find_connection_moves_line716_1.moves.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                moves_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for moves------------------*/
        memcpy(moves, moves_, sizeof(moves_));
        int distances_dimension_sizes[1];

        /*----------------- read data for distances----------------------*/
        char distances_dataFileName[] = "/dataFile/readconnect.c_find_connection_moves_line716_1.distances.dat";
        char distances_dataFileWithPath[256];
        sprintf (distances_dataFileWithPath, "%s/%s", argv[1], distances_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(distances_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/readconnect.c_find_connection_moves_line716_1.distances.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                distances_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for distances------------------*/
        memcpy(distances, distances_, sizeof(distances_));
        memcpy(&num_moves, &num_moves_, sizeof(num_moves_));

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

    unsigned char MD5_moves[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext_moves;
    MD5_Init (&mdContext_moves);
    for (int i0 = 0; i0 < 362; i0++)
    {
        MD5_Update(&mdContext_moves, &moves[i0], sizeof(int));
    }
    MD5_Final(MD5_moves, &mdContext_moves);
    printf("Int array MD5_moves: ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        printf("%02x", MD5_moves[i]);
    }
    printf("\n");

    unsigned char MD5_distances[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext_distances;
    MD5_Init (&mdContext_distances);
    for (int i0 = 0; i0 < 362; i0++)
    {
        MD5_Update(&mdContext_distances, &distances[i0], sizeof(int));
    }
    MD5_Final(MD5_distances, &mdContext_distances);
    printf("Int array MD5_distances: ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        printf("%02x", MD5_distances[i]);
    }
    printf("\n");

    printf("\n");
    printf("Scalar j: %d\n", j);
    printf("Scalar i: %d\n", i);


    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
