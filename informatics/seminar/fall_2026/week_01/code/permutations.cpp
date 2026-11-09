#include <cstdint>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> current;
        vector<uint8_t> used(nums.size(), 0);
        vector<vector<int>> permutations;

        generatePermutations(nums, current, used, permutations);

        return permutations;
    }

private:
    void generatePermutations(const vector<int>& nums, vector<int>& current,
        vector<uint8_t>& used, vector<vector<int>>& permutations) {
        if (current.size() == nums.size()) {
            permutations.push_back(current);

            return;
        }

        for (size_t i = 0; i < nums.size(); ++i) {
            if (!used[i]) {
                current.push_back(nums[i]);
                used[i] = 1;

                generatePermutations(nums, current, used, permutations);

                current.pop_back();
                used[i] = 0;
            }
        }
    }
};