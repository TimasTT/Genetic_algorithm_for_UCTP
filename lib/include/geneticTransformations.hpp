//
// Created by timas on 28.07.2021.
//

#ifndef INCLUDE_GENETICTRANSFORMATIONS_HPP
#define INCLUDE_GENETICTRANSFORMATIONS_HPP

#include "geneticStructure.hpp"

namespace genalg {

    /**
     * \brief Population observer
     */

    class PopulationObserver {
    private:
        std::shared_ptr<Individual> individualWithoutFlaws;

    public:
        PopulationObserver();

        void populationWithoutFlawsPrepared(std::shared_ptr<Individual> &&);

        const std::vector<Gen> &getChromosomeTime() const;

        const std::vector<Gen> &getChromosomeAuditory() const;
    };


    /**
     * \brief Population transformation
     */

    class PopulationTransformation {
    private:
        std::shared_ptr<Population> population;

        std::shared_ptr<PopulationObserver> populationObserver;

        std::vector<int> penaltyList;

        enum class PopulationState {
            POPULATION_NOT_PREPARED = 0, POPULATION_PREPARED = 1
        };

        PopulationState populationReduce();

    public:
        PopulationTransformation(std::shared_ptr<Population> &&, std::shared_ptr<PopulationObserver> &);

        void populationIterate();
    };

}

#endif  // INCLUDE_GENETICTRANSFORMATIONS_HPP
