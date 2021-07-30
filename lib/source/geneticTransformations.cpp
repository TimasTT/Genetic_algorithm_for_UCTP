//
// Created by timas on 28.07.2021.
//

#include "geneticTransformations.hpp"
#include "geneticRules.hpp"

#include <utility>
#include <memory>

namespace genalg {

    // Population transformation

    PopulationTransformation::PopulationTransformation(std::shared_ptr<Population> &&population_,
                                                       std::shared_ptr<PopulationObserver> &populationObserver_)
            : population(std::move(population_)), populationObserver(populationObserver_) {}

    void PopulationTransformation::populationIterate() {
        while (true) {
            if (populationReduce() == PopulationState::POPULATION_PREPARED) break;
            population->crossingover();
            population->mutation();
        }
    }

    PopulationTransformation::PopulationState PopulationTransformation::populationReduce() {
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

        for (size_t individualIndex = 0; individualIndex < penaltyList.size(); ++individualIndex) {
            if (penaltyList[individualIndex] == 0) {
                populationObserver->populationWithoutFlawsPrepared(std::move(population->getPopulation()[individualIndex]));
                return PopulationState::POPULATION_PREPARED;
            }
        }

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

        return PopulationState::POPULATION_NOT_PREPARED;
    }

    // Population Observer

    PopulationObserver::PopulationObserver() = default;

    void PopulationObserver::populationWithoutFlawsPrepared(std::shared_ptr<Individual> &&individual_) {
        individualWithoutFlaws = std::move(individual_);
    }

    const std::vector<Gen> &PopulationObserver::getChromosomeTime() const {
        return individualWithoutFlaws->getTimeChromosome()->getChromosome();
    }

    const std::vector<Gen> &PopulationObserver::getChromosomeAuditory() const {
        return individualWithoutFlaws->getAuditoryChromosome()->getChromosome();
    }

    const std::shared_ptr<Individual> &PopulationObserver::getIndividual() const {
        return individualWithoutFlaws;
    }

}