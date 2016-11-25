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

    void renderHeading(::MarkdownPoint::Heading *heading) {
        renderHeadingCalled = true;
    }

    void renderParagraph(MarkdownPoint::Paragraph *paragraph) {
        renderParagraphCalled = true;
    }

    bool renderPageCalled;
    bool renderHeadingCalled;
    bool renderParagraphCalled;
};

SpyRenderer *spyRenderer = new SpyRenderer();

TEST(presentation_renderer, will_delegate_creation_of_slide) {
    MarkdownPoint::PresentationRenderer renderer(spyRenderer);

    MarkdownPoint::Presentation presentation;
    presentation.addSlide();

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderPageCalled, true);
}

TEST(presentation_renderer, will_render_a_header) {
    MarkdownPoint::PresentationRenderer renderer(spyRenderer);

    MarkdownPoint::Presentation presentation;
    MarkdownPoint::Slide *slide = presentation.addSlide();
    slide->addBlock(new MarkdownPoint::Heading("Expected Header"));

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderHeadingCalled, true);
}

TEST(presentation_renderer, will_render_a_paragraph){
    MarkdownPoint::PresentationRenderer renderer(spyRenderer);

    MarkdownPoint::Presentation presentation;
    MarkdownPoint::Slide *slide = presentation.addSlide();
    slide->addBlock(new MarkdownPoint::Paragraph("Expected Header"));

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderParagraphCalled, true);
}

TEST(presentation_renderer, will_render_a_list_of_bullets){
    MarkdownPoint::PresentationRenderer renderer(spyRenderer);

    MarkdownPoint::Presentation presentation;
    MarkdownPoint::Slide *slide = presentation.addSlide();
    slide->addBlock(new MarkdownPoint::BulletPoint("Expected Header"));

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderParagraphCalled, true);
}