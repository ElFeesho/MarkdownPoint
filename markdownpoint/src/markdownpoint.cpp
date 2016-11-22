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

    Paragraph::Paragraph(const std::string &text) : _text(text) {
    }

    std::string Paragraph::type() {
        return "paragraph";
    }

    std::string Paragraph::text() {
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

            for(std::string element : markdownElements) {
                if (element.substr(0, 2) == "# ") {
                    slide->addBlock(new MarkdownPoint::Heading(element.substr(2), 1));
                } else {
                    slide->addBlock(new MarkdownPoint::Paragraph(element));
                }
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

    PresentationRenderer::PresentationRenderer(Renderer *renderer) : _renderer(renderer) {

    }

    void PresentationRenderer::render(Presentation &p) {
        for (uint32_t i = 0; i < p.slideCount(); i++)
        {
            Slide *slide = p.slide(i);
            _renderer->renderPage(slide);
            for (uint32_t k = 0; k < slide->blockCount(); k++)
            {
                Block *block = slide->block(k);
                if(block->type() == "heading") {
                    _renderer->renderHeading(dynamic_cast<Heading *>(block));
                }
                else if(block->type() == "paragraph")
                {
                    _renderer->renderParagraph(dynamic_cast<Paragraph *>(block));
                }
            }
        }
    }
}