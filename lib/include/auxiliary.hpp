//
// Created by timas on 27.07.2021.
//

#ifndef INCLUDE_AUX_HPP
#define INCLUDE_AUX_HPP

#include <algorithm>

namespace genalg {

    /**
     * \brief Get random number from range
     *
     * \param[in] min Minimal number of range
     * \param[in] max Maximum number of range
     *
     */

    int getRandomNumber(const int &min, const int &max);

    /**
     * \brief Block - Schedule unit
     *
     * One group corresponds to one subject taught by one teacher at one time.
     */

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
