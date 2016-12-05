#include <iostream>
#include <markdownpoint.hpp>
#include <hpdf.h>
#include <fstream>

#include "document.hpp"

class HPdfPresentationRenderer : public MarkdownPoint::Renderer {
public:
    HPdfPresentationRenderer() : _doc{}, _font{_doc.loadFont("Helvetica")} {

    }

    void renderPage(MarkdownPoint::Slide *slide) override {
        addNewPage();
    }

    void renderBulletPoint(const MarkdownPoint::BulletPoint &bulletPoint) override {

        if (bulletPoint.indentLevel() < 2) {
            HPDF::Page::GeometricDrawOperation op = [&](HPDF::DrawContext &ctx) {
                ctx.circle(textBoundaryOffset + bulletPoint.indentLevel() * 15 + 5, ctx.height() - textYPosition - 10, 3);
            };
            if (bulletPoint.indentLevel() == 0)
            {
                getCurrentPage().fillWithColour(textColour, op);
            }
            else
            {
                getCurrentPage().strokeWithColour(textColour, op);
            }
        } else {
            getCurrentPage().fillWithColour(textColour, [&](HPDF::DrawContext &ctx) {
                ctx.rectangle(textBoundaryOffset + bulletPoint.indentLevel() * 15 + 2, ctx.height() - textYPosition - 12, 6, 6);
            });
        }

        renderLineOfText(bulletPoint.text(), (bulletPoint.indentLevel() + 1) * 3 + 1);
    }

    void renderHeading(const MarkdownPoint::Heading &heading) override {
        unsigned int headingSize = heading.size() - 1;
        int fontSize = sizes[headingSize];
        int margin = margins[headingSize];
        getCurrentPage().textWithColour(textColour, [&](HPDF::DrawContext &ctx) {
            textYPosition += ctx.text(_font, heading.text(), textBoundaryOffset, ctx.height() - textYPosition,
                                      ctx.width() - textBoundaryOffset*2, fontSize, heading.size() == 1 ? HPDF_TALIGN_CENTER : HPDF_TALIGN_LEFT);
            textYPosition += margin-fontSize;
        });
    }

    void renderParagraph(const MarkdownPoint::Paragraph &paragraph) override {
        renderLineOfText(paragraph.text());
    }

    void renderLineOfText(const std::string &line, uint32_t textIndent = 0) {
        getCurrentPage().textWithColour(textColour, [&](HPDF::DrawContext &ctx) {
            textYPosition += ctx.text(_font, line, textBoundaryOffset + textIndent * 5, ctx.height() - textYPosition, ctx.width() - textBoundaryOffset * 2, 16);
        });
    }

    HPDF::Page &getCurrentPage() {
        return _doc.page(_pageCount - 1);
    }

    void writeToFile(const std::string &filename) {
        _doc.writeToFile(filename);
    }

private:
    void addNewPage() {
        HPDF::Page &page = _doc.addPage(HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
        page.fillWithColour(bgColour, [](HPDF::DrawContext &ctx) {
            ctx.rectangle(0, 0, ctx.width(), ctx.height());
        });

        textYPosition = 25;
        _pageCount++;
    }

    HPDF::Document _doc;
    HPDF::Font _font;
    uint32_t _pageCount{0};

    uint32_t textBoundaryOffset{100};
    uint32_t textYPosition{25};

    HPDF::Colour textColour{0xbbbbbb_rgb};
    HPDF::Colour bgColour{0x444444_rgb};

    int sizes[4]{48, 36, 24, 18};
    int margins[4]{56, 48, 36, 24};
};

std::string readFile(char *filename) {
    std::ifstream file(filename);
    file.unsetf(std::ios_base::skipws);
    return std::string(std::istream_iterator<char>(file), std::istream_iterator<char>());
}

int main(int argc, char **argv) {

    std::string markdown = readFile(argv[1]);

    MarkdownPoint::MarkdownPresentationParser parser;
    MarkdownPoint::Presentation presentation = parser.parse(markdown);

    HPdfPresentationRenderer renderer;
    MarkdownPoint::PresentationRenderer presentationRenderer(&renderer);
    presentationRenderer.render(presentation);

    renderer.writeToFile(argv[2]);

    return 0;
}
