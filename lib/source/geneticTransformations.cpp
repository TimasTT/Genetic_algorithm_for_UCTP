//
// Created by timas on 28.07.2021.
//

#include "geneticTransformations.hpp"
#include "geneticRules.hpp"

#include <utility>
#include <memory>
#include <iostream>

namespace genalg {

    // Population transformation

    PopulationTransformation::PopulationTransformation(std::shared_ptr<Population> &&population_)
            : population(std::move(population_)) {}

    void PopulationTransformation::populationIterate() {
        for (int i = 0; i < ITERATIONS; ++i) {
            populationReduce();
            population->crossingover();
            population->mutation();
        }
    }

    void PopulationTransformation::populationReduce() {
        penaltyList.clear();
        for (const auto &individual : population->getPopulation()) {
            int result = 0;
            std::unique_ptr<IRule> rule = std::make_unique<sameAuditorySameTime>();
            result += rule->calculationFitness(individual, population->getBlocks());
            rule = std::make_unique<sameGroupMoreBlock>();
            result += rule->calculationFitness(individual, population->getBlocks());
            rule = std::make_unique<sameTeacherMoreBlock>();
            result += rule->calculationFitness(individual, population->getBlocks());

            penaltyList.emplace_back(result);
        }

        std::vector<int> sortedPenalties = penaltyList;
        std::sort(sortedPenalties.begin(), sortedPenalties.end());

        int populationEdge = sortedPenalties[sortedPenalties.size() / 2];

// delete individuals with more than population edge flaws
// but not more than half of population

        size_t populationCounter = population->getPopulation().size() / 2;
        for (size_t i = 0; i < population->getPopulation().size(); ++i) {
            if (penaltyList[i] >= populationEdge) {
                population->getPopulation().erase(population->getPopulation().begin() + i);
            }
            if (populationCounter == 0) break;
            populationCounter--;
        }
    }
}