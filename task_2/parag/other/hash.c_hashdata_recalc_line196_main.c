#include <hash.c_hashdata_recalc_line196_1.ptrderefout.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <hash.c_hashdata_recalc_line196_1.h>
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
Intersection * restrict p;
int i;
typedef unsigned long Hashvalue;
typedef struct
{
    Hashvalue hashval[64 /(8 * sizeof(long ))];
} Hash_data;
Hash_data * restrict target;
Hashvalue  white_hash[(19 + 1) *(19 + 1)][64 /(8 * sizeof(long ))] = {0};
Hashvalue  black_hash[(19 + 1) *(19 + 1)][64 /(8 * sizeof(long ))] = {0};

int main(int argc, char** argv)
{
    int inputIndices[10];
    FILE* pFile_;
    int iterations = 1;
    uint64_t *cycleArray;
    void *oldBrk;

    static char* inputDataFileName[] = {"hash.c_hashdata_recalc_line196_1.ptrderefout.hd", "hash.c_hashdata_recalc_line196_1.ptrderefout.st", "hash.c_hashdata_recalc_line196_1.ptrderefout.gl"};
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
        p = (Intersection *) p_;
        target = (Hash_data *) target_;


        /*----------------- read data for black_hash----------------------*/
        char black_hash_dataFileName[] = "/dataFile/hash.c_hashdata_recalc_line196_1.black_hash.dat";
        char black_hash_dataFileWithPath[256];
        sprintf (black_hash_dataFileWithPath, "%s/%s", argv[1], black_hash_dataFileName);
        unsigned long unsigned_long_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(black_hash_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/hash.c_hashdata_recalc_line196_1.black_hash.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_, "%d", &inputIndices[1]);
                fscanf(pFile_,"%u", &unsigned_long_storage);
                black_hash_[inputIndices[0]][inputIndices[1]] = unsigned_long_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for black_hash------------------*/
        memcpy(black_hash, black_hash_, sizeof(black_hash_));

        /*----------------- read data for white_hash----------------------*/
        char white_hash_dataFileName[] = "/dataFile/hash.c_hashdata_recalc_line196_1.white_hash.dat";
        char white_hash_dataFileWithPath[256];
        sprintf (white_hash_dataFileWithPath, "%s/%s", argv[1], white_hash_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(white_hash_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/hash.c_hashdata_recalc_line196_1.white_hash.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_, "%d", &inputIndices[1]);
                fscanf(pFile_,"%u", &unsigned_long_storage);
                white_hash_[inputIndices[0]][inputIndices[1]] = unsigned_long_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for white_hash------------------*/
        memcpy(white_hash, white_hash_, sizeof(white_hash_));

        /*----------------- read data for board----------------------*/
        char board_dataFileName[] = "/dataFile/hash.c_hashdata_recalc_line196_1.board.dat";
        char board_dataFileWithPath[256];
        sprintf (board_dataFileWithPath, "%s/%s", argv[1], board_dataFileName);
        unsigned char unsigned_char_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(board_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/hash.c_hashdata_recalc_line196_1.board.dat does not exist!");
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
        target = (Hash_data *)target_;
        int target_hashval_dimension_sizes[1];

        /*----------------- read data for target_hashval----------------------*/
        char target_hashval_dataFileName[] = "/dataFile/hash.c_hashdata_recalc_line196_1.target_hashval.dat";
        char target_hashval_dataFileWithPath[256];
        sprintf (target_hashval_dataFileWithPath, "%s/%s", argv[1], target_hashval_dataFileName);

        if ( it < 1 )
        {
            pFile_ = fopen(target_hashval_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/hash.c_hashdata_recalc_line196_1.target_hashval.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%u", &unsigned_long_storage);
                target_hashval_[inputIndices[0]] = unsigned_long_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for target_hashval------------------*/

        if (heapChunkSize > 0)
        {
            if (it < 1)
                oldBrk = mallocMemoryChunk(heapDataFile, minimumHeapAddress, maximumHeapAddress, heapChunkSize);
            else
                resetHeapData(minimumHeapAddress, maximumHeapAddress, heapChunkSize);
        }

        if (it < 1)
            cycleArray = getCycleArray(heapChunkSize, iterations);

        memcpy(target->hashval, target_hashval_, sizeof(target_hashval_));
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
    printf("Scalar i: %d\n", i);
    printf("Scalar pos: %d\n", pos);

    void* ptrCheckSumVal = dummy(2, p, target);
    printf("The checksum of the addresses of pointer variables is: %p \n", ptrCheckSumVal);

    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
