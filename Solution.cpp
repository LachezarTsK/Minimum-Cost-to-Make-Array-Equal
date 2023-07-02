
#include <vector>
#include <algorithm>
using namespace std;

class Solution {

    struct Element {
        int value;
        int costOfChange;
        Element(int value, int costOfChange) : value{value}, costOfChange{costOfChange}{}
    };

    vector<Element> elements;
    size_t totalElements;

public:
    long long minCost(const vector<int>& inputValues, const vector<int>& costOfChange) {
        totalElements = inputValues.size();

        long long suffixSumCost = 0;
        long long currentCostToMakeAllElementsEqual = 0;

        for (int i = 0; i < totalElements; ++i) {
            currentCostToMakeAllElementsEqual += (long long) inputValues[i] * costOfChange[i];
            suffixSumCost += costOfChange[i];
            elements.emplace_back(inputValues[i], costOfChange[i]);
        }
        //C++20: std::ranges::sort(elements,[](const auto& x, const auto& y){return x.value < y.value;});
        sort(elements.begin(), elements.end(), [](const auto& x, const auto& y){return x.value < y.value;});

        return calculateMinCostToMakeAllElementsEqual(suffixSumCost, currentCostToMakeAllElementsEqual);
    }

private:
    long long calculateMinCostToMakeAllElementsEqual(long long suffixSumCost, long long currentCostToMakeAllElementsEqual) const {

        currentCostToMakeAllElementsEqual -= elements[0].value * suffixSumCost;
        long long prefixSumCost = elements[0].costOfChange;
        suffixSumCost -= elements[0].costOfChange;

        long long minCostToMakeAllElementsEqual = currentCostToMakeAllElementsEqual;

        for (int i = 1; i < totalElements; ++i) {
            currentCostToMakeAllElementsEqual += (elements[i].value - elements[i - 1].value) * (prefixSumCost - suffixSumCost);
            minCostToMakeAllElementsEqual = min(minCostToMakeAllElementsEqual, currentCostToMakeAllElementsEqual);

            prefixSumCost += elements[i].costOfChange;
            suffixSumCost -= elements[i].costOfChange;
        }
        return minCostToMakeAllElementsEqual;
    }
};
