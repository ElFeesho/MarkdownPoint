//
// Created by Christopher Sawczuk on 25/11/2016.
//

#ifndef MARKDOWNPOINT_BULLETPOINT_H
#define MARKDOWNPOINT_BULLETPOINT_H

#include <block.hpp>

namespace MarkdownPoint {
    class BulletPoint : public Block
    {
    public:
        BulletPoint(const std::string &text, uint32_t indentLevel = 0);

        std::string type();
    private:
        std::string _text;
        uint32_t _indentLevel;
    };
}

#endif //MARKDOWNPOINT_BULLETPOINT_H
