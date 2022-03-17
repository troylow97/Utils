/******************************************************************************/
/*! 
\brief This file contains the declaration of the bitset class.
       This bitset class allows for the setting, resetting, flipping,clearing
       testing, counting, putting to string of bits.
*/ 
/******************************************************************************/
#ifndef _BITSET_H_
#define _BITSET_H_

namespace CustomSTL
{
  template <size_t N=1>
  class bitset
  {
  private:
    constexpr static size_t BITS_IN_CHAR = sizeof(char) * CHAR_BIT;   
    constexpr static size_t EXTRA_BITS = N % BITS_IN_CHAR;   
    constexpr static size_t CHAR_COUNT = (N - 1)/8 + 1;   
    char bitset_array[CHAR_COUNT];
    void check_bound(size_t x) const;
    size_t shift_bits(size_t x) const;
    size_t arr_index(size_t x) const;
  public:
    explicit bitset();
    void set(size_t x,bool flag = true);
    void reset(size_t x);
    void flip(size_t x);
    bool test(size_t x) const;
    bool operator[](size_t x) const;
    size_t count() const;
    constexpr size_t size() const;
    std::string to_string(const char first = '0',const char second = '1') const;
  };   
}
#include "bitset.hpp"

#endif