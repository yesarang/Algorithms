#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>
#include <array>
#include <vector>
#include <atomic>
#include <future>
#include <algorithm>
#include <cassert>

using namespace std;

class ConcurrentQueue {
private:
	queue<int> q_;
	condition_variable cv_;
	mutex m_;

public:
	ConcurrentQueue() : q_(), cv_(), m_() {}

	void enqueue(int v) {
		{
			unique_lock<mutex> lck(m_);
			q_.push(v);
		}
		cv_.notify_all();
	}

	int dequeue() {
		unique_lock<mutex> lck(m_);
		cv_.wait(lck, [&]() { return !q_.empty(); });
		auto r = q_.front();
		q_.pop();
		return r;
	}
};

ConcurrentQueue cq;
static const int NTHR = 100;
atomic_int nprod = 0;

int produce() {
	static thread_local mt19937_64 gen;
	uniform_int_distribution<> dis(1, 50);
	this_thread::sleep_for(chrono::milliseconds(dis(gen)));

	for (int i = 1; i <= 1000; ++i) {
		if (i % 100 == 0) {
			cout << i << " generated" << endl;
		}
		cq.enqueue(i);
	}

	cout << this_thread::get_id() << " done" << endl;

	{
		unique_lock<mutex> lck;
		++nprod;
	}

	return static_cast<int>(nprod);
}

int consume() {
	vector<int> counts(1000);
	while (true) {
		if (auto v = cq.dequeue(); 1 <= v && v <= 1000) {
			++counts[v - 1];
		}
		else {
			break;
		}
	}

	int wrong_count = 0;
	for (int i = 0; i < 1000; ++i) {
		if (counts[i] != NTHR) {
			++wrong_count;
		}
	}

	cout << "wrong count = " << wrong_count << endl;
	cout << this_thread::get_id() << " done" << endl;

	return wrong_count;
}

auto create_producer() {
	return async(launch::async, []() { return produce(); });
}

int main() {
	vector<decltype(create_producer())> producers;
	generate_n(back_inserter(producers), NTHR, create_producer);
	auto ch = async(launch::async, []() { return consume(); });

	for (auto& h : producers) {
		if (h.get() == NTHR) {
			break;
		}
	}
	// send end of data signal
	cq.enqueue(0);

	cout << "waiting for consumer..." << endl;
	assert(ch.get() == 0);

	cout << "press any key to continue" << endl;
	char c;
	cin >> c;
}
