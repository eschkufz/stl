#ifndef STL_INCLUDE_INDENT_STREAM_H
#define STL_INCLUDE_INDENT_STREAM_H

#include <iostream>
#include <streambuf>
#include <string>

namespace stl {

class indent_buf : public std::streambuf {
  public:
    indent_buf(std::streambuf* buf) : buf_(buf), pending_(false), depth_(0), delim_("  ") { }

    void tab() {
      ++depth_;
    }
    void untab() {
      --depth_;
    }
    void delim(const std::string& d) {
      delim_ = d;
    }

  protected:
    int_type overflow(int_type c = traits_type::eof()) override {
      switch (c) {
        case '\n':
        case '\r':
          pending_ = true;
          return buf_->sputc(c);
        default:
          if (pending_) {
            pending_ = false;
            for (size_t i = 0; i < depth_; ++i) {
              for (auto d : delim_) {
                buf_->sputc(d);
              }
            }
          }
          return buf_->sputc(c);
      }
    }
    int_type sync() override {
      return buf_->pubsync();
    }

  private:
    std::streambuf* buf_;
    bool pending_;
    size_t depth_;
    std::string delim_;
};

class indent_stream : public std::ostream {
  public:
    indent_stream(std::ostream& os) : std::ostream(&buf_), buf_(os.rdbuf()) { }

    void tab() {
      buf_.tab();
    }
    void untab() {
      buf_.untab();
    }
    void delim(const std::string& d) {
      buf_.delim(d);
    }

  private:
    indent_buf buf_;
};

} // namespace stl

#endif
