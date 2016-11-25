//
// Created by Christopher Sawczuk on 25/11/2016.
//

#ifndef MARKDOWNPOINT_MARKDOWNPRESENTATIONPARSER_H
#define MARKDOWNPOINT_MARKDOWNPRESENTATIONPARSER_H

#include <presentation.hpp>

namespace MarkdownPoint {
    class MarkdownPresentationParser {
    public:
        MarkdownPoint::Presentation parse(const std::string &markdown);

    private:
        std::vector<std::string> splitSlides(const std::string &rawInput);

        std::vector<std::string> split(const std::string &rawInput, const std::string &delimeter);
    };
}

#endif //MARKDOWNPOINT_MARKDOWNPRESENTATIONPARSER_H
