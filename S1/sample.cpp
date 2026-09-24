/**
 * Proprietary Source-Available License.
 *
 * Copyright (c) 2026 Weather. All Rights Reserved.
 *
 * This code is for educational purposes only.
 * Unauthorized copying, distribution, or modification is prohibited.
 */

#include <utils.h>

#include <type_traits>
#include <memory>
#include <cassert>

extern "C" {
typedef struct _SimpleByteArray SimpleByteArray;

extern STATUS SimpleByteArray_init( SimpleByteArray **out_list );
extern STATUS SimpleByteArray_free( SimpleByteArray *in_list );
extern STATUS SimpleByteArray_insert( SimpleByteArray *list, size_t index, BYTE value );
extern STATUS SimpleByteArray_insert_bytes( SimpleByteArray *list, size_t index, const BYTE *values, size_t count );
extern STATUS SimpleByteArray_remove( SimpleByteArray *list, size_t index, BYTE *opt_removed );
extern STATUS SimpleByteArray_get( const SimpleByteArray *list, size_t index, BYTE *value );
extern STATUS SimpleByteArray_size( const SimpleByteArray *list, size_t *value );
}

template <typename T>
class SimpleArray
{
public:
    SimpleArray() 
    {
        // For byte arrays, T needs to be trivially copyable.
        // Things like interfaces, mutated classes or ref counted objects cannot be copied!
        static_assert( std::is_trivially_copyable_v<T> );
        check_st_( SimpleByteArray_init( &m_array ) );
    }

    ~SimpleArray()
    {
        check_st_( SimpleByteArray_free( m_array ) );
    }

    void
    Insert( size_t index, T value )
    {
        check_st_( SimpleByteArray_insert_bytes( m_array, index * sizeof(T), reinterpret_cast<const PBYTE>(&value), sizeof(T) ) );
    }

    void
    Remove( size_t index )
    {
        size_t iterator;
        const size_t byte_index = index * sizeof(T);

        for ( iterator = 0; iterator < sizeof(T); iterator++ )
            check_st_( SimpleByteArray_remove( m_array, byte_index, nullptr ) );
    }

    T
    Get( size_t index ) const
    {
        T value{};
        size_t iterator;
        const size_t byte_index = index * sizeof(T);
        BYTE* bytes = reinterpret_cast<BYTE*>(&value);

        for ( iterator = 0; iterator < sizeof(T); iterator++ )
            check_st_( SimpleByteArray_get( m_array, byte_index + iterator, &bytes[iterator] ) );

        return value;
    }

    size_t
    Size() const
    {
        size_t byte_size{};
        check_st_( SimpleByteArray_size( m_array, &byte_size ) );

        return byte_size / sizeof(T);
    }

private:
    SimpleByteArray *m_array{ nullptr };
};

void testArray()
{
    SimpleArray<int> array;

#ifdef LINKED_LISTS
    std::printf("Using Linked Lists...\n");
#elif defined(CONTIGUOUS_LISTS)
    std::printf("Using Contiguous Lists...\n");
#endif

    // Initially empty
    assert(array.Size() == 0);

    // Insert one value
    array.Insert(0, 42);
    assert(array.Size() == 1);
    assert(array.Get(0) == 42);

    // Insert another value
    array.Insert(1, 100);
    assert(array.Size() == 2);
    assert(array.Get(0) == 42);
    assert(array.Get(1) == 100);

    // Insert in the middle
    array.Insert(1, 55);
    assert(array.Size() == 3);
    assert(array.Get(0) == 42);
    assert(array.Get(1) == 55);
    assert(array.Get(2) == 100);

    // Remove a value
    array.Remove(1);
    assert(array.Size() == 2);
    assert(array.Get(0) == 42);
    assert(array.Get(1) == 100);

    // Remove first value
    array.Remove(0);
    assert(array.Size() == 1);
    assert(array.Get(0) == 100);

    // Remove last value
    array.Remove(0);
    assert(array.Size() == 0);

    // Test another trivially-copyable type
    SimpleArray<double> doubles;
    doubles.Insert(0, 3.14);
    doubles.Insert(1, 2.71);

    assert(doubles.Size() == 2);
    assert(doubles.Get(0) == 3.14);
    assert(doubles.Get(1) == 2.71);
}

struct Student
{
    int age;
    int id;
    double score;
};

#include <cstdio>

void printStudent(const Student& student)
{
    std::printf("ID: %d\n", student.id);
    std::printf("Age: %d\n", student.age);
    std::printf("Score: %f\n", student.score);
}

int main()
{
    SimpleArray<Student> students;
    int choice;

    testArray();

    while (true)
    {
        std::printf("\n--- Student Menu ---\n");
        std::printf("1. Add student\n");
        std::printf("2. Remove student\n");
        std::printf("3. Get student\n");
        std::printf("4. List students\n");
        std::printf("5. Exit\n");
        std::printf("Choose an option: ");

        std::cin >> choice;

        if ( choice == 1 )
        {
            Student student{};

            std::printf("Enter student ID: ");
            std::cin >> student.id;

            std::printf("Enter student age: ");
            std::cin >> student.age;

            std::printf("Enter student score: ");
            std::cin >> student.score;

            // Add to the end of the array
            students.Insert( students.Size(), student );

            std::printf("Student added.\n");
        }
        else if ( choice == 2 )
        {
            if ( students.Size() == 0 )
            {
                std::printf("There are no students.\n");
                continue;
            }

            size_t index;

            std::printf("Enter student index to remove: ");
            std::cin >> index;

            if ( index >= students.Size() )
            {
                std::printf("Invalid index.\n");
                continue;
            }

            students.Remove( index );

            std::printf("Student removed.\n");
        }
        else if ( choice == 3 )
        {
            if ( students.Size() == 0 )
            {
                std::printf("There are no students.\n");
                continue;
            }

            size_t index;

            std::printf("Enter student index: ");
            std::cin >> index;

            if ( index >= students.Size() )
            {
                std::printf("Invalid index.\n");
                continue;
            }

            Student student = students.Get( index );

            std::printf("\nStudent information:\n");
            printStudent( student );
        }
        else if ( choice == 4 )
        {
            if ( students.Size() == 0 )
            {
                std::printf("There are no students.\n");
                continue;
            }

            std::printf("\n--- Students ---\n");

            for ( size_t i = 0; i < students.Size(); i++ )
            {
                Student student = students.Get( i );

                std::printf("\nIndex: %zu\n", i);
                printStudent( student );
            }
        }
        else if ( choice == 5 )
        {
            std::printf("Goodbye!\n");
            break;
        }
        else
        {
            std::printf("Invalid option.\n");
        }
    }

    return 0;
}
