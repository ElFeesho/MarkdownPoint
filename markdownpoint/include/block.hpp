//
// Created by Christopher Sawczuk on 25/11/2016.
//

#ifndef MARKDOWNPOINT_BLOCK_H
#define MARKDOWNPOINT_BLOCK_H

#include <string>

namespace MarkdownPoint {
    class Block {
    public:
        Block() {}
        virtual ~Block(){}
        virtual std::string type() = 0;
    };
}

#endif //MARKDOWNPOINT_BLOCK_H
