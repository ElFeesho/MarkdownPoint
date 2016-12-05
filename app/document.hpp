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

    class DrawContext;

    class Font;

    class Font {
    public:
        friend class Document;

        friend class DrawContext;

        uint32_t measureText(const std::string &text, uint32_t maxWidth, uint32_t fontSize) const;

    private:
        Font(HPDF_Font font);

        HPDF_Font _font;
    };

    class DrawContext {
    public:
        void rectangle(int32_t x, int32_t y, int32_t w, int32_t h);

        uint32_t
        text(const Font &font, const std::string &text, uint32_t x, uint32_t y, uint32_t maxWidth, uint32_t fontSize,
             HPDF_TextAlignment alignment = HPDF_TALIGN_LEFT);

        void circle(int32_t x, int32_t y, float radius);

        uint32_t width();

        uint32_t height();

        friend class Page;

    private:
        DrawContext(std::weak_ptr<RawHPDF_Page> target);

        std::weak_ptr<RawHPDF_Page> _target;

        void setFillColour(const Colour &colour);

        void setStrokeColour(const Colour &colour);

        void fill();

        void stroke();
    };

    class Page {
    public:

        using GeometricDrawOperation = std::function<void(DrawContext &)>;
        using TextDrawOperation = std::function<void(DrawContext &)>;

        Page(Document *forDocument, HPDF_PageSizes pageSize, HPDF_PageDirection orientation);

        void strokeWithColour(const Colour &colour, GeometricDrawOperation operations);

        void fillWithColour(const Colour &colour, GeometricDrawOperation operations);

        void textWithColour(const Colour &colour, TextDrawOperation operations);


    private:
        std::shared_ptr<RawHPDF_Page> _page;
    };

    class Document {
    public:
        Document();

        Page &addPage(HPDF_PageSizes pageSize, HPDF_PageDirection orientation);

        Font loadFont(const std::string &fontName);

        Page &page(uint32_t index);

        void writeToFile(const std::string &filename);

        friend class Page;

    private:
        using unique_doc_ptr = std::unique_ptr<RawHPDF_Doc, std::function<void(RawHPDF_Doc *)>>;
        unique_doc_ptr _doc;

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

constexpr HPDF::Colour operator "" _rgb(unsigned long long int input) {
    return HPDF::Colour(((0xff0000 & input) >> 16) / 255.f, ((0xff00 & input) >> 8) / 255.f, (0xff & input) / 255.f);
}


#endif //MARKDOWNPOINT_HPDFDOCUMENT_HPP
