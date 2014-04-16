// check out whether this code works properly at http://ideone.com/QebiEj
#include <iostream>
#include <queue>
#include <string>
#include <cstdio>

using namespace std;

typedef unsigned Disc;
typedef string Tower;
struct DiscMove {
	Disc d_;
	string from_;
	string to_;
	DiscMove(Disc d, string from, string to)
		: d_(d), from_(from), to_(to)
	{}
};

Tower A("A"), B("B"), C("C");
queue<DiscMove> moves;

void solve(const Tower& source, const Tower& temp, const Tower& target, Disc upto) {
	// if we have only one disc to move, we can't divide the task
	if (upto == 1) {
		moves.push(DiscMove(upto, source, target));
		return;
	}
	solve(source, target, temp, upto - 1);
	moves.push(DiscMove(upto, source, target));
	solve(temp, source, target, upto - 1);
}

int main() {
	for (int i = 1; i <= 5; ++i) {
		printf("Moving %d discs from %s to %s\n", i, A.c_str(), C.c_str());
		solve(A, B, C, i);
		while (!moves.empty()) {
			DiscMove dm = moves.front();
			moves.pop();
			printf("%d: %s -> %s\n", dm.d_, dm.from_.c_str(), dm.to_.c_str());
		}
	}

	return 0;
}
