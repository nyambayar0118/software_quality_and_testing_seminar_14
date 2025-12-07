#ifndef CUNIT_BASIC_H
#define CUNIT_BASIC_H

#include "CUnit.h"

/* Basic test running modes */
typedef enum
{
    BRM_NORMAL = 0,
    BRM_SILENT = 1,
    BRM_VERBOSE = 2
} CU_BasicRunMode;

/* For backward compatibility */
#define CU_BRM_NORMAL BRM_NORMAL
#define CU_BRM_SILENT BRM_SILENT
#define CU_BRM_VERBOSE BRM_VERBOSE

/* Basic interface functions */
void CU_basic_set_mode(CU_BasicRunMode mode);
CU_BasicRunMode CU_basic_get_mode(void);

int CU_basic_run_tests(void);
int CU_basic_run_suite(CU_pSuite pSuite);
int CU_basic_run_test(CU_pSuite pSuite, CU_pTest pTest);

void CU_basic_show_failures(void);

/* Console output functions */
void CU_basic_print_header(void);
void CU_basic_print_summary(void);

#endif /* CUNIT_BASIC_H */