/*****************************************************************************/ 
/*! 
\brief This file contains the declaration of the bitset_tep class.
This class encapsulates an instance of type T created by calling a constructor
and passing params as a perfectly forwarded parameter pack.
This type also expose all the functionalites of the bitset class implementation
*/ 
/*************************************************************************/ 

#ifndef _BITSET_TEP_H_
#define _BITSET_TEP_H_
#include "bitset.h"
#include <memory>

namespace CustomSTL
{  
  class bitset_tep
  {
  private:
    struct IConcept
    {
      virtual void set(size_t x,bool flag = true) = 0;
      virtual void reset(size_t x) = 0;
      virtual void toggle(size_t x) = 0;
      virtual bool test(size_t x) const = 0;
      virtual size_t count() const = 0;
      virtual size_t size() const = 0;
      virtual std::string to_string(const char first = '0',
                                    const char second = '1') const = 0; 
      virtual bool operator[](size_t x) const = 0;
      ~IConcept() = default;
    };
  
   std::unique_ptr<IConcept> _concept_ptr;
  
    template <typename T>
    class Model : public IConcept 
    {
      T _instance;
    public:  
      template <typename... Args>    
      Model(Args&&... args);
      
      virtual void set(size_t x,bool flag = true);
      virtual void reset(size_t x);
      virtual void toggle(size_t x);
      virtual bool test(size_t x) const;
      virtual size_t count() const;
      virtual size_t size() const;
      virtual std::string to_string(const char first = '0',const char second = '1') const;
      virtual bool operator[](size_t x) const;  
    };
    bitset_tep(std::unique_ptr<IConcept>&& concept);

  public:
    void set(size_t x,bool flag = true);
    void reset(size_t x);
    void toggle(size_t x);
    bool test(size_t x);
    size_t count() const;
    size_t size() const;
    std::string to_string(const char first = '0',const char second = '1') const;
   
    template <typename T,typename... Args>
    static bitset_tep create(Args&&... args);
    
    bool operator[](size_t x) const;  

  };
}
#include "bitset_tep.hpp"

#endif