#include "gtest/gtest.h"
#include "include/indent_stream.h"

#include <sstream>

using namespace std;
using namespace stl;

TEST(indent_stream, no_tab) {
  ostringstream ss;
  indent_stream is(ss);

  is << "Hello world!" << endl;

  EXPECT_TRUE(ss.str() == string("Hello world!\n"));
}
TEST(indent_stream, one_tab) {
  ostringstream ss;
  indent_stream is(ss);

  is << "Hello" << endl;
  is.tab();
  is << "world" << endl;
  is.untab();
  is << "!" << endl;

  EXPECT_TRUE(ss.str() == string("Hello\n  world\n!\n"));
}
TEST(indent_stream, two_tabs) {
  ostringstream ss;
  indent_stream is(ss);

  is << "Hello" << endl;
  is.tab();
  is.tab();
  is << "world" << endl;
  is.untab();
  is.untab();
  is << "!" << endl;

  EXPECT_TRUE(ss.str() == string("Hello\n    world\n!\n"));
}
TEST(indent_stream, char_tabs) {
  ostringstream ss;
  indent_stream is(ss);
  is.delim("DD");

  is << "Hello" << endl;
  is.tab();
  is << "world" << endl;
  is.untab();
  is << "!" << endl;

  EXPECT_TRUE(ss.str() == string("Hello\nDDworld\n!\n"));
}
