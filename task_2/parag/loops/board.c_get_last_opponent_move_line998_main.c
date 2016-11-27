#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <board.c_get_last_opponent_move_line998_1.h>
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
int move_history_pointer;
int  move_history_color[500] = {0};
int color;
int  move_history_pos[500] = {0};

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

        /*----------------- read data for move_history_pos----------------------*/
        char move_history_pos_dataFileName[] = "/dataFile/board.c_get_last_opponent_move_line998_1.move_history_pos.dat";
        char move_history_pos_dataFileWithPath[256];
        sprintf (move_history_pos_dataFileWithPath, "%s/%s", argv[1], move_history_pos_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(move_history_pos_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/board.c_get_last_opponent_move_line998_1.move_history_pos.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                move_history_pos_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for move_history_pos------------------*/
        memcpy(move_history_pos, move_history_pos_, sizeof(move_history_pos_));
        memcpy(&color, &color_, sizeof(color_));

        /*----------------- read data for move_history_color----------------------*/
        char move_history_color_dataFileName[] = "/dataFile/board.c_get_last_opponent_move_line998_1.move_history_color.dat";
        char move_history_color_dataFileWithPath[256];
        sprintf (move_history_color_dataFileWithPath, "%s/%s", argv[1], move_history_color_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(move_history_color_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/board.c_get_last_opponent_move_line998_1.move_history_color.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                move_history_color_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for move_history_color------------------*/
        memcpy(move_history_color, move_history_color_, sizeof(move_history_color_));
        memcpy(&move_history_pointer, &move_history_pointer_, sizeof(move_history_pointer_));

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
