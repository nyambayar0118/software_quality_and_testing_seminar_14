#include <stdlib.h>
#include "CUnit.h"
#include "Basic.h"
#include "twosum.h"

void test_twosum(void)
{
    int returnSize;

    // ---- Test 1 ----
    int nums1[] = {2, 7, 11, 15};
    int *res1 = twoSum(nums1, 4, 9, &returnSize);

    CU_ASSERT_PTR_NOT_NULL(res1);
    CU_ASSERT_EQUAL(returnSize, 2);
    CU_ASSERT_EQUAL(res1[0], 0);
    CU_ASSERT_EQUAL(res1[1], 1);
    free(res1);

    // ---- Test 2 ----
    int nums2[] = {3, 2, 4};
    int *res2 = twoSum(nums2, 3, 6, &returnSize);

    CU_ASSERT_PTR_NOT_NULL(res2);
    CU_ASSERT_EQUAL(returnSize, 2);
    CU_ASSERT_EQUAL(res2[0], 1);
    CU_ASSERT_EQUAL(res2[1], 2);
    free(res2);

    // ---- Test 3 ----
    int nums3[] = {3, 3};
    int *res3 = twoSum(nums3, 2, 6, &returnSize);

    CU_ASSERT_PTR_NOT_NULL(res3);
    CU_ASSERT_EQUAL(returnSize, 2);
    CU_ASSERT_EQUAL(res3[0], 0);
    CU_ASSERT_EQUAL(res3[1], 1);
    free(res3);
}

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("TwoSum Test Suite", NULL, NULL);

    CU_add_test(suite, "Test TwoSum", test_twosum);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}