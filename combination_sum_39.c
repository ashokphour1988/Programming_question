/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
void backtracking(int **res, int* candidates, int candidatesSize, int* returnSize, int** returnColumnSizes, int target, int *current, int currentidx, int start, int total){
    if(total == target){
        res[*returnSize]=(int*)malloc(sizeof(int)*(currentidx));
        memcpy(res[*returnSize], current, sizeof(int)*currentidx);
        (*returnColumnSizes)[*returnSize]=currentidx;
        (*returnSize)+=1;      
        return;
    }

    for(int i=start; i<candidatesSize;i++){
        
        total+=candidates[i];
        if(total<=target){
            current[currentidx]=candidates[i];
            backtracking(res, candidates, candidatesSize, returnSize, returnColumnSizes, target, current, currentidx+1, i, total);
            
        }      
        total-=candidates[i];
    }
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

    for(i=0;i<candidatesSize;i++){
        if(candidates[i]<target){    //element smaller than target will be consider for combination
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








/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
struct node{
    int* val;
    int size;
    struct node* next;
};
struct Stack{
    struct node* top;
    int size;
};
int sum(int* array,int arraySize){
    int sum=0;
    for(int i=0;i<arraySize;i++){
        sum+=array[i];
    }
    return sum;
}
void push(struct Stack* stack,int* array,int arraySize){
    //create a new array to copy the previous elements
    int* newArray=malloc(arraySize*sizeof(int));
    for(int i=0;i<arraySize;i++){
        newArray[i]=array[i];
    }
    //push the new array to stack
    struct node* newNode=malloc(sizeof(struct node));
    newNode->val=newArray;
    newNode->size=arraySize;
    newNode->next=stack->top;
    stack->top=newNode;
    stack->size++;
}
int* pop(struct Stack* stack){
    stack->size--;
    int* result=stack->top->val;
    stack->top=stack->top->next;
    return result;
}
void backtrack(struct Stack* stack,int* combination,int combinationSize,int* candidates,int candidatesSize,int target,int startIndex){
    if(sum(combination,combinationSize)==target){
        push(stack,combination,combinationSize);
        return;
    }else if(sum(combination,combinationSize)>target || combinationSize>=target){
        return;
    }
    for(int i=startIndex;i<candidatesSize;i++){
        combination[combinationSize]=candidates[i];
        backtrack(stack,combination,combinationSize+1,candidates,candidatesSize,target,i); //not i+1 because we can reuse the same elements
    }
}
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    //create a stack
    struct Stack stack;
    stack.top=NULL; stack.size=0;
    //create a temporary array to store one combination. The max size of the array is target, assuming the smallest candidate is 1, there will be target/1=target number of elements in each combination
    int *combination=malloc(target*sizeof(int));
    backtrack(&stack,combination,0,candidates,candidatesSize,target,0);
    //create a new list to contain all combinations to return
    //transfer the combinations from stack to the list
    int** returnList=malloc(stack.size*sizeof(int*));
    *returnSize=stack.size;
    *returnColumnSizes=malloc(stack.size*sizeof(int));
    for(int i=0;i<*returnSize;i++){
        *(*returnColumnSizes+i)=(stack.top)->size;
        returnList[i]=pop(&stack);
    }
    return returnList;
}

