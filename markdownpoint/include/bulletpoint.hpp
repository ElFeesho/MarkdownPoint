//
// Created by Christopher Sawczuk on 25/11/2016.
//

#ifndef MARKDOWNPOINT_BULLETPOINT_H
#define MARKDOWNPOINT_BULLETPOINT_H

#include <block.hpp>

namespace MarkdownPoint {
    class BulletPoint : public Element
    {
    public:
        BulletPoint(const std::string &text, uint32_t indentLevel = 0);

        std::string type() const;

        uint32_t indentLevel() const;

        std::string text() const;
    private:
        std::string _text;
        uint32_t _indentLevel;
    };
}

#endif //MARKDOWNPOINT_BULLETPOINT_H
