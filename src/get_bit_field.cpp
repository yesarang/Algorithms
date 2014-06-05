// Implement a function which returns a value corresponding bit positions for a given value
// which starts at 'start' with width 'width'
// For example,
// val = 0xABCD8364
// get_bit_field(val, 4, 4) == 0x6
// get_bit_field(val, 8, 12) == 0xD83

#include <iostream>
#include <cstdint>

using namespace std;

uint32_t get_bit_field(uint32_t val, uint32_t start, uint32_t width) {
	// We can get bitmask with 'width' by calculating 0x01 << width) - 1
	// ex) 0x1 << 4 --> 0x10, 0x10 - 1 --> 0xf
	return (val & (((0x01 << width) - 1) << start)) >> start;
}

int main() {
	cout << hex;
	cout << "0x" << get_bit_field(0xABCD8364, 4, 4) << endl;
	cout << "0x" << get_bit_field(0xABCD8364, 8, 12) << endl;
	cout << "0x" << get_bit_field(0xABCD8364, 8, 12) << endl;
	cout << "0x" << get_bit_field(0xABCD8364, 2, 5) << endl;

	return 0;
}
