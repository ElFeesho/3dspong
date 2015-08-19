cmake_minimum_required(VERSION 3.2)
project(3dspong)

set(CMAKE_MODULE_PATH "/usr/local/Cellar/sfml/2.3/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I../source -I/usr/local/include/freetype2 -I../host -D__MACOSX__ -std=c++11 -I/usr/local/include -g -fPIC -Wall -O0 -W -Wshadow -Wunused-variable \
                                                                   -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers \
                                                                   -Wno-deprecated -Woverloaded-virtual -Wwrite-strings")
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES ../source/main.cpp ../source/ball.cpp ../source/pongpaddle.cpp sfmlgfx.cpp sfmlinput.cpp)

add_executable(3dspong ${SOURCE_FILES})
target_link_libraries(3dspong -lm -lfreetype ${SFML_LIBRARIES})
