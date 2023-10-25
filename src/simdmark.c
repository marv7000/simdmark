#include "simdmark.h"
#include "tests.h"

int main(const int argc, const char** argv)
{
    uint64_t iterations = SM_ITERATIONS;
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
        {
            printf("Usage:\n"
                "\t-h --help\n"
                "\t\tPrints the help string.\n"
                "\t-v --version\n"
                "\t\tPrints the version.\n"
                "\t-e --extensions\n"
                "\t\tPrints all available SIMD extensions.\n"
                "\t-i --iterations\n"
                "\t\tSpecifies the amount of iterations to run for each test.\n");
            return 0;
        }
        else if (!strcmp(argv[i], "-e") || !strcmp(argv[i], "--extensions"))
        {
            SimdFeatures f = sm_getExtensions();

            // Output features.
            puts("Available SIMD extensions:");
            printf("sse\t%c\n",     f.SSE ? 'y' : 'n');
            printf("sse2\t%c\n",    f.SSE2 ? 'y' : 'n');
            printf("sse3\t%c\n",    f.SSE3 ? 'y' : 'n');
            printf("ssse3\t%c\n",   f.SSSE3 ? 'y' : 'n');
            printf("sse4a\t%c\n",   f.SSE4A ? 'y' : 'n');
            printf("sse4.1\t%c\n",  f.SSE41 ? 'y' : 'n');
            printf("sse4.2\t%c\n",  f.SSE42 ? 'y' : 'n');
            printf("avx\t%c\n",     f.AVX ? 'y' : 'n');
            printf("avx2\t%c\n",    f.AVX2 ? 'y' : 'n');
            printf("avx512\t%c\n",  f.AVX512 ? 'y' : 'n');
            return 0;
        }
        else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version"))
        {
            printf("simdmark %i.%i\n\n", SM_VERSION_MAJ, SM_VERSION_MIN);
            return 0;
        }
        else if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--iterations"))
        {
            int64_t iter = atoll(argv[++i]);
            iterations = iter < 0 ? SM_ITERATIONS : iter;
        }
        else if (argv[i][0] == '-')
        {
            printf("Unknown parameter \"%s\"\n", argv[i]);
            return 0;
        }
    }

    printf("Running tests with %i iterations...\n\n", iterations);
    // TODO: Add new tests here.
    char* testNames[] =
    {
        "ArithmeticPacked [SSE]",
        "ArithmeticPacked [SSE2]",
        "ArithmeticScalar [SSE]",
        "ArithmeticScalar [SSE2]"
    };
    VoidFn tests[] = 
    {
        sm_testArithmeticPackedSSE,
        sm_testArithmeticPackedSSE2,
        sm_testArithmeticScalarSSE,
        sm_testArithmeticScalarSSE2,
    };

    SimdFeatures f = sm_getExtensions();
    clock_t time = clock();
    for (int testIdx = 0; testIdx < sizeof(tests) / sizeof(VoidFn); testIdx++)
    {
        clock_t testTime = tests[testIdx](f, iterations);
        if (testTime < 0)
            printf("Test %i\t (%s)\t failed (Check if the CPU supports these instructions with 'simdmark -e')!\n", testIdx, testNames[testIdx]);
        else
            printf("Test %i\t (%s)\t succeeded! took %fs\n", testIdx, testNames[testIdx], (double)testTime / (double)CLOCKS_PER_SEC);
        time += testTime;
    }
    printf("\nTotal time spent: %fs\n", (double)(time) / (double)CLOCKS_PER_SEC);
    return 0;
}