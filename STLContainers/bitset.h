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
#include <array>

namespace CustomSTL
{
    template <size_t N>
    class bitset;

    //template <size_t N = 1>
    //class bit_proxy
    //{
    //public:
    //    bit_proxy(bitset<N>& mask, unsigned bit) : bitset_array(mask.data()), index(bit) {}
    //
    //    explicit operator bool() const { return bitset_array & (1 << index); }
    //    void operator=(bool bit) { bitset_array = (bitset_array & ~(bit << index)) | (bit << index); }
    //
    //private:
    //    constexpr static size_t BITS_IN_CHAR = sizeof(char) * CHAR_BIT; //By default each char is 8 bits
    //    constexpr static size_t EXTRA_BITS = N % BITS_IN_CHAR;
    //    constexpr static size_t CHAR_COUNT = (N - 1) / 8 + 1;
    //    std::array<char, CHAR_COUNT> bitset_array;
    //    unsigned index;
    //};

    template <size_t N = 1>
    class bitset
    {
    private:
        constexpr static size_t BITS_IN_CHAR = sizeof(char) * CHAR_BIT; //By default each char is 8 bits
        constexpr static size_t EXTRA_BITS = N % BITS_IN_CHAR;
        constexpr static size_t CHAR_COUNT = (N - 1) / 8 + 1;
        std::array<char, CHAR_COUNT> bitset_array;
        void check_bound(size_t index) const;
        size_t shift_bits(size_t index) const;
        size_t arr_index(size_t index) const;
    public:
        explicit bitset();
        bitset(const bitset& rhs);
        inline std::array<char, CHAR_COUNT> data() const noexcept { return bitset_array; }
        void set(size_t index, bool flag = true);
        void reset(size_t index);
        void flip(size_t index);
        bool test(size_t index) const;
        bool any() const noexcept;
        bool none() const noexcept;
        bool all() const noexcept;
        explicit operator bool() const noexcept;
        bool operator[](size_t index) const;
        //template<size_t N>
        //bit_proxy<N>& operator[](std::size_t pos);
        bitset& operator&=(const bitset& rhs) noexcept;
        bitset& operator|=(const bitset& rhs) noexcept;
        bitset& operator^=(const bitset& rhs) noexcept;
        bitset operator~() const noexcept;
        const bitset& operator=(const bitset& rhs);
        size_t count() const;
        constexpr size_t size() const;
        std::string to_string(const char first = '0', const char second = '1') const;

        // Stream Operation, output only
        template <typename CharT, typename Traits>
        friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const bitset& bitset)
        {
            for (auto i = N; i > 0;)
                os << (bitset[--i] ? "1" : "0");

            return os;
        }
    };
}
#include "bitset.hpp"

#endif