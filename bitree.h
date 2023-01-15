/**
 * @file    bitree.h
 * @brief   Binary Indexed Tree
 * @author  间宫羽咲sama
 * @note    Template implementation of Binary Indexed Tree
 */

#ifndef INC_BINARYINDEXEDTREE_BITREE_H
#define INC_BINARYINDEXEDTREE_BITREE_H

#include <iostream>
#include <vector>

/**
 * @brief   Binary Indexed Tree
 * @details The English notes are as follows:
 *          Suppose 'L(x)' represents the lowest bit of 'x', '(101100) is the binary representation
 *          For example, if 'x == 44 == (101100)', then 'L(x) == 4 == (100)'
 *          Suppose 'T(i)' represents the sum of A from the interval of ( i - L(i), i ]
 *          For example, if 'i == (101100)', then 'i - L(i) == (101000)', and 'T(i)' is $\sum_{k=i-L(i)+1}^{i} {A_k}$
 *          In this case, The complexity of the update operation and the sum operation are both $O(log N)$
 *
 *       1. Sum: O(log N)
 *          Notice that: (0, (101100)] = ( (0), (100000) ] + ( (100000), (101000) ] + ( (101000), (101100) ]
 *          The maximum number of operations cannot exceed the number of bits, i.e. O(log N)
 *       2. Update: O(log N)
 *          If you want to modify index (101101), you only need to modify all the intervals containing it,
 *          the following numbers correspond to ( i - L(i), i ] will contain (101101):
 *              (101101), (101110), (110000), (1000000), (10000000), (100000000) ...
 *          But this number cannot exceed the length of the array, at most O(log N)
 *       3. Get: O(1)
 *          copy raw array to make the complexity of the get operation become O(1)
 *
 *
 *          The following content is the same as the English version, just a translated version.
 *          中文注释如下:
 *          记 01 串外面加括号代表数字的二进制表示, 如 (101100) .
 *          记 L(x) 为 x 的最低比特, 例如当 'x == 44 == (101100)' 时, 此时 'L(x) == 4 == (100)'
 *          记 'T(i)' 是 A 在区间 ( i - L(i), i ] 上的求和
 *          例如 'i == (101100)' 时, 有 'i - L(i) == (101000)', 此时 'T(i)' 是 $\sum_{k=i-L(i)+1}^{i} {A_k}$
 *          此时'更新'和'求和'操作的复杂度为 $O(log N)$
 *
 *       1. Sum: O(log N)
 *          注意到 (0, (101100)] = ( (0), (100000) ] + ( (100000), (101000) ] + ( (101000), (101100) ]
 *          最大操作数不超过数字的比特数, 显然为 O(log N)
 *       2. Update: O(log N)
 *          如果想修改 (101101), 只需要修改所有包含它的区间, 以下数字对应 ( i - L(i), i ] 会包含 (101101)
 *              (101101), (101110), (110000), (1000000), (10000000), (100000000) ...
 *          但是这个数字不可能超过数组长度, 最多只有 O(log N)
 *       3. Get: O(1)
 *          拷贝一份原始数组使得获取复杂度变成 O(1)
 */
template<class T>
class BITree {
public:
    // 1. This iterator can interact with algorithm 'lower_bound' in STL
    //    e.g. If you want to find the first element in the range [first, last) which does not compare less than 'val'
    //    You can use std::lower_bound(bt.begin(), bt.end(), val);
    class sum_iterator;
    using iterator = BITree<T>::sum_iterator;
private:
    // 2. Data member
    std::vector<T> m_tree;     // Binary Indexed Tree
    std::vector<T> m_arr;      // Let the get complexity become O(1), at the cost of doubling the space

protected:
    // 3. Only for the faster implementation of the constructor, it will not be called at other times
    virtual void add_impl(size_t index, T val);

public:
    // 4. Constructor
    BITree() = default;
    ~BITree() = default;
    BITree(const BITree &bt);
    BITree(BITree &&bt);
    BITree(const std::vector<T> &nums);
    BITree(std::vector<T> &&nums);


    // 5. All public interfaces: get, add, update, sum, resize
    /**
     * @brief   return A[index]
     * @note    plz ensure 0 <= index < m_arr.size()
     */
    virtual T get(size_t index) const;

    /**
     * @brief   Let A[index] increment by val
     * @note    plz ensure 0 <= index < m_arr.size()
     */
    virtual void add(size_t index, T val);

    /**
     * @brief   Let A[index] update by val, i.e. increment by (val - now_value)
     * @note    plz ensure 0 <= index < m_arr.size()
     */
    virtual void update(size_t index, T val);

    /**
     * @brief   Get the sum of the interval [0, index)
     * @note    plz ensure 0 <= index < m_arr.size() + 1
     */
    virtual T sum(size_t index) const;

    /**
     * @brief   Get the sum of the interval [left, right)
     *          if left > right, return the opposite of the sum of the interval [right, left)
     * @note    plz ensure 0 <= left, right < m_arr.size() + 1
     */
    virtual T sum(size_t left, size_t right) const;

    /**
     * @brief   return m_arr.size()
     */
    virtual size_t size() const;

    /**
     * @brief   resize, if siz < now_size, keep only [0, siz)
     */
    virtual void resize(size_t siz);

    /**
     * @brief   return iterator point to first item
     */
    virtual iterator begin();

    /**
     * @brief   return iterator point to last item
     */
    virtual iterator end();


    // 6. Make it easier to use
    /**
     * @brief   Get raw 'm_arr' for debug or other use
     */
    virtual const std::vector<T> &get_arr() const;


    // 7. For operator<< without the 'friend' keyword
    virtual void print(std::ostream &os) const;


    // 8. Iterator for search the sum, e.g. interact with lower_bound
    struct sum_iterator : public std::iterator<
            std::random_access_iterator_tag,    // iterator_category
            T,                                  // value_type
            size_t,                             // difference_type
            size_t,                             // pointer
            T>                                  // reference
    {
    private:
        BITree<T> *m_bt;
        size_t m_idx;

        using Self = sum_iterator;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = size_t;
        using pointer = size_t;
        using reference = T;
        
    public:
        pointer get_idx() const {return m_idx;}

    public:
        sum_iterator(BITree<T> *bt, size_t idx) : m_bt(bt), m_idx(idx) {}
        sum_iterator(const Self &other) : m_bt(other.m_bt), m_idx(other.m_idx) {}
        sum_iterator(Self &&other) : m_bt(other.m_bt), m_idx(other.m_idx) {}
        sum_iterator& operator=(const Self &other) {m_bt = other.m_bt; m_idx = other.m_idx; return *this;}
        sum_iterator& operator=(Self &&other) {m_bt = other.m_bt; m_idx = other.m_idx; return *this;}
        reference operator*() const {return m_bt->sum(m_idx);}
        Self& operator++() {++ m_idx; return *this;}
        Self  operator++(int) {Self ret_val = *this; ++ (*this); return ret_val;}
        Self& operator+=(difference_type n) {m_idx += n; return *this;}
        Self  operator+(difference_type n) {return Self(m_bt, m_idx + n);}
        Self& operator--() {-- m_idx; return *this;}
        Self  operator--(int) {Self ret_val = *this; -- (*this); return ret_val;}
        Self& operator-=(difference_type n) {m_idx -= n; return *this;}
        Self  operator-(difference_type n) {return Self(m_bt, m_idx - n);}
        bool operator==(Self other) const {return m_idx == other.m_idx;}
        bool operator!=(Self other) const {return !(*this == other);}
        bool operator<(Self other)  const {return m_idx < other.m_idx;}
        bool operator<=(Self other) const {return m_idx <= other.m_idx;}
        bool operator>(Self other)  const {return m_idx > other.m_idx;}
        bool operator>=(Self other) const {return m_idx >= other.m_idx;}
        difference_type operator-(Self other) const {return m_idx - other.m_idx;}
    };
};

template<class T>
std::ostream& operator<< (std::ostream& os, const BITree<T> &packet);



// because of template class connot be divided by '.h' and '.cpp'
#include "bitree.cpp"

#endif //INC_BINARYINDEXEDTREE_BITREE_H
