//
// Created by Christopher Sawczuk on 21/11/2016.
//

#include <gtest/gtest.h>
#include <markdownpoint.hpp>

class MarkdownPresentationParser
{
public:
    MarkdownPoint::Presentation parse(const std::string &markdown);
};

MarkdownPoint::Presentation MarkdownPresentationParser::parse(const std::string &markdown)
{
    MarkdownPoint::Presentation presentation;

    MarkdownPoint::Slide *slide = presentation.addSlide();

    return presentation;
}


TEST(markdown_parsing, can_parse_an_empty_page) {
    MarkdownPresentationParser p;
    MarkdownPoint::Presentation presentation = p.parse("");

    EXPECT_EQ(presentation.slideCount(), 1);
}