//
// Created by Christopher Sawczuk on 25/11/2016.
//

#ifndef MARKDOWNPOINT_PRESENTATION_H
#define MARKDOWNPOINT_PRESENTATION_H

#include <slide.hpp>

namespace MarkdownPoint {
    class Presentation {
    public:
        Presentation();

        ssize_t slideCount();

        Slide *addSlide();

        Slide *slide(uint32_t idx);

    private:
        std::vector<Slide *> _slides;
    };
}

#endif //MARKDOWNPOINT_PRESENTATION_H
