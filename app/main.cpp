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
        HPDF_Page_SetFontAndSize(currentPage, helvetica, 16);
        HPDF_UINT len = 0;
        HPDF_Page_SetRGBFill(currentPage, 0.8, 0.8, 0.8);
        HPDF_Page_BeginText(currentPage);
        HPDF_Page_TextRect(currentPage, 100, HPDF_Page_GetHeight(currentPage) - 125, HPDF_Page_GetWidth(currentPage), 100, paragraph->text().c_str(), HPDF_TALIGN_LEFT, &len);
        std::cout << "Text length: " << len << std::endl;
        HPDF_Page_EndText(currentPage);
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
    }

    HPDF_Doc pdf;
    HPDF_Page currentPage;
    HPDF_Font helvetica;
    HPDF_Font courier;
    int sizes[4] { 48, 36, 24, 18 };
};

int main(int argc, char **argv) {
    MarkdownPoint::MarkdownPresentationParser parser;
    MarkdownPoint::Presentation presentation = parser.parse(
            "# This is a test\nWoop<==># Of the markdown<==># Presentation maker<==># MarkdownPoint");
    HPdfPresentationRenderer renderer;
    MarkdownPoint::PresentationRenderer presentationRenderer(&renderer);
    presentationRenderer.render(presentation);

    renderer.writeToFile("test.pdf");
    return 0;
}
