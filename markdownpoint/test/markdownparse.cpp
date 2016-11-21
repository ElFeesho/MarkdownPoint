//
// Created by Christopher Sawczuk on 21/11/2016.
//

#include <string>

#include <gtest/gtest.h>
#include <markdownpoint.hpp>

class MarkdownPresentationParser
{
public:
    MarkdownPoint::Presentation parse(const std::string &markdown);
private:
    std::vector<std::string> splitSlides(const std::string &rawInput);
};

MarkdownPoint::Presentation MarkdownPresentationParser::parse(const std::string &markdown)
{
    MarkdownPoint::Presentation presentation;

    for(std::string slideString : splitSlides(markdown))
    {
        presentation.addSlide();
    }

    return presentation;
}

std::vector<std::string> MarkdownPresentationParser::splitSlides(const std::string &rawInput) {
    std::vector<std::string> individualSlides;

    std::string inputLeft = rawInput;
    while(inputLeft.find("<==>") != std::string::npos)
    {
        individualSlides.push_back(std::string(inputLeft, 0, inputLeft.find("<==>")));
        inputLeft = inputLeft.substr(inputLeft.find("<==>")+4);
    }

    individualSlides.push_back(inputLeft);

    return individualSlides;
}


TEST(markdown_parsing, can_parse_an_empty_page) {
    MarkdownPresentationParser p;
    MarkdownPoint::Presentation presentation = p.parse("");

    EXPECT_EQ(presentation.slideCount(), 1);
}

TEST(markdown_parsing, can_parse_multiple_slides) {
    MarkdownPresentationParser p;
    MarkdownPoint::Presentation presentation = p.parse("<==><==>");

    EXPECT_EQ(presentation.slideCount(), 3);
}