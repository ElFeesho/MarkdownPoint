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

        void addElement(Element *block);

        Element *element(uint32_t idx);

        template<typename T>
        T element(uint32_t idx)
        {
            return dynamic_cast<T>(_elements[idx].get());
        }

        ssize_t elementCount();

    private:
        std::vector<std::unique_ptr<Element>> _elements;
    };
}

#endif //MARKDOWNPOINT_SLIDE_HPP_H
