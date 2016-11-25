//
// Created by Christopher Sawczuk on 25/11/2016.
//

#include "paragraph.hpp"

namespace MarkdownPoint {
    Paragraph::Paragraph(const std::string &text) : _text(text) {
    }

    std::string Paragraph::type() {
        return "paragraph";
    }

    std::string Paragraph::text() {
        return _text;
    }
}