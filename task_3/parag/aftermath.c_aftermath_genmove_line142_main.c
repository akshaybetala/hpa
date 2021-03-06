#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <aftermath.c_aftermath_genmove_line142_1.h>
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

int pos;
typedef unsigned char Intersection;
Intersection  board[(19 + 2) *(19 + 1) + 1] = {0};
int  distance[20 * 20] = {0};
int k;
int  delta[8] = {0};
int d;
int other;
int closest_opponent;
int color;
int closest_own;
int something_found;

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
        memcpy(&closest_own, &closest_own_, sizeof(closest_own_));
        memcpy(&color, &color_, sizeof(color_));
        memcpy(&closest_opponent, &closest_opponent_, sizeof(closest_opponent_));
        memcpy(&other, &other_, sizeof(other_));
        memcpy(&d, &d_, sizeof(d_));

        /*----------------- read data for delta----------------------*/
        char delta_dataFileName[] = "/dataFile/aftermath.c_aftermath_genmove_line142_1.delta.dat";
        char delta_dataFileWithPath[256];
        sprintf (delta_dataFileWithPath, "%s/%s", argv[1], delta_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(delta_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/aftermath.c_aftermath_genmove_line142_1.delta.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                delta_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for delta------------------*/
        memcpy(delta, delta_, sizeof(delta_));
        int distance_dimension_sizes[1];

        /*----------------- read data for distance----------------------*/
        char distance_dataFileName[] = "/dataFile/aftermath.c_aftermath_genmove_line142_1.distance.dat";
        char distance_dataFileWithPath[256];
        sprintf (distance_dataFileWithPath, "%s/%s", argv[1], distance_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(distance_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/aftermath.c_aftermath_genmove_line142_1.distance.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                distance_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for distance------------------*/
        memcpy(distance, distance_, sizeof(distance_));

        /*----------------- read data for board----------------------*/
        char board_dataFileName[] = "/dataFile/aftermath.c_aftermath_genmove_line142_1.board.dat";
        char board_dataFileWithPath[256];
        sprintf (board_dataFileWithPath, "%s/%s", argv[1], board_dataFileName);
        unsigned char unsigned_char_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(board_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/aftermath.c_aftermath_genmove_line142_1.board.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%u", &unsigned_char_storage);
                board_[inputIndices[0]] = unsigned_char_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for board------------------*/
        memcpy(board, board_, sizeof(board_));

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

    unsigned char MD5_distance[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext_distance;
    MD5_Init (&mdContext_distance);
    for (int i0 = 0; i0 < 20 * 20; i0++)
    {
        MD5_Update(&mdContext_distance, &distance[i0], sizeof(int));
    }
    MD5_Final(MD5_distance, &mdContext_distance);
    printf("Int array MD5_distance: ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        printf("%02x", MD5_distance[i]);
    }
    printf("\n");

    printf("\n");
    printf("Scalar something_found: %d\n", something_found);
    printf("Scalar closest_own: %d\n", closest_own);
    printf("Scalar closest_opponent: %d\n", closest_opponent);
    printf("Scalar k: %d\n", k);
    printf("Scalar pos: %d\n", pos);


    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
