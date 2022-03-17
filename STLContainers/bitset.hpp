#include "bitset.h"

namespace CustomSTL
{
  template<size_t N>
  bitset<N>::bitset() :
    bitset_array{0}
  {}
  
  template<size_t N>
  void bitset<N>::set(size_t x,bool flag)
  {
    check_bound(x);
    if(flag == true)
      bitset_array[arr_index(x)] = static_cast<char>(bitset_array[arr_index(x)] 
                                   | (flag << shift_bits(x)));
    else
      bitset_array[arr_index(x)] = static_cast<char>(bitset_array[arr_index(x)] 
                                   & ~(1 << shift_bits(x)));
  }

  template<size_t N>  
  void bitset<N>::reset(size_t x)
  {
    check_bound(x);
    bitset_array[arr_index(x)] = static_cast<char>(bitset_array[arr_index(x)] 
                                 & ~(1 << shift_bits(x)));
  }

  template<size_t N>  
  void bitset<N>::flip(size_t x)
  {
    check_bound(x);
    bitset_array[arr_index(x)] = static_cast<char>(bitset_array[arr_index(x)] 
                                 ^ 1 << shift_bits(x));
  }

  template<size_t N>  
  bool bitset<N>::test(size_t x) const
  {
    check_bound(x);
    return ((bitset_array[arr_index(x)] >> shift_bits(x)) & 1);
  }

  template<size_t N>  
  bool bitset<N>::operator[](size_t x) const
  {
    check_bound(x);
    return (bitset_array[arr_index(x)] >> shift_bits(x));    
  }

  template<size_t N>  
  size_t bitset<N>::count() const
  {
    size_t count = 0;
    
    for (std::size_t i = 0; i < N; ++i)
    {
      if (test(i))
        ++count;
    }
    return count;
  }
  

  template<size_t N>  
  constexpr size_t bitset<N>::size() const
  {
    return N;
  }
  

  template<size_t N>  
  std::string bitset<N>::to_string(const char first,const char second) const
  {
    std::string bitset_str;
    
    for (std::size_t i = N; i > 0; --i)
    {
      if (test(i-1))
        bitset_str.push_back(second);
      else
        bitset_str.push_back(first);
    }
    return bitset_str; 
  }
  
  template<size_t N>
  void bitset<N>::check_bound(size_t x) const
  {
    if(x > (N-1))
      throw std::out_of_range{"out of bounds!"};
  }
  
  template<size_t N>
  size_t bitset<N>::shift_bits(size_t x) const
  {
    return (x % BITS_IN_CHAR);
  }
  
  template<size_t N>
  size_t bitset<N>::arr_index(size_t x) const
  {
    return (x / BITS_IN_CHAR);
  }
}