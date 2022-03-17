#ifndef _LIST_H_
#define _LIST_H_

#include <initializer_list>
#include <iterator>

namespace CustomSTL
{
  template <typename T>
  class list
  {
    struct node
    {
      node* _prev;
      node* _next;
      T _value;

      node(const T& value, node* prev = nullptr, node* next = nullptr) :
        _prev(prev),
        _next(next),
        _value(value)
      {
      }
    };

    node* _first;
    node* _last;

  public:

    class iterator_impl
    {
      node* _curr;
      node* _last;
    public:
      using iterator_category = std::bidirectional_iterator_tag;
      using value_type = T;
      using difference_type = ptrdiff_t;
      using pointer = value_type*;
      using reference = value_type&;

      bool operator!=(const iterator_impl& rhs) const;

      bool operator==(const iterator_impl& rhs) const;

      iterator_impl& operator++();

      iterator_impl& operator--();

      iterator_impl operator++(int);

      iterator_impl operator--(int);

      reference operator*() const;

      iterator_impl(node* last, node* curr = nullptr);
    };

    class const_iterator_impl
    {
      const node* _curr;
      const node* _last;
    public:
      using iterator_category = std::bidirectional_iterator_tag;
      using value_type = typename iterator_impl::value_type;
      using difference_type = typename iterator_impl::difference_type;
      using pointer = const value_type*;
      using reference = const value_type&;
    /**********************************************************************/
    /*!
    \fn    bool list<T>::const_iterator_impl::
          operator!=(const const_iterator_impl& rhs) const
    
    \brief Checks if the iterator is not equal to another iterator
    
    \param const iterator_impl& rhs
    
    \return true if iterator is not equal
    */ 
    /**********************************************************************/
      bool operator!=(const const_iterator_impl& rhs) const;
      
    /**********************************************************************/
    /*!
    \fn   bool list<T>::const_iterator_impl::
                      operator==(const const_iterator_impl& rhs) const
    
    \brief Checks if the iterator is equal to another iterator
    
    \param const iterator_impl& rhs
    
    \return true if iterator is equal
    */ 
    /**********************************************************************/ 
      bool operator==(const const_iterator_impl& rhs) const;
      
    /**********************************************************************/
    /*!
    \fn   typename list<T>::const_iterator_impl& 
                  list<T>::const_iterator_impl::operator++()
    
    \brief Pre-increment operator overload. Iterates to next node
    
    
    \return Returns the current reference of the iterator
    
    */ 
    /**********************************************************************/
      const_iterator_impl& operator++();
      
    /**********************************************************************/
    /*!
    \fn typename list<T>::const_iterator_impl& 
                list<T>::const_iterator_impl::operator--()
    
    \brief Pre-decrement operator overload. Iterates to next node
    
    
    \return Returns the current reference of the iterator
    
    */ 
    /**********************************************************************/
      const_iterator_impl& operator--();
      
    /**********************************************************************/
    /*!
    \fn typename list<T>::const_iterator_impl 
                list<T>::const_iterator_impl::operator++(int)
    
    \brief Post-increment operator overload. Iterates to next node
    
    
    \return Returns the current reference of the iterator
    
    */ 
    /**********************************************************************/
      const_iterator_impl operator++(int);   
      
    /**********************************************************************/
    /*!
    \fn   typename list<T>::const_iterator_impl 
                  list<T>::const_iterator_impl::operator--(int)
    
    \brief Post-decrement operator overload. Iterates to next node
    
    
    \return Returns the current reference of the iterator
    
    */ 
    /**********************************************************************/
      const_iterator_impl operator--(int);
      
    /**********************************************************************/
    /*!
    \fn typename list<T>::const_iterator_impl::reference 
                list<T>::const_iterator_impl::operator*() const
    
    \brief dereference operator overload. Get reference to the value
      
    \return Returns the reference to the value inside the iterator
    
    */ 
    /**********************************************************************/
      reference operator*() const;
      
    /**********************************************************************/
    /*!
    \fn list<T>::const_iterator_impl::
              const_iterator_impl(const node* last, const node* curr)
    
    \brief Conversion constructor for const_iterator_impl
      
    */ 
    /**********************************************************************/
      const_iterator_impl(const node* last, const node* curr = nullptr);
    };

    using size_type = size_t;
    using iterator = iterator_impl;
    using const_iterator = const_iterator_impl;
    using difference_type = typename iterator::difference_type;
    using value_type = typename iterator::value_type;
    using pointer = typename iterator::pointer;
    using const_pointer = typename const_iterator::pointer;
    using reference = typename iterator::reference;
    using const_reference = typename const_iterator::reference;
    /**********************************************************************/
    /*!
    \fn list<T>::list()
    \brief Default constructor for list
    */ 
    /**********************************************************************/  
    list();
    
    /**********************************************************************/
    /*!
    \fn list<T>::list(TInputIterator current, TInputIterator end)
    \brief For Range Loop Constructor
    */ 
    /**********************************************************************/  
    template<typename TInputIterator>
    list(TInputIterator begin, TInputIterator end);
    
    /**********************************************************************/
    /*!
    \fn list<T>::list(std::initializer_list<T> values)
    \brief   Initializer list Constructor
    */ 
  /**********************************************************************/  
    list(std::initializer_list<T> values);
    
    /**********************************************************************/
    /*!
    \fn list<T>::list(const list& rhs) : list(rhs.begin(), rhs.end())
    \brief Copy constructor for list
    */ 
    /**********************************************************************/  
    list(const list&);
    
    /**********************************************************************/
    /*!
    \fn list<T>::~list()
    \brief Default destructor for list
    */ 
    /**********************************************************************/ 
    ~list();
    
    /**********************************************************************/
    /*!
    \fn list<T>& list<T>::operator=(const list& rhs)
    \brief Copy assignment operator overload. Used to copy one list to another
    \param rhs 
              Reference of the list being copied to this list
    \returns Reference to the newly copied list
    */ 
    /**********************************************************************/  
    list& operator=(const list&);
    
    /**********************************************************************/
    /*!
    \fn typename list<T>::reference list<T>::front()
    \brief   Returns a reference to the first value
    \returns dereferenced to the list
    */ 
    /**********************************************************************/ 
    reference front();
    
    /**********************************************************************/
    /*!
    \fn typename list<T>::const_reference list<T>::front() const
    \brief   Returns a reference to the first value
    \returns dereferenced to the list
    */ 
    /**********************************************************************/  
    const_reference front() const;
    
    /**********************************************************************/
    /*!
    \fn void list<T>::push_back(const value_type& value)
    \brief  Adds an element at the back of the list.
    \param  value 
            value of the element to be added
    */ 
    /**********************************************************************/  
    void push_back(const value_type& value);
    
    /**********************************************************************/
    /*!
    \fn void list<T>::pop_front()
    \brief  Removes an element at the back of the list.
    */ 
    /***********************************************************************/  
    void pop_front();

    /**********************************************************************/
    /*!
    \fn bool list<T>::empty() const
    \brief Check if list is empty
    \return true if list is empty.
    */ 
    /**********************************************************************/  
    bool empty() const;

    /**********************************************************************/
    /*!
    \fn typename list<T>::const_iterator list<T>::cbegin() const
    
    \brief Creates a const begin iterator pointing to the first element of the 
          list
    
    \return Const_iterator to the front of the list
      
    */ 
    /***********************************************************************/
    const_iterator cbegin() const;

    /************************************************************************/
    /*!
    \fn typename list<T>::const_iterator list<T>::cend() const
    
    \brief Creates a const begin iterator pointing to the last element of the 
          list
    
    \return Const_iterator to the end of the list
      
    */ 
    /*************************************************************************/
    const_iterator cend() const;

    /************************************************************************/
    /*!
    \fn typename list<T>::const_iterator list<T>::begin() const
    
    \brief Creates a begin iterator pointing to the last element of the 
          list
    
    \return iterator to the start of the list
      
    */ 
    /************************************************************************/
    const_iterator begin() const;

    /***********************************************************************/
    /*!
    \fn typename list<T>::const_iterator list<T>::end() const
    
    \brief Creates an end iterator pointing to the last element of the 
          list
    
    \return iterator to the end of the list
      
    */ 
    /***********************************************************************/  
    const_iterator end() const;

    /***********************************************************************/
    /*!
    \fn typename list<T>::iterator list<T>::begin()
    
    \brief Creates an iterator pointing to the first element of the 
          list
    
    \return iterator to the start of the list
      
    */ 
    /***********************************************************************/  
    iterator begin();

    /***********************************************************************/
    /*!
    \fn typename list<T>::iterator list<T>::end()
    
    \brief Creates an iterator pointing to the last element of the 
          list
    
    \return iterator to the end of the list
      
    */ 
    /***********************************************************************/  
    iterator end();
  };
}

#include "list.tpp"

#endif
