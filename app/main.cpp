#include <iostream>
#include <markdownpoint.hpp>
#include <hpdf.h>
#include <fstream>

#include "document.hpp"

class HPdfPresentationRenderer : public MarkdownPoint::Renderer {
public:
    HPdfPresentationRenderer() {
        pdf = HPDF_New([](HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
            std::cerr << "Error (" << error_no << ", " << detail_no << ")" << std::endl;
        }, nullptr);

        helvetica = HPDF_GetFont(pdf, "Helvetica", NULL);
    }

    ~HPdfPresentationRenderer() override {
        HPDF_Free(pdf);
    }

    void renderPage(MarkdownPoint::Slide *slide) override {
        addNewPage();
    }

    void renderBulletPoint(const MarkdownPoint::BulletPoint &bulletPoint) override {

        if (bulletPoint.indentLevel() < 2)
        {
            HPDF_Page_Circle(currentPage, textBoundaryOffset + bulletPoint.indentLevel() * 15 + 5, HPDF_Page_GetHeight(currentPage) - textYPosition - 9 - 16, 3);
        }
        else
        {
            HPDF_Page_Rectangle(currentPage, textBoundaryOffset + bulletPoint.indentLevel() * 15 + 3, HPDF_Page_GetHeight(currentPage) - textYPosition - 12 - 16, 6, 6);
        }

        if (bulletPoint.indentLevel() == 1)
        {
            HPDF_Page_Stroke(currentPage);
        }
        else
        {
            HPDF_Page_Fill(currentPage);
        }
        renderLineOfText(bulletPoint.text(), 15 * (bulletPoint.indentLevel()+1));
    }

    void renderHeading(const MarkdownPoint::Heading &heading) override {
        unsigned int headingSize = heading.size() - 1;
        int fontSize = sizes[headingSize];
        int margin = margins[headingSize];
        HPDF_Page_SetFontAndSize(currentPage, helvetica, fontSize);
        float tw = HPDF_Page_TextWidth(currentPage, heading.text().c_str());
        HPDF_Page_SetRGBFill(currentPage, 0.8, 0.8, 0.8);
        HPDF_Page_BeginText(currentPage);
        uint32_t len;
        HPDF_Page_TextRect(currentPage, textBoundaryOffset, HPDF_Page_GetHeight(currentPage) - textYPosition - (margin - fontSize), textBoundaryOffset + textBoundaryWidth, textBoundaryOffset, heading.text().c_str(), headingSize == 0 ? HPDF_TALIGN_CENTER : HPDF_TALIGN_LEFT, &len);
        HPDF_Page_EndText(currentPage);

        textYPosition += margin;
    }

    void renderParagraph(const MarkdownPoint::Paragraph &paragraph) override {
        const char *text = paragraph.text().c_str();
        HPDF_REAL width = 0;

        std::vector<std::string> textLines = MarkdownPoint::splitString(paragraph.text(), [&](const std::string &input) -> unsigned long {
            return HPDF_Font_MeasureText(helvetica, (const HPDF_BYTE *) input.c_str(), (HPDF_UINT) paragraph.text().size(), textBoundaryWidth, 16, 0, 0, true, &width);
        });

        for(std::string line : textLines)
        {
            renderLineOfText(line);
        }

        if (textLines.size() == 0)
        {
            textYPosition += 20;
        }
    }

    void renderLineOfText(const std::string &line, uint32_t textIndent = 0) {
        HPDF_UINT len = 0;
        HPDF_Page_SetRGBFill(currentPage, 0.8, 0.8, 0.8);
        int fontSize = 16;
        HPDF_Page_SetFontAndSize(currentPage, helvetica, fontSize);
        HPDF_Page_BeginText(currentPage);
        HPDF_Page_TextRect(currentPage, textBoundaryOffset + textIndent, HPDF_Page_GetHeight(currentPage) - textYPosition - fontSize, textBoundaryOffset + textBoundaryWidth, textBoundaryOffset, line.c_str(), HPDF_TALIGN_LEFT, &len);
        HPDF_Page_EndText(currentPage);
        textYPosition += 20;
    }

    void writeToFile(const std::string &filename) {
        HPDF_SaveToFile(pdf, filename.c_str());
    }

private:
    void addNewPage() {
        currentPage = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(currentPage, HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
        HPDF_Page_SetRGBFill(currentPage, 0.3, 0.3, 0.3);
        HPDF_Page_Rectangle(currentPage, 0, 0, HPDF_Page_GetWidth(currentPage), HPDF_Page_GetHeight(currentPage));
        HPDF_Page_Fill(currentPage);
        HPDF_Page_SetRGBStroke(currentPage, 0.8, 0.8, 0.8);
        HPDF_Page_SetRGBFill(currentPage, 0.8, 0.8, 0.8);
        textBoundaryWidth = HPDF_Page_GetWidth(currentPage)-textBoundaryOffset*2;
        textYPosition = 25;
    }

    HPDF_Doc pdf;
    HPDF_Page currentPage;
    HPDF_Font helvetica;

    HPDF_REAL textBoundaryWidth;
    HPDF_REAL textBoundaryOffset { 100 };
    HPDF_REAL textYPosition { 125 };

    int sizes[4] { 48, 36, 24, 18 };
    int margins[4] { 56, 48, 36, 24 };
};

std::string readFile(char *filename)
{
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
    
    HPDF::Document document;
    HPDF::Page page = document.addPage();
    page.setSize(HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
    page.setFillColour(0x333333_rgb);
    page.drawRectangle(0, 0, page.width(), page.height());
    page.fill();

    document.writeToFile("test2.pdf");

    return 0;
}
