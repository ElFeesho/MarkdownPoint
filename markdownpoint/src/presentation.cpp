//
// Created by Christopher Sawczuk on 25/11/2016.
//

#include <presentation.hpp>

namespace MarkdownPoint {
    Presentation::Presentation() {
    }

    ssize_t Presentation::slideCount() {
        return _slides.size();
    }

    Slide *Presentation::addSlide() {
        Slide *slide = new Slide();
        _slides.push_back(slide);
        return slide;
    }

    Slide *Presentation::slide(uint32_t idx) {
        return _slides[idx];
    }
}