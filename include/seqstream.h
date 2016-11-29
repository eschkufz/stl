#ifndef STL_INCLUDE_SEQSTREAM_H
#define STL_INCLUDE_SEQSTREAM_H

#include "include/seqbuf.h"

namespace stl {

class seqstream : public std::iostream {
  public:
    seqstream() : std::iostream(&buf_) { }

    void push(std::iostream& ios) {
      buf_.push(ios.rdbuf());
    }

  private:
    seqbuf buf_;
};

} // namespace stl

#endif
