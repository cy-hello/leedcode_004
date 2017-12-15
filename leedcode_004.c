题目信息：
Median of Two Sorted Arrays

如果不考虑编程，我们都能想到方法：
1 把2个数组合并成一个数组
2 然后按照从大到小或者从小到大的顺序排序
3 分类：判断合并后的数组的元素个数是奇数还是偶数
4 如果是奇数：取中间值；如果是偶数取中间2个数的平均值

class Solution {  
public:  
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2){  
        vector<int> nums;  
        if (nums1.size() > nums2.size()){  
            nums = nums1;  
            for (unsigned int i = 0; i < nums2.size(); ++i){  
                nums.push_back(nums2[i]);  
            }  
        }  
        else{  
            nums = nums2;  
            for (unsigned int i = 0; i < nums1.size(); ++i){  
                nums.push_back(nums1[i]);  
            }  
        }  
		
        sort(nums.begin(), nums.end());  
        if (nums.size() & true){  
            return nums[nums.size() / 2]; 
        }  
        else{  
            return (nums[nums.size() / 2] + nums[(nums.size() / 2) - 1]) / 2.0;  
        }  
    }  
}; 


但是题目要求的时间复杂度是O(log(m+n))，虽然能通过，不符合题目要求；

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        const int m = nums1.size();		/*取数组1的长度*/
        const int n = nums2.size();		/*取数组2的长度*/
        int total = m + n;
        if (total & 0x1)               /*数组总数是偶数*/
            return find_kth(nums1.begin(), m, nums2.begin(), n, total / 2 + 1);
        else                           /*数组总数是奇数*/
            return (find_kth(nums1.begin(), m, nums2.begin(), n, total / 2)+ find_kth(nums1.begin(), m, nums2.begin(), n, total / 2 + 1)) / 2.0;
    }
    private:
        static int find_kth(std::vector<int>::const_iterator nums1, int m,
        std::vector<int>::const_iterator nums2, int n, int k) {
        //always assume that m is equal or smaller than n
        if (m > n) return find_kth(nums2, n, nums1, m, k);
        if (m == 0) return *(nums2 + k - 1);
        if (k == 1) return min(*nums1, *nums2);
        //divide k into two parts
        int ia = min(k / 2, m), ib = k - ia;
        if (*(nums1 + ia - 1) < *(nums2 + ib - 1))
            return find_kth(nums1 + ia, m - ia, nums2, n, k - ia);
        else if (*(nums1 + ia - 1) > *(nums2 + ib - 1))
            return find_kth(nums1, m, nums2 + ib, n - ib, k - ib);
        else
            return nums1[ia - 1];
    }
};