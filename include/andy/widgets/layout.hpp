#pragma once

#include <array>
#include <vector>
#include <map>

#include <andy/color.hpp>
#include <andy/xml.hpp>

#include "widget.hpp"

namespace andy
{
    namespace widgets
    {
        struct layout_style {
            enum layout_type : uint8_t {
                flexible,
                layout_type_max
            };

            enum layout_flex_direction : uint8_t {
                vertical,
                horizontal,
                layout_flex_direction_max
            };

            enum layout_align_items : uint8_t {
                start,
                center,
                end,
                layout_align_items_max
            };

            layout_type           type      = layout_type::flexible;
            layout_flex_direction direction = layout_flex_direction::vertical;
            layout_align_items    align_items = layout_align_items::start;
        };

        struct border {
            int width = 0;
            andy::color color = andy::color(0, 0, 0, 0);
            int radius = 0;
        };

        struct layout : widget {
            layout_style style_layout;

            std::vector<std::shared_ptr<widget>> childreans;

            andy::size calculate_min_size() override;
            void calculate_layout(int __x, int __y, int __w, int __h);

            void render(void* target) override;
            void parse(void* target, andy::xml::schema& schema, andy::xml& xml) override;
        };
    }
}