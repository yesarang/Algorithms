// 9.7 Implement the "paint fill" function that one might see on many image editing
// programs.That is, given a screen(represented by a two - dimensional array of colors),
// a point, and a new color, fill in the surrounding area until the color changes from the
// original color
#include <iostream>
#include <vector>

using namespace std;

typedef char Color;
typedef vector<vector<Color>> Screen;

void paint_fill(Screen& s, int x, int y, Color oc, Color nc) {
	if (x >= 0 && x < s.size() && y >= 0 && y < s[0].size() && s[x][y] == oc) {
		s[x][y] = nc;
		paint_fill(s, x - 1, y, oc, nc); // top
		paint_fill(s, x + 1, y, oc, nc); // bottom
		paint_fill(s, x, y - 1, oc, nc); // left
		paint_fill(s, x, y + 1, oc, nc); // right
	}
}

void paint_fill(Screen& s, int x, int y, Color nc) {
	if (s[x][y] == nc) {
		return;
	}
	else {
		paint_fill(s, x, y, s[x][y], nc);
	}
}

void print_screen(const Screen& s) {
	for (const auto& r : s) {
		for (auto c : r) {
			cout << c;
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	Screen s{
		{ 'G', 'G', 'G', 'G', 'G', 'G' },
		{ 'G', 'G', 'G', 'Y', 'Y', 'G' },
		{ 'G', 'G', 'G', 'Y', 'Y', 'G' },
		{ 'G', 'G', 'G', 'Y', 'Y', 'G' },
		{ 'G', 'G', 'G', 'G', 'G', 'G' },
		{ 'G', 'G', 'G', 'G', 'G', 'G' }
	};
	print_screen(s);
	paint_fill(s, 2, 2, 'B');
	print_screen(s);

	return 0;
}
