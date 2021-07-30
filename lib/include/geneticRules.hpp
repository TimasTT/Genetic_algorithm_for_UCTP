//
// Created by timas on 29.07.2021.
//

#ifndef INCLUDE_GENETICRULES_HPP
#define INCLUDE_GENETICRULES_HPP

#include "geneticStructure.hpp"

namespace genalg {

    /**
     * \brief Rule interface
     *
     * Rules are needed to identify inconsistencies in the schedule.
     */

    class IRule {
    public:
        virtual ~IRule();

        virtual int calculationFitness(const std::shared_ptr<Individual> &,
                                       const std::vector<Block> &) const = 0;
    };

    /**
     * \brief One audience rule
     *
     * One classroom cannot have two classes at the same time.
     */

    class sameAuditorySameTime: public IRule {
    public:
        int calculationFitness(const std::shared_ptr<Individual> &,
                               const std::vector<Block> &) const override;
    };

    /**
     * \brief One group rule
     *
     * One group at one time can have only one lesson.
     */

    class sameGroupMoreBlock: public IRule {
        int calculationFitness(const std::shared_ptr<Individual> &,
                               const std::vector<Block> &) const override;
    };

    /**
     * \brief One teacher rule
     *
     * One teacher at one time can have only one lesson with only one group.
     */

    class sameTeacherMoreBlock: public IRule {
        int calculationFitness(const std::shared_ptr<Individual> &,
                               const std::vector<Block> &) const override;
    };
}


#endif  // INCLUDE_GENETICRULES_HPP
