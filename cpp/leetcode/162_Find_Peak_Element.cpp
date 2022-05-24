class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if(nums.size() == 1) return 0;
        if(nums.size() == 2) return nums[0] > nums[1]? 0:1;
        
        int low = 0, high = nums.size();
        
        while(low <= high){
            int mid = low + (high - low) / 2;
            
            if(mid == 0)
                return mid;
            if(mid == nums.size() -1)
                return nums[mid] > nums[mid-1]? mid : mid - 1;
            
            if(nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1])
                return mid;
            else if(nums[mid-1] > nums[mid]){
                high = mid;
            }
            else{
                low = mid + 1;
            }
                    
            
        }
        
        return nums[low];
    }
};