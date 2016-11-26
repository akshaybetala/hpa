#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <reading.c_simple_ladder_attack_line4728_1.h>
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
struct reading_moves
{
    int pos[50];
    int score[50];
    int num;
};

struct reading_moves moves;
int  libs[2] = {0};

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

        /*----------------- read data for libs----------------------*/
        char libs_dataFileName[] = "/dataFile/reading.c_simple_ladder_attack_line4728_1.libs.dat";
        char libs_dataFileWithPath[256];
        sprintf (libs_dataFileWithPath, "%s/%s", argv[1], libs_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(libs_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/reading.c_simple_ladder_attack_line4728_1.libs.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                libs_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for libs------------------*/
        memcpy(libs, libs_, sizeof(libs_));
        int moves_pos_dimension_sizes[1];

        /*----------------- read data for moves_pos----------------------*/
        char moves_pos_dataFileName[] = "/dataFile/reading.c_simple_ladder_attack_line4728_1.moves_pos.dat";
        char moves_pos_dataFileWithPath[256];
        sprintf (moves_pos_dataFileWithPath, "%s/%s", argv[1], moves_pos_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(moves_pos_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/reading.c_simple_ladder_attack_line4728_1.moves_pos.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                moves_pos_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for moves_pos------------------*/
        memcpy(moves.pos, moves_pos_, sizeof(moves_pos_));
        int moves_score_dimension_sizes[1];

        /*----------------- read data for moves_score----------------------*/
        char moves_score_dataFileName[] = "/dataFile/reading.c_simple_ladder_attack_line4728_1.moves_score.dat";
        char moves_score_dataFileWithPath[256];
        sprintf (moves_score_dataFileWithPath, "%s/%s", argv[1], moves_score_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(moves_score_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/reading.c_simple_ladder_attack_line4728_1.moves_score.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                moves_score_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for moves_score------------------*/
        memcpy(moves.score, moves_score_, sizeof(moves_score_));
        memcpy(&moves.num, &moves_num_, sizeof(moves_num_));

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
    printf("Scalar moves: \n", moves);
    printf("Scalar k: %d\n", k);


    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
