#ifndef _ARRAY_H_

namespace CustomSTL
{
  template<typename T, size_t N> 
  class array
  {
  private:
    T _array[N];
 
  public:
    typedef T value_type;
    /*********************************************************************/
    /*!
    \fn T* array<T, N>::begin()
    
    \brief This function returns the value of the beginning of the array
    
    \return T*
            Pointer to the element
    */ 
    /*********************************************************************/
    T* begin();
    /*********************************************************************/
    /*!
    \fn const T* array<T, N>::cbegin() const
    
    \brief This function returns the const value of the 
           beginning of the array
    
    \return const T*
            Pointer to the element which is read only
    */ 
    /*********************************************************************/ 
    const T* cbegin() const;
    /*********************************************************************/
    /*!
    \fn T* array<T, N>::end()
    
    \brief This function returns the value of the end of the array
    
    \return T*
            Pointer to the element
    */ 
    /*********************************************************************/     
    T* end();
    /*********************************************************************/
    /*!
    \fn const T* array<T, N>::cend() const
    
    \brief This function returns the const value of the end of the array
    
    \return const T*
            Pointer to the element which is read only
    */ 
    /*********************************************************************/  
    const T* cend() const;
    /*********************************************************************/
    /*!
    \fn T array<T, N>::operator[](size_t index) const
    
    \brief This function returns the copy of the value of the 
          element in the specified index
    
    \param index
            To access a specific element in the array
    
    \return T
            Copy of the element of the specific index
    */ 
    /*********************************************************************/  
    T operator[](size_t index) const;
    /*********************************************************************/
    /*!
    \fn T& array<T, N>::operator[](size_t index)
    
    \brief This function returns the value of the element in the specified 
          index
    
    \param index
            To access a specific element in the array
    
    \return T&
            Element of the specific index
    */ 
    /*********************************************************************/ 
    T& operator[](size_t index);
    /*********************************************************************/
    /*!
    \fn size_t array<T, N>::size() const
    
    \brief This function returns the size of the array
    
    \return size_t
            size of array
    */ 
    /*********************************************************************/  
    size_t size() const;
  
  };
}
#include "array.tpp"

#endif


