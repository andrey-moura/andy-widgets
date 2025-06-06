#pragma once

#include <cstdint>
#include <string>

#include "widget.hpp"

namespace uva
{
    namespace widgets
    {
        enum text_vertical_alignment : uint8_t {
            text_vertical_alignment_top,
            text_vertical_alignment_center,
            text_vertical_alignment_bottom,
            text_vertical_alignment_max
        };

        enum text_horizontal_alignment : uint8_t {
            text_horizontal_alignment_left,
            text_horizontal_alignment_center,
            text_horizontal_alignment_right,
            text_horizontal_alignment_max
        };

        struct text_element_style {
            std::string font;
            size_t font_size;
            text_vertical_alignment vertical_alignment;
            text_horizontal_alignment horizontal_alignment;
        };

        struct text : public widget {
            text() = default;
            text(std::string __content, void* target, size_t font_size = 12);
            std::string content;

            text_element_style text_style;

            void render(void* target) override;
            void parse(void* target, uva::xml::schema& schema, uva::xml& xml) override;
        };
    }
}