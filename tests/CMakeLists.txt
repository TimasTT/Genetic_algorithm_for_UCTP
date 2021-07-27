add_executable(geneticAlgTests tests.cpp)
target_link_libraries(geneticAlgTests gtest ${CMAKE_THREAD_LIBS_INIT} GeneticAlgorithm)

add_test(NAME geneticAlgTests
        COMMAND geneticAlgTests)