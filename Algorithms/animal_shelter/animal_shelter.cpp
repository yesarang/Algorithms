#include <iostream>
#include <queue>
#include <cassert>
#include <chrono>

using namespace std;

struct animal {
	int id;
	enum class type {
		dog = 0,
		cat
	} type;
};

class animal_shelter {
private:
	struct animal_info {
		animal a;
		chrono::steady_clock::time_point queued_time;
	};

	queue<animal_info> dogq_;
	queue<animal_info> catq_;

public:
	void enqueue(animal a) {
		if (a.type == animal::type::dog) {
			dogq_.push({ a, chrono::steady_clock::now() });
		}
		else {
			catq_.push({ a, chrono::steady_clock::now() });
		}
	}

	animal dequeue_any() {
		queue<animal_info>* which_q = nullptr;
		if (!dogq_.empty() && !catq_.empty()) {
			which_q = dogq_.front().queued_time < catq_.front().queued_time ?
				&dogq_ : &catq_;
		}
		else if (dogq_.empty() && !catq_.empty()) {
			which_q = &catq_;

		}
		else if (catq_.empty() && !dogq_.empty()) {
			which_q = &dogq_;
		}

		if (which_q) {
			auto r = which_q->front().a;
			which_q->pop();
			return r;
		}
		else {
			throw "no animals";
		}
	}
};

int main() {
	animal_shelter as;
	int i = 0;
	as.enqueue(animal{ i++, animal::type::dog });
	as.enqueue(animal{ i++, animal::type::cat });
	as.enqueue(animal{ i++, animal::type::cat });
	as.enqueue(animal{ i++, animal::type::cat });
	as.enqueue(animal{ i++, animal::type::dog });
	as.enqueue(animal{ i++, animal::type::dog });

	auto a = as.dequeue_any();
	assert(a.id == 0 && a.type == animal::type::dog);
	a = as.dequeue_any();
	assert(a.id == 1 && a.type == animal::type::cat);
	a = as.dequeue_any();
	assert(a.id == 2 && a.type == animal::type::cat);
	a = as.dequeue_any();
	assert(a.id == 3 && a.type == animal::type::cat);
	a = as.dequeue_any();
	assert(a.id == 4 && a.type == animal::type::dog);
	a = as.dequeue_any();
	assert(a.id == 5 && a.type == animal::type::dog);
}