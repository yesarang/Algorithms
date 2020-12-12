/*
Leetcode: https://leetcode.com/problems/sliding-window-median/

480. Sliding Window Median
Median is the middle value in an ordered integer list. If the size of the list is even,
there is no middle value. So the median is the mean of the two middle value.

Examples:
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Given an array nums, there is a sliding window of size k which is moving
from the very left of the array to the very right.
You can only see the k numbers in the window.
Each time the sliding window moves right by one position.
Your job is to output the median array for each window in the original array.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Median
---------------               -----
[1  3  -1] -3  5  3  6  7       1
 1 [3  -1  -3] 5  3  6  7       -1
 1  3 [-1  -3  5] 3  6  7       -1
 1  3  -1 [-3  5  3] 6  7       3
 1  3  -1  -3 [5  3  6] 7       5
 1  3  -1  -3  5 [3  6  7]      6
Therefore, return the median sliding window as [1,-1,-1,3,5,6].

Note:
You may assume k is always valid, ie: k is always smaller than input array's size for non-empty array.
Answers within 10^-5 of the actual value will be accepted as correct.
*/

#include <iostream>
#include <vector>
#include <set>
#include <optional>
#include <queue>

using namespace std;

class data_stream {
    vector<int> data_;
    mutable size_t next_;

public:
    data_stream(vector<int>&& data)
        : data_(data)
        , next_(0)
    {}

    optional<int> get() const
    {
        return next_ < data_.size() ? make_optional(data_[next_++]) : nullopt;
    }
};

class stream_median {
    data_stream strm_;
    const size_t win_size_;
    mutable multiset<int> win_;
    mutable multiset<int>::const_iterator med_pos;
    mutable queue<multiset<int>::const_iterator> q;

public:
    stream_median(const data_stream& strm, size_t win_size)
        : strm_(strm)
        , win_size_(win_size)
        , win_()
        , med_pos()
        , q()
    {
        while (win_.size() < win_size_) {
            auto datum = strm_.get();
            if (datum.has_value()) {
                q.push(win_.insert(datum.value()));
            }
            else {
                break;
            }
        }

        if (win_.size() == win_size_) {
            med_pos = next(win_.cbegin(), (win_size_ - 1) / 2);
        }
        else {
            med_pos = win_.cend();
        }
    }

    optional<double> get() const
    {
        if (med_pos == win_.end()) {
            return nullopt;
        }

        auto r = win_size_ % 2
            ? static_cast<double>(*med_pos)
            : (static_cast<double>(*med_pos) + *(next(med_pos))) / 2.0;

        int adj = 0;

        auto datum = strm_.get();
        if (datum.has_value()) {
            auto new_val = datum.value();
            q.push(win_.insert(new_val));

            if (new_val >= *med_pos) {
                ++adj;
            }
            else {
                --adj;
            }

			if (q.front() == med_pos) {
                if (med_pos != win_.cbegin()) {
                    --med_pos;
                }
                else {
                    med_pos = win_.cend();
                }
				++adj;
			}
			else if (*q.front() <= *med_pos) {
				++adj;
			}
			else {
				--adj;
			}
			win_.erase(q.front());
			q.pop();

            if (med_pos == win_.cend()) {
                med_pos = win_.cbegin();
            }
            else {
                med_pos = next(med_pos, adj / 2);
            }
        }
        else {
            med_pos = win_.cend();
        }

        return r;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const optional<T>& opt)
{
    if (opt.has_value()) {
        os << opt.value();
    }
    else {
        os << "null";
    }

    return os;
}

int main()
{
    stream_median smed(vector<int>{ 1,3,-1,-3,5,3,6,6 }, 3);

    cout << smed.get() << endl;
    cout << smed.get() << endl;
    cout << smed.get() << endl;
    cout << smed.get() << endl;
    cout << smed.get() << endl;
    cout << smed.get() << endl;
    cout << smed.get() << endl;

    stream_median smed2(vector<int>{ 1,2,3 }, 1);

    cout << smed2.get() << endl;
    cout << smed2.get() << endl;
    cout << smed2.get() << endl;
    cout << smed2.get() << endl;

    stream_median smed3(vector<int>{4, 1, 7, 1, 8, 7, 8, 7, 7, 4}, 4);
    cout << smed3.get() << endl;
    cout << smed3.get() << endl;
    cout << smed3.get() << endl;
    cout << smed3.get() << endl;
    cout << smed3.get() << endl;
    cout << smed3.get() << endl;
    cout << smed3.get() << endl;
    cout << smed3.get() << endl;
}

