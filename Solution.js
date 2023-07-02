
/**
 * @param {number[]} inputValues
 * @param {number[]} costOfChange
 * @return {number}
 */
var minCost = function (inputValues, costOfChange) {
    this.totalElements = inputValues.length;
    this.elements = new Array(this.totalElements);

    let suffixSumCost = 0;
    let currentCostToMakeAllElementsEqual = 0;

    for (let i = 0; i < this.totalElements; ++i) {
        currentCostToMakeAllElementsEqual += inputValues[i] * costOfChange[i];
        suffixSumCost += costOfChange[i];
        this.elements[i] = new Element(inputValues[i], costOfChange[i]);
    }
    this.elements.sort((x, y) => x.value - y.value);

    return calculateMinCostToMakeAllElementsEqual(suffixSumCost, currentCostToMakeAllElementsEqual);
};

/**
 * @param {number} value
 * @param {number} costOfChange
 */
function Element(value, costOfChange) {
    this.value = value;
    this.costOfChange = costOfChange;
}

/**
 * @param {number} suffixSumCost
 * @param {number} currentCostToMakeAllElementsEqual 
 * @return {number}
 */
function calculateMinCostToMakeAllElementsEqual(suffixSumCost, currentCostToMakeAllElementsEqual) {

    currentCostToMakeAllElementsEqual -= this.elements[0].value * suffixSumCost;
    let prefixSumCost = this.elements[0].costOfChange;
    suffixSumCost -= this.elements[0].costOfChange;

    let minCostToMakeAllElementsEqual = currentCostToMakeAllElementsEqual;

    for (let i = 1; i < this.totalElements; ++i) {
        currentCostToMakeAllElementsEqual += (elements[i].value - elements[i - 1].value) * (prefixSumCost - suffixSumCost);
        minCostToMakeAllElementsEqual = Math.min(minCostToMakeAllElementsEqual, currentCostToMakeAllElementsEqual);

        prefixSumCost += elements[i].costOfChange;
        suffixSumCost -= elements[i].costOfChange;
    }
    return minCostToMakeAllElementsEqual;
}
