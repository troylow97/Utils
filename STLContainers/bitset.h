/******************************************************************************/
/*! 
\brief This file contains the declaration of the bitset class.
       This bitset class allows for the setting, resetting, flipping,clearing
       testing, counting, putting to string of bits.
*/ 
/******************************************************************************/
#ifndef _BITSET_H_
#define _BITSET_H_

#include <string>

namespace CustomSTL
{
  template <size_t N = 1>
  class bitset
  {
  private:
    constexpr static size_t BITS_IN_CHAR = sizeof(char) * CHAR_BIT;   
    constexpr static size_t EXTRA_BITS = N % BITS_IN_CHAR;   
    constexpr static size_t CHAR_COUNT = (N - 1)/8 + 1;   
    char bitset_array[CHAR_COUNT];
    void check_bound(size_t index) const;
    size_t shift_bits(size_t index) const;
    size_t arr_index(size_t index) const;
  public:
    explicit bitset();
    void set(size_t index,bool flag = true);
    void reset(size_t index);
    void flip(size_t index);
    bool test(size_t index) const;
    bool any() const noexcept;
    bool none() const noexcept;
    bool all() const noexcept;  
    bool operator[](size_t index) const;
    size_t count() const;
    constexpr size_t size() const;
    std::string to_string(const char first = '0',const char second = '1') const;
  };   
}
#include "bitset.hpp"

#endif