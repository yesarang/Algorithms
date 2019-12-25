#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <iterator>
#include <algorithm>
#include <tuple>

using namespace std;

uint32_t find_missing_int(vector<uint32_t>& v) {
	vector<bool> does_exist(v.size());
	for (auto i : v) {
		does_exist[i] = true;
	}

	for (auto i = 0; i < v.size(); ++i) {
		if (!does_exist[i]) {
			return i;
		}
	}

	return 0;
}

class missing_int_iterator {
public:
	struct iter {
		missing_int_iterator& mi_iter_;
		size_t c_;
		size_t i_;

		void next() {
			while (i_ < mi_iter_.size_ && mi_iter_.does_exist_[i_]) {
				++i_;
			}
			c_ = i_;
			++i_;
		}

		iter(missing_int_iterator& mi_iter, size_t i = 0) : mi_iter_(mi_iter), c_(i), i_(i) {
			next();
		}

		iter& operator++() {
			next();
			return *this;
		}

		uint32_t& operator*() {
			return c_;
		}

		bool operator==(const iter& rhs) {
			return &(this->mi_iter_) == &(rhs.mi_iter_) &&
				this->i_ == rhs.i_ &&
				this->c_ == rhs.c_;
		}

		bool operator!=(const iter& rhs) {
			return !(*this == rhs);
		}
	};

	missing_int_iterator(const vector<uint32_t>& v)
		: size_(v.size())
		, does_exist_(size_)
	{
		for (auto i : v) {
			does_exist_[i] = true;
		}
	}

	iter begin() {
		return iter(*this);
	}

	iter end() {
		return iter(*this, size_);
	}

private:
	const size_t size_;
	vector<bool> does_exist_;

	friend struct iter;
};

template<>
struct std::iterator_traits<missing_int_iterator::iter> {
	using iterator_category = forward_iterator_tag;
};

int main() {
	vector<uint32_t> v;
	generate_n(back_inserter(v), 10, []() {
		return rand() % 10 ;
	});
	cout << "[ ";
	copy(v.begin(), v.end(), ostream_iterator<uint32_t>(cout, " "));
	cout << "]" << endl;

	cout << find_missing_int(v) << " is missing" << endl;

	missing_int_iterator mi_iter(v);
	for_each(mi_iter.begin(), mi_iter.end(), [](auto& v) {
		cout << v << " is missing" << endl;
	});
}
