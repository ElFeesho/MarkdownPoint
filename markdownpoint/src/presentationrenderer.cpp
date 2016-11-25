//
// Created by Christopher Sawczuk on 25/11/2016.
//

#include <presentationrenderer.hpp>

namespace MarkdownPoint {

    PresentationRenderer::PresentationRenderer(Renderer *renderer) : _renderer(renderer) {

    }

    void PresentationRenderer::render(Presentation &p) {
        for (uint32_t i = 0; i < p.slideCount(); i++) {
            Slide *slide = p.slide(i);
            _renderer->renderPage(slide);
            for (uint32_t k = 0; k < slide->blockCount(); k++) {
                Block *block = slide->block(k);
                if (block->type() == "heading") {
                    _renderer->renderHeading(dynamic_cast<Heading *>(block));
                } else if (block->type() == "paragraph") {
                    _renderer->renderParagraph(dynamic_cast<Paragraph *>(block));
                }
            }
        }
    }
}