/*************************************************************************/
/*!  
\brief  
This file contains the template class definitions of
a static array container
/*************************************************************************/ 

namespace CustomSTL
{
  /***********************************************************************/
  /*!
  \fn T* array<T, N>::begin()
  
  \brief This function returns the value of the beginning of the array
  
  \return T*
          Pointer to the element
  */ 
  /***********************************************************************/
  template<typename T, size_t N>
  T* array<T, N>::begin()
  {
    return _array;
  }

  /***********************************************************************/
  /*!
  \fn const T* array<T, N>::cbegin() const
  
  \brief This function returns the const value of the beginning of the array
  
  \return const T*
          Pointer to the element which is read only
  */ 
  /***********************************************************************/ 
  template<typename T, size_t N>
  const T* array<T, N>::cbegin() const
  {
    return _array;
  }
 
  /***********************************************************************/
  /*!
  \fn T* array<T, N>::end()
  
  \brief This function returns the value of the end of the array
  
  \return T*
          Pointer to the element
  */ 
  /***********************************************************************/ 
  template<typename T, size_t N>
  T* array<T, N>::end()
  {
    return _array+N;
  }

  /***********************************************************************/
  /*!
  \fn const T* array<T, N>::cend() const
  
  \brief This function returns the const value of the end of the array
  
  \return const T*
          Pointer to the element which is read only
  */ 
  /***********************************************************************/   
  template<typename T, size_t N>
  const T* array<T, N>::cend() const
  {
    return _array+N;
  }

  /***********************************************************************/
  /*!
  \fn T array<T, N>::operator[](size_t index) const
  
  \brief This function returns the copy of the value of the 
         element in the specified index
  
  \param index
          To access a specific element in the array
  
  \return T
          Copy of the element of the specific index
  */ 
  /***********************************************************************/  
  template<typename T, size_t N>
  T array<T, N>::operator[](size_t index) const
  {
    return _array[index];
  }

  /***********************************************************************/
  /*!
  \fn T& array<T, N>::operator[](size_t index)
  
  \brief This function returns the value of the element in the specified 
         index
  
  \param index
          To access a specific element in the array
  
  \return T&
          Element of the specific index
  */ 
  /***********************************************************************/   
  template<typename T, size_t N>
  T& array<T, N>::operator[](size_t index)
  {
    return _array[index];
  }

  /***********************************************************************/
  /*!
  \fn size_t array<T, N>::size() const
  
  \brief This function returns the size of the array
  
  \return size_t
          size of array
  */ 
  /***********************************************************************/     
  template<typename T, size_t N>  
  size_t array<T, N>::size() const
  {
    return N;
  }
  
}
