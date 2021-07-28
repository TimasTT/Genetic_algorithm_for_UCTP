add_library(GeneticAlgorithm STATIC
        include/auxiliary.hpp
        source/auxiliary.cpp
        include/geneticStructure.hpp
        source/geneticStructure.cpp)

target_include_directories(GeneticAlgorithm PUBLIC include)