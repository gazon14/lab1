


project(SameGame)


add_library(SameGameLib
    cpp/SameGameBoard.cpp
     cpp/OptionDialog.cpp
      cpp/SameGame.cpp
     cpp/SameGameDoc.cpp
     cpp/SameGameView.cpp
)


target_include_directories(SameGameLib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_executable(SameGameMain
    cpp/SameGame.cpp
    
)


target_link_libraries(SameGameMain
    SameGameLib
)


add_executable(SameGameTests
    tests/SameGameBoardTest.cpp
    UnitTests/SameGameDocTest.cpp
     UnitTests/SameGameViewTest.cpp
)


target_link_libraries(SameGameTests
    SameGameLib
)


