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

    MarkdownPoint::Presentation MarkdownPresentationParser::parse(const std::string &markdown) {
        MarkdownPoint::Presentation presentation;

        for (std::string slideString : splitSlides(markdown)) {
            MarkdownPoint::Slide *slide = presentation.addSlide();

            std::vector<std::string> markdownElements = split(slideString, "\n");

            if (slideString.substr(0, 2) == "# ") {
                slide->addBlock(new MarkdownPoint::Heading(slideString.substr(2), 1));
            }
        }

        return presentation;
    }

    std::vector<std::string> MarkdownPresentationParser::splitSlides(const std::string &rawInput) {
        return split(rawInput, "<==>");
    }

    std::vector<std::string>
    MarkdownPresentationParser::split(const std::string &rawInput, const std::string &delimeter) {
        std::vector<std::string> tokenisedResult;

        std::string inputLeft = rawInput;
        while (inputLeft.find(delimeter) != std::string::npos) {
            tokenisedResult.push_back(std::string(inputLeft, 0, inputLeft.find(delimeter)));
            inputLeft = inputLeft.substr(inputLeft.find(delimeter) + delimeter.size());
        }

        tokenisedResult.push_back(inputLeft);

        return tokenisedResult;
    }
}