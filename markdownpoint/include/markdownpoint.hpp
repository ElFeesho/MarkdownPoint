#ifndef __MARKDOWN_POINT_HPP__
#define __MARKDOWN_POINT_HPP__

#include <vector>

namespace MarkdownPoint {

    class Block {
    public:
        Block() {}
        virtual ~Block(){}
        virtual std::string type() = 0;
    };

    class Heading : public Block {
    public:
        Heading(const std::string &text, int size = 1);
        virtual std::string type();
        uint32_t size();
        std::string text();
    private:
        std::string _text;
        uint32_t _size;
    };

    class Paragraph : public Block {
    public:
        Paragraph(const std::string &text);
        std::string type();
        std::string text();
    private:
        std::string _text;
    };

    class Slide {
    public:
        Slide();

        void addBlock(Block *block);
        Block *block(uint32_t idx);
        ssize_t blockCount();
    private:
        std::vector<Block *> _blocks;
    };

    class Presentation {
    public:
        Presentation();

        ssize_t slideCount();

        Slide *addSlide();

        Slide *slide(uint32_t idx);
    private:
        std::vector<Slide *> _slides;
    };

    class MarkdownPresentationParser {
    public:
        MarkdownPoint::Presentation parse(const std::string &markdown);

    private:
        std::vector<std::string> splitSlides(const std::string &rawInput);

        std::vector<std::string> split(const std::string &rawInput, const std::string &delimeter);
    };

    class Renderer {
    public:
        virtual ~Renderer(){}
        virtual void renderPage(Slide *slide) = 0;
        virtual void renderHeading(Heading *heading) = 0;
        virtual void renderParagraph(Paragraph *paragraph) = 0;
    };

    class PresentationRenderer {
    public:
        PresentationRenderer(Renderer* renderer);
        void render(Presentation &p);
    private:
        Renderer *_renderer;
    };
}

#endif