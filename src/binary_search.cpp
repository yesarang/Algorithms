#include <iostream>

using namespace std;

int*
binary_search(int* start, int* end, int data) {
    if (start >= end) {
        if (data == *start) {
            return start;
        }
        else {
            return 0;
        }
    }
    
    int* middle = start + (end - start) / 2;
    if (data > *middle) {
        return binary_search(middle + 1, end, data);
    }
	else {
        return binary_search(start, middle, data);
	}
}

int main()
{
    int arr[5] = {
        -23, -8, 16, 72, 104
    };
    int* pos = binary_search(arr, &arr[4], 104);
    if (pos)
        cout << *pos << endl;
    else
        cout << "can't find 104" << endl;
    pos = binary_search(arr, &arr[4], -8);
    if (pos)
        cout << *pos << endl;
    else
        cout << "can't find -8" << endl;
    pos = binary_search(arr, &arr[4], 72);
    if (pos)
        cout << *pos << endl;
    else
        cout << "can't find 72" << endl;
        
    int arr1[9] = {
        -23, -8, 16, 72, 104, 111, 347, 348, 910
    };
    pos = binary_search(arr1, &arr1[9], 111);
    if (pos)
        cout << *pos << endl;
    else
        cout << "can't find 111" << endl;
    pos = binary_search(arr, &arr[9], 2000);
    if (pos)
        cout << *pos << endl;
    else
        cout << "can't find 2000" << endl;
        
    return 0;
}

