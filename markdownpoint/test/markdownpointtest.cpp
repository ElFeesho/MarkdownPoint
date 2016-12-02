//
// Created by Christopher Sawczuk on 02/12/2016.
//

#include "markdownpoint.hpp"
#include <gtest/gtest.h>

TEST(markdown_point_string_utilities, will_split_a_string_on_newlines) {
    auto result = MarkdownPoint::splitString("one\ntwo");
    EXPECT_EQ(result[0], "one\n");
    EXPECT_EQ(result[1], "two");
}

TEST(markdown_point_string_utilities, will_split_a_string_at_arbitrary_intervals) {
    auto result = MarkdownPoint::splitString("onetwo", [](const std::string &input) -> unsigned long { return 3; });
    EXPECT_EQ(result[0], "one");
    EXPECT_EQ(result[1], "two");
}