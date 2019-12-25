#include <iostream>
#include <vector>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;

template <typename T, typename OrderComparer = less<T>>
class MyHeap {
private:
	mutable vector<T> data_;
	OrderComparer comp_;

public:
	MyHeap(OrderComparer comp = OrderComparer()) : data_(), comp_(comp) {}
	MyHeap(const MyHeap& other) : data_(other.data_), comp_(other.comp_) {}

	bool empty() const {
		return data_.empty();
	}

	void push(T v) {
		data_.push_back(v);
		auto ni = data_.size() - 1;
		while (ni > 0) {
			auto pi = (ni - 1) / 2;
			if (comp_(data_[ni], data_[pi])) {
				swap(data_[ni], data_[pi]);
				ni = pi;
			}
			else {
				break;
			}
		}
	}

	T pop() {
		auto r = data_[0];
		swap(data_[0], data_[data_.size() - 1]);
		data_.pop_back();
		auto i = static_cast<size_t>(0);
		while (2 * i + 1 < data_.size()) {
			auto lci = 2 * i + 1, rci = 2 * i + 2;
			auto ci = lci;
			if (rci < data_.size()) {
				ci = comp_(data_[lci], data_[rci]) ? lci : rci;
			}
			
			if (comp_(data_[ci], data_[i])) {
				swap(data_[ci], data_[i]);
				i = ci;
			}
			else {
				break;
			}
		}

		return r;
	}

	const vector<int> data() const { return data_; }

	vector<int> sort() const {
		MyHeap copy(*this);
		vector<int> r;
		while (!copy.empty()) {
			r.push_back(copy.pop());
		}
		return move(r);
	}
};

ostream& operator<<(ostream& os, const vector<int>& v) {
	for (auto d : v) {
		os << d << " ";
	}

	return os;
}

template <typename T, typename C>
ostream& operator<<(ostream& os, const MyHeap<T, C>& h) {
	for (auto d : h.data()) {
		os << d << " ";
	}

	return os;
}

int main() {
	MyHeap<int> min_heap;

	for (auto v : { 4,50,55,90,87,7,2 }) {
		min_heap.push(v);
	}

	cout << min_heap.data() << endl;

	while (!min_heap.empty()) {
		cout << min_heap.pop() << " ";
	}
	cout << endl;

	vector<int> v;
	generate_n(back_inserter(v), 10, rand);

	MyHeap<int> h1;
	cout << "pushing... " << v << endl;
	for (auto d : v) {
		h1.push(d);
	}

	cout << h1 << endl;
	cout << h1.sort() << endl;

	MyHeap<int, greater<int>> h2;
	cout << "pushing... " << v << endl;
	for (auto d : v) {
		h2.push(d);
	}

	cout << h2 << endl;
	cout << h2.sort() << endl;

}
