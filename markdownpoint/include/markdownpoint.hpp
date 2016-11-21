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
    private:
        int _size;
    };

    class Slide {
    public:
        Slide();

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

    private:
        std::vector<Slide *> _slides;
    };
}

#endif