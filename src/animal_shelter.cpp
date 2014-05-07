// An animal shelter holds only dogs and cats, and operates on a strictly "first in, first
// out" basis. People must adopt either the "oldest" (based on arrival time) of all animals
// at the shelter, or they can select whether they would prefer a dog or a cat (and will
// receive the oldest animal of that type). They cannot select which specific animal they
// would like. Create the data structures to maintain this system and implement operations
// such as enqueue, dequeueAny, dequeueDog and dequeueCat. You may
// use the built-in list data structure.
#include <iostream>
#include <list>
#include <string>
#include <stdexcept>
#include <cassert>

using namespace std;

class AnimalShelter {
public:
	struct AnimalInfo {
		string name;
		enum { DOG, CAT } type;
	};
private:
	typedef list<AnimalInfo>::iterator IterType;
	list<AnimalInfo> mq_;
	list<IterType> dq_;
	list<IterType> cq_;

public:
	void enqueue(const AnimalInfo& animal_info);
	AnimalInfo dequeueAny();
	string dequeueDog();
	string dequeueCat();
};

void AnimalShelter::enqueue(const AnimalShelter::AnimalInfo& animal_info) {
	mq_.push_back(animal_info);
	if (animal_info.type == AnimalInfo::DOG) {
		dq_.push_back(--(mq_.end()));
	}
	else {
		cq_.push_back(--(mq_.end()));
	}
}

AnimalShelter::AnimalInfo AnimalShelter::dequeueAny() {
	if (mq_.empty()) {
		throw underflow_error("Underflow");
	}
	AnimalInfo r = mq_.front();
	mq_.pop_front();
	if (r.type == AnimalInfo::DOG) {
		dq_.pop_front();
	}
	else {
		cq_.pop_front();
	}

	return r;
}

string AnimalShelter::dequeueDog() {
	if (dq_.empty()) {
		throw underflow_error("Underflow");
	}
	string r = dq_.front()->name;
	mq_.erase(dq_.front());
	dq_.pop_front();
	return r;
}

string AnimalShelter::dequeueCat() {
	if (cq_.empty()) {
		throw underflow_error("Underflow");
	}
	string r = cq_.front()->name;
	mq_.erase(cq_.front());
	cq_.pop_front();
	return r;
}

inline string animal_type(const AnimalShelter::AnimalInfo& ai) {
	return ai.type == AnimalShelter::AnimalInfo::DOG ? "DOG" : "CAT";
}

int main() {
	AnimalShelter::AnimalInfo animal_list[] = {
		{ "AAA", AnimalShelter::AnimalInfo::DOG },
		{ "BBB", AnimalShelter::AnimalInfo::CAT },
		{ "CCC", AnimalShelter::AnimalInfo::DOG },
		{ "DDD", AnimalShelter::AnimalInfo::CAT },
		{ "EEE", AnimalShelter::AnimalInfo::CAT }
	};
	AnimalShelter as;
	for (auto ai : animal_list) {
		as.enqueue(ai);
	}

	AnimalShelter::AnimalInfo ai = as.dequeueAny();
	cout << ai.name << " is a " << animal_type(ai) << endl;
	assert(ai.name == "AAA" && ai.type == AnimalShelter::AnimalInfo::DOG);

	string name{ as.dequeueDog() };
	cout << name << " is a DOG" << endl;
	assert(name == "CCC");

	try {
		name = as.dequeueDog();
	}
	catch (const underflow_error& ex) {
		cout << ex.what() << endl;
	}
	name = as.dequeueCat();
	cout << name << " is a CAT" << endl;
	assert(name == "BBB");
	
	ai = as.dequeueAny();
	cout << ai.name << " is a " << animal_type(ai) << endl;
	assert(ai.name == "DDD" && ai.type == AnimalShelter::AnimalInfo::CAT);

	ai = as.dequeueAny();
	cout << ai.name << " is a " << animal_type(ai) << endl;
	assert(ai.name == "EEE" && ai.type == AnimalShelter::AnimalInfo::CAT);

	try {
		name = as.dequeueCat();
	}
	catch (const underflow_error& ex) {
		cout << ex.what() << endl;
	}
	try {
		ai = as.dequeueAny();
	}
	catch (const underflow_error& ex) {
		cout << ex.what() << endl;
	}

	return 0;
}
