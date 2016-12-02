#ifndef __MARKDOWN_POINT_HPP__
#define __MARKDOWN_POINT_HPP__

#include <vector>
#include <block.hpp>
#include <heading.hpp>
#include <paragraph.hpp>
#include <slide.hpp>
#include <presentation.hpp>
#include <markdownpresentationparser.hpp>
#include <presentationrenderer.hpp>
#include <bulletpoint.hpp>
#include <functional>

namespace MarkdownPoint {
    using split_predicate = std::function<unsigned long(const std::string&)>;

    std::vector<std::string> splitString(const std::string &input, split_predicate = [](const std::string& input) -> unsigned long {
        unsigned long newLinePosition = input.find("\n");
        if (newLinePosition != std::string::npos)
        {
            return newLinePosition + 1;
        }
        else
        {
            return input.length();
        }
    });
}

#endif