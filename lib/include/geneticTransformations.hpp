//
// Created by timas on 28.07.2021.
//

#ifndef INCLUDE_GENETICTRANSFORMATIONS_HPP
#define INCLUDE_GENETICTRANSFORMATIONS_HPP

#include "geneticStructure.hpp"

namespace genalg {

    class PopulationTransformation {
    private:
        std::shared_ptr<Population> population;

        std::vector<int> penaltyList;

        void populationReduce();

        void populationCrossing();

    public:
        PopulationTransformation(std::shared_ptr<Population>&&);

        void populationIterate();
    };

}

#endif  // INCLUDE_GENETICTRANSFORMATIONS_HPP
