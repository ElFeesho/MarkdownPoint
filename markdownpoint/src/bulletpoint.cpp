//
// Created by Christopher Sawczuk on 25/11/2016.
//

#include <bulletpoint.hpp>

namespace MarkdownPoint {


    BulletPoint::BulletPoint(const std::string &text, uint32_t indentLevel) : _text(text), _indentLevel(indentLevel) {

    }

    std::string BulletPoint::type() {
        return "bulletpoint";
    }

    uint32_t BulletPoint::indentLevel() {
        return _indentLevel;
    }

    std::string BulletPoint::text() {
        return _text;
    }
}
