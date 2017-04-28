#ifndef STL_INCLUDE_SUB_STREAM_H
#define STL_INCLUDE_SUB_STREAM_H

#include <unordered_map>
#include <streambuf>
#include <string>

namespace stl {

class sub_buf : public std::streambuf {
  public:
    sub_buf(std::streambuf* buf) : buf_(buf), recurse_(false) { }

    void recurse(bool r = true) {
      recurse_ = r;
    }
    void sub(char c, char s) {
      subs_[c] = {s};
    }
    void sub(char c, const std::string& s) {
      subs_[c] = s;
    }

  protected:
    int_type overflow(int_type c = traits_type::eof()) override {
      const auto itr = subs_.find(c);
      if (itr != subs_.end()) {
        const auto& str = itr->second;
        const auto len = str.length();
        for (size_t i = 0, ie = len-1; i < ie; ++i) {
          if (recurse_) {
            overflow(str[i]);
          } else {
            buf_->sputc(str[i]);
          }
        }
        return recurse_ ? overflow(str[len-1]) : buf_->sputc(str[len-1]);
      }
      return buf_->sputc(c);
    }
    int_type sync() override {
      return buf_->pubsync();
    }

  private:
    std::streambuf* buf_;
    std::unordered_map<char, std::string> subs_;
    bool recurse_;
};

class sub_stream : public std::ostream {
  public:
    sub_stream(std::ostream& os) : std::ostream(&buf_), buf_(os.rdbuf()) { }

    void recurse(bool r = true) {
      buf_.recurse(r);
    }
    void sub(char c, char s) {
      buf_.sub(c, s);
    }
    void sub(char c, const std::string& s) {
      buf_.sub(c, s);
    }

  private:
    sub_buf buf_;
};

} // namespace stl

#endif

