#include <iostream>

#include <markdownpoint.hpp>

namespace MarkdownPoint
{
	Slide::Slide() {

	}

	Block *Slide::block(uint32_t idx) {
		return nullptr;
	}

	ssize_t Slide::blockCount() {
		return 0;
	}


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
}