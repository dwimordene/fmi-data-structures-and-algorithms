#include <queue>
#include <vector>

class Solution {
public:
    int numSquares(int n) {
        std::queue<int> states;
        std::vector<bool> visited(n + 1, false);

        states.push(n);
        visited[n] = true;

        int level = 0;

        while (!states.empty()) {
            ++level;
            int size = (int)states.size();

            for (int i = 0; i < size; ++i) {
                int current = states.front();
                states.pop();

                for (int j = 1; j * j <= current; ++j) {
                    int next = current - (j * j);

                    if (next == 0) {
                        return level;
                    }

                    if (!visited[next]) {
                        states.push(next);
                        visited[next] = true;
                    }
                }
            }
        }

        return level;
    }
};