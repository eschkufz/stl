#include "gtest/gtest.h"
#include "include/sub_stream.h"

#include <sstream>

using namespace std;
using namespace stl;

// A substream with no mappings shouldn't do anything
TEST(sub_stream, empty) {
  ostringstream ss; 
  sub_stream sub(ss);

  sub << "Hello world!" << endl;
  EXPECT_TRUE(ss.str() == string("Hello world!\n"));
}

// Single character replacement
TEST(sub_stream, single) {
  ostringstream ss; 
  sub_stream sub(ss);

  sub.sub('H', "M");
  sub.sub('w', 'm');

  sub << "Hello world!" << endl;
  EXPECT_TRUE(ss.str() == string("Mello morld!\n"));
}

// Multiple character replacement (with no recursion)
TEST(sub_stream, multiple) {
  ostringstream ss; 
  sub_stream sub(ss);

  sub.sub('H', "HH");
  sub.sub('w', "ww");

  sub << "Hello world!" << endl;
  EXPECT_TRUE(ss.str() == string("HHello wworld!\n"));
}

// Multiple character replacement (with recursion)
TEST(sub_stream, recursion) {
  ostringstream ss; 
  sub_stream sub(ss);

  sub.sub('H', "w");
  sub.sub('w', "mm");
  sub.recurse();

  sub << "Hello world!" << endl;
  EXPECT_TRUE(ss.str() == string("mmello mmorld!\n"));
}

