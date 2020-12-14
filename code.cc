#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> partion(vector<int>&nums, int left, int right){
    vector<int> p(2);
    if(nums.size()<0) return p;

    int smaller = left -1;
    int bigger = right;
    int num = nums[right];

    while(left<bigger){
        if(nums[left]<num){
            swap(nums[left],nums[++smaller]);
        }
        else if(nums[left]>num){
            swap(nums[left], nums[--bigger]);
        }
        else{
            left++;
        }
    }
    swap(nums[bigger], nums[right]);
    p[0] = smaller;
    p[1] = bigger;
    return p;
}

void quick(vector<int>&nums, int left, int right){
    if(left<right){
        vector<int> tmp = partion(nums, left, right);
        quick(nums, left, tmp[0]-1);
        quick(nums, tmp[1]+1, right);
    }
}

void quicksort(vector<int>& nums){
    if(nums.size()<2) return;
    quick(nums, 0, nums.size()-1);
}

int main(){
    vector<int>nums = {1,4,3,5,6,10,8,7,9};

    quicksort(nums);

    for(int i=0; i<nums.size(); i++){
        cout<< nums[i] << "  ";
    }
    cout << endl;
    return 0;
}