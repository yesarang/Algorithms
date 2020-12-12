/*
Leetcode: https://leetcode.com/problems/find-median-from-data-stream/

295. Find Median from Data Stream
Median is the middle value in an ordered integer list. If the size of the list is even,
there is no middle value. So the median is the mean of the two middle value.

For example,
[2,3,4], the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the data structure.
double findMedian() - Return the median of all elements so far.

Example:

addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3)
findMedian() -> 2

Follow up:
- If all integer numbers from the stream are between 0 and 100, how would you optimize it?
- If 99% of all integer numbers from the stream are between 0 and 100, how would you optimize it?
*/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class MedianFinder {
    priority_queue<int> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;

public:
    /** initialize your data structure here. */
    MedianFinder()
        : max_heap()
        , min_heap()
    {}

    void addNum(int num) {
        if (max_heap.empty()) {
            max_heap.push(num);
        }
        else if (num <= max_heap.top()) {
			max_heap.push(num);
			if (max_heap.size() > min_heap.size() + 1) {
				min_heap.push(max_heap.top());
				max_heap.pop();
			}
        }
        else {
            min_heap.push(num);
			if (max_heap.size() < min_heap.size()) {
				max_heap.push(min_heap.top());
				min_heap.pop();
			}
        }
    }

    double findMedian() {
        if (max_heap.size() == min_heap.size()) {
            return (max_heap.top() + min_heap.top()) / 2.0;
        }
        else {
            return max_heap.top();
        }
    }
};

int main()
{
    MedianFinder mf;

    mf.addNum(-1);
    cout << mf.findMedian() << endl;
    mf.addNum(-2);
    cout << mf.findMedian() << endl;
    mf.addNum(-3);
    cout << mf.findMedian() << endl;
    mf.addNum(-4);
    cout << mf.findMedian() << endl;
    mf.addNum(-5);
    cout << mf.findMedian() << endl;
}

