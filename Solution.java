
import java.util.Arrays;

public class Solution {

    private record Element(int value, int costOfChange){}
    private Element[] elements;
    private int totalElements;

    public long minCost(int[] inputValues, int[] costOfChange) {
        totalElements = inputValues.length;
        elements = new Element[totalElements];

        long suffixSumCost = 0;
        long currentCostToMakeAllElementsEqual = 0;

        for (int i = 0; i < totalElements; ++i) {
            currentCostToMakeAllElementsEqual += (long) inputValues[i] * costOfChange[i];
            suffixSumCost += costOfChange[i];
            elements[i] = new Element(inputValues[i], costOfChange[i]);
        }
        Arrays.sort(elements, (x, y) -> x.value - y.value);

        return calculateMinCostToMakeAllElementsEqual(suffixSumCost, currentCostToMakeAllElementsEqual);
    }

    private long calculateMinCostToMakeAllElementsEqual(long suffixSumCost, long currentCostToMakeAllElementsEqual) {

        currentCostToMakeAllElementsEqual -= elements[0].value * suffixSumCost;
        long prefixSumCost = elements[0].costOfChange;
        suffixSumCost -= elements[0].costOfChange;

        long minCostToMakeAllElementsEqual = currentCostToMakeAllElementsEqual;

        for (int i = 1; i < totalElements; ++i) {
            currentCostToMakeAllElementsEqual += (elements[i].value - elements[i - 1].value) * (prefixSumCost - suffixSumCost);
            minCostToMakeAllElementsEqual = Math.min(minCostToMakeAllElementsEqual, currentCostToMakeAllElementsEqual);

            prefixSumCost += elements[i].costOfChange;
            suffixSumCost -= elements[i].costOfChange;
        }
        return minCostToMakeAllElementsEqual;
    }
}
