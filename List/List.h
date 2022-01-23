#ifndef _LIST_
#define _LIST_

#include <iostream>
#include <utility>
#include <stdexcept>

namespace pic10b {

    class node;
    class iterator;
    class const_iterator;


    class LinkedList {
        friend iterator; // iterators need to know first element
        friend const_iterator;

        /**
         Swaps 2 LinkedLists
         @param list1 one list
         @param list2 another list
         */
        friend void swap(LinkedList& list1, LinkedList& list2);
        

    private:
        node* first, * last; // pointers to first and last node
        size_t sz; // number of elements in a list

    public:
        /**
         Default constructor
         */
        LinkedList() noexcept;

        
        /**
         Constructor that accepts initializer list
         @param my_list the initializer list
         */
        LinkedList(const std::initializer_list<int>& my_list) noexcept;

        
        /**
         Copy constructor
         @param another the LinkedList that will be copied from
         */
        LinkedList(const LinkedList& another);

        
        /**
         Move constructor
         @param another the LinkedList that will be moved from
         */
        LinkedList(LinkedList&& another) noexcept;

        
        /**
         Destructor
         */
        ~LinkedList();

        
        /**
         Assignment operators (Move and copy)
         @param rhs the LinkedList that will be copied/moved from
         */
        LinkedList& operator=(LinkedList rhs)&;

        
        /**
         Obtains const begin iterator
         @return a const_iterator set to the start
         */
        const_iterator begin() const;

        
        /**
         Obtains const iterator pointing past end
         @return a const_iterator set to past-the-end
         */
        const_iterator end() const;

        
        /**
         Obtains beg iterator
         @return an iterator set to the start
         */
        iterator begin();

        
        /**
         Obtains iterator pointing past end
         @return an iterator set to past-the-end
         */
        iterator end();

        
        /**
         Inserts value before current position
         @param it the iterator (has the current position and container)
         @param val the value that will be inserted
         */
        void insert(iterator it, int val);
        
        
        /**
         Erases value at position
         @param it the iterator (has the current position)
         */
        void erase(iterator it);

        
        /**
         Appends a value
         @param val the value that will be appended
         */
        void push_back(int val);

        
        /**
         Removes from the end
         */
        void pop_back();

        
        /**
         Adds a value to the beginning
         @param val the value that will be added
         */
        void push_front(int val);

        
        /**
         Removes element from beginning
         */
        void pop_front();

        
        /**
         Sorts a LinkedList in order
         */
        void sort();

        
        /**
         Returns the size of a LinkedList (# of elements)
         */
        const size_t& size() const {
            return sz;
        }

    };


    class node {
        friend LinkedList; /* LinkedList needs to construct nodes and
                            know details about them for insertions, deletions, etc. */

        friend iterator; // iterator needs to know next/prev to move, etc.
        friend const_iterator;

    private:
        int val; // the data
        node* prev, * next; // previous and next nodes

        
        /**
         Constructor, in private because user shouldn't be able to create nodes
         @param i the value from which a node will be created
         */
        node(int i);

    };


    class iterator {
        friend LinkedList;

    public:
        /**
         Prefix++, changing current position of iterator forward
         @return updated iterator
         */
        iterator& operator++();

        
        /**
         Postfix++, changing current position of iterator forward
         @param unused unused variable to note postfix
         @return copy of the original iterator
         */
        iterator operator++(int unused);

        
        /**
         Prefix--, changing current position of iterator backward
         @return updated iterator
         */
        iterator& operator--();

        
        /**
         Postfix--, changing current position of iterator backward
         @param unused unused variable to note postfix
         @return copy of the original iterator
         */
        iterator operator--(int unused);

        
        /**
         Dereferencing operator (unary)
         @return the dereferenced value
         */
        int& operator*() const;

        
        /**
         Converts iterator to const_iterator
         */
        operator const_iterator() const;
        
        
        /**
         Checks if 2 iterators are equal
         @param left iterator on the left of operator
         @param right iterator on the right of operator
         @return true if both are equal, false if not
         */
        friend bool operator==(const iterator& left, const iterator& right); // comparison

    private:
        node* curr; // currently managed node
        const LinkedList* container; // the LinkedList

        
        /**
         Constructor, in private because user shouldn't be able to create iterators
         @param n the node to set current postion
         @param ell the container (LinkedList)
         */
        iterator(node* n, const LinkedList* ell);

    };


    class const_iterator {
        friend LinkedList;
        friend iterator;

    public:
        /**
         Prefix++, changing current position of iterator forward
         @return updated iterator
         */
        const_iterator& operator++(); // prefix ++

        
        /**
         Postfix++, changing current position of iterator forward
         @param unused unused variable to note postfix
         @return copy of the original iterator
         */
        const_iterator operator++(int unused); // postfix ++

        
        /**
         Prefix--, changing current position of iterator backward
         @return updated iterator
         */
        const_iterator& operator--(); // prefix --

        
        /**
         Postfix--, changing current position of iterator backward
         @param unused unused variable to note postfix
         @return copy of the original iterator
         */
        const_iterator operator--(int unused); // postfix --

        
        /**
         Dereferencing operator (unary)
         @return the dereferenced value
         */
        const int& operator*() const; // dereferencing operator (unary)

        
        /**
         Checks if 2 const_iterators are equal
         @param left iterator on the left of operator
         @param right iterator on the right of operator
         @return true if both are equal, false if not
         */
        friend bool operator==(const const_iterator& left, const const_iterator& right); // comparison

    private:
        node* curr; // currently managed node
        const LinkedList* container; // the LinkedList

        
        /**
         Constructor, in private because user shouldn't be able to create iterators
         @param n the node to set current postion
         @param ell the container (LinkedList)
         */
        const_iterator(node* n, const LinkedList* ell);

    };

    /**
     Swaps 2 LinkedLists
     @param list1 one list
     @param list2 another list
     */
    void swap(LinkedList& list1, LinkedList& list2);

    // declared for fully qualified lookup
    
    /**
     Checks if 2 iterators are equal
     @param left iterator on the left of operator
     @param right iterator on the right of operator
     @return true if both are equal, false if not
     */
    bool operator==(const iterator& left, const iterator& right);


    /**
     Checks if 2 const_iterators are equal
     @param left iterator on the left of operator
     @param right iterator on the right of operator
     @return true if both are equal, false if not
     */
    bool operator==(const const_iterator& left, const const_iterator& right);


    /**
     Checks if 2 iterators are not equal
     @param left iterator on the left of operator
     @param right iterator on the right of operator
     @return true if not equal, false if equal
     */
    bool operator!=(const iterator& left, const iterator& right);


    /**
     Checks if 2 const_iterators are not equal
     @param left iterator on the left of operator
     @param right iterator on the right of operator
     @return true if not equal, false if equal
     */
    bool operator!=(const const_iterator& left, const const_iterator& right);


    /**
     Ostream operator, outputting the elements of a LinkedList
     @param out output stream
     @param my_list the LinkedList to be outputted
     @return the output stream
     */
    std::ostream& operator<<(std::ostream& out, const LinkedList& my_list); // operator <<


    /**
     Searches if there is a certain value between 2 points
     @param itr1 iterator marking one point
     @param itr2 iterator marking another point
     @param val the certain value
     @return true if value is found, false if not
     */
    bool seqSearch(const const_iterator& itr1, const const_iterator& itr2, size_t val);
}

#endif
