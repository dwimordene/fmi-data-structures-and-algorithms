#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    void generateMultisetPermutations(const vector<int>& nums, vector<int>& current,
        vector<uint8_t>& used, vector<vector<int>>& permutations) {
        if (current.size() == nums.size()) {
            permutations.push_back(current);

            return;
        }

        bool isValueProcessed = false;
        int lastSeenValue = -1;

        for (size_t i = 0; i < nums.size(); ++i) {
            if (!used[i] &&
                (!isValueProcessed || lastSeenValue != nums[i])) {
                current.push_back(nums[i]);
                used[i] = 1;

                isValueProcessed = true;
                lastSeenValue = nums[i];

                generateMultisetPermutations(nums, current,
                    used, permutations);

                current.pop_back();
                used[i] = 0;
            }
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> current;
        vector<uint8_t> used(nums.size(), 0);
        vector<vector<int>> permutations;

        generateMultisetPermutations(nums, current, used, permutations);

        return permutations;
    }
};

int main() {
    Solution s;
    vector<int> nums = { 1, 1, 2 };
    vector<vector<int>> permutations = s.permuteUnique(nums);

    cout << "Unique permutations for {1, 1, 2}:\n";

    for (const vector<int>& permutation : permutations) {
        cout << "(";

        for (size_t i = 0; i < permutation.size(); ++i) {
            cout << permutation[i];

            if (i + 1 < permutation.size()) cout << ", ";
        }

        cout << ")\n";
    }

    return 0;
}