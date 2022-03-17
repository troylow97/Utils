/*****************************************************************************/ 
/*! 
\brief This file contains the definitions of the bitset_tep class.
This class encapsulates an instance of type T created by calling a constructor
and passing params as a perfectly forwarded parameter pack.
This type also expose all the functionalites of the bitset class implementation
*/ 
/*************************************************************************/ 
#include "bitset_tep.h"

namespace CustomSTL
{
  template <typename T>
  template <typename... Args>   
  bitset_tep::Model<T>::Model(Args&&... args) :
    _instance
    {
      std::forward<Args>(args)... 
    }
    {}  
 
  template <typename T> 
  void bitset_tep::Model<T>::set(size_t x,bool flag)
  {
    _instance.set(x,flag);
  }     

  template <typename T> 
  void bitset_tep::Model<T>::reset(size_t x) 
  {
    _instance.reset(x);
  }
    
  template <typename T> 
  void bitset_tep::Model<T>::toggle(size_t x) 
  {
    _instance.flip(x);
  }
  
  template <typename T> 
  bool bitset_tep::Model<T>::test(size_t x) const 
  {
    return _instance.test(x);
  }
  
  template <typename T> 
  size_t bitset_tep::Model<T>::count() const 
  {
    return _instance.count();
  }
  
  template <typename T> 
  size_t bitset_tep::Model<T>::size() const 
  {
    return _instance.size();
  }
  
  template <typename T> 
  std::string bitset_tep::Model<T>::to_string(const char first, 
                                              const char second) const 
  {
    return _instance.to_string(first,second);
  } 
  
  template <typename T> 
  bool bitset_tep::Model<T>::operator[](size_t x) const 
  {
    return _instance[x];
  }    

  bitset_tep::bitset_tep(std::unique_ptr<IConcept>&& concept) : 
    _concept_ptr
    {
      std::move(concept)
    } 
  {
    
  }
  
  void bitset_tep::set(size_t x,bool flag) 
  {
    _concept_ptr->set(x,flag);
  }
  
  void bitset_tep::reset(size_t x) 
  {
    _concept_ptr->reset(x);
  }
  
  void bitset_tep::toggle(size_t x) 
  {
    _concept_ptr->toggle(x);
  }
  
  bool bitset_tep::test(size_t x) 
  {
    return _concept_ptr->test(x);
  }
  
  size_t bitset_tep::count() const 
  {
    return _concept_ptr->count();
  }
  
  size_t bitset_tep::size() const 
  {
    return _concept_ptr->size();
  }
    
  std::string bitset_tep::to_string(const char first,const char second) const 
  {
    return _concept_ptr->to_string(first,second);
  }     

  template <typename T,typename... Args>
  bitset_tep bitset_tep::create(Args&&... args) 
  {
    return bitset_tep(std::make_unique<Model<T>>(std::forward<Args>(args)...));
  }
  
  bool bitset_tep::operator[](size_t x) const 
  {
    return (*_concept_ptr)[x];
  }
}
