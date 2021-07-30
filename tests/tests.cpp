//
// Created by timas on 27.07.2021.
//

#include <gtest/gtest.h>
#include <geneticTransformations.hpp>
#include <geneticStructure.hpp>
#include <geneticRules.hpp>

using namespace genalg;

TEST(GeneticAlgorithmTests, PopulationInitialisateTest) {
    std::vector<Block> blocks;
    std::vector<int> AuditoryType1;
    std::vector<int> AuditoryType2;
    std::vector<int> AllTimes;

    const int blocksSize = 255;
    const int auditoryType1Size = 50;
    const int auditoryType2Size = 50;
    const int timeSize = 50;

    blocks.reserve(blocksSize);
    for (int i = 0; i < blocksSize; ++i) {
        Block newBlock = Block(i, i, i, getRandomNumber(1, 2), i);
        blocks.push_back(newBlock);
    }

    AuditoryType1.reserve(auditoryType1Size);
    for (int i = 0; i < 50; ++i) {
        AuditoryType1.push_back(i);
    }

    AuditoryType2.reserve(auditoryType2Size);
    for (int i = 50; i < 100; ++i) {
        AuditoryType2.push_back(i);
    }

    AllTimes.reserve(timeSize);
    for (int i = 0; i < 100; ++i) {
        AllTimes.push_back(i);
    }

    std::shared_ptr<Population> Population = std::make_shared<genalg::Population>(blocks, AuditoryType1, AuditoryType2, AllTimes);
    EXPECT_EQ(Population->getPopulation()[0]->getAuditoryChromosome()->getChromosome().size(), blocksSize);
}


class GeneticAlgorithmPopulationTests : public ::testing::Test {
protected:
    std::vector<Block> blocks;
    std::vector<int> AuditoryType1;
    std::vector<int> AuditoryType2;
    std::vector<int> AllTimes;

    const int blocksSize = 255;
    const int auditoryType1Size = 50;
    const int auditoryType2Size = 50;
    const int timeSize = 50;

    virtual void SetUp() {
        blocks.reserve(blocksSize);
        for (int i = 0; i < blocksSize; ++i) {
            Block newBlock = Block(i, i, i, getRandomNumber(1, 2), i);
            blocks.push_back(newBlock);
        }

        AuditoryType1.reserve(auditoryType1Size);
        for (int i = 0; i < 50; ++i) {
            AuditoryType1.push_back(i);
        }

        AuditoryType2.reserve(auditoryType2Size);
        for (int i = 50; i < 100; ++i) {
            AuditoryType2.push_back(i);
        }

        AllTimes.reserve(timeSize);
        for (int i = 0; i < 100; ++i) {
            AllTimes.push_back(i);
        }
    }

    virtual void TearDown() {}
};


TEST_F(GeneticAlgorithmPopulationTests, PopulationTransoformationTest) {
    std::vector<Block> blocks_ = blocks;
    std::shared_ptr<Population> Population = std::make_shared<genalg::Population>(blocks, AuditoryType1, AuditoryType2, AllTimes);
    std::shared_ptr<genalg::PopulationObserver> populationObserver = std::make_shared<genalg::PopulationObserver>();

    genalg::PopulationTransformation(std::move(Population), populationObserver).populationIterate();

    int result = 0;
    std::unique_ptr<IRule> rule = std::make_unique<sameAuditorySameTime>();
    result += rule->calculationFitness(populationObserver->getIndividual(), blocks_);
    rule = std::make_unique<sameGroupMoreBlock>();
    result += rule->calculationFitness(populationObserver->getIndividual(), blocks_);
    rule = std::make_unique<sameTeacherMoreBlock>();
    result += rule->calculationFitness(populationObserver->getIndividual(), blocks_);

    EXPECT_TRUE(result == 0);
}