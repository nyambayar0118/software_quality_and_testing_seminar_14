#include "Basic.h"
#include <stdio.h>
#include <string.h>

static CU_BasicRunMode basic_mode = BRM_NORMAL;
static int tests_run_count = 0;
static int tests_failed_count = 0;
static int suites_run_count = 0;
static int suites_failed_count = 0;

#define MAX_FAILURES 100
static struct
{
    char suite_name[256];
    char test_name[256];
    int line_number;
} failures[MAX_FAILURES];
static int failure_count = 0;

void CU_basic_set_mode(CU_BasicRunMode mode)
{
    basic_mode = mode;
}

CU_BasicRunMode CU_basic_get_mode(void)
{
    return basic_mode;
}

void CU_basic_print_header(void)
{
    if (basic_mode != BRM_SILENT)
    {
        printf("\n\n     CUnit - A unit testing framework for C\n\n");
    }
}

void CU_basic_print_summary(void)
{
    if (basic_mode == BRM_SILENT)
    {
        return;
    }

    printf("\n--Run Summary: Type      Total     Ran  Passed  Failed\n");
    printf("               suites  %7d %7d     n/a %7d\n",
           suites_run_count, suites_run_count, suites_failed_count);
    printf("               tests   %7d %7d %7d %7d\n",
           tests_run_count, tests_run_count,
           tests_run_count - tests_failed_count, tests_failed_count);
    printf("               asserts      n/a %7d %7d %7d\n",
           g_nTestsRun, g_nTestsRun - g_nTestsFailed, g_nTestsFailed);

    if (tests_failed_count > 0)
    {
        printf("\nFailed tests:\n");
        CU_basic_show_failures();
    }
}

void CU_basic_show_failures(void)
{
    int i;
    for (i = 0; i < failure_count && i < MAX_FAILURES; i++)
    {
        printf("  %d. %s:%s\n", i + 1, failures[i].suite_name, failures[i].test_name);
    }
}

int CU_basic_run_test(CU_pSuite pSuite, CU_pTest pTest)
{
    int failed_before;

    if (pSuite == NULL || pTest == NULL)
    {
        return -1;
    }

    failed_before = g_nTestsFailed;

    if (basic_mode == BRM_VERBOSE)
    {
        printf("    Running: %s ...", pTest->pName);
        fflush(stdout);
    }

    pTest->pTestFunc();

    tests_run_count++;

    if (g_nTestsFailed > failed_before)
    {
        tests_failed_count++;

        if (failure_count < MAX_FAILURES)
        {
            strncpy(failures[failure_count].suite_name, pSuite->pName, 255);
            failures[failure_count].suite_name[255] = '\0';
            strncpy(failures[failure_count].test_name, pTest->pName, 255);
            failures[failure_count].test_name[255] = '\0';
            failures[failure_count].line_number = 0;
            failure_count++;
        }

        if (basic_mode == BRM_VERBOSE)
        {
            printf(" FAILED\n");
        }
        else if (basic_mode == BRM_NORMAL)
        {
            printf("F");
            fflush(stdout);
        }
        return 0;
    }
    else
    {
        if (basic_mode == BRM_VERBOSE)
        {
            printf(" passed\n");
        }
        else if (basic_mode == BRM_NORMAL)
        {
            printf(".");
            fflush(stdout);
        }
        return 1;
    }
}

int CU_basic_run_suite(CU_pSuite pSuite)
{
    CU_pTest pTest;

    if (pSuite == NULL)
    {
        return -1;
    }

    suites_run_count++;

    if (basic_mode == BRM_VERBOSE)
    {
        printf("\nSuite: %s\n", pSuite->pName);
    }
    else if (basic_mode == BRM_NORMAL)
    {
        printf("\nSuite: %s\n  ", pSuite->pName);
    }

    if (pSuite->pInitFunc != NULL)
    {
        if (pSuite->pInitFunc() != 0)
        {
            if (basic_mode != BRM_SILENT)
            {
                printf("  Suite initialization failed - skipping suite.\n");
            }
            suites_failed_count++;
            return 0;
        }
    }

    pTest = pSuite->pTest;
    while (pTest != NULL)
    {
        CU_basic_run_test(pSuite, pTest);
        pTest = pTest->pNext;
    }

    if (pSuite->pCleanupFunc != NULL)
    {
        pSuite->pCleanupFunc();
    }

    if (basic_mode == BRM_NORMAL)
    {
        printf("\n");
    }

    return 1;
}

int CU_basic_run_tests(void)
{
    CU_pSuite pSuite;

    tests_run_count = 0;
    tests_failed_count = 0;
    suites_run_count = 0;
    suites_failed_count = 0;
    failure_count = 0;
    g_nTestsRun = 0;
    g_nTestsFailed = 0;

    CU_basic_print_header();

    pSuite = g_pTestRegistry;
    while (pSuite != NULL)
    {
        CU_basic_run_suite(pSuite);
        pSuite = pSuite->pNext;
    }

    CU_basic_print_summary();

    return (tests_failed_count == 0) ? 0 : 1;
}