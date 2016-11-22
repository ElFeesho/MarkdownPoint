//
// Created by Christopher Sawczuk on 22/11/2016.
//


#include <gtest/gtest.h>
#include <markdownpoint.hpp>

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

    void renderParagraph(MarkdownPoint::Paragraph *paragraph) {
        renderParagraphCalled = true;
    }

    bool renderPageCalled;
    bool renderHeadingCalled;
    bool renderParagraphCalled;
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

TEST(presentation_renderer, will_render_a_paragraph){
    SpyRenderer *spyRenderer = new SpyRenderer();

    MarkdownPoint::PresentationRenderer renderer(spyRenderer);

    MarkdownPoint::Presentation presentation;
    MarkdownPoint::Slide *slide = presentation.addSlide();
    slide->addBlock(new MarkdownPoint::Paragraph("Expected Header"));

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderParagraphCalled, true);
}