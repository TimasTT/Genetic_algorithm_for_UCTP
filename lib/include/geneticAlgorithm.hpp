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
    };


    /**
     *
     */

    class ChromosomeTime: public IChromosome {
    private:
        std::list<std::unique_ptr<Gen>> chromosome;

    public:
        ChromosomeTime();

        ChromosomeTime(const std::vector<Block> &, const std::vector<int> &);
    };


    /**
     *
     */

    class ChromosomeAuditory: public IChromosome {
    private:
        std::list<std::unique_ptr<Gen>> chromosome;

    public:
        ChromosomeAuditory();

        ChromosomeAuditory(const std::vector<Block> &, const std::vector<int> &,
                           const std::vector<int> &);
    };


    /**
     *
     */

    class Individual {
    private:
        std::unique_ptr<IChromosome> chromosomeTime;
        std::unique_ptr<IChromosome> chromosomeAuditory;

    public:
        Individual();

        Individual(const std::vector<Block> &, const std::vector<int> &, const std::vector<int> &,
                   const std::vector<int> &);
    };


    /**
     *
     */

    class Population {
    private:
        std::vector<std::unique_ptr<Individual>> population;

        std::vector<Block> blocks;
        std::vector<int> auditoryType1;
        std::vector<int> auditoryType2;
        std::vector<int> time;

    public:
        Population();

        Population(std::vector<Block> &, std::vector<int> &, std::vector<int> &,
                   std::vector<int> &);
    };

}

#endif  // INCLUDE_GENETICALGORITHM_HPP
