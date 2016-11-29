#ifndef STL_INCLUDE_SEQBUF_H
#define STL_INCLUDE_SEQBUF_H

#include <streambuf>
#include <queue>

namespace stl {

class seqbuf : public std::streambuf {
  public:
    seqbuf() : std::streambuf() { }

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

} // namespace stl

#endif
