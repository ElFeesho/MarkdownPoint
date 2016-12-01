//
// Created by Christopher Sawczuk on 25/11/2016.
//

#include <slide.hpp>

namespace MarkdownPoint {
    Slide::Slide() {

    }

    Element *Slide::element(uint32_t idx) {
        return _elements[idx].get();
    }

    ssize_t Slide::elementCount() {
        return _elements.size();
    }

    void Slide::addElement(Element *block) {
        _elements.push_back(std::unique_ptr<Element>(block));
    }
}