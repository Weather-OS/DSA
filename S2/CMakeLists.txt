add_executable(BracketTester_LinkedStacks
    ../S1/linkedlists.c
    brackettester.cpp )

add_executable(BracketTester_ContiguousStacks
        ../S1/linkedlists.c
        brackettester.cpp )

target_compile_definitions(BracketTester_LinkedStacks PRIVATE
        LINKED_LISTS )

target_compile_definitions(BracketTester_ContiguousStacks PRIVATE
        CONTIGUOUS_LISTS )