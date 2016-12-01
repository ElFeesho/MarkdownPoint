//
// Created by Christopher Sawczuk on 25/11/2016.
//

#ifndef MARKDOWNPOINT_PARAGRAPH_H
#define MARKDOWNPOINT_PARAGRAPH_H

#include "block.hpp"

namespace MarkdownPoint {

    class Paragraph : public Element {
    public:
        Paragraph(const std::string &text);

        std::string type() const;

        std::string text() const;

    private:
        std::string _text;
    };
}

#endif //MARKDOWNPOINT_PARAGRAPH_H
