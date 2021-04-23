/* Test file for strided_range task.
 * @file
 * @date 2019-08-29
 * @author Anonymous
 */

#include <boost/range/iterator_range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>

#include <vector>

#include <catch2/catch.hpp>

#include <strided_range.hpp>

#include <iostream>

 // Two checks with different strides.
TEST_CASE("strided_range::stride") {
    std::vector<int> a1;
    std::vector<int> a2;

    for (size_t i = 0; i < 10; ++i) {
        a1.push_back(i);
        a2.push_back(i);
    }

    const size_t width = 5;
    const size_t stride1 = 1;
    const size_t stride2 = 6;

    const auto str_range1 = make_strided_range(a1, width, stride1);
    const auto str_range2 = make_strided_range(a2, width, stride2);

    std::vector control1{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector control2{ 0, 1, 2, 3, 4, 6, 7, 8, 9 };

    CHECK(str_range1 == control1);
    CHECK(str_range2 == control2);
}

// Two checks with different widths.
TEST_CASE("strided_range::width") {
    std::vector<int> a1;
    std::vector<int> a2;

    for (size_t i = 0; i < 10; ++i) {
        a1.push_back(i);
        a2.push_back(i);
    }

    const size_t width1 = 1;
    const size_t width2 = 6;

    const size_t stride = 5;

    const auto str_range1 = make_strided_range(a1, width1, stride);
    const auto str_range2 = make_strided_range(a2, width2, stride);

    std::vector control1{ 0, 5 };
    std::vector control2{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    size_t i = 0;
    for (const auto el : str_range1) {
        CHECK(el == control1[i++]);
    }

    i = 0;
    for (const auto el : str_range2) {
        CHECK(el == control2[i++]);
    }

}

TEST_CASE("strided_range::stride_equal_width") {
    std::vector<int> a;

    for (size_t i = 0; i < 10; ++i) {
        a.push_back(i);
    }

    const size_t width = 10;
    const size_t stride = 10;

    const auto str_range = make_strided_range(a, width, stride);

    std::vector control{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    size_t i = 0;
    for (const auto el : str_range) {
        CHECK(el == control[i++]);
    }
}

// Use boost::size.
TEST_CASE("strided_range::distance") {
    std::vector<int> a1;
    std::vector<int> a2;

    for (size_t i = 0; i < 10; ++i) {
        a1.push_back(i);
        a2.push_back(i);
    }

    const size_t width = 5;
    const size_t stride1 = 1;
    const size_t stride2 = 6;

    const auto str_range1 = make_strided_range(a1, width, stride1);
    const auto str_range2 = make_strided_range(a2, width, stride2);

    CHECK(boost::size(str_range1) == 10);
    CHECK(boost::size(str_range2) == 9);
}

// Make strided_range from another strided_range.
TEST_CASE("strided_range::from_strided") {
    std::vector<int> a;

    for (size_t i = 0; i < 10; ++i) {
        a.push_back(i);
    }

    const size_t width = 5;
    const size_t stride = 10;

    const auto str_range = make_strided_range(a, width, stride);
    const auto b = make_strided_range(str_range, width, stride);

    CHECK(str_range == b);
}

// Provide example with shifted data. It's like a window in the image. Hint: boost::make_iterator_range.
TEST_CASE("strided_range::shift") {
    std::vector<int> a;

    for (size_t i = 0; i < 100; ++i) {
        a.push_back(i);
    }

    const size_t width = 5;
    const size_t stride = 10;

    const auto str_range = make_strided_range(a, width, stride);

    auto it_end = str_range.begin();
    std::advance(it_end, 10);

    const auto new_range = boost::make_iterator_range(str_range.begin(), it_end);

    std::vector control{ 0, 1, 2, 3, 4, 10, 11, 12, 13, 14 };
    size_t i = 0;

    for (const auto el : new_range) {
        CHECK(el == control[i++]);
    }
}

TEST_CASE("strided_range::corner_case1") {
    std::vector<int> a;

    const auto str_range = make_strided_range(a, 1, 1);

    CHECK(boost::size(str_range) == 0);
}

TEST_CASE("strided_range::corner_case2") {
    std::vector a{ 0, 1, 2, 3, 4 };

    const auto str_range = make_strided_range(a, 0, 1);

    CHECK(boost::size(str_range) == 0);
}
