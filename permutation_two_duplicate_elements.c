// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <string.h>
void swap (int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int cmpint(int *p1, int *p2, int size){ 
	while(size){
        if(*p1++!=*p2++)
            return 0;
        size--;
    }
	return 1;
}  

void backtracking(int **res, int *returnSize, int **returnColumnSizes, int *nums, int start, int size){

    if(start == size){
        printf("##### if condition #### start=%d\n",start);
        if((*returnSize)!=0){
            int i=0;
            while(i<*returnSize){
                if (cmpint(res[i], nums, size)==1)
                    return;
                i++;
            }
        }
        res[*returnSize]=(int*)malloc(sizeof(int)*(size));
        memcpy(res[*returnSize], nums, sizeof(int)*(size));
        (*returnColumnSizes)[*returnSize]=size;
        (*returnSize)++;
        printf("##### if condition return #### start=%d\n",start);
        return;
    }

    for(int i=start; i<size; i++){
        printf("##### start #### start=%d\ti=%d\n",start,i);
        swap(&nums[start],&nums[i]);
        backtracking(res, returnSize, returnColumnSizes, nums, start+1, size);
        swap(&nums[start],&nums[i]);
        printf("#### end ##### start=%d\ti=%d\n",start,i);
    }
    printf("######### END ######################\n");
}

int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int totalcombination=1;
    for(int i=numsSize;i>0;i--){
        totalcombination *=i;
    }

    *returnSize=0;
    int **res = (int**)malloc(sizeof(int*)*totalcombination);
    (*returnColumnSizes)=(int*)malloc(sizeof(int)*totalcombination);
    qsort(nums, numsSize, sizeof(int), compare);
    backtracking(res, returnSize, returnColumnSizes, nums, 0, numsSize);
    return res;
}

int main() {
   
    //int nums[] = {1,1,2};
    int nums[] = {1,2,3};
    int numsSize = sizeof(nums)/sizeof(nums[0]);
    int i=0,j=0,row=0,clmn=0;
    int* returnSize=&row;
    int* returnColumnSizes;
    int **p;
    
    p = permuteUnique(nums, numsSize, returnSize, &returnColumnSizes);
    
    //printf("\nreturnSize=%d\treturnColumnSizes=%d\n",*returnSize,*returnColumnSizes);
    
    //printf("row=%d\tclmn=%d\n", row,clmn);
    for(int i=0; i<*returnSize; i++){
        //printf("row=%d\tcol=%d\n",*returnSize,*returnColumnSizes);
        for(int j=0; j<*returnColumnSizes; j++){
            printf("%d\t",p[i][j]);
        }
        returnColumnSizes++;
        printf("\n");
    }
    
    return 0;
}
