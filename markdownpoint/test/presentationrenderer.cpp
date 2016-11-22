//
// Created by Christopher Sawczuk on 22/11/2016.
//


#include <gtest/gtest.h>
#include <markdownpoint.hpp>

namespace MarkdownPoint {

    class Renderer {
    public:
        virtual ~Renderer(){}
        virtual void renderPage(Slide *slide) = 0;
        virtual void renderHeading(Heading *heading) = 0;
    };

    class PresentationRenderer {
    public:
        PresentationRenderer(Renderer* renderer);
        void render(Presentation &p);
    private:
        Renderer *_renderer;
    };

    PresentationRenderer::PresentationRenderer(Renderer *renderer) : _renderer(renderer) {

    }

    void PresentationRenderer::render(Presentation &p) {
        for (uint32_t i = 0; i < p.slideCount(); i++)
        {
            Slide *slide = p.slide(i);
            _renderer->renderPage(slide);
            for (uint32_t k = 0; k < slide->blockCount(); k++)
            {
                _renderer->renderHeading(dynamic_cast<Heading *>(slide->block(k)));
            }
        }
    }
}

class SpyRenderer : public MarkdownPoint::Renderer
{
public:
    ~SpyRenderer() {

    }

    void renderPage(MarkdownPoint::Slide *slide) {
        renderPageCalled = true;
    }

    void renderHeading(MarkdownPoint::Heading *heading) {
        renderHeadingCalled = true;
    }

    bool renderPageCalled;
    bool renderHeadingCalled;
};

TEST(presentation_renderer, will_delegate_creation_of_slide) {
    SpyRenderer *spyRenderer = new SpyRenderer();

    MarkdownPoint::PresentationRenderer renderer(spyRenderer);

    MarkdownPoint::Presentation presentation;
    presentation.addSlide();

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderPageCalled, true);
}

TEST(presentation_renderer, will_render_a_header) {
    SpyRenderer *spyRenderer = new SpyRenderer();

    MarkdownPoint::PresentationRenderer renderer(spyRenderer);

    MarkdownPoint::Presentation presentation;
    MarkdownPoint::Slide *slide = presentation.addSlide();
    slide->addBlock(new MarkdownPoint::Heading("Expected Header"));

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderHeadingCalled, true);
}

