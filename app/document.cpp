//
// Created by Christopher Sawczuk on 01/12/2016.
//

#include <iostream>
#include <markdownpoint.hpp>
#include "document.hpp"

namespace HPDF {

    Font::Font(HPDF_Font font) : _font(font) {

    }

    uint32_t Font::measureText(const std::string &text, uint32_t maxWidth, uint32_t fontSize) const {
        HPDF_REAL width = 0;
        return HPDF_Font_MeasureText(_font, (const HPDF_BYTE *) text.c_str(), (HPDF_UINT) text.size(), maxWidth, fontSize, 0, 0, true, &width);
    }

    DrawContext::DrawContext(std::weak_ptr<RawHPDF_Page> target) : _target(target) {

    }

    void DrawContext::rectangle(int32_t x, int32_t y, int32_t w, int32_t h) {
        HPDF_Page_Rectangle(_target.lock().get(), x, y, w, h);
    }

    void DrawContext::circle(int32_t x, int32_t y, float radius) {
        HPDF_Page_Circle(_target.lock().get(), x, y, radius);
    }

    uint32_t DrawContext::text(const Font &font, const std::string &text, uint32_t x, uint32_t y, uint32_t maxWidth,
                               uint32_t fontSize, HPDF_TextAlignment alignment) {
        uint32_t height = 0;
        std::vector<std::string> textLines = MarkdownPoint::splitString(text, [&](const std::string &input) -> unsigned long {
            return font.measureText(input, maxWidth, fontSize);
        });

        for(std::string line : textLines)
        {
            HPDF_UINT len = 0;

            RawHPDF_Page *page = _target.lock().get();
            HPDF_Page_SetFontAndSize(page, font._font, fontSize);
            HPDF_Page_BeginText(page);
            HPDF_Page_TextRect(page, x, y-height, x + maxWidth, HPDF_Page_GetHeight(page), line.c_str(), alignment, &len);
            HPDF_Page_EndText(page);
            height += fontSize + 2;
        }

        if (textLines.size() == 0)
        {
            height += fontSize + 2;
        }
        return height;
    }

    void DrawContext::setFillColour(const Colour &colour) {
        HPDF_Page_SetRGBFill(_target.lock().get(), colour.red(), colour.green(), colour.blue());
    }

    void DrawContext::setStrokeColour(const Colour &colour) {
        HPDF_Page_SetRGBStroke(_target.lock().get(), colour.red(), colour.green(), colour.blue());
    }

    void DrawContext::fill() {
        HPDF_Page_Fill(_target.lock().get());
    }

    void DrawContext::stroke() {
        HPDF_Page_Stroke(_target.lock().get());
    }

    uint32_t DrawContext::width() {
        return (uint32_t) HPDF_Page_GetWidth(_target.lock().get());
    }

    uint32_t DrawContext::height() {
        return (uint32_t) HPDF_Page_GetHeight(_target.lock().get());
    }

    Page::Page(Document *forDocument, HPDF_PageSizes pageSize, HPDF_PageDirection orientation)
            : _page(std::shared_ptr<RawHPDF_Page>(HPDF_AddPage(forDocument->_doc.get()), [=](HPDF_Page page) {}) )
    {
        HPDF_Page_SetSize(_page.get(), pageSize, orientation);
    }

    void Page::strokeWithColour(const Colour &colour, GeometricDrawOperation  operations) {
        DrawContext context{std::weak_ptr<RawHPDF_Page>(_page)};
        context.setStrokeColour(colour);
        operations(context);
        context.stroke();
    }

    void Page::fillWithColour(const Colour &colour, GeometricDrawOperation  operations) {
        DrawContext context{std::weak_ptr<RawHPDF_Page>(_page)};
        context.setFillColour(colour);
        operations(context);
        context.fill();
    }

    void Page::textWithColour(const Colour &colour, TextDrawOperation operations) {
        DrawContext context {std::weak_ptr<RawHPDF_Page>(_page)};
        HPDF_Page_SetRGBFill(_page.get(), colour.red(), colour.green(), colour.blue());
        operations(context);
    }

    Document::Document() :
            _doc(unique_doc_ptr(HPDF_New([](HPDF_STATUS errorCode, HPDF_STATUS errorReason, void *){
                std::cout << "Error "<< std::hex << errorCode  << ", " << errorReason << std::dec << std::endl;
            }, nullptr), HPDF_Free))
    {
    }

    Page &Document::addPage(HPDF_PageSizes pageSize, HPDF_PageDirection orientation) {
        _pages.emplace_back(this, pageSize, orientation);
        return _pages[_pages.size()-1];
    }

    void Document::writeToFile(const std::string &filename) {
        HPDF_SaveToFile(_doc.get(), filename.c_str());
    }

    Font Document::loadFont(const std::string &fontName) {
        return Font(HPDF_GetFont(_doc.get(), fontName.c_str(), nullptr));
    }

    Page &Document::page(uint32_t index) {
        return _pages.at(index);
    }

    float Colour::red() const {
        return _r;
    }

    float Colour::green() const {
        return _g;
    }

    float Colour::blue() const {
        return _b;
    }

}
