//
// Created by ASUS on 2023/1/15.
//

#ifndef BINARYINDEXEDTREE_BITREE_TEST_H
#define BINARYINDEXEDTREE_BITREE_TEST_H

#include "bitree.h"
#include <algorithm>

void BITree_test1() {
    std::cout << std::endl << "---------- BITree_test1 begin ----------" << std::endl;

    std::cout << std::endl << "---------- Part-1: Construct ----------" << std::endl;
    std::vector<double> vec1{2.71828, 3.14159, 1.14514, 1.19198, 0.57721};
    size_t siz = vec1.size();
    BITree<double> bt1(std::move(vec1));

    // expect output: bt1 = [2.71828,3.14159,1.14514,1.19198,0.57721]
    std::cout << "bt1 = " << bt1 << std::endl;
    // expect output: bt1 = vec1.size() = 0
    std::cout << "vec1.size() = " << vec1.size() << std::endl;

    BITree<double> bt2(bt1);

    // expect output: bt2 = [2.71828,3.14159,1.14514,1.19198,0.57721]
    std::cout << "bt2 = " << bt2 << std::endl;

    BITree<double> bt3(std::move(bt2));

    // expect output: bt2 = []
    std::cout << "bt2 = " << bt2 << std::endl;
    // expect output: bt2 = [2.71828,3.14159,1.14514,1.19198,0.57721]
    std::cout << "bt3 = " << bt3 << std::endl;

    std::cout << std::endl << "---------- Part-2: Sum ----------" << std::endl;

    // expect output: bt1.sum(0) = 0
    //                bt1.sum(1) = 2.71828
    //                bt1.sum(2) = 5.85987
    //                bt1.sum(3) = 7.00501
    //                bt1.sum(4) = 8.19699
    //                bt1.sum(5) = 8.7742
    for (size_t i = 0; i <= siz; ++ i)
        std::cout << "bt1.sum(" << i << ") = " << bt1.sum(i) << std::endl;

    std::cout << std::endl << "---------- Part-3: Add ----------" << std::endl;

    bt1.add(2, 1);

    // expect output: bt1 = [2.71828,3.14159,2.14514,1.19198,0.57721]
    std::cout << "bt1 = " << bt1 << std::endl;

    // expect output: bt1.sum(0) = 0
    //                bt1.sum(1) = 2.71828
    //                bt1.sum(2) = 5.85987
    //                bt1.sum(3) = 8.00501
    //                bt1.sum(4) = 9.19699
    //                bt1.sum(5) = 9.7742
    for (size_t i = 0; i <= siz; ++ i)
        std::cout << "bt1.sum(" << i << ") = " << bt1.sum(i) << std::endl;

    std::cout << std::endl << "---------- Part-4: ReSize ----------" << std::endl;

    bt1.resize(siz - 1);

    // expect output: bt1 = [2.71828,3.14159,2.14514,1.19198]
    std::cout << "bt1 = " << bt1 << std::endl;

    // expect output: bt1.sum(0) = 0
    //                bt1.sum(1) = 2.71828
    //                bt1.sum(2) = 5.85987
    //                bt1.sum(3) = 8.00501
    //                bt1.sum(4) = 9.19699
    for (size_t i = 0; i <= siz - 1; ++ i)
        std::cout << "bt1.sum(" << i << ") = " << bt1.sum(i) << std::endl;

    bt3.resize(siz + 1);

    // expect output: bt3 = [2.71828,3.14159,2.14514,1.19198,0.57721, 0]
    std::cout << "bt3 = " << bt3 << std::endl;

    // expect output: bt3.sum(0) = 0
    //                bt3.sum(1) = 2.71828
    //                bt3.sum(2) = 5.85987
    //                bt3.sum(3) = 7.00501
    //                bt3.sum(4) = 8.19699
    //                bt3.sum(5) = 8.7742
    //                bt3.sum(6) = 8.7742
    for (size_t i = 0; i <= siz + 1; ++ i)
        std::cout << "bt3.sum(" << i << ") = " << bt3.sum(i) << std::endl;

    std::cout << std::endl << "---------- Part-5: Iterator ----------" << std::endl;

    BITree<double>::iterator it3 = std::lower_bound(bt1.begin(), bt1.end(), 5);
    // expect output: std::lower_bound(bt1.begin(), bt1.end(), 5) = 5.85987
    std::cout << "std::lower_bound(bt1.begin(), bt1.end(), 5) = " << *it3 << std::endl;

    ++ it3;
    // expect output: std::lower_bound(bt1.begin(), bt1.end(), 5) = 8.00501
    std::cout << "*++it = " << *it3 << std::endl;

    it3 = std::lower_bound(bt1.begin(), bt1.end(), 5.85988);
    // expect output: std::lower_bound(bt1.begin(), bt1.end(), 5.85988) = 8.00501
    std::cout << "std::lower_bound(bt1.begin(), bt1.end(), 5.85988) = " << *it3 << std::endl;

    // expect output: bt1.sum(0) = 0
    //                bt1.sum(1) = 2.71828
    //                bt1.sum(2) = 5.85987
    //                bt1.sum(3) = 8.00501
    //                bt1.sum(4) = 9.19699
    for (auto it = bt1.begin(); it <= bt1.end(); ++ it)
        std::cout << "bt1.sum(" << it.get_idx() << ") = " << *it << std::endl;

    // expect output: bt1.sum... = 0
    //                bt1.sum... = 2.71828
    //                bt1.sum... = 5.85987
    //                bt1.sum... = 8.00501
    for (auto prefix_sum : bt1)
        std::cout << "bt1.sum... = " << prefix_sum << std::endl;

}

#endif //BINARYINDEXEDTREE_BITREE_TEST_H
