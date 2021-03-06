// An algorithm to read a combined stream
//
// A combined stream is a stream consisting of multiple files.
// read operation should try to read data from the next file when
// a file reaches the end of file.
// 
// ex) file1: "abcde", file2 : "fghij", file3 : "klmno"
// read(buf, 3)--> "abc"
// read(buf, 3)--> "def"
// read(buf, 3)--> "ghi"
// read(buf, 3)--> "jkl"
// read(buf, 3)--> "mno"
// read(buf, 3)--> ""
//
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class CombinedStream {
	vector<stringstream> strms_;
	int last_read_file_;

public:
	CombinedStream(const vector<string>& strs);
	streamsize read(char* buf, streamsize cnt);
};

CombinedStream::CombinedStream(const vector<string>& strs)
	: strms_(strs.begin(), strs.end()), last_read_file_(0)
{}

streamsize CombinedStream::read(char* buf, streamsize cnt) {
	streamsize read_cnt = 0;
	while (cnt > 0) {
		strms_[last_read_file_].read(buf + read_cnt, cnt);
		streamsize this_read_cnt = strms_[last_read_file_].gcount();
		if (this_read_cnt < cnt) {
			++last_read_file_;
			if (last_read_file_ == strms_.size()) {
				break;
			}
		}
		read_cnt += this_read_cnt;
		cnt -= this_read_cnt;
	}

	return read_cnt;
}

int main() {
	vector<string> vs{ "abcde", "fghij", "klmno" };
	CombinedStream cstr(vs);

	char buf[10];
	streamsize read_cnt = cstr.read(buf, 3);
	buf[3] = '\0';
	cout << buf << endl;
	assert(read_cnt == 3);

	read_cnt = cstr.read(buf, 3);
	buf[3] = '\0';
	cout << buf << endl;
	assert(read_cnt == 3);

	read_cnt = cstr.read(buf, 3);
	buf[3] = '\0';
	cout << buf << endl;
	assert(read_cnt == 3);

	read_cnt = cstr.read(buf, 3);
	buf[3] = '\0';
	cout << buf << endl;
	assert(read_cnt == 3);

	read_cnt = cstr.read(buf, 3);
	buf[3] = '\0';
	cout << buf << endl;
	assert(read_cnt == 3);

	read_cnt = cstr.read(buf, 3);
	buf[3] = '\0';
	cout << buf << endl;
	assert(read_cnt == 0);

	return 0;
}
