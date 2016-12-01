//
// Created by Christopher Sawczuk on 25/11/2016.
//

#include <markdownpoint.hpp>

namespace MarkdownPoint {
    MarkdownPoint::Presentation MarkdownPresentationParser::parse(const std::string &markdown) {
        MarkdownPoint::Presentation presentation;

        for (std::string slideString : splitSlides(markdown)) {
            MarkdownPoint::Slide *slide = presentation.addSlide();

            std::vector<std::string> markdownElements = split(slideString, "\n");

            for (std::string element : markdownElements) {
                uint32_t spaces = countSpaces(element);
                std::string trimmed = element.substr(spaces);
                std::string start = element.substr(spaces, 2);
                if (trimmed.substr(0, 2) == "# ") {
                    slide->addElement(new MarkdownPoint::Heading(element.substr(2), 1));
                } else if (trimmed.substr(0, 3) == "## ") {
                    slide->addElement(new MarkdownPoint::Heading(element.substr(3), 2));
                } else if (trimmed.substr(0, 4) == "### ") {
                    slide->addElement(new MarkdownPoint::Heading(element.substr(4), 3));
                } else if (trimmed.substr(0, 5) == "#### ") {
                    slide->addElement(new MarkdownPoint::Heading(element.substr(5), 4));
                } else if (start == "* " || start == "- " || start == "+ ") {
                    slide->addElement(new MarkdownPoint::BulletPoint(element.substr(spaces + 2), (spaces / 2)));
                } else {
                    slide->addElement(new MarkdownPoint::Paragraph(element));
                }
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

    uint32_t MarkdownPresentationParser::countSpaces(std::string input) {
        uint32_t spaces = 0;
        for(uint32_t i = 0; i < input.size() && input[i] == ' '; i++)
        {
            spaces = i+1;
        }
        return spaces;
    }
}