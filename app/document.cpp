//
// Created by Christopher Sawczuk on 01/12/2016.
//

#include <iostream>
#include "document.hpp"

namespace HPDF {
    DrawContext::DrawContext(Page &target) : _target(target) {

    }

    void DrawContext::rectangle(int32_t x, int32_t y, int32_t w, int32_t h) {
        _target.drawRectangle(x, y, w, h);
    }

    void DrawContext::circle(int32_t x, int32_t y, float radius) {
        _target.drawCircle(x, y, radius);
    }

    int32_t DrawContext::width() {
        return _target.width();
    }

    int32_t DrawContext::height() {
        return _target.height();
    }

    Page::Page(Document *forDocument, HPDF_PageSizes pageSize, HPDF_PageDirection orientation)
            : _page(std::shared_ptr<RawHPDF_Page>(HPDF_AddPage(forDocument->_doc.get()), [=](HPDF_Page page) {}) )
    {
        HPDF_Page_SetSize(_page.get(), pageSize, orientation);
    }

    void Page::setFillColour(const Colour &colour) {
        HPDF_Page_SetRGBFill(_page.get(), colour.red(), colour.green(), colour.blue());
    }

    void Page::setStrokeColour(const Colour &colour) {
        HPDF_Page_SetRGBStroke(_page.get(), colour.red(), colour.green(), colour.blue());
    }

    void Page::fill() {
        HPDF_Page_Fill(_page.get());
    }

    void Page::stroke() {
        HPDF_Page_Stroke(_page.get());
    }

    void Page::drawRectangle(int32_t x, int32_t y, int32_t w, int32_t h) {
        HPDF_Page_Rectangle(_page.get(), x, y, w, h);
    }

    void Page::drawCircle(int32_t x, int32_t y, float radius) {
        HPDF_Page_Circle(_page.get(), x, y, radius);
    }

    int32_t Page::width() {
        return (int32_t) HPDF_Page_GetWidth(_page.get());
    }

    int32_t Page::height() {
        return (int32_t) HPDF_Page_GetHeight(_page.get());
    }

    void Page::strokeWithColour(const Colour &colour, std::function<void(DrawContext &)> operations) {
        DrawContext context{*this};
        setStrokeColour(colour);
        operations(context);
        stroke();
    }

    void Page::fillWithColour(const Colour &colour, std::function<void(DrawContext &)> operations) {
        DrawContext context{*this};
        setFillColour(colour);
        operations(context);
        fill();
    }

    Document::Document() :
            _doc(unique_doc_ptr(HPDF_New([](HPDF_STATUS errorCode, HPDF_STATUS errorReason, void *){
                std::cout << "Error " << errorCode  << ", " << errorReason << std::endl;
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
