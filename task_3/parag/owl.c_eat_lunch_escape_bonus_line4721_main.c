#include <owl.c_eat_lunch_escape_bonus_line4721_1.ptrderefout.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <owl.c_eat_lunch_escape_bonus_line4721_1.h>
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
int neighbors;
int adjoins;
struct eyevalue
{
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char d;
};

struct eye_data
{
    int color;
    int esize;
    int msize;
    int origin;
    struct eyevalue value;
    int attack_point;
    int defense_point;
    char marginal;
    char type;
    char neighbors;
    char marginal_neighbors;
    char cut;
};

struct half_eye_data
{
    float value;
    char type;
    int num_attacks;
    int attack_point[4];
    int num_defends;
    int defense_point[4];
};

struct local_owl_data
{
    char goal[(19 + 1) *(19 + 1)];
    char boundary[(19 + 1) *(19 + 1)];
    char escape_values[(19 + 1) *(19 + 1)];
    int color;
    struct eye_data my_eye[(19 + 1) *(19 + 1)];
    struct half_eye_data half_eye[(19 + 1) *(19 + 1)];
    int lunch[10];
    int lunch_attack_code[10];
    int lunch_attack_point[10];
    int lunch_defend_code[10];
    int lunch_defense_point[10];
    char inessential[(19 + 1) *(19 + 1)];
    int lunches_are_current;
    char safe_move_cache[(19 + 1) *(19 + 1)];
    int restore_from;
    int number_in_stack;
};

struct local_owl_data* restrict owl;
int  adjacent[160] = {0};

int main(int argc, char** argv)
{
    int inputIndices[10];
    FILE* pFile_;
    int iterations = 1;
    uint64_t *cycleArray;
    void *oldBrk;

    static char* inputDataFileName[] = {"owl.c_eat_lunch_escape_bonus_line4721_1.ptrderefout.hd", "owl.c_eat_lunch_escape_bonus_line4721_1.ptrderefout.st", "owl.c_eat_lunch_escape_bonus_line4721_1.ptrderefout.gl"};
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
        owl = (struct local_owl_data*) owl_;


        /*----------------- read data for adjacent----------------------*/
        char adjacent_dataFileName[] = "/dataFile/owl.c_eat_lunch_escape_bonus_line4721_1.adjacent.dat";
        char adjacent_dataFileWithPath[256];
        sprintf (adjacent_dataFileWithPath, "%s/%s", argv[1], adjacent_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(adjacent_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/owl.c_eat_lunch_escape_bonus_line4721_1.adjacent.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                adjacent_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for adjacent------------------*/
        memcpy(adjacent, adjacent_, sizeof(adjacent_));
        memcpy(&adjoins, &adjoins_, sizeof(adjoins_));
        memcpy(&neighbors, &neighbors_, sizeof(neighbors_));
        owl = (struct local_owl_data  *)owl_;

        /*----------------- read data for owl_goal----------------------*/
        char owl_goal_dataFileName[] = "/dataFile/owl.c_eat_lunch_escape_bonus_line4721_1.owl_goal.dat";
        char owl_goal_dataFileWithPath[256];
        sprintf (owl_goal_dataFileWithPath, "%s/%s", argv[1], owl_goal_dataFileName);
        char char_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(owl_goal_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/owl.c_eat_lunch_escape_bonus_line4721_1.owl_goal.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%c", &char_storage);
                owl_goal_[inputIndices[0]] = char_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for owl_goal------------------*/

        if (heapChunkSize > 0)
        {
            if (it < 1)
                oldBrk = mallocMemoryChunk(heapDataFile, minimumHeapAddress, maximumHeapAddress, heapChunkSize);
            else
                resetHeapData(minimumHeapAddress, maximumHeapAddress, heapChunkSize);
        }

        if (it < 1)
            cycleArray = getCycleArray(heapChunkSize, iterations);

        memcpy(owl->goal, owl_goal_, sizeof(owl_goal_));
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
    printf("Scalar adjoins: %d\n", adjoins);
    printf("Scalar n: %d\n", n);

    void* ptrCheckSumVal = dummy(1, owl);
    printf("The checksum of the addresses of pointer variables is: %p \n", ptrCheckSumVal);

    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
