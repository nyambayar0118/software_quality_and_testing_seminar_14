#include <stdlib.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    int *result = (int *)malloc(sizeof(int) * 2);
    for (int i = 0; i < numsSize - 1; i++)
    {
        for (int j = i + 1; j < numsSize; j++)
        {
            int sum;
            if (i == j)
                continue;
            sum = nums[i] + nums[j];
            result[0] = i;
            result[1] = j;

            if (sum == target)
            {
                *returnSize = 2;
                return result;
            }
        }
    }

    *returnSize = 0;
    return NULL;
}

// int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
//     for (int i=0; i<numsSize-1; i++) {
//         for (int j=i+1; j<numsSize; j++) {
//             if (nums[i] + nums[j] == target) {
//                 int* result = (int*)malloc(sizeof(int)*2);
//                 result[0] = i;
//                 result[1] = j;
//                 *returnSize=2;
//                 return result;
//             }
//         }
//     }

//     *returnSize=0;
//     return NULL;
// }