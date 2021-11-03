#include "BinarySearchTree.h"
using namespace pic10b;

// Default constructor for tree
Tree::Tree() noexcept : root(nullptr), sz(0) {}

// Copy constructor
Tree::Tree(const Tree& tree) : root(nullptr) {
    traverseInsert(tree.root); // calls a recursive function on nodes to copy
}

// Move constructor
Tree::Tree(Tree&& tree) noexcept : Tree() {
    pic10b::swap(*this, tree);
}

// Destructor
Tree::~Tree() {
    deleteTree(root);
}

// Delete Tree
void Tree::deleteTree(Tree::node* n) {
    if (n != nullptr) {
        if (n->left != nullptr) {
            deleteTree(n->left);
        }
        else {
            return;
        }

        if (n->right != nullptr) {
            deleteTree(n->left);
        }
        else {
            return;
        }

        delete n;
        n = nullptr;
    }

    else {
        return;
    }
}

// Find function
Tree::iterator Tree::find(const double _val) const {
    Tree::iterator itr(root, this);

    while (itr != end()) { // while itr hasn't reached the end
        if (itr.curr->val == _val) { // if _val is found
            return itr; // return the itr
        }
        else if (itr.curr->val < _val) { // if current val is less than _val
            ++itr; // increments itr
        }
        else if (itr.curr->val > _val) { // if current val is greater than _val
            --itr; // decrements itr
        }
    }

    return Tree::iterator(nullptr, this); // if not found, returns nullptr itr
}

// Assignment operator
Tree& Tree::operator=(Tree rhs)& {
    pic10b::swap(*this, rhs); // swaps this and the copy of rhs
    return *this; // returns the newly created Tree
}

// traverseInsert
void Tree::traverseInsert(Tree::node* n) {
    if (n != nullptr) {
        insert(n->val); // inserts node
        if (n->left != nullptr) { // if n has a left value
            traverseInsert(n->left); // recursive call
        }

        if (n->right != nullptr) { // if n has a right value
            traverseInsert(n->right); // recursive call
        }
    }
}

// Swap member function
void Tree::swap(Tree& tree) {
    std::swap(root, tree.root); // swaps root
    std::swap(sz, tree.sz); // swaps size
}

// Sets iterator to begin
Tree::iterator Tree::begin() const { // return type requires scope
    if (root == nullptr) { // if root is null then tree empty
        return iterator(nullptr, this); // retrun iterator that is null
    }

    node* n = root; // start at the root
    while (n->left != nullptr) { // while we can still go left (to lower value)
        n = n->left; // go left
    }

    return iterator(n, this); // return iterator for node of smallest value
}

// End iterator means "past the end" and should store null
Tree::iterator Tree::end() const {
    return iterator(nullptr, this);
}

// Insert a value to tree
void Tree::insert(double val) {
    if (!root) { // if root is empty
        // make a new node and set this to be root
        root = new node(std::move(val));
        ++sz; // updates size
    }
    else { // otherwise
        node* n = new node(std::move(val)); // create new node

        // and recursively pass it node to node until in place
        if (root->insertNode(n)) {
            ++sz;
        }
    }
}

// Erase function

void Tree::erase(Tree::iterator itr) {
    if (root) { // if there is a root. (if there isn't, there's nothing to erase)
        node* n = itr.curr;

        // if no child
        if ((n->right == nullptr) && (n->left == nullptr)) {
            if (n->parent != nullptr) { // if n has a parent
                if (n == n->parent->right) { // if n is the right child of its parent
                    n->parent->right = nullptr; // n's parent's right now points to null
                }
                else if (n == n->parent->left) { // if n is the left child of its parent
                    n->parent->left = nullptr; // n's parent's left now points to null
                }

                delete n; // delete n
                n = nullptr;

                --sz; // size update
            }
        }

        // if n only has a left child
        else if ((n->left != nullptr) && (n->right == nullptr)) {
            if (n->parent != nullptr) { // if n has a parent
                n->left->parent = n->parent; // left's child's parent is now n's parent

                if (n == n->parent->right) { // if n is its parent's right
                    n->parent->right = n->left; // n's parent's right child is now n's left
                }
                else if (n == n->parent->left) { // if n is its parent's left
                    n->parent->left = n->left; // n's parent's left child is now n's left
                }

                delete n; // delete n
                n = nullptr;

                --sz; // size update
            }
        }

        // if n only has a right child
        else if ((n->right != nullptr) && (n->left == nullptr)) {
            if (n->parent != nullptr) { // if n has a parent
                n->right->parent = n->parent; // right's child's parent is now n's parent

                if (n == n->parent->right) { // if n is its parent's right
                    n->parent->right = n->right; // n's parent's right is now n's right
                }
                else if (n == n->parent->left) { // if n is its parent's left
                    n->parent->left = n->right; // n's parent's left is now n's right
                }

                delete n; // delete n
                n = nullptr;

                --sz; // size update
            }
        }

        // if n has 2 children
        else {
            if (n->parent != nullptr) { // if n has a parent
                node* temp = n->right; // temporary node set to n's right child
                while (temp->left != nullptr) { // while temp's left value is not null
                    temp = temp->left; // goes as left as possible
                }

                n->val = temp->val; // overrides node's value with the right-far-left value
                Tree::iterator _itr(temp, itr.container); // creates iterator
                erase(_itr); // recursive call

                delete n;
                n = nullptr;

                --sz;
            }
            else {
                return;
            }
        }
    }
}

// Returns size
std::size_t& Tree::size() {
    return sz;
}




// Node constructor
Tree::node::node(double _val) : val(_val), left(nullptr), right(nullptr), parent(nullptr) {}

// Insert a node to the tree
bool Tree::node::insertNode(node* n) {

    // if this value is less than new node value, new node should go right
    if (val < n->val) {
        if (right) {
            right->insertNode(n); // recurse on the right child
        }
        else { // if the right child is null
            right = n; // make this the right child
            n->parent = this;
        }
        return true;
    }

    // if this value is larger than new node value, new node should go left
    else if (val > n->val) {
        if (left) { // if this node has a left child
            left->insertNode(n); // recurse on the left child
        }
        else { // if the left child is null
            left = n; // make this the left child
            n->parent = this;
        }
        return true;
    }

    else {
        // nothing to add if new node value neither < nor > than current value
        delete n; // but we should free the allocated node memory
    }
    return false;
}


// iterator constructor
Tree::iterator::iterator(Tree::node* n, const Tree* tree) : curr(n), container(tree) {}

// ++ prefix
Tree::iterator& Tree::iterator::operator++() {
    if (curr == nullptr) { // if curr is null
        throw std::logic_error("Invalid address"); // throw error
    }
    else if (curr->right != nullptr) { // if curr has a right child
        curr = curr->right; // goes right
        while (curr->left != nullptr) { // then goes all the way left until curr reaches null
            curr = curr->left;
        }
    }
    else if (curr->right == nullptr) { // if curr does not have a right child
        if (curr->parent != nullptr) { // if curr has a parent
            if (curr == curr->parent->left) { // curr is a left child
                curr = curr->parent; // curr is now set to its parent
            }
            else if (curr == curr->parent->right) { // if curr is a right child
                while (curr->parent != nullptr) { // while curr still has a parent
                    if (curr == curr->parent->right) { // if curr is a right child
                        curr = curr->parent; // curr is set to its parent
                    }
                    else {
                        break;
                    }
                }
                /* at this point, curr is possibly a left child but it is not the desired position.
                curr is still less than the original curr */
                if (curr->parent != nullptr) { // if curr has a parent
                    curr = curr->parent; // curr is set to its parent
                }
                else { // if curr does not have a parent (meaning root is reached)
                    curr = nullptr; // set to nullptr,
                    // means that curr was the greatest value in the tree
                }
            }
        }
        else { // if curr does not have a parent
            curr = nullptr; // set to nullptr
        }
    }
    return *this; // return iterator
}

// ++ postfix
Tree::iterator Tree::iterator::operator++(int unused) {
    iterator copy(*this); // makes a copy
    ++(*this); // increments original
    return copy; // returns copy
}

// -- prefix
Tree::iterator& Tree::iterator::operator--() {
    if (curr == nullptr) {
        curr = this->container->root;

        while (curr->right != nullptr) {
            curr = curr->right;
        }
    }
    else if (curr == container->begin().curr) {
        curr = nullptr;
    }
    else if (curr->left != nullptr) {
        curr = curr->left;
        while (curr->right != nullptr) {
            curr = curr->right;
        }
    }
    else if (curr->left == nullptr) {
        if (curr->parent != nullptr) {
            if (curr == curr->parent->right) {
                curr = curr->parent;
            }
            else if (curr == curr->parent->left) {
                while (curr->parent != nullptr) {
                    curr = curr->parent;
                }
                if (curr->parent != nullptr) {
                    curr = curr->parent;
                }
                else {
                    curr = nullptr;
                }
            }
        }
        else {
            curr = nullptr;
        }
    }
    return *this;
}

// -- postfix
Tree::iterator Tree::iterator::operator--(int unused) {
    iterator copy(*this);
    --(*this);
    return copy;
}

// * operator
const double& Tree::iterator::operator*() const {
    return curr->val;
}

// swap function
void pic10b::swap(Tree& left, Tree& right) {
    left.swap(right);
}

// == operator
bool pic10b::operator==(const Tree::iterator& left, const Tree::iterator& right) {
    return ((left.curr == right.curr) && (left.container == right.container));
}

// != operator
bool pic10b::operator!=(const Tree::iterator & left, const Tree::iterator& right) {
    return !(left == right);
}
