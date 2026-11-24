cmake_minimum_required(VERSION 3.20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

if(DEFINED ENV{OPENSSL_ROOT_DIR})
    set(OPENSSL_ROOT_DIR "$ENV{OPENSSL_ROOT_DIR}")
    set(OPENSSL_USE_STATIC_LIBS TRUE)
endif()

add_subdirectory(cpp-httplib)
add_subdirectory(json)

find_package(OpenSSL REQUIRED)

add_executable(db
    main.cpp
    src/DB.cpp
)

target_include_directories(db SYSTEM PRIVATE cpp-httplib json/single_include)

target_link_libraries(db PRIVATE
    httplib::httplib
    nlohmann_json::nlohmann_json
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
    ${CMAKE_DL_LIBS}
)

if(UNIX AND NOT APPLE)
    target_link_libraries(db PRIVATE anl)
endif()