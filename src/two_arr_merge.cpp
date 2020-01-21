#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int k = m + n - 1;
    int i = m - 1, j = n - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k--] = nums1[i--];
        }
        else {
            nums1[k--] = nums2[j--];
        }
    }

    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}

template <typename T>
void print(const vector<T>& solution) {
    size_t n = solution.size();
    if (n == 0) {
        cout << "[]" << endl;
        return;
    }

    cout << "[" << solution[0];
    for (size_t i = 1; i < n; ++i) {
        cout << "," << solution[i];
    }
    cout << "]" << endl;
}

int main() {
    vector<int> nums1{ 1,2,3,0,0,0 };
    vector<int> nums2{ 2,5,6 };

    merge(nums1, 3, nums2, 3);

    print(nums1);
}
