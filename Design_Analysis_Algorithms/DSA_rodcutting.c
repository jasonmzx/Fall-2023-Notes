#include <stdio.h>

//* ----- Memoized Entry, storing the Optimal Prices to sell at, for length  -----

struct bestCut {
    int maxPrice;
    int bestCutLength;
};

int rodCutting(int length, int priceList[], struct bestCut memo[], int n) {
    
    //* BASE CASE: If the length is 0 (or negative but it shouldn't be) means...
    // The rod's length has been fully partitioned out!
    if (length <= 0) {
        return 0;
    }

    // Memoization check: If the best price for this length has already been computed, return it to avoid redundant calculations.
    if (memo[length].maxPrice != -1) {
        return memo[length].maxPrice;
    }


    int maxVal = -1; //* init at low value, so it gets initially reset in for loop

    //! Start at 1, as 0 is garbage *(I is length in inches!)*
    for (int i = 1; i < n; i++) {

        //If Incoming length (rod length) is greater than the current length from the Price List, we know it could be composed as:
        if (length >= i) {

            //* VAL = << Price of Sub-Rod Piece of len: Pi >> + 
            //*       << Recursion, of Len: (Length-Pi), given priceList, memoizedTable, and propagated n. >> 
            // Calculate the total price for this cut:
            // Which is the sum of the price of this piece and the best price for the remaining length of the rod.

            int val = priceList[i] + rodCutting(length - i, priceList, memo, n);
            // Update maxVal if this cut leads to a better price than what we have found so far.
            if (val > maxVal) {
                maxVal = val;
                memo[length].bestCutLength = i; // Store the length of the cut that gave the best price.
            }
        }
    }

    memo[length].maxPrice = maxVal;
    return maxVal;
}

void initializeMemoizationTable(struct bestCut memo[], int length) {
    for (int i = 0; i <= length; i++) {
        memo[i].maxPrice = -1;
        memo[i].bestCutLength = 0;
    }
}

void printCutRodSolution(struct bestCut memo[], int rodLength) {
    while (rodLength > 0) {
        int cut = memo[rodLength].bestCutLength;
        printf("Cut: %d inches\n", cut);
        rodLength -= cut;
    }
}

void printMemoizationTable(struct bestCut memo[], int length) {
    printf("\nMemoization Table:\n");
    printf("Length | Max Price | Best Cut Length\n");
    printf("-------|-----------|----------------\n");

    for (int i = 1; i <= length; i++) {
        printf("%6d | %9d | %14d\n", i, memo[i].maxPrice, memo[i].bestCutLength);
    }
}


//PREDEFINED CONSTANT

#define PRICE_TABLE_LENGTH 10

int main() {
                                        //    X, 1, 2, 3, 4, 5,  6,  7,  8,  9,  10
    int priceList[PRICE_TABLE_LENGTH + 1] = {-1, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    int rodLength = 10;

    //* Allocate and Initialize Memoized Table, holding "Optimal" solutions for all lengths
    struct bestCut memoizedTable[rodLength + 1];
    initializeMemoizationTable(memoizedTable, rodLength);

    //* Actual Algorithm call
    int result = rodCutting(rodLength, priceList, memoizedTable, PRICE_TABLE_LENGTH);

    printf("Maximum obtainable price is: $%d\n", result);
    printf("Cuts used to achieve this price:\n");
    printCutRodSolution(memoizedTable, rodLength);

    // Call the new function to print the memoization table
    printMemoizationTable(memoizedTable, rodLength);


    return 0;
}
