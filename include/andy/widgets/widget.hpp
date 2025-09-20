#pragma once

#include <cstdint>

#include "andy/color.hpp"
#include "andy/size.hpp"
#include "andy/xml.hpp"
#include "andy/drawing/basic_renderer.hpp"

namespace andy
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
            andy::color color = andy::color(0, 0, 0, 255);
            andy::color background_color = andy::color(0, 0, 0, 0);
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

            virtual andy::size calculate_min_size(andy::drawing::basic_renderer& renderer) { return { w, h }; }
            virtual void render(andy::drawing::basic_renderer& renderer) { }
            virtual void parse(andy::xml::schema& schema, andy::xml& xml);
            virtual bool on_char(char c) { return false; }
        };
    };
};