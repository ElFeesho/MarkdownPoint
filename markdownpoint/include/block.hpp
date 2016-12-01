//
// Created by Christopher Sawczuk on 25/11/2016.
//

#ifndef MARKDOWNPOINT_BLOCK_H
#define MARKDOWNPOINT_BLOCK_H

#include <string>

namespace MarkdownPoint {
    class Element {
    public:
        Element() {}
        virtual ~Element(){}
        virtual std::string type() const = 0;
    };
}

#endif //MARKDOWNPOINT_BLOCK_H
