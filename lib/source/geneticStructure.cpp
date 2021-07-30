//
// Created by timas on 27.07.2021.
//

#include <utility>

#include "geneticStructure.hpp"

namespace genalg {

    Gen::Gen(const int &val)
            : value(val) {}

    void Gen::changeValue(const int &val) {
        value = val;
    }

    const int &Gen::getValue() const {
        return value;
    }


// Chromosome interface

    genalg::IChromosome::~IChromosome() = default;


//Chromosome Auditory

    ChromosomeAuditory::ChromosomeAuditory(const std::vector<Block> &blocks, const std::vector<int> &auditoryType1,
                                           const std::vector<int> &auditoryType2) {

        std::for_each(blocks.begin(), blocks.end(), [&](const auto &block) {
            if (block.subjectType == 1) {
                chromosome.emplace_back(Gen(auditoryType1[getRandomNumber(0, static_cast<int>(
                        auditoryType1.size() - 1))]));
            } else if (block.subjectType == 2) {
                chromosome.emplace_back(Gen(auditoryType2[getRandomNumber(0, static_cast<int>(
                        auditoryType2.size() - 1))]));
            }
        });
    }

    ChromosomeAuditory::ChromosomeAuditory(std::vector<Gen> &&chromosome1, std::vector<Gen> &&chromosome2) {
        chromosome.insert(chromosome.end(), chromosome1.begin(), chromosome1.end());
        chromosome.insert(chromosome.end(), chromosome2.begin(), chromosome2.end());
    }

    const std::vector<Gen> &ChromosomeAuditory::getChromosome() const {
        return chromosome;
    }

    void ChromosomeAuditory::changeOneGen(const std::vector<Block> &blocks, const std::vector<int> &auditoryType1,
                                          const std::vector<int> &auditoryType2) {

        auto numberOfChangebleGen = getRandomNumber(0, static_cast<int>(blocks.size() - 1));
        if (blocks[numberOfChangebleGen].subjectType == 1) {
            chromosome[numberOfChangebleGen].changeValue(getRandomNumber(0, static_cast<int>(auditoryType1.size() - 1)));
        } else if (blocks[numberOfChangebleGen].subjectType == 2) {
            chromosome[numberOfChangebleGen].changeValue(getRandomNumber(0, static_cast<int>(auditoryType2.size() - 1)));

        }
    }

    int ChromosomeAuditory::repetitionsCalculate() const {
        int repetitions = 0;
        for (auto gen_ : chromosome) {
            repetitions = std::count_if(chromosome.begin(), chromosome.end(), [&](const auto &gen) {
                return gen.getValue() == gen_.getValue();
            });
        }
        return repetitions;
    }

    genalg::ChromosomeAuditory::ChromosomeAuditory() = default;


// Chromosome time

    ChromosomeTime::ChromosomeTime() = default;

    ChromosomeTime::ChromosomeTime(const std::vector<Block> &blocks, const std::vector<int> &time) {

        std::for_each(blocks.begin(), blocks.end(), [&](const auto &block) {
            chromosome.emplace_back(Gen(getRandomNumber(0, static_cast<int>(time.size() - 1))));
        });
    }

    ChromosomeTime::ChromosomeTime(std::vector<Gen> &&chromosome1, std::vector<Gen> &&chromosome2) {
        chromosome.insert(chromosome.end(), chromosome1.begin(), chromosome1.end());
        chromosome.insert(chromosome.end(), chromosome2.begin(), chromosome2.end());
    }

    const std::vector<Gen> &ChromosomeTime::getChromosome() const {
        return chromosome;
    }

    void ChromosomeTime::changeOneGen(const std::vector<Block> &blocks, const std::vector<int> &time) {
        auto numberOfChangebleGen = getRandomNumber(0, static_cast<int>(blocks.size() - 1));
        chromosome[numberOfChangebleGen].changeValue(getRandomNumber(0, static_cast<int>(time.size() - 1)));
    }

    int ChromosomeTime::repetitionsCalculate() const {
        int repetitions = 0;
        for (auto gen_ : chromosome) {
            repetitions = std::count_if(chromosome.begin(), chromosome.end(), [&](const auto &gen) {
                return gen.getValue() == gen_.getValue();
            });
        }
        return repetitions;
    }


//Individual

    Individual::Individual() = default;

    Individual::Individual(const std::vector<Block> &blocks, const std::vector<int> &auditoryType1, const std::vector<int> &auditoryType2,
                           const std::vector<int> &time) {

        chromosomeTime = std::make_shared<ChromosomeTime>(blocks, time);
        chromosomeAuditory = std::make_shared<ChromosomeAuditory>(blocks, auditoryType1, auditoryType2);
    }

    Individual::Individual(std::vector<Gen> &&chromosomeTimePart1, std::vector<Gen> &&chromosomeTimePart2,
                           std::vector<Gen> &&chromosomeAuditoryPart1, std::vector<Gen> &&chromosomeAuditoryPart2) {

        chromosomeTime = std::make_shared<ChromosomeTime>(std::move(chromosomeTimePart1), std::move(chromosomeTimePart2));
        chromosomeAuditory = std::make_shared<ChromosomeAuditory>(std::move(chromosomeAuditoryPart1), std::move(chromosomeAuditoryPart2));
    }

    const std::shared_ptr<ChromosomeTime> &Individual::getTimeChromosome() {
        return chromosomeTime;
    }

    const std::shared_ptr<ChromosomeAuditory> &Individual::getAuditoryChromosome() {
        return chromosomeAuditory;
    }

    void
    Individual::changeGens(const std::vector<Block> &blocks, const std::vector<int> &auditoryType1, const std::vector<int> &auditoryType2,
                           const std::vector<int> &time) {
        chromosomeTime->changeOneGen(blocks, time);
        chromosomeAuditory->changeOneGen(blocks, auditoryType1, auditoryType2);
    }


// Populatiom

    Population::Population(std::vector<Block> &blocks_, std::vector<int> &auditoryType1_, std::vector<int> &auditoryType2_,
                           std::vector<int> &time_)
            : blocks(std::move(blocks_)), auditoryType1(std::move(auditoryType1_)), auditoryType2(std::move(auditoryType2_)),
              time(std::move(time_)) {

        for (size_t individual = 0; individual < POPULATION_SIZE; ++individual) {
            population.emplace_back(std::make_shared<Individual>(blocks, auditoryType1, auditoryType2, time));
        }
    }

    const std::vector<Block> &Population::getBlocks() const {
        return blocks;
    }

    std::vector<std::shared_ptr<Individual>> &Population::getPopulation() {
        return population;
    }

    void Population::crossingover() {
        size_t startPopulationSize = population.size();
        for (size_t indivInd = 0; indivInd < startPopulationSize - 1; ++indivInd) {
            int partIndex = getRandomNumber(0, static_cast<int>(blocks.size() - 1));
            std::vector<Gen> newTimeChromosomePart1;
            newTimeChromosomePart1.insert(newTimeChromosomePart1.begin(),
                                          population[indivInd]->getTimeChromosome()->getChromosome().begin(),
                                          population[indivInd]->getTimeChromosome()->getChromosome().begin() + partIndex);
            std::vector<Gen> newTimeChromosomePart2;
            newTimeChromosomePart2.insert(newTimeChromosomePart2.begin(),
                                          population[indivInd + 1]->getTimeChromosome()->getChromosome().begin() + partIndex,
                                          population[indivInd + 1]->getTimeChromosome()->getChromosome().end());
            std::vector<Gen> newAuditoryChromosomePart1;
            newAuditoryChromosomePart1.insert(newAuditoryChromosomePart1.begin(),
                                              population[indivInd]->getAuditoryChromosome()->getChromosome().begin(),
                                              population[indivInd]->getAuditoryChromosome()->getChromosome().begin() + partIndex);
            std::vector<Gen> newAuditoryChromosomePart2;
            newAuditoryChromosomePart2.insert(newAuditoryChromosomePart2.begin(),
                                              population[indivInd + 1]->getAuditoryChromosome()->getChromosome().begin() + partIndex,
                                              population[indivInd + 1]->getAuditoryChromosome()->getChromosome().end());

            std::shared_ptr<Individual> newIndividual = std::make_shared<Individual>(std::move(newTimeChromosomePart1),
                                                                                     std::move(newTimeChromosomePart2),
                                                                                     std::move(newAuditoryChromosomePart1),
                                                                                     std::move(newAuditoryChromosomePart2));

            population.emplace_back(newIndividual);

            std::vector<Gen> newTimeChromosomePart1Second;
            newTimeChromosomePart1Second.insert(newTimeChromosomePart1Second.begin(),
                                                population[indivInd + 1]->getTimeChromosome()->getChromosome().begin(),
                                                population[indivInd + 1]->getTimeChromosome()->getChromosome().begin() + partIndex);
            std::vector<Gen> newTimeChromosomePart2Second;
            newTimeChromosomePart2Second.insert(newTimeChromosomePart2Second.begin(),
                                                population[indivInd]->getTimeChromosome()->getChromosome().begin() + partIndex,
                                                population[indivInd]->getTimeChromosome()->getChromosome().end());
            std::vector<Gen> newAuditoryChromosomePart1Second;
            newAuditoryChromosomePart1Second.insert(newAuditoryChromosomePart1Second.begin(),
                                                    population[indivInd + 1]->getAuditoryChromosome()->getChromosome().begin(),
                                                    population[indivInd + 1]->getAuditoryChromosome()->getChromosome().begin() + partIndex);
            std::vector<Gen> newAuditoryChromosomePart2Second;
            newAuditoryChromosomePart2Second.insert(newAuditoryChromosomePart2Second.begin(),
                                                    population[indivInd]->getAuditoryChromosome()->getChromosome().begin() + partIndex,
                                                    population[indivInd]->getAuditoryChromosome()->getChromosome().end());

            std::shared_ptr<Individual> newIndividualSecond = std::make_shared<Individual>(std::move(newTimeChromosomePart1Second),
                                                                                           std::move(newTimeChromosomePart2Second),
                                                                                           std::move(newAuditoryChromosomePart1Second),
                                                                                           std::move(newAuditoryChromosomePart2Second));

            population.emplace_back(newIndividualSecond);

        }
    }

    void Population::mutation() {
        for (auto &individual : population) {
            individual->changeGens(blocks, auditoryType1, auditoryType2, time);
        }
    }

    Population::Population() = default;

}
// Gen

