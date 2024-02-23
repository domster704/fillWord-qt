set(PROJECT_LIBRARY
        resources.qrc
        fillWord.cpp
        include/fillWord/fillWord.hpp
        cellButton.cpp include/fillWord/cellButton.hpp
        wordsGenerator.cpp
        include/fillWord/wordsGenerator.hpp
        swipeHandler.cpp
        include/fillWord/swipeHandler.hpp
        label.cpp
        include/fillWord/label.hpp)

add_library(fillWord ${PROJECT_LIBRARY})
set_property(TARGET fillWord PROPERTY CXX_STANDARD 20)

target_include_directories(fillWord PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

target_link_libraries(fillWord PRIVATE pointsMatrixGeneration Qt${QT_VERSION_MAJOR}::Widgets)
install(TARGETS fillWord)

