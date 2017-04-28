#ifndef STL_INCLUDE_SEQ_STREAM_H
#define STL_INCLUDE_SEQ_STREAM_H

#include <iostream>
#include <streambuf>
#include <queue>

namespace stl {

class seq_buf : public std::streambuf {
  public:
    seq_buf() : std::streambuf() { }

    void push(std::streambuf* buf) {
      bufs_.push(buf);
    }

  protected:
    int_type underflow() override {
      if (bufs_.empty()) {
        return traits_type::eof();
      }
      const auto res = bufs_.front()->sgetc();
      if (res != traits_type::eof()) {
        return res;
      } 
      return bufs_.size() == 1 ? traits_type::eof() : traits_type::to_int_type(' '); 
    } 
    int_type uflow() override {
      if (bufs_.empty()) {
        return traits_type::eof();
      }
      const auto res = bufs_.front()->sbumpc();
      if (res != traits_type::eof()) {
        return res;
      }
      bufs_.pop();
      return bufs_.empty() ? traits_type::eof() : traits_type::to_int_type(' ');
    }
    std::streamsize showmanyc() override {
      return bufs_.empty() ? -1 : bufs_.front()->in_avail();
    }

  private:
    std::queue<std::streambuf*> bufs_;          
};

class seq_stream : public std::iostream {
  public:
    seq_stream() : std::iostream(&buf_) { }

    void push(std::iostream& ios) {
      buf_.push(ios.rdbuf());
    }

  private:
    seq_buf buf_;
};

} // namespace stl

#endif
