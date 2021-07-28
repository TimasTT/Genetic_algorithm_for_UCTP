add_library(GeneticAlgorithm SHARED
        include/auxiliary.hpp
        source/auxiliary.cpp
        include/geneticAlgorithm.hpp
        source/geneticAlgoritm.cpp)

target_include_directories(GeneticAlgorithm PUBLIC include)