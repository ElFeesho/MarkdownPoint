//
// Created by Christopher Sawczuk on 25/11/2016.
//

#ifndef MARKDOWNPOINT_SLIDE_HPP_H
#define MARKDOWNPOINT_SLIDE_HPP_H

#include <vector>
#include <block.hpp>

namespace MarkdownPoint {

    class Slide {
    public:
        Slide();

        void addBlock(Block *block);

        Block *block(uint32_t idx);

        template<typename T>
        T block(uint32_t idx)
        {
            return dynamic_cast<T>(_blocks[idx]);
        }

        ssize_t blockCount();

    private:
        std::vector<Block *> _blocks;
    };
}

#endif //MARKDOWNPOINT_SLIDE_HPP_H
