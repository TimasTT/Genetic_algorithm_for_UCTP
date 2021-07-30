add_executable(geneticAlgTests tests.cpp)
target_link_libraries(geneticAlgTests GTest::gtest_main GeneticAlgorithm)

add_test(NAME geneticAlgTests
        COMMAND geneticAlgTests)