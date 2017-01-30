# stl
Common idioms for stl programming.

## buf_stream.h
Treat an in-memory buffer as a stream without copying:
``` c++
const char* c = "Hello world!";
buf_stream bs(c, c+12);

string s;
cin >> s;
assert (s == "Hello");
```

## comment_stream.h
Ignore comments from an underlying istream:
``` c++
stringstream ss;
ss << "# This is a comment" << endl;
ss << "10";
comment_stream cs(ss);

int x;
cs >> x;
assert(x == 10);
```

## seq_stream.h
Treat a sequence of streams as a single stream (currently supports reads):
``` c++
seq_stream ss;

stringstream s1("Hello world");
ss.push(s1);

filestream s2("file.txt");
ss.push(s2);

int x;
while (ss >> x) {
  cout << x << endl;
}
```

