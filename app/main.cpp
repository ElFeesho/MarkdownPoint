#include <iostream>
#include <markdownpoint.hpp>
#include <hpdf.h>

class HPdfPresentationRenderer : public MarkdownPoint::Renderer {
public:
    HPdfPresentationRenderer() {
        pdf = HPDF_New([](HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
            std::cerr << "Error (" << error_no << ", " << detail_no << ")" << std::endl;
        }, nullptr);

        helvetica = HPDF_GetFont(pdf, "Helvetica", NULL);
        courier = HPDF_GetFont(pdf, "Courier", NULL);
    }

    ~HPdfPresentationRenderer() override {
        HPDF_Free(pdf);
    }

    void renderPage(MarkdownPoint::Slide *slide) override {
        addNewPage();
    }

    void renderHeading(MarkdownPoint::Heading *heading) override {
        HPDF_Page_SetFontAndSize(currentPage, helvetica, sizes[heading->size()-1]);
        float tw = HPDF_Page_TextWidth(currentPage, heading->text().c_str());
        HPDF_Page_SetRGBFill(currentPage, 0.8, 0.8, 0.8);
        HPDF_Page_BeginText(currentPage);
        HPDF_Page_TextOut(currentPage, (HPDF_Page_GetWidth(currentPage) - tw) / 2, HPDF_Page_GetHeight(currentPage) - 100, heading->text().c_str());
        HPDF_Page_EndText(currentPage);
    }

    void renderParagraph(MarkdownPoint::Paragraph *paragraph) override {
        const char *text = paragraph->text().c_str();
        std::cout << "Text length: " << paragraph->text().size() << std::endl;
        HPDF_REAL width = 0;
        HPDF_UINT outwidth = HPDF_Font_MeasureText(helvetica, (const HPDF_BYTE *) text, (HPDF_UINT) paragraph->text().size(), textBoundaryWidth, 16, 0, 0, true, &width);
        HPDF_Page_SetFontAndSize(currentPage, helvetica, 16);
        std::cout << "Out width: " << outwidth << std::endl;
        std::cout << "width: " << width << std::endl;

        HPDF_UINT len = 0;
        HPDF_Page_SetRGBFill(currentPage, 0.8, 0.8, 0.8);
        HPDF_Page_BeginText(currentPage);
        HPDF_Page_TextRect(currentPage, 100, HPDF_Page_GetHeight(currentPage) - textYPosition, textBoundaryOffset+textBoundaryWidth, 100, text, HPDF_TALIGN_LEFT, &len);
        if (outwidth != paragraph->text().size())
        {
            textYPosition += 18;
        }
        HPDF_Page_EndText(currentPage);
        textYPosition += 18;
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
        textBoundaryWidth = HPDF_Page_GetWidth(currentPage)-textBoundaryOffset*2;
        textYPosition = 125;
    }

    HPDF_Doc pdf;
    HPDF_Page currentPage;
    HPDF_Font helvetica;
    HPDF_Font courier;

    HPDF_REAL textBoundaryWidth;
    HPDF_REAL textBoundaryOffset { 100 };
    HPDF_REAL textYPosition { 125 };

    int sizes[4] { 48, 36, 24, 18 };
};

int main(int argc, char **argv) {
    MarkdownPoint::MarkdownPresentationParser parser;
    MarkdownPoint::Presentation presentation = parser.parse(
            "# Introduction\nMarkdown is a useful tool and is understood by anyone who has spent considerable time on GitHub.\nIt can be read as plain text, as well as formatted by a viewer.");
    HPdfPresentationRenderer renderer;
    MarkdownPoint::PresentationRenderer presentationRenderer(&renderer);
    presentationRenderer.render(presentation);

    renderer.writeToFile("test.pdf");
    return 0;
}
