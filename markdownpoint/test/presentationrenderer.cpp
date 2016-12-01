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

    void renderHeading(const MarkdownPoint::Heading &heading) {
        renderHeadingCalled = true;
    }

    void renderParagraph(const MarkdownPoint::Paragraph &paragraph) {
        renderParagraphCalled = true;
    }

    void renderBulletPoint(const MarkdownPoint::BulletPoint &bulletPoint) {
        renderBulletPointCalled = true;
    }

    bool renderPageCalled;
    bool renderHeadingCalled;
    bool renderParagraphCalled;
    bool renderBulletPointCalled;
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
    slide->addBlock(new MarkdownPoint::Paragraph("Expected Paragraph"));

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderParagraphCalled, true);
}

TEST(presentation_renderer, will_render_a_bullet_point){
    MarkdownPoint::PresentationRenderer renderer(spyRenderer);

    MarkdownPoint::Presentation presentation;
    MarkdownPoint::Slide *slide = presentation.addSlide();
    slide->addBlock(new MarkdownPoint::BulletPoint("Bullet Point"));

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderBulletPointCalled, true);
}
