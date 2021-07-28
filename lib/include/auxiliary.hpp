//
// Created by timas on 27.07.2021.
//

#ifndef INCLUDE_AUX_HPP
#define INCLUDE_AUX_HPP

#include <algorithm>

namespace genalg {

    int getRandomNumber(const int &min, const int &max);

    struct Block {
        int blockId;
        int group;
        int subject;
        int subjectType;
        int teacher;

        Block(int b, int g, int s, int st, int t): blockId(b), group(g), subject(s),
                                                   subjectType(st), teacher(t) {}
    };
}

#endif  // INCLUDE_AUX_HPP
