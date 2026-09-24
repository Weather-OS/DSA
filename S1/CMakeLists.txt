add_executable(LinkedLists
    tester.c
    linkedlists.c )

add_executable(ContiguousLists
    tester.c
    contiguouslists.c )

target_include_directories(LinkedLists PRIVATE
    ${PROJECT_SOURCE_DIR}/include )

target_include_directories(ContiguousLists PRIVATE
    ${PROJECT_SOURCE_DIR}/include )