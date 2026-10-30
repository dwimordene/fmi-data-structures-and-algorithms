#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Solution {
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

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> current;
        vector<vector<int>> subsets;

        generateSubsets(nums, 0, current, subsets);

        return subsets;
    }
};

int main() {
    try {
        Solution s;
        vector<int> nums = { 1, 2, 3 };
        vector<vector<int>> subsets = s.subsets(nums);

        cout << "Subsets for {1, 2, 3}:\n";

        for (const vector<int>& subset : subsets) {
            cout << "{";

            for (size_t i = 0; i < subset.size(); ++i) {
                cout << subset[i];

                if (i + 1 < subset.size()) cout << ", ";
            }

            cout << "}\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "[Caught Exception]: " << e.what() << std::endl;
    }

    return 0;
}