/*
Given the following:
static constexpr uint32_t kPageSizeBytes = 4096;

struct Page {
  size_t nread_bytes;   // number of bytes read. 4096..
  const char bytes[kPageSizeBytes];
};

class PageIterator {
 public:
  PageIterator(string filename) {}
  bool HasNext() {
    return false;
  }
  Page* Next() {
    return nullptr;
  }
};

Given above PageIterator interface, implement FileIterator class's constructor & Get method.
You can assume that PageIterator is already implemented.

class FileReader {
public:
  FileReader(string filename);
  size_t Read(size_t len, char* buf);
};

// Usage example:
// auto it = FileIterator(..)
// it.Get(n) // [0, n)
// it.Get(m) // [n, n + m)
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>
#include <ctime>

using namespace std;

// virtual file system
unordered_map<string /*filename*/, string /*data*/> vfs{
    make_pair("file1", "ABCDEFGHIJKLMN"),
    make_pair("file2", "abcdefghijklmnopqr"),
    make_pair("file3", "XYZ"),
};

static constexpr size_t kPageSizeBytes = 4;

struct Page {
    size_t nread_bytes;
    char bytes[kPageSizeBytes];
};

class PageIterator {
    const string& data_;
    size_t npos_;
    Page* pg_;

public:
    PageIterator(const string& filename)
        : data_(vfs[filename])
        , npos_(0)
        , pg_(new Page{})
    {}

    bool HasNext()
    {
        return npos_ < data_.size();
    }

    Page* Next()
    {
        size_t npossible_read = min(kPageSizeBytes, data_.size() - npos_);
        for (size_t i = 0; i < npossible_read; ++i) {
            pg_->bytes[i] = data_[npos_ + i];
        }
        pg_->nread_bytes = npossible_read;
        npos_ += npossible_read;

        return pg_;
    }
};

class FileReader {
    PageIterator pgi;
    Page* pg;
    size_t npos;

public:
    FileReader(const string& filename)
        : pgi(filename)
        , pg(nullptr)
        , npos(0)
    {
        if (pgi.HasNext()) {
            pg = pgi.Next();
        }
    }

    size_t Read(size_t len, char* buf)
    {
        if (!pg) {
            return 0;
        }

        if (npos + len < pg->nread_bytes) {
            memcpy(buf, pg->bytes + npos, len);
            npos += len;

            return len;
        }

        char* start_buf = buf;
        while (len > 0 && pg) {
            size_t npossible_read = min(len, pg->nread_bytes - npos);
            memcpy(buf, pg->bytes + npos, npossible_read);

            len -= npossible_read;
            buf += npossible_read;
            npos += npossible_read;

            // Consumed the current page and reached the end of page
            if (npos == pg->nread_bytes) {
                pg = pgi.HasNext() ? pgi.Next() : nullptr;
                npos = 0;
            }
        }

        return buf - start_buf;
    }
};

int main()
{
    FileReader fr1("file1");
    char buf[128];

    auto nread = fr1.Read(5, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    nread = fr1.Read(9, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    nread = fr1.Read(2, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    nread = fr1.Read(10, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    FileReader fr2("file2");

    nread = fr2.Read(2, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    nread = fr2.Read(3, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    nread = fr2.Read(2, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    nread = fr2.Read(3, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    nread = fr2.Read(2, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    nread = fr2.Read(3, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    nread = fr2.Read(2, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    nread = fr2.Read(3, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    FileReader fr3("file3");

    nread = fr3.Read(1, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    nread = fr3.Read(1, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    nread = fr3.Read(1, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;

    nread = fr3.Read(1, buf);
    buf[nread] = '\0';
    cout << "\"" << buf << "\"" << endl;
}
