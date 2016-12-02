//
// Created by Christopher Sawczuk on 01/12/2016.
//

#ifndef MARKDOWNPOINT_HPDFDOCUMENT_HPP
#define MARKDOWNPOINT_HPDFDOCUMENT_HPP

#include <hpdf.h>
#include <memory>
#include <functional>
#include <vector>
#include <string>

namespace HPDF {

    using RawHPDF_Doc = typename std::remove_pointer<HPDF_Doc>::type;
    using RawHPDF_Page = typename std::remove_pointer<HPDF_Page>::type;

    class Document;
    class Page;
    class Colour;

    class Page {
    public:
        Page(Document *forDocument);

        void setFillColour(const Colour &colour);

        void setStrokeColour(const Colour &colour);

        void setSize(HPDF_PageSizes size, _HPDF_PageDirection orientation);

        void drawRectangle(int32_t x, int32_t y, int32_t w, int32_t h);

        float width();

        float height();

        void fill();
    private:
        std::shared_ptr<RawHPDF_Page> _page;
    };

    class Document {
    public:
        Document();

        Page &addPage();

        void writeToFile(const std::string &filename);

        friend class Page;
    private:
        std::unique_ptr<RawHPDF_Doc, std::function<void(RawHPDF_Doc*)>> _doc;

        std::vector<Page> _pages;
    };

    class Colour {
    public:
        constexpr Colour(float r, float g, float b) : _r(r), _g(g), _b(b) {}

        float red() const;
        float green() const;
        float blue() const;
    private:
        float _r, _g, _b;
    };
}

constexpr HPDF::Colour operator"" _rgb(unsigned long long int input) {
    return HPDF::Colour(((0xff0000 & input) >> 16) / 255.f, ((0xff00 & input) >> 8) / 255.f, (0xff & input) / 255.f);
}


#endif //MARKDOWNPOINT_HPDFDOCUMENT_HPP
