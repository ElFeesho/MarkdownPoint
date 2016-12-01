//
// Created by Christopher Sawczuk on 25/11/2016.
//

#ifndef MARKDOWNPOINT_PRESENTATIONRENDERER_H
#define MARKDOWNPOINT_PRESENTATIONRENDERER_H

#include <presentation.hpp>
#include <heading.hpp>
#include <paragraph.hpp>
#include "bulletpoint.hpp"

namespace MarkdownPoint {

    class Renderer {
    public:
        virtual ~Renderer(){}
        virtual void renderPage(Slide *slide) = 0;
        virtual void renderHeading(const Heading &heading) = 0;
        virtual void renderParagraph(const Paragraph &paragraph) = 0;
        virtual void renderBulletPoint(const BulletPoint &bulletPoint) = 0;
    };

    class PresentationRenderer {
    public:
        PresentationRenderer(Renderer* renderer);
        void render(Presentation &p);
    private:
        Renderer *_renderer;
    };
}

#endif //MARKDOWNPOINT_PRESENTATIONRENDERER_H
