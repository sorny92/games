#pragma once

#include <bits/stdc++.h>

struct Node {
    std::vector<std::pair<int,int>> values;

    bool operator==(const Node &e2) const {
        return (this->values == e2.values);
    }

    bool operator!=(const Node &e2) const { return !(*this == e2); };

    struct HashLexic {
    public:
        size_t operator()(const Node &e) const {
            size_t accum{0};
            for (const auto v: e.values) {
                accum += v.second;
                accum *= 10;
            }
            return accum;
        }
    };
};