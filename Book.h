//
// Created by matias on 10/16/20.
//

#ifndef TEST_BOOK_H
#define TEST_BOOK_H

#define MAX_BOOK_DEPTH 100
#include <vector>
using std::vector;


typedef struct {
    vector<float> bid_price;
    vector<float> ask_price;
    vector<float> bid_size;
    vector<float> ask_size;
}BOOK;

typedef struct {
    double px;
    double qty;
}LT;


#endif //TEST_BOOK_H
