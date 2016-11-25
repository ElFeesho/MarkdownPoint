//
// Created by Christopher Sawczuk on 25/11/2016.
//

#include <markdownpoint.hpp>
#include <iostream>
#include "heading.hpp"

namespace MarkdownPoint {
    Heading::Heading(const std::string &text, uint32_t size) : _text(text), _size(size) {

    }

    std::string Heading::type() {
        return "heading";
    }

    uint32_t Heading::size() {
        return _size;
    }

    std::string Heading::text() {
        return _text;
    }
}