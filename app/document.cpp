//
// Created by Christopher Sawczuk on 01/12/2016.
//

#include "document.hpp"

namespace HPDF {
    Page::Page(Document *forDocument) : _page(std::shared_ptr<RawHPDF_Page>(HPDF_AddPage(forDocument->_doc.get()),[=](HPDF_Page page) {
        HPDF_Dict_Free(page);
    })){

    }

    void Page::setFillColour(const Colour &colour) {
        HPDF_Page_SetRGBFill(_page.get(), colour.red(), colour.green(), colour.blue());
    }

    void Page::setStrokeColour(const Colour &colour) {
        HPDF_Page_SetRGBStroke(_page.get(), colour.red(), colour.green(), colour.blue());
    }

    void Page::setSize(HPDF_PageSizes size, HPDF_PageDirection orientation) {
        HPDF_Page_SetSize(_page.get(), size, orientation);
    }

    void Page::fill() {
        HPDF_Page_Fill(_page.get());
    }

    void Page::drawRectangle(int32_t x, int32_t y, int32_t w, int32_t h) {
        HPDF_Page_Rectangle(_page.get(), x, y, w, h);
    }

    float Page::width() {
        return HPDF_Page_GetWidth(_page.get());
    }

    float Page::height() {
        return HPDF_Page_GetHeight(_page.get());
    }


    Document::Document() :
            _doc(std::unique_ptr<RawHPDF_Doc, std::function<void(RawHPDF_Doc*)>>(HPDF_New([](HPDF_STATUS, HPDF_STATUS, void *){}, nullptr), HPDF_Free))
    {
    }

    Page &Document::addPage() {
        _pages.emplace_back(this);
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
