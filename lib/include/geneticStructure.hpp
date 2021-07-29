//
// Created by timas on 27.07.2021.
//

#ifndef INCLUDE_GENETICALGORITHM_HPP
#define INCLUDE_GENETICALGORITHM_HPP

#include <memory>
#include <list>
#include <vector>
#include <algorithm>

#include "auxiliary.hpp"

namespace genalg {

#define POPULATION_SIZE 64

    /**
     * \brief Elementary block in algorithm
     *
     * Stores a number representing a specific time or audience.
     */

    class Gen {
    private:
        int value;

    public:
        Gen(const int &);

        void changeValue(const int &);

        const int &getValue() const;
    };


    /**
     *
     */

    class IChromosome {
    public:
        virtual ~IChromosome();

        virtual const std::vector<Gen> &getChromosome() const = 0;

        virtual int repetitionsCalculate() const = 0;
    };


    /**
     *
     */

    class ChromosomeTime: public IChromosome {
    private:
        std::vector<Gen> chromosome;

    public:
        ChromosomeTime();

        ChromosomeTime(const std::vector<Block> &, const std::vector<int> &);

        ChromosomeTime(std::vector<Gen> &&, std::vector<Gen> &&);

        void changeOneGen(const std::vector<Block> &, const std::vector<int> &);

        int repetitionsCalculate() const override;

        const std::vector<Gen> &getChromosome() const override;
    };


    /**
     *
     */

    class ChromosomeAuditory: public IChromosome {
    private:
        std::vector<Gen> chromosome;

    public:
        ChromosomeAuditory();

        ChromosomeAuditory(const std::vector<Block> &, const std::vector<int> &, const std::vector<int> &);

        ChromosomeAuditory(std::vector<Gen> &&, std::vector<Gen> &&);

        void changeOneGen(const std::vector<Block> &, const std::vector<int> &, const std::vector<int> &);

        int repetitionsCalculate() const override;

        const std::vector<Gen> &getChromosome() const override;
    };


    /**
     *
     */

    class Individual {
    private:
        std::shared_ptr<ChromosomeTime> chromosomeTime;
        std::shared_ptr<ChromosomeAuditory> chromosomeAuditory;

    public:
        Individual();

        Individual(const std::vector<Block> &, const std::vector<int> &, const std::vector<int> &,
                   const std::vector<int> &);

        Individual(std::vector<Gen> &&, std::vector<Gen> &&, std::vector<Gen> &&, std::vector<Gen> &&);

        void changeGens(const std::vector<Block> &, const std::vector<int> &, const std::vector<int> &,
                        const std::vector<int> &);

        const std::shared_ptr<ChromosomeTime> &getTimeChromosome();

        const std::shared_ptr<ChromosomeAuditory> &getAuditoryChromosome();
    };


    /**
     *
     */

    class Population {
    private:
        std::vector<std::shared_ptr<Individual>> population;

        std::vector<Block> blocks;
        std::vector<int> auditoryType1;
        std::vector<int> auditoryType2;
        std::vector<int> time;

    public:
        Population();

        Population(std::vector<Block> &, std::vector<int> &, std::vector<int> &, std::vector<int> &);

        const std::vector<Block> &getBlocks() const;

        std::vector<std::shared_ptr<Individual>> &getPopulation();

        void crossingover();

        void mutation();
    };

}

#endif  // INCLUDE_GENETICALGORITHM_HPP
