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
        _renderer->renderPage(p.slide(0));
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

    bool renderPageCalled;
};

TEST(presentation_renderer, will_delegate_creation_of_slide) {
    SpyRenderer *spyRenderer = new SpyRenderer();

    MarkdownPoint::PresentationRenderer renderer(spyRenderer);
    
    MarkdownPoint::Presentation presentation;
    presentation.addSlide();

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderPageCalled, true);
}

