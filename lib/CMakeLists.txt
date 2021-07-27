add_library(GeneticAlgorithm SHARED
        include/geneticAlgorithm.hpp
        source/geneticAlgoritm.cpp)

target_include_directories(GeneticAlgorithm PUBLIC include)