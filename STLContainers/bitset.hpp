#include "bitset.h"
#include  <stdexcept>
#include <ostream>

namespace CustomSTL
{
  template<size_t N>
  bitset<N>::bitset() :
    bitset_array{0}
  {}

  template<size_t N>
  bitset<N>::bitset(const bitset& rhs)
  {
      rhs.data = bitset_array.data;
  }
  
  template<size_t N>
  void bitset<N>::set(size_t index,bool flag)
  {
    check_bound(index);
    if(flag)
      bitset_array[arr_index(index)] = static_cast<char>(bitset_array[arr_index(index)] 
                                   | (flag << shift_bits(index)));
    else
      bitset_array[arr_index(index)] = static_cast<char>(bitset_array[arr_index(index)] 
                                   & ~(1 << shift_bits(index)));
  }

  template<size_t N>  
  void bitset<N>::reset(size_t index)
  {
    check_bound(index);
    bitset_array[arr_index(index)] = static_cast<char>(bitset_array[arr_index(index)] 
                                 & ~(1 << shift_bits(index)));
  }

  template<size_t N>  
  void bitset<N>::flip(size_t index)
  {
    check_bound(index);
    bitset_array[arr_index(index)] = static_cast<char>(bitset_array[arr_index(index)] 
                                 ^ 1 << shift_bits(index));
  }

  template<size_t N>  
  bool bitset<N>::test(size_t index) const
  {
    check_bound(index);
    return ((bitset_array[arr_index(index)] >> shift_bits(index)) & 1);
  }

  template<size_t N>    
  bool bitset<N>::any() const noexcept
  {
    for (std::size_t i = 0; i < N; ++i)
    {
        if (test(i))
            return true;
    }

    return false;
  }

  template<size_t N>  
  bool bitset<N>::none() const noexcept
  {
    return !any();
  }

  template<size_t N>  
  bool bitset<N>::all() const noexcept
  {
    for (std::size_t i = 0; i < N; ++i)
    {
        if (!test(i))
            return false;
    }

    return true;
  }
  
  /*************************************************************************/
  /*!
   Returns true if any of the bit is toggled.
  /*************************************************************************/
  template<size_t N>
  bitset<N>::operator bool() const noexcept
  {
      return any();
  }

  /*************************************************************************/
  /*!
    Returns the value to the bit at position pos.
  /*************************************************************************/
  template<size_t N>  
  bool bitset<N>::operator[](size_t index) const
  {
    check_bound(index);
    return (bitset_array[arr_index(index)] >> shift_bits(index));    
  }

  /*************************************************************************/
  /*!
    Returns the reference to the bit at position pos.
  /*************************************************************************/
  //template<size_t N>
  //bit_proxy<N>& bitset<N>::operator[](size_t index)
  //{
  //    check_bound(index);
  //    return bit_proxy(bitset_array, index);
  //}

  /*************************************************************************/
  /*!
   Performs the AND operation
  /*************************************************************************/
  //template<size_t N>
  //bitset<N>& bitset<N>::operator&=(const bitset& rhs) noexcept
  //{
  //    for (size_t i = 0; i < N; ++i)
  //    {
  //        
  //    }
  //
  //    return true;
  //}

  /*************************************************************************/
  /*!
   Performs the OR operation
  /*************************************************************************/
  //template<size_t N>
  //bitset<N>& bitset<N>::operator|=(const bitset& rhs) noexcept
  //{
  //    for (size_t i = 0; i < N; ++i)
  //    {
  //        
  //    }
  //
  //    return true;
  //}

  /*************************************************************************/
  /*!
   Performs the XOR operation
  /*************************************************************************/
  //template<size_t N>
  //bitset<N>& bitset<N>::operator^=(const bitset& rhs) noexcept
  //{
  //    for (size_t i = 0; i < N; ++i)
  //    {
  //        
  //    }
  //
  //    return true;
  //}

  /*************************************************************************/
  /*!
   Return a new bitset with all the bits flipped
  /*************************************************************************/
  template<size_t N>
  bitset<N> bitset<N>::operator~() const noexcept
  {
      return bitset(*this).flip();
  }

  /*************************************************************************/
  /*!
   Copy assignment operator
  /*************************************************************************/
  template<size_t N>
  const bitset<N>& bitset<N>::operator=(const bitset& rhs)
  {
      if (this != rhs)
      {
          rhs(*this);
      }

      return *this;
  }

  /*************************************************************************/
  /*!
   Returns number of toggled bit
  /*************************************************************************/
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
  
  /*************************************************************************/
  /*!
   Returns the maximum capactiy of the bitset
  /*************************************************************************/
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
  void bitset<N>::check_bound(size_t index) const
  {
    if(index > (N-1))
      throw std::out_of_range{("out of bounds!")};
  }
  
  template<size_t N>
  size_t bitset<N>::shift_bits(size_t index) const
  {
    return (index % BITS_IN_CHAR);
  }
  
  template<size_t N>
  size_t bitset<N>::arr_index(size_t index) const
  {
    return (index / BITS_IN_CHAR);
  }

}