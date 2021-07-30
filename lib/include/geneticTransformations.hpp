//
// Created by timas on 28.07.2021.
//

#ifndef INCLUDE_GENETICTRANSFORMATIONS_HPP
#define INCLUDE_GENETICTRANSFORMATIONS_HPP

#include "geneticStructure.hpp"

namespace genalg {

    /**
     * \brief Population observer
     *
     * As soon as, as a result of the operation of the algorithm, a description without
     * errors is obtained, it is transferred to this class and the algorithm ends.
     */

    class PopulationObserver {
    private:
        std::shared_ptr<Individual> individualWithoutFlaws;

    public:
        PopulationObserver();

        void populationWithoutFlawsPrepared(std::shared_ptr<Individual> &&);

        const std::vector<Gen> &getChromosomeTime() const;

        const std::vector<Gen> &getChromosomeAuditory() const;

        const std::shared_ptr<Individual> &getIndividual() const;
    };


    /**
     * \brief Population transformation
     *
     * This class controls the work of the genetic algorithm.
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
        /**
         * \brief Population transformate
         *
         *  Transformation takes place in 3 stages:
         *  1) Reducing population by removing the species with the greatest number of errors.
         *  2) Increase in the population due to the crossing of the remaining individuals.
         *  3) Population mutation.
         */

        PopulationTransformation(std::shared_ptr<Population> &&, std::shared_ptr<PopulationObserver> &);

        void populationIterate();
    };

}

#endif  // INCLUDE_GENETICTRANSFORMATIONS_HPP
