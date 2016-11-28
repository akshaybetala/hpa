#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <openssl/md5.h>
#include <value_moves.c_record_top_move_line2681_1.h>
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
float val;
float  best_move_values[10] = {0};
int  best_moves[10] = {0};
int move;

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
        memcpy(&move, &move_, sizeof(move_));
        int best_moves_dimension_sizes[1];

        /*----------------- read data for best_moves----------------------*/
        char best_moves_dataFileName[] = "/dataFile/value_moves.c_record_top_move_line2681_1.best_moves.dat";
        char best_moves_dataFileWithPath[256];
        sprintf (best_moves_dataFileWithPath, "%s/%s", argv[1], best_moves_dataFileName);
        int int_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(best_moves_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/value_moves.c_record_top_move_line2681_1.best_moves.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%d", &int_storage);
                best_moves_[inputIndices[0]] = int_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for best_moves------------------*/
        memcpy(best_moves, best_moves_, sizeof(best_moves_));
        int best_move_values_dimension_sizes[1];

        /*----------------- read data for best_move_values----------------------*/
        char best_move_values_dataFileName[] = "/dataFile/value_moves.c_record_top_move_line2681_1.best_move_values.dat";
        char best_move_values_dataFileWithPath[256];
        sprintf (best_move_values_dataFileWithPath, "%s/%s", argv[1], best_move_values_dataFileName);
        float float_storage;

        if ( it < 1 )
        {
            pFile_ = fopen(best_move_values_dataFileWithPath, "r");
            if (pFile_ == NULL)
            {
                printf("data file: /dataFile/value_moves.c_record_top_move_line2681_1.best_move_values.dat does not exist!");
                exit(-1);
            }
            while(fscanf(pFile_, "%d", &inputIndices[0]) != EOF)
            {
                fscanf(pFile_,"%f", &float_storage);
                best_move_values_[inputIndices[0]] = float_storage;
            }
            fclose(pFile_);
        }
        /*----------------- Read is done for best_move_values------------------*/
        memcpy(best_move_values, best_move_values_, sizeof(best_move_values_));
        memcpy(&val, &val_, sizeof(val_));

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

    unsigned char MD5_best_moves[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext_best_moves;
    MD5_Init (&mdContext_best_moves);
    for (int i0 = 0; i0 < 10; i0++)
    {
        MD5_Update(&mdContext_best_moves, &best_moves[i0], sizeof(int));
    }
    MD5_Final(MD5_best_moves, &mdContext_best_moves);
    printf("Int array MD5_best_moves: ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        printf("%02x", MD5_best_moves[i]);
    }
    printf("\n");

    float fp_checksum_best_move_values = 0.0;
    for (int i0 = 0; i0 < 10; i0++)
    {
        fp_checksum_best_move_values += best_move_values[i0];
    }
    printf("f.p. array best_move_values: %f",fp_checksum_best_move_values);
    printf("\n");

    printf("\n");
    printf("Scalar k: %d\n", k);


    printf("Simulation time (cycles) stats:\n min\tmax\tmean\tmedian\tstdv\n");
    printf("%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t%"PRIu64"\t\n", min_tsc_cycles, max_tsc_cycles, mean_tsc_cycles, median_tsc_cycles, stdv_tsc_cycles);

    return 0;
}
