# stl
Common idioms for stl programming.

## seqstream.h
Treat a sequence of streams as a single stream (currently supports reads):
```
seqstream ss;

stringstream s1("Hello world");
ss.push(s1);

filestream s2("file.txt");
ss.push(s2);

int x;
while (ss >> x) {
  cout << x << endl;
}
```
