/**
 * @file    bitree.h
 * @brief   Binary Indexed Tree
 * @author  间宫羽咲sama
 * @note    Template implementation of Binary Indexed Tree
 */

#ifndef INC_BINARYINDEXEDTREE_BITREE_CPP
#define INC_BINARYINDEXEDTREE_BITREE_CPP

#include "bitree.h"

template<class T>
BITree<T>::BITree(const BITree<T> &nums)
        : m_tree(nums.m_tree)
        , m_arr(nums.m_arr)
{
}

template<class T>
BITree<T>::BITree(BITree<T> &&nums)
        : m_tree(std::move(nums.m_tree))
        , m_arr(std::move(nums.m_arr))
{
}

template<class T>
BITree<T>::BITree(const std::vector<T> &nums)
        : m_tree(nums.size() + 1)
        , m_arr(nums)
{
    for (size_t i = 0; i < m_arr.size(); ++ i)
        add_impl(i, m_arr[i]);
}

template<class T>
BITree<T>::BITree(std::vector<T> &&nums)
        : m_tree(nums.size() + 1)
        , m_arr(std::move(nums))
{
    for (size_t i = 0; i < m_arr.size(); ++ i)
        add_impl(i, m_arr[i]);
}

template<class T> T
BITree<T>::get(size_t index) const {
    return m_arr[index];
}

template<class T> void
BITree<T>::add_impl(size_t index, T val) {
    for (++ index; index < m_tree.size(); index += index & (-index))
        m_tree[index] += val;
}

template<class T> void
BITree<T>::add(size_t index, T val) {
    m_arr[index] += val;
    add_impl(index, val);
}

template<class T> void
BITree<T>::update(size_t index, T val) {
    add(index, val - get(index));
}

template<class T> T
BITree<T>::sum(size_t index) const {
    T ans = 0;
    for (; index > 0; index &= index - 1)
        ans += m_tree[index];
    return ans;
}

template<class T> T
BITree<T>::sum(size_t left, size_t right) const {
    return sum(right) - sum(left);
}

template<class T> const std::vector<T> &
BITree<T>::get_arr() const {
    return m_arr;
}

template<class T> size_t
BITree<T>::size() const {
    return m_arr.size();
}

template<class T> void
BITree<T>::resize(size_t siz) {
    if (siz == m_arr.size())
        return;

    m_arr.resize(siz);
    // erase all
    m_tree.resize(0);
    m_tree.resize(siz + 1);
    for (size_t i = 0; i < m_arr.size(); ++ i)
        add_impl(i, m_arr[i]);
}

template<class T> typename BITree<T>::iterator
BITree<T>::begin() {
    return BITree<T>::iterator(this, 0);
}

template<class T> typename BITree<T>::iterator
BITree<T>::end() {
    return BITree<T>::iterator(this, size());
}

template<class T> void
BITree<T>::print(std::ostream &os) const {
    auto end_1 = m_arr.end() - 1;
    os << "[";
    for (auto it = m_arr.begin(); it != m_arr.end(); ++ it)
        os << *it << (it != end_1 ? "," : "");
    os << "]";
}

template<class T> std::ostream &
operator<< (std::ostream &os, const BITree<T> &packet) {
    packet.print(os);
    return os;
}

#endif //INC_BINARYINDEXEDTREE_BITREE_CPP
