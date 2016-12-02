#include "gtest/gtest.h"
#include "include/seq_stream.h"

#include <sstream>
#include <vector>

using namespace std;
using namespace stl;

// Reading from no streams using a seq_stream
TEST(seq_stream, read_0) {
  seq_stream ss;
  int i;

  ss >> i;
  EXPECT_TRUE(ss.eof());
}
// Reading from one stream using a seq_stream
TEST(seq_stream, read_1) {
  seq_stream ss;
  stringstream ss1("0 1 2 3 4");
  ss.push(ss1);

  int i;
  vector<int> is;
  while (ss >> i) {
    is.push_back(i);
  }

  ASSERT_EQ(is.size(), 5ul);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(i, is[i]);
  }
}
// Reading from multiple stream using a seq_stream
TEST(seq_stream, read_2) {
  seq_stream ss;
  stringstream ss1("0 1 2 3 4");
  ss.push(ss1);
  stringstream ss2("5 6 7 8 9");
  ss.push(ss2);

  int i;
  vector<int> is;
  while (ss >> i) {
    is.push_back(i);
  }

  ASSERT_EQ(is.size(), 10ul);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(i, is[i]);
  }
}
