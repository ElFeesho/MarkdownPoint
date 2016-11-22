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
        int _size;
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


}

#endif