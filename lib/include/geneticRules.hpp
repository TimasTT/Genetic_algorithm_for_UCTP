//
// Created by timas on 29.07.2021.
//

#ifndef INCLUDE_GENETICRULES_HPP
#define INCLUDE_GENETICRULES_HPP

#include "geneticStructure.hpp"

namespace genalg {

#define ITERATIONS 3

    class IRule {
    public:
        virtual ~IRule();

        virtual int calculationFitness(const std::shared_ptr<Individual> &,
                                       const std::vector<Block> &) const = 0;
    };

    class sameAuditorySameTime: public IRule {
    public:
        int calculationFitness(const std::shared_ptr<Individual> &,
                               const std::vector<Block> &) const override;
    };

    class sameGroupMoreBlock: public IRule {
        int calculationFitness(const std::shared_ptr<Individual> &,
                               const std::vector<Block> &) const override;
    };

    class sameTeacherMoreBlock: public IRule {
        int calculationFitness(const std::shared_ptr<Individual> &,
                               const std::vector<Block> &) const override;
    };
}


#endif  // INCLUDE_GENETICRULES_HPP
