#include "CUnit.h"
#include <string.h>

/* Global variables */
CU_pSuite g_pTestRegistry = NULL;
int g_nTestsFailed = 0;
int g_nTestsRun = 0;

/* Initialize the test registry */
int CU_initialize_registry(void)
{
    g_pTestRegistry = NULL;
    g_nTestsFailed = 0;
    g_nTestsRun = 0;
    return 0;
}

/* Cleanup the test registry */
void CU_cleanup_registry(void)
{
    CU_pSuite pSuite = g_pTestRegistry;
    while (pSuite != NULL)
    {
        CU_pSuite pNextSuite = pSuite->pNext;

        /* Free all tests in this suite */
        CU_pTest pTest = pSuite->pTest;
        while (pTest != NULL)
        {
            CU_pTest pNextTest = pTest->pNext;
            free(pTest->pName);
            free(pTest);
            pTest = pNextTest;
        }

        free(pSuite->pName);
        free(pSuite);
        pSuite = pNextSuite;
    }
    g_pTestRegistry = NULL;
}

/* Add a suite to the registry */
CU_pSuite CU_add_suite(const char *strName, int (*pInit)(void), int (*pClean)(void))
{
    CU_pSuite pSuite = (CU_pSuite)malloc(sizeof(CU_Suite));
    CU_pSuite pTemp;

    if (pSuite == NULL)
    {
        return NULL;
    }

    pSuite->pName = (char *)malloc(strlen(strName) + 1);
    strcpy(pSuite->pName, strName);
    pSuite->pTest = NULL;
    pSuite->pNext = NULL;
    pSuite->pInitFunc = pInit;
    pSuite->pCleanupFunc = pClean;

    /* Add to registry */
    if (g_pTestRegistry == NULL)
    {
        g_pTestRegistry = pSuite;
    }
    else
    {
        pTemp = g_pTestRegistry;
        while (pTemp->pNext != NULL)
        {
            pTemp = pTemp->pNext;
        }
        pTemp->pNext = pSuite;
    }

    return pSuite;
}

/* Add a test to a suite */
CU_pTest CU_add_test(CU_pSuite pSuite, const char *strName, void (*pTestFunc)(void))
{
    CU_pTest pTest;
    CU_pTest pTemp;

    if (pSuite == NULL)
    {
        return NULL;
    }

    pTest = (CU_pTest)malloc(sizeof(CU_Test));
    if (pTest == NULL)
    {
        return NULL;
    }

    pTest->pName = (char *)malloc(strlen(strName) + 1);
    strcpy(pTest->pName, strName);
    pTest->pTestFunc = pTestFunc;
    pTest->pNext = NULL;

    /* Add to suite */
    if (pSuite->pTest == NULL)
    {
        pSuite->pTest = pTest;
    }
    else
    {
        pTemp = pSuite->pTest;
        while (pTemp->pNext != NULL)
        {
            pTemp = pTemp->pNext;
        }
        pTemp->pNext = pTest;
    }

    return pTest;
}