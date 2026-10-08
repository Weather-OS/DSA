add_executable(BracketTester
    ../S1/linkedlists.c
    brackettester.cpp )

target_include_directories(BracketTester PRIVATE
        ${PROJECT_SOURCE_DIR}/include )