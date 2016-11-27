#include <utils.c_superstring_add_string_line1785_1.ptrderefout.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <utils.c_superstring_add_string_line1785_1.h>
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
int num_my_libs;
char  ml[(19 + 1) *(19 + 1)] = {0};
int  my_libs[724 / 3] = {0};
int do_add;
int liberty_cap;
int * restrict libs;
int * restrict num_libs;
int maxlibs;

int main(int argc, char** argv)
{
    int inputIndices[10];
    FILE* pFile_;
    int iterations = 1;
    uint64_t *cycleArray;
    void *oldBrk;

    static char* inputDataFileName[] = {"utils.c_superstring_add_string_line1785_1.ptrderefout.hd", "utils.c_superstring_add_string_line1785_1.ptrderefout.st", "utils.c_superstring_add_string_line1785_1.ptrderefout.gl"};
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
        libs = (int *) libs_;
        num_libs = (int *) num_libs_;

        memcpy(&maxlibs, &maxlibs_, sizeof(maxlibs_));
        memcpy(&liberty_cap, &liberty_cap_, sizeof(liberty_cap_));
        memcpy(&do_add, &do_add_, sizeof(do_add_));

        /*----------------- read data for my_libs----------------------*/
        char my_libs_dataFileName[] = "/dataFile/utils.c_superstring_add_string_line1785_1.my_libs.dat";
        char my_libs_dataFileWithPath[256];
        sprintf (my_libs_dataFileWithPath, "%s/%s", argv[1], my_libs_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(my_libs_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/utils.c_superstring_add_string_line1785_1.my_libs.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                my_libs_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for my_libs------------------*/
        memcpy(my_libs, my_libs_, sizeof(my_libs_));
        int ml_dimension_sizes[1];

        /*----------------- read data for ml----------------------*/
        char ml_dataFileName[] = "/dataFile/utils.c_superstring_add_string_line1785_1.ml.dat";
        char ml_dataFileWithPath[256];
        sprintf (ml_dataFileWithPath, "%s/%s", argv[1], ml_dataFileName);
        char char_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(ml_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/utils.c_superstring_add_string_line1785_1.ml.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%c", &char_storage);
                ml_[inputIndices[0]] = char_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for ml------------------*/
        memcpy(ml, ml_, sizeof(ml_));
        memcpy(&num_my_libs, &num_my_libs_, sizeof(num_my_libs_));

        if (heapChunkSize > 0)
        {
            if (it < 1)
                oldBrk = mallocMemoryChunk(heapDataFile, minimumHeapAddress, maximumHeapAddress, heapChunkSize);
            else
                resetHeapData(minimumHeapAddress, maximumHeapAddress, heapChunkSize);
        }

        if (it < 1)
            cycleArray = getCycleArray(heapChunkSize, iterations);

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

    unsigned char MD5_ml[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext_ml;
    MD5_Init (&mdContext_ml);
    for (int i0 = 0; i0 < (19 + 1) *(19 + 1); i0++)
    {
        MD5_Update(&mdContext_ml, &ml[i0], sizeof(char));
    }
    MD5_Final(MD5_ml, &mdContext_ml);
    printf("Int array MD5_ml: ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        printf("%02x", MD5_ml[i]);
    }
    printf("\n");

    printf("\n");
    printf("Scalar k: %d\n", k);

    void* ptrCheckSumVal = dummy(2, libs, num_libs);
    printf("The checksum of the addresses of pointer variables is: %p \n", ptrCheckSumVal);

    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
