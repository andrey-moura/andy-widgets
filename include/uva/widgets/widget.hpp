#pragma once

#include <uva/color.hpp>
#include <uva/size.hpp>

#include <cstdint>

#include <uva/xml.hpp>

struct SDL_Renderer;

namespace uva
{
    namespace widgets
    {
        enum widget_cursor : uint8_t {
            widget_cursor_default,
            widget_cursor_pointer,
            widget_cursor_max
        };

        struct widget_style {
            widget_style() = default;
            widget_style(int flex) : flex(flex) {}

            uint8_t             flex = 0;
            widget_cursor cursor = widget_cursor::widget_cursor_default;

            int        padding = 0;
            int        gap     = 0;
            uva::color color = uva::color(0, 0, 0, 255);
            uva::color background_color = uva::color(0, 0, 0, 0);
            int border_radius = 0;
        };

        class widget {
        public:
            widget() = default;
            widget(int x, int y, int w, int h, widget_style style = {});
        public:
            int x = 0;
            int y = 0;

            int w;
            int h;

            std::string id;
        public:
            widget_style style;

            virtual uva::size calculate_min_size() { return { w, h }; }
            virtual void render(SDL_Renderer* renderer);
            virtual void parse(SDL_Renderer* renderer, uva::xml::schema& schema, uva::xml& xml);
            virtual bool on_char(std::string c) { return false; }
        };
    };
};