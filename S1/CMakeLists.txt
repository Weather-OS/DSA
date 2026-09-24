add_executable(LinkedListsTests
    tester.c
    linkedlists.c )

add_executable(ContiguousListsTests
    tester.c
    contiguouslists.c )

add_executable(LinkedListsSample
    sample.cpp
    linkedlists.c )

add_executable(ContiguousListsSample
    sample.cpp
    contiguouslists.c )

target_include_directories(LinkedListsTests PRIVATE
    ${PROJECT_SOURCE_DIR}/include )

target_include_directories(ContiguousListsTests PRIVATE
    ${PROJECT_SOURCE_DIR}/include )

target_include_directories(LinkedListsSample PRIVATE
    ${PROJECT_SOURCE_DIR}/include )

target_include_directories(ContiguousListsSample PRIVATE
    ${PROJECT_SOURCE_DIR}/include )