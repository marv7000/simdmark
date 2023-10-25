#pragma once
#include <immintrin.h>
#include "simdmark.h"

static inline double randDouble()
{
    return (double)rand() * ((double)rand() / rand()+1);
}

static inline clock_t sm_testArithmeticPackedSSE(SimdFeatures f, uint64_t iter)
{
    clock_t t = clock();
    if (f.SSE)
    {
        __m128 first = _mm_set1_ps(randDouble());
        __m128 second = _mm_set1_ps(randDouble());

        for (int i = 0; i < iter; i++)
        {
            first = _mm_add_ps(first, second);
        }
        first = _mm_setzero_ps();
        for (int i = 0; i < iter; i++)
        {
            first = _mm_sub_ps(first, second);
        }
        first = _mm_setzero_ps();
        for (int i = 0; i < iter; i++)
        {
            first = _mm_mul_ps(first, second);
        }
        first = _mm_setzero_ps();
        for (int i = 0; i < iter; i++)
        {
            first = _mm_div_ps(first, second);
        }
    }
    else return -1;
    return clock() - t;
}

static inline clock_t sm_testArithmeticPackedSSE2(SimdFeatures f, uint64_t iter)
{
    clock_t t = clock();
    if (f.SSE2)
    {
        __m128d first = _mm_set1_pd(randDouble());
        __m128d second = _mm_set1_pd(randDouble());

        for (int i = 0; i < iter; i++)
        {
            first = _mm_div_pd(first, second);
        }
        first = _mm_setzero_pd();
        for (int i = 0; i < iter; i++)
        {
            first = _mm_add_pd(first, second);
        }
        first = _mm_setzero_pd();
        for (int i = 0; i < iter; i++)
        {
            first = _mm_sub_pd(first, second);
        }
        first = _mm_setzero_pd();
        for (int i = 0; i < iter; i++)
        {
            first = _mm_mul_pd(first, second);
        }
    }
    else return -1;
    return clock() - t;
}

static inline clock_t sm_testArithmeticScalarSSE(SimdFeatures f, uint64_t iter)
{
    clock_t t = clock();
    if (f.SSE2)
    {
        __m128d first = _mm_set1_pd(randDouble());
        __m128d second = _mm_set1_pd(randDouble());

        for (int i = 0; i < iter; i++)
        {
            first = _mm_div_pd(first, second);
        }
        first = _mm_setzero_pd();
        for (int i = 0; i < iter; i++)
        {
            first = _mm_add_pd(first, second);
        }
        first = _mm_setzero_pd();
        for (int i = 0; i < iter; i++)
        {
            first = _mm_sub_pd(first, second);
        }
        first = _mm_setzero_pd();
        for (int i = 0; i < iter; i++)
        {
            first = _mm_mul_pd(first, second);
        }
    }
    else return -1;
    return clock() - t;
}

static inline clock_t sm_testArithmeticScalarSSE2(SimdFeatures f, uint64_t iter)
{
    clock_t t = clock();
    if (f.SSE2)
    {
        __m128d first = _mm_set_sd(randDouble());
        __m128d second = _mm_set_sd(randDouble());

        for (int i = 0; i < iter; i++)
        {
            first = _mm_add_sd(first, second);
        }
        first = _mm_set_sd(randDouble());
        for (int i = 0; i < iter; i++)
        {
            first = _mm_sub_sd(first, second);
        }
        first = _mm_set_sd(randDouble());
        for (int i = 0; i < iter; i++)
        {
            first = _mm_mul_sd(first, second);
        }
        first = _mm_set_sd(randDouble());
        for (int i = 0; i < iter; i++)
        {
            first = _mm_div_sd(first, second);
        }
    }
    else return -1;
    return clock() - t;
}