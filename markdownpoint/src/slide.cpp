//
// Created by Christopher Sawczuk on 25/11/2016.
//

#include <slide.hpp>

namespace MarkdownPoint {
    Slide::Slide() {

    }

    Block *Slide::block(uint32_t idx) {
        return _blocks[idx];
    }

    ssize_t Slide::blockCount() {
        return _blocks.size();
    }


    void Slide::addBlock(Block *block) {
        _blocks.push_back(block);
    }
}