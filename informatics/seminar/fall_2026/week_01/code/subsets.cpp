#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> current;
        vector<vector<int>> subsets;

        generateSubsets(nums, 0, current, subsets);

        return subsets;
    }

private:
    void generateSubsets(const vector<int>& nums, unsigned int i,
        vector<int>& current, vector<vector<int>>& subsets) {
        if (i == nums.size()) {
            subsets.push_back(current);

            return;
        }

        // Include the current element
        current.push_back(nums[i]);
        generateSubsets(nums, i + 1, current, subsets);

        // Exclude the current element (backtrack)
        current.pop_back();
        generateSubsets(nums, i + 1, current, subsets);
    }
};