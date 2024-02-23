set(PROJECT_LIBRARY
        pointsMatrixGeneration.cpp
        include/pointsMatrixGeneration/pointsMatrixGeneration.hpp
        point.cpp
        include/pointsMatrixGeneration/point.hpp
        snakeAlgorithm.cpp
        include/pointsMatrixGeneration/snakeAlgorithm.hpp
        include/pointsMatrixGeneration/direction.hpp
        include/pointsMatrixGeneration/difficulty.hpp)

add_library(pointsMatrixGeneration ${PROJECT_LIBRARY})

target_include_directories(pointsMatrixGeneration PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
install(TARGETS pointsMatrixGeneration)
