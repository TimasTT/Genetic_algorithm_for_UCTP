//
// Created by timas on 29.07.2021.
//

#include "geneticRules.hpp"
#include "geneticStructure.hpp"

namespace genalg {

    // Rule interface

    IRule::~IRule() = default;


    // same auditory same time rule

    int sameAuditorySameTime::calculationFitness(const std::shared_ptr<Individual> &individual_, const std::vector<Block> &blocks_) const {
        int repetitions = 0;
        for (size_t i = 0; i < blocks_.size(); ++i) {
            for (size_t j = i + 1; j < blocks_.size() - 1; ++j) {
                if (individual_->getAuditoryChromosome()->getChromosome()[i].getValue() ==
                    individual_->getAuditoryChromosome()->getChromosome()[j].getValue() &&
                    individual_->getTimeChromosome()->getChromosome()[i].getValue() ==
                    individual_->getTimeChromosome()->getChromosome()[j].getValue())
                    repetitions++;
            }
        }

        return repetitions;
    }


    // same group more block rule

    int sameGroupMoreBlock::calculationFitness(const std::shared_ptr<Individual> &individual_, const std::vector<Block> &blocks_) const {
        int repetitions = 0;
        for (size_t i = 0; i < blocks_.size(); ++i) {
            for (size_t j = i + 1; j < blocks_.size() - 1; ++j) {
                if (blocks_[i].group == blocks_[j].group && individual_->getTimeChromosome()->getChromosome()[i].getValue() ==
                                                            individual_->getTimeChromosome()->getChromosome()[j].getValue())
                    repetitions++;
            }
        }

        return repetitions;
    }


    // same teacher more block rule

    int sameTeacherMoreBlock::calculationFitness(const std::shared_ptr<Individual> &individual_, const std::vector<Block> &blocks_) const {
        int repetitions = 0;
        for (size_t i = 0; i < blocks_.size(); ++i) {
            for (size_t j = i + 1; j < blocks_.size() - 1; ++j) {
                if (blocks_[i].teacher == blocks_[j].teacher && individual_->getTimeChromosome()->getChromosome()[i].getValue() ==
                                                                individual_->getTimeChromosome()->getChromosome()[j].getValue())
                    repetitions++;
            }
        }

        return repetitions;
    }
}