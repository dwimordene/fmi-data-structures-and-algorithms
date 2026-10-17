#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
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

public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> current;
        vector<uint8_t> used(nums.size(), 0);
        vector<vector<int>> permutations;

        generatePermutations(nums, current, used, permutations);

        return permutations;
    }
};

int main() {
    Solution s;
    vector<int> nums = { 1, 2, 3 };
    vector<vector<int>> permutations = s.permute(nums);

    cout << "Permutations for {1, 2, 3}:\n";

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