#include "List.h"
using namespace pic10b;


// default constructor for LinkedList
LinkedList::LinkedList() noexcept : first(nullptr), last(nullptr), sz(0) {}

// constructor for node
node::node(int _val) : val(_val), prev(nullptr), next(nullptr) {}

// constructor for iterator
iterator::iterator(node* n, const LinkedList* ell) : curr(n), container(ell) {}

// constructor for const_iterator
const_iterator::const_iterator(node* n, const LinkedList* ell) : curr(n), container(ell) {}

// constructor accepting initializer list
LinkedList::LinkedList(const std::initializer_list<int>& my_list) noexcept : first(nullptr), last(nullptr), sz(0) {
    for (int i : my_list) { // goes through each element
        push_back(i); // adds each element to list
    }
}

// copy constructor
LinkedList::LinkedList(const LinkedList& another) : first(nullptr), last(nullptr), sz(0) {
    for (int i : another) { // goes through each element
        push_back(i); // adds each element
    }
}

// swap function
void pic10b::swap(LinkedList& list1, LinkedList& list2) {
    std::swap(list1.first, list2.first); // swaps the 2 firsts
    std::swap(list1.last, list2.last); // swaps the 2 lasts
}

// move constructor
LinkedList::LinkedList(LinkedList&& another) noexcept : LinkedList() {
    swap(*this, another); // swaps
}

// destructor
LinkedList::~LinkedList() {
    node* n = first; // start at first node
    while (n != nullptr) { // while n is not nullptr
        node* temp = n->next; // temporarily store next position
        delete n; // deletes the node on heap
        n = temp; // move n right
    }
}

// assignment operator
LinkedList& LinkedList::operator=(LinkedList rhs)& {
    swap(*this, rhs); // swaps with the copy of rhs
    return *this; // returns *this
}

// push_back function
void LinkedList::push_back(int val) {
    node* n = new node(val); // creates new node

    if (last) { // if last node is not null
        last->next = n; // last points to n
        n->prev = last; // makes n have last as its prev
        last = n; // updates last position
    }
    else { // if last is null (if list is empty)
        first = last = n; // both equal to n
    }

    ++sz; // increments size
}

// pop_back function
void LinkedList::pop_back() {
    if (!last) { // if last is null (if list is empty)
        throw std::logic_error("pop_back on empty list");
        // throws an error
    }
    else if (first == last) { // if list contains only 1 element
        delete first; // frees heap
        first = last = nullptr; // both are null --> list is empty

        --sz; // decrements size
    }
    else { // if there are multiple elements
        node* newlast = last->prev; // store the new last node
        newlast->next = nullptr; // set its next pointer to null
        delete last; // free heap memory
        last = newlast; // updates last value

        --sz; // decrements size
    }
}

// push_front function
void LinkedList::push_front(int val) {
    node* n = new node(val);

    if (first) { // if first node is not null
        first->prev = n; // first points to n
        n->next = first; // makes n have first as its next
        first = n; // updates first position
    }
    else {
        last = first = n; // both equal to n
    }

    ++sz; // increments size
}

// pop_front function
void LinkedList::pop_front() {
    if (!first) { // if first is null (if list is empty)
        throw std::logic_error("pop_front on empty list");
        // throws an error
    }
    else if (first == last) { // if list contains only 1 element
        delete last; // frees heap
        last = first = nullptr; // both are null --> list is empty

        --sz; // decrements size;
    }
    else { // if there are multiple elements
        node* newfirst = first->next; // store the new first node
        newfirst->prev = nullptr; // sets its prev pointer to null
        delete first; // free heap memory
        first = newfirst; // updates first value

        --sz; // decrements size;
    }
}

// begin function (for const)
const_iterator LinkedList::begin() const {
    const_iterator _begin(first, this);
    return _begin; // returns iterator to beginning
}

// begin function (for non-const)
iterator LinkedList::begin() {
    iterator _begin(first, this);
    return _begin; // returns iterator to beginning
}

// end function (for const)
const_iterator LinkedList::end() const {
    const_iterator _end(nullptr, this); // last->next means past the end
    return _end; // returns iterator to end
}

// end function (for non-const)
iterator LinkedList::end() {
    iterator _end(nullptr, this); // last->next means past the end
    return _end; // returns iterator to end
}

// insert function
void LinkedList::insert(iterator it, int val) {
    if (it.curr == nullptr) { // if inserting before past-the-end
        push_back(val); // adds val to the end
    }
    else if (it.curr == first) { // if inserting at beginning
        push_front(val); // adds val to the front
    }
    else { // if inserting between elements
        node* n = new node(val);
        n->next = it.curr; // sets n's next
        n->prev = it.curr->prev; // sets n's prev

        it.curr->prev->next = n; // makes current prev's next node into n
        it.curr->prev = n; // makes current prev node into n
        ++sz; // increments size
    }
}

// erase function
void LinkedList::erase(iterator it) {
    if (it.curr == nullptr) { // if erasing before past-the-end
        pop_back(); // erases last
    }
    else if (it.curr == first) { // if erasing at beginning
        pop_front(); // erases first
    }
    else { // if erasing between elements
        it.curr->prev->next = it.curr->next; // sets prev's next
        it.curr->next->prev = it.curr->prev; // sets next's prev
        delete it.curr; // deletes current
        --sz; // decrements size
    }
}

// sort function
void LinkedList::sort() {
    for (iterator itr1 = begin(); itr1 != end(); ++itr1) { // compares a value
        for (iterator itr2 = itr1; itr2 != end(); ++itr2) { // compares that value with every node after
            if (*itr1 > *itr2) { // if a smaller node is found, then the two are swapped
                int temp = *itr1; // itr1 stored in temp
                itr1.curr->val = *itr2; // value of itr1 changed to value of itr2
                itr2.curr->val = temp; // value of itr2 changed to the original value of itr1
            }
        }
    }
}

// operator <<
std::ostream& pic10b::operator<<(std::ostream& out, const LinkedList& my_list) {
    for (auto i : my_list) { // goes through the list
        out << i << ' '; // outputs each element followed by a space
    }
    return out;
}

// ++ prefix
iterator& iterator::operator++() {
    if (curr == nullptr) {
        // can't go past the end
        throw std::logic_error("Invalid address");
    }
    else if (curr == container->last) { // if curr is last
        curr = nullptr; // points to null
    }
    else {
        curr = curr->next; // points to next node
    }
    return *this;
}

// ++ prefix (overloaded on const)
const_iterator& const_iterator::operator++() {
    if (curr == nullptr) {
        // can't go past the end
        throw std::logic_error("Invalid address");
    }
    else if (curr == container->last) { // if curr is last
        curr = nullptr; // points to last
    }
    else {
        curr = curr->next; // points to next node
    }
    return *this;
}

// ++ postfix
iterator iterator::operator++(int unused) {
    iterator copy(*this); // makes a copy
    ++(*this); // increments the original
    return copy; // returns the copy
}

// ++ postfix (overloaded on const)
const_iterator const_iterator::operator++(int unused) {
    const_iterator copy(*this); // makes a copy
    ++(*this); // increments the original
    return copy;
}

// -- prefix
iterator& iterator::operator--() {
    if (curr == container->first) { // can't go before first
        throw std::logic_error("Invalid address"); // throws an error
    }
    else if (curr == nullptr) { // if past the end
        curr = container->last; // points to the last element
    }
    else { // if in the middle
        curr = curr->prev; // points to previous node
    }
    return *this;
}

// -- prefix (overloaded on const)
const_iterator& const_iterator::operator--() {
    if (curr == container->first) { // can't go before first
        throw std::logic_error("Invalid address"); // throws an error
    }
    else if (curr == nullptr) { // if past the end
        curr = container->last; // points to the last element
    }
    else { // if in the middle
        curr = curr->prev; // points to previous node
    }
    return *this;
}

// -- postfix
iterator iterator::operator--(int unused) {
    iterator copy(*this); // makes a copy
    --(*this); // decrements the original
    return copy; // returns the copy
}

// -- postfix (overloaded on const)
const_iterator const_iterator::operator--(int unused) {
    const_iterator copy(*this); // makes a copy
    --(*this); // decrements the original
    return copy; // returns the copy
}

// * operator
int& iterator::operator*() const {
    return curr->val; // return reference to the int stored
}

// * operator for const
const int& const_iterator::operator*() const {
    return curr->val; // return copy of the int stored
}

// converts from iterator to const iterator
iterator::operator const_iterator() const {
    return const_iterator(curr, container);
}

// == for iterator
bool pic10b::operator==(const iterator& left, const iterator& right) {
    return ((left.curr == right.curr) == (left.container == right.container));
}

// == for const_iterator
bool pic10b::operator==(const const_iterator& left, const const_iterator& right) {
    return ((left.curr == right.curr) == (left.container == right.container));
}

// != for iterator
bool pic10b::operator!=(const iterator& left, const iterator& right) {
    return !(left == right); // negated ==
}

// != for iterator
bool pic10b::operator!=(const const_iterator& left, const const_iterator& right) {
    return !(left == right); // negated ==
}

bool pic10b::seqSearch(const const_iterator& itr1, const const_iterator& itr2, size_t val) {
    for (auto i = itr1, end = itr2; i != end; ++i) { // goes through each element in the frame
        if (*i == val) { // if value is found
            return true; // returns true
        }
    }

    return false; // if a value is not found, returns false
}
