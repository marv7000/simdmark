#pragma once
#include <stdbool.h>
#include <cpuid.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define SM_VERSION_MAJ 1
#define SM_VERSION_MIN 0
#define SM_ITERATIONS 10000

#define SM_BITFLAG(val, cmp) ((val & cmp) == cmp)

typedef struct _SimdFeatures
{
    bool SSE : 1;
    bool SSE2 : 1;
    bool SSE3 : 1;
    bool SSSE3 : 1;
    bool SSE4A : 1;
    bool SSE41 : 1;
    bool SSE42 : 1;
    bool SSE5 : 1;
    bool AVX : 1;
    bool AVX2 : 1;
    bool AVX512 : 1;
} SimdFeatures;

typedef clock_t(*VoidFn)(SimdFeatures f, uint64_t iter);

// Calls the CPUID instruction. 
static inline void sm_cpuId(int leaf, int subleaf, uint32_t registers[4])
{
    registers[0] = leaf;
    registers[1] = 0;
    registers[2] = subleaf;
    registers[3] = 0;

    uint32_t ext = leaf & 0x80000000;
    uint32_t mLevel = __get_cpuid_max(ext, 0);

    if (mLevel == 0 || mLevel < leaf)
    {
        printf("Couldn't fetch CPUID data for %i, %i!\n", leaf, subleaf);
        exit(1);
        return;
    }
    __get_cpuid_count(leaf, subleaf, registers + 0, registers + 1, registers + 2, registers +3);
}

// Gets all SIMD extensions.
static inline SimdFeatures sm_getExtensions()
{
    SimdFeatures f;
    uint32_t info[4] = {0, 0, 0, 0};
    
    // Get base SSE and AVX extensions.
    sm_cpuId(1, 0, info);
    f.SSE    = SM_BITFLAG(info[3], bit_SSE);
    f.SSE2   = SM_BITFLAG(info[3], bit_SSE2);
    f.SSE3   = SM_BITFLAG(info[2], bit_SSE3);
    f.SSSE3  = SM_BITFLAG(info[2], bit_SSSE3);
    f.SSE41  = SM_BITFLAG(info[2], bit_SSE4_1);
    f.SSE42  = SM_BITFLAG(info[2], bit_SSE4_2);
    f.AVX    = SM_BITFLAG(info[2], bit_AVX);
    
    // Get new SSE extensions.
    sm_cpuId(0x80000000, 0, info);
    if (info[0] >= 0x80000001)
    {
        f.SSE4A  = SM_BITFLAG(info[2], bit_SSE4a);
        f.SSE5   = SM_BITFLAG(info[2], bit_XOP);
    }
    
    // Get new AVX extensions.
    sm_cpuId(7, 0, info);
    f.AVX2   = SM_BITFLAG(info[1], bit_AVX2);
    f.AVX512 = SM_BITFLAG(info[1], bit_AVX512F);

    return f;
}