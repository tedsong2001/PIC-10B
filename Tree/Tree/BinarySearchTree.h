#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_

#include <string>
#include <stdexcept>

namespace pic10b {

    class Tree {

    private:

        class node; // nested node class

        node* root; // root of the tree
        std::size_t sz;

        /**
         Recursively deletes the tree
         @param n the node to be deleted
         */
        void deleteTree(node* n);

        /**
         Helps with copying
         @param n the node
         */
        void traverseInsert(node* n);

    public:

        class iterator; // nested iterator class

        /**
         Default constructor
         */
        Tree() noexcept;

        /**
         Destructor
         */
        ~Tree();

        /**
         Copy constructor
         @param tree the other tree to be copied
         */
        Tree(const Tree& tree);

        /**
         Move constructor
         @param tree the other tree to be moved
         */
        Tree(Tree&& tree) noexcept;

        /**
         Assignment operators
         @param rhs the tree to be copied/moved
         */
        Tree& operator=(Tree rhs)&;

        /**
        Checks to see if the tree contains a double
        @param _val the specific double
        @return true if found, false if not
        */
        iterator find(const double _val) const;

        /**
        Swaps two trees
        @param tree the other tree to be swapped
        */
        void swap(Tree& tree);

        /**
         Sets iterator to begin position
         @return the iterator that is set to begin position
         */
        iterator begin() const;

        /**
         Sets iterator to end position
         @return the iterator that is set to end position
         */
        iterator end() const;

        /**
         Adds a value to the tree
         @param val the double value to be added
         */
        void insert(double val);

        /**
         Erases a value
         @param itr the iterator with the position to be deleted
         */
        void erase(iterator itr);

        /**
         Accesses the number of elements on a tree (size)
         @return size
         */
        std::size_t& size();

    };

    class Tree::node {

        friend Tree; // tree member functions may search through nodes
        friend iterator; // to be able to advance by checking node values

    private:

        /**
         Constructor
         @param _val the double value from which the node will be created
         */
        node(double _val);

        double val; // data value stored
        node* left, * right; // children
        node* parent; // parent


        /**
         Inserts a node
         @param n the node to be inserted
         @return true if successful insertion, false if not
         */
        bool insertNode(node* n);

    };

    class Tree::iterator {

        friend Tree; // to allow the iterator modifications by Tree operations

    private:

        /**
         Constructor
         @param n the node
         @param tree the tree that the iterator will go through
         */
        iterator(node* n, const Tree* tree);

        node* curr; // current position
        const Tree* container; // holding container

    public:

        /**
        Prefix ++ operator
        @return the updated iterator
        */
        iterator &operator++();

        /**
        Postfix ++ operator
        @param unused informs compiler that function is postfix
        @return the copy of the iterator
        */
        iterator operator++(int unused);

        /**
        Prefix-- operator
        @return the updated iterator
        */
        iterator &operator--();

        /**
        Postfix -- operator
        @param unused informs compiler that function is postfix
        @return the copy of the iterator
        */
        iterator operator--(int unused);

        /**
        Dereferencing operator
        @return the double at the current node
        */
        const double& operator*() const;

        /**
        Arrow operator
        @return the current position dereferenced
        */
        const double* operator->() const {
            return & (curr->val);
        }

        /**
        Checks to see if two iterators are the same
        @param left an iterator
        @param right another iterator for comparison
        @return true if both are equal, false if not
        */
        friend bool operator==(const Tree::iterator& left, const Tree::iterator& right);
    };

    /**
     Swaps two trees
     @param left a tree to be swapped
     @param right the other tree to be swapped
     */
    void swap(Tree& left, Tree& right);

    /**
    Checks to see if two iterators are the same
    @param left an iterator
    @param right another iterator for comparison
    @return true if both are equal, false if not
    */
    bool operator==(const Tree::iterator& left, const Tree::iterator& right);

    /**
    Checks to see if two iterators are different
    @param left an iterator
    @param right another for comparison
    @return true if iterators are different, false if they are the same
    */
    bool operator!=(const Tree::iterator& left, const Tree::iterator& right);

}


#endif
