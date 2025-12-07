#ifndef CUNIT_CUNIT_H
#define CUNIT_CUNIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Test Registry */
typedef struct CU_Suite
{
    char *pName;
    struct CU_Test *pTest;
    struct CU_Suite *pNext;
    int (*pInitFunc)(void);
    int (*pCleanupFunc)(void);
} CU_Suite;

typedef struct CU_Test
{
    char *pName;
    void (*pTestFunc)(void);
    struct CU_Test *pNext;
} CU_Test;

typedef CU_Suite *CU_pSuite;
typedef CU_Test *CU_pTest;

/* Global variables */
extern CU_pSuite g_pTestRegistry;
extern int g_nTestsFailed;
extern int g_nTestsRun;

/* Registry functions */
int CU_initialize_registry(void);
void CU_cleanup_registry(void);
CU_pSuite CU_add_suite(const char *strName, int (*pInit)(void), int (*pClean)(void));
CU_pTest CU_add_test(CU_pSuite pSuite, const char *strName, void (*pTestFunc)(void));

/* Assertion macros */
#define CU_ASSERT(value)                                                     \
    do                                                                       \
    {                                                                        \
        g_nTestsRun++;                                                       \
        if (!(value))                                                        \
        {                                                                    \
            g_nTestsFailed++;                                                \
            printf("FAILED: %s, line %d: %s\n", __FILE__, __LINE__, #value); \
        }                                                                    \
    } while (0)

#define CU_ASSERT_EQUAL(actual, expected)                                                                  \
    do                                                                                                     \
    {                                                                                                      \
        g_nTestsRun++;                                                                                     \
        if ((actual) != (expected))                                                                        \
        {                                                                                                  \
            g_nTestsFailed++;                                                                              \
            printf("FAILED: %s, line %d: %d != %d\n", __FILE__, __LINE__, (int)(actual), (int)(expected)); \
        }                                                                                                  \
    } while (0)

#define CU_ASSERT_PTR_NOT_NULL(value)                                             \
    do                                                                            \
    {                                                                             \
        g_nTestsRun++;                                                            \
        if ((value) == NULL)                                                      \
        {                                                                         \
            g_nTestsFailed++;                                                     \
            printf("FAILED: %s, line %d: pointer is NULL\n", __FILE__, __LINE__); \
        }                                                                         \
    } while (0)

#define CU_ASSERT_PTR_NULL(value)                                                     \
    do                                                                                \
    {                                                                                 \
        g_nTestsRun++;                                                                \
        if ((value) != NULL)                                                          \
        {                                                                             \
            g_nTestsFailed++;                                                         \
            printf("FAILED: %s, line %d: pointer is not NULL\n", __FILE__, __LINE__); \
        }                                                                             \
    } while (0)

#define CU_ASSERT_STRING_EQUAL(actual, expected)                                                         \
    do                                                                                                   \
    {                                                                                                    \
        g_nTestsRun++;                                                                                   \
        if (strcmp((actual), (expected)) != 0)                                                           \
        {                                                                                                \
            g_nTestsFailed++;                                                                            \
            printf("FAILED: %s, line %d: \"%s\" != \"%s\"\n", __FILE__, __LINE__, (actual), (expected)); \
        }                                                                                                \
    } while (0)

#define CU_PASS(msg)                 \
    do                               \
    {                                \
        g_nTestsRun++;               \
        printf("PASSED: %s\n", msg); \
    } while (0)

#define CU_FAIL(msg)                 \
    do                               \
    {                                \
        g_nTestsRun++;               \
        g_nTestsFailed++;            \
        printf("FAILED: %s\n", msg); \
    } while (0)

#endif /* CUNIT_CUNIT_H */