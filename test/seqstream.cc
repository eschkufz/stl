#include "gtest/gtest.h"
#include "include/seqstream.h"

#include <fstream>
#include <vector>


#include <iostream>

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
  fstream fs("data/int_1.dat");
  ss.push(fs);

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
  fstream fs1("data/int_1.dat");
  ss.push(fs1);
  fstream fs2("data/int_2.dat");
  ss.push(fs2);

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
