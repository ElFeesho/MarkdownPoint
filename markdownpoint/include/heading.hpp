//
// Created by Christopher Sawczuk on 25/11/2016.
//

#ifndef MARKDOWNPOINT_HEADING_H
#define MARKDOWNPOINT_HEADING_H

#include <vector>
#include "block.hpp"

namespace MarkdownPoint {

    class Heading : public MarkdownPoint::Block {
    public:
        Heading(const std::string &text, uint32_t size = 1);

        virtual std::string type();

        unsigned int size();

        std::string text();

    private:
        std::string _text;
        unsigned int _size;
    };
}


#endif //MARKDOWNPOINT_HEADING_H