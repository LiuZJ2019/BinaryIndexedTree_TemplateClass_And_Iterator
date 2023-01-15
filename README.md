# BinaryIndexedTree_TemplateClass_And_Iterator

![cpp version](https://img.shields.io/badge/C%2B%2B-C%2B%2B11-brightgreen) ![License](https://shields.io/badge/license-MIT-green)


## README-English-Version

This project implements the **Binary Indexed Tree** with template. It can obtain the prefix sum in $O\left(\log N\right)$ time, add or update one item in $O\left(\log N\right)$ time, random-access in $O\left(1\right)$ time.

At the same time, we provide a **random access iterator** of the prefix sum. The iterator can interact well with many STL algorithms. For example, If you want to find the first element in the range `[first, last)` which does not compare less than `val`, you can use `std::lower_bound(bt.begin(), bt.end(), val)` to find it in $O\left(\log^2 N\right)$ time.

 The full function is listed below (as a demo):

```c++
template<class T>
class BITree {
// data member
private:
    std::vector<T> m_tree;     // Binary Indexed Tree
    std::vector<T> m_arr;
    ...
    
// public interface
public:
    // fun1: random-access
    virtual T get(size_t index) const;
    // fun2: add
    virtual void add(size_t index, T val);
    // fun3: update
    virtual void update(size_t index, T val);
    // fun4: sum[0:index]
    virtual T sum(size_t index) const;
    // fun5: sum[left:right]
    virtual T sum(size_t left, size_t right) const;
    // fun6: length of m_arr
    virtual size_t size() const;
    // fun7: resize
    virtual void resize(size_t siz);
    // fun8: get begin sum_iterator, to adapt STL algoritm
    virtual iterator begin();
    // fun9: get end sum_iterator, to adapt STL algoritm
    virtual iterator end();
    // fun10: get m_arr
    virtual const std::vector<T> &get_arr() const;
    // fun11: display
    virtual void print(std::ostream &os) const;

// random access iterator
    struct sum_iterator : public std::iterator<...> {
        ...
    };
}

// encapsulation for stream I/O
template<class T>
std::ostream& operator<< (std::ostream& os, const BITree<T> &packet);
```

The core code is `bitree.h` and `bitree.cpp` , the `bitree_test.h` and `main.cpp` is just for test. You can read the examples in `bitree_test.h` to know how to use the code, **the code of this project provides detailed comments**.



## 中文文档(README-Chinese-Version)

本项目实现了**基于模板的二叉索引树**。 它可以在 $O\left(\log N\right)$ 时间内获取前缀和，在 $O\left(\log N\right)$ 时间内对某元素进行更改，在 $O\left( 1\right)$ 时间实现随机访问。

同时，本项目还提供了一个**对前缀和的随机访问迭代器**，该迭代器可以与许多 STL 算法很好地交互。 例如，如果要查找区间 `[first, last)` 中不小于 `val` 的第一个元素，可以使用 `std::lower_bound(bt.begin(), bt.end( ), val)` 就能在 $O\left(\log^2 N\right)$ 时间内找到它。

下面列出了完整的功能（作为演示）：

```c++
template<class T>
class BITree {
// 数据成员
private:
    std::vector<T> m_tree;     // Binary Indexed Tree
    std::vector<T> m_arr;
    ...
    
// 公有接口
public:
    // fun1: 随机访问
    virtual T get(size_t index) const;
    // fun2: 元素自增
    virtual void add(size_t index, T val);
    // fun3: 元素更新
    virtual void update(size_t index, T val);
    // fun4: sum[0:index]
    virtual T sum(size_t index) const;
    // fun5: sum[left:right]
    virtual T sum(size_t left, size_t right) const;
    // fun6: m_arr 的长度
    virtual size_t size() const;
    // fun7: resize
    virtual void resize(size_t siz);
    // fun8: 获取头迭代器, 可适配于 STL
    virtual iterator begin();
    // fun9: 获取尾迭代器, 可适配于 STL
    virtual iterator end();
    // fun10: 获取 m_arr
    virtual const std::vector<T> &get_arr() const;
    // fun11: 打印输出
    virtual void print(std::ostream &os) const;

// 随机访问迭代器
    struct sum_iterator : public std::iterator<...> {
        ...
    };
}

// 封装供流式IO调用
template<class T>
std::ostream& operator<< (std::ostream& os, const BITree<T> &packet);
```

核心代码是 `bitree.h` 和 `bitree.cpp` ， `bitree_test.h` 和 `main.cpp`  是用来测试的。 你可以阅读 `bitree_test.h` 的例子来了解如何使用代码，**该项目的代码提供了详细的注释**。

