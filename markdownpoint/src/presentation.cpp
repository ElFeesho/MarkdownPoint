//
// Created by Christopher Sawczuk on 25/11/2016.
//

#include <presentation.hpp>

namespace MarkdownPoint {
    Presentation::Presentation() {
    }

    ssize_t Presentation::slideCount() const {
        return _slides.size();
    }

    Slide *Presentation::addSlide() {
        _slides.emplace_back(new Slide());
        return _slides[_slides.size()-1].get();
    }

    Slide *Presentation::slide(uint32_t idx) const {
        return _slides[idx].get();
    }
}