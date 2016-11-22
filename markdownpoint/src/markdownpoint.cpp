#include <iostream>

#include <markdownpoint.hpp>

namespace MarkdownPoint
{
    Heading::Heading(const std::string &text, int size) : _text(text), _size(size) {

    }



    std::string Heading::type() {
        return "heading";
    }

    uint32_t Heading::size()
    {
        return _size;
    }

    std::string Heading::text() {
        return _text;
    }


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

    Slide *Presentation::slide(uint32_t idx)
    {
        return _slides[idx];
    }
}