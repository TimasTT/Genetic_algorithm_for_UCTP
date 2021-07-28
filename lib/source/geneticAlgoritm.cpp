//
// Created by timas on 27.07.2021.
//

#include <utility>

#include "geneticAlgorithm.hpp"

// Gen

genalg::Gen::Gen(const int &val): value(val) {}

void genalg::Gen::changeValue(const int &val) {
    value = val;
}

const int &genalg::Gen::getValue() const {
    return value;
}


// Chromosome interface

genalg::IChromosome::~IChromosome() = default;


//Chromosome Auditory

genalg::ChromosomeAuditory::ChromosomeAuditory(const std::vector<Block> &blocks,
                                               const std::vector<int> &auditoryType1,
                                               const std::vector<int> &auditoryType2) {
    std::for_each(blocks.begin(), blocks.end(), [&](const auto &block) {
        if (block.subjectType == 1) {
            chromosome.emplace_back(std::make_unique<Gen>(
                    auditoryType1[getRandomNumber(0, static_cast<int>(auditoryType1.size() - 1))]));
        } else if (block.subjectType == 2) {
            chromosome.emplace_back(std::make_unique<Gen>(
                    auditoryType2[getRandomNumber(0, static_cast<int>(auditoryType2.size() - 1))]));
        }
    });
}

genalg::ChromosomeAuditory::ChromosomeAuditory() = default;


// Chromosome time

genalg::ChromosomeTime::ChromosomeTime() = default;

genalg::ChromosomeTime::ChromosomeTime(const std::vector<Block> &blocks,
                                       const std::vector<int> &time) {
    std::for_each(blocks.begin(), blocks.end(), [&](const auto &block) {
        chromosome.emplace_back(
                std::make_unique<Gen>(getRandomNumber(0, static_cast<int>(time.size() - 1))));
    });
}


//Individual

genalg::Individual::Individual() = default;

genalg::Individual::Individual(const std::vector<Block> &blocks,
                               const std::vector<int> &auditoryType1,
                               const std::vector<int> &auditoryType2,
                               const std::vector<int> &time) {
    chromosomeTime = std::make_unique<ChromosomeTime>(blocks, time);
    chromosomeAuditory = std::make_unique<ChromosomeAuditory>(blocks, auditoryType1, auditoryType2);
}


// Populatiom

genalg::Population::Population(std::vector<Block> &blocks_, std::vector<int> &auditoryType1_,
                               std::vector<int> &auditoryType2_, std::vector<int> &time_): blocks(
        std::move(blocks_)), auditoryType1(std::move(auditoryType1_)), auditoryType2(
        std::move(auditoryType2_)), time(std::move(time_)) {
    std::for_each(blocks.begin(), blocks.end(), [&](const auto &block) {
        population.emplace_back(
                std::make_unique<Individual>(blocks, auditoryType1, auditoryType2, time));
    });
}

genalg::Population::Population() = default;
