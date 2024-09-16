#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
void backtracking(int **res, int* candidates, int candidatesSize, int* returnSize, int** returnColumnSizes, int target, int *current, int currentidx, int start, int total){
    //printf("start=%d\tcurrentidx=%d\ttotal=%d\n",start,currentidx,total);
    if(total == target){
        res[*returnSize]=(int*)malloc(sizeof(int)*(currentidx));
        memcpy(res[*returnSize], current, sizeof(int)*currentidx);
        //printf("currentidx=%d\n",currentidx);
        (*returnColumnSizes)[*returnSize]=currentidx;
        (*returnSize)+=1;      
        return;
    }

    for(int i=start; i<candidatesSize;i++){
        
        total+=candidates[i];
        //printf("######start###### total=%d\tidx=%d\n",total,i);
        if(total<=target){
            current[currentidx]=candidates[i];
            backtracking(res, candidates, candidatesSize, returnSize, returnColumnSizes, target, current, currentidx+1, i, total);
            
        }   
        printf("######back###### idx=%d\n",i);
        total-=candidates[i];
    }
    printf("########end##############################\n");
}

int comparator(const void *p, const void *q){
    int val1 = *(const int*)p;
    int val2 = *(const int*)q;
    return (val1-val2);
}

int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    *returnSize=0; 
    int maxcom=20;
    int count=0;
    int i=0;
    long long int maxcombination;

    qsort(candidates,candidatesSize,sizeof(candidates[0]),comparator);
    printf("candidatesSize=%d\n",candidatesSize);
    /*after sorting skiping elements bigger than target*/
    /*[29,24,20,10,30,38,13,18,22,27,32,14,35,37,26,40,12,28,11,36,39,16,31,23,33,21,34,15,25,19]*/
    for(i=0;i<candidatesSize;i++){
        printf("%d,",candidates[i]);
        if(candidates[i]<target){
            count++;
        }
    }
    
    maxcombination = 1<<(count);
    //printf("candidatesSize=%d\tmaxcombination=%d\ttarget=%d\n",candidatesSize,maxcombination,target);
    int **res = (int**)malloc(sizeof(int*)*maxcombination);
    if(target==1)
        return res;
    
    int *current= (int*)malloc(sizeof(int)*maxcom);
    memset(current,0,sizeof(int)*maxcom);
    (*returnColumnSizes) = (int*)malloc(sizeof(int)*maxcombination);

    backtracking(res, candidates, candidatesSize, returnSize, returnColumnSizes, target, current, 0, 0, 0);
    free(current);
    return res;
}
int main() {
   //int nums[] = {1,1,2,10,30,38,13,18,22,27,32,14,35,37,26,40,12,28,11,36,39,16,31,23,33,21,34,15,25,19};
   int nums[] = {1,1,2};
    int candidatesSize = sizeof(nums)/sizeof(nums[0]);
    int target=3;
    int i=0,j=0,row=0,clmn=0;
    int* returnSize=&row;
    int* returnColumnSizes;
    int **p;
    
    p = combinationSum(nums, candidatesSize, target, returnSize, &returnColumnSizes);
    
    //printf("\nreturnSize=%d\treturnColumnSizes=%d\n",*returnSize,*returnColumnSizes);
    //row = *returnSize;
    clmn=*returnColumnSizes;
    
    printf("row=%d\tclmn=%d\n", row,clmn);
    for(int i=0; i<*returnSize; i++){
        printf("row=%d\tcol=%d\n",*returnSize,*returnColumnSizes);
        for(int j=0; j<*returnColumnSizes; j++){
            printf("%d\t",p[i][j]);
        }
        returnColumnSizes++;
        printf("\n");
    }
    
    return 0;
}
