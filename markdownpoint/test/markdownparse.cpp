//
// Created by Christopher Sawczuk on 21/11/2016.
//

#include <string>

#include <gtest/gtest.h>
#include <markdownpoint.hpp>

namespace MarkdownPoint {

    class MarkdownPresentationParser {
    public:
        MarkdownPoint::Presentation parse(const std::string &markdown);

    private:
        std::vector<std::string> splitSlides(const std::string &rawInput);

        std::vector<std::string> split(const std::string &rawInput, const std::string &delimeter);
    };

    MarkdownPoint::Presentation MarkdownPresentationParser::parse(const std::string &markdown) {
        MarkdownPoint::Presentation presentation;

        for (std::string slideString : splitSlides(markdown)) {
            MarkdownPoint::Slide *slide = presentation.addSlide();

            std::vector<std::string> markdownElements = split(slideString, "\n");

            if (slideString.substr(0, 2) == "# ") {
                slide->addBlock(new MarkdownPoint::Heading(slideString.substr(2), 1));
            }
        }

        return presentation;
    }

    std::vector<std::string> MarkdownPresentationParser::splitSlides(const std::string &rawInput) {
        return split(rawInput, "<==>");
    }

    std::vector<std::string>
    MarkdownPresentationParser::split(const std::string &rawInput, const std::string &delimeter) {
        std::vector<std::string> tokenisedResult;

        std::string inputLeft = rawInput;
        while (inputLeft.find(delimeter) != std::string::npos) {
            tokenisedResult.push_back(std::string(inputLeft, 0, inputLeft.find(delimeter)));
            inputLeft = inputLeft.substr(inputLeft.find(delimeter) + delimeter.size());
        }

        tokenisedResult.push_back(inputLeft);

        return tokenisedResult;
    }
}

TEST(markdown_parsing, can_parse_an_empty_page) {
    MarkdownPoint::MarkdownPresentationParser p;
    MarkdownPoint::Presentation presentation = p.parse("");

    EXPECT_EQ(presentation.slideCount(), 1);
}

TEST(markdown_parsing, can_parse_multiple_slides) {
    MarkdownPoint::MarkdownPresentationParser p;
    MarkdownPoint::Presentation presentation = p.parse("<==><==>");

    EXPECT_EQ(presentation.slideCount(), 3);
}

TEST(markdown_parsing, can_parse_a_heading) {
    MarkdownPoint::MarkdownPresentationParser p;
    MarkdownPoint::Presentation presentation = p.parse("# Heading");

    MarkdownPoint::Slide *slide = presentation.slide(0);
    EXPECT_EQ(slide->blockCount(), 1);
    EXPECT_EQ(slide->block(0)->type(), "heading");

    MarkdownPoint::Heading *heading = dynamic_cast<MarkdownPoint::Heading *>(slide->block(0));
    EXPECT_EQ(heading->size(), 1);
    EXPECT_EQ(heading->text(), "Heading");
}