#include "gtest/gtest.h"
#include "include/comment_stream.h"

#include <sstream>

using namespace std;
using namespace stl;

// Reading from a stream with a comment
TEST(comment_stream, read) {
  stringstream ss("10#This is a comment\n20");
  comment_stream cs(ss);

  int x;
  cs >> x;
  
  EXPECT_EQ(x, 10);
} 

// Reading from a stream that ends in a comment
TEST(comment_stream, read_end) {
  stringstream ss("10#This is a comment");
  comment_stream cs(ss);

  int x;
  cs >> x;

  EXPECT_EQ(x, 10);
}

// Reading from a stream that only contains a comment
TEST(comment_stream, read_none) {
  stringstream ss("#This is a comment\n");
  comment_stream cs(ss);

  int x;
  cs >> x;

  EXPECT_TRUE(cs.fail());
}
