#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <score.c_close_bubbles_line231_1.h>
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

int ii;
typedef unsigned char Intersection;
Intersection  board[(19 + 2) *(19 + 1) + 1] = {0};
int  gb[(19 + 1) *(19 + 1)] = {0};
int  bubbles[20 * 20] = {0};

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

        /*----------------- read data for bubbles----------------------*/
        char bubbles_dataFileName[] = "/dataFile/score.c_close_bubbles_line231_1.bubbles.dat";
        char bubbles_dataFileWithPath[256];
        sprintf (bubbles_dataFileWithPath, "%s/%s", argv[1], bubbles_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(bubbles_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/score.c_close_bubbles_line231_1.bubbles.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                bubbles_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for bubbles------------------*/
        memcpy(bubbles, bubbles_, sizeof(bubbles_));
        int gb_dimension_sizes[1];

        /*----------------- read data for gb----------------------*/
        char gb_dataFileName[] = "/dataFile/score.c_close_bubbles_line231_1.gb.dat";
        char gb_dataFileWithPath[256];
        sprintf (gb_dataFileWithPath, "%s/%s", argv[1], gb_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(gb_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/score.c_close_bubbles_line231_1.gb.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                gb_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for gb------------------*/
        memcpy(gb, gb_, sizeof(gb_));

        /*----------------- read data for board----------------------*/
        char board_dataFileName[] = "/dataFile/score.c_close_bubbles_line231_1.board.dat";
        char board_dataFileWithPath[256];
        sprintf (board_dataFileWithPath, "%s/%s", argv[1], board_dataFileName);
        unsigned char unsigned_char_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(board_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/score.c_close_bubbles_line231_1.board.dat does not exist!");
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

    unsigned char MD5_gb[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext_gb;
    MD5_Init (&mdContext_gb);
    for (int i0 = 0; i0 < (19 + 1) *(19 + 1); i0++)
    {
        MD5_Update(&mdContext_gb, &gb[i0], sizeof(int));
    }
    MD5_Final(MD5_gb, &mdContext_gb);
    printf("Int array MD5_gb: ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        printf("%02x", MD5_gb[i]);
    }
    printf("\n");

    printf("\n");
    printf("Scalar ii: %d\n", ii);


    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
