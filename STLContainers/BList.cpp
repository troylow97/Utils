/*************************************************************************/
/*!
  \fn BList<T, Size>::BList()

  \brief Initialises the BList
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
BList<T, Size>::BList() :
  head_{nullptr},
  tail_{nullptr},
  stats_{nodesize(),0,Size,0}
{}

/*************************************************************************/
/*!
 \fn BList<T, Size>::BList(const BList &rhs)
 
 \brief Copy constructor for the BList
 
 \param rhs
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
BList<T, Size>::BList(const BList &rhs): stats_{rhs.stats_} 
{
    const BNode* original = rhs.head_;
    
    BNode* copy = nullptr;
    BNode* copy_prev = nullptr;
    while (original) 
    {
      copy = new BNode{};
      copy->count = original->count;
      for (unsigned i = 0; i < original->count; ++i)
        copy->values[i] = original->values[i];


      if (copy_prev) 
      {
          copy_prev->next = copy;
          copy->prev = copy_prev;
      }
      else 
          head_ = copy;
      
      copy_prev = copy;
      original = original->next;
    }

    tail_ = copy_prev;
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::~BList()
 
 \brief Destructor for the BList
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
BList<T, Size>::~BList()
{ 
  clear();
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::operator=(const BList &rhs)
 
 \brief Assignment operator for the BList
 
 \param rhs
 
 \return BList<T, Size>&
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
BList<T, Size>& BList<T, Size>::operator=(const BList &rhs)
{
  if(rhs.head_ == head_)
      return *this;
  clear();
  BNode* original = rhs.head_;
  
  BNode* copy = nullptr;
  BNode* copy_prev = nullptr;
  while (original) 
  {
    copy = new BNode{};
    copy->count = original->count;
    for (unsigned i=0; i<original->count; ++i)
      copy->values[i] = original->values[i];


    if (copy_prev) 
    {
        copy_prev->next = copy;
        copy->prev = copy_prev;
    }
    else 
        head_ = copy;
    
    copy_prev = copy;
    original = original->next;
  }

  tail_ = copy_prev;
  stats_ = rhs.stats_;
  return *this;
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::push_back(const T& value)
 
 \brief pushes back a value into the tail of the BList
 
 \param value
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
void BList<T, Size>::push_back(const T& value)
{ 
  if(!head_)
  {
    head_ = CreateNewNode();
    tail_ = head_;
    head_->values[0] = value;
    ++stats_.ItemCount;
    ++head_->count; 
    return;   
  }

  if(tail_->count < Size)
  {
    tail_->values[tail_->count] = value;   
  }
  else
  {
    BNode* temp = CreateNewNode();
    tail_->next = temp;
    temp->prev = tail_;
    tail_ = temp;
    tail_->values[0] = value;
  } 
    
  ++stats_.ItemCount;
  ++tail_->count;    
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::push_front(const T& value)
 
 \brief pushes a value into the head of the BList
 
 \param value
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
void BList<T, Size>::push_front(const T& value)
{ 
  if(!head_)
  {
    head_ = CreateNewNode();
    tail_ = head_;
    head_->values[0] = value;    
    ++stats_.ItemCount;
    ++head_->count; 
    return;      
  }  

  if(head_->count < Size)
  { 
    for (unsigned i = head_->count; i > 0; --i)
    {
      head_->values[i] = head_->values[i - 1];
    }  
    head_->values[0] = value; 
  }
  else
  {
    BNode* temp = CreateNewNode();  
    temp->next = head_;
    head_->prev = temp;
    head_ = temp;
    head_->values[0] = value;
  }
    
  ++stats_.ItemCount;
  ++head_->count;
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::insert(const T& value)
 
 \brief This function inserts a value into the BList in a sorted manner
 
 \param value
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
void BList<T, Size>::insert(const T& value)
{
  BNode* temp = head_;
  if(head_ == nullptr)
  {
    push_front(value);
    return;       
  }
  
  while(temp != nullptr)
  {
    if(Size == 1)
    {
      BNode* insertednode = nullptr;        
      if(temp == head_ && value < temp->values[0])
      {
        push_front(value);
        return;
      }
      else if(value < temp->values[0])
      {
        insertednode = CreateNewNode();
        insertednode->next = temp;
        insertednode->prev = temp->prev;
        temp->prev = insertednode;
        temp->prev->next = insertednode;
        insertednode->values[0] = value;
        ++insertednode->count;
        ++stats_.ItemCount;
        return;
      }
      else if
              (
                temp->next                    && 
                !(value < temp->values[0])    && 
                value < temp->next->values[0]
              )
      {
        insertednode = CreateNewNode();
        insertednode->next = temp->next;
        insertednode->prev = temp;
        temp->next->prev = insertednode;
        temp->next = insertednode;
        insertednode->values[0] = value;
        ++insertednode->count;
        ++stats_.ItemCount;        
        return;        
      }
      else if(!temp->next)
      {
        push_back(value);
        return;
      }
      else
      {
        temp = temp->next;
        continue;
      }
    }
    
    if(value < temp->values[0])
    {
      if(temp != head_)
      {
        unsigned prev_count = temp->prev->count;
        bool prev_has_space = prev_count < Size;
        bool curr_has_space = temp->count < Size;
        
        if(prev_has_space && curr_has_space)
        {        
          InsertToArray(temp->prev,value);
          return;
        }
        if(!prev_has_space && !curr_has_space)
        {
          BNode* left = SplitNode(temp->prev);
          AddValueToCorrectNode(left,value);
          return;          
        }
        if(prev_has_space && !curr_has_space)
        {           
          InsertToArray(temp->prev,value);
          return;
        }
        if(!prev_has_space && curr_has_space)
        {
          if(temp->prev->values[prev_count-1] < value)
          {
            InsertToArray(temp,value);
            return;
          }
          BNode* left = SplitNode(temp->prev);          
          if(value < left->next->values[0])
          { 
            InsertToArray(left,value);
            return;            
          }
          InsertToArray(left->next,value);
          return;            
        }         
      }
      else
      {
        if(temp->count < Size)
        {      
          InsertToArray(temp,value);
          return;           
        }     
        BNode* left = SplitNode(temp);
        AddValueToCorrectNode(left,value);
        return;
      }
    }
   
    temp = temp->next; 
  }
  if(tail_->count < Size)
  {      
    InsertToArray(tail_,value);
    return;
  }     
  BNode* left = SplitNode(tail_);
  AddValueToCorrectNode(left,value);
  while(tail_->next)
    tail_ = tail_->next;  


}

/*************************************************************************/
/*!
 \fn BList<T, Size>::remove(int index)
 
 \brief This function removes a value in the BList given an index
 
 \param index
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
void BList<T, Size>::remove(int index)
{
  if(IndexInBound(index))
  {
    BNode* temp = head_;
    int counter = 0;
    int actual_index = -1;
    while(temp != nullptr)
    {
      for(unsigned i = 0; i < temp->count; ++i)
      {
        if(index == counter)
        {
          actual_index = i;
          for(unsigned j = (actual_index+1); j < temp->count; ++j)
              temp->values[j-1] = temp->values[j];       
          --temp->count;
          --stats_.ItemCount;
          if(temp->count == 0)
          {
            RemoveNode(temp);
          }
            
          return;
        }
        counter++;
      }    
      temp = temp->next;
    }
  }
    
  throw(BListException(
        BListException::E_BAD_INDEX, "Subscript out of range."));        
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::remove_by_value(const T& value)
 
 \brief This function removes a value in the BList
 
 \param value
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
void BList<T, Size>::remove_by_value(const T& value)
{
  for(BNode* node = head_;  node != nullptr; node = node->next)
  {
    for(unsigned i = 0; i < node->count; ++i)
    {
      if(value == node->values[i])
      {
        for(unsigned j = (i+1); j < node->count; ++j)
           node->values[j-1] = node->values[j];         
        --node->count;
        --stats_.ItemCount;
        if(node->count == 0)
        {
          RemoveNode(node);
        }
          
        return;
      }
    }
  }   
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::find(const T& value) const
 
 \brief This function removes a value in the BList.
        Returns -1 if not found.
 
 \param value
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
int BList<T, Size>::find(const T& value) const
{
  BNode* temp = head_;
  int counter = 0;
  while(temp != nullptr)
  {
    for(unsigned i = 0; i < temp->count; ++i)
    {
      if(value == temp->values[i])
      {
        return counter;
      }
      counter++;
    }    
    temp = temp->next;
  }  
  return -1;
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::operator[](int index)
 
 \brief Subscript operator overload to return a l value in the BList
 
 \param index
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
T& BList<T, Size>::operator[](int index)
{
  if(IndexInBound(index))
  {
    BNode* temp = head_;
    int counter = 0;
    while(temp != nullptr)
    {
      for(unsigned i = 0; i < temp->count; ++i)
      {
        if(index == counter)
        {
          return temp->values[i];
        }
        counter++;
      }    
      temp = temp->next;
    }    
  }
   
  return head_->values[0];
}             

/*************************************************************************/
/*!
 \fn BList<T, Size>::operator[](int index) const
 
 \brief Subscript operator overload to return a r value in the BList
 
 \param index
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
const T& BList<T, Size>::operator[](int index) const
{
  if(IndexInBound(index))
  {
    BNode* temp = head_;
    int counter = 0;
    while(temp != nullptr)
    {
      for(unsigned i = 0; i < temp->count; ++i)
      {
        if(index == counter)
        {
          return temp->values[i];
        }
        counter++;
      }    
      temp = temp->next;
    }    
  }
   
  return head_->values[0];  
} 

/*************************************************************************/
/*!
 \fn BList<T, Size>::size() const
 
 \brief Returns the amount of items inside the BList
 
 \return size_t
*/ 
/*************************************************************************/
template <typename T, unsigned Size>   
size_t BList<T, Size>::size() const
{
  return stats_.ItemCount;
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::clear()
 
 \brief Removes all items and nodes in the BList
t
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
void BList<T, Size>::clear()
{
  BNode* current = head_;
  
  while(current)
  {
    head_ = head_->next;
    delete current;
    current = head_;
  }
  stats_.NodeSize = 0;
  stats_.NodeCount = 0;
  stats_.ItemCount = 0;
  head_ = nullptr;
  tail_ = nullptr; 
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::nodesize(void)
 
 \brief Returns the size of a BNode
 
 \return size_t
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
size_t BList<T, Size>::nodesize(void)
{
  return sizeof(BNode);
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::GetHead() const
 
 \brief Returns the head of the BList
 
 \return BNode*
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
const typename BList<T, Size>::BNode* BList<T, Size>::GetHead() const
{
  return head_;
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::GetStats() const
 
 \brief Returns the stats of the BList
 
 \return BListStats
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
BListStats BList<T, Size>::GetStats() const
{
  return stats_;
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::CreateNewNode()
 
 \brief Creates a new node in the BList

*/ 
/*************************************************************************/
template <typename T, unsigned Size>
typename BList<T, Size>::BNode* BList<T, Size>::CreateNewNode()
{
  BNode* ptr = nullptr;
  try
  {
    ptr = new BList<T, Size>::BNode{};
  }
  catch(std::bad_alloc&)
  {
    throw(
            BListException(BListException::E_NO_MEMORY, 
                           "Not enough memory to allocate new node.")
                          );
  }
  ++stats_.NodeCount;
  return ptr;
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::SplitNode(BNode* node)
 
 \brief Splits the given node into 2 nodes. 
        Transfering half of the elements over.

 \return Returns a pointer to the original split node (left side)
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
typename BList<T, Size>::BNode* BList<T, Size>::SplitNode(BNode* node)
{
  if(node->count != Size)
    throw(std::exception());

  //Inserting a new node
  BNode* temp = CreateNewNode();
  temp->next = node->next;
  node->next = temp;
  temp->prev = node;
  if(temp->next != nullptr)  
    temp->next->prev = temp;
  
  //Start splitting
  unsigned index = 0;
  unsigned prevcount = node->count;
  temp->count = Size/2;
  node->count = Size - temp->count;
  for(unsigned i = node->count; i < prevcount; ++i,++index)
  {
    temp->values[index] = node->values[i];
  }
  return node;
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::InsertToArray(BNode* temp,const T& value)
 
 \brief Inserts a value into one of the BList's node, 
        sorting it in the process.
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
void BList<T, Size>::InsertToArray(BNode* temp,const T& value)
{
  int count = temp->count;
  if(!(temp->values[0] < value))
  {
    InsertToStartArray(temp,value);
    return;
  }
  
  int index = -1;
  //find index to insert
  for(int i = 0; i < (count-1); ++i)
  {
    if(!(temp->values[i] < value) || value < temp->values[i+1])
    {
      index = i+1;
      break;
    }
  }
  
  if(index != -1)
  {
    for(int i = (count); i > index; --i)
    {
      temp->values[i] = temp->values[i-1];
    }
    temp->values[index] = value;
  }
  else
  {
    temp->values[count] = value;    
  }
  
  ++temp->count;
  ++stats_.ItemCount;   
}

/*************************************************************************/
/*!
 \fn BList<T, Size>::AddValueToCorrectNode(BNode* temp,const T& value)
 
 \brief Inserts a value into either the current node or the next node
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
void BList<T, Size>::AddValueToCorrectNode(BNode* temp,const T& value)
{
  if(temp->values[temp->count-1] < value && value < temp->next->values[0])
  {
    InsertToArray(temp,value);
    return;
  }
  
  if(value < temp->values[temp->count-1]) 
  {
    InsertToArray(temp,value);
    return;    
  }
  InsertToArray(temp->next,value);
  return;  
 
} 
  
/*************************************************************************/
/*!
 \fn BList<T, Size>::InsertToStartArray(BNode* temp,const T& value)
 
 \brief Inserts a value into the start of the given  BList's node.
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
void BList<T, Size>::InsertToStartArray(BNode* temp,const T& value)
{
  int count = temp->count;
  for(int i = count; i > 0; --i)
  {
    temp->values[i] = temp->values[i-1];
  }
  temp->values[0] = value;
  ++temp->count;
  ++stats_.ItemCount;
  return;  
}    
  
/*************************************************************************/
/*!
 \fn BList<T, Size>::InsertToStartArray(BNode* temp,const T& value)
 
 \brief Inserts a value into the back of the given  BList's node.
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
void BList<T, Size>::InsertToBackArray(BNode* temp,const T& value)
{
  temp->values[temp->count] = value;
  ++temp->count;
  ++stats_.ItemCount;
  return;  
}
  
/*************************************************************************/
/*!
 \fn BList<T, Size>::IndexInBound(int index) const
 
 \brief Checks if the given index is within the bounds of the BList
 
 \return bool
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
bool BList<T, Size>::IndexInBound(int index) const
{
  if(index < 0 || index >= stats_.ItemCount)
  {
    throw(BListException(
          BListException::E_BAD_INDEX, "Subscript out of range."));    
    return false;
  }
  return true;
}
  
/*************************************************************************/
/*!
 \fn BList<T, Size>::RemoveNode(BNode* temp)
 
 \brief Removes a Node from the BList
*/ 
/*************************************************************************/
template <typename T, unsigned Size>
void BList<T, Size>::RemoveNode(BNode* temp)
{
  BNode* temp2 = temp;
  
  if(temp == head_)
  {
    head_ = temp->next;
    delete temp2;
    --stats_.NodeCount;
    return;
  }
  
  if(temp == tail_ && temp->prev)
  {
    temp->prev->next = nullptr;
  }
  
  temp->prev->next = temp->next;
  if(temp->next)
    temp->next->prev = temp->prev;
  delete temp2;
  --stats_.NodeCount;
}
