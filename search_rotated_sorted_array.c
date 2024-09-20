class Solution {
public:
    bool search(vector<int>& nums, int target) {
        
        int left=0,right=0;
        bool result = false;
        
        if(nums.size() == 0)
           return false;
        
        if(nums.size()>1){
            //removeduplicate(nums);
            vector<int>::iterator ip;
            ip = unique(nums.begin(), nums.end());
            nums.resize(distance(nums.begin(), ip));
        }
            
        if(nums.size() == 1){
            if(nums[0] == target)
                return true;
            else
                return false;
        }
        
        right=  nums.size()-1;
            
        int pivot = findpivot(nums, left, right);
        
        if(nums[pivot] == target)
            return true;
        
        if(pivot == -1 || pivot == 0){
            result = binarysearch(nums, left, right, target);
            return result;
        }
        
        if(nums[0] <= target){
            result = binarysearch(nums, left, pivot-1, target);
        }
        else{
            result = binarysearch(nums, pivot+1, right, target);
        }
        
        return result;    
    }
    
    void removeduplicate(vector<int>& nums){
        int j=0;
        int i=0;
        int n = nums.size();
        vector<int> unums(n-1,0);
        
        for(i=0; i<nums.size()-1; i++){
            if(nums[i] != nums[i+1]){ 
                // loop iterate less n-1 as checking [i+1]th veriable
                unums[j++] = nums[i];
            }
        }
        
        unums[j++] = nums[i];
        if( j != n)
            nums.resize(j);
        
        for(i=0; i<j; i++){
            nums[i] = unums[i];
        }
    }
    
    int findpivot(vector<int>& nums, int left, int right){
        
        if(right<left || left>right)
            return -1;
        
        if(right == left)
            return 0;
           
        int mid = (right+left)/2;
        
        if(mid+1<= (nums.size()-1) && nums[mid] > nums[mid+1])
            return mid;
        if(mid-1>=0 && nums[mid-1] > nums[mid])
            return mid-1;
        
        if(nums[left] <= nums[mid])
            return findpivot(nums, mid+1, right);
        else
            return findpivot(nums, left, mid-1);
    }
    
    bool binarysearch(vector<int>& nums, int left, int right, int target){
        
        if(right<left || left>right)
            return false;
        
        //if(right == left)
          //  return false;
        
        int mid = (left+right)/2;
        
        if(nums[mid] == target)
            return true;
        
        if(mid-1>=0 && nums[mid-1] == target){
            return true;
        }
        
        if(mid+1<= (nums.size()-1) && nums[mid+1] == target){
            return true;
        }
        
        if(nums[mid] < target)
            return binarysearch( nums, mid+1, right, target);
        else
            return binarysearch( nums, left, mid-1, target);
    }
    
};
