//
// Created by timas on 27.07.2021.
//

#include <memory>
#include <geneticStructure.hpp>
#include <geneticTransformations.hpp>

int main() {

    // Algorithm work with large number of auditors.

    std::vector<genalg::Block> blocks;
    std::vector<int> AuditoryType1;
    std::vector<int> AuditoryType2;
    std::vector<int> AllTimes;

    blocks.reserve(255);
    for (int i = 0; i < 255; ++i) {
        genalg::Block newBlock = genalg::Block(i, i, i, genalg::getRandomNumber(1, 2), i);
        blocks.push_back(newBlock);
    }
    AuditoryType1.reserve(50);
    for (int i = 0; i < 50; ++i) {
        AuditoryType1.push_back(i);
    }
    AuditoryType2.reserve(50);
    for (int i = 50; i < 100; ++i) {
        AuditoryType2.push_back(i);
    }
    AllTimes.reserve(50);
    for (int i = 0; i < 100; ++i) {
        AllTimes.push_back(i);
    }
    std::shared_ptr<genalg::Population> Population = std::make_shared<genalg::Population>(blocks, AuditoryType1, AuditoryType2, AllTimes);

    std::shared_ptr<genalg::PopulationObserver> populationObserver = std::make_shared<genalg::PopulationObserver>();

    genalg::PopulationTransformation(std::move(Population), populationObserver).populationIterate();
    std::vector<genalg::Gen> time(populationObserver->getChromosomeTime());
    std::vector<genalg::Gen> auditory(populationObserver->getChromosomeAuditory());

    return 0;
}
