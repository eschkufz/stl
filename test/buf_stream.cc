#include "gtest/gtest.h"
#include "include/buf_stream.h"

using namespace std;
using namespace stl;

// Reading from a buffer of length zero
TEST(buf_stream, read_0) {
  auto c = "";
  buf_stream bs(c, c);
  int i;

  bs >> i;
  EXPECT_TRUE(bs.eof());
}
// Reading a single object from a buffer
TEST(buf_stream, read_1) {
  auto c = "10";
  buf_stream bs(c, c+2);
  int i;

  bs >> i;
  EXPECT_EQ(i,10);
  bs >> i;
  EXPECT_TRUE(bs.eof());
}
// Reading multiple objects from a buffer
TEST(buf_stream, read_2) {
  auto c = "10 20";
  buf_stream bs(c, c+5);
  int i;

  bs >> i;
  EXPECT_EQ(i,10);
  bs >> i;
  EXPECT_EQ(i,20);
  bs >> i;
  EXPECT_TRUE(bs.eof());
}
