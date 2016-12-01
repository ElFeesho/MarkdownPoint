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
MarkdownPoint::PresentationRenderer renderer(spyRenderer);

MarkdownPoint::Presentation givenAPresentationSlideContaining(MarkdownPoint::Block *block)
{
    MarkdownPoint::Presentation presentation;

    presentation.addSlide()->addBlock(block);

    return presentation;
}

TEST(presentation_renderer, will_delegate_creation_of_slide) {
    MarkdownPoint::Presentation presentation;
    presentation.addSlide();

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderPageCalled, true);
}

TEST(presentation_renderer, will_render_a_header) {
    auto presentation = givenAPresentationSlideContaining(new MarkdownPoint::Heading("Expected Header"));

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderHeadingCalled, true);
}

TEST(presentation_renderer, will_render_a_paragraph){
    auto presentation = givenAPresentationSlideContaining(new MarkdownPoint::Paragraph("Expected Paragraph"));

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderParagraphCalled, true);
}

TEST(presentation_renderer, will_render_a_bullet_point){
    auto presentation = givenAPresentationSlideContaining(new MarkdownPoint::BulletPoint("Bullet Point"));

    renderer.render(presentation);

    EXPECT_EQ(spyRenderer->renderBulletPointCalled, true);
}
