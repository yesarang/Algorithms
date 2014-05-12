// 9.8 Given an infinite number of quarters(25 cents), dimes(10 cents), nickels(5
// cents) and pennies(1 cent), write code to calculate the number of ways of representing
// n cents
#include <iostream>
#include <unordered_map>
#include <cassert>

using namespace std;

enum ChgType {
	QUARTER = 25,
	DIME = 10,
	NICKEL = 5,
	PENNY = 1
};

long long count_chg_ways_impl(int rem_chg, ChgType cur_chg_type) {
	long long nways = 0;
	switch (cur_chg_type) {
	case QUARTER:
		for (int i = 0; i <= rem_chg / cur_chg_type; ++i) {
			nways += count_chg_ways_impl(rem_chg - i * QUARTER, DIME);
		}
		return nways;

	case DIME:
		for (int i = 0; i <= rem_chg / cur_chg_type; ++i) {
			nways += count_chg_ways_impl(rem_chg - i * DIME, NICKEL);
		}
		return nways;

	case NICKEL:
		return rem_chg / cur_chg_type + 1;

	default:
		assert(!"This should not happen");
		return -1;
	}
}

long long count_chg_ways(int chg) {
	if (chg >= QUARTER) {
		return count_chg_ways_impl(chg, QUARTER);
	}
	else if (chg >= DIME) {
		return count_chg_ways_impl(chg, DIME);
	}
	else if (chg >= NICKEL) {
		return count_chg_ways_impl(chg, NICKEL);
	}
	else {
		return 1;
	}
}

#if 0
long long count_chg_ways_dp_impl(int rem_chg, ChgType cur_chg_type, unordered_map<long long, long long>& ways) {
	long long nways = 0;
	int new_rem_chg;
	long long key;
	switch (cur_chg_type) {
	case QUARTER:
		for (int i = 0; i <= rem_chg / cur_chg_type; ++i) {
			new_rem_chg = rem_chg - i * QUARTER;
			key = new_rem_chg << 5 | DIME;
			if (ways.find(key) == ways.end()) {
				ways[key] = count_chg_ways_dp_impl(new_rem_chg, DIME, ways);
			}
			nways += ways[key];
		}
		return nways;

	case DIME:
		for (int i = 0; i <= rem_chg / cur_chg_type; ++i) {
			new_rem_chg = rem_chg - i * DIME;
			key = new_rem_chg << 5 | NICKEL;
			if (ways.find(key) == ways.end()) {
				nways += count_chg_ways_dp_impl(new_rem_chg, NICKEL, ways);
			}
			nways += ways[key];
		}
		return nways;

	case NICKEL:
		return rem_chg / cur_chg_type + 1;

	default:
		assert(!"This should not happen");
		return -1;
	}
}

long long count_chg_ways_dp(int chg) {
	unordered_map<long long, long long> ways;
	if (chg >= QUARTER) {
		return count_chg_ways_dp_impl(chg, QUARTER, ways);
	}
	else if (chg >= DIME) {
		return count_chg_ways_dp_impl(chg, DIME, ways);
	}
	else if (chg >= NICKEL) {
		return count_chg_ways_dp_impl(chg, NICKEL, ways);
	}
	else {
		return 1;
	}
}
#endif

int main() {
	int changes = 1;
	for (; changes <= 100; ++changes) {
		cout << "For " << changes << ": " << count_chg_ways(changes) << endl;
	}

	changes = 200;
	cout << "For " << changes << ": " << count_chg_ways(changes) << endl;

	changes = 100000;
	cout << "For " << changes << ": " << count_chg_ways(changes) << endl;

	// changes = 100000;
	// cout << "For " << changes << ": " << count_chg_ways_dp(changes) << endl;

	return 0;
}