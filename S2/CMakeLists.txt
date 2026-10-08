add_executable(BracketTester_LinkedStacks
    ../S1/linkedlists.c
    brackettester.cpp )

add_executable(BracketTester_ContiguousStacks
        ../S1/contiguouslists.c
        brackettester.cpp )

add_executable(ManualStack_LinkedStacks
        ../S1/linkedlists.c
        manualstack.cpp )

add_executable(ManualStack_ContiguousStacks
        ../S1/contiguouslists.c
        manualstack.cpp )

add_executable(ManualQueue_LinkedQueues
        ../S1/linkedlists.c
        manualqueue.cpp )

add_executable(ManualQueue_ContiguousQueues
        ../S1/contiguouslists.c
        manualqueue.cpp )

add_executable(ManualList_LinkedLists
        ../S1/linkedlists.c
        manuallist.cpp )

add_executable(ManualList_ContiguousLists
        ../S1/contiguouslists.c
        manuallist.cpp )

target_compile_definitions(BracketTester_LinkedStacks PRIVATE
        LINKED_LISTS )

target_compile_definitions(BracketTester_ContiguousStacks PRIVATE
        CONTIGUOUS_LISTS )

target_compile_definitions(ManualStack_LinkedStacks PRIVATE
        LINKED_LISTS )

target_compile_definitions(ManualStack_ContiguousStacks PRIVATE
        CONTIGUOUS_LISTS )

target_compile_definitions(ManualQueue_LinkedQueues PRIVATE
        LINKED_LISTS )

target_compile_definitions(ManualQueue_ContiguousQueues PRIVATE
        CONTIGUOUS_LISTS )

target_compile_definitions(ManualList_LinkedLists PRIVATE
        LINKED_LISTS )

target_compile_definitions(ManualList_ContiguousLists PRIVATE
        CONTIGUOUS_LISTS )