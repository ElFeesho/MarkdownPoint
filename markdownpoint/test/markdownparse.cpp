//
// Created by Christopher Sawczuk on 21/11/2016.
//

#include <string>

#include <gtest/gtest.h>
#include <markdownpoint.hpp>

TEST(markdown_parsing, can_parse_an_empty_page) {
    MarkdownPoint::MarkdownPresentationParser p;
    MarkdownPoint::Presentation presentation = p.parse("");

    EXPECT_EQ(presentation.slideCount(), 1);
}

TEST(markdown_parsing, can_parse_multiple_slides) {
    MarkdownPoint::MarkdownPresentationParser p;
    MarkdownPoint::Presentation presentation = p.parse("<==><==>");

    EXPECT_EQ(presentation.slideCount(), 3);
}

TEST(markdown_parsing, can_parse_a_heading) {
    MarkdownPoint::MarkdownPresentationParser p;
    MarkdownPoint::Presentation presentation = p.parse("# Heading");

    MarkdownPoint::Slide *slide = presentation.slide(0);
    EXPECT_EQ(slide->blockCount(), 1);
    EXPECT_EQ(slide->block(0)->type(), "heading");

    MarkdownPoint::Heading *heading = dynamic_cast<MarkdownPoint::Heading *>(slide->block(0));
    EXPECT_EQ(heading->size(), 1);
    EXPECT_EQ(heading->text(), "Heading");
}

TEST(markdown_parsing, can_parse_a_paragraph) {
    MarkdownPoint::MarkdownPresentationParser p;
    MarkdownPoint::Presentation presentation = p.parse("Paragraph text is boring");

    MarkdownPoint::Slide *slide = presentation.slide(0);
    EXPECT_EQ(slide->blockCount(), 1);
    EXPECT_EQ(slide->block(0)->type(), "paragraph");

    MarkdownPoint::Paragraph *paragraph = dynamic_cast<MarkdownPoint::Paragraph *>(slide->block(0));
    EXPECT_EQ(paragraph->text(), "Paragraph text is boring");
}


TEST(markdown_parsing, can_parse_a_paragraph_and_heading) {
    MarkdownPoint::MarkdownPresentationParser p;
    MarkdownPoint::Presentation presentation = p.parse("# Heading\nParagraph text is boring");

    MarkdownPoint::Slide *slide = presentation.slide(0);
    EXPECT_EQ(slide->blockCount(), 2);
    EXPECT_EQ(slide->block(0)->type(), "heading");

    MarkdownPoint::Heading *heading = dynamic_cast<MarkdownPoint::Heading *>(slide->block(0));
    EXPECT_EQ(heading->size(), 1);
    EXPECT_EQ(heading->text(), "Heading");

    EXPECT_EQ(slide->block(1)->type(), "paragraph");
    MarkdownPoint::Paragraph *paragraph = dynamic_cast<MarkdownPoint::Paragraph *>(slide->block(1));
    EXPECT_EQ(paragraph->text(), "Paragraph text is boring");
}

TEST(markdown_parsing, can_parse_a_bullet_point) {
    MarkdownPoint::MarkdownPresentationParser p;
    MarkdownPoint::Presentation presentation = p.parse("* Bullet point\n+ Bullet point 2\n- Bullet point 3");

    MarkdownPoint::Slide *slide = presentation.slide(0);
    EXPECT_EQ(slide->blockCount(), 3);
    EXPECT_EQ(slide->block(0)->type(), "bulletpoint");
    EXPECT_EQ(slide->block(1)->type(), "bulletpoint");
    EXPECT_EQ(slide->block(2)->type(), "bulletpoint");

    MarkdownPoint::BulletPoint *bulletPoint = dynamic_cast<MarkdownPoint::BulletPoint *>(slide->block(0));
    EXPECT_EQ(bulletPoint->indentLevel(), 0);
    EXPECT_EQ(bulletPoint->text(), "Bullet point");

    bulletPoint = dynamic_cast<MarkdownPoint::BulletPoint *>(slide->block(1));
    EXPECT_EQ(bulletPoint->indentLevel(), 0);
    EXPECT_EQ(bulletPoint->text(), "Bullet point 2");

    bulletPoint = dynamic_cast<MarkdownPoint::BulletPoint *>(slide->block(2));
    EXPECT_EQ(bulletPoint->indentLevel(), 0);
    EXPECT_EQ(bulletPoint->text(), "Bullet point 3");
}