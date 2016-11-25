//
// Created by Christopher Sawczuk on 25/11/2016.
//

#include <markdownpresentationparser.hpp>
#include <heading.hpp>
#include <paragraph.hpp>

namespace MarkdownPoint {
    MarkdownPoint::Presentation MarkdownPresentationParser::parse(const std::string &markdown) {
        MarkdownPoint::Presentation presentation;

        for (std::string slideString : splitSlides(markdown)) {
            MarkdownPoint::Slide *slide = presentation.addSlide();

            std::vector <std::string> markdownElements = split(slideString, "\n");

            for (std::string element : markdownElements) {
                if (element.substr(0, 2) == "# ") {
                    slide->addBlock(new MarkdownPoint::Heading(element.substr(2), 1));
                } else {
                    slide->addBlock(new MarkdownPoint::Paragraph(element));
                }
            }
        }

        return presentation;
    }

    std::vector <std::string> MarkdownPresentationParser::splitSlides(const std::string &rawInput) {
        return split(rawInput, "<==>");
    }

    std::vector <std::string>
    MarkdownPresentationParser::split(const std::string &rawInput, const std::string &delimeter) {
        std::vector <std::string> tokenisedResult;

        std::string inputLeft = rawInput;
        while (inputLeft.find(delimeter) != std::string::npos) {
            tokenisedResult.push_back(std::string(inputLeft, 0, inputLeft.find(delimeter)));
            inputLeft = inputLeft.substr(inputLeft.find(delimeter) + delimeter.size());
        }

        tokenisedResult.push_back(inputLeft);

        return tokenisedResult;
    }
}