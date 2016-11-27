#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <influence.c_accumulate_influence_line296_1.h>
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
int queue_end;
int ii;
int  queue[20 * 20] = {0};
int  working[20 * 20] = {0};
int  influence[(19 + 1) *(19 + 1)] = {0};

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
        int influence_dimension_sizes[1];

        /*----------------- read data for influence----------------------*/
        char influence_dataFileName[] = "/dataFile/influence.c_accumulate_influence_line296_1.influence.dat";
        char influence_dataFileWithPath[256];
        sprintf (influence_dataFileWithPath, "%s/%s", argv[1], influence_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(influence_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_accumulate_influence_line296_1.influence.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                influence_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for influence------------------*/
        memcpy(influence, influence_, sizeof(influence_));
        int working_dimension_sizes[1];

        /*----------------- read data for working----------------------*/
        char working_dataFileName[] = "/dataFile/influence.c_accumulate_influence_line296_1.working.dat";
        char working_dataFileWithPath[256];
        sprintf (working_dataFileWithPath, "%s/%s", argv[1], working_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(working_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_accumulate_influence_line296_1.working.dat does not exist!");
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

        /*----------------- read data for queue----------------------*/
        char queue_dataFileName[] = "/dataFile/influence.c_accumulate_influence_line296_1.queue.dat";
        char queue_dataFileWithPath[256];
        sprintf (queue_dataFileWithPath, "%s/%s", argv[1], queue_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(queue_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/influence.c_accumulate_influence_line296_1.queue.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                queue_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for queue------------------*/
        memcpy(queue, queue_, sizeof(queue_));
        memcpy(&queue_end, &queue_end_, sizeof(queue_end_));

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

    unsigned char MD5_influence[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext_influence;
    MD5_Init (&mdContext_influence);
    for (int i0 = 0; i0 < (19 + 1) *(19 + 1); i0++)
    {
        MD5_Update(&mdContext_influence, &influence[i0], sizeof(int));
    }
    MD5_Final(MD5_influence, &mdContext_influence);
    printf("Int array MD5_influence: ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        printf("%02x", MD5_influence[i]);
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
    printf("Scalar ii: %d\n", ii);
    printf("Scalar k: %d\n", k);


    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
