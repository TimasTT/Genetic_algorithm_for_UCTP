add_library(GeneticAlgorithm STATIC
        include/auxiliary.hpp
        source/auxiliary.cpp
        include/geneticStructure.hpp
        source/geneticStructure.cpp
        include/geneticTransformations.hpp
        source/geneticTransformations.cpp
        include/geneticRules.hpp
        source/geneticRules.cpp)

target_include_directories(GeneticAlgorithm PUBLIC include)