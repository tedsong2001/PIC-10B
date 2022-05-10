#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include <string>
#include <stdexcept>

namespace pic10b {

    class Tree {
    private:
        class node;
        node* root;
        std::size_t sz;
        
        /**
         Deletes a tree at certain node
         @param n the node
         */
        void deleteTree(node* n);
        
        /**
         Inserts a node and its children via recursive call (helps with copy constructing)
         @param n the node
         */
        void traverseInsert(node* n);
        
    public:
        class iterator;
        
        /**
         Default constructor
         */
        Tree() noexcept;
        
        ~Tree() {
            deleteTree(root);
        }
        
        /**
         Copy constructor
         @param tree tree to be copied
         */
        Tree(const Tree& tree);
        
        /**
         Move constructor
         @param tree tree to be moved
         */
        Tree(Tree&& tree) noexcept;
        
        /**
         Assignment operator
         @param rhs the tree on the right side of the =
         @return new tree with the values of rhs
         */
        Tree& operator=(Tree rhs)&;
        
        /**
         Searches if the tree has a given value
         @param _val the given value
         @return true if found, false if not
         */
        iterator find(const double _val) const;
        
        /**
         Swaps of the current tree and another tree
         @param tree tree to swap
         */
        void swap(Tree& tree);
        
        /**
         Sets iterator at beginning position
         @return iterator at the beginning position
         */
        iterator begin() const;
        
        /**
         Sets iterator at end position
         @return iterator at the end position
         */
        iterator end() const;
        
        /**
        Sets iterator the last element of the tree
        @return the iterator at last element
        */
        iterator last() const;
        
        /**
         Inserts a value into the tree
         @param val the value
         */
        void insert(double val);
        
        /**
         Erases a value set at the iterator
         @param itr iterator
         */
        void erase(iterator itr);
        
        /**
         Accesses the size of a tree
         @return sz
         */
        std::size_t& size() { return sz; }
    };


    class Tree::node {
        friend Tree;
        friend iterator;
        
    private:
        /**
         Constructor
         @param _val value of the node
         */
        node(double _val);
        
        double val;
        node *left, *right;
        node* parent;
        
        /**
         Recursively inserts a node into the tree
         @param n the node to be added
         */
        void insertNode(node* n);
        
    };


    class Tree::iterator {
        friend Tree;
        
    private:
        /**
         Constructor
         @param n node
         @param tree the binary search tree
         */
        iterator(node* n, const Tree* tree);
        
        node* curr;
        const Tree* CONTAINER;
        
    public:
        /**
         Prefix ++
         @return incremented iterator
         */
        iterator& operator++();
        
        /**
         Postfix ++
         @return copy of the original iterator
         */
        iterator operator++(int unused);
        
        /**
         Prefix --
         @return decremented iterator
         */
        iterator& operator--();
        
        /**
         Postfix --
         @return copy of the original iterator
         */
        iterator operator--(int unused);
        
        /**
         Dereferencing operator
         @return the value of the current node
         */
        const double& operator*() const {
            return curr->val;
        }
        
        /**
         Arrow operator
         @return the reference to the value of the current node
         */
        const double* operator->() const {
            return &(curr->val);
        }
        
        /**
         Checks if two iterators are the same
         @param left iterator 1
         @param right iterator 2
         @return true if same, false if not
         */
        friend bool operator==(const Tree::iterator& left, const Tree::iterator& right);
        
    };

    /**
     Swaps the contents of two trees
     @param left first tree
     @param right second tree
     */
    void swap(Tree& left, Tree& right);

    /**
     Checks if two iterators are the same
     @param left iterator 1
     @param right iterator 2
     @return true if same, false if not
     */
    bool operator==(const Tree::iterator& left, const Tree::iterator& right);

    /**
     Checks if two iterators are the different
     @param left iterator 1
     @param right iterator 2
     @return true if different, false if not
     */
    bool operator!=(const Tree::iterator& left, const Tree::iterator& right);

} // end of pic10b namespace

#endif /* BinarySearchTree_hpp */
