#include <influence.c_value_territory_line1198_1.ptrderefout.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <influence.c_value_territory_line1198_1.h>
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
struct intrusion_data
{
    int source_pos;
    int strength_pos;
    float strength;
    float attenuation;
};

struct influence_data
{
    char safe[(19 + 1) *(19 + 1)];
    float white_influence[(19 + 1) *(19 + 1)];
    float black_influence[(19 + 1) *(19 + 1)];
    float white_strength[(19 + 1) *(19 + 1)];
    float black_strength[(19 + 1) *(19 + 1)];
    float white_attenuation[(19 + 1) *(19 + 1)];
    float black_attenuation[(19 + 1) *(19 + 1)];
    float white_permeability[(19 + 1) *(19 + 1)];
    float black_permeability[(19 + 1) *(19 + 1)];
    int territory_segmentation[(19 + 1) *(19 + 1)];
    int moyo_segmentation[(19 + 1) *(19 + 1)];
    int area_segmentation[(19 + 1) *(19 + 1)];
    int region_type[3 * 19 * 19 + 1];
    int region_size[3 * 19 * 19 + 1];
    float region_territorial_value[3 * 19 * 19 + 1];
    int number_of_regions;
    int is_territorial_influence;
    float territory_value[(19 + 1) *(19 + 1)];
    int non_territory[(19 + 1) *(19 + 1)];
    int captured;
    int color_to_move;
    int queue[19 * 19];
    int intrusion_counter;
    struct intrusion_data intrusions[2 * 19 * 19];
};

struct influence_data* restrict q;
int k;
int  delta[8] = {0};
float  first_guess[20 * 20] = {0};

int main(int argc, char** argv)
{
    int inputIndices[10];
    FILE* pFile_;
    int iterations = 1;
    uint64_t *cycleArray;
    void *oldBrk;

    static char* inputDataFileName[] = {"influence.c_value_territory_line1198_1.ptrderefout.hd", "influence.c_value_territory_line1198_1.ptrderefout.st", "influence.c_value_territory_line1198_1.ptrderefout.gl"};
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
        q = (struct influence_data*) q_;


        /*----------------- read data for first_guess----------------------*/
        char first_guess_dataFileName[] = "/dataFile/influence.c_value_territory_line1198_1.first_guess.dat";
        char first_guess_dataFileWithPath[256];
        sprintf (first_guess_dataFileWithPath, "%s/%s", argv[1], first_guess_dataFileName);
        float float_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(first_guess_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_value_territory_line1198_1.first_guess.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%f", &float_storage);
                first_guess_[inputIndices[0]] = float_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for first_guess------------------*/
        memcpy(first_guess, first_guess_, sizeof(first_guess_));

        /*----------------- read data for delta----------------------*/
        char delta_dataFileName[] = "/dataFile/influence.c_value_territory_line1198_1.delta.dat";
        char delta_dataFileWithPath[256];
        sprintf (delta_dataFileWithPath, "%s/%s", argv[1], delta_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(delta_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_value_territory_line1198_1.delta.dat does not exist!");
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

        /*----------------- read data for board----------------------*/
        char board_dataFileName[] = "/dataFile/influence.c_value_territory_line1198_1.board.dat";
        char board_dataFileWithPath[256];
        sprintf (board_dataFileWithPath, "%s/%s", argv[1], board_dataFileName);
        unsigned char unsigned_char_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(board_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_value_territory_line1198_1.board.dat does not exist!");
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
        q = (struct influence_data  *)q_;
        int q_safe_dimension_sizes[1];

        /*----------------- read data for q_safe----------------------*/
        char q_safe_dataFileName[] = "/dataFile/influence.c_value_territory_line1198_1.q_safe.dat";
        char q_safe_dataFileWithPath[256];
        sprintf (q_safe_dataFileWithPath, "%s/%s", argv[1], q_safe_dataFileName);
        char char_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(q_safe_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_value_territory_line1198_1.q_safe.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%c", &char_storage);
                q_safe_[inputIndices[0]] = char_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for q_safe------------------*/
        int q_white_permeability_dimension_sizes[1];

        /*----------------- read data for q_white_permeability----------------------*/
        char q_white_permeability_dataFileName[] = "/dataFile/influence.c_value_territory_line1198_1.q_white_permeability.dat";
        char q_white_permeability_dataFileWithPath[256];
        sprintf (q_white_permeability_dataFileWithPath, "%s/%s", argv[1], q_white_permeability_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(q_white_permeability_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_value_territory_line1198_1.q_white_permeability.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%f", &float_storage);
                q_white_permeability_[inputIndices[0]] = float_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for q_white_permeability------------------*/
        int q_black_permeability_dimension_sizes[1];

        /*----------------- read data for q_black_permeability----------------------*/
        char q_black_permeability_dataFileName[] = "/dataFile/influence.c_value_territory_line1198_1.q_black_permeability.dat";
        char q_black_permeability_dataFileWithPath[256];
        sprintf (q_black_permeability_dataFileWithPath, "%s/%s", argv[1], q_black_permeability_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(q_black_permeability_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_value_territory_line1198_1.q_black_permeability.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%f", &float_storage);
                q_black_permeability_[inputIndices[0]] = float_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for q_black_permeability------------------*/
        int q_territory_value_dimension_sizes[1];

        /*----------------- read data for q_territory_value----------------------*/
        char q_territory_value_dataFileName[] = "/dataFile/influence.c_value_territory_line1198_1.q_territory_value.dat";
        char q_territory_value_dataFileWithPath[256];
        sprintf (q_territory_value_dataFileWithPath, "%s/%s", argv[1], q_territory_value_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(q_territory_value_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_value_territory_line1198_1.q_territory_value.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%f", &float_storage);
                q_territory_value_[inputIndices[0]] = float_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for q_territory_value------------------*/

        if (heapChunkSize > 0)
        {
            if (it < 1)
                oldBrk = mallocMemoryChunk(heapDataFile, minimumHeapAddress, maximumHeapAddress, heapChunkSize);
            else
                resetHeapData(minimumHeapAddress, maximumHeapAddress, heapChunkSize);
        }

        if (it < 1)
            cycleArray = getCycleArray(heapChunkSize, iterations);

        memcpy(q->safe, q_safe_, sizeof(q_safe_));
        memcpy(q->white_permeability, q_white_permeability_, sizeof(q_white_permeability_));
        memcpy(q->black_permeability, q_black_permeability_, sizeof(q_black_permeability_));
        memcpy(q->territory_value, q_territory_value_, sizeof(q_territory_value_));
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
    printf("Scalar k: %d\n", k);
    printf("Scalar ii: %d\n", ii);

    void* ptrCheckSumVal = dummy(1, q);
    printf("The checksum of the addresses of pointer variables is: %p \n", ptrCheckSumVal);

    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}