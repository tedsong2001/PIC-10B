#include "BinarySearchTree.hpp"
using namespace pic10b;

// TREE CLASS FUNCTIONS

// deleteTree()
void Tree::deleteTree(node* n) {
    if (n) {
        if (n->left) {
            deleteTree(n->left);
        }
        if (n->right) {
            deleteTree(n->left);
        }
        erase(iterator(n,this));
    }
}

// traverseInsert()
void Tree::traverseInsert(node* n) {
    if (n) { // if n is not nullptr
        insert(n->val); // inserts node
        
        if (n->left) { // if n has a left value
            traverseInsert(n->left); // recursively traverseInsert for the left values
        }
        
        if (n->right) { // if n has a right value
            traverseInsert(n->right); // recursively traverseInsert for the right values
        }
    }
}

// constructor
Tree::Tree() noexcept : root(nullptr), sz(0) {}

// copy constructor
Tree::Tree(const Tree& tree) : root(nullptr), sz(tree.sz) {
    traverseInsert(tree.root); // calls recursive function on nodes to copy
}

// move constructor
Tree::Tree(Tree&& tree) noexcept : Tree() {
    pic10b::swap(*this, tree);
}

// assignment operator
Tree& Tree::operator=(Tree rhs) & {
    pic10b::swap(*this, rhs);
    return *this;
}

// find()
Tree::iterator Tree::find(const double _val) const {
    iterator itr = iterator(root, this); // creates an iterator starting from the root
    
    while (itr != end()) { // iterator goes thru tree
        if (itr.curr->val == _val) { // if value is found
            return itr; // return true
        }
        else if (itr.curr->val > _val) { // if the iterator's val is greater than desired value
            --itr; // decrement iterator
        }
        else if (itr.curr->val < _val) { // if the iterator's val is lesser than desired value
            ++itr; // increment iterator
        }
    }
    
    return iterator(nullptr, this); // return false if desired value was not found in the tree
}

// swap()
void Tree::swap(Tree& tree) {
    std::swap(root, tree.root); // swap root
    std::swap(sz, tree.sz); // swap sz
}

// begin()
Tree::iterator Tree::begin() const {
    if (root == nullptr) { // if there is no root
        return iterator(nullptr, this); // return iterator that is null
    }
    
    node* n = root; // start at the root
    
    while (n->left != nullptr) {
        n = n->left; // go to the leftmost value (lowest value)
    }
    
    return iterator(n, this); // return iterator at leftmost value
}

// end()
Tree::iterator Tree::end() const {
    return iterator(nullptr, this);
}

Tree::iterator Tree::last() const {
    if (root == nullptr) {
        return iterator(nullptr, this);
    }
    
    node* n = root;
    while (n->right != nullptr) {
        n = n->right;
    }
    
    return iterator(n, this);
}

// insert function
void Tree::insert(double val) {
    if (!root) { // if root is empty
        root = new node(std::move(val)); // set root
        ++sz; // increment size
    }
    else { // if there is a root
        node* n = new node(std::move(val)); // create node
        
        root->insertNode(n); // recursively insert the node using insertNode(n)
        ++sz; // increment size
    }
}

// erase()
void Tree::erase(iterator itr) {
    if (root) {
        // if the node has no children and a non-null parent
        if (itr.curr->left==nullptr && itr.curr->right==nullptr && itr.curr->parent) {
            // if the current node is a left child
            if (itr.curr->parent->left == itr.curr) {
                itr.curr->parent->left = nullptr; // set the parent's pointer to null
            }
            else { // if the current node is a right child
                itr.curr->parent->right = nullptr; // set the parent's pointer to null
            }
            
            // delete the current node
            delete itr.curr;
            itr.curr = nullptr;
            
            --sz; // decrement size
        }
        // if the node has only a left child and a non-null parent
        else if (itr.curr->left && itr.curr->right==nullptr && itr.curr->parent) {
            itr.curr->left->parent = itr.curr->parent; // update the parent of the current node's child
            
            if (itr.curr->parent->left == itr.curr) { // if the current node is a left child
                itr.curr->parent->left = itr.curr->left; // update the left child of the current node's parent
            }
            else { // if the current node is a right child
                itr.curr->parent->right = itr.curr->left; // update the left child of the current node's parent
            }
            
            // delete the current node
            delete itr.curr;
            itr.curr=nullptr;
            
            --sz; // decrement size
        }
        
        // if the node has only a right child and a non-null parent
        else if (itr.curr->left==nullptr && itr.curr->right && itr.curr->parent) {
            itr.curr->right->parent = itr.curr->parent; // update the parent of the current node's child
            
            if (itr.curr->parent->left == itr.curr) { // if the current node is a left child
                itr.curr->parent->left = itr.curr->right; // update the left child of the current node's parent
            }
            else { // if the current node is a right child
                itr.curr->parent->right = itr.curr->right; // update the left child of the current node's parent
            }
            
            // delete the current node
            delete itr.curr;
            itr.curr = nullptr;
            
            --sz; // decrement size
        }
        
        // if the node has two children and a non-null parent
        else if (itr.curr->left && itr.curr->right && itr.curr->parent) {
            node* n = itr.curr; // new node
            n = n->right; // go right once
            while (n->left != nullptr) { // go all the way left to the next value of the tree
                n = n->left;
            }
            
            itr.curr->val = n->val; // overwrite the value of the current node to the next value
            erase(iterator(n,this)); // recursively erase
        }
        
        else if (itr.curr->parent == nullptr) { // if the node doesn't have a parent, it's the root
            
            if (itr.curr->right) { // if the root has a right child
                node* n = itr.curr; // new node
                n = n->right; // go right once
                while (n->left != nullptr) { // go all the way to the left
                    n = n->left;
                }
                itr.curr->val = n->val; // overwrite the root with the next high value
                erase(iterator(n,this)); // erase that value
                root = itr.curr; // update root
            }
            else if (itr.curr->left) { // if the root has a left child
                node* n = itr.curr; // new node
                n = n->left; // go left once
                while(n->right != nullptr) { // go all the way to the right
                    n = n->right;
                }
                itr.curr->val = n->val; // overwrite the root with the next low value
                erase(iterator(n, this)); // erase that value
                root = itr.curr; // update root
            }
            else {
                delete itr.curr;
                itr.curr = nullptr;
                
                root = nullptr; // set the root to nullptr
                --sz; // decrement size
            }
        }
    }
}



// NODE CLASS FUNCTIONS

// constructor
Tree::node::node(double _val) : val(_val), left(nullptr), right(nullptr), parent(nullptr) {}

// insertNode()
void Tree::node::insertNode(node* n) {
    if (val < n->val) { // if the current node value is less than n's value
        if (right) { // if there is a right child
            right->insertNode(n); // recursively traverse on the right
        }
        else { // if there is no right child
            right = n; // make n the right child
            n->parent = this;
        }
    }
    else if (val > n->val) { // if the current node value is greater than n's value
        if (left) { // if there is a left child
            left->insertNode(n); // recursively traverse on the left
        }
        else { // if there is no left child
            left = n; // make n the left child
            n->parent = this;
        }
    }
    else { // if n's value is the same as the current node value, nothing to add
        delete n; // so delete n
    }
}



// ITERATOR CLASS FUNCTION

// constructor
Tree::iterator::iterator(node* n, const Tree* tree) : curr(n), CONTAINER(tree) {}

// prefix ++
Tree::iterator& Tree::iterator::operator++() {
    if (curr == nullptr) {
        throw std::logic_error("Invalid address");
    }
    
    else if (curr->right) { // if the current node has a right child
        curr = curr->right; // go to the right
        while (curr->left != nullptr) {
            curr = curr->left; // go all the way to the left
        }
        
        return *this;
    }
    
    else { // if there is no right child
        
        if (*this == CONTAINER->last()) { // if the current position is the end
            curr = nullptr; // set curr to null
            return *this; // return the current iterator
        }
        
        // following code will run if the current position is not the end
        
        while (true) {
            if (curr == curr->parent->right) { // if the current node is a right child
                curr = curr->parent; // set current node to parent
            }
            else { // if the current node is a left child
                curr = curr->parent; // set current node to parent
                return *this; // return the current iterator
            }
        }
    }
}

// postfix ++
Tree::iterator Tree::iterator::operator++(int unused) {
    iterator copy(*this); // create a copy
    ++(*this); // increment original
    return copy; // return the copy
}

// prefix --
Tree::iterator& Tree::iterator::operator--() {
    if (curr == nullptr) {
        curr = CONTAINER->last().curr;
        return *this;
    }
    
    else if (curr->left) { // if the current node has a left child
        curr = curr->left; // go to the left
        while (curr->right != nullptr) {
            curr = curr->right; // go all the way to right
        }
        
        return *this; // return current iterator
    }
    
    else { // if there is no left child
        
        if (*this == CONTAINER->begin()) { // if the current position is the beginning
            curr = nullptr; // set curr to null
            return *this; // return the current iterator
        }
        
        // following code will run if the current position is not the beginning
        
        while (true) {
            if (curr == curr->parent->left) { // if the current node is a left child
                curr = curr->parent; // set current node to parent
            }
            else { // if the current node is a right child
                curr = curr->parent; // set current node to parent
                return *this; // return the current iterator
            }
        }
    }
}

// postfix --
Tree::iterator Tree::iterator::operator--(int unused) {
    iterator copy(*this); // create a copy
    --(*this); // decrement original
    return copy; // return the copy
}


// swap function
void pic10b::swap(Tree& left, Tree& right) {
    left.swap(right);
}

// == operator
bool pic10b::operator==(const Tree::iterator& left, const Tree::iterator& right) {
    return (left.curr == right.curr) && (left.CONTAINER == right.CONTAINER);
}

// != operator
bool pic10b::operator!=(const Tree::iterator& left, const Tree::iterator& right) {
    return !(left==right);
}
