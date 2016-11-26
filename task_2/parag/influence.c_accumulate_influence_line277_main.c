#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <influence.c_accumulate_influence_line277_1.h>
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

int d;
typedef unsigned char Intersection;
Intersection  board[(19 + 2) *(19 + 1) + 1] = {0};
int ii;
int  delta[8] = {0};
char  safe[(19 + 1) *(19 + 1)] = {0};
int  deltai[8] = {0};
int delta_i;
int  deltaj[8] = {0};
int delta_j;
int queue_start;
int  permeability_array[(19 + 1) *(19 + 1)] = {0};
int current_strength;
int b;
int  working[20 * 20] = {0};
int  queue[20 * 20] = {0};
int queue_end;

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
        memcpy(&queue_end, &queue_end_, sizeof(queue_end_));
        int queue_dimension_sizes[1];
        int working_dimension_sizes[1];

        /*----------------- read data for working----------------------*/
        char working_dataFileName[] = "/dataFile/influence.c_accumulate_influence_line277_1.working.dat";
        char working_dataFileWithPath[256];
        sprintf (working_dataFileWithPath, "%s/%s", argv[1], working_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(working_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_accumulate_influence_line277_1.working.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                working_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for working------------------*/
        memcpy(working, working_, sizeof(working_));
        memcpy(&b, &b_, sizeof(b_));
        memcpy(&current_strength, &current_strength_, sizeof(current_strength_));

        /*----------------- read data for permeability_array----------------------*/
        char permeability_array_dataFileName[] = "/dataFile/influence.c_accumulate_influence_line277_1.permeability_array.dat";
        char permeability_array_dataFileWithPath[256];
        sprintf (permeability_array_dataFileWithPath, "%s/%s", argv[1], permeability_array_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(permeability_array_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_accumulate_influence_line277_1.permeability_array.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                permeability_array_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for permeability_array------------------*/
        memcpy(permeability_array, permeability_array_, sizeof(permeability_array_));
        memcpy(&queue_start, &queue_start_, sizeof(queue_start_));
        memcpy(&delta_j, &delta_j_, sizeof(delta_j_));

        /*----------------- read data for deltaj----------------------*/
        char deltaj_dataFileName[] = "/dataFile/influence.c_accumulate_influence_line277_1.deltaj.dat";
        char deltaj_dataFileWithPath[256];
        sprintf (deltaj_dataFileWithPath, "%s/%s", argv[1], deltaj_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(deltaj_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_accumulate_influence_line277_1.deltaj.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                deltaj_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for deltaj------------------*/
        memcpy(deltaj, deltaj_, sizeof(deltaj_));
        memcpy(&delta_i, &delta_i_, sizeof(delta_i_));

        /*----------------- read data for deltai----------------------*/
        char deltai_dataFileName[] = "/dataFile/influence.c_accumulate_influence_line277_1.deltai.dat";
        char deltai_dataFileWithPath[256];
        sprintf (deltai_dataFileWithPath, "%s/%s", argv[1], deltai_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(deltai_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_accumulate_influence_line277_1.deltai.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                deltai_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for deltai------------------*/
        memcpy(deltai, deltai_, sizeof(deltai_));

        /*----------------- read data for safe----------------------*/
        char safe_dataFileName[] = "/dataFile/influence.c_accumulate_influence_line277_1.safe.dat";
        char safe_dataFileWithPath[256];
        sprintf (safe_dataFileWithPath, "%s/%s", argv[1], safe_dataFileName);
        char char_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(safe_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_accumulate_influence_line277_1.safe.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%c", &char_storage);
                safe_[inputIndices[0]] = char_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for safe------------------*/
        memcpy(safe, safe_, sizeof(safe_));

        /*----------------- read data for delta----------------------*/
        char delta_dataFileName[] = "/dataFile/influence.c_accumulate_influence_line277_1.delta.dat";
        char delta_dataFileWithPath[256];
        sprintf (delta_dataFileWithPath, "%s/%s", argv[1], delta_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(delta_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_accumulate_influence_line277_1.delta.dat does not exist!");
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
        memcpy(&ii, &ii_, sizeof(ii_));

        /*----------------- read data for board----------------------*/
        char board_dataFileName[] = "/dataFile/influence.c_accumulate_influence_line277_1.board.dat";
        char board_dataFileWithPath[256];
        sprintf (board_dataFileWithPath, "%s/%s", argv[1], board_dataFileName);
        unsigned char unsigned_char_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(board_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_accumulate_influence_line277_1.board.dat does not exist!");
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

    unsigned char MD5_queue[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext_queue;
    MD5_Init (&mdContext_queue);
    for (int i0 = 0; i0 < 20 * 20; i0++)
    {
        MD5_Update(&mdContext_queue, &queue[i0], sizeof(int));
    }
    MD5_Final(MD5_queue, &mdContext_queue);
    printf("Int array MD5_queue: ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        printf("%02x", MD5_queue[i]);
    }
    printf("\n");

    unsigned char MD5_working[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext_working;
    MD5_Init (&mdContext_working);
    for (int i0 = 0; i0 < 20 * 20; i0++)
    {
        MD5_Update(&mdContext_working, &working[i0], sizeof(int));
    }
    MD5_Final(MD5_working, &mdContext_working);
    printf("Int array MD5_working: ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        printf("%02x", MD5_working[i]);
    }
    printf("\n");

    printf("\n");
    printf("Scalar queue_end: %d\n", queue_end);
    printf("Scalar d: %d\n", d);


    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
