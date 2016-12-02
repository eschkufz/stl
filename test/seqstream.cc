#include "gtest/gtest.h"
#include "include/seqstream.h"

#include <sstream>
#include <vector>

using namespace std;
using namespace stl;

// Reading from no streams using a seqstream
TEST(seqstream, read_0) {
  seqstream ss;
  int i;

  ss >> i;
  EXPECT_TRUE(ss.eof());
}
// Reading from one stream using a seqstream
TEST(seqstream, read_1) {
  seqstream ss;
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
// Reading from multiple stream using a seqstream
TEST(seqstream, read_2) {
  seqstream ss;
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
