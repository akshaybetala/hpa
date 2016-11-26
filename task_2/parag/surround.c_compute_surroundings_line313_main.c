#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <surround.c_compute_surroundings_line313_1.h>
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

int dpos;
int surrounded;
typedef unsigned char Intersection;
Intersection  board[(19 + 2) *(19 + 1) + 1] = {0};
char  mf[20 * 20] = {0};
int color;
char  mn[20 * 20] = {0};
int other;

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
        memcpy(&other, &other_, sizeof(other_));

        /*----------------- read data for mn----------------------*/
        char mn_dataFileName[] = "/dataFile/surround.c_compute_surroundings_line313_1.mn.dat";
        char mn_dataFileWithPath[256];
        sprintf (mn_dataFileWithPath, "%s/%s", argv[1], mn_dataFileName);
        char char_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(mn_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/surround.c_compute_surroundings_line313_1.mn.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%c", &char_storage);
                mn_[inputIndices[0]] = char_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for mn------------------*/
        memcpy(mn, mn_, sizeof(mn_));
        memcpy(&color, &color_, sizeof(color_));

        /*----------------- read data for mf----------------------*/
        char mf_dataFileName[] = "/dataFile/surround.c_compute_surroundings_line313_1.mf.dat";
        char mf_dataFileWithPath[256];
        sprintf (mf_dataFileWithPath, "%s/%s", argv[1], mf_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(mf_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/surround.c_compute_surroundings_line313_1.mf.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%c", &char_storage);
                mf_[inputIndices[0]] = char_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for mf------------------*/
        memcpy(mf, mf_, sizeof(mf_));

        /*----------------- read data for board----------------------*/
        char board_dataFileName[] = "/dataFile/surround.c_compute_surroundings_line313_1.board.dat";
        char board_dataFileWithPath[256];
        sprintf (board_dataFileWithPath, "%s/%s", argv[1], board_dataFileName);
        unsigned char unsigned_char_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(board_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/surround.c_compute_surroundings_line313_1.board.dat does not exist!");
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
        memcpy(&surrounded, &surrounded_, sizeof(surrounded_));

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
    printf("Scalar surrounded: %d\n", surrounded);
    printf("Scalar dpos: %d\n", dpos);


    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
