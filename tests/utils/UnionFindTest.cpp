//Copyright (c) 2018 Ultimaker B.V.
//CuraEngine is released under the terms of the AGPLv3 or higher.

#include "UnionFindTest.h"

namespace cura
{

CPPUNIT_TEST_SUITE_REGISTRATION(UnionFindTest);

void UnionFindTest::setUp()
{
    union_find = UnionFind<char>(); //Recreate the UnionFind data structure.
}

void UnionFindTest::tearDown()
{
    //Nothing to tear down.
}

void UnionFindTest::findSimpleTest()
{
    size_t original = union_find.add('A');
    size_t result = union_find.find('A');
    CPPUNIT_ASSERT_MESSAGE("The set of the first element may not be -1.", result != (size_t)-1);
    CPPUNIT_ASSERT_MESSAGE("Find must return the original key that was returned when adding.", result == original);
}

void UnionFindTest::findMultipleTest()
{
    size_t original_a = union_find.add('A');
    size_t original_b = union_find.add('B');
    size_t original_c = union_find.add('C');
    size_t result_a = union_find.find('A');
    size_t result_b = union_find.find('B');
    size_t result_c = union_find.find('C');

    CPPUNIT_ASSERT_MESSAGE("A must be the same as when adding it.", original_a == result_a);
    CPPUNIT_ASSERT_MESSAGE("B must be the same as when adding it.", original_b == result_b);
    CPPUNIT_ASSERT_MESSAGE("C must be the same as when adding it.", original_c == result_c);
    CPPUNIT_ASSERT_MESSAGE("A must not be in the same set as B or C.", result_a != result_b && result_a != result_c);
    CPPUNIT_ASSERT_MESSAGE("B must not be in the same set as C.", result_b != result_c);
}

void UnionFindTest::uniteTwoTest()
{
    union_find.add('A');
    union_find.add('B');
    size_t original_a = union_find.find('A');
    size_t original_b = union_find.find('B');
    CPPUNIT_ASSERT_MESSAGE("A must not yet be in the same set as B.", original_a != original_b);

    union_find.unite(original_a, original_b);

    size_t united_a = union_find.find('A');
    size_t united_b = union_find.find('B');
    CPPUNIT_ASSERT_MESSAGE("A must now be in the same set as B.", united_a == united_b);
}

void UnionFindTest::uniteThreeTest()
{
    union_find.add('A');
    union_find.add('B');
    union_find.add('C');

    size_t original_a = union_find.find('A');
    size_t original_b = union_find.find('B');
    size_t original_c = union_find.find('C');
    CPPUNIT_ASSERT_MESSAGE("A, B and C must not yet be in the same set!", original_a != original_b && original_a != original_c && original_b != original_c);

    union_find.unite(original_a, original_b);
    union_find.unite(original_b, original_c);

    size_t united_a = union_find.find('A');
    size_t united_b = union_find.find('B');
    size_t united_c = union_find.find('C');
    CPPUNIT_ASSERT_MESSAGE("A, B and C must now be in the same set.", united_a == united_b && united_b == united_c);
}

}