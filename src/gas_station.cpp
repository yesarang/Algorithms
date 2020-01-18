/*
Gas Station

Average Rating: 4.77 (26 votes)
March 12, 2019  |  17.6K views

There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1.

Note:

    If there exists a solution, it is guaranteed to be unique.
    Both input arrays are non-empty and have the same length.
    Each element in the input arrays is a non-negative integer.

Example 1:

Input:
gas  = [1,2,3,4,5]
cost = [3,4,5,1,2]

Output: 3

Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.

Example 2:

Input:
gas  = [2,3,4]
cost = [3,4,3]

Output: -1

Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.
*/

#include <iostream>
#include <vector>

using namespace std;

int where_to_start_car_trip(const vector<int>& gas, const vector<int>& cost) {
    int trip_gas_in_tank = 0;
    int cur_gas_in_tank = 0;
    int start = 0;

    for (int i = 0; i < gas.size(); ++i) {
        if (cur_gas_in_tank < 0) {
            cur_gas_in_tank = 0;
            start = i;
        }

        trip_gas_in_tank += gas[i] - cost[i];
        cur_gas_in_tank += gas[i] - cost[i];
    }

    return trip_gas_in_tank >= 0 ? start : -1;
}

int main() {
    auto gas = vector<int>{ 1, 2, 3, 4, 5 };
    auto cost = vector<int>{ 3, 4, 5, 1, 2 };

    cout << where_to_start_car_trip(gas, cost) << endl;

    cost = { 4, 1, 5, 3, 2 };

    cout << where_to_start_car_trip(gas, cost) << endl;

    cost = { 1, 2, 3, 4, 5 };

    cout << where_to_start_car_trip(gas, cost) << endl;

    cost = { 1, 1, 1, 6, 10 };

    cout << where_to_start_car_trip(gas, cost) << endl;
}
