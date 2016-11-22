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