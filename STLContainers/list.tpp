#include "list.h"

namespace CustomSTL
{
  /***********************************************************************/
  /*!
  \fn list<T>::list()
  \brief Default constructor for list
  */ 
  /***********************************************************************/  
  template <typename T>
  list<T>::list() :
    _first{nullptr},
    _last{nullptr}
  {
  }

  /***********************************************************************/
  /*!
  \fn list<T>::list(TInputIterator current, TInputIterator end)
  \brief For Range Loop Constructor
  */ 
  /***********************************************************************/  
  template<typename T>
  template<typename TInputIterator>
  list<T>::list(TInputIterator current, TInputIterator end) :
    _first{nullptr},
    _last{nullptr}
  {
    while (current != end)
    {
      push_back(*current++);
    }
  }

  /***********************************************************************/
  /*!
  \fn list<T>::list(std::initializer_list<T> values)
  \brief   Initializer list Constructor
  */ 
  /***********************************************************************/  
  template <typename T>
  list<T>::list(std::initializer_list<T> values) :
    list{values.begin(), values.end()}
  {
  }

  /***********************************************************************/
  /*!
  \fn list<T>::list(const list& rhs) : list(rhs.begin(), rhs.end())
  \brief Copy constructor for list
  */ 
  /***********************************************************************/  
  template<typename T>
  list<T>::list(const list& rhs) : list(rhs.begin(), rhs.end())
  {
  }

  /***********************************************************************/
  /*!
  \fn list<T>::~list()
  \brief Default destructor for list
  */ 
  /***********************************************************************/  
  template<typename T>
  list<T>::~list()
  {
    while (!empty())
    {
      pop_front();
    }
  }

  /***********************************************************************/
  /*!
  \fn list<T>& list<T>::operator=(const list& rhs)
  \brief Copy assignment operator overload. Used to copy one list to another
  \param rhs 
            Reference of the list being copied to this list
  \returns Reference to the newly copied list
  */ 
  /***********************************************************************/  
  template<typename T>
  list<T>& list<T>::operator=(const list& rhs)
  {
    if (this != &rhs)
    {
      while (!empty())
      {
        pop_front();
      }
      const_iterator current = rhs.begin();
      const const_iterator end = rhs.end();
      while (current != end)
      {
        push_back(*current++);
      }
    }
    return *this;
  }

  /***********************************************************************/
  /*!
 \fn typename list<T>::reference list<T>::front()
 \brief   Returns a reference to the first value
 \returns dereferenced to the list
  */ 
  /***********************************************************************/  
  template <typename T>
  typename list<T>::reference list<T>::front()
  {
    return _first->_value;
  }

  /***********************************************************************/
  /*!
  \fn typename list<T>::const_reference list<T>::front() const
  \brief   Returns a reference to the first value
  \returns dereferenced to the list
  */ 
  /***********************************************************************/  
  template <typename T>
  typename list<T>::const_reference list<T>::front() const
  {
    return _first->_value;
  }

  /***********************************************************************/
  /*!
  \fn void list<T>::push_back(const value_type& value)
  \brief  Adds an element at the back of the list.
  \param  value 
          value of the element to be added
  */ 
  /***********************************************************************/  
  template <typename T>
  void list<T>::push_back(const value_type& value)
  {
    list<T>::node* node = new list<T>::node(value, _last, nullptr);
    if (_last)
    {
      _last->_next = node;
    }
    _last = node;
    if (!_first)
    {
      _first = _last;
    }
  }

  /***********************************************************************/
  /*!
  \fn void list<T>::pop_front()
  \brief  Removes an element at the back of the list.
  */ 
  /***********************************************************************/  
  template <typename T>
  void list<T>::pop_front()
  {
    list<T>::node* temp = _first;
    _first = _first->_next;
    delete temp;
    if (_first)
    {
      _first->_prev = nullptr;
    }
    else
    {
      _last = nullptr;
    }
  }

  /***********************************************************************/
  /*!
  \fn bool list<T>::empty() const
  \brief Check if list is empty
  \return true if list is empty.
  */ 
  /***********************************************************************/  
  template <typename T>
  bool list<T>::empty() const
  {
    return (!_first);
  }

  /***********************************************************************/
  /*!
  \fn bool list<T>::iterator_impl::operator!=(const iterator_impl& rhs) const
  
  \brief Checks if the iterator is not equal to another iterator
  
  \param const iterator_impl& rhs
  
   \return true if iterator is not equal
  */ 
  /***********************************************************************/
  template<typename T>
  bool list<T>::iterator_impl::operator!=(const iterator_impl& rhs) const
  {
    return !(*this == rhs);
  }

  /***********************************************************************/
  /*!
  \fn bool list<T>::iterator_impl::operator==(const iterator_impl& rhs) const
  
  \brief Checks if the iterator is equal to another iterator
  
  \param const iterator_impl& rhs
  
  \return true if iterator is equal
  
  */ 
  /***********************************************************************/
  template<typename T>
  bool list<T>::iterator_impl::operator==(const iterator_impl& rhs) const
  {
    return (_curr == rhs._curr);
  }

  /***********************************************************************/
  /*!
  \fn typename list<T>::iterator_impl& list<T>::iterator_impl::operator++()
  
  \brief Pre-increment operator overload. Iterates to next node
  
  
  \return Returns the current reference of the iterator
  
  */ 
  /***********************************************************************/
  template<typename T>
  typename list<T>::iterator_impl& list<T>::iterator_impl::operator++()
  {
    _curr = _curr->_next;
    return *this;
  }

  /***********************************************************************/
  /*!
  \fn typename list<T>::iterator_impl& list<T>::iterator_impl::operator--()
  
  \brief Pre-decrement operator overload. Iterates to next node
  
  
  \return Returns the current reference of the iterator
  
  */ 
  /***********************************************************************/
  template<typename T>
  typename list<T>::iterator_impl& list<T>::iterator_impl::operator--()
  {
    if(_curr != nullptr)
    {
      _curr = _curr->_prev;
      return *this;     
    }
    else
    {
      _curr = _last;
      return *this;
    }

  }

  /***********************************************************************/
  /*!
  \fn typename list<T>::iterator_impl list<T>::iterator_impl::operator++(int)
  
  \brief Post-increment operator overload. Iterates to next node
  
  
  \return Returns the current reference of the iterator
  
  */ 
  /***********************************************************************/
  template<typename T>
  typename list<T>::iterator_impl list<T>::iterator_impl::operator++(int)
  {
    const_iterator_impl temp = *this;
    ++(*this);
    return temp;
  }

  /***********************************************************************/
  /*!
  \fn typename list<T>::iterator_impl list<T>::iterator_impl::operator--(int)
  
  \brief Post-decrement operator overload. Iterates to next node
  
  
  \return Returns the current reference of the iterator
  
  */ 
  /***********************************************************************/
  template<typename T>
  typename list<T>::iterator_impl list<T>::iterator_impl::operator--(int)
  {
    const_iterator_impl temp = *this;
    --(*this);
    return temp;
  }

  /***********************************************************************/
  /*!
  \fn typename list<T>::iterator_impl::reference 
               list<T>::iterator_impl::operator*() const
  
  \brief dereference operator overload. Get reference to the value
    
  \return Returns the reference to the value inside the iterator
  
  */ 
  /***********************************************************************/
  template<typename T>
  typename list<T>::iterator_impl::reference 
           list<T>::iterator_impl::operator*() const
  {
    return _curr->_value;
  }

  /***********************************************************************/
  /*!
  \fn list<T>::iterator_impl::iterator_impl(node* last, node* curr)
  
  \brief Conversion constructor for iterator_impl
    
  */ 
  /***********************************************************************/
  template<typename T>
  list<T>::iterator_impl::iterator_impl(node* last, node* curr) :
    _curr{curr},
    _last{last}  
  {}
  
  /***********************************************************************/
  /*!
  \fn    bool list<T>::const_iterator_impl::
         operator!=(const const_iterator_impl& rhs) const
  
  \brief Checks if the iterator is not equal to another iterator
  
  \param const iterator_impl& rhs
  
  \return true if iterator is not equal
  */ 
  /***********************************************************************/
   template<typename T> 
  bool list<T>::const_iterator_impl::
       operator!=(const const_iterator_impl& rhs) const
  {
    return !(*this == rhs);
  }

  /***********************************************************************/
  /*!
  \fn   bool list<T>::const_iterator_impl::
                    operator==(const const_iterator_impl& rhs) const
  
  \brief Checks if the iterator is equal to another iterator
  
  \param const iterator_impl& rhs
  
   \return true if iterator is equal
  */ 
  /***********************************************************************/ 
  template<typename T>
  bool list<T>::const_iterator_impl::
              operator==(const const_iterator_impl& rhs) const
  {
    return (_curr == rhs._curr);  
  }

  /***********************************************************************/
  /*!
  \fn   typename list<T>::const_iterator_impl& 
                 list<T>::const_iterator_impl::operator++()
  
  \brief Pre-increment operator overload. Iterates to next node
  
  
  \return Returns the current reference of the iterator
  
  */ 
  /***********************************************************************/
  template<typename T>
  typename list<T>::const_iterator_impl& 
           list<T>::const_iterator_impl::operator++()
  {
    _curr = _curr->_next;
    return *this;
  }

  /***********************************************************************/
  /*!
  \fn typename list<T>::const_iterator_impl& 
               list<T>::const_iterator_impl::operator--()
  
  \brief Pre-decrement operator overload. Iterates to next node
  
  
  \return Returns the current reference of the iterator
  
  */ 
  /***********************************************************************/
  template<typename T>
  typename list<T>::const_iterator_impl& 
           list<T>::const_iterator_impl::operator--()
  {
    if(_curr != nullptr)
    {
      _curr = _curr->_prev;
      return *this;     
    }
    else
    {
      return _last;
    }
  }

  /***********************************************************************/
  /*!
  \fn typename list<T>::const_iterator_impl 
               list<T>::const_iterator_impl::operator++(int)
  
  \brief Post-increment operator overload. Iterates to next node
  
  
  \return Returns the current reference of the iterator
  
  */ 
  /***********************************************************************/
  template<typename T>
  typename list<T>::const_iterator_impl 
           list<T>::const_iterator_impl::operator++(int)
  {
    const_iterator_impl temp = *this;
    ++(*this);
    return temp;
  }

  /***********************************************************************/
  /*!
  \fn   typename list<T>::const_iterator_impl 
                 list<T>::const_iterator_impl::operator--(int)
  
  \brief Post-decrement operator overload. Iterates to next node
  
  
  \return Returns the current reference of the iterator
  
  */ 
  /***********************************************************************/
  template<typename T>
  typename list<T>::const_iterator_impl 
           list<T>::const_iterator_impl::operator--(int)
  {
    const_iterator_impl temp = *this;
    ++(*this);
    return temp;
  }

  /***********************************************************************/
  /*!
  \fn typename list<T>::const_iterator_impl::reference 
               list<T>::const_iterator_impl::operator*() const
  
  \brief dereference operator overload. Get reference to the value
    
  \return Returns the reference to the value inside the iterator
  
  */ 
  /***********************************************************************/
  template<typename T>
  typename list<T>::const_iterator_impl::reference 
           list<T>::const_iterator_impl::operator*() const
  {
    return _curr->_value;
  }

  /***********************************************************************/
  /*!
  \fn list<T>::const_iterator_impl::
             const_iterator_impl(const node* last, const node* curr)
  
  \brief Conversion constructor for const_iterator_impl
    
  */ 
  /***********************************************************************/
  template<typename T>
  list<T>::const_iterator_impl
         ::const_iterator_impl(const node* last, const node* curr) :
  _curr{curr},
  _last{last}
  {}

  /***********************************************************************/
  /*!
  \fn typename list<T>::const_iterator list<T>::cbegin() const
  
  \brief Creates a const begin iterator pointing to the first element of the 
         list
  
  \return Const_iterator to the front of the list
    
  */ 
  /***********************************************************************/
  template <typename T>
  typename list<T>::const_iterator list<T>::cbegin() const
  {
    return {_last, _first};
  }

  /***********************************************************************/
  /*!
  \fn typename list<T>::const_iterator list<T>::cend() const
  
  \brief Creates a const begin iterator pointing to the last element of the 
         list
  
  \return Const_iterator to the end of the list
    
  */ 
  /***********************************************************************/
  template<typename T>
  typename list<T>::const_iterator list<T>::cend() const
  {
    return _last;
  }

  /***********************************************************************/
  /*!
  \fn typename list<T>::const_iterator list<T>::begin() const
  
  \brief Creates a begin iterator pointing to the last element of the 
         list
  
  \return iterator to the start of the list
    
  */ 
  /***********************************************************************/
  template <typename T>
  typename list<T>::const_iterator list<T>::begin() const
  {
    return {_last, _first};
  }

  /***********************************************************************/
  /*!
  \fn typename list<T>::const_iterator list<T>::end() const
  
  \brief Creates an end iterator pointing to the last element of the 
         list
  
  \return iterator to the end of the list
    
  */ 
  /***********************************************************************/  
  template<typename T>
  typename list<T>::const_iterator list<T>::end() const
  {
    return _last;      
  }
 
  /***********************************************************************/
  /*!
  \fn typename list<T>::iterator list<T>::begin()
  
  \brief Creates an iterator pointing to the first element of the 
         list
  
  \return iterator to the start of the list
    
  */ 
  /***********************************************************************/  
  template<typename T> 
  typename list<T>::iterator list<T>::begin()
  {
    return {_last, _first};  
  }

  /***********************************************************************/
  /*!
  \fn typename list<T>::iterator list<T>::end()
  
  \brief Creates an iterator pointing to the last element of the 
         list
  
  \return iterator to the end of the list
    
  */ 
  /***********************************************************************/  
  template<typename T>
  typename list<T>::iterator list<T>::end()
  {
    return _last;       
  }
    
}
