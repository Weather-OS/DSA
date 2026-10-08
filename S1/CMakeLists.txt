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

target_compile_definitions(LinkedListsSample PRIVATE
        LINKED_LISTS )

target_compile_definitions(ContiguousListsSample PRIVATE
        CONTIGUOUS_LISTS )