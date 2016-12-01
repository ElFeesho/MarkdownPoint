//
// Created by Christopher Sawczuk on 21/11/2016.
//

#include <vector>
#include <string>

#include <gtest/gtest.h>
#include <markdownpoint.hpp>

MarkdownPoint::Presentation parsePresentation(const std::string &markdown);

MarkdownPoint::Slide *givenAParsedPresentationSlide(const MarkdownPoint::Presentation &presentation) {
    return presentation.slide(0);
}

MarkdownPoint::Presentation parsePresentation(const std::string &markdown) {
    return MarkdownPoint::MarkdownPresentationParser().parse(markdown);
}

void blocksAreOfTheFollowingTypes(MarkdownPoint::Slide *slide, std::vector<const std::string> types) {
    for (uint32_t i = 0; i < types.size(); i++) {
        EXPECT_EQ(slide->element(i)->type(), types[i]);
    }
}

void expectHeadingWithSizeAndText(MarkdownPoint::Heading *heading, int size, const std::string &text) {
    EXPECT_EQ(heading->size(), size);
    EXPECT_EQ(heading->text(), text);
}

void expectParagraphWithText(MarkdownPoint::Paragraph *paragraph, const std::string &text) {
    EXPECT_EQ(paragraph->text(), text);
}

void expectBulletPointhWithIndentationAndText(MarkdownPoint::BulletPoint *bulletPoint, uint32_t indentation, const std::string &text) {
    EXPECT_EQ(bulletPoint->text(), text);
    EXPECT_EQ(bulletPoint->indentLevel(), indentation);
}

TEST(markdown_parsing, can_parse_an_empty_page) {
    auto presentation = MarkdownPoint::MarkdownPresentationParser().parse("");

    EXPECT_EQ(presentation.slideCount(), 1);
}

TEST(markdown_parsing, can_parse_multiple_slides) {
    auto presentation = MarkdownPoint::MarkdownPresentationParser().parse("<==><==>");

    EXPECT_EQ(presentation.slideCount(), 3);
}

TEST(markdown_parsing, can_parse_a_heading) {
    auto presentation = parsePresentation("# Heading");

    auto slide = givenAParsedPresentationSlide(presentation);

    blocksAreOfTheFollowingTypes(slide, {"heading"});

    expectHeadingWithSizeAndText(slide->element<MarkdownPoint::Heading *>(0), 1, "Heading");
}

TEST(markdown_parsing, can_parse_a_heading_of_multiple_sizes) {
    auto presentation = parsePresentation("# Heading\n## Heading 2\n### Heading 3\n#### Heading 4");

    auto slide = givenAParsedPresentationSlide(presentation);

    blocksAreOfTheFollowingTypes(slide, {"heading", "heading", "heading", "heading"});

    expectHeadingWithSizeAndText(slide->element<MarkdownPoint::Heading *>(0), 1, "Heading");
    expectHeadingWithSizeAndText(slide->element<MarkdownPoint::Heading *>(1), 2, "Heading 2");
    expectHeadingWithSizeAndText(slide->element<MarkdownPoint::Heading *>(2), 3, "Heading 3");
    expectHeadingWithSizeAndText(slide->element<MarkdownPoint::Heading *>(3), 4, "Heading 4");
}

TEST(markdown_parsing, can_parse_a_paragraph) {
    auto presentation = parsePresentation("Paragraph text is boring");
    
    auto slide = givenAParsedPresentationSlide(presentation);

    expectParagraphWithText(slide->element<MarkdownPoint::Paragraph *>(0), "Paragraph text is boring");
}


TEST(markdown_parsing, can_parse_a_paragraph_and_heading) {
    const MarkdownPoint::Presentation presentation = parsePresentation("# Heading\nParagraph text is boring");
    
    auto slide = givenAParsedPresentationSlide(presentation);

    expectHeadingWithSizeAndText(slide->element<MarkdownPoint::Heading *>(0), 1, "Heading");

    expectParagraphWithText(slide->element<MarkdownPoint::Paragraph *>(1), "Paragraph text is boring");
}

TEST(markdown_parsing, can_parse_a_bullet_point) {
    const MarkdownPoint::Presentation presentation = parsePresentation("* Bullet point\n+ Bullet point 2\n- Bullet point 3");
    
    auto slide = givenAParsedPresentationSlide(presentation);

    blocksAreOfTheFollowingTypes(slide, {"bulletpoint", "bulletpoint", "bulletpoint"});

    expectBulletPointhWithIndentationAndText(slide->element<MarkdownPoint::BulletPoint *>(0), 0, "Bullet point");
    expectBulletPointhWithIndentationAndText(slide->element<MarkdownPoint::BulletPoint *>(1), 0, "Bullet point 2");
    expectBulletPointhWithIndentationAndText(slide->element<MarkdownPoint::BulletPoint *>(2), 0, "Bullet point 3");
}


TEST(markdown_parsing, can_parse_a_indented_bullet_points) {
    const MarkdownPoint::Presentation presentation = parsePresentation("  * Bullet point\n    + Bullet point 2\n      - Bullet point 3");

    auto slide = givenAParsedPresentationSlide(presentation);

    blocksAreOfTheFollowingTypes(slide, {"bulletpoint", "bulletpoint", "bulletpoint"});

    expectBulletPointhWithIndentationAndText(slide->element<MarkdownPoint::BulletPoint *>(0), 1, "Bullet point");
    expectBulletPointhWithIndentationAndText(slide->element<MarkdownPoint::BulletPoint *>(1), 2, "Bullet point 2");
    expectBulletPointhWithIndentationAndText(slide->element<MarkdownPoint::BulletPoint *>(2), 3, "Bullet point 3");
}