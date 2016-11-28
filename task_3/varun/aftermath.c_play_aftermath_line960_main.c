#include <aftermath.c_play_aftermath_line960_1.ptrderefout.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <aftermath.c_play_aftermath_line960_1.h>
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
struct aftermath_data
{
    int white_captured;
    int black_captured;
    int white_prisoners;
    int black_prisoners;
    int white_territory;
    int black_territory;
    int white_area;
    int black_area;
    int white_control[(19 + 1) *(19 + 1)];
    int black_control[(19 + 1) *(19 + 1)];
    int final_status[(19 + 1) *(19 + 1)];
};

struct aftermath_data* restrict a;

int main(int argc, char** argv)
{
    int inputIndices[10];
    FILE* pFile_;
    int iterations = 1;
    uint64_t *cycleArray;
    void *oldBrk;

    static char* inputDataFileName[] = {"aftermath.c_play_aftermath_line960_1.ptrderefout.hd", "aftermath.c_play_aftermath_line960_1.ptrderefout.st", "aftermath.c_play_aftermath_line960_1.ptrderefout.gl"};
    static char heapDataFile[256] = {0};
    static char stackDataFile[256] = {0};
    static char globalDataFile[256] = {0};
    static uint64_t tsc_start = 0, tsc_end, loop_cycles = 0;
    static uint64_t min_tsc_cycles = LLONG_MAX, max_tsc_cycles = 0;
    static uint64_t mean_tsc_cycles = 0, median_tsc_cycles, stdv_tsc_cycles;

    if (argc < 3)
    {
        printf("Usage: %s path_to_data_files iterations\n", argv[0]);
        exit(1);
    }

    sprintf (heapDataFile, "%s/%s", argv[1], inputDataFileName[0]);
    sprintf (stackDataFile, "%s/%s", argv[1], inputDataFileName[1]);
    sprintf (globalDataFile, "%s/%s", argv[1], inputDataFileName[2]);

    iterations = atoi(argv[2]);

    for (int it = 0; it < iterations; it++)
    {
        a = (struct aftermath_data*) a_;


        /*----------------- read data for board----------------------*/
        char board_dataFileName[] = "/dataFile/aftermath.c_play_aftermath_line960_1.board.dat";
        char board_dataFileWithPath[256];
        sprintf (board_dataFileWithPath, "%s/%s", argv[1], board_dataFileName);
        unsigned char unsigned_char_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(board_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/aftermath.c_play_aftermath_line960_1.board.dat does not exist!");
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
        a = (struct aftermath_data  *)a_;
        int a_white_control_dimension_sizes[1];

        /*----------------- read data for a_white_control----------------------*/
        char a_white_control_dataFileName[] = "/dataFile/aftermath.c_play_aftermath_line960_1.a_white_control.dat";
        char a_white_control_dataFileWithPath[256];
        sprintf (a_white_control_dataFileWithPath, "%s/%s", argv[1], a_white_control_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(a_white_control_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/aftermath.c_play_aftermath_line960_1.a_white_control.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                a_white_control_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for a_white_control------------------*/
        int a_black_control_dimension_sizes[1];

        /*----------------- read data for a_black_control----------------------*/
        char a_black_control_dataFileName[] = "/dataFile/aftermath.c_play_aftermath_line960_1.a_black_control.dat";
        char a_black_control_dataFileWithPath[256];
        sprintf (a_black_control_dataFileWithPath, "%s/%s", argv[1], a_black_control_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(a_black_control_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/aftermath.c_play_aftermath_line960_1.a_black_control.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                a_black_control_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for a_black_control------------------*/
        int a_final_status_dimension_sizes[1];

        /*----------------- read data for a_final_status----------------------*/
        char a_final_status_dataFileName[] = "/dataFile/aftermath.c_play_aftermath_line960_1.a_final_status.dat";
        char a_final_status_dataFileWithPath[256];
        sprintf (a_final_status_dataFileWithPath, "%s/%s", argv[1], a_final_status_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(a_final_status_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/aftermath.c_play_aftermath_line960_1.a_final_status.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                a_final_status_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for a_final_status------------------*/

        if (heapChunkSize > 0)
        {
            if (it < 1)
                oldBrk = mallocMemoryChunk(heapDataFile, minimumHeapAddress, maximumHeapAddress, heapChunkSize);
            else
                resetHeapData(minimumHeapAddress, maximumHeapAddress, heapChunkSize);
        }

        if (it < 1)
            cycleArray = getCycleArray(heapChunkSize, iterations);

        memcpy(&a->white_prisoners, &a_white_prisoners_, sizeof(a_white_prisoners_));
        memcpy(&a->black_prisoners, &a_black_prisoners_, sizeof(a_black_prisoners_));
        memcpy(&a->white_territory, &a_white_territory_, sizeof(a_white_territory_));
        memcpy(&a->black_territory, &a_black_territory_, sizeof(a_black_territory_));
        memcpy(&a->white_area, &a_white_area_, sizeof(a_white_area_));
        memcpy(&a->black_area, &a_black_area_, sizeof(a_black_area_));
        memcpy(a->white_control, a_white_control_, sizeof(a_white_control_));
        memcpy(a->black_control, a_black_control_, sizeof(a_black_control_));
        memcpy(a->final_status, a_final_status_, sizeof(a_final_status_));
        static long long stack_length = 0;
        register void* rsp __asm__ ("sp");
        register void *preRSP = rsp;
        void *storedTo;
        if (stackChunkSize > 0)
        {
            rsp = (void *) benStackPtrAddress;
            storedTo = saveCurrentStackToHeap(preRSP, stackBottomAddress, &stack_length);
            char* buffer = loadBenchStackToCurrentStack(stackDataFile, benStackPtrAddress, stackChunkSize);
            memcpy(rsp, buffer, stackChunkSize);
        }

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

        if (stackChunkSize > 0)
        {
            rsp = preRSP;
            if (stack_length > 0)
            {
                void *storeSpValAddr = getSavedAddress(storedTo);
                memcpy(rsp, storeSpValAddr, stack_length);
                restoreCurrentStack(storedTo, stack_length);
            }
        }

    }

    standardDeviation(cycleArray, iterations, &mean_tsc_cycles, &stdv_tsc_cycles);
    median_tsc_cycles = findMedian(cycleArray, iterations);

    if (heapChunkSize > 0)
        deleteMemoryMapping(oldBrk, maximumHeapAddress, heapChunkSize, iterations);
    else
        deleteCycleArray(cycleArray);

    printf("\n");
    printf("Scalar pos: %d\n", pos);
    printf("Scalar a: %p\n", a);
    printf("Scalar a: %p\n", a);
    printf("Scalar a: %p\n", a);
    printf("Scalar a: %p\n", a);
    printf("Scalar a: %p\n", a);
    printf("Scalar a: %p\n", a);

    void* ptrCheckSumVal = dummy(1, a);
    printf("The checksum of the addresses of pointer variables is: %p \n", ptrCheckSumVal);

    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
