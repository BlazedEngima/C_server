cmake_minimum_required(VERSION 3.14)
project(cpp_server)
set(LIBASYIK_ENABLE_SOCI OFF)  # if SOCI database support is desired
set(CMAKE_CXX_STANDARD 17)    # set to 14 or 17 when available

add_executable(${PROJECT_NAME} server.cpp) # add more source code here
add_executable(client client.cpp)

#######
#include other dependencies
#######
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
    target_link_libraries(client ${OpenCV_LIBS})
endif()

# LibAsyik
find_package(libasyik)
if(libasyik_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${libasyik_INCLUDE_DIR})
    target_include_directories(client PUBLIC ${libasyik_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} libasyik)
    target_link_libraries(client libasyik)
endif()

# Boost
find_package(Boost COMPONENTS context fiber date_time url REQUIRED)
if(Boost_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR})
    target_include_directories(client PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} Boost::fiber Boost::context Boost::date_time Boost::url)
    target_link_libraries(client Boost::fiber Boost::context Boost::date_time Boost::url)
endif()

# SOCI
find_package(SOCI REQUIRED) # if SOCI database support is desired
if(SOCI_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC /usr/include/postgresql)
    target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/soci)
    target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/soci/postgresql)
    target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/soci/sqlite3)
    target_include_directories(client PUBLIC /usr/include/postgresql)
    target_include_directories(client PUBLIC /usr/local/include/soci)
    target_include_directories(client PUBLIC /usr/local/include/soci/postgresql)
    target_include_directories(client PUBLIC /usr/local/include/soci/sqlite3)
 
    target_link_libraries(${PROJECT_NAME} SOCI::soci_core SOCI::soci_postgresql SOCI::soci_sqlite3)
    target_link_libraries(client SOCI::soci_core SOCI::soci_postgresql SOCI::soci_sqlite3)
endif()

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(client Threads::Threads)

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL)
target_link_libraries(client OpenSSL::SSL)