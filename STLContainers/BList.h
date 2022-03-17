/***************************************************************************/
/*! 
\brief  The container is a modified double-linked list 
that has an interface that is a small subset of the std::list interface. 
Clients can use as a container of any type. 
It’s also kind of like a hybrid between a linked-list and an array in that it appears to be a linked-list of arrays. 
The arrays can be sorted or unsorted.
The essential difference from a “standard” linked-list is that each node can contain more than one data item.
A standard linked-list has a one-to-one mapping of items to nodes. This means that a BList that has 2 items
per node will require fewer nodes than a list with nodes containing only 1 item per node. A BList with 4
items per node will require even fewer nodes, and so on. This can provide a significant performance increase
while only requiring some additional complexity in the code.
The BList class will also have the capability to maintain a sort order when using the insert method.
*/ 
/***************************************************************************/ 
#ifndef BLIST_H
#define BLIST_H

#include <string> // error strings

/*!
  The exception class for BList
*/
class BListException : public std::exception
{
  private:
    int m_ErrCode;             //!< One of E_NO_MEMORY, E_BAD_INDEX, E_DATA_ERROR
    std::string m_Description; //!< Description of the exception

  public:
    /*!
      Constructor

      \param ErrCode
        The error code for the exception.

      \param Description
        The description of the exception.
    */
    BListException(int ErrCode, const std::string& Description) :
    m_ErrCode(ErrCode), m_Description(Description) {};

    /*!
      Get the kind of exception

      \return
        One of E_NO_MEMORY, E_BAD_INDEX, E_DATA_ERROR
    */
    virtual int code() const {
      return m_ErrCode;
    }

    /*!
      Get the human-readable text for the exception

      \return
        The description of the exception
    */
    virtual const char *what() const throw() {
      return m_Description.c_str();
    }

    /*!
      Destructor is "implemented" because it needs to be virtual
    */
    virtual ~BListException() {
    }

    //! The reason for the exception
    enum BLIST_EXCEPTION {E_NO_MEMORY, E_BAD_INDEX, E_DATA_ERROR};
};

/*!
  Statistics about the BList
*/
struct BListStats
{
    //!< Default constructor
  BListStats() : NodeSize(0), NodeCount(0), ArraySize(0), ItemCount(0)  {};

  /*! 
    Non-default constructor

    \param nsize
      Size of the node

    \param ncount
      Number of nodes in the list

    \param asize
      Number of elements in each node (array)

    \param count
      Number of items in the list

  */
  BListStats(size_t nsize, int ncount, int asize, int count) : 
  NodeSize(nsize), NodeCount(ncount), ArraySize(asize), ItemCount(count)  {};

  size_t NodeSize; //!< Size of a node (via sizeof)
  int NodeCount;   //!< Number of nodes in the list
  int ArraySize;   //!< Max number of items in each node
  int ItemCount;   //!< Number of items in the entire list
};  

/*!
  The BList class
*/
template <typename T, unsigned Size = 1>
class BList
{
 
  public:
    /*!
      Node struct for the BList
    */
    struct BNode
    {
      BNode *next;    //!< pointer to next BNode
      BNode *prev;    //!< pointer to previous BNode
      unsigned count;      //!< number of items currently in the node
      T values[Size]; //!< array of items in the node

      //!< Default constructor
      BNode() : next(0), prev(0), count(0) {}
    };

    /*************************************************************************/
    /*!
      \fn BList()
    
      \brief Initialises the BList
    */ 
    /*************************************************************************/
    BList();
    
    /*************************************************************************/
    /*!
    \fn BList(const BList &rhs)
    
    \brief Copy constructor for the BList
    
    \param rhs
    */ 
    /*************************************************************************/    
    BList(const BList &rhs);
    
    /*************************************************************************/
    /*!
    \fn ~BList()
    
    \brief Destructor for the BList
    */ 
    /*************************************************************************/    
    ~BList();

    /*************************************************************************/
    /*!
    \fn operator=(const BList &rhs)
    
    \brief Assignment operator for the BList
    
    \param rhs
    
    \return BList<T, Size>&
    */ 
    /*************************************************************************/    
    BList& operator=(const BList &rhs);

    /*************************************************************************/
    /*!
    \fn push_back(const T& value)
    
    \brief pushes back a value into the tail of the BList
    
    \param value
    */ 
    /*************************************************************************/
    void push_back(const T& value);
    
    /*************************************************************************/
    /*!
    \fn push_front(const T& value)
    
    \brief pushes a value into the head of the BList
    
    \param value
    */ 
    /*************************************************************************/    
    void push_front(const T& value);

    /*************************************************************************/
    /*!
    \fn insert(const T& value)
    
    \brief This function inserts a value into the BList in a sorted manner
    
    \param value
    */ 
    /*************************************************************************/
    void insert(const T& value);

    /*************************************************************************/
    /*!
    \fn remove(int index)
    
    \brief This function removes a value in the BList given an index
    
    \param index
    */ 
    /*************************************************************************/
    void remove(int index);
    
    /*************************************************************************/
    /*!
    \fn remove_by_value(const T& value)
    
    \brief This function removes a value in the BList
    
    \param value
    */ 
    /*************************************************************************/   
    void remove_by_value(const T& value);
    
    /*************************************************************************/
    /*!
    \fn find(const T& value) const
    
    \brief This function removes a value in the BList.
           Returns -1 if not found.
    
    \param value
    */ 
    /*************************************************************************/
    int find(const T& value) const;
    
    /*************************************************************************/
    /*!
    \fn operator[](int index)
    
    \brief Subscript operator overload to return a l value in the BList
    
    \param index
    */ 
    /*************************************************************************/
    T& operator[](int index);

    /*************************************************************************/
    /*!
    \fn operator[](int index) const
    
    \brief Subscript operator overload to return a r value in the BList
    
    \param index
    */ 
    /*************************************************************************/    
    const T& operator[](int index) const;

    /*************************************************************************/
    /*!
    \fn size() const
    
    \brief Returns the amount of items inside the BList
    
    \return size_t
    */ 
    /*************************************************************************/
    size_t size() const;
    
    /*************************************************************************/
    /*!
    \fn clear()
    
    \brief Removes all items and nodes in the BList
    t
    */ 
    /*************************************************************************/    
    void clear();
    
    /*************************************************************************/
    /*!
    \fn nodesize(void)
    
    \brief Returns the size of a BNode
    
    \return size_t
    */ 
    /*************************************************************************/
    static size_t nodesize(); 
    
    /*************************************************************************/
    /*!
    \fn GetHead() const
    
    \brief Returns the head of the BList
    
    \return BNode*
    */ 
    /*************************************************************************/
    const BNode *GetHead() const;
    
    /*************************************************************************/
    /*!
    \fn GetStats() const
    
    \brief Returns the stats of the BList
    
    \return BListStats
    */ 
    /*************************************************************************/
    BListStats GetStats() const;

  private:
    BNode *head_; //!< points to the first node
    BNode *tail_; //!< points to the last node
    BListStats stats_;
    
    /*************************************************************************/
    /*!
    \fn CreateNewNode()
    
    \brief Creates a new node in the BList
    
    */ 
    /*************************************************************************/
    BNode* CreateNewNode();
    
    /*************************************************************************/
    /*!
    \fn SplitNode(BNode* node)
    
    \brief Splits the given node into 2 nodes. 
            Transfering half of the elements over.
    
    \return Returns a pointer to the original split node (left side)
    */ 
    /*************************************************************************/
    BNode* SplitNode(BNode* node);
    
    /*************************************************************************/
    /*!
    \fn InsertToArray(BNode* temp,const T& value)
    
    \brief Inserts a value into one of the BList's node, 
            sorting it in the process.
    */ 
    /*************************************************************************/
    void InsertToArray(BNode* temp,const T& value);
    
    /*************************************************************************/
    /*!
    \fn AddValueToCorrectNode(BNode* temp,const T& value)
    
    \brief Inserts a value into either the current node or the next node
    */ 
    /*************************************************************************/
    void InsertToStartArray(BNode* temp,const T& value);
    
    /*************************************************************************/
    /*!
    \fn InsertToStartArray(BNode* temp,const T& value)
    
    \brief Inserts a value into the start of the given  BList's node.
    */ 
    /*************************************************************************/
    void InsertToBackArray(BNode* temp,const T& value);
    
    /*************************************************************************/
    /*!
    \fn InsertToStartArray(BNode* temp,const T& value)
    
    \brief Inserts a value into the back of the given  BList's node.
    */ 
    /*************************************************************************/
    void AddValueToCorrectNode(BNode* temp,const T& value); 
    
    /*************************************************************************/
    /*!
    \fn IndexInBound(int index) const
    
    \brief Checks if the given index is within the bounds of the BList
    
    \return bool
    */ 
    /*************************************************************************/
    bool IndexInBound(int index) const;
    
    /*************************************************************************/
    /*!
    \fn RemoveNode(BNode* temp)
    
    \brief Removes a Node from the BList
    */ 
    /*************************************************************************/
    void RemoveNode(BNode* temp);
};

#include "BList.cpp"

#endif // BLIST_H
