#ifndef STL_INCLUDE_BUF_STREAM_H
#define STL_INCLUDE_BUF_STREAM_H

#include <iostream>
#include <streambuf>

namespace stl {

class buf_buf : public std::streambuf {
  public:
    buf_buf(const char* begin, const char* end) : begin_(begin), end_(end), p_(begin) { 
      (void) begin_;
    }

  protected:
    int_type underflow() override {
      return p_ == end_ ? traits_type::eof() : traits_type::to_int_type(*p_);
    }
    int_type uflow() override {
      return p_ == end_ ? traits_type::eof() : traits_type::to_int_type(*p_++);
    }
    std::streamsize showmanyc() override {
      return end_ - p_;
    }

  private:
    const char* begin_;
    const char* end_;
    const char* p_;
};


class buf_stream : public std::iostream {
  public:
    buf_stream(const char* begin, const char* end) : std::iostream(&buf_), buf_(begin, end) { }

  private:
    buf_buf buf_;
};

} // namespace stl

#endif
